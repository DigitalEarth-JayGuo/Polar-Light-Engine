/*
 * PLEngineSysThreadPoolInface.h
 *
 *  Created on: 2009-11-10
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINESYSTHREADPOOLINFACE_H_
#define PLENGINESYSTHREADPOOLINFACE_H_
	#define HThreadPool void_pl *
	#define PLSysTP_Const_TaskerMaxCount 1024
//	PLThreadHandle g_hAndle;
	typedef enum _ePL_SysThreadPoolTaskerState{
		PLSysTP_Const_TaskerState_UnInitialize = 0,
		PLSysTP_Const_TaskerState_Stop		      ,
		PLSysTP_Const_TaskerState_Run
	}ePL_SysThreadPoolTaskerState;
	typedef enum _ePL_SysThreadPoolThreadItemState{
		PLSysTP_Const_ThreadItem_Ide = 0	,
		PLSysTP_Const_ThreadItem_Busyness 	,
		PLSysTP_Const_ThreadItem_Exit		,
		PLSysTP_Const_ThreadItem_ExceptionalExit
	}ePL_SysTPThreadItemState;
#pragma pack(8)
	typedef struct Aligned(8) _SPLThreadPoolParamer{
		intV_pl iMaxCount;
		intV_pl iTaskerMaxCount;
	}__Aligned(8) PLThreadPoolParamer;
#pragma pack()
#endif /* PLENGINESYSTHREADPOOLINFACE_H_ */
