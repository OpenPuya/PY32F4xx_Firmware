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
static void APP_ExtiConfig(void);
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

  /* Initialize external interrupt */
  APP_ExtiConfig();
  
  /* Turn on LED */
  BSP_LED_On(LED_GREEN);

  /* Wait for button press */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* Turn off LED */
  BSP_LED_Off(LED_GREEN);

  /* Enter Stop mode */
  APP_EnterStop();
  
  while (1)
  {
    /* Toggle LED */
    BSP_LED_Toggle(LED_GREEN);
    
    /* Delay for 200ms */
    LL_mDelay(200);
  }
}

/**
  * @brief  Configure external interrupt
  * @param  None
  * @retval None
  */
static void APP_ExtiConfig(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
 
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};

  /* Enable GPIOA clock */
  LL_AHB2_GRP1_EnableClock (LL_AHB2_GRP1_PERIPH_GPIOA);
  
  /* Select PA06 pin */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  /* Select input mode */
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  /* Select pull-up */
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  /* Initialize GPIOA */
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Select EXTI6 as external interrupt input */
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA,LL_SYSCFG_EXTI_LINE6);

  /* Select EXTI6 */
  EXTI_InitStruct.Line = LL_EXTI_LINE_6;
  /* Enable */
  EXTI_InitStruct.LineCommand = ENABLE;
  /* Select interrupt mode */
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  /* Select falling edge trigger */
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
  /* Initialize external interrupt */
  LL_EXTI_Init(&EXTI_InitStruct);

  /* Set interrupt priority */
  NVIC_SetPriority(EXTI9_5_IRQn,1);
  /* Enable interrupt */
  NVIC_EnableIRQ(EXTI9_5_IRQn); 
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
