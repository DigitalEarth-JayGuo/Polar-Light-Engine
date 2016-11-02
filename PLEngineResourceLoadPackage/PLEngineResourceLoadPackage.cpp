/*
 * PLEngineResrouceLoadPackage.cpp
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "PLEngineResourceLoadPackage.h"
	PLLibraryHandle CreateLibraryPL(HPPLEngine hEngine,void_pl * ptrEx){
		PL_ResourceLoadLibraryHeavy * ptrInface;
		PL_ResourceLoadLibraryFunTable    * ptrTable;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		PLConstCharTableHandle hECTHandle;
//		PLFileCFGHandle hCFGHandle;
		PLConstCharTableHandle hResourceLoadHandle;
		char_pl pPath[PL3DSystemFileNameMaxLength];
		intV_pl iPathSize;
		intV_pl iInfaceSize;
		intV_pl iTableSize;
		void_pl * ptrConstCT;
		int iConstCTSize;
		if((hEngine == NULL_PL) || (g_hLibraryHandle_Resource != NULL_PL))
			return NULL_PL;

		ptrInface = NULL_PL;
		ptrTable  = NULL_PL;
		ptrSysEnv  = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo    = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		hECTHandle = PLSysAPI_Sys_GetEngineConstCharTable(hEngine);
		if((ptrSysEnv == NULL_PL) || (ptrInfo == NULL_PL) || (hECTHandle == NULL_PL))
			return NULL_PL;

		iInfaceSize = PL_CompilerAllocSize(PL_ResourceLoadLibraryHeavy);
		ptrInface   = (PL_ResourceLoadLibraryHeavy *)PLSysAPI_Mem_AllocateMemoryPool(iInfaceSize);
		if(ptrInface==NULL_PL)
			return NULL_PL;
		PLSysAPI_MemoryClearZero((void_pl *)(ptrInface),iInfaceSize);
		iTableSize = PL_CompilerAllocSize(PL_ResourceLoadLibraryFunTable) + PL_CompilerAllocSize(fun_pl) * PLRL_Table_FunMaxSize;
		ptrTable   = (PL_ResourceLoadLibraryFunTable *)PLSysAPI_Mem_AllocateMemoryPool(iTableSize);
		if(ptrTable == NULL_PL){
			if(ptrInface!=NULL_PL){
				PLSysAPI_Mem_FreeMemoryPool(ptrInface);
				ptrInface = NULL_PL;
			}
			return NULL_PL;
		}
		PLSysAPI_MemoryClearZero((void_pl *)(ptrTable),iTableSize);
		ptrTable->Inface.cbSize 	= iTableSize;
		ptrTable->Inface.iFunCount  = PLRL_Table_FunMaxSize;
		ptrInface->Inface.cbSize 			 = iInfaceSize;
		ptrInface->Inface.hModuleHandle 	 = PLLibraryHandle_Invalid;
		ptrInface->Inface.Destory_LibraryPL  = Destory_LibraryPL;
		ptrInface->Inface.UnInstallLibraryPL = UnInstallLibraryPL;
		ptrInface->Inface.InstallLibraryPL   = InstallLibraryPL;
		ptrInface->Inface.ptrFunTable 		 = (PL_EngineLibraryFunTable *)ptrTable;
		ptrInface->Inface.ptrExternData 	 = NULL_PL;

		ptrInface->iCWDSize = ptrSysEnv->iCWDSize;
		PLSysAPI_MemoryCpy(ptrInface->pCWD,ptrSysEnv->pCWD,ptrInface->iCWDSize);

		ptrInface->iResourceCWDSize = ptrSysEnv->iResourceCWDSize;
		PLSysAPI_MemoryCpy(ptrInface->pResourceCWD,ptrSysEnv->pResourceCWD,ptrInface->iResourceCWDSize);


		ptrConstCT = PLSysAPI_Sys_GetConstCharID(hECTHandle,PLSys_ConstChar_EngineCFG,&iConstCTSize);
		PLSysAPI_MemoryClearZero(pPath,PL3DSystemFileNameMaxLength);
		iPathSize = ptrSysEnv->iCWDSize;
		PLSysAPI_MemoryCpy(pPath,ptrSysEnv->pCWD,iPathSize);
		if((ptrConstCT != NULL_PL) && (iConstCTSize>0)){
			PLSysAPI_MemoryCpy(&(pPath[iPathSize]),ptrConstCT,iConstCTSize);
			iPathSize += iConstCTSize;
		}
//		hCFGHandle = PLSysAPI_Sys_OpenCfgFile(pPath,iPathSize);



		iPathSize = ptrInface->iCWDSize;
		PLSysAPI_MemoryClearZero(pPath,PL3DSystemFileNameMaxLength);
		PLSysAPI_MemoryCpy(pPath,ptrInface->pCWD,iPathSize);
		PLSysAPI_MemoryCpy(&(pPath[iPathSize]),PLScript_ConstID_ResourceLoadConstFile_Str
								,PL_CompilerStringSize(PLScript_ConstID_ResourceLoadConstFile_Str));
		iPathSize += PL_CompilerStringSize(PLScript_ConstID_ResourceLoadConstFile_Str);

		hResourceLoadHandle = PLSysAPI_Sys_OpenConstCharTable(pPath,iPathSize);
		if(hResourceLoadHandle==NULL_PL){
			PLSysAPI_Mem_FreeMemoryPool(ptrTable);
			ptrTable = NULL_PL;
			ptrInface->Inface.ptrFunTable = NULL_PL;
			PLSysAPI_Mem_FreeMemoryPool(ptrInface);
			ptrInface = NULL_PL;
			return NULL_PL;
		}
		ptrInface->hSysConstCharTable = hResourceLoadHandle;
		ptrInface->hEngine            = hEngine;
		g_hLibraryHandle_Resource = ptrInface;
		//		PLConstCharTableHandle g_hSysConstCharTable
		return (PLLibraryHandle)ptrInface;
	}
	bool_pl 	InstallLibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
		bool_pl bInstall;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		bInstall = false_pl;
		if((hAndle == NULL_PL) || (hEngine == NULL_PL))
			return bInstall;
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

		PLSysAPI_RC_CreatePackage				= Eg_CreatePackage;
		PLSysAPI_RC_OpenPackage  				= Eg_OpenPackage;
		PLSysAPI_RC_LoadPackageFTable			= Eg_LoadPackageFTable;
		PLSysAPI_RC_CreatePackageFTFindMap		= Eg_CreatePackageFTFindMap;
		PLSysAPI_RC_existPackageFTable			= Eg_existPackageFTable;
		PLSysAPI_RC_existPackageFTFindMap 		= Eg_existPackageFTFindMap;
		PLSysAPI_RC_GetPackageFileItemResType   = Eg_GetPackageFileItemResType;
		PLSysAPI_RC_GetPackageFileItemName      = Eg_GetPackageFileItemName;
		PLSysAPI_RC_GetPackageFileSize			= Eg_GetPackageFileSize;
		PLSysAPI_RC_GetPackageFileItemObject	= Eg_GetPackageFileItemObject;
		PLSysAPI_RC_GetPackageFileItemObjectI	= Eg_GetPackageFileItemObjectI;
		PLSysAPI_RC_GetPackageFileItemCount		= Eg_GetPackageFileItemCount;
		PLSysAPI_RC_GetPackageFileItemSize		= Eg_GetPackageFileItemSize;
		PLSysAPI_RC_ReadPackageFileItemData     = Eg_ReadPackageFileItemData;
		PLSysAPI_RC_ClosePackage 				= Eg_ClosePackage;
		PLSysAPI_RC_CreateResDataSystemCrParamer    	= Eg_CreateResDataSystemCrParamer;
		PLSysAPI_RC_DestoryResDataSystemCrParamer		= Eg_DestoryResDataSystemCrParamer;
		PLSysAPI_RC_CreateResourceDataSystem			= Eg_CreateResourceDataSystem;
		PLSysAPI_RC_CreateResourceDataSystemPKGMapping	= Eg_CreateResourceDataSystemPKGMapping;
		PLSysAPI_RC_ReleaseResourceDataSystemPKGMapping	= Eg_ReleaseResourceDataSystemPKGMapping;
		PLSysAPI_RC_ReleaseResourceDataSystemPKGMappingN= Eg_ReleaseResourceDataSystemPKGMappingN;
		PLSysAPI_RC_MappinResourceDataSystemPKG			= Eg_MappinResourceDataSystemPKG;
		PLSysAPI_RC_MappingResourceDataSystemPKGItem	= Eg_MappingResourceDataSystemPKGItem;
		PLSysAPI_RC_RefurbishResourceDataMgrSystem		= Eg_RefurbishResourceDataMgrSystem;
		PLSysAPI_RC_DestoryResourceDataSystem			= Eg_DestoryResourceDataSystem;
		PLSysAPI_RC_OpenResourceDataItem				= Eg_OpenResourceDataItem;
		PLSysAPI_RC_CloseResourceDataItem				= Eg_CloseResourceDataItem;

		return bInstall;
	}
	HPL_Result UnInstallLibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
		HPL_Result hResult;
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		hResult = HPLResult_Fail;
		if((hEngine == NULL_PL) || (hAndle == NULL_PL))
			return hResult;
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		PLSysAPI_RC_CreatePackage				= NULL_PL;
		PLSysAPI_RC_OpenPackage  				= NULL_PL;
		PLSysAPI_RC_LoadPackageFTable			= NULL_PL;
		PLSysAPI_RC_CreatePackageFTFindMap		= NULL_PL;
		PLSysAPI_RC_existPackageFTable			= NULL_PL;
		PLSysAPI_RC_existPackageFTFindMap 		= NULL_PL;
		PLSysAPI_RC_GetPackageFileItemResType   = NULL_PL;
		PLSysAPI_RC_GetPackageFileItemName 		= NULL_PL;
		PLSysAPI_RC_GetPackageFileSize			= NULL_PL;
		PLSysAPI_RC_GetPackageFileItemObject	= NULL_PL;
		PLSysAPI_RC_GetPackageFileItemObjectI	= NULL_PL;
		PLSysAPI_RC_GetPackageFileItemCount		= NULL_PL;
		PLSysAPI_RC_GetPackageFileItemSize		= NULL_PL;
		PLSysAPI_RC_ReadPackageFileItemData     = NULL_PL;
		PLSysAPI_RC_ClosePackage 				= NULL_PL;

		PLSysAPI_RC_CreateResDataSystemCrParamer    	= NULL_PL;
		PLSysAPI_RC_DestoryResDataSystemCrParamer		= NULL_PL;
		PLSysAPI_RC_CreateResourceDataSystem			= NULL_PL;
		PLSysAPI_RC_CreateResourceDataSystemPKGMapping	= NULL_PL;
		PLSysAPI_RC_ReleaseResourceDataSystemPKGMapping	= NULL_PL;
		PLSysAPI_RC_ReleaseResourceDataSystemPKGMappingN= NULL_PL;
		PLSysAPI_RC_MappinResourceDataSystemPKG			= NULL_PL;
		PLSysAPI_RC_MappingResourceDataSystemPKGItem	= NULL_PL;
		PLSysAPI_RC_RefurbishResourceDataMgrSystem		= NULL_PL;
		PLSysAPI_RC_DestoryResourceDataSystem			= NULL_PL;
		PLSysAPI_RC_OpenResourceDataItem				= NULL_PL;
		PLSysAPI_RC_CloseResourceDataItem				= NULL_PL;
		return HPLResult_OK;
	}
	void_pl	Destory_LibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
		PL_ConstSystemInfo * ptrInfo;
		PL_OperatSysEnvSet * ptrSysEnv;
		PL_ResourceLoadLibraryHeavy * ptrInface;
		ptrInface = (PL_ResourceLoadLibraryHeavy *)hAndle;
		if((hEngine == NULL_PL) || (hAndle == NULL_PL))
			return;
		g_hLibraryHandle_Resource = NULL_PL;
		ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
		ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
		if(ptrInface->hSysConstCharTable!=NULL_PL){
			PLSysAPI_Sys_ReleaseConstCharTable(ptrInface->hSysConstCharTable);
			ptrInface->hSysConstCharTable = NULL_PL;
		}
		if(ptrInface->Inface.ptrFunTable!=NULL_PL){
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrInface->Inface.ptrFunTable));
			ptrInface->Inface.ptrFunTable = NULL_PL;
		}
		if(ptrInface->Inface.ptrExternData!=NULL_PL){
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrInface->Inface.ptrExternData));
			ptrInface->Inface.ptrExternData = NULL_PL;
		}
		PLSysAPI_Mem_FreeMemoryPool(ptrInface);
	}
