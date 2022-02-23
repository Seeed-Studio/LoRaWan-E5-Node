/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define  SYSTEMPARAM_ADDR                   0x08004000
#define	APP_SECTOR_NUM			       16
#define USER_FLASH_SIZE               ((uint32_t)0x00010000)
#define APP1_ADDR               0x08010000
#define APP2_ADDR               0x08020000
/* updata  version */
#define	UPDATE_VERSION		0xFFFFFFFEU
#define	TEST_VERSION		0xDDDDDDDDU
typedef  void (*pFunction)(void);

uint32_t APP_ADDR[2];
typedef	__PACKED_STRUCT{
	uint32_t Device_id;
	uint32_t Hardware_Version;			// 硬件版本信息
	uint32_t App_Version;		// APP软件版本(准备升级时app将其置为0xFFFFFFFFF,升级后设置boot将其置为0xDDDDDDDD,再跳到app设置为对应版本号)
	uint32_t App_Status;		// APP的状态（0：app0 1：app1）
}SystemParamTypeDef;

extern SystemParamTypeDef SystemParam;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
