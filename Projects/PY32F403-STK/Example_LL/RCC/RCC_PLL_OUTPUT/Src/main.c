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
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_GPIOConfig(void);

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

  /* Configure PA08 for MCO alternate function */
  APP_GPIOConfig();
  
  /* MCO output clock and division initialization */
  LL_RCC_ConfigMCO(LL_RCC_MCOSOURCE_SYSCLK,LL_RCC_MCO_DIV_1);

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
  
  /* Configure HSI as system clock */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Configure PLL */
  LL_RCC_PLL_Disable();
  while(LL_RCC_PLL_IsReady() != 0)
  {
  }
  LL_RCC_PLL_SetMainSource(LL_RCC_PLLSOURCE_HSI);
  LL_RCC_PLL_SetMulFactor(LL_RCC_PLLMUL_18);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }
  
  /* Set flash latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_6);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_6)
  {
  }

  /* Select PLL as system clock source, and if it goes over or under 80Mhz, 
  it is necessary to use HCLK prescaler 2 for intermediate steps */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set AHB prescaler: HCLK = SYSCLK */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  
  /* Set APB1 & APB2 prescaler: PCLK1 = HCLK, PCLK2 = HCLK/2 */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  
  /* Set systick to 1ms in using frequency set to 144MHz */
  LL_Init1msTick(144000000);

  /* Update the SystemCoreClock global variable(which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(144000000);
}

/**
  * @brief  Configure PA08 for MCO alternate function
  * @param  None
  * @retval None
  */
static void APP_GPIOConfig(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* Enable GPIOA clock */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  
  /* Configure PA08 for MCO alternate function */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;                  /* Select pin 8 */
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;        /* Configure as alternate function */
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH; /* Select output speed */
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL; /* Select output mode */
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;               /* No pull-up/down */
  GPIO_InitStruct.Alternate = LL_GPIO_AF0_MCO;          /* Select alternate function AF0 */
  LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
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
