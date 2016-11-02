/*
 * PLEngineRenderPackage.cpp
 *
 *  Created on: 2009-9-14
 *      Author: Administrator
 */
#include "PLEngineRenderPackage.h"

	PLLibraryHandle CreateLibraryPL(HPPLEngine hEngine,void_pl * ptrEx){
/*		PL_ScriptLibraryHeavy * ptrInface;
		PL_ScriptLibraryFunTable    * ptrTable;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		AddresValue_pl  addresV;
		PLConstCharTableHandle hScriptHandle;
		char_pl pPath[PL3DSystemFileNameMaxLength];
		intV_pl iPathSize;
		intV_pl iAllocSize;
		intV_pl iInfaceSize;
		intV_pl iTableALlocSize;
		intV_pl iTableSize;
		intV_pl iCacheLineSize;

		if((hEngine == NULL_PL) || (g_hLibraryHandle_Script != NULL_PL))
			return NULL_PL;
		ptrInface = NULL_PL;
		ptrTable  = NULL_PL;
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		iCacheLineSize = ptrInfo->iCacheLineSize;

		iInfaceSize = PL_CompilerAllocSize(PL_ScriptLibraryHeavy);
		iAllocSize  = PLSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
		ptrInface   = (PL_ScriptLibraryHeavy *)PLSysAPI_AllocateMemory(iAllocSize);
		if(ptrInface==NULL_PL)
			return NULL_PL;
		addresV = (AddresValue_pl)ptrInface;
		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
		PLSysAPI_MemoryClearZero((void_pl *)(addresV),iInfaceSize);
		((PL_ScriptLibraryHeavy *)addresV)->ptrMem = ptrInface;
		ptrInface = (PL_ScriptLibraryHeavy *)addresV;

		iTableSize = PL_CompilerAllocSize(PL_ScriptLibraryFunTable);
		iTableALlocSize = PLSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (PL_ScriptLibraryFunTable *)PLSysAPI_AllocateMemory(iTableALlocSize);
		if(ptrTable == NULL_PL){
			if(ptrInface!=NULL_PL){
				PLSysAPI_FreeMemory(ptrInface->ptrMem);
				ptrInface = NULL_PL;
			}
			return NULL_PL;
		}
		addresV = (AddresValue_pl)ptrTable;
		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
		PLSysAPI_MemoryClearZero((void_pl *)(addresV),iTableSize);
		((PL_ScriptLibraryFunTable *)addresV)->ptrMem = ptrTable;
		ptrTable = (PL_ScriptLibraryFunTable *)addresV;
		ptrTable->Inface.cbSize = iTableSize;
		ptrTable->Inface.iFunCount = PLScript_Table_FunMaxSize;

		ptrInface->Inface.cbSize 			 = iInfaceSize;
		ptrInface->Inface.hModuleHandle 	 = PLLibraryHandle_Invalid;
		ptrInface->Inface.Destory_LibraryPL  = Destory_LibraryPL;
		ptrInface->Inface.UnInstallLibraryPL = UnInstallLibraryPL;
		ptrInface->Inface.InstallLibraryPL   = InstallLibraryPL;
		ptrInface->Inface.ptrFunTable 		 = (PL_EngineLibraryFunTable *)ptrTable;
		ptrInface->Inface.ptrExternData 	 = NULL_PL;

		ptrInface->iCWDSize = ptrSysEnv->iPlusCWDSize;
		PLSysAPI_MemoryCpy(ptrInface->pCWD,ptrSysEnv->pPlusCWD,ptrInface->iCWDSize);

		iPathSize = ptrInface->iCWDSize;
		PLSysAPI_MemoryClearZero(pPath,PL3DSystemFileNameMaxLength);
		PLSysAPI_MemoryCpy(pPath,ptrInface->pCWD,iPathSize);
		PLSysAPI_MemoryCpy(&(pPath[iPathSize]),PLScript_ConstID_ScriptConstFile_Str
								,PL_CompilerAllocSize(PLScript_ConstID_ScriptConstFile_Str));
		iPathSize += PL_CompilerStringSize(PLScript_ConstID_ScriptConstFile_Str);

		hScriptHandle = PLSysAPI_Sys_OpenConstCharTable(pPath,iPathSize);
		if(hScriptHandle==NULL_PL){
			PLSysAPI_FreeMemory(ptrTable->ptrMem);
			ptrTable = NULL_PL;
			ptrInface->Inface.ptrFunTable = NULL_PL;
			PLSysAPI_FreeMemory(ptrInface->ptrMem);
			ptrInface = NULL_PL;
			return NULL_PL;
		}
		ptrInface->hSysConstCharTable = hScriptHandle;
		ptrInface->hEngine            = hEngine;
		g_hLibraryHandle_Script = ptrInface;
		//		PLConstCharTableHandle g_hSysConstCharTable
		return (PLLibraryHandle)ptrInface;*/
		return NULL_PL;
	}
	bool_pl 	InstallLibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
		bool_pl bInstall;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		bInstall = false_pl;
		if((hAndle == NULL_PL) || (hEngine == NULL_PL))
			return bInstall;
/*		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

		PLSysAPI_Script_Open 			 		= Eg_OpenScript;
		PLSysAPI_Script_InitializeScript 		= Eg_InitializeScriptLib;
		PLSysAPI_Script_Close 			 		= Eg_CloseScript;
		PLSysAPI_Script_GetLibraryHandle        = Eg_GetLibraryHandle_global;
//		PLSysAPI_Script_ScriptConverToState	    = Eg_ScriptConverToState;
//		PLSysAPI_Script_StateConverToScript     = Eg_StateConverToScript;

		PLSysAPI_Script_PushInt32 				= Eg_PushInt32;
		PLSysAPI_Script_PopInt32  				= Eg_PopInt32;
		PLSysAPI_Script_PushIntV  				= Eg_PushIntV;
		PLSysAPI_Script_PopIntV   				= Eg_PopIntV;
		PLSysAPI_Script_PushString				= Eg_PushString;
		PLSysAPI_Script_PopString 				= Eg_PopString;
		PLSysAPI_Script_PushBool  				= Eg_PushBool;
		PLSysAPI_Script_PopBool   				= Eg_PopBool;
		PLSysAPI_Script_PushDouble  			= Eg_PushDouble;
		PLSysAPI_Script_PopDouble				= Eg_PopDouble;
		PLSysAPI_Script_PushFloat				= Eg_PushFloat;
		PLSysAPI_Script_PopFloat				= Eg_PopFloat;
		PLSysAPI_Script_PushPointer 			= Eg_PushPointer;
		PLSysAPI_Script_PopPointer  			= Eg_PopPointer;

		PLSysAPI_Script_CopyStackData			= Eg_CopyStackData;
		PLSysAPI_Script_MoveStackData			= Eg_MoveStackData;
		PLSysAPI_Script_RemoveStackData			= Eg_RemoveStackData;
		PLSysAPI_Script_ReplaceStackData		= Eg_ReplaceStackData;
		PLSysAPI_Script_PushGTable				= Eg_PushGTable;
		PLSysAPI_Script_PushCTable				= Eg_PushCTable;
		PLSysAPI_Script_PushTable				= Eg_PushTable;
		PLSysAPI_Script_PushNewTable            = Eg_PushNewTable;

		PLSysAPI_Script_GetStackElementCount	= Eg_GetStackElementCount;
		PLSysAPI_Script_SetGlobalValue			= Eg_SetGlobalValue;
		PLSysAPI_Script_GetGlobalValue			= Eg_GetGlobalValue;
		PLSysAPI_Script_SetGlobalValueI			= NULL_PL;
		PLSysAPI_Script_GetGlobalValueI			= NULL_PL;
		PLSysAPI_Script_GetGlobalSize			= NULL_PL;
		PLSysAPI_Script_SetRegisterValue		= NULL_PL;
		PLSysAPI_Script_GetRegisterValue		= NULL_PL;
		PLSysAPI_Script_SetRegisterValueI		= NULL_PL;
		PLSysAPI_Script_GetRegisterValueI		= NULL_PL;
		PLSysAPI_Script_GetRegisterSize			= NULL_PL;
		PLSysAPI_Script_SetTableValue			= NULL_PL;
		PLSysAPI_Script_GetTableValue			= NULL_PL;
		PLSysAPI_Script_SetTableValueI			= NULL_PL;
		PLSysAPI_Script_GetTableValueI			= NULL_PL;
		PLSysAPI_Script_GetTableSize			= NULL_PL;
		PLSysAPI_Script_isGlobalValueNull		= NULL_PL;
		PLSysAPI_Script_isRegisterValueNull		= NULL_PL;
		PLSysAPI_Script_isTableValueNull		= NULL_PL;

		PLSysAPI_Script_AllocCScriptSpaceMemory    = Eg_AllocCScriptSpaceMemory;
		PLSysAPI_Script_GetCScriptSpaceMemoryPtr   = Eg_GetCScriptSpaceMemoryPointer;
		PLSysAPI_Script_FreeCScriptSpaceMemory     = Eg_FreeCScriptSpaceMemory;

		PLSysAPI_Script_RegisterScriptFunc      = Eg_RegisterScriptFunc;
		PLSysAPI_Script_CreateBuildScript       = Eg_CreateBuildScript;
		PLSysAPI_Script_ExecuteBuildScript      = Eg_ExecuteBuildScript;
		PLSysAPI_Script_ReleaseBuildScrip       = Eg_ReleaseBuildScript;
		PLSysAPI_Script_ExecuteStringScript 	= Eg_ExecuteStringScript;*/
		return bInstall;
	}
	HPL_Result UnInstallLibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
		HPL_Result hResult;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		hResult = HPLResult_Fail;
		if((hEngine == NULL_PL) || (hAndle == NULL_PL))
			return hResult;
/*		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

		PLSysAPI_Script_Open 			 		= NULL_PL;
		PLSysAPI_Script_InitializeScript 		= NULL_PL;
		PLSysAPI_Script_Close 			 		= NULL_PL;
		PLSysAPI_Script_GetLibraryHandle        = NULL_PL;
//		PLSysAPI_Script_ScriptConverToState	    = NULL_PL;
//		PLSysAPI_Script_StateConverToScript     = NULL_PL;

		PLSysAPI_Script_PushInt32 				= NULL_PL;
		PLSysAPI_Script_PopInt32  				= NULL_PL;
		PLSysAPI_Script_PushIntV  				= NULL_PL;
		PLSysAPI_Script_PopIntV   				= NULL_PL;
		PLSysAPI_Script_PushString				= NULL_PL;
		PLSysAPI_Script_PopString 				= NULL_PL;
		PLSysAPI_Script_PushBool				= NULL_PL;
		PLSysAPI_Script_PopBool					= NULL_PL;
		PLSysAPI_Script_PushDouble				= NULL_PL;
		PLSysAPI_Script_PopDouble				= NULL_PL;
		PLSysAPI_Script_PushFloat				= NULL_PL;
		PLSysAPI_Script_PopFloat				= NULL_PL;
		PLSysAPI_Script_Pop						= NULL_PL;


		PLSysAPI_Script_CopyStackData		= NULL_PL;
		PLSysAPI_Script_MoveStackData		= NULL_PL;
		PLSysAPI_Script_RemoveStackData		= NULL_PL;
		PLSysAPI_Script_ReplaceStackData	= NULL_PL;
		PLSysAPI_Script_PushGTable			= NULL_PL;
		PLSysAPI_Script_PushCTable			= NULL_PL;
		PLSysAPI_Script_PushTable			= NULL_PL;
		PLSysAPI_Script_PushNewTable        = NULL_PL;
		PLSysAPI_Script_GetStackElementCount= NULL_PL;
		PLSysAPI_Script_SetGlobalValue		= NULL_PL;
		PLSysAPI_Script_GetGlobalValue		= NULL_PL;

		PLSysAPI_Script_AllocCScriptSpaceMemory    = NULL_PL;
		PLSysAPI_Script_GetCScriptSpaceMemoryPtr   = NULL_PL;
		PLSysAPI_Script_FreeCScriptSpaceMemory     = NULL_PL;

		PLSysAPI_Script_CreateBuildScript       = NULL_PL;
		PLSysAPI_Script_ReleaseBuildScrip       = NULL_PL;
		PLSysAPI_Script_ExecuteStringScript 	= NULL_PL;
		PLSysAPI_Script_RegisterScriptFunc      = NULL_PL;*/
		return HPLResult_OK;
	}
	void_pl	Destory_LibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
/*		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		PL_ScriptLibraryHeavy * ptrInface;
		ptrInface = (PL_ScriptLibraryHeavy *)hAndle;
		if((hEngine == NULL_PL) || (hAndle == NULL_PL))
			return;
		g_hLibraryHandle_Script = NULL_PL;
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		if(ptrInface->hSysConstCharTable!=NULL_PL){
			PLSysAPI_Sys_ReleaseConstCharTable(ptrInface->hSysConstCharTable);
			ptrInface->hSysConstCharTable = NULL_PL;
		}
		if(ptrInface->Inface.ptrFunTable!=NULL_PL){
			PLSysAPI_FreeMemory(((PL_ScriptLibraryFunTable *)(ptrInface->Inface.ptrFunTable))->ptrMem);
			ptrInface->Inface.ptrFunTable = NULL_PL;
		}
		if(ptrInface->Inface.ptrExternData!=NULL_PL){
			PLSysAPI_FreeMemory((void_pl *)(ptrInface->Inface.ptrExternData));
			ptrInface->Inface.ptrExternData = NULL_PL;
		}
		PLSysAPI_FreeMemory(ptrInface->ptrMem);*/
	}
