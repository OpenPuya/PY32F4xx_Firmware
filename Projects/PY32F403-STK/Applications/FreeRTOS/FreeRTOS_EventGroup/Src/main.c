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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EventGroupHandle_t EventGroupHandle;  /* Define a EventGroupHandle */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define EVENTBIT_0  (1<<0)
#define EVENTBIT_1  (1<<1)

/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void Task1(void *pvParamters);
static void Task2(void *pvParamters);
static void EventGroupCreate(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();

  /* System clock configuration */
  APP_SystemClockConfig();

  /* Initialize UART */
  BSP_USART_Config();

  /* Create event group */
  EventGroupCreate();

  /* Create the tasks that are created using the original xTaskCreate() API function. */
  xTaskCreate( Task1, "Task1", 128, NULL, 1, NULL );  
  xTaskCreate( Task2, "Task2", 128, NULL, 2, NULL );

  /* Start the scheduler. */
  vTaskStartScheduler();
}

/**
  * @brief  Set assign bit to event group, assign bit is stored in "pxEventBits->uxEventBits"
  * @param  *pvParamters: The parameters passed to the task function when the task is created
  * @retval None
  */
static void Task1(void *pvParamters)
{
  uint8_t CountValue = 0;
  while (1)
  {
    /* If CountValue = 10,prepare write EVENTBIT_0 to EventGroupHandle */
    if(CountValue == 10)
    {
      xEventGroupSetBits(EventGroupHandle, EVENTBIT_0);
      printf("Task1: Set bit0\r\n");
    }
    /* If CountValue = 20,prepare write EVENTBIT_1 to EventGroupHandle */
    else if(CountValue == 20)
    {
      xEventGroupSetBits(EventGroupHandle, EVENTBIT_1);
      printf("Task1: Set bit1\r\n");
    }
    CountValue++;
    /* If CountValue count 20,set CountValue = 0 */
    if(CountValue == 21)
    {
      CountValue = 0;
    }
    /* vTaskDelay(100): Blocking delay,Task1 goes into a blocked state after invocation */
    vTaskDelay(100);
  }
}

/**
  * @brief  Set assign bit to event group, assign bit is stored in "pxEventBits->uxEventBits"
  * @param  *pvParamters: The parameters passed to the task function when the task is created
  * @retval None
  */
static void Task2(void *pvParamters)
{
  EventBits_t EventBit = 0;
  while(1)
  { 
    /* Gets the event bit waiting to be specified from event group */
    EventBit = xEventGroupWaitBits( EventGroupHandle,         /* Specifies the event flag group to wait for */
                                    EVENTBIT_0 | EVENTBIT_1,  /* Specifies the event bits to wait for */
                                    pdTRUE,                   /* Before exiting this function.
                                                                 pdTRUE: Clear EVENTBIT_0 | EVENTBIT_1;
                                                                 pdFALSE: Keep EVENTBIT_0 | EVENTBIT_1 */
                                    pdTRUE,                   /* This function exits the blocking state condition
                                                                 pdTRUE:  All waiting event bits are set to one; 
                                                                 pdFALSE: Set any one of the waiting event bits to one */
                                    portMAX_DELAY);           /* Don't get the data you want, keep waiting, task enters the blocked state. */
    printf("Task2: EventBit:0x%x\r\n",(unsigned int)EventBit);
  }
}

/**
  * @brief  Create event group.
  * @param  None
  * @retval None
  */
static void EventGroupCreate()
{
  /* Create event group,return value to BinarySemphoreHandle */
  EventGroupHandle = xEventGroupCreate();
  /* If EventGroupHandle != NULL,event group create success. */
  if(EventGroupHandle != NULL)
  {
    printf("Event group create success!\r\n");
  }
  /* If EventGroupHandle == NULL,event group create fail */
  else
  {
    printf("Event group create fail!\r\n");
  }
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
  OscInitstruct.LSIState        = RCC_LSI_OFF;                              /* Disable LSI */
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
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock 1 division */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock 1 division */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* APB2 clock 2 division */
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
  /* Infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file：pointer to the source file name
  * @param  line：assert_param error line source number
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
