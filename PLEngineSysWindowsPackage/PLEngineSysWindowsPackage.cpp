/*
 * PLEngineWindowsPackage.cpp
 *
 *  Created on: 2009-10-27
 *      Author: Administrator
 */

#include "PLEngineSysWindowsPackage.h"
#include "EngineSysWindowsAPI.h"
PLLibraryHandle CreateLibraryPL(HPPLEngine hEngine,void_pl * ptrEx){
	PL_SysWindowsLibraryHeavy * ptrInface;
	PL_SysWindowsLibraryFunTable    * ptrTable;
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
	PLConstCharTableHandle hECTHandle;
//	PLFileCFGHandle hCFGHandle;
//	PLConstCharTableHandle hResourceLoadHandle;
//	char_pl pPath[PL3DSystemFileNameMaxLength];
	intV_pl iPathSize;
	intV_pl iInfaceSize;
	intV_pl iTableSize;
	void_pl * ptrConstCT;
	int iConstCTSize;
	if((hEngine == NULL_PL) || (g_hLibraryHandle_SysWindows != NULL_PL))
		return NULL_PL;

	ptrInface = NULL_PL;
	ptrTable  = NULL_PL;
	ptrSysEnv  = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo    = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
	hECTHandle = PLSysAPI_Sys_GetEngineConstCharTable(hEngine);
	if((ptrSysEnv == NULL_PL) || (ptrInfo == NULL_PL) || (hECTHandle == NULL_PL))
		return NULL_PL;


 	iInfaceSize = PL_CompilerAllocSize(PL_SysWindowsLibraryHeavy);
	ptrInface   = (PL_SysWindowsLibraryHeavy *)PLSysAPI_Mem_AllocateMemoryPool(iInfaceSize);
	if(ptrInface==NULL_PL)
		return NULL_PL;
	PLSysAPI_MemoryClearZero((void_pl *)(ptrInface),iInfaceSize);
/*	iTableSize = PL_CompilerAllocSize(PL_ResourceLoadLibraryFunTable) + PL_CompilerAllocSize(fun_pl) * PLRL_Table_FunMaxSize;
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
	*/
	return NULL_PL;
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
/*
	PLSysAPI_RMgr_CreatePolygonManager 			= Eg_CreatePolygonManager;
	PLSysAPI_RMgr_DestoryPolygonManager 		= Eg_DestoryPolygonManager;
	PLSysAPI_RMgr_CreatePolygonMgrObject 		= Eg_CreatePolygonMgrObject;
	PLSysAPI_RMgr_OpenPolygonMgrObject			= Eg_OpenPolygonMgrObject;
	PLSysAPI_RMgr_ReleasePolygonMgrObject		= Eg_ReleasePolygonMgrObject;
	PLSysAPI_RMgr_DestoryPolygonMgrObject		= Eg_DestoryPolygonMgrObject;
	PLSysAPI_RMgr_PushPolygonRTaskerQueue		= Eg_PushPolygonRTaskerQueue;
	PLSysAPI_RMgr_PushPolygonRTaskerQueueN		= Eg_PushPolygonRTaskerQueueN;
	PLSysAPI_RMgr_RefurbishPolygonRBgDispose	= Eg_RefurbishPolygonRBackgroundDispose;
*/
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
/*
	PLSysAPI_RMgr_CreatePolygonManager 			= NULL_PL;
	PLSysAPI_RMgr_DestoryPolygonManager 		= NULL_PL;
	PLSysAPI_RMgr_CreatePolygonMgrObject 		= NULL_PL;
	PLSysAPI_RMgr_OpenPolygonMgrObject			= NULL_PL;
	PLSysAPI_RMgr_ReleasePolygonMgrObject		= NULL_PL;
	PLSysAPI_RMgr_DestoryPolygonMgrObject		= NULL_PL;
	PLSysAPI_RMgr_PushPolygonRTaskerQueue		= NULL_PL;
	PLSysAPI_RMgr_PushPolygonRTaskerQueueN		= NULL_PL;
	PLSysAPI_RMgr_RefurbishPolygonRBgDispose	= NULL_PL;
*/

	return HPLResult_OK;
}
void_pl Destory_LibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
	PL_SysWindowsLibraryHeavy * ptrInface;

	ptrInface = (PL_SysWindowsLibraryHeavy *)hAndle;
	if((hEngine == NULL_PL) || (hAndle == NULL_PL))
		return;
	g_hLibraryHandle_SysWindows = NULL_PL;
	ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

	/*
	if(ptrInface->hSysConstCharTable!=NULL_PL){
		PLSysAPI_Sys_ReleaseConstCharTable(ptrInface->hSysConstCharTable);
		ptrInface->hSysConstCharTable = NULL_PL;
	}
	*/
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
