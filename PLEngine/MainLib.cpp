/*
 * MainLib.cpp
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "header/MainLib.h"
#include "header/PLEngineMemoryPool.h"
//#include "PLEngineHeavyH.h"
#if PLOperat_System == PLOperatSystem_Window
	_PLE_lib_VariableN PPL_EngineTLSQueue g_ptrTLSQueue = NULL_PL;
	BOOL DllMain(HMODULE module, DWORD reason, void* reserved){
	    switch (reason){
			case DLL_PROCESS_ATTACH:
				if(g_ptrTLSQueue==NULL_PL){
					g_ptrTLSQueue = PLSysAPI_WinLocal_InitializeTLSQueue();
					if(g_ptrTLSQueue==NULL_PL)
						return FALSE;
				}
				break;
			case DLL_THREAD_ATTACH:
				break;
			case DLL_THREAD_DETACH:
				if(g_ptrTLSQueue!=NULL_PL){
					PLSysAPI_WinLocal_NotifyTLSDataAllFree(g_ptrTLSQueue);
				}
				break;
			case DLL_PROCESS_DETACH:
				if(g_ptrTLSQueue!=NULL_PL){
					PLSysAPI_WinLocal_DestoryTLSToQueue(&g_ptrTLSQueue);
				}
				break;
	    }
	    return TRUE;
	}
#endif

	PLThreadVirtualID	  g_ThreadAllID 					= 0;
	PLMemManager  	 	  g_MemPoolManager 					= {0};
	PLTLSKey     	 	  g_allocateOrganKey 				= PLTLSKey_Invalid;
	PLTLSKey      		  g_ThreadVirtualIDKey  			= PLTLSKey_Invalid;
	PLMemFreeObject     * g_AllocateOrganFreeList        	= NULL_PL;
	_Syn_SpinLock         g_AOFreeListLock               	= PLSyn_Const_SynSpinLockPass;
	volatile_pl intV_pl   g_iAOMaxSize                   	= 0;
	volatile_pl intV_pl   g_iAOCurrentSize               	= 0;


	_CallStack_default_ PLLibraryHandle _CreateBasisLibrary_PL_Math(HPPLEngine,void_pl*);
	_CallStack_default_ PLLibraryHandle _CreateBasisLibrary_PL_SysWith(HPPLEngine,void_pl*);
	_CallStack_default_ PLLibraryHandle _CreateBasisLibrary_PL_SystemIO(HPPLEngine,void_pl*);
	_CallStack_default_ void_pl _DestroyBasisLibrary_PL(HPPLEngine,PLLibraryHandle,void_pl*);

	HPPLEngine CreateEngineHandle(){
		PLFileCFGHandle hCFGHandle;
		PLConstCharTableHandle hConstCharHandle;
		PLConstCharTableHandle hDbgCharTable;
		PL_EngineState * ptrState;
		PL_ConstSystemInfo constinfo;
		PL_OperatSysEnvSet operatenv;
		intV_pl iAllocSize;
		intV_pl iCacheLineSize;
		UTFSyschar_pl pPath[PL3DSystemFilePathNameMaxLength];
		intV_pl iwPathSize;
		UTFSyschar_pl * ptrConstCharRes;
		intV_pl   iwConstCharResSize;
		UTFSyschar_pl * ptrLable;
		intV_pl   iwLableSize;
		hConstCharHandle = NULL_PL;
		hDbgCharTable = NULL_PL;

		ptrState = NULL_PL;
		if(g_ptrCurrentEngineState!=NULL_PL)
			return g_ptrCurrentEngineState;
		do{
			PLSysAPI_MemoryClearZero(&constinfo,PL_CompilerAllocSize(PL_ConstSystemInfo));
			PLSysAPI_MemoryClearZero(&operatenv,PL_CompilerAllocSize(PL_OperatSysEnvSet));
			if(HResulPL_FAILED(__PLSysAPI_Sys_GetConstSystemInfo__Private(&constinfo)) || HResulPL_FAILED(__PLSysAPI_Sys_GetOperatSystemEnv__Private(&operatenv)))
				break;
			iCacheLineSize = constinfo.iCacheLineSize;
			iwPathSize =0;
			PLSysAPI_SysStringClear(pPath,PL3DSystemFilePathNameMaxLength);
			iwPathSize = operatenv.iwCWDSize;
			PLSysAPI_SysStringCpy(pPath,operatenv.pCWD,iwPathSize);
			PLSysAPI_SysStringCpy(&(pPath[iwPathSize]),PLSys_ConstChar_EngineConstFile,PLSysAPI_SysConstStringSize(PLSys_ConstChar_EngineConstFile));
			iwPathSize += PLSysAPI_SysConstStringSize(PLSys_ConstChar_EngineConstFile);
			//Open ConstCharTable File of Engine
			hConstCharHandle = PLSysAPI_Sys_OpenConstCharTable(pPath,iwPathSize);
			if(hConstCharHandle==NULL_PL)
				break;
			//
			if(g_ThreadVirtualIDKey != PLTLSKey_Invalid){
				PLSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
				g_ThreadVirtualIDKey = PLTLSKey_Invalid;
			}
			//alloc a TLS
			if(HResulPL_FAILED(PLSysAPI_SystemProcess_AllocTLSKey(&(g_ThreadVirtualIDKey),PLTLSKey_ThreadVirtualID_Destory)) == true_pl){
				g_ThreadVirtualIDKey = PLTLSKey_Invalid;
				break;
			}
			iwPathSize =0;
			PLSysAPI_SysStringClear(pPath,PL3DSystemFilePathNameMaxLength);
			iwPathSize = operatenv.iwCWDSize;
			PLSysAPI_SysStringCpy(pPath,operatenv.pCWD,iwPathSize);

			ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(hConstCharHandle,PLSys_ConstChar_DebugInformationFileName,&iwConstCharResSize);
			if((ptrConstCharRes!=NULL_PL) && (iwConstCharResSize >0)){
				PLSysAPI_SysStringCpy(&(pPath[iwPathSize]),ptrConstCharRes,iwConstCharResSize);
				iwPathSize += iwConstCharResSize;
				hDbgCharTable = PLSysAPI_Sys_OpenConstCharTable(pPath,iwPathSize);
			}
			// open engine's config file . file format is like ini same
			iwPathSize =0;
			PLSysAPI_SysStringClear(pPath,PL3DSystemFilePathNameMaxLength);
			iwPathSize = operatenv.iwCWDSize;
			PLSysAPI_SysStringCpy(pPath,operatenv.pCWD,iwPathSize);
			ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(hConstCharHandle,PLSys_ConstChar_EngineCFG,&iwConstCharResSize);
			PLSysAPI_SysStringCpy(&(pPath[iwPathSize]),ptrConstCharRes,iwConstCharResSize);
			iwPathSize += iwConstCharResSize;
			hCFGHandle = PLSysAPI_Sys_OpenCfgFile(pPath,iwPathSize);
			if(hCFGHandle==NULL_PL){
				if(hConstCharHandle != NULL_PL){
					PLSysAPI_Sys_ReleaseConstCharTable(hConstCharHandle);
					hConstCharHandle = NULL_PL;
				}
				if(hDbgCharTable != NULL_PL){
					PLSysAPI_Sys_ReleaseConstCharTable(hDbgCharTable);
					hDbgCharTable = NULL_PL;
				}
				if(g_ThreadVirtualIDKey != PLTLSKey_Invalid){
					PLSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
					g_ThreadVirtualIDKey = PLTLSKey_Invalid;
				}
				break;
			}
			PLSysAPI_Mem_InitializtionMemoryPool();
			//allocate  engine's hanlde memory
			iAllocSize = PL_CompilerAllocSize(PL_EngineState);
			iAllocSize = PLSysAPI_Alignment(iAllocSize,iCacheLineSize) + iCacheLineSize;
			ptrState =  (PL_EngineState *)PLSysAPI_AllocateMemory(iAllocSize);
			//if not allocate so return;
			if(ptrState==NULL_PL){
				if(hConstCharHandle != NULL_PL){
					PLSysAPI_Sys_ReleaseConstCharTable(hConstCharHandle);
					hConstCharHandle = NULL_PL;
				}
				if(hDbgCharTable != NULL_PL){
					PLSysAPI_Sys_ReleaseConstCharTable(hDbgCharTable);
					hDbgCharTable = NULL_PL;
				}
				if(hCFGHandle != NULL_PL){
					PLSysAPI_Sys_CloseCfgFile(hCFGHandle);
					hCFGHandle = NULL_PL;
				}
				if(g_ThreadVirtualIDKey != PLTLSKey_Invalid){
					PLSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
					g_ThreadVirtualIDKey = PLTLSKey_Invalid;
				}
				break;
			}
			//clear zero allocate memory struct
			PLSysAPI_MemoryClearZero(ptrState,iAllocSize);
			PLSysAPI_Sys_CopyConstSystemInfo(&(ptrState->ConstSysInfo),&constinfo);
			PLSysAPI_Sys_CopyOperatSystemEnv(&(ptrState->OperatEnv),&operatenv);
			ptrState->bInitialize = false_pl;
			ptrState->hSysConstCharTable = hConstCharHandle;
			ptrState->hDbgConstCharTable = hDbgCharTable;

			ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(hConstCharHandle,PLSys_ConstChar_CreateLibrary,&iwConstCharResSize);
	//		ptrState->PlusStandard.iEnterNSize = PLSysAPI_Sys_GetCfgFiletoString(hCFGHandle,"PlusEnterPointer\0",PL_CompilerStringSize("PlusEnterPointer\0")
	//					,"CreateEnter\0",PL_CompilerStringSize("CreateEnter\0"),(char_pl *)(ptrState->PlusStandard.pCreateEnterName),PLSys_Const_PlusCreateEnter_NameSize);
			ptrState->PlusStandard.iwEnterNSize = iwConstCharResSize;


			PLSysAPI_SysStringClear(ptrState->PlusStandard.pCreateEnterName,PLSys_Const_PlusCreateEnter_NameSize);
			PLSysAPI_SysStringCpy(ptrState->PlusStandard.pCreateEnterName,ptrConstCharRes,ptrState->PlusStandard.iwEnterNSize);


			//make Engine run directory struct
			ptrLable = PLSysAPI_Sys_GetConstCharID(hConstCharHandle,PLSys_ConstChar_PathLable,&iwLableSize);
			//Plus CurrentDirectory
			ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(hConstCharHandle,PLSys_ConstChar_PlusCWD,&iwConstCharResSize);
			//const_pl char_pl * ptrID,intV_pl iIDSize,char_pl * ptrString,intV_pl iMaxSize
			iwConstCharResSize = PLSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_pl UTFSyschar_pl *)ptrLable,iwLableSize
									,(const_pl UTF16char_pl  *)ptrConstCharRes,iwConstCharResSize
									,&(ptrState->OperatEnv.pPlusCWD[ptrState->OperatEnv.iwPlusCWDSize])
									,PL3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwPlusCWDSize);
			if(iwConstCharResSize>0){
				ptrState->OperatEnv.iwPlusCWDSize += iwConstCharResSize;
				ptrState->OperatEnv.pPlusCWD[ptrState->OperatEnv.iwPlusCWDSize] = PLSys_ConstChar_SystemCWDPartition;
				ptrState->OperatEnv.iwPlusCWDSize++;
			}
			PLSysAPI_SysStringClear(&(ptrState->OperatEnv.pPlusCWD[ptrState->OperatEnv.iwPlusCWDSize]),(PL3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwPlusCWDSize));
			//Resource CurrentDirectory
			ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(hConstCharHandle,PLSys_ConstChar_ResourceCWD,&iwConstCharResSize);
			iwConstCharResSize = PLSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_pl UTF16char_pl *)ptrLable,iwLableSize
									,(const_pl UTF16char_pl *)ptrConstCharRes,iwConstCharResSize,&(ptrState->OperatEnv.pResourceCWD[ptrState->OperatEnv.iwResourceCWDSize])
									,(PL3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwResourceCWDSize));
			if(iwConstCharResSize>0){
				ptrState->OperatEnv.iwResourceCWDSize += iwConstCharResSize;
				ptrState->OperatEnv.pResourceCWD[ptrState->OperatEnv.iwResourceCWDSize] = PLSys_ConstChar_SystemCWDPartition;
				ptrState->OperatEnv.iwResourceCWDSize++;
			}
			PLSysAPI_SysStringClear(&(ptrState->OperatEnv.pResourceCWD[ptrState->OperatEnv.iwResourceCWDSize])
											,(PL3DSystemFilePathNameMaxLength - ptrState->OperatEnv.iwResourceCWDSize));
			//Close Engine Main Cfig File
			PLSysAPI_Sys_CloseCfgFile(hCFGHandle);
			hCFGHandle = NULL_PL;
		}while(0);
		g_ptrCurrentEngineState = ptrState;
		PLSysAPI_SystemProcess_InitializeProcessLibrary();
		printf("CreateEngineHandle\n");
		return (HPPLEngine)ptrState;
	}
	HPL_Result InitializeEngine(HPPLEngine handle){
		PL_EngineState * ptrState;
		PL_OperatSysEnvSet * ptrSysEnv;
		PL_ConstSystemInfo * ptrInfo;
		void_pl * ptrFunc;
		PLLibModuleHandle hModule;
		__Create_Library__PL__ creatfun;
		UTFSyschar_pl pPath[PL3DSystemFilePathNameMaxLength];
		intV_pl  iwPathSize;
		UTFSyschar_pl * ptrConstCharRes;
		intV_pl   iwConstCharResSize;
		UTFSyschar_pl * ptrLable;
		intV_pl   iwLableSize;
		intV_pl   iwStrSize;
		PLConstCharTableHandle hConstCharhandle;
		PLConstCharTableHandle hDbgCharTable;
		PLFileCFGHandle hCFGHandle;
		PL_native_ELoadLibrary StLoadLibrary;
		PL_EngineLibraryHeavyInface * ptrInface;

		ptrState = (PL_EngineState *)handle;

		if(ptrState==NULL_PL || ptrState->bInitialize==true_pl)
			return HPLResult_Fail;
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(handle);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(handle);
		hConstCharhandle = ptrState->hSysConstCharTable;
		hDbgCharTable    = ptrState->hDbgConstCharTable;

		PLSysAPI_SysStringClear(pPath,PL3DSystemFilePathNameMaxLength);
		iwPathSize = ptrSysEnv->iwCWDSize;

		PLSysAPI_SysStringCpy(pPath,ptrSysEnv->pCWD,iwPathSize);
		ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(hConstCharhandle,PLSys_ConstChar_EngineCFG,&iwConstCharResSize);

		PLSysAPI_SysStringCpy(&(pPath[iwPathSize]),ptrConstCharRes,iwConstCharResSize);
		iwPathSize += iwConstCharResSize;
		hCFGHandle = PLSysAPI_Sys_OpenCfgFile(pPath,iwPathSize);
		if(hCFGHandle==NULL_PL)
			return HPLResult_Fail;

		PLSysAPI_MemoryClearZero(&StLoadLibrary,PL_CompilerAllocSize(PL_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = PLSys_ConstChar_ScriptPlus;
		if(HResulPL_FAILED(__native_LoadLibrary_PL(handle,NULL_PL,&(ptrState->ScriptPlus),&StLoadLibrary)) == true_pl){
			//load failed
		}

		PLSysAPI_MemoryClearZero(&StLoadLibrary,PL_CompilerAllocSize(PL_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = PLSys_ConstChar_ScenePlus;
		if(HResulPL_FAILED(__native_LoadLibrary_PL(handle,NULL_PL,&(ptrState->SceneManagerPlus),&StLoadLibrary)) == true_pl){

		}

		PLSysAPI_MemoryClearZero(&StLoadLibrary,PL_CompilerAllocSize(PL_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = PLSys_ConstChar_RenderSystemPlus;
		if(HResulPL_FAILED(__native_LoadLibrary_PL(handle,NULL_PL,&(ptrState->RenderSystemPlus),&StLoadLibrary)) == false_pl){

		}

		PLSysAPI_MemoryClearZero(&StLoadLibrary,PL_CompilerAllocSize(PL_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = PLSys_ConstChar_ResourcePlus;
		if(HResulPL_FAILED(__native_LoadLibrary_PL(handle,NULL_PL,&(ptrState->ResourceLoadPlus),&StLoadLibrary)) == false_pl){

		}

		PLSysAPI_MemoryClearZero(&StLoadLibrary,PL_CompilerAllocSize(PL_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = PLSys_ConstChar_ResourceMgrPlus;
		if(HResulPL_FAILED(__native_LoadLibrary_PL(handle,NULL_PL,&(ptrState->ResourceManagerPlus),&StLoadLibrary)) == false_pl){

		}

		PLSysAPI_MemoryClearZero(&StLoadLibrary,PL_CompilerAllocSize(PL_native_ELoadLibrary));
		StLoadLibrary.hCFGHandle = hCFGHandle;
		StLoadLibrary.iPlusID    = PLSys_ConstChar_LogPlus;
		if(HResulPL_FAILED(__native_LoadLibrary_PL(handle,NULL_PL,&(ptrState->LogSystemPlus),&StLoadLibrary)) == false_pl){

		}

		ptrState->bInitialize = true_pl;
		PLSysAPI_Sys_CloseCfgFile(hCFGHandle);
		hCFGHandle = NULL_PL;
		return HPLResult_OK;
	}
	HPL_Result DestoryEngineHandle(HPPLEngine handle){
		PL_EngineState * ptrState;
		PL_EngineLibraryHeavyInface * ptrInface;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		PLLibModuleHandle hModule;
		intV_pl iCacheLineSize;

		ptrState = (PL_EngineState *)handle;
		if(ptrState==NULL_PL)
			return HPLResultF_Paramer_NULL;
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(handle);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(handle);
		printf("DestoryEngineHandle\n");
		iCacheLineSize = ptrInfo->iCacheLineSize;
		if(g_ptrCurrentEngineState==ptrState)
			g_ptrCurrentEngineState = NULL_PL;
/*
		if(ptrState->ptrMath!=ptrState->ptrDefaultMath){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,(PL_EngineLibraryHeavyInface *)ptrState->ptrMath);
			ptrState->ptrMath = NULL_PL;
		}
		ptrInface = (PL_EngineLibraryHeavyInface *)ptrState->ptrDefaultMath;
		if(ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,ptrInface);
		}
		ptrState->ptrDefaultMath = NULL_PL;

		if(ptrState->ptrSysWith!=ptrState->ptrDefaultSysWith){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,(PL_EngineLibraryHeavyInface *)ptrState->ptrSysWith);
			ptrState->ptrSysWith = NULL_PL;
		}
		ptrInface = (PL_EngineLibraryHeavyInface *)ptrState->ptrDefaultSysWith;
		if(ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,ptrInface);
		}
		ptrState->ptrDefaultSysWith = NULL_PL;
*/
		if(ptrState->SceneManagerPlus.ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,&(ptrState->SceneManagerPlus));
		}
		if(ptrState->ScriptPlus.ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,&(ptrState->ScriptPlus));
		}
		if(ptrState->RenderSystemPlus.ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,&(ptrState->RenderSystemPlus));
		}
		if(ptrState->ResourceManagerPlus.ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,&(ptrState->ResourceManagerPlus));
		}
		if(ptrState->ResourceLoadPlus.ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,&(ptrState->ResourceLoadPlus));
		}
		if(ptrState->LogSystemPlus.ptrInface!=NULL_PL){
			__native_ReleaseLoadLibrary_PL(handle,NULL_PL,&(ptrState->LogSystemPlus));
		}
		if(ptrState->hSysConstCharTable != NULL_PL){
			PLSysAPI_Sys_ReleaseConstCharTable(ptrState->hSysConstCharTable);
			ptrState->hSysConstCharTable = NULL_PL;
		}
		if(ptrState->hDbgConstCharTable != NULL_PL){
			PLSysAPI_Sys_ReleaseConstCharTable(ptrState->hDbgConstCharTable);
			ptrState->hDbgConstCharTable = NULL_PL;
		}
//		if(ptrState->hMM != NULL_PL){
//			PLSysAPI_Mem_DestoryMemoryPool(ptrState->hMM);
//			ptrState->hMM = NULL_PL;
//		}
		PLSysAPI_FreeMemory(ptrState);
		PLSysAPI_Mem_DestoryMemoryPool();
		if(g_ThreadVirtualIDKey != PLTLSKey_Invalid){
			PLSysAPI_SystemProcess_FreeTLSKey(&g_ThreadVirtualIDKey);
			g_ThreadVirtualIDKey = PLTLSKey_Invalid;
		}
		PLSysAPI_SystemProcess_ReleaseProcessLibrary();
		ptrState = NULL_PL;
		return HPLResult_OK;
	}
	PLLibraryHandle _CreateBasisLibrary_PL_Math(HPPLEngine hEngine,void_pl * ptrEx){
		PL_EngineLibraryHeavyInface * ptrInface;
		PL_EngineLibraryFunTable    * ptrTable;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrEnv;
//		AddresValue_pl  addresV;
		intV_pl iAllocSize;
		intV_pl iInfaceSize;
		intV_pl iTableALlocSize;
		intV_pl iTableSize;
		intV_pl iFunCount;
		intV_pl iCacheLineSize;
		if(hEngine == NULL_PL)
			return NULL_PL;

		ptrInface = NULL_PL;
		ptrInfo = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrEnv  = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);

		iCacheLineSize = ptrInfo->iCacheLineSize;
		iInfaceSize = PL_CompilerAllocSize(PL_EngineLibraryHeavyInface);
		iAllocSize = PLSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
		ptrInface  = (PL_EngineLibraryHeavyInface *)PLSysAPI_AllocateMemory(iAllocSize);

		iFunCount  = PLLib_Const_SysMath_Tag_MaxSize - 1;
		iTableALlocSize = PL_CompilerAllocSize(PL_EngineLibraryFunTable);
		iTableSize = iTableALlocSize + PL_CompilerAllocSize(fun_pl) * iFunCount;
		iTableALlocSize = PLSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (PL_EngineLibraryFunTable *)PLSysAPI_AllocateMemory(iTableALlocSize);
		if((ptrInface == NULL_PL) || (ptrTable == NULL_PL)){
			if(ptrInface!=NULL_PL){
				PLSysAPI_FreeMemory((void_pl *)ptrInface);
				ptrInface = NULL_PL;
			}
			if(ptrTable!=NULL_PL){
				PLSysAPI_FreeMemory((void_pl *)ptrTable);
				ptrTable = NULL_PL;
			}
			return NULL_PL;
		}
//		addresV = (AddresValue_pl)ptrInface;
//		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrInface = (PL_EngineLibraryHeavyInface *)addresV;
		PLSysAPI_MemoryClearZero((void_pl *)(ptrInface),iInfaceSize);
//		addresV = (AddresValue_pl)ptrTable;
//		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrTable = (PL_EngineLibraryFunTable *)addresV;
		PLSysAPI_MemoryClearZero((void_pl *)(ptrTable),iTableSize);
		ptrTable->cbSize = iTableSize;
		ptrTable->iFunCount = iFunCount;
		ptrTable->functionlist[PLLib_Const_SysMath_InitializNormalizMatrix3x3] = (fun_pl)InitializNormalizMatrix3x3;
		ptrTable->functionlist[PLLib_Const_SysMath_InitializNormalizMatrix4x4] = (fun_pl)InitializNormalizMatrix4x4;
/*
		ptrDefaultLibrary->PLSysAPI_Math_Matrix3x3AxisRotation      = Matrix3x3AxisRotation;
		ptrDefaultLibrary->PLSysAPI_Math_Matrix3x3Mul               = Matrix3x3Mul;
		ptrDefaultLibrary->PLSysAPI_Math_Matrix4x4Mul               = Matrix4x4Mul;
		ptrDefaultLibrary->PLSysAPI_Math_QuaternionSlerp            = QuaternionSlerp;
*/
		ptrInface->cbSize = iInfaceSize;
		ptrInface->hModuleHandle = PLLibraryHandle_Invalid;
		ptrInface->Destory_LibraryPL = _DestroyBasisLibrary_PL;
		ptrInface->UnInstallLibraryPL = NULL_PL;
		ptrInface->InstallLibraryPL = NULL_PL;
		ptrInface->ptrFunTable = ptrTable;

		return (PLLibraryHandle)ptrInface;
	}
	PLLibraryHandle _CreateBasisLibrary_PL_SysWith(HPPLEngine hEngine,void_pl * ptrEx){
/*		PL_EngineState * ptrState;
		PL_OperatSysEnvSet * ptrSysEnv;
		PL_ConstSystemInfo * ptrInfo;
		void_pl * ptrFunc;
		PLLibModuleHandle hModule;
		__Create_Library__PL__ creatfun;
		char_pl pPath[PL3DSystemFileNameMaxLength];
		intV_pl  iPathSize;
		void_pl * ptrConstCharRes;
		intV_pl   iConstCharResSize;
		void_pl * ptrLable;
		intV_pl   iLableSize;
		intV_pl   iStrSize;
		PLConstCharTableHandle hConstCharhandle;
		PLConstCharTableHandle hDbgCharTable;
		PLFileCFGHandle hCFGHandle;


		if(hEngine==NULL_PL)
			return NULL_PL;

		ptrInfo = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrSysEnv  = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		iCacheLineSize = ptrInfo->iCacheLineSize;
		iInfaceSize = PL_CompilerAllocSize(PL_EngineLibraryHeavyInface);
		iAllocSize = PLSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
		ptrInface  = (PL_EngineLibraryHeavyInface *)PLSysAPI_AllocateMemory(iAllocSize);

		iFunCount  = PLLib_Const_SysWith_Tag_MaxSize - 1;
		iTableALlocSize = PL_CompilerAllocSize(PL_EngineLibraryFunTable);
		iTableSize = iTableALlocSize + sizeof(fun_pl) * iFunCount;
		iTableALlocSize = PLSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (PL_EngineLibraryFunTable *)PLSysAPI_AllocateMemory(iTableALlocSize);
		if((ptrInface == NULL_PL) || (ptrTable == NULL_PL)){
			if(ptrInface!=NULL_PL){
				PLSysAPI_FreeMemory((void_pl *)ptrInface);
				ptrInface = NULL_PL;
			}
			if(ptrTable!=NULL_PL){
				PLSysAPI_FreeMemory((void_pl *)ptrTable);
				ptrTable = NULL_PL;
			}
			return NULL_PL;
		}
//		addresV = (AddresValue_pl)ptrInface;
//		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrInface = (PL_EngineLibraryHeavyInface *)addresV;
		PLSysAPI_MemoryClearZero((void_pl *)(ptrInface),iInfaceSize);
//		addresV = (AddresValue_pl)ptrTable;
//		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
//		ptrTable = (PL_EngineLibraryFunTable *)addresV;
		PLSysAPI_MemoryClearZero((void_pl *)(ptrTable),iTableSize);
		ptrTable->cbSize = iTableSize;
		ptrTable->iFunCount = iFunCount;
		ptrInface->cbSize = iInfaceSize;
		ptrInface->hModuleHandle = PLLibraryHandle_Invalid;
		ptrInface->Destory_LibraryPL = _DestroyBasisLibrary_PL;
		ptrInface->UnInstallLibraryPL = NULL_PL;
		ptrInface->InstallLibraryPL = NULL_PL;
		ptrInface->ptrFunTable = ptrTable;

		return (PLLibraryHandle)ptrInface;*/
		return NULL_PL;
	}
	void_pl _DestroyBasisLibrary_PL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
		PL_EngineLibraryHeavyInface * ptrInface;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrEnv;

		ptrInface = (PL_EngineLibraryHeavyInface *)hAndle;
		if((ptrInface==NULL_PL) || (hEngine==NULL_PL))
			return;

		ptrInfo = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrEnv  = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		if(ptrInface->ptrFunTable!=NULL_PL){
			PLSysAPI_FreeMemory((void_pl *)(ptrInface->ptrFunTable));
			ptrInface->ptrFunTable = NULL_PL;
		}
		if(ptrInface->ptrExternData!=NULL_PL){
			PLSysAPI_FreeMemory((void_pl *)(ptrInface->ptrExternData));
			ptrInface->ptrExternData = NULL_PL;
		}
		PLSysAPI_FreeMemory(ptrInface);
	}
	HPL_Result __native_LoadLibrary_PL(HPPLEngine hEngine,void_pl * ptrEx,PL_EngineLibraryPlusNode * ptrNode,PL_native_ELoadLibrary * ptrLibParamer){
		PL_EngineState * ptrState;
		PL_OperatSysEnvSet * ptrSysEnv;
		PL_ConstSystemInfo * ptrInfo;
		PL_EngineLibraryHeavyInface * ptrLibInface;
//		PL_EngineLibraryPlusNode * ptrPlusNode;
		void_pl * ptrFunc;
		PLLibModuleHandle hModule;
		__Create_Library__PL__ creatfun;
		UTFSyschar_pl pPath[PL3DSystemFilePathNameMaxLength];
		intV_pl  iwPathSize;
		UTFSyschar_pl pPlusModelName[PL3DSystemFileFNameMaxLength];
		intV_pl  iwPlusModelNSize;
		UTFSyschar_pl * ptrConstCharRes;
		intV_pl   iwConstCharResSize;
		UTFSyschar_pl * ptrLable;
		intV_pl   iwLableSize;
		intV_pl   iwStrSize;
		PLConstCharTableHandle hConstCharhandle;
		PLConstCharTableHandle hDbgCharTable;
		PLFileCFGHandle hCFGHandle;

		ptrState = (PL_EngineState *)hEngine;
		if((ptrState==NULL_PL) || (ptrState->bInitialize==true_pl) || (ptrLibParamer->hCFGHandle==NULL_PL) || (ptrNode==NULL_PL))
			return HPLResult_Fail;
		ptrLibInface = NULL_PL;
		hConstCharhandle = ptrState->hSysConstCharTable;
		hDbgCharTable    = ptrState->hDbgConstCharTable;
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		hCFGHandle = ptrLibParamer->hCFGHandle;
		if(hCFGHandle==NULL_PL)
			return HPLResult_Fail;
		ptrLable = PLSysAPI_Sys_GetConstCharID(hConstCharhandle,PLSys_ConstChar_PlusLable,&iwLableSize);

		PLSysAPI_SysStringClear(pPath,PL3DSystemFilePathNameMaxLength);
		iwPathSize = ptrSysEnv->iwPlusCWDSize;
		PLSysAPI_SysStringCpy(pPath,ptrSysEnv->pPlusCWD,iwPathSize);
		ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(hConstCharhandle,ptrLibParamer->iPlusID,&iwConstCharResSize);
		//clear plus file name buffer
		PLSysAPI_SysStringClear(pPlusModelName,PL3DSystemFileFNameMaxLength);
		//get plus file name
		iwPlusModelNSize = PLSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_pl UTFSyschar_pl *)ptrLable,iwLableSize,
							(const_pl UTFSyschar_pl *)ptrConstCharRes,iwConstCharResSize,pPlusModelName,PL3DSystemFileFNameMaxLength);
		//link path name and plus file name
		PLSysAPI_SysStringCpy(&(pPath[iwPathSize]),pPlusModelName,iwPlusModelNSize);
	//	iwStrSize = PLSysAPI_Sys_GetCfgFiletoString(hCFGHandle,(const_pl UTFSyschar_pl *)ptrLable,iwLableSize,(const_pl UTF16char_pl *)ptrConstCharRes,iwConstCharResSize,&(pPath[iwPathSize]),(PL3DSystemFilePathNameMaxLength - iwPathSize));
		iwPathSize += iwStrSize;
		if((HResulPL_FAILED(PLSysAPI_Lib_OpenLibrary(&hModule,pPath,iwPathSize,0))==false_pl) && (hModule!=PLLibraryHandle_Invalid)){
			//printf("load %s ok\n",pPath);
			ptrFunc = PLSysAPI_Lib_SearchLibraryObject(hModule,(const_pl UTFSyschar_pl *)(ptrState->PlusStandard.pCreateEnterName),ptrState->PlusStandard.iwEnterNSize);
			creatfun = (__Create_Library__PL__)ptrFunc;
			if(creatfun!=NULL_PL){
				//printf("call lib creatfun\n");
				ptrLibInface = (PL_EngineLibraryHeavyInface*)creatfun(hEngine,NULL_PL);
				if(ptrLibInface!=NULL_PL){
					ptrLibInface->hModuleHandle = hModule;
					if(ptrLibInface->InstallLibraryPL){
						ptrLibInface->InstallLibraryPL(hEngine,(PLLibraryHandle)(ptrLibInface),NULL_PL);
					}
				}
			}else{
				PLSysAPI_Lib_CloseLibrary(hModule);
			}
		}
		ptrNode->iNSize = PLSysAPI_SysString_findMarkCharR(pPlusModelName,iwPlusModelNSize,PLWChar_Point);
		ptrNode->cbSize = PL_CompilerAllocSize(PL_EngineLibraryPlusNode);
		ptrNode->ptrNext = NULL_PL;
		ptrNode->ptrInface = ptrLibInface;
		PLSysAPI_SysStringClear(ptrNode->ptrName,PL3DSystemModuleNameMaxLength);
		ptrNode->iNSize = (ptrNode->iNSize<0 ? iwPlusModelNSize : (ptrNode->iNSize + 1));
		PLSysAPI_SysStringCpy(ptrNode->ptrName,pPlusModelName,ptrNode->iNSize);
		return HPLResult_OK;
	}
	HPL_Result    __native_ReleaseLoadLibrary_PL(HPPLEngine hEngine,void_pl * ptrEx,PL_EngineLibraryPlusNode * ptrNode){
		HPL_Result hResult;
		PLLibModuleHandle hModule;
		PL_EngineLibraryHeavyInface * ptrInface;
		hResult = HPLResult_Fail;
		if((ptrNode==NULL_PL) || (ptrNode->ptrInface==NULL_PL))
			return HPLResult_Fail;
		ptrInface = ptrNode->ptrInface;
		ptrNode->ptrInface = NULL_PL;
		hModule = ptrInface->hModuleHandle;
		if(ptrInface->UnInstallLibraryPL!=NULL_PL)
			ptrInface->UnInstallLibraryPL(hEngine,ptrInface,NULL_PL);
		if(ptrInface->Destory_LibraryPL!=NULL_PL)
			ptrInface->Destory_LibraryPL(hEngine,ptrInface,NULL_PL);
		if(hModule!=PLLibraryHandle_Invalid){
			PLSysAPI_Lib_CloseLibrary(hModule);
		}
		hResult = HPLResult_OK;
		return hResult;
	}

