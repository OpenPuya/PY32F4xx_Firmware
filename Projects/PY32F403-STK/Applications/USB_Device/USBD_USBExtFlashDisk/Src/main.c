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
#include "usb_config.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hSPI2;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_USBInit(void);
static void APP_SPIInit(void);

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
  
  /* Initialize SPI peripheral */
  APP_SPIInit();

  /* Initialize USB peripheral */
  APP_USBInit();

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  USB peripheral initialization function
  * @param  None
  * @retval None
  */
static void APP_USBInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  SET_BIT(RCC->CFGR1,RCC_CFGR1_USBSELHSI48_Msk);
  __HAL_RCC_USB_CLK_ENABLE();

  msc_ram_init();

  /* Enable USB interrupt */
  NVIC_EnableIRQ(USBD_IRQn);
}

/**
  * @brief  SPI peripheral initialization function
  * @param  None
  * @retval None
  */
static void APP_SPIInit(void)
{
  /*Deinitialize SPI configuration*/
  hSPI2.Instance               = SPI2;                       /* SPI2 */
  hSPI2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;   /* Prescaler: 16 */
  hSPI2.Init.Direction         = SPI_DIRECTION_2LINES;       /* Full-duplex */
  hSPI2.Init.CLKPolarity       = SPI_POLARITY_LOW;           /* Clock polarity: Low */
  hSPI2.Init.CLKPhase          = SPI_PHASE_1EDGE ;           /* Data sampling on the first clock edge */
  hSPI2.Init.DataSize          = SPI_DATASIZE_8BIT;          /* SPI data size: 8-bit */
  hSPI2.Init.FirstBit          = SPI_FIRSTBIT_MSB;           /* MSB transmitted first */
  hSPI2.Init.NSS               = SPI_NSS_SOFT;               /* NSS software mode */
  hSPI2.Init.Mode = SPI_MODE_MASTER;                         /* Configured as master */
  if (HAL_SPI_DeInit(&hSPI2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* SPI initialization */
  if (HAL_SPI_Init(&hSPI2) != HAL_OK)
  {
    APP_ErrorHandler();
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
  OscInitstruct.HSEState        = RCC_HSE_ON;                              /* Enable HSE */
  OscInitstruct.HSEFreq         = RCC_HSE_16_32MHz;                        /* HSE working frequency range: 16M~32M */
  OscInitstruct.HSI48MState     = RCC_HSI48M_ON;                           /* Enable HSI48M */
  OscInitstruct.HSIState        = RCC_HSI_ON;                              /* Enable HSI */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                             /* Disable LSE */
  OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH;                       /* Drive capability level: High */
  OscInitstruct.LSIState        = RCC_LSI_OFF;                             /* Disable LSI */
  OscInitstruct.PLL.PLLState    = RCC_PLL_ON;                              /* Enable PLL */
  OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;                       /* PLL clock source: HSE */
  OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL5;                            /* PLL multiplication factor is 5 */
  /* Configure Oscillators */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;              /* SYSCLK source select as PLL */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock not divided */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock not divided */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV1;                        /* APB2 clock not divided */
  /* Configure Clocks */
  if(HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_4) != HAL_OK)
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
