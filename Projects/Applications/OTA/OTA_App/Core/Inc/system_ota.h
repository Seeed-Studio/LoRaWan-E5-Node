/*
 * system_ota.h
 *
 *  Created on: 2021年11月26日
 *      Author: DELL
 */

#ifndef INC_SYSTEM_OTA_H_
#define INC_SYSTEM_OTA_H_

#include "main.h"
#include "stm32wlxx_hal.h"
/* Define APP software version */
#define	APP_VERSION		0x00000028U
#define	UPDATE_VERSION		0xFFFFFFFEU

#define  SYSTEMPARAM_ADDR                   0x08004000
typedef  void (*pFunction)(void);

typedef enum {
	APP_NORMAL = 0,		// APP能正常稳定运�?
	APP_UPDATED,		// APP刚更新完成，等待测试启动
	APP_ERROR,			// APP错误，不能正常工�?
}App_Status_t;

typedef	__PACKED_STRUCT{
	uint32_t Device_id;
	uint32_t Hardware_Version;			// 硬件版本信息
	uint32_t App_Version;		// APP软件版本(准备升级时app将其置为0xFFFFFFFFF,升级后设置boot将其置为0xDDDDDDDD,再跳到app设置为对应版本号)
	uint32_t App_Status;		// APP的状态（0：app0 1：app1）
}SystemParamTypeDef;

uint32_t System_ParamUpdate(uint32_t addr, SystemParamTypeDef *pData);
void System_ParamReadCheckUpdate(SystemParamTypeDef *pData);
void SystemParam_OTA(SystemParamTypeDef *pData);
#endif /* INC_SYSTEM_OTA_H_ */
