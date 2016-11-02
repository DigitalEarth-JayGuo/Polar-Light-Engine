/*
 * PLEngineScenePackage.cpp
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "PLEngineScenePackage.h"
PLLibraryHandle CreateLibraryPL(HPPLEngine hEngine,void_pl * ptrEx){
	PL_EngineLibraryHeavyInface * ptrInface;
	PL_EngineLibraryFunTable    * ptrTable;
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
//	AddresValue_pl  addresV;
	int_pl iAllocSize;
	int_pl iInfaceSize;
	int_pl iTableALlocSize;
	int_pl iTableSize;
	int_pl iFunCount;
	int_pl iCacheLineSize;
	if(hEngine == NULL_PL)
		return NULL_PL;
	ptrInface = NULL_PL;
	ptrTable  = NULL_PL;
	ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);
	iCacheLineSize = ptrInfo->iCacheLineSize;
	printf("CreateLibraryPL\n");
	iInfaceSize = PL_CompilerAllocSize(PL_EngineLibraryHeavyInface);


	ptrInface  = (PL_EngineLibraryHeavyInface *)PLSysAPI_Mem_AllocateMemoryPool(iInfaceSize);

//	iAllocSize = PLSysAPI_Alignment(iInfaceSize,iCacheLineSize) + iCacheLineSize;
//	ptrInface  = (PL_EngineLibraryHeavyInface *)PLSysAPI_AllocateMemory(iAllocSize);
	iFunCount  = 5;
	iTableALlocSize = PL_CompilerAllocSize(PL_EngineLibraryFunTable);
	iTableSize = iTableALlocSize + sizeof(fun_pl) * iFunCount;
	ptrTable   = (PL_EngineLibraryFunTable *)PLSysAPI_Mem_AllocateMemoryPool(iTableSize);
//	iTableALlocSize = PLSysAPI_Alignment(iTableSize,iCacheLineSize) + iCacheLineSize;
//	ptrTable   = (PL_EngineLibraryFunTable *)PLSysAPI_AllocateMemory(iTableALlocSize);

	if((ptrInface == NULL_PL) || (ptrTable == NULL_PL)){
		if(ptrInface!=NULL_PL){
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrInface);
			//PLSysAPI_FreeMemory((void_pl *)ptrInface);
			ptrInface = NULL_PL;
		}
		if(ptrTable!=NULL_PL){
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrTable);
			//PLSysAPI_FreeMemory((void_pl *)ptrTable);
			ptrTable = NULL_PL;
		}
		return NULL_PL;
	}

	PLSysAPI_MemoryClearZero((void_pl *)(ptrInface),iInfaceSize);
	PLSysAPI_MemoryClearZero((void_pl *)(ptrTable),iTableSize);
	ptrTable->cbSize = iTableSize;
	ptrTable->iFunCount = iFunCount;
	ptrInface->cbSize = iInfaceSize;
	ptrInface->hModuleHandle = PLLibraryHandle_Invalid;
	ptrInface->Destory_LibraryPL  = Destory_LibraryPL;
	ptrInface->UnInstallLibraryPL = UnInstallLibraryPL;
	ptrInface->InstallLibraryPL   = InstallLibraryPL;
	ptrInface->ptrFunTable = ptrTable;

	return (PLLibraryHandle)ptrInface;
}
bool_pl InstallLibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
	printf("InstallLibraryPL\n");
	if((hEngine == NULL_PL) || (hAndle == NULL_PL))
		return false_pl;

	ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

	return true_pl;
}
HPL_Result UnInstallLibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;
	if((hEngine == NULL_PL) || (hAndle == NULL_PL))
		return HPLResult_Fail;
	ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

	return HPLResult_OK;
}
void_pl Destory_LibraryPL(HPPLEngine hEngine,PLLibraryHandle hAndle,void_pl * ptrEx){
	PL_EngineLibraryHeavyInface * ptrInface;
	PL_ConstSystemInfo * ptrInfo;
	PL_OperatSysEnvSet * ptrSysEnv;

	printf("Destory_LibraryPL\n");
	ptrInface = (PL_EngineLibraryHeavyInface *)hAndle;
	if((ptrInface==NULL_PL) || (hEngine==NULL_PL))
		return;
	ptrSysEnv = PLSysAPI_Sys_GetOperatSystemEnv(hEngine);
	ptrInfo   = PLSysAPI_Sys_GetConstSystemInfo(hEngine);

	if(ptrInface->ptrFunTable!=NULL_PL){
		PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrInface->ptrFunTable));
		ptrInface->ptrFunTable = NULL_PL;
	}
	if(ptrInface->ptrExternData!=NULL_PL){
		PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrInface->ptrExternData));
		ptrInface->ptrExternData = NULL_PL;
	}
	PLSysAPI_Mem_FreeMemoryPool(ptrInface);
}
