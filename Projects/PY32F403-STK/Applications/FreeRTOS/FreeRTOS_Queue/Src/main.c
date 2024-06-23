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

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Create KeyQueue and BigDataQueue */
QueueHandle_t KeyQueue;
QueueHandle_t BigDataQueue;
char BigBuff[100] = {"Puya semiconductor welcome to you!"};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define KEYMSG_Q_NUM    2
#define BIG_DATA_Q_NUM  1

/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void Task1(void *pvParamters);
static void Task2(void *pvParamters);
static void Task3(void *pvParamters);
static void QueueCreate(void);

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

  /* Create queue */
  QueueCreate();

  /* Create the tasks that are created using the original xTaskCreate() API function. */
  xTaskCreate( Task1, "Task1", 128, NULL, 1, NULL );
  xTaskCreate( Task2, "Task2", 128, NULL, 2, NULL );
  xTaskCreate( Task3, "Task3", 128, NULL, 3, NULL );

  /* Start the scheduler. */
  vTaskStartScheduler();
}


/**
  * @brief  Send a byte and set a buff to queue
  * @param  *pvParamters: The parameters passed to the task function when the task is created
  * @retval None
  */
static void Task1(void *pvParamters)
{
  uint8_t CountValue = 0;
  char * TempBuff = NULL;
  BaseType_t Err;
  TempBuff = BigBuff;
  while (1)
  {
    /* if CountValue count 10,prepare send count_value to Key_Queue */
    if(CountValue == 10)
    {
      /* Send CountValue to KeyQueue,return a value to Err */
      /* portMAX_DELAY: don't get the data you want, keep waiting, task enters the blocked state. */
      Err = xQueueSend(KeyQueue, &CountValue, portMAX_DELAY);
      printf("Task1: CountValue send success\r\n");
      /* Err = errQUEUE_FULL,send fail. */
      if(Err == errQUEUE_FULL)
      {
        printf("Task1: KeyQueue Full, data send fail!\r\n");
      }
    }
    /* if CountValue count 20,prepare send TempBuff to BigDataQueue */
    else if(CountValue == 20)
    {
      /* Send TempBuff to BigDataQueue,return a value to Err */
      /* portMAX_DELAY: don't get the data you want, keep waiting, task enters the blocked state. */
      Err = xQueueSend(BigDataQueue, &TempBuff, portMAX_DELAY);
      printf("Task1: CountValue send success\r\n");
      /* Err = errQUEUE_FULL,send fail. */
      if(Err == errQUEUE_FULL)
      {
        printf("Task1: BIGDATAQueue Full, data send fail!\r\n");
      }
    }
    CountValue++;
    /* if count_value count 21, set count_value = 0 */
    if(CountValue == 21)
    {
      CountValue = 0;
    }
    /* vTaskDelay(100): Blocking delay,Task1 goes into a blocked state after invocation */
    vTaskDelay(100);
  }
}

/**
  * @brief  Receive a byte from queue
  * @param  *pvParamters: The parameters passed to the task function when the task is created
  * @retval None
  */
static void Task2(void *pvParamters)
{
  uint8_t    KeyValue = 0;
  BaseType_t Err = 0;
  while(1)
  { 
    /* Receive a byte from Key_queue to key_value */
    /* portMAX_DELAY: don't get the data you want, keep waiting, task enters the blocked state. */
    Err = xQueueReceive(KeyQueue, &KeyValue, portMAX_DELAY);
    /* Err = pdTRUE,recreive success. */
    if(Err == pdTRUE)
    {
      printf("Task2: KeyValue = %d\r\n",KeyValue);
    }
  }
}

/**
  * @brief  Receive a buff from queue
  * @param  *pvParamters: The parameters passed to the task function when the task is created
  * @retval None
  */
static void Task3(void *pvParamters)
{
  char *     TempBuff = NULL;
  BaseType_t Err = 0;

  while(1)
  {
    /* Receive a buff from Key_queue to BIG_DATA_Queue */
    /* portMAX_DELAY: don't get the data you want, keep waiting, task enters the blocked state. */
    Err = xQueueReceive(BigDataQueue, &TempBuff, portMAX_DELAY);
    /* Err = pdTRUE,recreive success. */
    if(Err == pdTRUE)
    {
      printf("Task3: %s\r\n", TempBuff);
    }
  }
}

/**
  * @brief  Create KeyQueue and BigDataQueue
  * @param  None
  * @retval None
  */
static void QueueCreate()
{
  /* Create a KeyQueue. */
  KeyQueue = xQueueCreate(KEYMSG_Q_NUM,sizeof(uint8_t));
  /* Create a BigDataQueue. */
  BigDataQueue = xQueueCreate(BIG_DATA_Q_NUM,sizeof(char *));
  /* Err != pdFALSE,KeyQueue create success. */
  if(KeyQueue != pdFALSE)
  {
    printf("KeyQueue create success!\r\n");
  }
  /* Err == pdFALSE,KeyQueue create fail. */
  else
  {
    printf("KeyQueue create fail!\r\n");
  }
  /* Err != pdFALSE,BigDataQueue create success. */
  if(BigDataQueue != pdFALSE)
  {
    printf("BigDataQueue create success!\r\n");
  }
  /* Err == pdFALSE,BigDataQueue create fail. */
  else
  {
    printf("BigDataQueue create fail!\r\n");
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
