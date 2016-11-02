/*
 * PLEngineResourcePKGAPI.cpp
 *
 *  Created on: 2009-10-20
 *      Author: Administrator
 */
#include "EngineResourceLoadAPI.h"
/*
	_PLE_lib_c _CallStack_default_ int_pl       __PLSysAPI_SystemIO_fwrite_(FILEStream * ptrStream,const_pl void_pl * ptrData,intV_pl iSize,intV_pl iWCount);
	_PLE_lib_c _CallStack_default_ lint_pl      __PLSysAPI_SystemIO_fseek_(FILEStream * ptrStream,lint_pl iMov,ePL_SysIOSeekMode eMode);
	_PLE_lib_c _CallStack_default_ void_pl      __PLSysAPI_SystemIO_fclose_(FILEStream * ptrStream);
	_PLE_lib_c _CallStack_default_ void_pl      __PLSysAPI_SystemIO_fflush_(FILEStream * ptrStream);
	_PLE_lib_c _CallStack_default_ lint_pl      __PLSysAPI_SystemIO_fGetFileCurPos_(FILEStream * ptrStream);
	_PLE_lib_c _CallStack_default_ int_pl       __PLSysAPI_SystemIO_GetCurWD_(char_pl * ptrCurWD,int_pl iMaxLength);

	#define PLSysAPI_SystemIO_fread             __PLSysAPI_SystemIO_fread_
	#define PLSysAPI_SystemIO_fwrite            __PLSysAPI_SystemIO_fwrite_
	#define PLSysAPI_SystemIO_fseek             __PLSysAPI_SystemIO_fseek_
	#define PLSysAPI_SystemIO_fclose            __PLSysAPI_SystemIO_fclose_
	#define PLSysAPI_SystemIO_fflush            __PLSysAPI_SystemIO_fflush_
	#define PLSysAPI_SystemIO_fGetFileCurPos    __PLSysAPI_SystemIO_fGetFileCurPos

 * */

HPKGObjAndle Eg_CreatePackage(const_pl char_pl * ptrKey,intV_pl iKeySize,intV_pl iMode,intV_pl iStoreMode){
	PL_PackageObjectState * ptrObject;
	PL_RLPoolMap * ptrListMap;
	char_pl tBuffer[PL3DSystemFileNameMaxLength];
	intV_pl iBuffSize;
	PLDeviceHandle hFileAndle;
	intV_pl iCount;
	PLLibraryHandle hAndle;
	PL_ResourceLoadLibraryHeavy * ptrInface;
	uintV_pl uFileFlage;
	uint_pl  uFileMode;

	ptrObject = NULL_PL;
	if((ptrKey == NULL_PL) || (iKeySize<=0) || ((hAndle = Eg_GetLibraryHandle_global())==NULL_PL))
		return NULL_PL;
	if((iMode & PLLR_ConstID_PackageOpenMode_NotCreateFTable) == PLLR_ConstID_PackageOpenMode_NotCreateFTable){
		iMode |= PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap;
	}
	ptrInface = (PL_ResourceLoadLibraryHeavy *)hAndle;
	PLSysAPI_MemoryClearZero(tBuffer,PL3DSystemFileNameMaxLength);
	iBuffSize = ptrInface->iResourceCWDSize;
	PLSysAPI_MemoryCpy(tBuffer,ptrInface->pResourceCWD,iBuffSize);
	PLSysAPI_MemoryCpy(&(tBuffer[iBuffSize]),ptrKey,iKeySize);
	iBuffSize+=iKeySize;
	iMode = (iMode & PLRL_ConstID_PackageOpenMode_UserDefineRangeMark) | PLLR_ConstID_PackageOpenMode_CreateNewPackage;

	uFileFlage = (PLSysIO_Const_OpenMode_CreatAlways | PLSysIO_Const_OpenOperat_Write);
	uFileMode  = (PLSysIO_Const_Att_UGRead | PLSysIO_Const_Att_UGWrite | PLSysIO_Const_Att_UGExecute | PLSysIO_Const_Att_URead | PLSysIO_Const_Att_UWrite | PLSysIO_Const_Att_UExecute);
	hFileAndle = NULL_PL;
	if(HResulPL_FAILED(PLSysAPI_SystemIO_Create(&hFileAndle,tBuffer,iBuffSize,uFileFlage,uFileMode,NULL_PL)) == true_pl){
		if(hFileAndle != NULL_PL){
			PLSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_PL;
		}
		return NULL_PL;
	}

//	ptrObject = (PL_PackageObjectState *) (((iMode & PLRL_ConstID_PackageOpenMode_LocalAllocate) == PLRL_ConstID_PackageOpenMode_LocalAllocate)
//						? PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_PackageObjectState))
//						: PLSysAPI_Mem_AllocateMemoryPool(PL_CompilerAllocSize(PL_PackageObjectState)));
	ptrObject = (PL_PackageObjectState *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_PackageObjectState));
	if((iMode & PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap) == PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap){
		ptrListMap = (PL_RLPoolMap *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_RLPoolMap));
	}
	if((ptrObject == NULL_PL)  || ((((iMode & PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap) != PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap) ) && (ptrListMap == NULL_PL))){
		if(ptrObject == NULL_PL){
			PLSysAPI_Mem_TLPLreeMemoryPool(ptrObject);
			ptrObject = NULL_PL;
		}
		PLSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_PL;
		return ptrObject;
	}
	PLSysAPI_MemoryClearZero(ptrObject,PL_CompilerAllocSize(PL_PackageObjectState));
	if(ptrListMap != NULL_PL){
		PLSysAPI_MemoryClearZero(ptrListMap,PL_CompilerAllocSize(PL_RLPoolMap));
	}
	ptrObject->ptrListMap 	= ptrListMap;

	ptrObject->header.uFID 	= PLRL_ConstID_PackageFileID;
	ptrObject->header.uLVer	= 0;
	ptrObject->header.uHVer	= 1;
	ptrObject->iMode 		= iMode;
	ptrObject->hFileAndle   = hFileAndle;
	ptrObject->iMode = iMode;
	if(ptrListMap != NULL_PL){
		ptrListMap->iSlotMapMaxSize  = PLRL_ConstID_PackageFileItemSlotMapMaxSize;
	//	ptrObject->ListMap.iSpeedupMOD      = PLRL_ConstID_PackageFileItemSlotMapSpeedupMOD;
		ptrListMap->hashfunc 	 	= __native_hash;
		ptrListMap->insertfunc    	= (__Rc_InsertFITableMapFunc__PL__)__native_InsertFITableMap;
		ptrListMap->removefunc 	 	= (__Rc_RemoveFITableMapFunc__PL__)__native_RemoveFITableMap;
		ptrListMap->removeallfunc 	= (__Rc_RemoveAllFITableMapFunc__PL__)__native_RemoveAllFITableMap;
		ptrListMap->destoryfunc   	= (__Rc_DestoryFITableMapFunc__PL__)__native_DestoryFITableMap;
		ptrListMap->destoryallfunc	= (__Rc_DestoryAllFITableMapFunc__PL__)__native_DestoryAllFITableMap;
		ptrListMap->searchtablefunc  = (__Rc_SearchFITableMapFunc__PL__)__native_SearchFITableMap;
		ptrListMap->getcountfunc     = (__Rc_GetCountFITableMapFunc__PL__)__native_GetCountFITableMap;
		ptrListMap->iStoreMode       = *((intV_pl *)(&(ptrObject->header.iLStoreModeF)));
		for(iCount = 0;iCount < ptrListMap->iSlotMapMaxSize;iCount++){
			PLSysAPI_Syn_InitializeRWLockWF(ptrListMap->lockList[iCount]);
			//ptrObject->ListMap.lockList[iCount]  = PLSyn_Const_SynSpinLockPass;
			ptrListMap->ptrRLItem[iCount] = NULL_PL;
		}
	}
	return (HPKGObjAndle)ptrObject;
}

HPKGObjAndle Eg_OpenPackage(const_pl char_pl * ptrKey,intV_pl iKeySize,intV_pl iMode){
	PL_PackageObjectState * ptrObject;
	char_pl tBuffer[PL3DSystemFileNameMaxLength];
	PL_ResourceLoadLibraryHeavy * ptrInface;
	PL_RLItem * ptrRLItem;
	PL_RLPKFileTableItem * ptrRLPKFItem;
	PL_RLPoolMap * ptrListMap;
	intV_pl iBuffSize;
	int32_pl iTableAlloc;
	int32_pl iTableMapAlloc;
	PLDeviceHandle hFileAndle;
	lint_pl lMov;
	lint_pl lPos;
	intV_pl iPos;
	intV_pl iCount;
	uintV_pl uFileFlage;
	uint_pl  uFileMode;
	PLLibraryHandle hAndle;
	void_pl * ptrFileTable;
	intV_pl iRRSize;

	ptrObject = NULL_PL;
	if((ptrKey==NULL_PL) || (iKeySize<=0) || ((hAndle = Eg_GetLibraryHandle_global())==NULL_PL))
		return NULL_PL;
	iMode &= PLRL_ConstID_PackageOpenMode_UserDefineRangeMark;
	ptrInface = (PL_ResourceLoadLibraryHeavy *)hAndle;
	PLSysAPI_MemoryClearZero(tBuffer,PL3DSystemFileNameMaxLength);
	iBuffSize = ptrInface->iResourceCWDSize;
	PLSysAPI_MemoryCpy(tBuffer,ptrInface->pResourceCWD,iBuffSize);
	PLSysAPI_MemoryCpy(&(tBuffer[iBuffSize]),ptrKey,iKeySize);
	iBuffSize+=iKeySize;

	uFileFlage = (PLSysIO_Const_OpenMode_NotCreat | PLSysIO_Const_OpenOperat_Read);
	uFileMode  = (PLSysIO_Const_Att_UGRead | PLSysIO_Const_Att_UGExecute | PLSysIO_Const_Att_URead | PLSysIO_Const_Att_UExecute);
	hFileAndle = NULL_PL;
	ptrListMap = NULL_PL;
	if(HResulPL_FAILED(PLSysAPI_SystemIO_Open(&hFileAndle,tBuffer,iBuffSize,uFileFlage,uFileMode,NULL_PL)) == true_pl){
		if(hFileAndle != NULL_PL){
			PLSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_PL;
		}
		return NULL_PL;
	}
	if((iMode & PLLR_ConstID_PackageOpenMode_NotCreateFTable) == PLLR_ConstID_PackageOpenMode_NotCreateFTable){
		iMode |= PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap;
	}
//	ptrObject = (PL_PackageObjectState *) (((iMode & PLRL_ConstID_PackageOpenMode_LocalAllocate) == PLRL_ConstID_PackageOpenMode_LocalAllocate)
//						? PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_PackageObjectState))
//						: PLSysAPI_Mem_AllocateMemoryPool(PL_CompilerAllocSize(PL_PackageObjectState)));
	ptrObject = (PL_PackageObjectState *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_PackageObjectState));
	if((iMode & PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap) == PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap){
		ptrListMap = (PL_RLPoolMap *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_RLPoolMap));
	}
	if((ptrObject == NULL_PL) || ((((iMode & PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap) != PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap) ) && (ptrListMap == NULL_PL))){
		if(ptrObject == NULL_PL){
			PLSysAPI_Mem_TLPLreeMemoryPool(ptrObject);
			ptrObject = NULL_PL;
		}
		PLSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_PL;
		return ptrObject;
	}
	PLSysAPI_MemoryClearZero(ptrObject,PL_CompilerAllocSize(PL_PackageObjectState));
	if(ptrListMap != NULL_PL){
		PLSysAPI_MemoryClearZero(ptrListMap,PL_CompilerAllocSize(PL_RLPoolMap));
	}
	ptrObject->ptrListMap = ptrListMap;
	if((HResulPL_FAILED(PLSysAPI_SystemIO_Read(hFileAndle,&(ptrObject->header),
			PL_CompilerAllocSize(PL_RLPackageFileHeader),&iRRSize,NULL_PL)) == true_pl)
			|| (PL_CompilerAllocSize(PL_RLPackageFileHeader) != iRRSize)
			|| (ptrObject->header.uFID != PLRL_ConstID_PackageFileID)
			|| ((lMov = *((lint_pl *)(&(ptrObject->header.iLTableSecOffset))))<=0)
			|| (HResulPL_FAILED(PLSysAPI_SystemIO_Seek(hFileAndle,*((lint_pl *)(&(ptrObject->header.iLTableSecOffset)))
					,&lPos,PLSys_Const_SystemIO_Seek_Set,NULL_PL))==true_pl)
			|| (*((lint_pl *)(&(ptrObject->header.iLTableSecOffset))) != lPos)){
		if(ptrObject->ptrListMap!=NULL_PL){
			PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)(ptrObject->ptrListMap));
			ptrObject->ptrListMap = NULL_PL;
		}
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrObject);
		ptrObject = NULL_PL;
		PLSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_PL;
		return NULL_PL;
	}
	ptrObject->iMode = iMode;
	ptrObject->iFPLength		= ptrInface->iResourceCWDSize;
	PLSysAPI_MemoryCpy(ptrObject->pFullPath,ptrInface->pResourceCWD,ptrObject->iFPLength);
	iPos = PLSysAPI_Ansi_findMarkCharR(ptrKey,iKeySize,PLSys_ConstChar_ExpandSplitSymbol);
	if(iPos<=0){
		iPos = iKeySize;
	}
	PLSysAPI_MemoryCpy(&(ptrObject->pFullPath[ptrObject->iFPLength]),ptrKey,iPos);
	ptrObject->iFPLength += iPos;
	ptrObject->hFileAndle = hFileAndle;

	if((iMode & PLLR_ConstID_PackageOpenMode_NotCreateFTable) != PLLR_ConstID_PackageOpenMode_NotCreateFTable){
		iTableAlloc    = ptrObject->header.iTableCount*ptrObject->header.iTableSize;
		iTableMapAlloc = ptrObject->header.iTableCount*PL_CompilerAllocSize(PL_RLItem);
		ptrObject->ptrTableItemData = PLSysAPI_Mem_TLSAllocateMemoryPool(iTableMapAlloc);
		ptrFileTable = PLSysAPI_Mem_TLSAllocateMemoryPool(iTableAlloc);

	//	PLSysAPI_SystemIO_Seek(hFileAndle,*((lint_pl *)(&(ptrObject->header.iLTableSecOffset))),&lPos,PLSys_Const_SystemIO_Seek_Set,NULL_PL);
	//	PLSysAPI_SystemIO_Read(hFileAndle,ptrFileTable,iTableAlloc,&iRRSize,NULL_PL);

		//ptrOCP
		if((ptrObject->ptrTableItemData == NULL_PL) || (ptrFileTable == NULL_PL) || (HResulPL_FAILED(PLSysAPI_SystemIO_Read(hFileAndle,ptrFileTable,iTableAlloc,&iRRSize,NULL_PL)) == true_pl) || (iRRSize != iTableAlloc)){
			if(ptrObject->ptrTableItemData != NULL_PL){
				PLSysAPI_Mem_TLPLreeMemoryPool(ptrObject->ptrTableItemData);
				ptrObject->ptrTableItemData = NULL_PL;
			}
			if(ptrFileTable != NULL_PL){
				PLSysAPI_Mem_TLPLreeMemoryPool(ptrFileTable);
				ptrFileTable = NULL_PL;
			}
			PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)(ptrObject->ptrListMap));
			ptrObject->ptrListMap = NULL_PL;
			PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrObject);
			ptrObject = NULL_PL;
			PLSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_PL;
			return NULL_PL;
		}

		PLSysAPI_MemoryClearZero(ptrObject->ptrTableItemData,iTableMapAlloc);
		ptrListMap->iSlotMapMaxSize  = PLRL_ConstID_PackageFileItemSlotMapMaxSize;
	//	ptrObject->ListMap.iSpeedupMOD      = PLRL_ConstID_PackageFileItemSlotMapSpeedupMOD;
		ptrListMap->hashfunc 	 	= __native_hash;
		ptrListMap->insertfunc    	= (__Rc_InsertFITableMapFunc__PL__)__native_InsertFITableMap;
		ptrListMap->removefunc 	 	= (__Rc_RemoveFITableMapFunc__PL__)__native_RemoveFITableMap;
		ptrListMap->removeallfunc 	= (__Rc_RemoveAllFITableMapFunc__PL__)__native_RemoveAllFITableMap;
		ptrListMap->destoryfunc   	= (__Rc_DestoryFITableMapFunc__PL__)__native_DestoryFITableMap;
		ptrListMap->destoryallfunc	= (__Rc_DestoryAllFITableMapFunc__PL__)__native_DestoryAllFITableMap;
		ptrListMap->searchtablefunc = (__Rc_SearchFITableMapFunc__PL__)__native_SearchFITableMap;
		ptrListMap->getcountfunc    = (__Rc_GetCountFITableMapFunc__PL__)__native_GetCountFITableMap;
		ptrListMap->iStoreMode      = *((intV_pl *)(&(ptrObject->header.iLStoreModeF)));
		ptrRLPKFItem = (PL_RLPKFileTableItem *)ptrFileTable;
		ptrRLItem    = (PL_RLItem *)(ptrObject->ptrTableItemData);
		for(iCount = 0;iCount < ptrObject->ptrListMap->iSlotMapMaxSize;iCount++){
			PLSysAPI_Syn_InitializeRWLockWF(ptrObject->ptrListMap->lockList[iCount]);
		}
		for(iCount = 0;iCount < ptrObject->header.iTableCount;iCount++){
			PLSysAPI_MemoryCpy(&(ptrRLItem[iCount].item),&(ptrRLPKFItem[iCount]),PL_CompilerAllocSize(PL_RLPKFileTableItem));
			ptrRLItem[iCount].iRLItemMode = PLRL_ConstID_IdenticalAllocate_PKGItem;
			if((ptrObject->iMode & PLRL_ConstID_PackageOpenMode_LocalAllocate) == PLRL_ConstID_PackageOpenMode_LocalAllocate){
				ptrRLItem[iCount].iRLItemMode |= PLRL_ConstID_LocalAllocate_PKGItem;
			}
			ptrRLItem[iCount].ptrNext   = NULL_PL;
			ptrRLItem[iCount].hFileAndle= ((ptrObject->header.iLStoreModeF & PLRL_ConstID_PKExteriorLinkIndex) != PLRL_ConstID_PKExteriorLinkIndex)	?  hFileAndle : NULL_PL;
			ptrRLItem[iCount].hPKGAndle = (HPKGObjAndle)ptrObject;
			if(ptrListMap!=NULL_PL)
				ptrListMap->insertfunc(ptrObject->ptrListMap,&(ptrRLItem[iCount]));
		}
		if(ptrFileTable == NULL_PL){
			PLSysAPI_Mem_TLPLreeMemoryPool(ptrFileTable);
			ptrFileTable = NULL_PL;
		}
	}

	return (HPKGObjAndle)ptrObject;
}
HPL_Result Eg_LoadPackageFTable(HPKGObjAndle hAndle){
	PL_PackageObjectState * ptrObject;
	void_pl * ptrFileTable;
	PL_RLPKFileTableItem * ptrRLPKFItem;
	PL_RLItem * ptrRLItem;

	HPL_Result hResult;
	lint_pl lPos;
	intV_pl iTableAlloc;
	intV_pl iTableMapAlloc;
	intV_pl iRRSize;
	hResult = HPLResult_OK;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if((ptrObject == NULL_PL) || (ptrObject->hFileAndle == NULL_PL) || (ptrObject->header.iTableSize<=0) || (ptrObject->header.iTableCount<=0))
		return HPLResult_Fail;
	if(ptrObject->ptrTableItemData != NULL_PL)
		return HPLResult_OK;
	if((HResulPL_FAILED(PLSysAPI_SystemIO_Seek(ptrObject->hFileAndle,*((lint_pl *)(&(ptrObject->header.iLTableSecOffset)))
			,&lPos,PLSys_Const_SystemIO_Seek_Set,NULL_PL))==true_pl) || ((*((lint_pl *)(&(ptrObject->header.iLTableSecOffset))) != lPos)))
		return HPLResult_Fail;

	iTableAlloc    = ptrObject->header.iTableCount*ptrObject->header.iTableSize;
	iTableMapAlloc = ptrObject->header.iTableCount*PL_CompilerAllocSize(PL_RLItem);
	ptrObject->ptrTableItemData = PLSysAPI_Mem_TLSAllocateMemoryPool(iTableMapAlloc);
	ptrFileTable = PLSysAPI_Mem_TLSAllocateMemoryPool(iTableAlloc);
	if((ptrObject->ptrTableItemData == NULL_PL) || (ptrFileTable == NULL_PL)
			|| (HResulPL_FAILED(PLSysAPI_SystemIO_Read(ptrObject->hFileAndle,ptrFileTable,iTableAlloc,&iRRSize,NULL_PL)) == true_pl)
			|| (iRRSize != iTableAlloc)){
		if(ptrObject->ptrTableItemData != NULL_PL){
			PLSysAPI_Mem_TLPLreeMemoryPool(ptrObject->ptrTableItemData);
			ptrObject->ptrTableItemData = NULL_PL;
		}
		if(ptrFileTable != NULL_PL){
			PLSysAPI_Mem_TLPLreeMemoryPool(ptrFileTable);
			ptrFileTable = NULL_PL;
		}
		return HPLResult_Fail;
	}
	PLSysAPI_MemoryClearZero(ptrObject->ptrTableItemData,iTableMapAlloc);
	ptrRLPKFItem = (PL_RLPKFileTableItem *)ptrFileTable;
	ptrRLItem    = (PL_RLItem *)(ptrObject->ptrTableItemData);

	for(intV_pl iCount = 0;iCount < ptrObject->header.iTableCount;iCount++){
		PLSysAPI_MemoryCpy(&(ptrRLItem[iCount].item),&(ptrRLPKFItem[iCount]),PL_CompilerAllocSize(PL_RLPKFileTableItem));
		ptrRLItem[iCount].iRLItemMode = PLRL_ConstID_IdenticalAllocate_PKGItem;
		if((ptrObject->iMode & PLRL_ConstID_PackageOpenMode_LocalAllocate) == PLRL_ConstID_PackageOpenMode_LocalAllocate){
			ptrRLItem[iCount].iRLItemMode |= PLRL_ConstID_LocalAllocate_PKGItem;
		}
		ptrRLItem[iCount].ptrNext   = NULL_PL;
		ptrRLItem[iCount].hFileAndle= ((ptrObject->header.iLStoreModeF & PLRL_ConstID_PKExteriorLinkIndex) != PLRL_ConstID_PKExteriorLinkIndex)	?  ptrObject->hFileAndle : NULL_PL;
		ptrRLItem[iCount].hPKGAndle = (HPKGObjAndle)ptrObject;
	}
	if(ptrFileTable == NULL_PL){
		PLSysAPI_Mem_TLPLreeMemoryPool(ptrFileTable);
		ptrFileTable = NULL_PL;
	}
	return hResult;
}
HPL_Result Eg_CreatePackageFTFindMap(HPKGObjAndle hAndle){
	PL_PackageObjectState * ptrObject;
	PL_RLItem * ptrRLItem;
	PL_RLPoolMap * ptrListMap;
	HPL_Result hResult;
	intV_pl iCount;
	hResult = HPLResult_OK;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if((ptrObject == NULL_PL) || (ptrObject->hFileAndle == NULL_PL) || (ptrObject->header.iTableSize<=0)
			|| (ptrObject->header.iTableCount<=0) || (ptrObject->ptrTableItemData == NULL_PL))
		return HPLResult_Fail;
	if(ptrObject->ptrListMap != NULL_PL){
		return HPLResult_OK;
	}

	ptrListMap = (PL_RLPoolMap *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_RLPoolMap));
	if(ptrListMap == NULL_PL){
		return HPLResult_Fail;
	}
	ptrListMap->iSlotMapMaxSize  = PLRL_ConstID_PackageFileItemSlotMapMaxSize;
	ptrListMap->hashfunc 	 	= __native_hash;
	ptrListMap->insertfunc    	= (__Rc_InsertFITableMapFunc__PL__)__native_InsertFITableMap;
	ptrListMap->removefunc 	 	= (__Rc_RemoveFITableMapFunc__PL__)__native_RemoveFITableMap;
	ptrListMap->removeallfunc 	= (__Rc_RemoveAllFITableMapFunc__PL__)__native_RemoveAllFITableMap;
	ptrListMap->destoryfunc   	= (__Rc_DestoryFITableMapFunc__PL__)__native_DestoryFITableMap;
	ptrListMap->destoryallfunc	= (__Rc_DestoryAllFITableMapFunc__PL__)__native_DestoryAllFITableMap;
	ptrListMap->searchtablefunc = (__Rc_SearchFITableMapFunc__PL__)__native_SearchFITableMap;
	ptrListMap->getcountfunc    = (__Rc_GetCountFITableMapFunc__PL__)__native_GetCountFITableMap;
	ptrListMap->iStoreMode      = *((intV_pl *)(&(ptrObject->header.iLStoreModeF)));
	for(iCount = 0;iCount < ptrObject->ptrListMap->iSlotMapMaxSize;iCount++){
		PLSysAPI_Syn_InitializeRWLockWF(ptrObject->ptrListMap->lockList[iCount]);
	}
	ptrRLItem    = (PL_RLItem *)(ptrObject->ptrTableItemData);
	for(iCount = 0;iCount < ptrObject->header.iTableCount;iCount++){
		ptrListMap->insertfunc(ptrObject->ptrListMap,&(ptrRLItem[iCount]));
	}
	return hResult;
}
bool_pl Eg_existPackageFTable(HPKGObjAndle hAndle){
	PL_PackageObjectState * ptrObject;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if((ptrObject != NULL_PL) && (ptrObject->ptrTableItemData != NULL_PL)){
		return true_pl;
	}
	return false_pl;
}
bool_pl Eg_existPackageFTFindMap(HPKGObjAndle hAndle){
	PL_PackageObjectState * ptrObject;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if((ptrObject != NULL_PL) && (ptrObject->ptrListMap != NULL_PL)){
		return true_pl;
	}
	return false_pl;
}
int64_pl Eg_GetPackageFileSize(HPKGObjAndle hAndle){
	PL_PackageObjectState * ptrObject;
	if(hAndle==NULL_PL)
		return 0;
	ptrObject = (PL_PackageObjectState *)hAndle;
	return *((int64_pl *)(&(ptrObject->header.iLFileSize)));
}
intV_pl Eg_GetPackageFileItemCount(HPKGObjAndle hAndle){
	PL_PackageObjectState * ptrObject;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if(hAndle==NULL_PL)
		return 0;
	return (intV_pl)(ptrObject->header.iTableCount);
}
HPKGFileItemAndle  Eg_GetPackageFileItemObjectI(HPKGObjAndle hAndle,intV_pl iIndex){
	PL_PackageObjectState * ptrObject;
	PL_RLItem * ptrItem;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if((ptrObject == NULL_PL) || (ptrObject->ptrTableItemData==NULL_PL) || (iIndex>=ptrObject->header.iTableCount))
		return NULL_PL;
	ptrItem = (PL_RLItem *)ptrObject->ptrTableItemData;
	return (HPKGFileItemAndle)(&(ptrItem[iIndex]));
}
HPKGFileItemAndle Eg_GetPackageFileItemObject(HPKGObjAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_PackageObjectState * ptrObject;
	PL_RLItem * ptrItem;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if((ptrObject == NULL_PL) || (ptrKey == NULL_PL) || (iKeySize<=0) || (ptrObject->ptrListMap == NULL_PL))
		return 0;
	ptrItem = (PL_RLItem *)ptrObject->ptrListMap->searchtablefunc(ptrObject->ptrListMap,ptrKey,iKeySize);
	return (HPKGFileItemAndle)ptrItem;
}
intV_pl Eg_GetPackageFileItemSize(HPKGFileItemAndle hAndle){
	PL_RLItem * ptrItem;
	ptrItem = (PL_RLItem *)hAndle;
	if(ptrItem==NULL_PL)
		return 0;
	return *((intV_pl *)(&(ptrItem->item.iLFileSize)));
}
intV_pl Eg_GetPackageFileItemResType(HPKGFileItemAndle hAndle){
	PL_RLItem * ptrItem;
	ptrItem = (PL_RLItem *)hAndle;
	if(ptrItem==NULL_PL)
		return 0;
	return *((intV_pl *)(&(ptrItem->item.uLType)));
}
intV_pl	Eg_GetPackageFileItemName(HPKGFileItemAndle hAndle,const_pl char_pl ** ppBuf){
	PL_RLItem * ptrItem;
	intV_pl iBSize;
	ptrItem = (PL_RLItem *)hAndle;
	if(ptrItem == NULL_PL || ppBuf == NULL_PL)
		return -1;
	(*ppBuf) = ptrItem->item.FileName;
	iBSize = *((intV_pl *)(&(ptrItem->item.iLSize)));
	return iBSize;
}
intV_pl Eg_ReadPackageFileItemData(HPKGFileItemAndle hAndle,void_pl * ptrData,intV_pl iBSize,intV_pl ioffset){
	PL_RLItem * ptrItem;
	PL_PackageObjectState * ptrObject;
	PLDeviceHandle hFileAndle;
	intV_pl iRetReadSize;
	intV_pl iReadSize;
	intV_pl iRRSize;
	lint_pl lMov;
	lint_pl lPos;
	int64_pl iStoreMode;

	iRetReadSize = 0;
	ptrItem = (PL_RLItem *)hAndle;
	if((hAndle == NULL_PL) || (ptrItem->hPKGAndle == NULL_PL) || (ptrData == NULL_PL) || (iBSize<=0))
		return 0;
	ptrObject = (PL_PackageObjectState *)(ptrItem->hPKGAndle);
	lMov = *((lint_pl *)(&(ptrItem->item.iLDataOffset)));
	lMov += ioffset;
	iStoreMode = *((int64_pl *)(&(ptrObject->header.iLStoreModeF)));
	if((iStoreMode & PLRL_ConstID_PKExteriorLinkIndex) == PLRL_ConstID_PKExteriorLinkIndex){
		return __native_Eg_ReadFileItemData(hAndle,ptrData,iBSize,ioffset);
	}else{
		hFileAndle = ptrItem->hFileAndle;
	}
	iReadSize = *((intV_pl *)(&(ptrItem->item.iLFileSize))) - ioffset;
	if((hFileAndle == NULL_PL) || iReadSize<=0 || (HResulPL_FAILED(PLSysAPI_SystemIO_Seek(hFileAndle,lMov,&lPos,PLSys_Const_SystemIO_Seek_Set,NULL_PL)) == true_pl))
		return 0;
	if(iReadSize>iBSize)
		iReadSize = iBSize;
	if(HResulPL_FAILED(PLSysAPI_SystemIO_Read(hFileAndle,ptrData,iReadSize,&iRRSize,NULL_PL)) == false_pl)
		iRetReadSize = iRRSize;
	return iRetReadSize;
}
intV_pl __native_Eg_ReadFileItemData(HPKGFileItemAndle hAndle,void_pl * ptrData,intV_pl iBSize,intV_pl ioffset){
	PL_RLItem * ptrItem;
	PL_PackageObjectState * ptrObject;
	PLDeviceHandle hFileAndle;
	char_pl pFullPath[PL3DSystemFileNameMaxLength];
	intV_pl iFPLength;
	intV_pl iRetReadSize;
	intV_pl iReadSize;
	intV_pl iRRSize;
	lint_pl lMov;
	lint_pl lPos;
	int64_pl iStoreMode;
	uintV_pl uFileFlage;
	uint_pl  uFileMode;
	iRetReadSize = 0;

	ptrItem = (PL_RLItem *)hAndle;
	ptrObject = (PL_PackageObjectState *)(ptrItem->hPKGAndle);
	lMov = *((lint_pl *)(&(ptrItem->item.iLDataOffset)));
	lMov += ioffset;
	iStoreMode = *((int64_pl *)(&(ptrObject->header.iLStoreModeF)));

	PLSysAPI_MemoryClearZero(pFullPath,PL3DSystemFileNameMaxLength);
	iFPLength = ptrObject->iFPLength;
	PLSysAPI_MemoryCpy(pFullPath,pFullPath,iFPLength);
	PLSysAPI_MemoryCpy(&(pFullPath[iFPLength]),ptrItem->item.FileName,*((intV_pl *)(&(ptrItem->item.iLSize))));
	iFPLength += (*((intV_pl *)(&(ptrItem->item.iLSize))));
	uFileFlage = (PLSysIO_Const_OpenMode_NotCreat | PLSysIO_Const_OpenOperat_Read);
	uFileMode  = (PLSysIO_Const_Att_UGRead | PLSysIO_Const_Att_UGExecute | PLSysIO_Const_Att_URead | PLSysIO_Const_Att_UExecute);
	if(HResulPL_FAILED(PLSysAPI_SystemIO_Open(&hFileAndle,pFullPath,iFPLength,uFileFlage,uFileMode,NULL_PL)) == true_pl){
		if(hFileAndle != NULL_PL){
			PLSysAPI_SystemIO_Close(hFileAndle);
			hFileAndle = NULL_PL;
		}
		return 0;
	}
	iReadSize = *((intV_pl *)(&(ptrItem->item.iLFileSize))) - ioffset;
	if((hFileAndle == NULL_PL) || iReadSize<=0 || (HResulPL_FAILED(PLSysAPI_SystemIO_Seek(hFileAndle,lMov,&lPos,PLSys_Const_SystemIO_Seek_Set,NULL_PL)) == true_pl))
		return 0;
	if(iReadSize>iBSize)
		iReadSize = iBSize;
	if(HResulPL_FAILED(PLSysAPI_SystemIO_Read(hFileAndle,ptrData,iReadSize,&iRRSize,NULL_PL)) == false_pl)
		iRetReadSize = iRRSize;
	if(hFileAndle != NULL_PL){
		PLSysAPI_SystemIO_Close(hFileAndle);
		hFileAndle = NULL_PL;
	}
	return iRetReadSize;
}
void_pl Eg_ClosePackage(HPKGObjAndle hAndle){
	PL_PackageObjectState * ptrObject;
	if(hAndle == NULL_PL)
		return;
	ptrObject = (PL_PackageObjectState *)hAndle;
	if(ptrObject->ptrListMap != NULL_PL){
		ptrObject->ptrListMap->destoryallfunc(ptrObject->ptrListMap);
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)(ptrObject->ptrListMap));
		ptrObject->ptrListMap = NULL_PL;
	}
	if(ptrObject->hFileAndle!=NULL_PL){
		PLSysAPI_SystemIO_Close(ptrObject->hFileAndle);
		ptrObject->hFileAndle = NULL_PL;
	}
	if(ptrObject->ptrTableItemData!=NULL_PL){
		PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrObject->ptrTableItemData));
		ptrObject->ptrTableItemData = NULL_PL;
	}
	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrObject);
}

ePL_ResourceDataMgrType __native_Eg_ConverItemTypeToMgrType(intV_pl iSpecificType){
	ePL_ResourceDataMgrType eType;

	switch(iSpecificType ){
	case PLRL_ConstID_RDI_Polygon:
		eType = PLSys_Const_ResD_ePLPolygonMgr;
		break;
	case PLRL_ConstID_RDI_Bone:
		eType = PLSys_Const_ResD_ePLBoneMgr;
		break;
	case PLRL_ConstID_RDI_Tex:
		eType = PLSys_Const_ResD_ePLTextureMgr;
		break;
	case PLRL_ConstID_RDI_WavEffect:
		eType = PLSys_Const_ResD_ePLWaveMgr;
	case PLRL_ConstID_RDI_Sound:
		eType = PLSys_Const_ResD_ePLSoundMgr;
		break;
	case PLRL_ConstID_RDI_Video:
		eType = PLSys_Const_ResD_ePLVideoMgr;
		break;
	case PLRL_ConstID_RDI_Script:
		eType = PLSys_Const_ResD_ePLScriptMgr;
		break;
	case PLRL_ConstID_RDI_Text:
		eType = PLSys_Const_ResD_ePLTextMgr;
		break;
	case PLRL_ConstID_RDI_MaterialDepict:
		eType = PLSys_Const_ResD_ePLMaterialMgr;
		break;
	case PLRL_ConstID_RDI_Data1:
	case PLRL_ConstID_RDI_Data2:
		eType = PLSys_Const_ResD_eData;
		break;
	default:
		eType = PLSys_Const_ResD_eData;
		break;
	}

	return eType;
}
