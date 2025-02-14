/**
  ******************************************************************************
  * @file    py32f403_ll_system.h
  * @author  MCU Application Team
  * @brief   Header file of SYSTEM LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PY32F403_LL_SYSTEM_H
#define PY32F403_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f4xx.h"

/** @addtogroup PY32F403_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG) || defined (DBGMCU)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
  * @{
  */
#define LL_SYSCFG_REMAP_FLASH               0x00000000U                                           /*!< Main Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SYSTEMFLASH         SYSCFG_CFGR1_MEM_MODE_0                               /*!< System Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_ESMC                SYSCFG_CFGR1_MEM_MODE_1                               /*!< ESMC mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SRAM                (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0)   /*!< Embedded SRAM mapped at 0x00000000 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_I2C_ANF I2C ANALOG FILTER ENABLE CONTORL
  * @{
  */
#define LL_SYSCFG_I2C_ANF_PB5            SYSCFG_CFGR1_I2C_PB5
#define LL_SYSCFG_I2C_ANF_PB6            SYSCFG_CFGR1_I2C_PB6
#define LL_SYSCFG_I2C_ANF_PB7            SYSCFG_CFGR1_I2C_PB7
#define LL_SYSCFG_I2C_ANF_PB8            SYSCFG_CFGR1_I2C_PB8
#define LL_SYSCFG_I2C_ANF_PB9            SYSCFG_CFGR1_I2C_PB9
#define LL_SYSCFG_I2C_ANF_PB10           SYSCFG_CFGR1_I2C_PB10
#define LL_SYSCFG_I2C_ANF_PB11           SYSCFG_CFGR1_I2C_PB11
#define LL_SYSCFG_I2C_ANF_PB12           SYSCFG_CFGR1_I2C_PB12
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK TIMER BREAK INPUT
  * @{
  */
#if defined(SYSCFG_CFGR2_LOCKUP_LOCK)
#define LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL      SYSCFG_CFGR2_LOCKUP_LOCK
#endif
#if defined(SYSCFG_CFGR2_PVD_LOCK)
#define LL_SYSCFG_TIMBREAK_PVD_TO_ALL         SYSCFG_CFGR2_PVD_LOCK
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DMA_MAP DMA MAP
  * @{
  */
#define LL_SYSCFG_DMA_MAP_ADC1              0x00000000U
#define LL_SYSCFG_DMA_MAP_ADC2              0x00000001U
#define LL_SYSCFG_DMA_MAP_ADC3              0x00000002U
#if defined(DAC1)
#define LL_SYSCFG_DMA_MAP_DAC1              0x00000003U
#define LL_SYSCFG_DMA_MAP_DAC2              0x00000004U
#endif /* DAC1 */
#define LL_SYSCFG_DMA_MAP_SPI1_RD           0x00000005U
#define LL_SYSCFG_DMA_MAP_SPI1_WR           0x00000006U
#define LL_SYSCFG_DMA_MAP_SPI2_RD           0x00000007U
#define LL_SYSCFG_DMA_MAP_SPI2_WR           0x00000008U
#define LL_SYSCFG_DMA_MAP_SPI3_RD           0x00000009U
#define LL_SYSCFG_DMA_MAP_SPI3_WR           0x0000000AU
#define LL_SYSCFG_DMA_MAP_USART1_RD         0x0000000BU
#define LL_SYSCFG_DMA_MAP_USART1_WR         0x0000000CU
#define LL_SYSCFG_DMA_MAP_USART2_RD         0x0000000DU
#define LL_SYSCFG_DMA_MAP_USART2_WR         0x0000000EU
#define LL_SYSCFG_DMA_MAP_USART3_RD         0x0000000FU
#define LL_SYSCFG_DMA_MAP_USART3_WR         0x00000010U
#define LL_SYSCFG_DMA_MAP_USART4_RD         0x00000011U
#define LL_SYSCFG_DMA_MAP_USART4_WR         0x00000012U
#define LL_SYSCFG_DMA_MAP_USART5_RD         0x00000013U
#define LL_SYSCFG_DMA_MAP_USART5_WR         0x00000014U
#define LL_SYSCFG_DMA_MAP_I2C1_RD           0x00000015U
#define LL_SYSCFG_DMA_MAP_I2C1_WR           0x00000016U
#define LL_SYSCFG_DMA_MAP_I2C2_RD           0x00000017U
#define LL_SYSCFG_DMA_MAP_I2C2_WR           0x00000018U
#define LL_SYSCFG_DMA_MAP_TIM1_CH1          0x00000019U
#define LL_SYSCFG_DMA_MAP_TIM1_CH2          0x0000001AU
#define LL_SYSCFG_DMA_MAP_TIM1_CH3          0x0000001BU
#define LL_SYSCFG_DMA_MAP_TIM1_CH4          0x0000001CU
#define LL_SYSCFG_DMA_MAP_TIM1_COM          0x0000001DU
#define LL_SYSCFG_DMA_MAP_TIM1_TRIG         0x0000001EU
#define LL_SYSCFG_DMA_MAP_TIM1_UP           0x0000001FU
#define LL_SYSCFG_DMA_MAP_TIM2_CH1          0x00000020U
#define LL_SYSCFG_DMA_MAP_TIM2_CH2          0x00000021U
#define LL_SYSCFG_DMA_MAP_TIM2_CH3          0x00000022U
#define LL_SYSCFG_DMA_MAP_TIM2_CH4          0x00000023U
#define LL_SYSCFG_DMA_MAP_TIM2_UP           0x00000024U
#define LL_SYSCFG_DMA_MAP_TIM3_CH1          0x00000025U
#define LL_SYSCFG_DMA_MAP_TIM3_CH3          0x00000026U
#define LL_SYSCFG_DMA_MAP_TIM3_CH4          0x00000027U
#define LL_SYSCFG_DMA_MAP_TIM3_UP           0x00000028U
#define LL_SYSCFG_DMA_MAP_TIM3_TRIG         0x00000029U
#define LL_SYSCFG_DMA_MAP_TIM4_CH1          0x0000002AU
#define LL_SYSCFG_DMA_MAP_TIM4_CH2          0x0000002BU
#define LL_SYSCFG_DMA_MAP_TIM4_CH3          0x0000002CU
#define LL_SYSCFG_DMA_MAP_TIM4_UP           0x0000002DU
#define LL_SYSCFG_DMA_MAP_TIM5_CH1          0x0000002EU
#define LL_SYSCFG_DMA_MAP_TIM5_CH2          0x0000002FU
#define LL_SYSCFG_DMA_MAP_TIM5_CH3          0x00000030U
#define LL_SYSCFG_DMA_MAP_TIM5_CH4          0x00000031U
#define LL_SYSCFG_DMA_MAP_TIM5_UP           0x00000032U
#define LL_SYSCFG_DMA_MAP_TIM5_TRIG         0x00000033U
#define LL_SYSCFG_DMA_MAP_TIM6              0x00000034U
#define LL_SYSCFG_DMA_MAP_TIM7              0x00000035U
#define LL_SYSCFG_DMA_MAP_TIM8_CH1          0x00000036U
#define LL_SYSCFG_DMA_MAP_TIM8_CH2          0x00000037U
#define LL_SYSCFG_DMA_MAP_TIM8_CH3          0x00000038U
#define LL_SYSCFG_DMA_MAP_TIM8_CH4          0x00000039U
#define LL_SYSCFG_DMA_MAP_TIM8_COM          0x0000003AU
#define LL_SYSCFG_DMA_MAP_TIM8_TRIG         0x0000003BU
#define LL_SYSCFG_DMA_MAP_TIM8_UP           0x0000003CU
#define LL_SYSCFG_DMA_MAP_TIM2_TRIG         0x0000003DU
#define LL_SYSCFG_DMA_MAP_TIM3_CH2          0x0000003EU
#define LL_SYSCFG_DMA_MAP_TIM4_CH4          0x0000003FU
#define LL_SYSCFG_DMA_MAP_TIM4_TRIG         0x00000040U
#define LL_SYSCFG_DMA_MAP_ESMC_TX           0x00000041U
#define LL_SYSCFG_DMA_MAP_ESMC_RX           0x00000042U
#define LL_SYSCFG_DMA_MAP_SDIO              0x00000043U
#define LL_SYSCFG_DMA_MAP_USB               0x00000044U
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_EXTI_PORT EXTI PORT
  * @{
  */
#define LL_SYSCFG_EXTI_PORTA            0U   /*!< EXTI PORT A */
#define LL_SYSCFG_EXTI_PORTB            1U   /*!< EXTI PORT B */
#define LL_SYSCFG_EXTI_PORTC            2U   /*!< EXTI PORT C */
#define LL_SYSCFG_EXTI_PORTD            3U   /*!< EXTI PORT D */
#define LL_SYSCFG_EXTI_PORTE            4U   /*!< EXTI PORT E */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_EXTI_LINE EXTI LINE
  * @{
  */
#define LL_SYSCFG_EXTI_LINE0            (0x000FU << 16U | 0U)  /*!< EXTI_POSITION_0  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE1            (0x00F0U << 16U | 0U)  /*!< EXTI_POSITION_4  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE2            (0x0F00U << 16U | 0U)  /*!< EXTI_POSITION_8  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE3            (0xF000U << 16U | 0U)  /*!< EXTI_POSITION_12 | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE4            (0x000FU << 16U | 1U)  /*!< EXTI_POSITION_0  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE5            (0x00F0U << 16U | 1U)  /*!< EXTI_POSITION_4  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE6            (0x0F00U << 16U | 1U)  /*!< EXTI_POSITION_8  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE7            (0xF000U << 16U | 1U)  /*!< EXTI_POSITION_12 | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE8            (0x000FU << 16U | 2U)  /*!< EXTI_POSITION_0  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE9            (0x00F0U << 16U | 2U)  /*!< EXTI_POSITION_4  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE10           (0x0F00U << 16U | 2U)  /*!< EXTI_POSITION_8  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE11           (0xF000U << 16U | 2U)  /*!< EXTI_POSITION_12 | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE12           (0x000FU << 16U | 3U)  /*!< EXTI_POSITION_0  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE13           (0x00F0U << 16U | 3U)  /*!< EXTI_POSITION_4  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE14           (0x0F00U << 16U | 3U)  /*!< EXTI_POSITION_8  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE15           (0xF000U << 16U | 3U)  /*!< EXTI_POSITION_12 | EXTICR[3] */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_GPIO_PORT GPIO PORT
  * @{
  */
#define LL_SYSCFG_GPIO_PORTA              0x00000000U
#define LL_SYSCFG_GPIO_PORTB              0x00000001U
#define LL_SYSCFG_GPIO_PORTC              0x00000002U
#define LL_SYSCFG_GPIO_PORTD              0x00000003U
#define LL_SYSCFG_GPIO_PORTE              0x00000004U
/**
  * @}
  */
  
/** @defgroup SYSTEM_LL_EC_GPIO_PIN GPIO PIN
  * @{
  */
#define LL_SYSCFG_GPIO_PIN_0              0x00000001U
#define LL_SYSCFG_GPIO_PIN_1              0x00000002U
#define LL_SYSCFG_GPIO_PIN_2              0x00000004U
#define LL_SYSCFG_GPIO_PIN_3              0x00000008U
#define LL_SYSCFG_GPIO_PIN_4              0x00000010U
#define LL_SYSCFG_GPIO_PIN_5              0x00000020U
#define LL_SYSCFG_GPIO_PIN_6              0x00000040U
#define LL_SYSCFG_GPIO_PIN_7              0x00000080U
#define LL_SYSCFG_GPIO_PIN_8              0x00000100U
#define LL_SYSCFG_GPIO_PIN_9              0x00000200U
#define LL_SYSCFG_GPIO_PIN_10             0x00000400U
#define LL_SYSCFG_GPIO_PIN_11             0x00000800U
#define LL_SYSCFG_GPIO_PIN_12             0x00001000U
#define LL_SYSCFG_GPIO_PIN_13             0x00002000U
#define LL_SYSCFG_GPIO_PIN_14             0x00004000U
#define LL_SYSCFG_GPIO_PIN_15             0x00008000U
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_GPIO_ENA GPIO Enable Analog Mode
  * @{
  */
#define LL_SYSCFG_GPIO_ENA_PA0            SYSCFG_GPIOENA_PA_ENA_0
#define LL_SYSCFG_GPIO_ENA_PA1            SYSCFG_GPIOENA_PA_ENA_1
#define LL_SYSCFG_GPIO_ENA_PA2            SYSCFG_GPIOENA_PA_ENA_2
#define LL_SYSCFG_GPIO_ENA_PA3            SYSCFG_GPIOENA_PA_ENA_3
#define LL_SYSCFG_GPIO_ENA_PA4            SYSCFG_GPIOENA_PA_ENA_4
#define LL_SYSCFG_GPIO_ENA_PA5            SYSCFG_GPIOENA_PA_ENA_5
#define LL_SYSCFG_GPIO_ENA_PA6            SYSCFG_GPIOENA_PA_ENA_6
#define LL_SYSCFG_GPIO_ENA_PA7            SYSCFG_GPIOENA_PA_ENA_7
#define LL_SYSCFG_GPIO_ENA_PB0            SYSCFG_GPIOENA_PB_ENA_0
#define LL_SYSCFG_GPIO_ENA_PB1            SYSCFG_GPIOENA_PB_ENA_1
#define LL_SYSCFG_GPIO_ENA_PC0            SYSCFG_GPIOENA_PC_ENA_0
#define LL_SYSCFG_GPIO_ENA_PC1            SYSCFG_GPIOENA_PC_ENA_1
#define LL_SYSCFG_GPIO_ENA_PC2            SYSCFG_GPIOENA_PC_ENA_2
#define LL_SYSCFG_GPIO_ENA_PC3            SYSCFG_GPIOENA_PC_ENA_3
#define LL_SYSCFG_GPIO_ENA_PC4            SYSCFG_GPIOENA_PC_ENA_4
#define LL_SYSCFG_GPIO_ENA_PC5            SYSCFG_GPIOENA_PC_ENA_5
/**
  * @}
  */


/** @defgroup SYSTEM_LL_EC_TIMER_CLOCK_2X Timer clock 2X pclk
  * @{
  */
#define LL_SYSCFG_TIM2_3_4_5_6_7_12_13_14_SEL    SYSCFG_TIM_PCLK1_SEL                  /*!< timer clock 2X APB1 clock */
#define LL_SYSCFG_TIM1_8_9_10_11_SEL             SYSCFG_TIM_PCLK2_SEL                  /*!< timer clock 2X APB2 clock */
/**
  * @}
  */

  
/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000UL                                  /*!< FLASH Zero wait state */
#define LL_FLASH_LATENCY_1                 FLASH_ACR_LATENCY_0                           /*!< FLASH One wait state */
#define LL_FLASH_LATENCY_3                 (FLASH_ACR_LATENCY_0 | FLASH_ACR_LATENCY_1)   /*!< FLASH Three wait state */
#define LL_FLASH_LATENCY_4                 FLASH_ACR_LATENCY_2                           /*!< FLASH Four wait state */
#define LL_FLASH_LATENCY_5                 (FLASH_ACR_LATENCY_0 | FLASH_ACR_LATENCY_2)   /*!< FLASH Five wait state */
#define LL_FLASH_LATENCY_6                 (FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_2)   /*!< FLASH Six wait state */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DBGMCU_TRACE DBGMCU TRACE Pin Assignment
  * @{
  */
#define LL_DBGMCU_TRACE_NONE               0x00000000U                                     /*!< TRACE pins not assigned (default state) */
#define LL_DBGMCU_TRACE_ASYNCH             DBGMCU_CR_TRACE_IOEN                            /*!< TRACE pin assignment for Asynchronous Mode */
#define LL_DBGMCU_TRACE_SYNCH_SIZE1        (DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE_0) /*!< TRACE pin assignment for Synchronous Mode with a TRACEDATA size of 1 */
#define LL_DBGMCU_TRACE_SYNCH_SIZE2        (DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE_1) /*!< TRACE pin assignment for Synchronous Mode with a TRACEDATA size of 2 */
#define LL_DBGMCU_TRACE_SYNCH_SIZE4        (DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE)   /*!< TRACE pin assignment for Synchronous Mode with a TRACEDATA size of 4 */
/**
  * @}
  */
  
/** @defgroup SYSTEM_LL_EC_STOP_IP  DBGMCU STOP IP
  * @{
  */
#if defined(DBGMCU_CR_DBG_IWDG_STOP)
#define LL_DBGMCU_IWDG_STOP                  DBGMCU_CR_DBG_IWDG_STOP
#endif

#if defined(DBGMCU_CR_DBG_WWDG_STOP)
#define LL_DBGMCU_WWDG_STOP                  DBGMCU_CR_DBG_WWDG_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM1_STOP)
#define LL_DBGMCU_TIM1_STOP                  DBGMCU_CR_DBG_TIM1_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM2_STOP)
#define LL_DBGMCU_TIM2_STOP                  DBGMCU_CR_DBG_TIM2_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM3_STOP)
#define LL_DBGMCU_TIM3_STOP                  DBGMCU_CR_DBG_TIM3_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM4_STOP)
#define LL_DBGMCU_TIM4_STOP                  DBGMCU_CR_DBG_TIM4_STOP
#endif

#if defined(DBGMCU_CR_DBG_CAN_STOP)
#define LL_DBGMCU_CAN_STOP                   DBGMCU_CR_DBG_CAN_STOP
#endif

#if defined(DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT)
#define LL_DBGMCU_I2C1_SMBUS_TIMEOUT                   DBGMCU_CR_DBG_I2C1_SMBUS_TIMEOUT
#endif

#if defined(DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT)
#define LL_DBGMCU_I2C2_SMBUS_TIMEOUT                   DBGMCU_CR_DBG_I2C2_SMBUS_TIMEOUT
#endif

#if defined(DBGMCU_CR_DBG_TIM8_STOP)
#define LL_DBGMCU_TIM8_STOP                  DBGMCU_CR_DBG_TIM8_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM5_STOP)
#define LL_DBGMCU_TIM5_STOP                  DBGMCU_CR_DBG_TIM5_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM6_STOP)
#define LL_DBGMCU_TIM6_STOP                  DBGMCU_CR_DBG_TIM6_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM7_STOP)
#define LL_DBGMCU_TIM7_STOP                  DBGMCU_CR_DBG_TIM7_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM12_STOP)
#define LL_DBGMCU_TIM12_STOP                  DBGMCU_CR_DBG_TIM12_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM13_STOP)
#define LL_DBGMCU_TIM13_STOP                  DBGMCU_CR_DBG_TIM13_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM14_STOP)
#define LL_DBGMCU_TIM14_STOP                  DBGMCU_CR_DBG_TIM14_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM9_STOP)
#define LL_DBGMCU_TIM9_STOP                  DBGMCU_CR_DBG_TIM9_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM10_STOP)
#define LL_DBGMCU_TIM10_STOP                  DBGMCU_CR_DBG_TIM10_STOP
#endif

#if defined(DBGMCU_CR_DBG_TIM11_STOP)
#define LL_DBGMCU_TIM11_STOP                  DBGMCU_CR_DBG_TIM11_STOP
#endif

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_ESMC
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(SYSCFG->CFGR[0], SYSCFG_CFGR1_MEM_MODE, Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_ESMC
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR[0], SYSCFG_CFGR1_MEM_MODE));
}

/**
  * @brief  Enable analog filtering of I2C related IO
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  I2CAnalogFilter This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB5 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB6 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB7 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB8 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB9 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB10
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB11
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB12
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableI2CAnalogFilter(uint32_t I2CAnalogFilter)
{
  SET_BIT(SYSCFG->CFGR[0], I2CAnalogFilter);
}

/**
  * @brief  Disable analog filtering of I2C related IO
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  I2CAnalogFilter This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB5 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB6 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB7 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB8 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB9 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB10
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB11
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB12
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableI2CAnalogFilter(uint32_t I2CAnalogFilter)
{
  CLEAR_BIT(SYSCFG->CFGR[0], I2CAnalogFilter);
}

/**
  * @brief  Indicate if enable analog filtering of I2C related IO
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  I2CAnalogFilter This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB5 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB6 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB7 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB8 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB9 
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB10
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB11
  *         @arg @ref LL_SYSCFG_I2C_ANF_PB12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledI2CAnalogFilter(uint32_t I2CAnalogFilter)
{
  return ((READ_BIT(SYSCFG->CFGR[0], I2CAnalogFilter) == (I2CAnalogFilter)) ? 1UL : 0UL);
}

/**
  * @brief  Enables COMPx as TIMx break input
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  TIMBreakInputs This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableTIMBreakInputs(uint32_t TIMBreakInputs)
{
  SET_BIT(SYSCFG->CFGR[1], TIMBreakInputs);
}

/**
  * @brief  Disables COMPx as TIMx break input
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  TIMBreakInputs This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableTIMBreakInputs(uint32_t TIMBreakInputs)
{
  CLEAR_BIT(SYSCFG->CFGR[1], TIMBreakInputs);
}

/**
  * @brief  Indicate if COMPx as TIMx break input
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  TIMBreakInputs This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP_TO_ALL
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD_TO_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledTIMBreakInputs(uint32_t TIMBreakInputs)
{
  return ((READ_BIT(SYSCFG->CFGR[1], TIMBreakInputs) == (TIMBreakInputs)) ? 1UL : 0UL);
}

/**
  * @brief Enable the remapping of ADC1_ETRGINJ (ADC 1 External trigger injected conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableRemap_ADC1_ETRGINJ(void)
{
  SET_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC1_ETRGINJ_REMAP);
}

/**
  * @brief Disable the remapping of ADC1_ETRGINJ (ADC 1 External trigger injected conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableRemap_ADC1_ETRGINJ(void)
{
  CLEAR_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC1_ETRGINJ_REMAP);
}

/**
  * @brief  Check if ADC1_ETRGINJ has been remaped or not
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledRemap_ADC1_ETRGINJ(void)
{
  return (READ_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC1_ETRGINJ_REMAP) == (SYSCFG_CFGR2_ADC1_ETRGINJ_REMAP));
}

/**
  * @brief Enable the remapping of ADC1_ETRGREG (ADC 1 External trigger regular conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableRemap_ADC1_ETRGREG(void)
{
  SET_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC1_ETRGREG_REMAP);
}

/**
  * @brief Disable the remapping of ADC1_ETRGREG (ADC 1 External trigger regular conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableRemap_ADC1_ETRGREG(void)
{
  CLEAR_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC1_ETRGREG_REMAP);
}

/**
  * @brief  Check if ADC1_ETRGREG has been remaped or not
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledRemap_ADC1_ETRGREG(void)
{
  return (READ_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC1_ETRGREG_REMAP) == (SYSCFG_CFGR2_ADC1_ETRGREG_REMAP));
}

/**
  * @brief Enable the remapping of ADC2_ETRGINJ (ADC 2 External trigger injected conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableRemap_ADC2_ETRGINJ(void)
{
  SET_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC2_ETRGINJ_REMAP);
}

/**
  * @brief Disable the remapping of ADC2_ETRGINJ (ADC 2 External trigger injected conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableRemap_ADC2_ETRGINJ(void)
{
  CLEAR_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC2_ETRGINJ_REMAP);
}

/**
  * @brief  Check if ADC2_ETRGINJ has been remaped or not
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledRemap_ADC2_ETRGINJ(void)
{
  return (READ_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC2_ETRGINJ_REMAP) == (SYSCFG_CFGR2_ADC2_ETRGINJ_REMAP));
}

/**
  * @brief Enable the remapping of ADC2_ETRGREG (ADC 2 External trigger regular conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableRemap_ADC2_ETRGREG(void)
{
  SET_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC2_ETRGREG_REMAP);
}

/**
  * @brief Disable the remapping of ADC2_ETRGREG (ADC 2 External trigger regular conversion).
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableRemap_ADC2_ETRGREG(void)
{
  CLEAR_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC2_ETRGREG_REMAP);
}

/**
  * @brief  Check if ADC2_ETRGREG has been remaped or not
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledRemap_ADC2_ETRGREG(void)
{
  return (READ_BIT(SYSCFG->CFGR[1], SYSCFG_CFGR2_ADC2_ETRGREG_REMAP) == (SYSCFG_CFGR2_ADC2_ETRGREG_REMAP));
}

/**
  * @brief  Configure source input for the EXTI external interrupt.
  * @param  Port This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_PORTA
  *         @arg @ref LL_SYSCFG_EXTI_PORTB
  *         @arg @ref LL_SYSCFG_EXTI_PORTC
  *         @arg @ref LL_SYSCFG_EXTI_PORTD
  *         @arg @ref LL_SYSCFG_EXTI_PORTE
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_LINE0 
  *         @arg @ref LL_SYSCFG_EXTI_LINE1 
  *         @arg @ref LL_SYSCFG_EXTI_LINE2 
  *         @arg @ref LL_SYSCFG_EXTI_LINE3 
  *         @arg @ref LL_SYSCFG_EXTI_LINE4 
  *         @arg @ref LL_SYSCFG_EXTI_LINE5 
  *         @arg @ref LL_SYSCFG_EXTI_LINE6 
  *         @arg @ref LL_SYSCFG_EXTI_LINE7 
  *         @arg @ref LL_SYSCFG_EXTI_LINE8 
  *         @arg @ref LL_SYSCFG_EXTI_LINE9 
  *         @arg @ref LL_SYSCFG_EXTI_LINE10
  *         @arg @ref LL_SYSCFG_EXTI_LINE11
  *         @arg @ref LL_SYSCFG_EXTI_LINE12
  *         @arg @ref LL_SYSCFG_EXTI_LINE13
  *         @arg @ref LL_SYSCFG_EXTI_LINE14
  *         @arg @ref LL_SYSCFG_EXTI_LINE15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetEXTISource(uint32_t Port, uint32_t Line)
{
  MODIFY_REG(SYSCFG->EXTICR[Line & 0xFF], (Line >> 16), Port << POSITION_VAL((Line >> 16)));
}

/**
  * @brief  Get the configured defined for specific EXTI Line
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_LINE0 
  *         @arg @ref LL_SYSCFG_EXTI_LINE1 
  *         @arg @ref LL_SYSCFG_EXTI_LINE2 
  *         @arg @ref LL_SYSCFG_EXTI_LINE3 
  *         @arg @ref LL_SYSCFG_EXTI_LINE4 
  *         @arg @ref LL_SYSCFG_EXTI_LINE5 
  *         @arg @ref LL_SYSCFG_EXTI_LINE6 
  *         @arg @ref LL_SYSCFG_EXTI_LINE7 
  *         @arg @ref LL_SYSCFG_EXTI_LINE8 
  *         @arg @ref LL_SYSCFG_EXTI_LINE9 
  *         @arg @ref LL_SYSCFG_EXTI_LINE10
  *         @arg @ref LL_SYSCFG_EXTI_LINE11
  *         @arg @ref LL_SYSCFG_EXTI_LINE12
  *         @arg @ref LL_SYSCFG_EXTI_LINE13
  *         @arg @ref LL_SYSCFG_EXTI_LINE14
  *         @arg @ref LL_SYSCFG_EXTI_LINE15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_PORTA
  *         @arg @ref LL_SYSCFG_EXTI_PORTB
  *         @arg @ref LL_SYSCFG_EXTI_PORTC
  *         @arg @ref LL_SYSCFG_EXTI_PORTD
  *         @arg @ref LL_SYSCFG_EXTI_PORTE
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetEXTISource(uint32_t Line)
{
  return (uint32_t)(READ_BIT(SYSCFG->EXTICR[Line & 0xFF], (Line >> 16)) >> POSITION_VAL(Line >> 16));
}

/**
  * @brief  Enable GPIO Filter
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  *         @arg @ref LL_SYSCFG_GPIO_PORTB
  *         @arg @ref LL_SYSCFG_GPIO_PORTC
  *         @arg @ref LL_SYSCFG_GPIO_PORTD
  *         @arg @ref LL_SYSCFG_GPIO_PORTE
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_0
  *         @arg @ref LL_SYSCFG_GPIO_PIN_1
  *         @arg @ref LL_SYSCFG_GPIO_PIN_2
  *         @arg @ref LL_SYSCFG_GPIO_PIN_3
  *         @arg @ref LL_SYSCFG_GPIO_PIN_4
  *         @arg @ref LL_SYSCFG_GPIO_PIN_5
  *         @arg @ref LL_SYSCFG_GPIO_PIN_6
  *         @arg @ref LL_SYSCFG_GPIO_PIN_7
  *         @arg @ref LL_SYSCFG_GPIO_PIN_8
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  *         @arg @ref LL_SYSCFG_GPIO_PIN_11
  *         @arg @ref LL_SYSCFG_GPIO_PIN_12
  *         @arg @ref LL_SYSCFG_GPIO_PIN_13
  *         @arg @ref LL_SYSCFG_GPIO_PIN_14
  *         @arg @ref LL_SYSCFG_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableGPIOFilter(uint32_t GPIOPort, uint32_t GPIOPin)
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    SET_BIT(SYSCFG->PAENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTB)
  {
    SET_BIT(SYSCFG->PBENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTC)
  {    
    SET_BIT(SYSCFG->PCENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTD)
  {    
    SET_BIT(SYSCFG->PDENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTE)
  {
    SET_BIT(SYSCFG->PEENS, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @brief  Disable GPIO Filter
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOPort This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PORTA
  *         @arg @ref LL_SYSCFG_GPIO_PORTB
  *         @arg @ref LL_SYSCFG_GPIO_PORTC
  *         @arg @ref LL_SYSCFG_GPIO_PORTD
  *         @arg @ref LL_SYSCFG_GPIO_PORTE
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_PIN_0
  *         @arg @ref LL_SYSCFG_GPIO_PIN_1
  *         @arg @ref LL_SYSCFG_GPIO_PIN_2
  *         @arg @ref LL_SYSCFG_GPIO_PIN_3
  *         @arg @ref LL_SYSCFG_GPIO_PIN_4
  *         @arg @ref LL_SYSCFG_GPIO_PIN_5
  *         @arg @ref LL_SYSCFG_GPIO_PIN_6
  *         @arg @ref LL_SYSCFG_GPIO_PIN_7
  *         @arg @ref LL_SYSCFG_GPIO_PIN_8
  *         @arg @ref LL_SYSCFG_GPIO_PIN_9
  *         @arg @ref LL_SYSCFG_GPIO_PIN_10
  *         @arg @ref LL_SYSCFG_GPIO_PIN_11
  *         @arg @ref LL_SYSCFG_GPIO_PIN_12
  *         @arg @ref LL_SYSCFG_GPIO_PIN_13
  *         @arg @ref LL_SYSCFG_GPIO_PIN_14
  *         @arg @ref LL_SYSCFG_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableGPIOFilter(uint32_t GPIOPort, uint32_t GPIOPin)
{
  if(GPIOPort == LL_SYSCFG_GPIO_PORTA)
  {
    CLEAR_BIT(SYSCFG->PAENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTB)
  {
    CLEAR_BIT(SYSCFG->PBENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTC)
  {    
    CLEAR_BIT(SYSCFG->PCENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTD)
  {    
    CLEAR_BIT(SYSCFG->PDENS, GPIOPin);
  }
  else if(GPIOPort == LL_SYSCFG_GPIO_PORTE)
  {
    CLEAR_BIT(SYSCFG->PEENS, GPIOPin);
  }
  else
  {
    
  }
}

/**
  * @brief  Enable GPIO Analog Mode
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOAnalogEnable This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA0
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA1
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA2
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA3
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA4
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA5
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA6
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA7
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PB0
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PB1
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC0
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC1
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC2
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC3
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC4
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC5
  */
__STATIC_INLINE void LL_SYSCFG_EnableGPIOAnalogMode(uint32_t GPIOAnalogEnable)
{
  SET_BIT(SYSCFG->GPIOENA,GPIOAnalogEnable);
}

/**
  * @brief  Disable GPIO Analog Mode
  * @note   Depending on devices and packages, some IOs may not be available.
  *         Refer to device datasheet for IOs availability.
  * @param  GPIOAnalogEnable This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA0
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA1
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA2
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA3
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA4
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA5
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA6
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PA7
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PB0
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PB1
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC0
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC1
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC2
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC3
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC4
  *         @arg @ref LL_SYSCFG_GPIO_ENA_PC5
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableGPIOAnalogMode(uint32_t GPIOAnalogEnable)
{
  CLEAR_BIT(SYSCFG->GPIOENA,GPIOAnalogEnable);
}

/**
  * @brief  Enable the timer clock 2X pclk
  * @note   Depending on devices and packages, some timers may not be available.
  *         Refer to device datasheet for timers availability.
  * @param  TimerSelect This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIM2_3_4_5_6_7_12_13_14_SEL
  *         @arg @ref LL_SYSCFG_TIM1_8_9_10_11_SEL
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableTimerClock2xPclk(uint32_t TimerSelect)
{    
  CLEAR_BIT(SYSCFG->TIM_CLK_EXT,TimerSelect);
}

/**
  * @brief  Disable the timer clock 2X pclk
  * @note   Depending on devices and packages, some timers may not be available.
  *         Refer to device datasheet for timers availability.
  * @param  TimerSelect This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIM2_3_4_5_6_7_12_13_14_SEL
  *         @arg @ref LL_SYSCFG_TIM1_8_9_10_11_SEL
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableTimerClock2xPclk(uint32_t TimerSelect)
{
  SET_BIT(SYSCFG->TIM_CLK_EXT,TimerSelect);
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_3
  *         @arg @ref LL_FLASH_LATENCY_4
  *         @arg @ref LL_FLASH_LATENCY_5
  *         @arg @ref LL_FLASH_LATENCY_6
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_3
  *         @arg @ref LL_FLASH_LATENCY_4
  *         @arg @ref LL_FLASH_LATENCY_5
  *         @arg @ref LL_FLASH_LATENCY_6
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the device revision identifier
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Indicate if enable the Debug Module during SLEEP mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGSleepMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP) == (DBGMCU_CR_DBG_SLEEP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Indicate if enable the Debug Module during STOP mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStopMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP) == (DBGMCU_CR_DBG_STOP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Debug Module during Standby mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STDBY);
}

/**
  * @brief  Disable the Debug Module during Standby mode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STDBY);
}

/**
  * @brief  Indicate if enable the Debug Module during Standby mode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStandbyMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STDBY) == (DBGMCU_CR_DBG_STDBY)) ? 1UL : 0UL);
}

/**
  * @brief  Set Trace pin assignment control
  * @param  PinAssignment This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_TRACE_NONE
  *         @arg @ref LL_DBGMCU_TRACE_ASYNCH
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE1
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE2
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE4
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_SetTracePinAssignment(uint32_t PinAssignment)
{
  MODIFY_REG(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE, PinAssignment);
}

/**
  * @brief  Get Trace pin assignment control
  * @retval  PinAssignment This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_TRACE_NONE
  *         @arg @ref LL_DBGMCU_TRACE_ASYNCH
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE1
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE2
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE4
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetTracePinAssignment()
{
  return (READ_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE));
}

/**
  * @brief  Freeze peripherals.
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  *         @arg @ref LL_DBGMCU_TIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM3_STOP
  *         @arg @ref LL_DBGMCU_TIM4_STOP
  *         @arg @ref LL_DBGMCU_CAN_STOP
  *         @arg @ref LL_DBGMCU_I2C1_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_I2C2_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM5_STOP
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_TIM12_STOP
  *         @arg @ref LL_DBGMCU_TIM13_STOP
  *         @arg @ref LL_DBGMCU_TIM14_STOP
  *         @arg @ref LL_DBGMCU_TIM9_STOP
  *         @arg @ref LL_DBGMCU_TIM10_STOP
  *         @arg @ref LL_DBGMCU_TIM11_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->CR, Periphs);
}

/**
  * @brief  Unfreeze peripherals.D
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  *         @arg @ref LL_DBGMCU_TIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM3_STOP
  *         @arg @ref LL_DBGMCU_TIM4_STOP
  *         @arg @ref LL_DBGMCU_CAN_STOP
  *         @arg @ref LL_DBGMCU_I2C1_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_I2C2_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM5_STOP
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_TIM12_STOP
  *         @arg @ref LL_DBGMCU_TIM13_STOP
  *         @arg @ref LL_DBGMCU_TIM14_STOP
  *         @arg @ref LL_DBGMCU_TIM9_STOP
  *         @arg @ref LL_DBGMCU_TIM10_STOP
  *         @arg @ref LL_DBGMCU_TIM11_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->CR, Periphs);
}

/**
  * @brief  Indicate if Freeze peripherals.
  * @note   Depending on devices and packages, some Peripherals may not be available.
  *         Refer to device datasheet for Peripherals availability.
  * @param  Periphs This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  *         @arg @ref LL_DBGMCU_TIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM3_STOP
  *         @arg @ref LL_DBGMCU_TIM4_STOP
  *         @arg @ref LL_DBGMCU_CAN_STOP
  *         @arg @ref LL_DBGMCU_I2C1_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_I2C2_SMBUS_TIMEOUT
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM5_STOP
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_TIM12_STOP
  *         @arg @ref LL_DBGMCU_TIM13_STOP
  *         @arg @ref LL_DBGMCU_TIM14_STOP
  *         @arg @ref LL_DBGMCU_TIM9_STOP
  *         @arg @ref LL_DBGMCU_TIM10_STOP
  *         @arg @ref LL_DBGMCU_TIM11_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsFreezePeriph(uint32_t Periphs)
{
  return ((READ_BIT(DBGMCU->CR, Periphs) == (Periphs)) ? 1UL : 0UL);
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */



#endif /* defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F403_LL_SYSTEM_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
