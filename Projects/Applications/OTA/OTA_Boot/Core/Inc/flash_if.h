/*
 * flash_if.h
 *
 *  Created on: Aug 12, 2020
 *      Author: Sudaroot
 */

#ifndef INC_FLASH_IF_H_
#define INC_FLASH_IF_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Error code */
enum
{
  FLASHIF_OK = 0,
  FLASHIF_ERASEKO,
  FLASHIF_WRITINGCTRL_ERROR,
  FLASHIF_WRITING_ERROR
};

/* End of the Flash address */
#define USER_FLASH_END_ADDRESS        0x08040000

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FLASH_If_Init(void);
void FLASH_If_DeInit(void);
uint32_t FLASH_If_Erase(uint32_t StartSector, uint32_t NumberSectors);
uint32_t FLASH_If_Write(uint32_t destination, uint32_t* p_source, uint32_t DataLength);
uint32_t FLASH_If_Read(uint32_t destination, uint32_t* p_source ,uint32_t DataLength);

#endif /* INC_FLASH_IF_H_ */
