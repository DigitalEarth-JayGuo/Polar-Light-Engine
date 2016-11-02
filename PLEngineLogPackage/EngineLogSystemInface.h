/*
 * PLEngineLogInface.h
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "PLEngineLogPKH.h"
#include "EngineLogSystemI.h"
#ifndef PLENGINELOGINFACE_H_
#define PLENGINELOGINFACE_H_
#define PLSys_Const_LogSys_LogItemMaxCount		5

	typedef enum _ePL_SysLogSystemState{
		PLSysLog_Const_LogSys_UnInitialize = 0	,
		PLSysLog_Const_LogSys_Initialize		,
	}PL_SysLogSystemState;


#pragma pack(4)
	typedef  struct Aligned(8) _SPL_LogSystemPlusLibraryHeavy{
		PL_EngineLibraryHeavyInface Inface;
		PLConstCharTableHandle hSysConstCharTable;
		HPPLEngine hEngine;
		char_pl pCWD[PL3DSystemFileNameMaxLength];
		intV_pl iCWDSize;
		char_pl pLogCWD[PL3DSystemFileNameMaxLength];
		intV_pl iLogCWDSize;
	}__Aligned(8) PL_LogSystemLibraryHeavy;
	typedef  struct Aligned(8) _SPL_LogSystemLibraryFunTable{
		PL_EngineLibraryFunTable Inface;
		fun_pl functionlistEx[PLLog_Table_FunMaxSize - 1];
	}__Aligned(8) PL_LogSystemLibraryFunTable;

	typedef struct Aligned(8) _SPL_LogSystem{
		PL_SysLogSystemState eState;
		char_pl pHeaderName[PLLog_ConstID_HeaderNameMaxSize];
		intV_pl  iHNSize;
		PLDeviceHandle hDefaultFile;
		PLDeviceHandle hFileList[PLSys_Const_LogSys_LogItemMaxCount];
	}__Aligned(8) PL_LogSystem;


#pragma pack()
#endif /* PLENGINELOGINFACE_H_ */
