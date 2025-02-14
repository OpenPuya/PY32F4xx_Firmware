/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
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
#include "py32f403xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define HAL_ADC_TSCAL1                  (*(uint32_t *)(0x1fff5310))  /*!< Temperature Scale1 */
#define HAL_ADC_TSCAL2                  (*(uint32_t *)(0x1fff5400))  /*!< Temperature Scale2 */
#define Vcc_Power     3.3l                                            /* VCC power supply voltage, modify according to actual situation  */
#define TScal1        (float)((HAL_ADC_TSCAL1) * 3.3 / Vcc_Power)     /* Voltage corresponding to calibration value at 25 ℃ */
#define TScal2        (float)((HAL_ADC_TSCAL2) * 3.3 / Vcc_Power)     /* Voltage corresponding to calibration value at 85 ℃ */
#define TStem1        25l                                             /* 25 ℃ */
#define TStem2        85l                                             /* 85 ℃ */
#define Temp_k        ((float)(TStem2-TStem1)/(float)(TScal2-TScal1)) /* Temperature calculation */

/* Private variables ---------------------------------------------------------*/
__IO uint32_t wait_loop_index = 0;
__IO uint16_t hADCxConvertedData_Temperature_DegreeCelsius = 0;
__IO uint16_t ADCxConvertedData =0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcConfig(void);
static void APP_AdcCalibrate(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Enable SYSCFG and PWR clock */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /* 3 bits for pre-emption priority, 0 bits for subpriority */
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

  /* Configure system clock */
  APP_SystemClockConfig();

   BSP_USART_Config();
  
  /* ADC configuration */
  APP_AdcConfig();
  
  /* ADC calibration */
  APP_AdcCalibrate();
  
  LL_mDelay(1);
 
  /* Enable ADC */
  LL_ADC_Enable(ADC1);

  LL_mDelay(1);

  while (1)
  {
    LL_ADC_REG_StartConversionSWStart(ADC1);
    while(LL_ADC_IsActiveFlag_EOS(ADC1)==0)
    {

    }
    LL_ADC_ClearFlag_EOS(ADC1);
    ADCxConvertedData = LL_ADC_REG_ReadConversionData12(ADC1);
 
    hADCxConvertedData_Temperature_DegreeCelsius =(int16_t)(Temp_k * ADCxConvertedData - Temp_k * TScal1 + TStem1);
      
    printf("Temperature: %d\r\n",hADCxConvertedData_Temperature_DegreeCelsius);
    LL_mDelay(1000);
  }
}

/**
  * @brief  ADC Configuration Function.
  * @param  None
  * @retval None
  */
static void APP_AdcConfig()
{ 
  /* Enable ADC clock */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
  
  /* Set ADC to PCLK Quad */
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_PCLK2_DIV4);
  
  /* Set internal mode to Temperature */
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_TEMPSENSOR);
  
  wait_loop_index = ((LL_ADC_DELAY_TEMPSENSOR_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }

  /* Set the resolution to 12 bits */
  LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);
    
  /* Set data right alignment */
  LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

  /* Disable scanning mode */
  LL_ADC_SetSequencersScanMode(ADC1, LL_ADC_SEQ_SCAN_DISABLE);  
 
  /* Set General Group Trigger Software */
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
    
  /* Set regular group single conversion mode */
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
    
  /* Set regular group DMA mode None */
  LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);
    
  /* Set regular group sequence length 1 */
  LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
    
  /* Disable regular group discont  mode */
  LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

  /* Set regular group RANK1 channel Temperature */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_TEMPSENSOR);

  /* Set the sampling time to 239.5Cycles */
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_TEMPSENSOR, LL_ADC_SAMPLINGTIME_239CYCLES_5);   
}

/**
  * @brief  ADC calibration function.
  * @param  None
  * @retval None
  */
static void APP_AdcCalibrate()
{
  #if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0; /* Variable used for timeout management */
  #endif /* USE_TIMEOUT */
  
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {

    /* Enable ADC calibration */
    LL_ADC_StartCalibration(ADC1);
    
    /* Poll for ADC effectively calibrated */
    #if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
    #endif /* USE_TIMEOUT */
    
    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
    #if (USE_TIMEOUT == 1)
      /* Check Systick counter flag to decrement the time-out value */
      if (LL_SYSTICK_IsActiveCounterFlag())
      {
        if(Timeout-- == 0)
        {
          APP_ErrorHandler();
        }
      }
    #endif /* USE_TIMEOUT */
    }  

/*  if(LL_ADC_GetCalibrationOffsetStatus(ADC1)!=LL_ADC_CAL_OFFSET_STATUS_SUCCESS)  */
/*  {                                                                              */
/*    APP_ErrorHandler();                                                          */
/*  }                                                                              */
        
  }
}

/**
  * @brief  Configure system clock
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler: HCLK = SYSCLK */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Select HSI as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Set APB1 & APB2 prescaler: PCLK1 = HCLK, PCLK2 = HCLK/2 */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  
  /* Set systick to 1ms in using frequency set to 8MHz */
  LL_Init1msTick(8000000);

  /* Update the SystemCoreClock global variable(which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  Error handling function
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file：Pointer to the source file name
  * @param  line：assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add His own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
