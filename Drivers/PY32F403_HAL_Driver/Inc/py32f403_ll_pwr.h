/**
  ******************************************************************************
  * @file    py32f403_ll_pwr.h
  * @author  MCU Application Team
  * @brief   Header file of PWR LL module.
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
#ifndef PY32F403_LL_PWR_H
#define PY32F403_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f4xx.h"

/** @addtogroup PY32F403_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_REGU_VOLTAGE REGU VOLTAGE
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SCALE1         0x00000000U                     /* After entering stop mode, VDD=1.1V */
#define LL_PWR_REGU_VOLTAGE_SCALE2         (PWR_CR_VOS_0)                  /* After entering stop mode, VDD=1.0V */
#define LL_PWR_REGU_VOLTAGE_SCALE3         (PWR_CR_VOS_1)                  /* After entering stop mode, VDD=0.9V */
#define LL_PWR_REGU_VOLTAGE_SCALE4         (PWR_CR_VOS_1 | PWR_CR_VOS_0)   /* After entering stop mode, VDD=0.8V */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGU_VOLTAGE REGU VOLTAGE
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_1P1V           LL_PWR_REGU_VOLTAGE_SCALE1        /* After entering stop mode, VDD=1.1V */
#define LL_PWR_REGU_VOLTAGE_1P0V           LL_PWR_REGU_VOLTAGE_SCALE2        /* After entering stop mode, VDD=1.0V */
#define LL_PWR_REGU_VOLTAGE_0P9V           LL_PWR_REGU_VOLTAGE_SCALE3        /* After entering stop mode, VDD=0.9V */
#define LL_PWR_REGU_VOLTAGE_0P8V           LL_PWR_REGU_VOLTAGE_SCALE4        /* After entering stop mode, VDD=0.8V */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_BACKUP_VOLTAGE BACKUP VOLTAGE
  * @{
  */
#define LL_PWR_BACKUP_VOLTAGE_1P1V           (0x00000000)                                     /* VDDK=1.1V */
#define LL_PWR_BACKUP_VOLTAGE_0P9V           (PWR_CR_BKPVR_VOS_0)                             /* VDDK=0.9V */
#define LL_PWR_BACKUP_VOLTAGE_0P85V          (PWR_CR_BKPVR_VOS_1)                             /* VDDK=0.85V */
#define LL_PWR_BACKUP_VOLTAGE_0P8V           (PWR_CR_BKPVR_VOS_1 | PWR_CR_BKPVR_VOS_0)        /* VDDK=0.8V */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_HSION_MODE WAKEUP HSI ON MODE
  * @{
  */
#define LL_PWR_STOPWAKEUP_HSION_AFTER_MR       0x00000000U        /* Wake up from the STOP mode, After the MR becomes stable, enable HSI */
#define LL_PWR_STOPWAKEUP_HSION_IMMEDIATE      PWR_CR_HSION_CTRL  /* Wake up from the STOP mode, Enable HSI immediately */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_FLASH_DELAY WAKEUP FLASH DELAY
  * @{
  */          
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_3US      (0x00000000U)                             /* Wake up from the STOP mode, Delay 3us enable flash*/
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_5US      (                    PWR_CR_FLS_WUPT_0)   /* Wake up from the STOP mode, Delay 5us enable flash*/
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_2US      (PWR_CR_FLS_WUPT_1                    )   /* Wake up from the STOP mode, Delay 2us enable flash*/
#define LL_PWR_STOPWAKEUP_FLASH_DELAY_0US      (PWR_CR_FLS_WUPT_1 | PWR_CR_FLS_WUPT_0)   /* Wake up from the STOP mode, Delay 0us enable flash*/
/**
  * @}
  */


/** @defgroup PWR_LL_EC_WAKEUP_FLASH_DELAY WAKEUP FLASH DELAY
  * @{
  */          
#define LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_5US      (0x00000000U)                                           /* Wake up from the STANDBY mode, MR ready wait 5us*/
#define LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_10US     (                            PWR_CR_STDBY_MRRDY_WAIT_0) /* Wake up from the STANDBY mode, MR ready wait 10us*/
#define LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_20US     (PWR_CR_STDBY_MRRDY_WAIT_1                            ) /* Wake up from the STANDBY mode, MR ready wait 20us*/
#define LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_30US     (PWR_CR_STDBY_MRRDY_WAIT_1 | PWR_CR_STDBY_MRRDY_WAIT_0) /* Wake up from the STANDBY mode, MR ready wait 30us*/
/**
  * @}
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
#define LL_PWR_CR_CSBF                     PWR_CR_CSBF            /*!< Clear standby flag */
#define LL_PWR_CR_CWUF                     PWR_CR_CWUF            /*!< Clear wakeup flag */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_CSR_WUF                     PWR_CSR_WUF            /*!< Wakeup flag */
#define LL_PWR_CSR_SBF                     PWR_CSR_SBF            /*!< Standby flag */
#define LL_PWR_CSR_PVDO                    PWR_CSR_PVDO           /*!< Power voltage detector output flag */
#define LL_PWR_CSR_EWUP1                   PWR_CSR_EWUP1          /*!< Enable WKUP pin 1 */
#define LL_PWR_CSR_EWUP2                   PWR_CSR_EWUP2          /*!< Enable WKUP pin 2 */
#define LL_PWR_CSR_EWUP3                   PWR_CSR_EWUP3          /*!< Enable WKUP pin 3 */
#define LL_PWR_CSR_EWUP4                   PWR_CSR_EWUP4          /*!< Enable WKUP pin 4 */
#define LL_PWR_CSR_EWUP5                   PWR_CSR_EWUP5          /*!< Enable WKUP pin 5 */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_MODE_PWR Mode Power
  * @{
  */
#define LL_PWR_MODE_STOP_MAINREGU             0x00000000U                    /*!< Enter Stop mode when the CPU enters deepsleep */
#define LL_PWR_MODE_STOP_LPREGU               (PWR_CR_LPDS)                  /*!< Enter Stop mode (with low power Regulator ON) when the CPU enters deepsleep */
#define LL_PWR_MODE_STANDBY                   (PWR_CR_PDDS)                  /*!< Enter Standby mode when the CPU enters deepsleep */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGU_MODE_DS_MODE  Regulator Mode In Deep Sleep Mode
 * @{
 */
#define LL_PWR_REGU_DSMODE_MAIN        0x00000000U           /*!< Voltage Regulator in main mode during deepsleep mode */
#define LL_PWR_REGU_DSMODE_LOW_POWER   (PWR_CR_LPDS)         /*!< Voltage Regulator in low-power mode during deepsleep mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL Power Voltage Detector Level
  * @{
  */
#define LL_PWR_PVDLEVEL_0                  (PWR_CR_PLS_LEV0)      /*!< Voltage threshold detected by PVD 1.8 V */
#define LL_PWR_PVDLEVEL_1                  (PWR_CR_PLS_LEV1)      /*!< Voltage threshold detected by PVD 2.0 V */
#define LL_PWR_PVDLEVEL_2                  (PWR_CR_PLS_LEV2)      /*!< Voltage threshold detected by PVD 2.2 V */
#define LL_PWR_PVDLEVEL_3                  (PWR_CR_PLS_LEV3)      /*!< Voltage threshold detected by PVD 2.4 V */
#define LL_PWR_PVDLEVEL_4                  (PWR_CR_PLS_LEV4)      /*!< Voltage threshold detected by PVD 2.6 V */
#define LL_PWR_PVDLEVEL_5                  (PWR_CR_PLS_LEV5)      /*!< Voltage threshold detected by PVD 2.8 V */
#define LL_PWR_PVDLEVEL_6                  (PWR_CR_PLS_LEV6)      /*!< Voltage threshold detected by PVD 3.0 V */
#define LL_PWR_PVDLEVEL_7                  (PWR_CR_PLS_LEV7)      /*!< Voltage threshold detected by PVD 3.2 V */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDFILTER PVDFILTER
  * @{
  */
#define LL_PWR_PVD_FILTER_1CLOCK          (0x00000000u)                                                   /*!< PVD filter 1    clock */
#define LL_PWR_PVD_FILTER_2CLOCK          (                                          PWR_CSR_FLT_CTRL_0)  /*!< PVD filter 2    clock */
#define LL_PWR_PVD_FILTER_4CLOCK          (                     PWR_CSR_FLT_CTRL_1                     )  /*!< PVD filter 2    clock */
#define LL_PWR_PVD_FILTER_16CLOCK         (                     PWR_CSR_FLT_CTRL_1 | PWR_CSR_FLT_CTRL_0)  /*!< PVD filter 4    clock */
#define LL_PWR_PVD_FILTER_64CLOCK         (PWR_CSR_FLT_CTRL_2                                          )  /*!< PVD filter 16   clock */
#define LL_PWR_PVD_FILTER_128CLOCK        (PWR_CSR_FLT_CTRL_2                      | PWR_CSR_FLT_CTRL_0)  /*!< PVD filter 128  clock */
#define LL_PWR_PVD_FILTER_1024CLOCK       (PWR_CSR_FLT_CTRL_2 | PWR_CSR_FLT_CTRL_1                     )  /*!< PVD filter 1024 clock */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN  Wakeup Pins
  * @{
  */
#define LL_PWR_WAKEUP_PIN1                 (PWR_CSR_EWUP1)         /*!< WKUP pin 1 : PA0 */
#define LL_PWR_WAKEUP_PIN2                 (PWR_CSR_EWUP2)         /*!< WKUP pin 2 : PC13 */
#define LL_PWR_WAKEUP_PIN3                 (PWR_CSR_EWUP3)         /*!< WKUP pin 3 : PE6 */
#define LL_PWR_WAKEUP_PIN4                 (PWR_CSR_EWUP4)         /*!< WKUP pin 4 : PA2 */
#define LL_PWR_WAKEUP_PIN5                 (PWR_CSR_EWUP5)         /*!< WKUP pin 5 : PC5 */
/**
  * @}
  */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Set the main internal regulator output voltage
  * @rmtoll CR          VOS           LL_PWR_SetRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_1P1V
  *         @arg @ref LL_PWR_REGU_VOLTAGE_1P0V
  *         @arg @ref LL_PWR_REGU_VOLTAGE_0P9V
  *         @arg @ref LL_PWR_REGU_VOLTAGE_0P8V
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->CR, PWR_CR_VOS, VoltageScaling);
}

/**
  * @brief  Get the main internal regulator output voltage
  * @rmtoll CR          VOS           LL_PWR_GetRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_1P1V
  *         @arg @ref LL_PWR_REGU_VOLTAGE_1P0V
  *         @arg @ref LL_PWR_REGU_VOLTAGE_0P9V
  *         @arg @ref LL_PWR_REGU_VOLTAGE_0P8V
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_VOS));
}

/**
  * @brief  Set the HSI turn on mode after wake up 
  * @rmtoll CR           HSION_CTRL          LL_PWR_SetStopWakeUpHSIOnMode
  * @param  HsiOnMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_AFTER_MR
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_IMMEDIATE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStopWakeUpHSIOnMode(uint32_t HsiOnMode)
{
  MODIFY_REG(PWR->CR, PWR_CR_HSION_CTRL, HsiOnMode);
}

/**
  * @brief  Get the HSI turn on mode after wake up
  * @rmtoll CR          HSION_CTRL          LL_PWR_GetStopWakeUpHSIOnMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_AFTER_MR
  *         @arg @ref LL_PWR_STOPWAKEUP_HSION_IMMEDIATE
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopWakeUpHSIOnMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_HSION_CTRL));
}

/**
  * @brief  Set the flash delay time after wake up 
  * @rmtoll CR          STDBY_MRRDY_WAIT          LL_PWR_SetStandbyWakeUpMRReadyDelay
  * @param  FlashDelay This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_5US
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_10US
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_20US
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_30US
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStandbyWakeUpMRReadyDelay(uint32_t FlashDelay)
{
  MODIFY_REG(PWR->CR, PWR_CR_STDBY_MRRDY_WAIT, FlashDelay);
}

/**
  * @brief  Get the flash delay time after wake up 
  * @rmtoll CR          STDBY_MRRDY_WAIT          LL_PWR_GetStandbyWakeUpMRReadyDelay
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_5US
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_10US
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_20US
  *         @arg @ref LL_PWR_STANDBYWAKEUP_MRREADY_DELAY_30US
  */
__STATIC_INLINE uint32_t LL_PWR_GetStandbyWakeUpMRReadyDelay(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_STDBY_MRRDY_WAIT));
}

/**
  * @brief  Set the flash delay time after wake up 
  * @rmtoll CR          FLS_WUPT          LL_PWR_SetStopWakeUpFlashDelay
  * @param  FlashDelay This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_3US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_5US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_2US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_0US
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStopWakeUpFlashDelay(uint32_t FlashDelay)
{
  MODIFY_REG(PWR->CR, PWR_CR_FLS_WUPT, FlashDelay);
}

/**
  * @brief  Get the flash delay time after wake up 
  * @rmtoll CR          FLS_WUPT          LL_PWR_GetStopWakeUpFlashDelay
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_3US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_5US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_2US
  *         @arg @ref LL_PWR_STOPWAKEUP_FLASH_DELAY_0US
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopWakeUpFlashDelay(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_FLS_WUPT));
}

/**
  * @brief  Set the Backup voltage
  * @rmtoll CR          BKPVR_VOS          LL_PWR_SetBkUpVoltage
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_1P1V
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_0P9V
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_0P85V
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_0P8V
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetBkUpVoltage(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->CR, PWR_CR_BKPVR_VOS, VoltageScaling);   
}

/**
  * @brief  Get the Backup voltage
  * @rmtoll CR          BKPVR_VOS          LL_PWR_GetBkUpVoltage
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_1P1V
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_0P9V
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_0P85V
  *         @arg @ref LL_PWR_BACKUP_VOLTAGE_0P8V
  */
__STATIC_INLINE uint32_t LL_PWR_GetBkUpVoltage(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_BKPVR_VOS));
}

/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR    DBP       LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR, PWR_CR_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR    DBP       LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR    DBP       LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_DBP) == (PWR_CR_DBP));
}

/**
  * @brief  Set voltage Regulator mode during deep sleep mode
  * @rmtoll CR    LPDS         LL_PWR_SetRegulModeDS
  * @param  RegulMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulModeDS(uint32_t RegulMode)
{
  MODIFY_REG(PWR->CR, PWR_CR_LPDS, RegulMode);
}

/**
  * @brief  Get voltage Regulator mode during deep sleep mode
  * @rmtoll CR    LPDS         LL_PWR_GetRegulModeDS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulModeDS(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_LPDS));
}

/**
  * @brief  Set Power Down mode when CPU enters deepsleep
  * @rmtoll CR    PDDS         LL_PWR_SetPowerMode\n
  * @rmtoll CR    LPDS         LL_PWR_SetPowerMode
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP_MAINREGU
  *         @arg @ref LL_PWR_MODE_STOP_LPREGU
  *         @arg @ref LL_PWR_MODE_STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS| PWR_CR_LPDS), PDMode);
}

/**
  * @brief  Get Power Down mode when CPU enters deepsleep
  * @rmtoll CR    PDDS         LL_PWR_GetPowerMode\n
  * @rmtoll CR    LPDS         LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP_MAINREGU
  *         @arg @ref LL_PWR_MODE_STOP_LPREGU
  *         @arg @ref LL_PWR_MODE_STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, (PWR_CR_PDDS| PWR_CR_LPDS)));
}

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll CSR   EWUP       LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CSR, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll CSR   EWUP       LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CSR, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll CSR   EWUP       LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return (READ_BIT(PWR->CSR, WakeUpPin) == (WakeUpPin));
}
/**
  * @}
  */


/** @defgroup PWR_LL_EF_PVD_Management PVD_Management
  * @{
  */

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector
  * @rmtoll CR    PLS       LL_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR, PWR_CR_PLS, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR    PLS       LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_PLS));
}

/**
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR    PVDE       LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR, PWR_CR_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector
  * @rmtoll CR    PVDE       LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled
  * @rmtoll CR    PVDE       LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_PVDE) == (PWR_CR_PVDE));
}

/**
  * @brief  Enable PVD Filter
  * @rmtoll CSR          FLTEN          LL_PWR_EnablePVDFilter
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVDFilter(void)
{
  SET_BIT(PWR->CSR, PWR_CSR_FLTEN);
}

/**
  * @brief  Disable PVD Filter
  * @rmtoll CSR          FLTEN          LL_PWR_DisablePVDFilter
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVDFilter(void)
{
  CLEAR_BIT(PWR->CSR, PWR_CSR_FLTEN);
}

/**
  * @brief  Check if PVD Filter is enabled
  * @rmtoll CSR          FLTEN          LL_PWR_IsEnabledPVDFilter
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVDFilter(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_FLTEN) == (PWR_CSR_FLTEN));
}

/**
  * @brief  PVD detection power supply selection
  * @rmtoll CSR          FLT_CTRL          LL_PWR_SetPVDFilter
  * @param  PVDFilter This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVD_FILTER_1CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_2CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_4CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_16CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_64CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_128CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_1024CLOCK
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDFilter(uint32_t PVDFilter)
{
  MODIFY_REG(PWR->CSR, PWR_CSR_FLT_CTRL, PVDFilter);
}

/**
  * @brief  Get PVD detection power supply 
  * @rmtoll CSR          FLT_CTRL          LL_PWR_GetPVDFilter
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVD_FILTER_1CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_2CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_4CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_16CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_64CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_128CLOCK
  *         @arg @ref LL_PWR_PVD_FILTER_1024CLOCK
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDFilter(void)
{
  return (uint32_t)(READ_BIT(PWR->CSR, PWR_CSR_FLT_CTRL));
}
/**
  * @}
  */


/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Wake-up Flag
  * @rmtoll CSR   WUF       LL_PWR_IsActiveFlag_WU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_WUF) == (PWR_CSR_WUF));
}

/**
  * @brief  Get Standby Flag
  * @rmtoll CSR   SBF       LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_SBF) == (PWR_CSR_SBF));
}

/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold
  * @rmtoll CSR   PVDO       LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_PVDO) == (PWR_CSR_PVDO));
}

/**
  * @brief  Clear Standby Flag
  * @rmtoll CR   CSBF       LL_PWR_ClearFlag_SB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  SET_BIT(PWR->CR, PWR_CR_CSBF);
}

/**
  * @brief  Clear Wake-up Flags
  * @rmtoll CR   CWUF       LL_PWR_ClearFlag_WU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  SET_BIT(PWR->CR, PWR_CR_CWUF);
}
/**
  * @}
  */
/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F403_LL_PWR_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
