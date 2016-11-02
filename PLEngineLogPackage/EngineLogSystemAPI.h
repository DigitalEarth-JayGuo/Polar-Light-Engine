/*
 * EngineLogSystemAPI.h
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "EngineLogSystemInface.h"
#include "PLEngineLogPKH.h"
#ifndef ENGINELOGSYSTEMAPI_H_
#define ENGINELOGSYSTEMAPI_H_
extern PLLibraryHandle g_hLibraryHandle_Log;
	_CallStack_default_	PLLogSystemHandle 		Eg_CreateLogSystem();
	_CallStack_default_ void_pl 				Eg_SetLogSystemHeaderName(PLLogSystemHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_	void_pl			  		Eg_DestroyLogSystem(PLLogSystemHandle hAndle);
	//ePL_LogMsgType
#endif /* ENGINELOGSYSTEMAPI_H_ */
