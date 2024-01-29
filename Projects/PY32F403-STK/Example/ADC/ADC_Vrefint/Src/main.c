/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef        AdcHandle;
uint16_t                 aADCxConvertedData;
TIM_HandleTypeDef        TimHandle;
TIM_MasterConfigTypeDef  sMasterConfig;
uint16_t                 T_VCC;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */ 
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig(); 

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize UART */
  BSP_USART_Config();
  
  /* Configure ADC */
  APP_AdcConfig();
  
  /* ADC Calibrate */ 
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
    
  /* ADC Start */
  HAL_ADC_Start(&AdcHandle);

  while(1)
  {
   /* Poll For ADC Conversion */
    if(HAL_ADC_PollForConversion(&AdcHandle, 2000) == HAL_OK)
    {
      /* Get ADC Value */
      aADCxConvertedData = HAL_ADC_GetValue(&AdcHandle); 
       
      T_VCC = 4095*1200/aADCxConvertedData; 

      /* Printf VCC Data */
      printf("VCC : %dmV",T_VCC);
    }
    HAL_Delay(1000);
  }   
}

/**
  * @brief  ADC configure function
  * @param  None
  * @retval None
  */
static void APP_AdcConfig(void)
{
  ADC_ChannelConfTypeDef   sConfig={0}; 
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInit={0};
  
  __HAL_RCC_ADC1_CLK_ENABLE();                                           /* Enable ADC Clock */
  
  RCC_PeriphCLKInit.PeriphClockSelection= RCC_PERIPHCLK_ADC;
  RCC_PeriphCLKInit.AdcClockSelection   = RCC_ADCPCLK2_DIV8;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInit);
  
  AdcHandle.Instance = ADC1;
  
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;             /* 12-bit resolution for converted data */
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;            /* Right-alignment for converted data  */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DISABLE;               /* Scan Mode Disable */
  AdcHandle.Init.ContinuousConvMode    = ENABLE;                         /* Continuous Mode */
  AdcHandle.Init.NbrOfConversion       = 1;                              /* Conversion Number 1 */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                        /* Disable Discontinuous Mode */
  AdcHandle.Init.NbrOfDiscConversion   = 1;                              /* Discontinuous Number 1 */
  AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;             /* Software Trigger */

  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig.Channel      = ADC_CHANNEL_VREFINT;
  sConfig.Rank         = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
  /* ADC Channel Configure */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  System clock configuration function.
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef  OscInitstruct = {0};
  RCC_ClkInitTypeDef  ClkInitstruct = {0};
  
  OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | 
                                  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
  OscInitstruct.HSEState        = RCC_HSE_OFF;                              /* Disable HSE */
/* OscInitstruct.HSEFreq         = RCC_HSE_16_32MHz; */                     /* HSE frequency range 16~32M */
  OscInitstruct.HSI48MState     = RCC_HSI48M_OFF;                           /* Disable HSI48M */
  OscInitstruct.HSIState        = RCC_HSI_ON;                               /* Enable HSI */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                              /* Disable HSE */
/* OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH; */                    /* LSEDrive ：High */
  OscInitstruct.LSIState        = RCC_LSI_OFF;                              /* Disable LSI */
  OscInitstruct.PLL.PLLState    = RCC_PLL_OFF;                              /* Disable PLL */
/*  OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE; */                   /* PLL clock source selection HSE */
/*  OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL6; */                        /* PLL clock source 6-fold frequency */
  /* Configure oscillator */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_HSI;                 /* Select HSI as system clock */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock 1 division */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock 1 division */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV1;                        /* APB2 clock 1 division */
  /* Configure clock source */
  if(HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
