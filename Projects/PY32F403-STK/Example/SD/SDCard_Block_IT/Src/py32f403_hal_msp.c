/**
  ******************************************************************************
  * @file    py32f403_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief Initialize global MSP
  */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
  GPIO_InitTypeDef SDIOInit = {0};
  
  /* enable clock */
  __HAL_RCC_SDIO_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  
  /* configuration pins
  PD2:  CMD
  PC8:  D0
  PC9:  D1
  PC10: D2
  PC11: D3
  PC12: SCK
  */

  SDIOInit.Mode       = GPIO_MODE_AF_PP;
  SDIOInit.Pull       = GPIO_PULLUP;
  SDIOInit.Speed      = GPIO_SPEED_FREQ_VERY_HIGH;
  SDIOInit.Alternate  = GPIO_AF11_SDIO;
  
  SDIOInit.Pin    = GPIO_PIN_2;
  HAL_GPIO_Init(GPIOD,&SDIOInit);
  
  SDIOInit.Pin    = GPIO_PIN_8;
  HAL_GPIO_Init(GPIOC,&SDIOInit);
  
  SDIOInit.Pin    = GPIO_PIN_9;
  HAL_GPIO_Init(GPIOC,&SDIOInit);
  
  SDIOInit.Pin    = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOC,&SDIOInit);
  
  SDIOInit.Pin    = GPIO_PIN_11;
  HAL_GPIO_Init(GPIOC,&SDIOInit);
  
  SDIOInit.Pin    = GPIO_PIN_12;
  HAL_GPIO_Init(GPIOC,&SDIOInit);
  
  /*  Enable SDIO Global IT  */
  __HAL_SD_ENABLE_GLOBAL_IT(&SDHandle);
  
  /* Enable NVIC */
  HAL_NVIC_SetPriority(SDIO_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(SDIO_IRQn);
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
