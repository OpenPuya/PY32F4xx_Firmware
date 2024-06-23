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
RTC_HandleTypeDef RtcHandle;
RTC_TimeTypeDef RTCtime;
RTC_AlarmTypeDef RTC_AlarmStruct;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_RtcInit(void);
static void APP_RtcSetAlarm_IT(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Enable LSI clock */
  APP_SystemClockConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialization button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Initialize debugging serial port (used by printf) */
  BSP_USART_Config();
  
  /* RTC initialization */
  APP_RtcInit();
  
  /* Turn on LED */
  BSP_LED_On(LED_GREEN);
  
  /* Wait for button press */
  while (BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }
  
  /* Get current RTC time in binary format */
  HAL_RTC_GetTime(&RtcHandle,&RTCtime,RTC_FORMAT_BIN);
  
  /* Configure the time of the first alarm in binary format */
  RTC_AlarmStruct.AlarmTime = RTCtime;
  RTC_AlarmStruct.AlarmTime.Seconds += 1;
  HAL_RTC_SetAlarm_IT(&RtcHandle, &RTC_AlarmStruct, RTC_FORMAT_BIN);

   /* Turn off LED */
  BSP_LED_Off(LED_GREEN);
  
  while (1)
  {  
    /* Suspend systick interrupt */
    HAL_SuspendTick();
    
    /* Enter STOP mode */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    
    /* Resume systick interrupt */
    HAL_ResumeTick();

    /* Wait for synchronization */
    HAL_RTC_WaitForSynchro(&RtcHandle);

    /* Set RTC alarm */
    APP_RtcSetAlarm_IT();
  }
}

/**
  * @brief  RTC initialization function, sets RTC to January 1, 2022, Saturday, 00:00:00
  * @param  None
  * @retval None
  */
static void APP_RtcInit(void)
{
  RTC_TimeTypeDef Timeinit = {0};
  RCC_PeriphCLKInitTypeDef RTCLCKconfig = {0};
  
  /* RCC peripheral clock initialization */
  RTCLCKconfig.PeriphClockSelection = RCC_PERIPHCLK_RTC;/* RCC peripheral clock selection as RTC */
  RTCLCKconfig.RtcClockSelection = RCC_RTCCLKSOURCE_LSI;/* RTC source selection as LSI */
  HAL_RCCEx_PeriphCLKConfig(&RTCLCKconfig);

  __HAL_RCC_RTC_ENABLE();                               /* Enable RTC clock */

  /* RTC initialization */
  RtcHandle.Instance = RTC;                               /* Select RTC */
  RtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND;        /* Automatic calculation of RTC's 1-second time base */
  RtcHandle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;          /* No output on the TAMPER pin */

  /*Set RTC current time：2022-1-1-00:00:00*/
  RtcHandle.DateToUpdate.Year = 22;                       /* Year 22 */
  RtcHandle.DateToUpdate.Month = RTC_MONTH_JANUARY;       /* January */
  RtcHandle.DateToUpdate.Date = 1;                        /* 1st day */
  RtcHandle.DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;  /* Saturday */
  Timeinit.Hours = 0x00;                                /* 0 hours */
  Timeinit.Minutes = 0x00;                              /* 0 minutes */
  Timeinit.Seconds = 0x00;                              /* 0 seconds */
  
  /* RTC deinitialization */
  HAL_RTC_DeInit(&RtcHandle);
  
  /* RTC initialization */
  HAL_RTC_Init(&RtcHandle);
  HAL_RTC_SetTime(&RtcHandle, &Timeinit, RTC_FORMAT_BIN);
}

/**
  * @brief  Set RTC alarm interrupt
  * @param  Sec：seconds；
  * @param  Min：minutes；
  * @param  Hour：hours；
  * @retval None
  */
static void APP_RtcSetAlarm_IT()
{
/* Get current alarm time in binary format */
  HAL_RTC_GetAlarm(&RtcHandle, &RTC_AlarmStruct, RTC_FORMAT_BIN);
  
  /* Update alarm time in binary format */
  RTC_AlarmStruct.AlarmTime.Seconds += 1;
  HAL_RTC_SetAlarm_IT(&RtcHandle, &RTC_AlarmStruct, RTC_FORMAT_BIN);
}

/**
  * @brief  RTC alarm event callback function, LED turns on when exiting low-power mode
  * @param  hrtc：RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  BSP_LED_Toggle(LED_GREEN);
  printf("%02u:%02u:%02u\r\n",  RTC_AlarmStruct.AlarmTime.Hours , RTC_AlarmStruct.AlarmTime.Minutes, RTC_AlarmStruct.AlarmTime.Seconds);
}

/**
  * @brief  System clock configuration function
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
/* OscInitstruct.HSEFreq         = RCC_HSE_16_32MHz; */                     /* HSE working frequency range: 16M~32M */
  OscInitstruct.HSI48MState     = RCC_HSI48M_OFF;                           /* Disable HSI48M */
  OscInitstruct.HSIState        = RCC_HSI_ON;                               /* Enable HSI */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                              /* Disable LSE */
/* OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH; */                    /* Drive capability level: High */
  OscInitstruct.LSIState        = RCC_LSI_ON;                               /* Enable LSI */
  OscInitstruct.PLL.PLLState    = RCC_PLL_OFF;                              /* Disable PLL */
/*  OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE; */                   /* PLL clock source: HSE */
/*  OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL6; */                        /* PLL multiplication factor: 6 */
  /* Configure Oscillators */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_HSI;                 /* System clock source: HSI */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock not divided */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock not divided */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* APB2 clock divided by 2 */
  /* Configure Clocks */
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
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
