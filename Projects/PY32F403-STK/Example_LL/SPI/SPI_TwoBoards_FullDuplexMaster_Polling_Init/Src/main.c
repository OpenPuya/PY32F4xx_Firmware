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
/* Private variables ---------------------------------------------------------*/
/* Send buffer definition */
uint8_t aTxBuffer[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t ubNbDataToTransmit = sizeof(aTxBuffer);
__IO uint8_t ubTransmitIndex = 0;

/* Receive buffer definition */
uint8_t aRxBuffer[sizeof(aTxBuffer)] = {0};
uint8_t ubNbDataToReceive = sizeof(aTxBuffer);
__IO uint8_t ubReceiveIndex = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigSPI(void);
static void APP_SpiMasterTransmitReceive(void);
static void APP_WaitAndCheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
static void APP_LedBlinking(void);

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
  
  /* Configure Systemclock */
  APP_SystemClockConfig(); 

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

 /* Initialize SPI */
  APP_ConfigSPI();

  /* Wait for the button to be pressed*/
  while(BSP_PB_GetState(BUTTON_KEY) == 1);
  
  /* Enable SPI1 */
  LL_SPI_Enable(SPI1);
  
  /* Master sending and receiving data */
  APP_SpiMasterTransmitReceive();
  
  /* Wait transfer to be completed and check the received data */
  APP_WaitAndCheckEndOfTransfer();

  while (1)
  {
  }
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
  * @brief  SPI1 configuration function
  * @param  None
  * @retval None
  */
static void APP_ConfigSPI(void)
{
  LL_SPI_InitTypeDef SPI_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Enable clock */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /** SPI1 Pin config
  PB3   ------> SPI1_SCK
  PB4   ------> SPI1_MISO
  PB5   ------> SPI1_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_3;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_3;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_3;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* SPI1 parameter configuration*/
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV128;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 0x0U;
  LL_SPI_Init(SPI1, &SPI_InitStruct);
}

/**
  * @brief  Data transfer and receive function of the SPI1 peripheral
  * @param  None
  * @retval None
  */
static void APP_SpiMasterTransmitReceive(void)
{
  uint32_t             txallowed = 1U;
  
  /* Data is transmited and received in polling mode */
  while((ubReceiveIndex < ubNbDataToReceive) || (ubTransmitIndex < ubNbDataToTransmit))
  {
    /* Wait to send (send condition: send data register is empty, data is not sent, receive is completed) */
    if ((LL_SPI_IsActiveFlag_TXE(SPI1) == 1) && (ubTransmitIndex < ubNbDataToTransmit) && txallowed == 1U)
    {
      LL_SPI_TransmitData8(SPI1, aTxBuffer[ubTransmitIndex++]);
      txallowed = 0U;
    }
    
    /* Wait for receiving (receiving condition: the receiving data register is full, the data has not been received) */
    if((LL_SPI_IsActiveFlag_RXNE(SPI1) == 1) && (ubReceiveIndex < ubNbDataToReceive))
    {
      aRxBuffer[ubReceiveIndex++] = LL_SPI_ReceiveData8(SPI1);
      txallowed = 1U;
    }
  }
}

/**
  * @brief  SPI1Wait for transfer to complete，and check the received data
  * @param  None
  * @retval None
  */
static void APP_WaitAndCheckEndOfTransfer(void)
{
  /* 1 - Wait transfer to be completed  */
  while (ubTransmitIndex != ubNbDataToTransmit)
  {
  }

  /* 2 - Wait data to be received completely */
  while (ubNbDataToReceive > ubReceiveIndex)
  {
  }

  /* 3 - Compare sent and received data */
  if(APP_Buffercmp8((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, ubNbDataToTransmit))
  {
    /* error handling */
    APP_LedBlinking();
  }
  else
  {
    /* If the data is received correctly, the LED is turned on */
    BSP_LED_On(LED_GREEN);
  }
}

/**
  * @brief  Character comparison function
  * @param  pBuffer1：Pointer to buffer 1 that to be compared
  * @param  pBuffer2：Pointer to buffer 2 that to be compared
  * @param  BufferLength：The number of characters to be compared
  * @retval 0: The comparison value is the same; 1: The comparison value is different
  */
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

/**
  * @brief  LED blinking
  * @param  None
  * @retval None
  */
static void APP_LedBlinking(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN); 
    LL_mDelay(200);
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
