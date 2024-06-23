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
#define BLOCK_SIZE  (0x200)
#define BLOCK_NUM   (0x02)
#define STARTADDR   (0x00) /* Start address in blocks */

/* Private variables ---------------------------------------------------------*/
uint8_t Txbuff[BLOCK_SIZE*BLOCK_NUM]={0};
uint8_t Rxbuff[BLOCK_SIZE*BLOCK_NUM]={0};

SD_HandleTypeDef SDHandle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static uint32_t APP_BuffCmp(uint8_t *buff1, uint8_t* buff2, uint32_t size);
static uint32_t APP_BuffElementCheck(uint8_t *buff1, uint32_t size, uint8_t value);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  uint32_t i = 0;
  
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();
  
  /* Configure system clock */
  APP_SystemClockConfig(); 

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /*  initialize an array  */
  for(i=0;i < BLOCK_SIZE*BLOCK_NUM;i++)
  {
    Txbuff[i] = i;
  }
  
  /* Initialize SD card */
  SDHandle.Instance = SDIO;
  SDHandle.Init.ClockSel            = SDIO_CLOCK_OFFSET_180C;
  SDHandle.Init.ClockDiv            = 0x01;
  SDHandle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
  SDHandle.Init.BusWide             = SDIO_BUS_WIDE_1B;
  SDHandle.Init.PreSampling         = SDIO_PRE_SAMPLING_ENABLE;
  SDHandle.Init.PreSamplingClockSel = SDIO_PRE_SAMPLING_CLOCK_OFFSET_270C;
  if(HAL_SD_Init(&SDHandle) != HAL_SD_ERROR_NONE)
  {
    APP_ErrorHandler();
  }
  
  /* Enable 4-wire data transmission */
  if(HAL_SD_ConfigWideBusOperation(&SDHandle, SDIO_BUS_WIDE_4B) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* block erase */
  if(HAL_SD_Erase(&SDHandle,STARTADDR,(STARTADDR + BLOCK_NUM - 1)) != HAL_SD_ERROR_NONE)
  {
    APP_ErrorHandler();
  }
  /* Wait for SD card to complete current operation */
  while((HAL_SD_GetState(&SDHandle) != HAL_SD_STATE_READY) || (HAL_SD_GetCardState(&SDHandle) != HAL_SD_CARD_TRANSFER))
  {
  }
  
  /* block read */
  if(HAL_SD_ReadBlocks_IT(&SDHandle,Rxbuff,STARTADDR,BLOCK_NUM) != HAL_SD_ERROR_NONE)
  {
    APP_ErrorHandler();
  }    
  /* Wait for SD card to complete current operation */
  while((HAL_SD_GetState(&SDHandle) != HAL_SD_STATE_READY) || (HAL_SD_GetCardState(&SDHandle) != HAL_SD_CARD_TRANSFER))
  {
  }
  
  /*  Check if erasure succeeded  */
  if (APP_BuffElementCheck(Rxbuff, BLOCK_SIZE*BLOCK_NUM, 0x0))
  {
    APP_ErrorHandler();
  }
  
  /* block write */
  if(HAL_SD_WriteBlocks_IT(&SDHandle,Txbuff,STARTADDR,BLOCK_NUM) != HAL_SD_ERROR_NONE)
  {
    APP_ErrorHandler();
  }
  /* Wait for SD card to complete current operation */
  while((HAL_SD_GetState(&SDHandle) != HAL_SD_STATE_READY) || (HAL_SD_GetCardState(&SDHandle) != HAL_SD_CARD_TRANSFER))
  {
  }
  
  /* block read */
  if(HAL_SD_ReadBlocks_IT(&SDHandle,Rxbuff,STARTADDR,BLOCK_NUM) != HAL_SD_ERROR_NONE)
  {
    APP_ErrorHandler();
  }    
  /* Wait for SD card to complete current operation */
  while((HAL_SD_GetState(&SDHandle) != HAL_SD_STATE_READY) || (HAL_SD_GetCardState(&SDHandle) != HAL_SD_CARD_TRANSFER))
  {
  }

  /* compare array */
  if(APP_BuffCmp(Txbuff, Rxbuff, BLOCK_SIZE*BLOCK_NUM))
  {
    APP_ErrorHandler();
  }
  
  /* Turn on LED */
  BSP_LED_On(LED_GREEN);
  
  /* Infinite loop */
  while (1)
  {
  }
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
  * @brief  array comparison function
  * @param  buff1： array 1
  * @param  buff2： array 2
  * @param  size： array size
  * @retval 0：Same array
  *         1：Different arrays
  */
static uint32_t APP_BuffCmp(uint8_t *buff1, uint8_t *buff2, uint32_t size)
{
  while (size--)
  {
    if ((*buff1) != (*buff2))
    {
      return 1;
    }
    buff1++;
    buff2++;
  }
  return 0;
}

/**
  * @brief  A function that compares an array element to an expected value.
  * @param  buff： array to be compared
  * @param  size： array size
  * @param  value：expected value
  * @retval 0: Array elements are the same as expected values
  *         1:  Array elements differ from expected values
  */
static uint32_t APP_BuffElementCheck(uint8_t *buff1, uint32_t size, uint8_t value)
{
  while (size--)
  {
    if ((*buff1) != value)
    {
      return 1;
    }
    buff1++;
  }
  return 0;
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
