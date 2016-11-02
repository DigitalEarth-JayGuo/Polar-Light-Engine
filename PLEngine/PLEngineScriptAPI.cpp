/*
 * PLEngineScriptAPI.cpp
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "header/PLEngineScriptAPI.h"
	_PLE_lib_VariableN __Script_OpenScript__PL__ 					PLSysAPI_Script_Open  			 = NULL_PL;
	_PLE_lib_VariableN __Script_InitializeScript__PL__				PLSysAPI_Script_InitializeScript = NULL_PL;
	_PLE_lib_VariableN __Script_CloseScript__PL__ 					PLSysAPI_Script_Close 			 = NULL_PL;
	_PLE_lib_VariableN __Script_GetLibraryHandleScript_global__PL__	PLSysAPI_Script_GetLibraryHandle = NULL_PL;

	_PLE_lib_VariableN __Script_PushInt32__PL__		PLSysAPI_Script_PushInt32 	= NULL_PL;
	_PLE_lib_VariableN __Script_PopInt32__PL__		PLSysAPI_Script_PopInt32  	= NULL_PL;
	_PLE_lib_VariableN __Script_PushIntV__PL__		PLSysAPI_Script_PushIntV  	= NULL_PL;
	_PLE_lib_VariableN __Script_PopIntV__PL__		PLSysAPI_Script_PopIntV   	= NULL_PL;
	_PLE_lib_VariableN __Script_PushString__PL__	PLSysAPI_Script_PushString	= NULL_PL;
	_PLE_lib_VariableN __Script_PopString__PL__		PLSysAPI_Script_PopString 	= NULL_PL;
	_PLE_lib_VariableN __Script_PushBool__PL__		PLSysAPI_Script_PushBool  	= NULL_PL;
	_PLE_lib_VariableN __Script_PopBool__PL__		PLSysAPI_Script_PopBool   	= NULL_PL;
	_PLE_lib_VariableN __Script_PushDouble__PL__  	PLSysAPI_Script_PushDouble  = NULL_PL;
	_PLE_lib_VariableN __Script_PopDouble__PL__  	PLSysAPI_Script_PopDouble	= NULL_PL;
	_PLE_lib_VariableN __Script_PushFloat__PL__  	PLSysAPI_Script_PushFloat	= NULL_PL;
	_PLE_lib_VariableN __Script_PopFloat__PL__    	PLSysAPI_Script_PopFloat	= NULL_PL;
	_PLE_lib_VariableN __Script_PushPointer__PL__	PLSysAPI_Script_PushPointer = NULL_PL;
	_PLE_lib_VariableN __Script_PopPointer__PL__	PLSysAPI_Script_PopPointer  = NULL_PL;
	_PLE_lib_VariableN __Script_Pop__PL__			PLSysAPI_Script_Pop			= NULL_PL;


	_PLE_lib_VariableN __Script_CopyStackData__PL__				PLSysAPI_Script_CopyStackData		= NULL_PL;
	_PLE_lib_VariableN __Script_MoveStackData__PL__				PLSysAPI_Script_MoveStackData		= NULL_PL;
	_PLE_lib_VariableN __Script_RemoveStackData__PL__			PLSysAPI_Script_RemoveStackData		= NULL_PL;
	_PLE_lib_VariableN __Script_ReplaceStackData__PL__			PLSysAPI_Script_ReplaceStackData	= NULL_PL;
	_PLE_lib_VariableN __Script_PushGTable__PL__				PLSysAPI_Script_PushGTable			= NULL_PL;
	_PLE_lib_VariableN __Script_PushCTable__PL__				PLSysAPI_Script_PushCTable			= NULL_PL;
	_PLE_lib_VariableN __Script_PushTable__PL__					PLSysAPI_Script_PushTable			= NULL_PL;
	_PLE_lib_VariableN __Script_PushNewTable__PL__				PLSysAPI_Script_PushNewTable		= NULL_PL;

	_PLE_lib_VariableN __Script_GetStackElementCount__PL__		PLSysAPI_Script_GetStackElementCount= NULL_PL;
	_PLE_lib_VariableN __Script_SetGlobalValue__PL__			PLSysAPI_Script_SetGlobalValue		= NULL_PL;
	_PLE_lib_VariableN __Script_GetGlobalValue__PL__			PLSysAPI_Script_GetGlobalValue		= NULL_PL;
	_PLE_lib_VariableN __Script_SetGlobalValueI__PL__			PLSysAPI_Script_SetGlobalValueI		= NULL_PL;
	_PLE_lib_VariableN __Script_GetGlobalValueI__PL__ 			PLSysAPI_Script_GetGlobalValueI		= NULL_PL;
	_PLE_lib_VariableN __Script_GetGlobalSize__PL__ 			PLSysAPI_Script_GetGlobalSize		= NULL_PL;
	_PLE_lib_VariableN __Script_SetRegisterValue__PL__			PLSysAPI_Script_SetRegisterValue	= NULL_PL;
	_PLE_lib_VariableN __Script_GetRegisterValue__PL__			PLSysAPI_Script_GetRegisterValue	= NULL_PL;
	_PLE_lib_VariableN __Script_SetRegisterValueI__PL__			PLSysAPI_Script_SetRegisterValueI	= NULL_PL;
	_PLE_lib_VariableN __Script_GetRegisterValueI__PL__			PLSysAPI_Script_GetRegisterValueI	= NULL_PL;
	_PLE_lib_VariableN __Script_GetRegisterSize__PL__			PLSysAPI_Script_GetRegisterSize		= NULL_PL;
	_PLE_lib_VariableN __Script_SetTableValue__PL__				PLSysAPI_Script_SetTableValue		= NULL_PL;
	_PLE_lib_VariableN __Script_GetTableValue__PL__				PLSysAPI_Script_GetTableValue		= NULL_PL;
	_PLE_lib_VariableN __Script_SetTableValueI__PL__			PLSysAPI_Script_SetTableValueI		= NULL_PL;
	_PLE_lib_VariableN __Script_GetTableValueI__PL__			PLSysAPI_Script_GetTableValueI		= NULL_PL;
	_PLE_lib_VariableN __Script_GetTableSize__PL__				PLSysAPI_Script_GetTableSize		= NULL_PL;
	_PLE_lib_VariableN __Script_isGlobalValueNull__PL__			PLSysAPI_Script_isGlobalValueNull	= NULL_PL;
	_PLE_lib_VariableN __Script_isRegisterValueNull__PL__		PLSysAPI_Script_isRegisterValueNull	= NULL_PL;
	_PLE_lib_VariableN __Script_isTableValueNull__PL__			PLSysAPI_Script_isTableValueNull	= NULL_PL;

	_PLE_lib_VariableN __Script_AllocCScriptSpaceMemory__PL__    		PLSysAPI_Script_AllocCScriptSpaceMemory    = NULL_PL;
	_PLE_lib_VariableN __Script_GetCScriptSpaceMemoryPointer__PL__ 		PLSysAPI_Script_GetCScriptSpaceMemoryPtr   = NULL_PL;
	_PLE_lib_VariableN __Script_FreeCScriptSpaceMemory__PL__ 			PLSysAPI_Script_FreeCScriptSpaceMemory     = NULL_PL;

	_PLE_lib_VariableN __Script_CreateBuildScript__PL__		PLSysAPI_Script_CreateBuildScript   = NULL_PL;
	_PLE_lib_VariableN __Script_ExecuteBuildScript__PL__   	PLSysAPI_Script_ExecuteBuildScript  = NULL_PL;
	_PLE_lib_VariableN __Script_ExecuteBuildNativeFuncScript__PL__ PLSysAPI_Script_ExecuteBuildNativeFuncScript = NULL_PL;
	_PLE_lib_VariableN __Script_ReleaseBuildScript__PL__	PLSysAPI_Script_ReleaseBuildScrip   = NULL_PL;
	_PLE_lib_VariableN __Script_RegisterScriptFunc__PL__	PLSysAPI_Script_RegisterScriptFunc  = NULL_PL;
	_PLE_lib_VariableN __Script_RegisterScriptPackageFunc__PL__  PLSysAPI_Script_RegisterScriptPackageFunc = NULL_PL;
	_PLE_lib_VariableN __Script_ExecuteStringScript__PL__	PLSysAPI_Script_ExecuteStringScript = NULL_PL;
