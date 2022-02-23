/*
 * system_ota.c
 *
 *  Created on: 2021年11月26日
 *      Author: DELL
 */

#include <stdio.h>
#include <string.h>
#include "system_ota.h"

extern UART_HandleTypeDef huart1;

#define	UART_BUF_SIZE		256
uint8_t uart_buf[UART_BUF_SIZE] = {0};


/* 扇区数据需要一个一个擦写。若同时两个扇区擦写容易出现数据同时丢失  */
uint32_t System_ParamUpdate(uint32_t addr, SystemParamTypeDef *pData)
{
	if(addr != SYSTEMPARAM_ADDR )//&& address != SYSTEMPARAM_BACKUPADDR)
		return 1;

	if(FLASH_If_Erase(addr, 1) != 0)
		return 2;

	if(FLASH_If_Write(addr, (uint32_t*)pData, sizeof(SystemParamTypeDef) / 4) != HAL_OK)
		return 3;

	return 0;
}


void System_ParamReadCheckUpdate(SystemParamTypeDef *pData)
{
	FLASH_If_Read(SYSTEMPARAM_ADDR, (uint32_t*)pData, sizeof(SystemParamTypeDef) / 4);
	  printf("\r\n=================== Main Menu ============================\r\n\n");
	  printf("  IAP:Download user application to the internal Flash ----- 0\r\n\n");
	  printf("  Current System Device id: 0x%08lX\r\n", pData->Device_id);
	  printf("  Current System Hardware Version: 0x%08lX\r\n", pData->Hardware_Version);
	  printf("  Current System APP Version: 0x%08lX\r\n", pData->App_Version);
	  printf("  Current System APP Status: 0x%08lX\r\n", pData->App_Status);
	/* APP1的软件版本号与固件内部软件版本号不一致，更新版本号并写入Flash */
	if(pData->App_Version != APP_VERSION)
	{
		printf("Update APP0 Software Version : 0x%08X\r\n", APP_VERSION);
		pData->App_Version = APP_VERSION;

		if(pData->App_Status != APP_NORMAL)
		{
			printf("Update APP0 Status, APP_NORMAL\r\n");
			pData->App_Status = APP_NORMAL;
		}
		System_ParamUpdate(SYSTEMPARAM_ADDR, pData);
		FLASH_If_Read(SYSTEMPARAM_ADDR, (uint32_t*)pData, sizeof(SystemParamTypeDef) / 4);
		  printf("\r\n=================== HHHHHHHH ============================\r\n\n");
		  printf("  IAP:Download user application to the internal Flash ----- 0\r\n\n");
		  printf("  Current System Device id: 0x%08lX\r\n", pData->Device_id);
		  printf("  Current System Hardware Version: 0x%08lX\r\n", pData->Hardware_Version);
		  printf("  Current System APP Version: 0x%08lX\r\n", pData->App_Version);
		  printf("  Current System APP Status: 0x%08lX\r\n", pData->App_Status);
	}
}

void SystemParam_OTA(SystemParamTypeDef *pData)
{
	pData->App_Version = UPDATE_VERSION;
	System_ParamUpdate(SYSTEMPARAM_ADDR, pData);
	printf("device reboot\r\n");
	HAL_NVIC_SystemReset();
}
