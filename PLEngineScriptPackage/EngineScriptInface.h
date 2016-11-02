/*
 * EngineScriptInface.h
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "PLEngineScriptPKH.h"
#include "EngineScriptI.h"
#ifndef ENGINESCRIPTINFACE_H_
#define ENGINESCRIPTINFACE_H_
	#define PLScript_Table_FunMaxSize 5
#pragma pack(8)
	typedef  struct _SPL_ScriptPlusLibraryHeavy{
		PL_EngineLibraryHeavyInface Inface;
		//void_pl * ptrMem;
		PLConstCharTableHandle hSysConstCharTable;
		HPPLEngine hEngine;
		char_pl pCWD[PL3DSystemFileNameMaxLength];
		intV_pl iCWDSize;
	}PL_ScriptLibraryHeavy;
	typedef struct _SPL_ScriptLibraryFunTable{
		PL_EngineLibraryFunTable Inface;
		fun_pl functionlistEx[PLScript_Table_FunMaxSize - 1];
		//void_pl * ptrMem;
	}PL_ScriptLibraryFunTable;

	typedef struct _SPL_ScriptNativeReg{
		void_pl * callfunction;
		PLScriptHandle hAndle;
	}PL_ScriptNativeReg;
	typedef struct _SPL_ScriptObject{
		intV_pl icbSize;
		//void_pl * ptrMem;
		lua_State * ptrState;
		PLConstCharTableHandle hSysConstCharTable;
		bool_pl   bInitialize;
	}PL_ScriptObject;
#pragma pack()
#endif /* ENGINESCRIPTINFACE_H_ */
