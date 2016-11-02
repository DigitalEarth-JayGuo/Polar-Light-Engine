/*
 * PLEngineResourceManagerPackage.cpp
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "PLEngineResourceManagerPackage.h"

PLLibraryHandle CreateLibraryPL(HPPLEngine hEngine,void_pl * ptrEx){
	PL_ResourceManagerLibraryHeavy 		 * ptrInface;
	PL_ResourceManagerLibraryFunTable    * ptrTable;
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
	PLConstCharTableHandle hECTHandle;
	PLFileCFGHandle hCFGHandle;
	PLConstCharTableHandle hResourceMgrHandle;
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

	iInfaceSize = PL_CompilerAllocSize(PL_ResourceManagerLibraryHeavy);
	ptrInface   = (PL_ResourceManagerLibraryHeavy *)PLSysAPI_Mem_AllocateMemoryPool(iInfaceSize);
	if(ptrInface==NULL_PL)
		return NULL_PL;
	PLSysAPI_MemoryClearZero((void_pl *)(ptrInface),iInfaceSize);
	iTableSize = PL_CompilerAllocSize(PL_ResourceManagerLibraryFunTable) + PL_CompilerAllocSize(fun_pl) * PLRMgr_Table_FunMaxSize;
	ptrTable   = (PL_ResourceManagerLibraryFunTable *)PLSysAPI_Mem_AllocateMemoryPool(iTableSize);
	if(ptrTable == NULL_PL){
		if(ptrInface!=NULL_PL){
			PLSysAPI_Mem_FreeMemoryPool(ptrInface);
			ptrInface = NULL_PL;
		}
		return NULL_PL;
	}
	PLSysAPI_MemoryClearZero((void_pl *)(ptrTable),iTableSize);
	ptrTable->Inface.cbSize 	= iTableSize;
	ptrTable->Inface.iFunCount  = PLRMgr_Table_FunMaxSize;
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
	ptrInface->iLogCWDSize = ptrSysEnv->iCWDSize;
	PLSysAPI_MemoryCpy(ptrInface->pLogCWD,ptrSysEnv->pCWD,ptrInface->iLogCWDSize);


	ptrConstCT = PLSysAPI_Sys_GetConstCharID(hECTHandle,PLSys_ConstChar_EngineCFG,&iConstCTSize);
	PLSysAPI_MemoryClearZero(pPath,PL3DSystemFileNameMaxLength);
	iPathSize = ptrSysEnv->iCWDSize;
	PLSysAPI_MemoryCpy(pPath,ptrSysEnv->pCWD,iPathSize);
	if((ptrConstCT != NULL_PL) && (iConstCTSize>0)){
		PLSysAPI_MemoryCpy(&(pPath[iPathSize]),ptrConstCT,iConstCTSize);
		iPathSize += iConstCTSize;
	}
	hCFGHandle = PLSysAPI_Sys_OpenCfgFile(pPath,iPathSize);
//	if(hCFGHandle != NULL_PL){
		//PLSysAPI_Sys_GetConstCharID(hECTHandle,, );
//	}
	if(hCFGHandle != NULL_PL){
		PLSysAPI_Sys_CloseCfgFile(hCFGHandle);
		hCFGHandle = NULL_PL;
	}
	ptrInface->hSysConstCharTable = NULL_PL;
	ptrInface->hEngine            = hEngine;
	g_hLibraryHandle_Resource = ptrInface;
	return (PLLibraryHandle)ptrInface;
}
bool_pl InstallLibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
	bool_pl bInstall;
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
	bInstall = false_pl;
	if((hAndle == NULL_PL) || (hEngine == NULL_PL))
		return bInstall;
	ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

	PLSysAPI_RMgr_CreatePolygonManager 			= Eg_CreatePolygonManager;
	PLSysAPI_RMgr_DestoryPolygonManager 		= Eg_DestoryPolygonManager;
	PLSysAPI_RMgr_CreatePolygonMgrObject 		= Eg_CreatePolygonMgrObject;
	PLSysAPI_RMgr_OpenPolygonMgrObject			= Eg_OpenPolygonMgrObject;
	PLSysAPI_RMgr_ReleasePolygonMgrObject		= Eg_ReleasePolygonMgrObject;
	PLSysAPI_RMgr_DestoryPolygonMgrObject		= Eg_DestoryPolygonMgrObject;
	PLSysAPI_RMgr_PushPolygonRTaskerQueue		= Eg_PushPolygonRTaskerQueue;
	PLSysAPI_RMgr_PushPolygonRTaskerQueueN		= Eg_PushPolygonRTaskerQueueN;
	PLSysAPI_RMgr_RefurbishPolygonRBgDispose	= Eg_RefurbishPolygonRBackgroundDispose;

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

	PLSysAPI_RMgr_CreatePolygonManager 			= NULL_PL;
	PLSysAPI_RMgr_DestoryPolygonManager 		= NULL_PL;
	PLSysAPI_RMgr_CreatePolygonMgrObject 		= NULL_PL;
	PLSysAPI_RMgr_OpenPolygonMgrObject			= NULL_PL;
	PLSysAPI_RMgr_ReleasePolygonMgrObject		= NULL_PL;
	PLSysAPI_RMgr_DestoryPolygonMgrObject		= NULL_PL;
	PLSysAPI_RMgr_PushPolygonRTaskerQueue		= NULL_PL;
	PLSysAPI_RMgr_PushPolygonRTaskerQueueN		= NULL_PL;
	PLSysAPI_RMgr_RefurbishPolygonRBgDispose	= NULL_PL;




	return HPLResult_OK;
}
void_pl	Destory_LibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
	PL_ResourceManagerLibraryHeavy * ptrInface;
	ptrInface = (PL_ResourceManagerLibraryHeavy *)hAndle;
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
