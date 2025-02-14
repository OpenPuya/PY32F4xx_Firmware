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
/* Defines related to Clock configuration */
/* Uncomment to enable the adequate Clock Source */
#define RTC_CLOCK_SOURCE_LSI
/* #define RTC_CLOCK_SOURCE_LSE */

#ifdef RTC_CLOCK_SOURCE_LSI
/* ck_apre=LSIFreq/(ASYNC prediv + 1) with LSIFreq=40kHz RC */
#define RTC_ASYNCH_PREDIV          ((uint32_t)0x9C3F)
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
/* ck_apre=LSEFreq/(ASYNC prediv + 1) = 1Hz with LSEFreq=32768Hz */
#define RTC_ASYNCH_PREDIV          ((uint32_t)0x7FFF)
#endif

/* Private variables ---------------------------------------------------------*/
/* Time structure and its variables */
struct time_t
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
};
struct time_t RTC_TimeStruct;
struct time_t RTC_AlarmStruct;
/* Date structure and its variables */
struct date_t
{
  uint8_t month;
  uint8_t day;
  uint8_t year;
};
struct date_t RTC_DateStruct;
uint8_t EndOfMonth[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/* Buffer for displaying time and date */
uint32_t TimeCounter = 0;
uint32_t AlarmCounter = 0;
uint8_t aShowTime[50] = {0};
uint8_t aShowDate[50] = {0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigRtc(void);
static void APP_ConfigRtcAlarm(void);
static void APP_ConfigRtcDate(uint8_t ,uint8_t , uint8_t);
static void APP_UpadateRtcTimeStruct(void);
static void APP_UpadateRtcDateStruct(void);
static void APP_EnterStop(void);

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

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Configure RTC peripheral */
  APP_ConfigRtc();
  
  /* Turn on LED */
  BSP_LED_On(LED_GREEN);
  
  /*  Wait for the button to be pressed  */
  while(BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }
  
  /* Get the current time */
  AlarmCounter = LL_RTC_TIME_Get(RTC);
  
  /* Set alarm time */
  APP_ConfigRtcAlarm();
  
  /* Turn off LED */
  BSP_LED_Off(LED_GREEN);

  while (1)
  {
    /* Update time and date */
    APP_UpadateRtcTimeStruct();
    APP_UpadateRtcDateStruct();
    
    /* Enter STOP mode */
    APP_EnterStop();
    
    /* Wait for synchronization */
    LL_RTC_WaitForSynchro(RTC);
    
    /* Set alarm time */
    APP_ConfigRtcAlarm();
  }
}

/**
  * @brief  Configure RTC clock
  * @param  None
  * @retval None
  */
static void APP_ConfigRtc(void)
{
  LL_RTC_InitTypeDef rtc_initstruct = {0};
  
  /*##-1- Enable PWR clock and enable access to the backup domain #######*/
  /* To change the source clock of the RTC functionalities (LSE, LSI), you have to:
      - Enable the PWR clock
      - Enable write access to configure the RTC clock source (once after reset).
      - Reset the Backup domain
      - Configure the needed RTC clock source */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  LL_PWR_EnableBkUpAccess();

  /*##-2- Configure LSE/LSI as RTC clock source ###############################*/
#ifdef RTC_CLOCK_SOURCE_LSE
  /* Reset backup domain */
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
  /* Enable LSE */
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_HIGH);
  LL_RCC_LSE_Enable();
  while (LL_RCC_LSE_IsReady() != 1)
  {
  }
  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
#elif defined(RTC_CLOCK_SOURCE_LSI)
  /* Enable LSI */
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() != 1)
  {
  }
  /* Reset backup domain only if LSI is not yet selected as RTC clock source */
  if (LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSI)
  {
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
  }
#else
#error "configure clock for RTC"
#endif
  
  /* Enable RTC clock*/
  LL_RCC_EnableRTC();
  
  /*##-4 Configure RTC ######################################### ############*/
  /* Configure RTC prescaler and RTC data registers */
  if (LL_RTC_DeInit(RTC) != SUCCESS) 
  {
    /* Error prompt */
    
  }
  
  /* Configure prescaler and output source */
  rtc_initstruct.AsynchPrescaler = RTC_ASYNCH_PREDIV;
  rtc_initstruct.OutPutSource    = LL_RTC_CALIB_OUTPUT_NONE;
  if (LL_RTC_Init(RTC, &rtc_initstruct) != SUCCESS)
  {
    /* Error prompt */
    
  }
  
  LL_RTC_TimeTypeDef  rtc_time_initstruct = {0};
  /*## Configure Date ##################################################*/
  /* Set date: 2022.08.16 */
  APP_ConfigRtcDate(16, 8, 22);
  
  /*##Configure Time ################################################*/
  /* Set Time: 00:00:00 */
  rtc_time_initstruct.Hours      =0;
  rtc_time_initstruct.Minutes    =0 ;
  rtc_time_initstruct.Seconds    =0;
  /* Initialize RTC time according to the parameters defined in the initialization structure */  
  if (LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &rtc_time_initstruct) != SUCCESS)   
  {
    /* Error prompt */
  }
}

/**
  * @brief  Configure RTC alarm
  * @param  None
  * @retval None
  */
static void APP_ConfigRtcAlarm(void)
{
  /*##Configure Alarm #################################*/
  AlarmCounter += 1;
  if (LL_RTC_ALARM_SetCounter(RTC, AlarmCounter) != SUCCESS)
  {
    /* Error prompt */
  }
  
  /* Clear alarm interrupt flag */
  LL_RTC_ClearFlag_ALR(RTC);
  
  /* Enable alarm interrupt */
  LL_RTC_EnableIT_ALR(RTC);
  
  /*##- Configure RTC NVIC ###############################*/
  NVIC_SetPriority(RTC_IRQn, 0x00);
  NVIC_EnableIRQ(RTC_IRQn);
  
  /* RTC Alarm Interrupt Configuration: EXTI configuration */
  LL_EXTI_EnableIT(LL_EXTI_LINE_17);
  LL_EXTI_EnableRisingTrig(LL_EXTI_LINE_17);
}

/**
  * @brief  Configure Date
  * @param  fYear：year
  * @param  fMonth：month
  * @param  fDate：day
  * @retval None
  */
static void APP_ConfigRtcDate(uint8_t fDate , uint8_t fMonth , uint8_t fYear)
{
  RTC_DateStruct.day   = fDate;
  RTC_DateStruct.month = fMonth;
  RTC_DateStruct.year  = fYear;
}

/**
  * @brief  Update time
  * @param  None
  * @retval None
  */
static void APP_UpadateRtcTimeStruct(void)
{  
  TimeCounter = LL_RTC_TIME_Get(RTC);
  RTC_TimeStruct.hour = (TimeCounter/3600);
  RTC_TimeStruct.min  = (TimeCounter % 3600) / 60;
  RTC_TimeStruct.sec  = (TimeCounter % 3600) % 60; 
}

/**
  * @brief  Update date
  * @param  None
  * @retval None
  */
static void APP_UpadateRtcDateStruct(void)
{
  /* Update date when the time is 23:59:59 */
  if (TimeCounter == 0x0001517FU)
  {
    if(RTC_DateStruct.day == EndOfMonth[RTC_DateStruct.month -1])
    {
      RTC_DateStruct.day = 1U;
      RTC_DateStruct.month += 1U;
    }
    else
    {
      RTC_DateStruct.day = RTC_DateStruct.day + 0x1U;
    }
  }
}

/**
  * @brief  Enter Stop mode
  * @param  None
  * @retval None
  */
static void APP_EnterStop(void)
{
  /* Enable PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /* Set STOP_LPREGU mode when CPU enters deepsleep */
  LL_PWR_SetPowerMode(LL_PWR_MODE_STOP_LPREGU);

  /* Set VOS = 0.8V */
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_0P8V);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  LL_LPM_EnableDeepSleep(); 
  
  /* Wait for interrupt instruction */
  __WFI();

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  LL_LPM_EnableSleep(); 
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
