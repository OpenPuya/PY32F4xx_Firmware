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

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_RtcAlarmConfig(void);
static void APP_RtcTimeShow(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();
  
  /* Configure system clock */
  APP_SystemClockConfig(); 
  
  /* Initialize debug USART (used for printf) */
  DEBUG_USART_Config();
  
  /* RTC initialization */
  RtcHandle.Instance = RTC;                       /* Select RTC */
  RtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND; /* RTC one second time base automatic calculation */
  RtcHandle.Init.OutPut = RTC_OUTPUTSOURCE_NONE;   /* No output on the TAMPER pin */
  if (HAL_RTC_Init(&RtcHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* RTC clock configuration */
  APP_RtcAlarmConfig();
  
  while (1)
  {
  }
}

/**
  * @brief  RTC event execution function, allowing for the current time through serial port
  * @param  hrtc：RTC handle
  * @retval None
  */
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
  printf("RTC_IT_SEC\r\n");
  APP_RtcTimeShow();
}

/**
  * @brief  Alarm interrupt callback function
  * @param  hrtc：RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  printf("RTC_IT_ALARM\r\n");
}

/**
  * @brief  RTC alarm clock configuration
  * @param  None
  * @retval None
  */
static void APP_RtcAlarmConfig(void)
{
  RTC_DateTypeDef  sdatestructure = {0};
  RTC_TimeTypeDef  stimestructure = {0};
  RTC_AlarmTypeDef salarmstructure = {0};

  /* Set date: Tuesday, May 21, 2021 */
  sdatestructure.Year = 0x21;
  sdatestructure.Month = 0x05;
  sdatestructure.Date = 0x21;
  sdatestructure.WeekDay = RTC_WEEKDAY_TUESDAY;
  if (HAL_RTC_SetDate(&RtcHandle, &sdatestructure, RTC_FORMAT_BCD) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Set time: 12:13:00 */
  stimestructure.Hours = 0x12;
  stimestructure.Minutes = 0x13;
  stimestructure.Seconds = 0x00;
  if (HAL_RTC_SetTime(&RtcHandle, &stimestructure, RTC_FORMAT_BCD) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /*Set the RTC alarm clock to generate an interrupt at 12:13:35*/
  salarmstructure.AlarmTime.Hours = 0x12;
  salarmstructure.AlarmTime.Minutes = 0x13;
  salarmstructure.AlarmTime.Seconds = 0x35;
  if (HAL_RTC_SetAlarm_IT(&RtcHandle, &salarmstructure, RTC_FORMAT_BCD) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Display RTC current time
  * @param  None
  * @retval None
  */
static void APP_RtcTimeShow(void)
{
  RTC_DateTypeDef sdatestructureget = {0};
  RTC_TimeTypeDef stimestructureget = {0};
  
  /*Display RTC current time*/
  HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);

  /* Set RTC current date */
  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);

  /* The display time format is: hh: mm: ss */
  printf("%02d:%02d:%02d\r\n", stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
}

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef  OscInitstruct = {0};
  RCC_ClkInitTypeDef  ClkInitstruct = {0};
  
  OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | 
                                  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
  OscInitstruct.HSEState        = RCC_HSE_OFF;                              /* Close HSE */
/* OscInitstruct.HSEFreq         = RCC_HSE_16_32MHz; */                     /* Choose HSE frequency of 16-32MHz */
  OscInitstruct.HSI48MState     = RCC_HSI48M_OFF;                           /* Close HSI48M */
  OscInitstruct.HSIState        = RCC_HSI_ON;                               /* Enable HSI */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                              /* Close LSE */
/* OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH; */                    /* Drive capability level: high */
  OscInitstruct.LSIState        = RCC_LSI_OFF;                              /* Close LSI */
  OscInitstruct.PLL.PLLState    = RCC_PLL_OFF;                              /* Close PLL */
/* OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE; */                    /* PLL clock source selection HSE */
/* OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL6; */                         /* PLL clock source 6-fold frequency */
  /* Configure oscillator */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_HSI;                 /* System clock selection HSI */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock 1 division */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock 1 division */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* APB2 clock 2 division */
  /* Configure Clock */
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
  /* Infinite loop */
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
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)  */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
