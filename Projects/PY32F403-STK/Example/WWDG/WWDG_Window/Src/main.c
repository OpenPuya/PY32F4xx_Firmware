/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
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
#define WINDOW_IN                                    /* Refresh WWDG Within the window time*/
/* #define WINDOW_UPPER */                           /* Refresh WWDG outside the window time upper limit */
/* #define WINDOW_LOWER */                           /* Refresh WWDG outside the window time lower limit */

/* Private variables ---------------------------------------------------------*/
WWDG_HandleTypeDef   WwdgHandle;
uint32_t delay;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static uint32_t APP_TimeoutCalculation(uint32_t timevalue);

/**
  * @brief  Main program
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Configure Systemclock */
  APP_SystemClockConfig(); 
  
 /* Initialize button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN); 

  if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
  {
    /* LED ON */
    BSP_LED_On(LED_GREEN);

    /* Delay 4s */
    HAL_Delay(4000);
    
    /* LED off */
    BSP_LED_Off(LED_GREEN);

    /* Delay 500ms */
    HAL_Delay(500);

    /* Set RMVF bit to clear the reset flags */
    __HAL_RCC_CLEAR_RESET_FLAGS();
  }
  else
  {
    /* LED off */
    BSP_LED_Off(LED_GREEN);
  }

  /* Initialize WWDG */
  WwdgHandle.Instance = WWDG;                                                             /* Select WWDG */
  WwdgHandle.Init.Prescaler = WWDG_PRESCALER_8;                                           /* WWDG counter clock = (PCLK1/4096)/8 */
  WwdgHandle.Init.Window    = 0x50;                                                       /* WWDG window value */
  WwdgHandle.Init.Counter   = 0x7F;                                                       /* WWDG free-running downcounter value(7 bit) */
  WwdgHandle.Init.EWIMode   = WWDG_EWI_DISABLE;                                           /* EWI disable */
  /* Initialize WWDG */
  if (HAL_WWDG_Init(&WwdgHandle) != HAL_OK)                                               
  {
    APP_ErrorHandler();
  }

#if defined(WINDOW_IN)
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - WwdgHandle.Init.Window) + 1) + 1;   /* Within the window */
#elif defined(WINDOW_UPPER)
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - WwdgHandle.Init.Window)-5 ) + 1;    /* Outside the window time upper limit */
#else 
  delay = APP_TimeoutCalculation((WwdgHandle.Init.Counter - 0x3f) +5) + 1;                      /* outside the window time lower limit */
#endif

  /* Infinite loop */
  while (1)
  {
    /* Toggle LED */
    BSP_LED_Toggle(LED_GREEN);

    /* Insert the calculated delay above */
    HAL_Delay(delay);

    /* Refresh WWDG */
    if (HAL_WWDG_Refresh(&WwdgHandle) != HAL_OK)
    {
      APP_ErrorHandler();
    }
  }
}

/**
  * @brief  Timeout Calculation.
  * @param  timevalue：time
  * @retval int
  */
static uint32_t APP_TimeoutCalculation(uint32_t timevalue)
{
  uint32_t timeoutvalue = 0;
  uint32_t pclk1 = 0;
  uint32_t wdgtb = 0;
  /* Get PCLK value */
  pclk1 = HAL_RCC_GetPCLK1Freq();
  /* Get prescaler */
  wdgtb = (1 << ((WwdgHandle.Init.Prescaler) >> 7)); /* 2^WDGTB[1:0] */
  /* Calculating timeout value */
  timeoutvalue = ((4096 * wdgtb * timevalue) / (pclk1 / 1000));
  return timeoutvalue;
}

/**
  * @brief   Configure systemclock
  * @param   None
  * @retval  None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef  OscInitstruct = {0};
  RCC_ClkInitTypeDef  ClkInitstruct = {0};
  
  OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | 
                                  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
  OscInitstruct.HSEState        = RCC_HSE_OFF;                              /* HSE OFF */
/* OscInitstruct.HSEFreq         = RCC_HSE_16_32MHz; */                     /* HSE clock range 16~32MHz */
  OscInitstruct.HSI48MState     = RCC_HSI48M_OFF;                           /* Disable HSI48M clock */
  OscInitstruct.HSIState        = RCC_HSI_ON;                               /* HSI ON */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                              /* LSE OFF */
/* OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH; */                    /* LSE high drive capability */
  OscInitstruct.LSIState        = RCC_LSI_OFF;                              /* LSI OFF */
  OscInitstruct.PLL.PLLState    = RCC_PLL_OFF;                              /* PLL OFF */
/*  OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE; */                   /* HSE oscillator clock selected as PLL clock entry */
/*  OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL6; */                        /* PLLVCO = PLL clock entry x 6 */
  /* Initialize the RCC Oscillators */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_HSI;                 /* Select HSI as system clock */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* SYSCLK not divided: HCLK=SYSCLK */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* HCLK not divided: PCLK1=HCLK */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* HCLK divided by 2: PCLK2=HCLK/2 */
  /* Set clock source */
  if(HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
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
