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

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle, htim3;
TIM_SlaveConfigTypeDef   sSlaveConfig;
TIM_MasterConfigTypeDef sMasterConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);

/**
  * @brief  Main program
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Configure Systemclock */
  APP_SystemClockConfig(); 

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  TimHandle.Instance = TIM1;                                           /* Select TIM1 */
  TimHandle.Init.Period            = 800 - 1;                          /* Auto reload value */
  TimHandle.Init.Prescaler         = 100 - 1;                          /* Prescaler：100-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* Clock division: tDTS=tCK_INT */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* CounterMode:Up */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* repetition counter value:1-1 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   /* TIM1_ARR register is not buffered */
  /* Initialize TIM1 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  htim3.Instance = TIM3;                                               /* Select TIM3 */
  htim3.Init.Prescaler = 100 - 1;                                      /* Prescaler：100-1 */
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;                         /* CounterMode:Up */
  htim3.Init.Period = 1 - 1;                                           /* Auto reload value */
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                   /* Clock division: tDTS=tCK_INT */
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;       /* TIM1_ARR register is not buffered */
  /* Initializes the TIM3 Time base Unit */
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                 /* Update event is used as trigger output (TRGO) */
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;         /* The master/slave mode is disabled */
  /* Configures the TIM3 in master mode */
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

  sSlaveConfig.SlaveMode        = TIM_SLAVEMODE_EXTERNAL1;             /* Slave mode is External Clock Mode 1 */
  sSlaveConfig.InputTrigger     = TIM_TS_ITR2;                         /* The trigger selection for TIM1 is TIM3 */
  sSlaveConfig.TriggerPolarity  = TIM_TRIGGERPOLARITY_NONINVERTED;     /* ETR is non-inverted, active at high level or rising edge */
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;           /* Prescaler OFF */
  sSlaveConfig.TriggerFilter    = 0;                                   /* No filter */
  /* Configures the TIM1 in Slave mode */
  if (HAL_TIM_SlaveConfigSynchro(&TimHandle, &sSlaveConfig) != HAL_OK) 
  {
    APP_ErrorHandler();
  }
  
  /* Starts the TIM1 Base generation in interrupt mode */
  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Starts the TIM3 Base generation. */
  if (HAL_TIM_Base_Start(&htim3) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Infinite loop */
  while (1)
  {}
}

/**
  * @brief  TIM1Update interrupt callback
  * @param  htim：TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Toggle LED */
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief   Configure systemclock
  * @param   None
  * @retval  None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef  OscInitstruct = {0};
  RCC_ClkInitTypeDef  ClkInitstruct = {0};
  
  OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | 
                                  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
  OscInitstruct.HSEState        = RCC_HSE_OFF;                              /* HSE OFF */
/* OscInitstruct.HSEFreq         = RCC_HSE_16_32MHz; */                     /* HSE clock range 16~32MHz */
  OscInitstruct.HSI48MState     = RCC_HSI48M_OFF;                           /* Disable HSI48M clock */
  OscInitstruct.HSIState        = RCC_HSI_ON;                               /* HSI ON */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                              /* LSE OFF */
/* OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH; */                    /* LSE high drive capability */
  OscInitstruct.LSIState        = RCC_LSI_OFF;                              /* LSI OFF */
  OscInitstruct.PLL.PLLState    = RCC_PLL_OFF;                              /* PLL OFF */
/* OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE; */                    /* HSE oscillator clock selected as PLL clock entry */
/* OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL6; */                         /* PLLVCO = PLL clock entry x 6 */
  /* Initialize the RCC Oscillators */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_HSI;                 /* Select HSI as system clock */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* SYSCLK not divided: HCLK=SYSCLK */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* HCLK not divided: PCLK1=HCLK */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* HCLK divided by 2: PCLK2=HCLK/2 */
  /* Set clock source */
  if(HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
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
