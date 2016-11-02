/*
 * EngineScriptAPI.h
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "PLEngineScriptPKH.h"
#include "EngineScriptInface.h"
#include "EngineScriptDataDispose.h"
#ifndef ENGINESCRIPTAPI_H_
#define ENGINESCRIPTAPI_H_
	extern PLLibraryHandle        g_hLibraryHandle_Script;
	typedef intV_pl (* __PL_ScriptFunc_CallBack)(PLScriptHandle);
	int_pl __Native_ScriptCallBack(PLScriptStateHandle hState);
	_CallStack_default_ PLLibraryHandle     Eg_GetLibraryHandle_global();
	_CallStack_default_ PLScriptHandle  	Eg_OpenScript();
	_CallStack_default_ HPL_Result      	Eg_InitializeScriptLib(PLScriptHandle hAndle);
	_CallStack_default_ PLScriptHandle      Eg_ConverScriptHandleToScriptStateHandle(PLScriptStateHandle hAndle);
	_CallStack_default_ HPL_Result      	Eg_RegisterScriptFunc(PLScriptHandle hAndle,const_pl char_pl * ptrScript,intV_pl iScriptSize,const_pl char_pl * ptrPackage,intV_pl iPackageSize,void_pl * ptrFunc);
	_CallStack_default_ intV_pl 	      	Eg_RegisterScriptPackageFunc(PLScriptHandle hAndle,const_pl char_pl * ptrPackageName,intV_pl iPackageSize,PL_RegScriptLib * ptrScriptLib,intV_pl iCount);
	_CallStack_default_ HPL_Result          Eg_CreateBuildScript(PLScriptHandle hAndle,const_pl char_pl * ptrScript,intV_pl iScriptSize,const_pl char_pl * pRegisterKey);
	_CallStack_default_ HPL_Result          Eg_ExecuteBuildScript(PLScriptHandle hAndle,const_pl char_pl * pRegisterKey);
	_CallStack_default_ HPL_Result          Eg_ExecuteBuildNativeFuncScript(PLScriptHandle hAndle,PL_ScriptNativeFuncParamer * ptrSNFP,const_pl char_pl * pRegisterKey);
	_CallStack_default_ void_pl             Eg_ReleaseBuildScript(PLScriptHandle hAndle,const_pl char_pl * pRegisterKey);

	//_CallStack_default_
	//use Script's UserData Memory
	_CallStack_default_ PLScriptUDMHandle   Eg_AllocCScriptSpaceMemory(PLScriptHandle hAndle,intV_pl iSize);
	_CallStack_default_ void_pl *           Eg_GetCScriptSpaceMemoryPointer(PLScriptHandle hAndle,PLScriptUDMHandle hMem);
	_CallStack_default_ void_pl             Eg_FreeCScriptSpaceMemory(PLScriptHandle hAndle,PLScriptUDMHandle hMem);

	_CallStack_default_ HPL_Result			Eg_ExecuteStringScript(PLScriptHandle hAndle,const_pl char_pl * ptrScript,intV_pl iScriptSize);
	_CallStack_default_ void_pl         	Eg_CloseScript(PLScriptHandle hAndle);
//	_CallStack_default_ 					Eg_PushParamer();
#endif /* ENGINESCRIPTAPI_H_ */
