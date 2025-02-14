/**
  ******************************************************************************
  * @file    py32f403_ll_flash.h
  * @author  MCU Application Team
  * @brief   Header file of FLASH LL module.
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
#ifndef PY32F403_LL_FLASH_H
#define PY32F403_LL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f4xx.h"



/** @addtogroup PY32F403_LL_Driver
  * @{
  */

#if defined (FLASH)

/** @defgroup FLASH_LL FLASH
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASH_LL_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_LL_EC_IWDGMODE IWDG Mode
  * @{
  */
#define LL_FLASH_IWDG_MODE_HW          (0x00000000U)                                         /*!< Hardware IWDG selected */
#define LL_FLASH_IWDG_MODE_SW          (FLASH_OPTR_IWDG_SW)                                  /*!< Software IWDG selected */
/**
  * @}
  */


/** @defgroup FLASH_LL_EC_STOP_RST_MODE STOP RST Mode
  * @{
  */
#define LL_FLASH_STOP_RST              (0x00000000U)                                         /*!< Reset generated when entering Stop mode */
#define LL_FLASH_STOP_NORST            (FLASH_OPTR_NRST_STOP)                                /*!< No reset generated when entering Stop mode */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_STANDBY_RST_MODE STANDBY RST Mode
  * @{
  */
#define LL_FLASH_STANDBY_RST           (0x00000000U)                                         /*!< Reset generated when entering Standby mode */
#define LL_FLASH_STANDBY_NORST         (FLASH_OPTR_NRST_STDBY)                               /*!< No reset generated when entering Standby mode */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_RDP RDP Mode
  * @{
  */
#define LL_FLASH_RDP_LEVEL_0         ((uint8_t)0xAAU)
#define LL_FLASH_RDP_LEVEL_1         ((uint8_t)0x55U)

/**
  * @}
  */

/** @defgroup FLASH_LL_EC_WRP Write Protection
  * @{
  */
#define LL_FLASH_WRP_DISABLE          ((uint32_t)0x00000000)         /* Write protection disable */
#define LL_FLASH_WRP_BLOCK_0          ((uint32_t)FLASH_WRPR_WRP_0)   /* Write protection of Block0 */
#define LL_FLASH_WRP_BLOCK_1          ((uint32_t)FLASH_WRPR_WRP_1)   /* Write protection of Block1 */
#define LL_FLASH_WRP_BLOCK_2          ((uint32_t)FLASH_WRPR_WRP_2)   /* Write protection of Block2 */
#define LL_FLASH_WRP_BLOCK_3          ((uint32_t)FLASH_WRPR_WRP_3)   /* Write protection of Block3 */
#define LL_FLASH_WRP_BLOCK_4          ((uint32_t)FLASH_WRPR_WRP_4)   /* Write protection of Block4 */
#define LL_FLASH_WRP_BLOCK_5          ((uint32_t)FLASH_WRPR_WRP_5)   /* Write protection of Block5 */
#define LL_FLASH_WRP_BLOCK_6          ((uint32_t)FLASH_WRPR_WRP_6)   /* Write protection of Block6 */
#define LL_FLASH_WRP_BLOCK_7          ((uint32_t)FLASH_WRPR_WRP_7)   /* Write protection of Block7 */
#define LL_FLASH_WRP_BLOCK_8          ((uint32_t)FLASH_WRPR_WRP_8)   /* Write protection of Block8 */
#define LL_FLASH_WRP_BLOCK_9          ((uint32_t)FLASH_WRPR_WRP_9)   /* Write protection of Block9 */
#define LL_FLASH_WRP_BLOCK_10         ((uint32_t)FLASH_WRPR_WRP_10)  /* Write protection of Block10 */
#define LL_FLASH_WRP_BLOCK_11         ((uint32_t)FLASH_WRPR_WRP_11)  /* Write protection of Block11 */

#define LL_FLASH_WRP_Pages0to127      ((uint32_t)FLASH_WRPR_WRP_0)   /* Write protection from page0    to page127 */
#define LL_FLASH_WRP_Pages128to255    ((uint32_t)FLASH_WRPR_WRP_1)   /* Write protection from page128  to page255 */
#define LL_FLASH_WRP_Pages256to383    ((uint32_t)FLASH_WRPR_WRP_2)   /* Write protection from page256  to page383 */
#define LL_FLASH_WRP_Pages384to511    ((uint32_t)FLASH_WRPR_WRP_3)   /* Write protection from page384  to page511 */
#define LL_FLASH_WRP_Pages512to639    ((uint32_t)FLASH_WRPR_WRP_4)   /* Write protection from page512  to page639 */
#define LL_FLASH_WRP_Pages640to767    ((uint32_t)FLASH_WRPR_WRP_5)   /* Write protection from page640  to page767 */
#define LL_FLASH_WRP_Pages768to895    ((uint32_t)FLASH_WRPR_WRP_6)   /* Write protection from page768  to page895 */
#define LL_FLASH_WRP_Pages896to1023   ((uint32_t)FLASH_WRPR_WRP_7)   /* Write protection from page896  to page1023 */
#define LL_FLASH_WRP_Pages1024to1151  ((uint32_t)FLASH_WRPR_WRP_8)   /* Write protection from page1024 to page1151 */
#define LL_FLASH_WRP_Pages1152to1279  ((uint32_t)FLASH_WRPR_WRP_9)   /* Write protection from page1152 to page1279 */
#define LL_FLASH_WRP_Pages1280to1407  ((uint32_t)FLASH_WRPR_WRP_10)  /* Write protection from page1280 to page1407 */
#define LL_FLASH_WRP_Pages1408to1535  ((uint32_t)FLASH_WRPR_WRP_11)  /* Write protection from page1408 to page1535 */

#define LL_FLASH_WRP_AllPages          ((uint32_t)0x000000FFFU)      /*!< Write protection of all Sectors */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_KEY Key Value
  * @{
  */
#define LL_FLASH_KEY1                  (FLASH_KEY1)
#define LL_FLASH_KEY2                  (FLASH_KEY2)
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_OPTKEY Optkey Value
  * @{
  */
#define LL_FLASH_OPTKEY1               (FLASH_OPTKEY1)
#define LL_FLASH_OPTKEY2               (FLASH_OPTKEY2)
/**
  * @}
  */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Macros FLASH Exported Macros
  * @{
  */

/** @defgroup FLASH_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_FLASH_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_FLASH_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Functions FLASH Exported Functions
  * @{
  */

/** @defgroup FLASH_LL_EF_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief  Indicate the status of End of operation flag.
  * @rmtoll SR          EOP              LL_FLASH_IsActiveFlag_EOP
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_EOP(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_EOP) == (FLASH_SR_EOP));
}

/**
  * @brief  Indicate the status of WRPERR flag.
  * @rmtoll SR          WPRERR           LL_FLASH_IsActiveFlag_WRPERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WRPERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_WRPERR) == (FLASH_SR_WRPERR));
}

/**
  * @brief  Indicate the status of OPTVERR flag.
  * @rmtoll SR          OPTVERR          LL_FLASH_IsActiveFlag_OPTVERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OPTVERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_OPTVERR) == (FLASH_SR_OPTVERR));
}

/**
  * @brief  Indicate the status of BUSY flag.
  * @rmtoll SR          BSY              LL_FLASH_IsActiveFlag_BUSY
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BUSY(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_BSY) == (FLASH_SR_BSY));
}

/**
  * @brief  Clear End of operation flag.
  * @rmtoll SR          EOP              LL_FLASH_ClearFlag_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_EOP(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_EOP);
}

/**
  * @brief  Clear WRPERR flag.
  * @rmtoll SR          WRPERR           LL_FLASH_ClearFlag_WRPERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_WRPERR(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_WRPERR);
}

/**
  * @brief  Clear OPTVERR flag.
  * @rmtoll SR          OPTVERR          LL_FLASH_ClearFlag_OPTVERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OPTVERR(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_OPTVERR);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_ERASE_Management Erase Management
  * @{
  */

/**
  * @brief  Enable Page Program
  * @rmtoll CR          PG               LL_FLASH_EnablePageProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePageProgram(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PG);
}

/**
  * @brief  Enable Mass Erase
  * @rmtoll CR          MER              LL_FLASH_EnableMassErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableMassErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_MER);
}

/**
  * @brief  Enable Page Erase
  * @rmtoll CR          PER              LL_FLASH_EnablePageErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePageErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PER);
}

/**
  * @brief  Enable Sector Erase
  * @rmtoll CR          SER              LL_FLASH_EnableSectorErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableSectorErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_SER);
}

/**
  * @brief  Enable Block Erase
  * @rmtoll CR          BER              LL_FLASH_EnableBlockErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableBlockErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_BER);
}

/**
  * @brief  Disable Program
  * @rmtoll CR          PG               LL_FLASH_DisablePageProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePageProgram(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PG);
}

/**
  * @brief  Disable Mass Erase
  * @rmtoll CR          MER              LL_FLASH_DisableMassErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableMassErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_MER);
}

/**
  * @brief  Disable Page Erase
  * @rmtoll CR          PER              LL_FLASH_DisablePageErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePageErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PER);
}

/**
  * @brief  Disable Sector Erase
  * @rmtoll CR          SER              LL_FLASH_DisableSectorErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableSectorErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_SER);
}

/**
  * @brief  Disable Block Erase
  * @rmtoll CR          BER              LL_FLASH_DisableBlockErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableBlockErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_BER);
}

/**
  * @brief  Check if Page Program is enabled
  * @rmtoll CR          PG               LL_FLASH_IsEnabledPageProgram
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageProgram(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_PG) == (FLASH_CR_PG)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Mass erase is enabled
  * @rmtoll CR          MER              LL_FLASH_IsEnabledMassErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledMassErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_MER) == (FLASH_CR_MER)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Page erase is enabled
  * @rmtoll CR          PER              LL_FLASH_IsEnabledPageErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_PER) == (FLASH_CR_PER)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Sector Erase is enabled
  * @rmtoll CR          SER              LL_FLASH_IsEnabledSectorErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledSectorErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_SER) == (FLASH_CR_SER)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Block Erase is enabled
  * @rmtoll CR          BER              LL_FLASH_IsEnabledBlockErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledBlockErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_BER) == (FLASH_CR_BER)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Erase Address
  * @rmtoll LL_FLASH_SetEraseAddress
  * @param  FLASHx FLASH Instance
  * @param  address Erase address
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetEraseAddress(FLASH_TypeDef *FLASHx,uint32_t address)
{
  *(__IO uint32_t *)(address) = 0xFFFFFFFF;
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_Lock_Management Lock Management
  * @{
  */

/**
  * @brief Unlock the Flash
  * @rmtoll KEYR        KEYR             LL_FLASH_Unlock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Unlock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->KEYR, LL_FLASH_KEY1);
  SET_BIT(FLASHx->KEYR, LL_FLASH_KEY2);
}

/**
  * @brief  Unlock the Option
  * @rmtoll OPTKEYR     OPTKEYR          LL_FLASH_OBUnlock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OBUnlock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->OPTKEYR, LL_FLASH_OPTKEY1);
  SET_BIT(FLASHx->OPTKEYR, LL_FLASH_OPTKEY2);
}


/**
  * @brief  Lock the Flash
  * @rmtoll CR          LOCK             LL_FLASH_Lock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Lock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_LOCK);
}

/**
  * @brief  Lock the Option
  * @rmtoll CR          OPTLOCK          LL_FLASH_OBLock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OBLock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OPTLOCK);
}

/**
  * @brief  Check if Flash is locked
  * @rmtoll CR          LOCK             LL_FLASH_IsLocked
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsLocked(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_LOCK) == (FLASH_CR_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Option is locked
  * @rmtoll CR          OPTLOCK          LL_FLASH_IsOBLocked
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsOBLocked(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_OPTLOCK) == (FLASH_CR_OPTLOCK)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_LAUNCH_Management Launch Management
  * @{
  */

/**
  * @brief  Force the Option byte loading
  * @rmtoll CR          OBL_LAUNCH       LL_FLASH_Launch
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Launch(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OBL_LAUNCH);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief  Enable Error interrupts.
  * @rmtoll CR          ERRIR            LL_FLASH_EnableIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableIT_ERR(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_ERRIE);
}

/**
  * @brief  Enable End of operation interrupts.
  * @rmtoll CR          EOPIE            LL_FLASH_EnableIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableIT_EOP(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_EOPIE);
}

/**
  * @brief  Disable Error interrupts.
  * @rmtoll CR          ERRIE            LL_FLASH_DisableIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableIT_ERR(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_ERRIE);
}

/**
  * @brief  Disable End of operation interrupts.
  * @rmtoll CR          EOPIE            LL_FLASH_DisableIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableIT_EOP(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_EOPIE);
}

/**
  * @brief  Check if Error interrupts are enabled or disabled.
  * @rmtoll CR          ERRIE            LL_FLASH_IsEnabledIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_ERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASH->CR, FLASH_CR_ERRIE) == (FLASH_CR_ERRIE));
}

/**
  * @brief  Check if End of operation interrupts are enabled or disabled.
  * @rmtoll CR          EOPIE            LL_FLASH_IsEnabledIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_EOP(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASH->CR, FLASH_CR_EOPIE) == (FLASH_CR_EOPIE));
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_PROGRAM_Management Program Management
  * @{
  */

/**
  * @brief  Enable Page Program Start
  * @rmtoll CR          PGSTRT           LL_FLASH_EnablePageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_EnablePageProgramStart(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PGSTRT);
}

/**
  * @brief  Enable Option Program Start
  * @rmtoll CR          OPTSTRT          LL_FLASH_EnableOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_EnableOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OPTSTRT);
}

/**
  * @brief Disable Page Program start
  * @rmtoll CR          PGSTRT           LL_FLASH_DisablePageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_DisablePageProgramStart(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PGSTRT);
}

/**
  * @brief  Disable Option Program start
  * @rmtoll CR          OPTSTRT          LL_FLASH_DisableOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_DisableOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_OPTSTRT);
}

/**
  * @brief  Check if Page Program start is enabled
  * @rmtoll CR          PGSTRT              LL_FLASH_IsEnabledPageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageProgramStart(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_PGSTRT) == (FLASH_CR_PGSTRT));
}

/**
  * @brief  Check if Option program Start is enabled
  * @rmtoll CR          OPTSTRT         LL_FLASH_IsEnabledOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_OPTSTRT) == (FLASH_CR_OPTSTRT));
}

/**
  * @brief  Program the page
  * @rmtoll CR          PGSTRT          LL_FLASH_PageProgram
  * @param  FLASHx FLASH Instance
  * @param  Address   Program Address
  * @param  DataAddress Data Address
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_PageProgram(FLASH_TypeDef *FLASHx,uint32_t Address, uint32_t * DataAddress)
{
  uint8_t index=0;
  uint32_t dest = Address;
  uint32_t * src = DataAddress;
  uint32_t primask_bit;
  /* Enter critical section */
  primask_bit = __get_PRIMASK();
  __disable_irq();
  /* 64 words*/
  while(index<64U)
  {
    *(uint32_t *)dest = *src;
    src += 1U;
    dest += 4U;
    index++;
    if(index==63)
    {
      LL_FLASH_EnablePageProgramStart(FLASHx);
    }
  }

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_WRP_Management WRP Management
  * @{
  */

/**
  * @brief  Set WRP Address
  * @rmtoll WRPR        WRP             LL_FLASH_SetWRPRAddress
  * @param  FLASHx FLASH Instance
  * @param  Address This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_WRP_DISABLE
  *         @arg @ref LL_FLASH_WRP_BLOCK_0
  *         @arg @ref LL_FLASH_WRP_BLOCK_1
  *         @arg @ref LL_FLASH_WRP_BLOCK_2
  *         @arg @ref LL_FLASH_WRP_BLOCK_3
  *         @arg @ref LL_FLASH_WRP_BLOCK_4
  *         @arg @ref LL_FLASH_WRP_BLOCK_5
  *         @arg @ref LL_FLASH_WRP_BLOCK_6
  *         @arg @ref LL_FLASH_WRP_BLOCK_7
  *         @arg @ref LL_FLASH_WRP_BLOCK_8
  *         @arg @ref LL_FLASH_WRP_BLOCK_9
  *         @arg @ref LL_FLASH_WRP_BLOCK_10
  *         @arg @ref LL_FLASH_WRP_BLOCK_11
  *         @arg @ref LL_FLASH_WRP_Pages0to127
  *         @arg @ref LL_FLASH_WRP_Pages128to255
  *         @arg @ref LL_FLASH_WRP_Pages256to383
  *         @arg @ref LL_FLASH_WRP_Pages384to511
  *         @arg @ref LL_FLASH_WRP_Pages512to639
  *         @arg @ref LL_FLASH_WRP_Pages640to767
  *         @arg @ref LL_FLASH_WRP_Pages768to895
  *         @arg @ref LL_FLASH_WRP_Pages896to1023
  *         @arg @ref LL_FLASH_WRP_Pages1024to1151
  *         @arg @ref LL_FLASH_WRP_Pages1152to1279
  *         @arg @ref LL_FLASH_WRP_Pages1280to1407
  *         @arg @ref LL_FLASH_WRP_Pages1408to1535
  *         @arg @ref LL_FLASH_WRP_AllPages
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetWRPAddress(FLASH_TypeDef *FLASHx,uint32_t Address)
{
  MODIFY_REG(FLASHx->WRPR, FLASH_WRPR_WRP , ((~(Address)) & FLASH_WRPR_WRP));
}

/**
  * @brief  Get WRP Address
  * @rmtoll WRPR        WRP             LL_FLASH_GetWRPAddress
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_FLASH_WRP_DISABLE
  *         @arg @ref LL_FLASH_WRP_BLOCK_0
  *         @arg @ref LL_FLASH_WRP_BLOCK_1
  *         @arg @ref LL_FLASH_WRP_BLOCK_2
  *         @arg @ref LL_FLASH_WRP_BLOCK_3
  *         @arg @ref LL_FLASH_WRP_BLOCK_4
  *         @arg @ref LL_FLASH_WRP_BLOCK_5
  *         @arg @ref LL_FLASH_WRP_BLOCK_6
  *         @arg @ref LL_FLASH_WRP_BLOCK_7
  *         @arg @ref LL_FLASH_WRP_BLOCK_8
  *         @arg @ref LL_FLASH_WRP_BLOCK_9
  *         @arg @ref LL_FLASH_WRP_BLOCK_10
  *         @arg @ref LL_FLASH_WRP_BLOCK_11
  *         @arg @ref LL_FLASH_WRP_Pages0to127
  *         @arg @ref LL_FLASH_WRP_Pages128to255
  *         @arg @ref LL_FLASH_WRP_Pages256to383
  *         @arg @ref LL_FLASH_WRP_Pages384to511
  *         @arg @ref LL_FLASH_WRP_Pages512to639
  *         @arg @ref LL_FLASH_WRP_Pages640to767
  *         @arg @ref LL_FLASH_WRP_Pages768to895
  *         @arg @ref LL_FLASH_WRP_Pages896to1023
  *         @arg @ref LL_FLASH_WRP_Pages1024to1151
  *         @arg @ref LL_FLASH_WRP_Pages1152to1279
  *         @arg @ref LL_FLASH_WRP_Pages1280to1407
  *         @arg @ref LL_FLASH_WRP_Pages1408to1535
  *         @arg @ref LL_FLASH_WRP_AllPages
  */
__STATIC_INLINE uint32_t LL_FLASH_GetWRPAddress(FLASH_TypeDef *FLASHx)
{
  return ((~(READ_BIT(FLASHx->WRPR, FLASH_WRPR_WRP))) & FLASH_WRPR_WRP);
}
/**
  * @}
  */

/** @defgroup FLASH_LL_EF_OPTR_Management OPTR Management
  * @{
  */
/**
  * @brief  Set Optr
  * @rmtoll OPTR            NRST_STDBY           LL_FLASH_SetOPTR
  * @rmtoll OPTR            NRST_STOP            LL_FLASH_SetOPTR
  * @rmtoll OPTR            IWDG_SW              LL_FLASH_SetOPTR
  * @rmtoll OPTR            RDP                  LL_FLASH_SetOPTR
  * @param  FLASHx FLASH Instance
  * @param  NRSTStandby This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_STOP_RST
  *         @arg @ref LL_FLASH_STOP_NORST
  * @param  NRSTStop This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_STANDBY_RST
  *         @arg @ref LL_FLASH_STANDBY_NORST
  * @param  IWDGMode This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_MODE_HW
  *         @arg @ref LL_FLASH_IWDG_MODE_SW
  * @param  RDPLevel This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_RDP_LEVEL_0
  *         @arg @ref LL_FLASH_RDP_LEVEL_1
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetOPTR(FLASH_TypeDef *FLASHx,uint32_t NRSTStandby,uint32_t NRSTStop,uint32_t IWDGMode,uint32_t RDPLevel)
{
  MODIFY_REG(FLASHx->OPTR, (FLASH_OPTR_NRST_STOP | FLASH_OPTR_NRST_STDBY | FLASH_OPTR_IWDG_SW | FLASH_OPTR_RDP), (NRSTStandby | NRSTStop | IWDGMode | RDPLevel));
}

/**
  * @brief Get IWDG Mode
  * @rmtoll OPTR        IWDG_SW          LL_FLASH_GetIWDGMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_MODE_HW
  *         @arg @ref LL_FLASH_IWDG_MODE_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIWDGMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_IWDG_SW);
}

/**
  * @brief Get Stop Reset
  * @rmtoll OPTR        NRST_STOP          LL_FLASH_GetSTOPReset
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_STOP_RST
  *         @arg @ref LL_FLASH_STOP_NORST
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSTOPReset(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_NRST_STOP);
}

/**
  * @brief Get Standby Reset
  * @rmtoll OPTR        NRST_STDBY          LL_FLASH_GetSTANDBYReset
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_STANDBY_RST
  *         @arg @ref LL_FLASH_STANDBY_NORST
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSTANDBYReset(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_NRST_STDBY);
}

/**
  * @brief Get RDP Level
  * @rmtoll OPTR        RDP          LL_FLASH_GetRDP
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_RDP_LEVEL_0
  *         @arg @ref LL_FLASH_RDP_LEVEL_1
  */
__STATIC_INLINE uint32_t LL_FLASH_GetRDP(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_RDP);
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
#endif /* defined (FLASH) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F403_LL_FLASH_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
