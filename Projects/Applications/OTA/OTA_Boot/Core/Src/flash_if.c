/*
 * flash_if.c
 *
 *  Created on: Aug 12, 2020
 *      Author: Sudaroot
 */


/** @addtogroup STM32wlxx_IAP_Main
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_Init(void)
{
  HAL_FLASH_Unlock();

  /* Clear OPTVERR bit set on virgin samples */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

  /* Unlock the Options Bytes *************************************************/
  //HAL_FLASH_OB_Unlock();
}

/**
  * @brief  Locks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_DeInit(void)
{
  HAL_FLASH_Lock();
  //HAL_FLASH_OB_Lock();
}

/**
  * @brief  This function does an erase of all user flash area
  * @param  StartSector: start of user flash area
  * @retval 0: user flash area successfully erased
  *         1: error occurred
  */
static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }

  return page;
}
uint32_t FLASH_If_Erase(uint32_t StartSector, uint32_t NumberSectors)
{
  uint32_t UserStartSector;
  uint32_t SectorError;
  FLASH_EraseInitTypeDef pEraseInit;

  /* Get the sector where start the user flash area */
  UserStartSector = GetPage(StartSector);

  /* Unlock the Flash to enable the flash control register access *************/
  FLASH_If_Init();
  pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
  pEraseInit.Page = UserStartSector;
  pEraseInit.NbPages = NumberSectors;

  if (HAL_FLASHEx_Erase(&pEraseInit, &SectorError) != HAL_OK)
  {
	  FLASH_If_DeInit();
     /* Error occurred while page erase */
     return (1);
  }

  FLASH_If_DeInit();
  return (0);
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(uint32_t destination, uint32_t* p_source ,uint32_t length)
{
  uint32_t i = 0;

  FLASH_If_Init();
  for (i = 0; (i < length) && (destination <= (USER_FLASH_END_ADDRESS-8)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, destination, *((uint64_t *)(p_source+2*i))) == HAL_OK)
    {
     /* Check the written value */
      if (*(uint64_t*)destination != *(uint64_t *)(p_source+2*i))
      {
    	 FLASH_If_DeInit();
        /* Flash content doesn't match SRAM content */
        return(FLASHIF_WRITINGCTRL_ERROR);
      }
      /* Increment FLASH destination address */
      destination += 8;
    }
    else
    {
      FLASH_If_DeInit();
      /* Error occurred while writing data in Flash memory */
      return (FLASHIF_WRITING_ERROR);
    }
  }

  FLASH_If_DeInit();
  return (FLASHIF_OK);
}

uint32_t FLASH_If_Read(uint32_t FlashAddress, uint32_t* Data ,uint32_t DataLength)
{
  uint32_t i = 0;

  for(i = 0; i < DataLength; i++)
  {
	  Data[i] = *(uint32_t*)FlashAddress;
	  FlashAddress += 4;
  }

  return (FLASHIF_OK);
}
/**
  * @}
  */

