/*
 * PLEngineResourceDataManager.cpp
 *
 *  Created on: 2009-10-20
 *      Author: Administrator
 */
#include "EngineResourceLoadAPI.h"
_CallStack_default_ uintV_pl  __ResD_native_hashstringFunc__PL__(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange);
PL_ResDataSystemCrParamer * Eg_CreateResDataSystemCrParamer(){
	PL_ResDataSystemCrParamer * ptrParamer;
//#define  PLSysAPI_Mem_TLSAllocateMemoryPool 	distri_TLSAllocateMemory_PL
//#define  PLSysAPI_Mem_TLPLreeMemoryPool 		distri_TLPLreeMemory_PL
	ptrParamer=(PL_ResDataSystemCrParamer *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_ResDataSystemCrParamer));
	if(ptrParamer!=NULL_PL){
		PLSysAPI_MemoryClearZero(ptrParamer,PL_CompilerAllocSize(PL_ResDataSystemCrParamer));
	}
	return ptrParamer;
}
void_pl	Eg_DestoryResDataSystemCrParamer(PL_ResDataSystemCrParamer * ptrParamer){
	if(ptrParamer == NULL_PL)
		return;
	PLSysAPI_Mem_FreeMemoryPool(ptrParamer);
}

HResDataSystem Eg_CreateResourceDataSystem(PL_ResDataSystemCrParamer * ptrParamer){
	PL_ResourceDataSystem * ptrSystem;
	intV_pl iCount;
	intV_pl iNCount;
	intV_pl iAllSize;
	if(ptrParamer == NULL_PL)
		return NULL_PL;
	ptrSystem = (PL_ResourceDataSystem *)PLSysAPI_Mem_AllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceDataSystem));
	if(ptrSystem == NULL_PL)
		return NULL_PL;
	PLSysAPI_MemoryClearZero(ptrSystem,PL_CompilerAllocSize(PL_ResourceDataSystem));
	for(iCount = 0;iCount < PLSys_Const_ResD_ePLMgrMaxCount;iCount++){
		*((intV_pl *)(&(ptrSystem->MgrList[iCount].iMaxCount))) = PLRL_ConstID_ResourceDataMgrMapBaseMaxSize;
		ptrSystem->MgrList[iCount].ptrList = NULL_PL;
	}
	ptrSystem->MappHashfunc = __ResD_native_hashstringFunc__PL__;
	*((intV_pl *)(&(ptrSystem->MgrList[PLSys_Const_ResD_ePLPolygonMgr].iMaxCount))) = PLRL_ConstID_ResourceDataPolygonMgrMapMaxSize;
	*((intV_pl *)(&(ptrSystem->MgrList[PLSys_Const_ResD_ePLBoneMgr].iMaxCount))) 	= PLRL_ConstID_ResourceDataBoneMgrMapMaxSize;
	*((intV_pl *)(&(ptrSystem->MgrList[PLSys_Const_ResD_ePLTextureMgr].iMaxCount))) = PLRL_ConstID_ResourceDataTextureMgrMapMaxSize;
	*((intV_pl *)(&(ptrSystem->MgrList[PLSys_Const_ResD_ePLScriptMgr].iMaxCount)))  = PLRL_ConstID_ResourceDataScriptMgrMapMaxSize;
	*((intV_pl *)(&(ptrSystem->MgrList[PLSys_Const_ResD_ePLMaterialMgr].iMaxCount))) = PLRL_ConstID_ResourceDataMaterialMgrMapMaxSize;
	for(iCount = 0;iCount < PLSys_Const_ResD_ePLMgrMaxCount;iCount++){
		iAllSize = PL_CompilerAllocSize(PL_ResourceDataMapItem) * ptrSystem->MgrList[iCount].iMaxCount;
		ptrSystem->MgrList[iCount].ptrList = (PL_ResourceDataMapItem *)(PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceDataMapItem) * iAllSize));

		if(ptrSystem->MgrList[iCount].ptrList == NULL_PL){
			break;
		}
		PLSysAPI_MemoryClearZero(ptrSystem->MgrList[iCount].ptrList,PL_CompilerAllocSize(PL_ResourceDataMapItem) * iAllSize);

		for(iNCount = 0;iNCount;iNCount++){
			PLSysAPI_Syn_InitializeRWLockWF((ptrSystem->MgrList[iCount].ptrList[iNCount].lock));
		}
		ptrSystem->MgrList[iCount].hfunc = __ResD_native_hashstringFunc__PL__;
	}
	if(iCount<PLSys_Const_ResD_ePLMgrMaxCount){
		while(iCount>=0){
			if(ptrSystem->MgrList[iCount].ptrList != NULL_PL){
				for(iNCount = 0;iNCount;iNCount++){
					PLSysAPI_Syn_ForceReleaseRWLockWF((ptrSystem->MgrList[iCount].ptrList[iNCount].lock));
				}
				PLSysAPI_Mem_TLPLreeMemoryPool(ptrSystem->MgrList[iCount].ptrList);
				ptrSystem->MgrList[iCount].ptrList = NULL_PL;
			}
			iCount--;
		}
		PLSysAPI_Mem_FreeMemoryPool(ptrSystem);
		ptrSystem = NULL_PL;
	}

	for(iCount=0;iCount < PLRL_ConstID_PackageFileItemMappingSlotMapMaxSize;iCount++){
		PLSysAPI_Syn_InitializeRWLockWF(ptrSystem->lockPKGMapList[iCount]);
	}

	return (HResDataSystem)ptrSystem;
}
void_pl Eg_DestoryResourceDataSystem(HResDataSystem hAndle){
	PL_ResourceDataSystem * ptrSystem;
	PL_ResourceDataItem * ptrItem;
	PL_ResourceDataItem * ptrNext;
	PL_ResourceDataMapItem * ptrList;
	PL_PKGMemoryMapping * ptrPKGMapp;
	PL_PKGMemoryMapping * ptrNextPKGMapp;
	void_pl * ptrData;
	intV_pl iCount;
	intV_pl iNCount;
	ptrSystem = (PL_ResourceDataSystem *)hAndle;
	ptrList = ptrSystem->MgrList[iCount].ptrList;
	ptrSystem->MgrList[iCount].ptrList = NULL_PL;
	for(iCount = 0;iCount<PLSys_Const_ResD_ePLMgrMaxCount;iCount++){
		for(iNCount = 0;iNCount < ptrSystem->MgrList[iCount].iMaxCount;iNCount++){
			ptrNext = ptrList[iNCount].ptrRoot;
			ptrList[iNCount].ptrRoot = NULL_PL;
			PLSysAPI_Syn_ForceReleaseRWLockWF(ptrList[iNCount].lock);
			while(ptrNext){
				ptrItem = ptrNext;
				ptrNext = (PL_ResourceDataItem *)(ptrNext->ptrNext);
//				ptrData = ptrItem->ptrData;
//				ptrItem->ptrData = NULL_PL;
//				if(ptrItem->iPool == PLRL_ConstID_RS_TrusteeshipSystemPool){
//					PLSysAPI_Mem_FreeMemoryPool(ptrData);
//				}else
				if(ptrItem->iPool == PLRL_ConstID_RS_UserPool){
					PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrItem->ptrName));
					ptrItem->ptrName = NULL_PL;
				}
				PLSysAPI_Mem_FreeMemoryPool(ptrItem);
			}
		}
	}
	for(iCount=0;iCount < PLRL_ConstID_PackageFileItemMappingSlotMapMaxSize;iCount++){
		ptrSystem->ptrPKGMapList[iCount] = NULL_PL;
		PLSysAPI_Syn_ForceReleaseRWLockWF(ptrSystem->lockPKGMapList[iCount]);
	}
	ptrNextPKGMapp = ptrSystem->ptrPKGRoot;
	ptrSystem->ptrPKGRoot = NULL_PL;
	while(ptrNextPKGMapp!=NULL_PL){
		ptrPKGMapp = ptrNextPKGMapp;
		ptrNextPKGMapp = (PL_PKGMemoryMapping *)ptrNextPKGMapp->ptrChainNext;
		if(ptrPKGMapp->hAndle!=NULL_PL){
			Eg_ClosePackage(ptrPKGMapp->hAndle);
			ptrPKGMapp->hAndle = NULL_PL;
		}
	}


	PLSysAPI_Mem_FreeMemoryPool(ptrList);
	PLSysAPI_Mem_FreeMemoryPool(ptrSystem);
}
HResDataItemAndle Eg_GetResDataItem(HResDataSystem hAndle,ePL_ResourceDataMgrType eMgr,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_ResourceDataItem * ptrItem;
	PL_ResourceDataItem * ptrNext;
	PL_ResourceDataManager * ptrMgr;
	HPL_Result hResult;
	uintV_pl uHash;
	ptrItem = NULL_PL;
	ptrMgr = &(((PL_ResourceDataSystem *)hAndle)->MgrList[eMgr]);
	uHash = ptrMgr->hfunc(ptrKey,iKeySize,ptrMgr->iMaxCount);
	do{
		if(ptrMgr->ptrList == NULL_PL)
			break;
		if(HResulPL_FAILED( (hResult = PLSysAPI_Syn_AcquireRWLockReadWF(ptrMgr->ptrList[uHash].lock))) == true_pl)
			break;
		ptrNext = ptrMgr->ptrList[uHash].ptrRoot;
		while(ptrNext!=NULL_PL){
			if((ptrNext->iNSize == iKeySize) && (PLSysAPI_MemoryCmp(ptrNext->ptrName,ptrKey,ptrNext->iNSize) == 0))
				ptrItem = ptrNext;
				break;
			ptrNext = (PL_ResourceDataItem *)(ptrNext->ptrNext);
		}
		PLSysAPI_Syn_ReleaseRWLockReadWF(ptrMgr->ptrList[uHash].lock);
	}while(false_pl);
	return(HResDataItemAndle) ptrItem;
}

HPL_Result Eg_RefurbishResourceDataMgrSystem(HResDataSystem hAndle){

	return HPLResult_OK;
}


HResDataPKGMMAndle Eg_CreateResourceDataSystemPKGMapping(HResDataSystem hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,intV_pl iMapping){
	PL_PKGMemoryMapping * ptrObject;
	PL_PKGMemoryMapping * ptrNObject;
	HPKGObjAndle hPKGAndle;
	PL_ResourceDataSystem * ptrSystem;
	uintV_pl uHash;
	ptrSystem = (PL_ResourceDataSystem *)hAndle;
	if(ptrSystem == NULL_PL || ptrKey==NULL_PL || iKeySize<=0)
		return NULL_PL;
	uHash= ptrSystem->MappHashfunc(ptrKey,iKeySize,PLRL_ConstID_PackageFileItemMappingSlotMapMaxSize);

	PLSysAPI_Syn_AcquireRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
	ptrObject = ptrSystem->ptrPKGMapList[uHash];
	while(ptrObject!=NULL_PL){
		if((iKeySize == ptrObject->iPKGNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrObject->ptrPKGName,iKeySize) == 0))
			break;
		ptrObject = (PL_PKGMemoryMapping *)(ptrObject->ptrNext);
	}
//	_SPL_PKGMemoryMapping * ptrChainUp;
//	_SPL_PKGMemoryMapping * ptrChainNext;
	PLSysAPI_Syn_ReleaseRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
	if(ptrObject!=NULL_PL)
		return NULL_PL;
	ptrObject = (PL_PKGMemoryMapping *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_PKGMemoryMapping));
	PLSysAPI_MemoryClearZero(ptrObject,PL_CompilerAllocSize(PL_PKGMemoryMapping));
	ptrObject->hAndle = NULL_PL;
	ptrObject->iRefCount  = 0;
	ptrObject->eLoadState = PLSys_Const_ResLoad_ePLBeginLoad;
	ptrObject->iPKGNSize  = iKeySize;
	ptrObject->ptrSystem  = ptrSystem;
	ptrObject->ptrPKGName = (const_pl char_pl *)PLSysAPI_Mem_TLSAllocateMemoryPool(ptrObject->iPKGNSize + 1);
	PLSysAPI_MemoryClearZero((void_pl *)(ptrObject->ptrPKGName),ptrObject->iPKGNSize + 1);
	PLSysAPI_MemoryCpy((void_pl *)(ptrObject->ptrPKGName),ptrKey,ptrObject->iPKGNSize);
	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrSystem->lockPKGMapList[uHash]);
	ptrNObject = ptrSystem->ptrPKGMapList[uHash];
	while(ptrNObject!=NULL_PL){
		if((iKeySize == ptrNObject->iPKGNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrNObject->ptrPKGName,iKeySize) == 0))
			break;
		ptrNObject = (PL_PKGMemoryMapping *)(ptrNObject->ptrNext);
	}
	if(ptrNObject != NULL_PL){
		PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrSystem->lockPKGMapList[uHash]);
		PLSysAPI_Mem_TLPLreeMemoryPool(ptrObject);
		ptrObject = NULL_PL;
		return NULL_PL;
	}
	ptrObject->ptrNext 				= ptrSystem->ptrPKGMapList[uHash];
	ptrSystem->ptrPKGMapList[uHash] = ptrObject;
	ptrObject->ptrChainNext = ptrSystem->ptrPKGRoot;
	ptrSystem->ptrPKGRoot   = ptrObject;
	if(ptrObject->ptrChainNext != NULL_PL )
		ptrObject->ptrChainNext->ptrChainUp = ptrObject;
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrSystem->lockPKGMapList[uHash]);
	ptrObject->eLoadState 				= PLSys_Const_ResLoad_ePLLoading;
	hPKGAndle = Eg_OpenPackage(ptrKey,iKeySize,PLLR_ConstID_PackageOpenMode_NotCreateFTable | PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap);
	ptrObject->hAndle 					= hPKGAndle;
	ptrObject->eLoadState 				= PLSys_Const_ResLoad_ePLLoadComplete;
	return (HResDataPKGMMAndle)ptrObject;
}
HPL_Result Eg_ReleaseResourceDataSystemPKGMapping(HResDataPKGMMAndle hAndle){
	PL_PKGMemoryMapping * ptrObject;
	intV_pl iRefCount;
	ptrObject = (PL_PKGMemoryMapping *)hAndle;
	if(ptrObject == NULL_PL)
		return HPLResult_Fail;
	iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrObject->iRefCount),-1);
	return HPLResult_OK;
}
HPL_Result Eg_ReleaseResourceDataSystemPKGMappingN(HResDataSystem hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_PKGMemoryMapping   * ptrObject;
	PL_ResourceDataSystem * ptrSystem;
	intV_pl iRefCount;
	uintV_pl uHash;
	ptrSystem = (PL_ResourceDataSystem *)hAndle;
	if((ptrSystem == NULL_PL) || (ptrKey == NULL_PL) || (iKeySize<=0))
		return HPLResult_Fail;
	uHash = ptrSystem->MappHashfunc(ptrKey,iKeySize,PLRL_ConstID_PackageFileItemMappingSlotMapMaxSize);
	PLSysAPI_Syn_AcquireRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
		ptrObject = ptrSystem->ptrPKGMapList[uHash];
		while(ptrObject!=NULL_PL){
			if((ptrObject->iPKGNSize == iKeySize) && ( PLSysAPI_MemoryCmp(ptrObject->ptrPKGName,ptrKey,iKeySize) == 0)){
				break;
			}
			ptrObject = (PL_PKGMemoryMapping *)(ptrObject->ptrNext);
		}
		if(ptrObject!=NULL_PL){
			iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrObject->iRefCount),-1);
		}
	PLSysAPI_Syn_ReleaseRWLockReadWF(ptrSystem->lockPKGMapList[uHash]);
	return HPLResult_OK;
}
HPL_Result Eg_MappinResourceDataSystemPKG(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle){
	PL_PKGMemoryMapping * ptrObject;
	PL_ResourceDataSystem  * ptrSystem;
	PL_ResourceDataItem    * ptrRDItem;
	PL_ResourceDataItem    * ptrNRDItem;
	PL_ResourceDataMapItem * ptrRDMItem;
	ePL_ResourceDataMgrType eItemType;
	intV_pl 			    iSItemType;
	const_pl char_pl * ptrName;
	intV_pl iNSize;
	HPKGFileItemAndle hAndleItem;
	intV_pl iItemCount;
	uintV_pl uHash;
	intV_pl iRefCount;
	HPL_Result hResult;


	hResult = HPLResult_OK;
	ptrSystem = (PL_ResourceDataSystem *)hAndle;
	ptrObject = (PL_PKGMemoryMapping *)hMMAndle;
	if(ptrSystem==NULL_PL || ptrObject==NULL_PL)
		return HPLResult_Fail;
	if((HResulPL_FAILED(Eg_LoadPackageFTable(ptrObject->hAndle)) == true_pl) || (HResulPL_FAILED(Eg_CreatePackageFTFindMap(ptrObject->hAndle)) == true_pl)){
		return HPLResult_Fail;
	}
	iItemCount = Eg_GetPackageFileItemCount(ptrObject->hAndle);
	if(iItemCount<=0)
		return HPLResult_Fail;
	for(intV_pl iCount = 0;iCount<iItemCount;iCount++){
		hAndleItem = Eg_GetPackageFileItemObjectI(ptrObject->hAndle,iCount);
		if(hAndleItem==NULL_PL)
			continue;
		ptrName = NULL_PL;
		iNSize = Eg_GetPackageFileItemName(hAndleItem,&ptrName);
		if((iNSize<=0) || (ptrName == NULL_PL))
			continue;
		iSItemType = Eg_GetPackageFileItemResType(hAndleItem);
		eItemType  = PLRL_Maroc_ConverTypeItemToMgr(iSItemType);
		uHash = ptrSystem->MgrList[eItemType].hfunc(ptrName,iNSize,ptrSystem->MgrList[eItemType].iMaxCount);
		ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);
		PLSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
			while(ptrNRDItem!=NULL_PL){
				if((ptrNRDItem->iNSize == iNSize) && (PLSysAPI_MemoryCmp(ptrNRDItem->ptrName,ptrName,iNSize)==0)){
					break;
				}
				ptrNRDItem = (PL_ResourceDataItem *)ptrNRDItem->ptrNext;
			}
		PLSysAPI_Syn_ReleaseRWLockReadWF(ptrRDMItem->lock);
		if(ptrNRDItem!=NULL_PL)
			continue;
		ptrRDItem = (PL_ResourceDataItem *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceDataItem));
		PLSysAPI_MemoryClearZero(ptrRDItem,PL_CompilerAllocSize(PL_ResourceDataItem));
		ptrRDItem->eLoadState = PLSys_Const_ResLoad_ePLUnLoadComplete;
		ptrRDItem->lock       = PLSyn_Const_SynSpinLockPass;
		ptrRDItem->eOperator  = PLSys_Const_ResDOpert_ReadOnly;
		ptrRDItem->hAndle     = hAndleItem;
		ptrRDItem->iRefCount  = 0;
		ptrRDItem->iSpecificType = iSItemType;
		ptrRDItem->eType      = eItemType;
		ptrRDItem->iNSize     = iNSize;
		ptrRDItem->ptrName    = ptrName;
		ptrRDItem->iPool      = PLRL_ConstID_RS_TrusteeshipSystemPool;
		PLSysAPI_Syn_AcquireRWLockWriteWF(ptrRDMItem->lock);
			ptrNRDItem = ptrRDMItem->ptrRoot;
			while(ptrNRDItem!=NULL_PL){
				if((ptrRDItem->iNSize == ptrNRDItem->iNSize) && (PLSysAPI_MemoryCmp(ptrRDItem->ptrName,ptrNRDItem->ptrName,ptrRDItem->iNSize)==0)){
					break;
				}
				ptrNRDItem = (PL_ResourceDataItem *)(ptrNRDItem->ptrNext);
			}
			if(ptrNRDItem==NULL_PL){
				ptrRDItem->ptrNext  = ptrRDMItem->ptrRoot;
				ptrRDMItem->ptrRoot = ptrRDItem;
				iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrObject->iRefCount),1);
			}
		PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
		if(ptrNRDItem!=NULL_PL && ptrRDItem!=NULL_PL){
			PLSysAPI_Mem_TLPLreeMemoryPool(ptrRDItem);
			ptrRDItem = NULL_PL;
		}
	}
	return HPLResult_OK;
}
HPL_Result Eg_MappingResourceDataSystemPKGItem(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle,intV_pl iIndex){
	PL_ResourceDataSystem  * ptrSystem;
	PL_PKGMemoryMapping    * ptrObject;
	PL_ResourceDataItem    * ptrRDItem;
	PL_ResourceDataItem    * ptrNRDItem;
	PL_ResourceDataMapItem * ptrRDMItem;
	HPKGFileItemAndle        hFItem;
	ePL_ResourceDataMgrType eItemType;
	intV_pl 			    iSItemType;
	const_pl char_pl * ptrName;
	intV_pl iNSize;
	uintV_pl uHash;
//	HPL_Result hResult;

	ptrSystem = (PL_ResourceDataSystem *)hAndle;
	ptrObject = (PL_PKGMemoryMapping   *)hMMAndle;
	if((ptrSystem == NULL_PL) || (ptrObject == NULL_PL) || (iIndex<0))
		return HPLResult_Fail;
	hFItem = Eg_GetPackageFileItemObjectI(ptrObject->hAndle,iIndex);
	if(hFItem == NULL_PL )
		return HPLResult_Fail;
	iNSize = Eg_GetPackageFileItemName(hFItem,&ptrName);
	if((iNSize<=0) || (ptrName == NULL_PL))
		return HPLResult_Fail;

	iSItemType = Eg_GetPackageFileItemResType(hFItem);
	eItemType  = PLRL_Maroc_ConverTypeItemToMgr(iSItemType);
	uHash = ptrSystem->MgrList[eItemType].hfunc(ptrName,iNSize,ptrSystem->MgrList[eItemType].iMaxCount);
	ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);


	PLSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
	ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_PL){
			if((ptrNRDItem->iNSize == iNSize) && (PLSysAPI_MemoryCmp(ptrNRDItem->ptrName,ptrName,iNSize)==0)){
				break;
			}
			ptrNRDItem = (PL_ResourceDataItem *)ptrNRDItem->ptrNext;
		}
	PLSysAPI_Syn_ReleaseRWLockReadWF(ptrRDMItem->lock);
	if(ptrNRDItem!=NULL_PL)
		return HPLResult_Fail;

	ptrRDItem = (PL_ResourceDataItem *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceDataItem));
	PLSysAPI_MemoryClearZero(ptrRDItem,PL_CompilerAllocSize(PL_ResourceDataItem));
	ptrRDItem->eLoadState = PLSys_Const_ResLoad_ePLUnLoadComplete;
	ptrRDItem->lock       = PLSyn_Const_SynSpinLockPass;
	ptrRDItem->eOperator  = PLSys_Const_ResDOpert_ReadOnly;
	ptrRDItem->hAndle     = hFItem;
	ptrRDItem->iRefCount  = 0;
	ptrRDItem->iSpecificType = iSItemType;
	ptrRDItem->eType      = eItemType;
	ptrRDItem->iNSize     = iNSize;
	ptrRDItem->ptrName    = ptrName;
	ptrRDItem->iPool      = PLRL_ConstID_RS_TrusteeshipSystemPool;
	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_PL){
			if((ptrRDItem->iNSize == ptrNRDItem->iNSize) && (PLSysAPI_MemoryCmp(ptrRDItem->ptrName,ptrNRDItem->ptrName,ptrRDItem->iNSize)==0)){
				break;
			}
			ptrNRDItem = (PL_ResourceDataItem *)(ptrNRDItem->ptrNext);
		}
		if(ptrNRDItem==NULL_PL){
			ptrRDItem->ptrNext  = ptrRDMItem->ptrRoot;
			ptrRDMItem->ptrRoot = ptrRDItem;
		}
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
	if(ptrNRDItem!=NULL_PL && ptrRDItem!=NULL_PL){
		PLSysAPI_Mem_TLPLreeMemoryPool(ptrRDItem);
		ptrRDItem = NULL_PL;
	}
	return HPLResult_OK;
}
HResDataItemAndle Eg_OpenResourceDataItem(HResDataSystem hAndle,intV_pl iSItemType,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_ResourceDataSystem  * ptrSystem;
	PL_ResourceDataMapItem * ptrRDMItem;
//	PL_ResourceDataItem    * ptrRDItem;
	PL_ResourceDataItem    * ptrNRDItem;
	intV_pl iRefCount;
	ePL_ResourceDataMgrType eItemType;
	uintV_pl uHash;
	ptrSystem = (PL_ResourceDataSystem *)hAndle;
	eItemType = PLRL_Maroc_ConverTypeItemToMgr(iSItemType);
	ptrNRDItem = NULL_PL;
	do{
		if((ptrSystem == NULL_PL) || (ptrKey == NULL_PL) || (iKeySize<=0))
			break;
		uHash = ptrSystem->MgrList[eItemType].hfunc(ptrKey,iKeySize,ptrSystem->MgrList[eItemType].iMaxCount);
		ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);
		PLSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
			ptrNRDItem = ptrRDMItem->ptrRoot;
			while(ptrNRDItem!=NULL_PL){
				if((iKeySize == ptrNRDItem->iNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrNRDItem->ptrName,iKeySize) == 0)){
					iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrNRDItem->iRefCount),1);
					break;
				}
				ptrNRDItem = (PL_ResourceDataItem *)(ptrNRDItem->ptrNext);
			}
		PLSysAPI_Syn_ReleaseRWLockReadWF(ptrRDMItem->lock);
	}while(0);
	return (HResDataItemAndle)ptrNRDItem;
}
void_pl Eg_CloseResourceDataItem(HResDataItemAndle hAndle){
	PL_ResourceDataItem * ptrItem;
	intV_pl iRefCount;
	ptrItem = (PL_ResourceDataItem *)hAndle;
	if(ptrItem == NULL_PL)
		return;
	iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrItem->iRefCount),-1);
}

/*
HResDataItemAndle Eg_CreateResourceDataItemUD(HResDataSystem hAndle,intV_pl iSItemType,const_pl char_pl * ptrName,intV_pl iSize,ePL_ResourceDataOperator eOpera){
	PL_ResourceDataSystem  * ptrSystem;
	PL_ResourceDataMapItem * ptrRDMItem;
	PL_ResourceDataItem    * ptrRDItem;
	PL_ResourceDataItem    * ptrNRDItem;
	ePL_ResourceDataMgrType eItemType;
	HResDataItemAndle hRDAndle;
	uintV_pl uHash;

	hRDAndle   = NULL_PL;
	ptrSystem  = (PL_ResourceDataSystem *)hAndle;
	eItemType  = PLRL_Maroc_ConverTypeItemToMgr(iSItemType);
	if((ptrSystem == NULL_PL) || (ptrName == NULL_PL) || (iSize<=0))
		return NULL_PL;
	uHash = ptrSystem->MgrList[eItemType].hfunc(ptrName,iSize,ptrSystem->MgrList[eItemType].iMaxCount);
	ptrRDMItem = &(ptrSystem->MgrList[eItemType].ptrList[uHash]);
	PLSysAPI_Syn_AcquireRWLockReadWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_PL){
			if((iSize == ptrNRDItem->iNSize) && (PLSysAPI_MemoryCmp(ptrName,ptrNRDItem->ptrName,iSize) == 0)){
				break;
			}
			ptrNRDItem = (PL_ResourceDataItem *)(ptrNRDItem->ptrNext);
		}

	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
	if(ptrNRDItem != NULL_PL)
		return NULL_PL;
	ptrRDItem = (PL_ResourceDataItem *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceDataItem));
	PLSysAPI_MemoryClearZero(ptrRDItem,PL_CompilerAllocSize(PL_ResourceDataItem));
	ptrRDItem->eLoadState = PLSys_Const_ResLoad_ePLUnLoadComplete;
	ptrRDItem->lock       = PLSyn_Const_SynSpinLockPass;
	ptrRDItem->eOperator  = eOpera;
	ptrRDItem->hAndle     = NULL_PL;
	ptrRDItem->iRefCount  = 0;
	ptrRDItem->iSpecificType = iSItemType;
	ptrRDItem->eType      = eItemType;
	ptrRDItem->iNSize     = iSize;
	ptrRDItem->iPool	  = PLRL_ConstID_RS_UserPool;
	ptrRDItem->ptrName    = (const_pl char_pl *)(PLSysAPI_Mem_TLSAllocateMemoryPool(ptrRDItem->iNSize + PLChr_ConstID_StringEndChrLength));
	PLSysAPI_MemoryClearZero((char_pl *)(ptrRDItem->ptrName),ptrRDItem->iNSize + PLChr_ConstID_StringEndChrLength);
	PLSysAPI_MemoryCpy((char_pl *)(ptrRDItem->ptrName),ptrName,ptrRDItem->iNSize);

	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrRDMItem->lock);
		ptrNRDItem = ptrRDMItem->ptrRoot;
		while(ptrNRDItem!=NULL_PL){
			if((iSize == ptrNRDItem->iNSize) && (PLSysAPI_MemoryCmp(ptrName,ptrNRDItem->ptrName,iSize) == 0)){
				break;
			}
			ptrNRDItem = (PL_ResourceDataItem *)(ptrNRDItem->ptrNext);
		}
		if(ptrNRDItem == NULL_PL){
			ptrRDItem->ptrNext = ptrRDMItem->ptrRoot;
			ptrRDMItem->ptrRoot= ptrRDItem;
			ptrRDItem->iRefCount++;
		}
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrRDMItem->lock);
	if((ptrNRDItem!=NULL_PL) && (ptrRDItem!=NULL_PL)){
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)(ptrRDItem->ptrName));
		PLSysAPI_Mem_TLPLreeMemoryPool(ptrRDItem);
	}
	return hRDAndle;
}
HPL_Result Eg_ReleaseResourceDataItemUD(HResDataSystem hAndle,HResDataItemAndle hItemAndle){
	PL_ResourceDataSystem  * ptrSystem;
	PL_ResourceDataItem    * ptrRDItem;
//	PL_ResourceDataItem    * ptrNRDItem;

	ptrSystem = (PL_ResourceDataSystem *)hAndle;
	ptrRDItem = (PL_ResourceDataItem *)hItemAndle;
	if(ptrSystem == NULL_PL || ptrRDItem == NULL_PL)
		return HPLResult_Fail;
	ptrRDItem->iRefCount--;
	return HPLResult_OK;
}
*/


uintV_pl  __ResD_native_hashstringFunc__PL__(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange){
	uintV_pl uHKey;
	uHKey = 0;
	for(intV_pl iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}

