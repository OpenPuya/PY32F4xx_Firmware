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
#include "list.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
List_t      TestList;     /* Define a List */
ListItem_t  ListItem1;    /* Define a ListItem */
ListItem_t  ListItem2;    /* Define a ListItem */
ListItem_t  ListItem3;    /* Define a ListItem */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_GpioConfig(void);
static void Task1(void *pvParamters);
static void Task2(void *pvParamters);

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

  /* GPIO configuration */
  APP_GpioConfig();

  /* Create the tasks that are created using the original xTaskCreate() API function. */
  xTaskCreate( Task1, "Task1", 128, NULL, 1, NULL );  
  xTaskCreate( Task2, "Task2", 128, NULL, 2, NULL );

  /* Start the scheduler. */
  vTaskStartScheduler();
}

/**
  * @brief  Toggle LED,express task1 is running.
  * @param  *pvParamters: The parameters passed to the task function when the task is created
  * @retval None
  */
static void Task1(void *pvParamters)
{
  while (1)
  {
    /* Toggle GPIO pin control LED On or Off. */
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
    /* vTaskDelay(500): Blocking delay,This Task1 goes into a blocked state after invocation */
    vTaskDelay(500);
    printf("Task1 is running\r\n");
  }
}

/**
  * @brief  Create list、listitem；insert、remove、insertend list items. output log once 1s
  * @param  *pvParamters: The parameters passed to the task function when the task is created
  * @retval None
  */
static void Task2(void *pvParamters)
{
  /* Initiatial List and LisIitem */
  vListInitialise(&TestList);
  vListInitialiseItem(&ListItem1);
  vListInitialiseItem(&ListItem2);
  vListInitialiseItem(&ListItem3);
  /* Initiatial LisIitemx.xItemValue */
  ListItem1.xItemValue = 10;
  ListItem2.xItemValue = 30;
  ListItem3.xItemValue = 20;

  /* Print List and LisIitem primary address */	
  printf("/*print List and ListItem address*/\r\n");
  printf("Item\t\t\t\t\tAddress\r\n");
  printf("TestList->pxIndex\t\t\t0x%p\t\r\n",&TestList.pxIndex);
  printf("TestList->xListEnd\t\t\t0x%p\t\r\n",&TestList.xListEnd);
  printf("ListItem1\t\t\t\t0x%p\t\r\n",&ListItem1);
  printf("ListItem2\t\t\t\t0x%p\t\r\n",&ListItem2);
  printf("ListItem3\t\t\t\t0x%p\t\r\n",&ListItem3);
  printf("\r\n");

  /* Insert ListItem1,Insert in order of xItemValue value size */
  vListInsert((List_t *)&TestList, (ListItem_t *)&ListItem1);
  printf("Item\t\t\t\t\tAddress\r\n");
  printf("TestList->xListEnd->pxNext\t\t0x%p\t\r\n",TestList.xListEnd.pxNext);
  printf("ListItem1\t\t\t\t0x%p\t\r\n",&ListItem1.pxNext);
  printf("TestList->xListEnd->pxPrevious\t\t0x%p\t\r\n", TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious\t\t\t0x%p\t\r\n",&ListItem1.pxPrevious);
  printf("\r\n");

  /* Insert ListItem2,Insert in order of xItemValue value size */
  vListInsert((List_t *)&TestList, (ListItem_t *)&ListItem2);
  printf("Item\t\t\t\t\tAddress\r\n");
  printf("TestList->xListEnd->pxNext\t\t0x%p\t\r\n",TestList.xListEnd.pxNext);
  printf("ListItem1\t\t\t\t0x%p\t\r\n",&ListItem1.pxNext);
  printf("ListItem2\t\t\t\t0x%p\t\r\n",&ListItem2.pxNext);
  printf("TestList->xListEnd->pxPrevious\t\t0x%p\t\r\n", TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious\t\t\t0x%p\t\r\n",&ListItem1.pxPrevious);
  printf("ListItem2->pxPrevious\t\t\t0x%p\t\r\n",&ListItem2.pxPrevious);
  printf("\r\n");

  /* Insert ListItem3,Insert in order of xItemValue value size */
  vListInsert((List_t *)&TestList, (ListItem_t *)&ListItem3);
  printf("Item\t\t\t\t\tAddress\r\n");
  printf("TestList->xListEnd->pxNext\t\t0x%p\t\r\n",TestList.xListEnd.pxNext);
  printf("ListItem1\t\t\t\t0x%p\t\r\n",&ListItem1.pxNext);
  printf("ListItem2\t\t\t\t0x%p\t\r\n",&ListItem2.pxNext);
  printf("ListItem3\t\t\t\t0x%p\t\r\n",&ListItem3.pxNext);
  printf("TestList->xListEnd->pxPrevious\t\t0x%p\t\r\n", TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious\t\t\t0x%p\t\r\n",&ListItem1.pxPrevious);
  printf("ListItem2->pxPrevious\t\t\t0x%p\t\r\n",&ListItem2.pxPrevious);
  printf("ListItem3->pxPrevious\t\t\t0x%p\t\r\n",&ListItem3.pxPrevious);
  printf("\r\n");

  /* Remove ListItem2 */
  uxListRemove((ListItem_t *)&ListItem2);
  printf("Item\t\t\t\t\tAddress\r\n");
  printf("TestList->xListEnd->pxNext\t\t0x%p\t\r\n",TestList.xListEnd.pxNext);
  printf("ListItem1\t\t\t\t0x%p\t\r\n",&ListItem1.pxNext);
  printf("ListItem3\t\t\t\t0x%p\t\r\n",&ListItem3.pxNext);
  printf("TestList->xListEnd->pxPrevious\t\t0x%p\t\r\n", TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious\t\t\t0x%p\t\r\n",&ListItem1.pxPrevious);
  printf("ListItem3->pxPrevious\t\t\t0x%p\t\r\n",&ListItem3.pxPrevious);
  printf("\r\n");

  /* Insert ListItem2,insert list end */
  vListInsertEnd((List_t *)&TestList, (ListItem_t *)&ListItem2);
  printf("Item\t\t\t\t\tAddress\r\n");
  printf("TestList->xListEnd->pxNext\t\t0x%p\t\r\n",TestList.xListEnd.pxNext);
  printf("ListItem1\t\t\t\t0x%p\t\r\n",&ListItem1.pxNext);
  printf("ListItem2\t\t\t\t0x%p\t\r\n",&ListItem2.pxNext);
  printf("ListItem3\t\t\t\t0x%p\t\r\n",&ListItem3.pxNext);
  printf("TestList->xListEnd->pxPrevious\t\t0x%p\t\r\n", TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious\t\t\t0x%p\t\r\n",&ListItem1.pxPrevious);
  printf("ListItem2->pxPrevious\t\t\t0x%p\t\r\n",&ListItem2.pxPrevious);
  printf("ListItem3->pxPrevious\t\t\t0x%p\t\r\n",&ListItem3.pxPrevious);
  printf("\r\n");

  while(1)
  {
    /* vTaskDelay(1000): Blocking delay,This Task2 goes into a blocked state after invocation */
    vTaskDelay(1000);
  }
}

/**
  * @brief  GPIO configuration
  * @param  None
  * @retval None
  */
static void APP_GpioConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();                          /* Enable GPIOA clock */

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */  
  /* GPIO Initialization */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);    
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
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock not divided */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock not divided */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* APB1 clock divided by 2 */
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
