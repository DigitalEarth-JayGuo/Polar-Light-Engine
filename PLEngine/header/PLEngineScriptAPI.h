/*
 * PLEngineScriptAPI.h
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "PLEngineH.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineSysAPI.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#ifndef PLENGINESCRIPTAPI_H_
#define PLENGINESCRIPTAPI_H_
	/*
	 *
	 *
	 * */
	typedef _CallStack_default_ PLScriptHandle (* __Script_OpenScript__PL__)					();
	typedef _CallStack_default_ HPL_Result     (* __Script_InitializeScript__PL__)				(PLScriptHandle);
	typedef _CallStack_default_ void_pl        (* __Script_CloseScript__PL__)					(PLScriptHandle);
	typedef _CallStack_default_ PLLibraryHandle (* __Script_GetLibraryHandleScript_global__PL__)();

	typedef _CallStack_default_ HPL_Result     (* __Script_PushInt32__PL__)				(PLScriptHandle,int32_pl);
	typedef _CallStack_default_ int32_pl       (* __Script_PopInt32__PL__)				(PLScriptHandle);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushIntV__PL__) 				(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ intV_pl        (* __Script_PopIntV__PL__) 				(PLScriptHandle);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushString__PL__)    		(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ intV_pl        (* __Script_PopString__PL__) 			(PLScriptHandle,char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushBool__PL__) 				(PLScriptHandle,bool_pl);
	typedef _CallStack_default_ bool_pl        (* __Script_PopBool__PL__) 				(PLScriptHandle);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushDouble__PL__) 			(PLScriptHandle,double_pl);
	typedef _CallStack_default_ double_pl      (* __Script_PopDouble__PL__) 			(PLScriptHandle);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushFloat__PL__) 			(PLScriptHandle,float_pl);
	typedef _CallStack_default_ float_pl       (* __Script_PopFloat__PL__) 				(PLScriptHandle);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushPointer__PL__) 			(PLScriptHandle,void_pl *);
	typedef _CallStack_default_ void_pl *      (* __Script_PopPointer__PL__) 			(PLScriptHandle);
	typedef _CallStack_default_ void_pl        (* __Script_Pop__PL__) 					(PLScriptHandle);


	typedef _CallStack_default_ HPL_Result     (* __Script_CopyStackData__PL__) 		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_MoveStackData__PL__) 		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_RemoveStackData__PL__) 		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_ReplaceStackData__PL__) 		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushGTable__PL__) 			(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushCTable__PL__) 			(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushTable__PL__) 			(PLScriptHandle,intV_pl,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_PushNewTable__PL__)			(PLScriptHandle,const_pl char_pl *,intV_pl);

	typedef _CallStack_default_ intV_pl        (* __Script_GetStackElementCount__PL__) 	(PLScriptHandle);
	typedef _CallStack_default_ void_pl        (* __Script_SetGlobalValue__PL__) 		(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_GetGlobalValue__PL__) 		(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ void_pl        (* __Script_SetGlobalValueI__PL__)		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_GetGlobalValueI__PL__) 		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ intV_pl        (* __Script_GetGlobalSize__PL__) 		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ void_pl        (* __Script_SetRegisterValue__PL__)		(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_GetRegisterValue__PL__)		(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ void_pl        (* __Script_SetRegisterValueI__PL__)		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_GetRegisterValueI__PL__)		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ intV_pl        (* __Script_GetRegisterSize__PL__)		(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ void_pl        (* __Script_SetTableValue__PL__)			(PLScriptHandle,intV_pl,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_GetTableValue__PL__)			(PLScriptHandle,intV_pl,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ void_pl        (* __Script_SetTableValueI__PL__)		(PLScriptHandle,intV_pl,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_GetTableValueI__PL__)		(PLScriptHandle,intV_pl,intV_pl);
	typedef _CallStack_default_ intV_pl        (* __Script_GetTableSize__PL__)			(PLScriptHandle,intV_pl);
	typedef _CallStack_default_ bool_pl        (* __Script_isGlobalValueNull__PL__)		(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ bool_pl        (* __Script_isRegisterValueNull__PL__)	(PLScriptHandle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ bool_pl        (* __Script_isTableValueNull__PL__)		(PLScriptHandle,intV_pl,const_pl char_pl *,intV_pl);

	typedef _CallStack_default_ PLScriptUDMHandle  (* __Script_AllocCScriptSpaceMemory__PL__) 		    (PLScriptHandle,intV_pl);
	typedef _CallStack_default_ void_pl *     	   (* __Script_GetCScriptSpaceMemoryPointer__PL__) 		(PLScriptHandle,PLScriptUDMHandle);
	typedef _CallStack_default_ void_pl            (* __Script_FreeCScriptSpaceMemory__PL__) 			(PLScriptHandle,PLScriptUDMHandle);

	typedef _CallStack_default_ HPL_Result     (* __Script_CreateBuildScript__PL__)  (PLScriptHandle,const_pl byte_pl *,intV_pl,const_pl UTFSyschar_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_ExecuteBuildScript__PL__) (PLScriptHandle,const_pl UTFSyschar_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_ExecuteBuildNativeFuncScript__PL__)(PLScriptHandle,PL_ScriptNativeFuncParamer *,const_pl UTFSyschar_pl *,intV_pl);
	typedef _CallStack_default_ void_pl        (* __Script_ReleaseBuildScript__PL__) (PLScriptHandle,const_pl UTFSyschar_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_ExecuteStringScript__PL__)(PLScriptHandle,const_pl byte_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result     (* __Script_RegisterScriptFunc__PL__) (PLScriptHandle,const_pl UTFSyschar_pl *,intV_pl,const_pl UTFSyschar_pl *,intV_pl,void_pl *);
	typedef _CallStack_default_ intV_pl		   (* __Script_RegisterScriptPackageFunc__PL__)(PLScriptHandle,const_pl UTFSyschar_pl *,intV_pl,PL_RegScriptLib *,intV_pl);

	/*
	 *
	 *
	 * */
	_PLE_lib_Variable __Script_OpenScript__PL__  					PLSysAPI_Script_Open;
	_PLE_lib_Variable __Script_InitializeScript__PL__				PLSysAPI_Script_InitializeScript;
	_PLE_lib_Variable __Script_CloseScript__PL__ 					PLSysAPI_Script_Close;
	_PLE_lib_Variable __Script_GetLibraryHandleScript_global__PL__	PLSysAPI_Script_GetLibraryHandle;
//	_PLE_lib_Variable __Script_ScriptConverToState__PL__   		PLSysAPI_Script_ScriptConverToState;
//	_PLE_lib_Variable __Script_StateConverToScript__PL__   		PLSysAPI_Script_StateConverToScript;

	_PLE_lib_Variable __Script_PushInt32__PL__					PLSysAPI_Script_PushInt32;
	_PLE_lib_Variable __Script_PopInt32__PL__					PLSysAPI_Script_PopInt32;
	_PLE_lib_Variable __Script_PushIntV__PL__					PLSysAPI_Script_PushIntV;
	_PLE_lib_Variable __Script_PopIntV__PL__					PLSysAPI_Script_PopIntV;
	_PLE_lib_Variable __Script_PushString__PL__					PLSysAPI_Script_PushString;
	_PLE_lib_Variable __Script_PopString__PL__					PLSysAPI_Script_PopString;
	_PLE_lib_Variable __Script_PushBool__PL__					PLSysAPI_Script_PushBool;
	_PLE_lib_Variable __Script_PopBool__PL__					PLSysAPI_Script_PopBool;
	_PLE_lib_Variable __Script_PushDouble__PL__  				PLSysAPI_Script_PushDouble;
	_PLE_lib_Variable __Script_PopDouble__PL__  				PLSysAPI_Script_PopDouble;
	_PLE_lib_Variable __Script_PushFloat__PL__  				PLSysAPI_Script_PushFloat;
	_PLE_lib_Variable __Script_PopFloat__PL__    				PLSysAPI_Script_PopFloat;
	_PLE_lib_Variable __Script_Pop__PL__						PLSysAPI_Script_Pop;

	_PLE_lib_Variable __Script_PushPointer__PL__				PLSysAPI_Script_PushPointer;
	_PLE_lib_Variable __Script_PopPointer__PL__					PLSysAPI_Script_PopPointer;

	_PLE_lib_Variable __Script_CopyStackData__PL__				PLSysAPI_Script_CopyStackData;
	_PLE_lib_Variable __Script_MoveStackData__PL__				PLSysAPI_Script_MoveStackData;
	_PLE_lib_Variable __Script_RemoveStackData__PL__			PLSysAPI_Script_RemoveStackData;
	_PLE_lib_Variable __Script_ReplaceStackData__PL__			PLSysAPI_Script_ReplaceStackData;
	_PLE_lib_Variable __Script_PushGTable__PL__					PLSysAPI_Script_PushGTable;
	_PLE_lib_Variable __Script_PushCTable__PL__					PLSysAPI_Script_PushCTable;
	_PLE_lib_Variable __Script_PushTable__PL__					PLSysAPI_Script_PushTable;
	_PLE_lib_Variable __Script_PushNewTable__PL__				PLSysAPI_Script_PushNewTable;

	_PLE_lib_Variable __Script_GetStackElementCount__PL__		PLSysAPI_Script_GetStackElementCount;
	_PLE_lib_Variable __Script_SetGlobalValue__PL__				PLSysAPI_Script_SetGlobalValue;
	_PLE_lib_Variable __Script_GetGlobalValue__PL__				PLSysAPI_Script_GetGlobalValue;
	_PLE_lib_Variable __Script_SetGlobalValueI__PL__			PLSysAPI_Script_SetGlobalValueI;
	_PLE_lib_Variable __Script_GetGlobalValueI__PL__ 			PLSysAPI_Script_GetGlobalValueI;
	_PLE_lib_Variable __Script_GetGlobalSize__PL__ 				PLSysAPI_Script_GetGlobalSize;
	_PLE_lib_Variable __Script_SetRegisterValue__PL__			PLSysAPI_Script_SetRegisterValue;
	_PLE_lib_Variable __Script_GetRegisterValue__PL__			PLSysAPI_Script_GetRegisterValue;
	_PLE_lib_Variable __Script_SetRegisterValueI__PL__			PLSysAPI_Script_SetRegisterValueI;
	_PLE_lib_Variable __Script_GetRegisterValueI__PL__			PLSysAPI_Script_GetRegisterValueI;
	_PLE_lib_Variable __Script_GetRegisterSize__PL__			PLSysAPI_Script_GetRegisterSize;
	_PLE_lib_Variable __Script_SetTableValue__PL__				PLSysAPI_Script_SetTableValue;
	_PLE_lib_Variable __Script_GetTableValue__PL__				PLSysAPI_Script_GetTableValue;
	_PLE_lib_Variable __Script_SetTableValueI__PL__				PLSysAPI_Script_SetTableValueI;
	_PLE_lib_Variable __Script_GetTableValueI__PL__				PLSysAPI_Script_GetTableValueI;
	_PLE_lib_Variable __Script_GetTableSize__PL__				PLSysAPI_Script_GetTableSize;
	_PLE_lib_Variable __Script_isGlobalValueNull__PL__			PLSysAPI_Script_isGlobalValueNull;
	_PLE_lib_Variable __Script_isRegisterValueNull__PL__		PLSysAPI_Script_isRegisterValueNull;
	_PLE_lib_Variable __Script_isTableValueNull__PL__			PLSysAPI_Script_isTableValueNull;

	_PLE_lib_Variable __Script_AllocCScriptSpaceMemory__PL__    		PLSysAPI_Script_AllocCScriptSpaceMemory;
	_PLE_lib_Variable __Script_GetCScriptSpaceMemoryPointer__PL__ 		PLSysAPI_Script_GetCScriptSpaceMemoryPtr;
	_PLE_lib_Variable __Script_FreeCScriptSpaceMemory__PL__ 			PLSysAPI_Script_FreeCScriptSpaceMemory;

	_PLE_lib_Variable __Script_CreateBuildScript__PL__				PLSysAPI_Script_CreateBuildScript;
	_PLE_lib_Variable __Script_ExecuteBuildScript__PL__         	PLSysAPI_Script_ExecuteBuildScript;
	_PLE_lib_Variable __Script_ExecuteBuildNativeFuncScript__PL__ 	PLSysAPI_Script_ExecuteBuildNativeFuncScript;
	_PLE_lib_Variable __Script_ReleaseBuildScript__PL__				PLSysAPI_Script_ReleaseBuildScrip;
	_PLE_lib_Variable __Script_RegisterScriptFunc__PL__				PLSysAPI_Script_RegisterScriptFunc;
	_PLE_lib_Variable __Script_RegisterScriptPackageFunc__PL__  	PLSysAPI_Script_RegisterScriptPackageFunc;
	_PLE_lib_Variable __Script_ExecuteStringScript__PL__			PLSysAPI_Script_ExecuteStringScript;

	#define PLSysAPI_Script_PushInt PLSysAPI_Script_PushInt32
	#define PLSysAPI_Script_PopInt  PLSysAPI_Script_PopInt32
#endif /* PLENGINESCRIPTAPI_H_ */
