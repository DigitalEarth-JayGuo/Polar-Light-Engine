/*
 * PLEngineScriptAPIInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "PLEngineBaseH.h"
#include "PLEngineSysDataMacro.h"

#ifndef PLENGINESCRIPTAPIINFACE_H_
#define PLENGINESCRIPTAPIINFACE_H_
	#define PLScriptHandle  		void_pl *
	#define PLScriptStateHandle 	void_pl *
	#define PLScriptCodeHandle  	void_pl *
	#define PLScriptUDMHandle       intV_pl
#pragma pack(8)
	typedef  struct _SPL_RegisterScriptLib{
		const_pl UTFSyschar_pl * ptrFuncName;
		intV_pl                  iFNSize;
		void_pl *          ptrFuncCall;
	} PL_RegScriptLib;
	typedef  struct _SPL_ScriptNativeFuncCallParamer{
		const_pl UTFSyschar_pl * ptrFuncName;
		intV_pl iFNSize;
		intV_pl iInputParamerCount;
		intV_pl iResultParamerCount;
	}PL_ScriptNativeFuncParamer;
#pragma pack()
#endif /* PLENGINESCRIPTAPIINFACE_H_ */
