/*
 * PLEngineResourceLoadAPI.cpp
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "EngineResourceLoadAPI.h"
PLLibraryHandle g_hLibraryHandle_Resource = NULL_PL;
PLLibraryHandle     Eg_GetLibraryHandle_global(){
	return g_hLibraryHandle_Resource;
}
HPKGTaskersObjAndle Eg_CreatePackageTaskersObject(){
	PL_PackageTaskersState * ptrState;
	ptrState = NULL_PL;
	ptrState = (PL_PackageTaskersState *)PLSysAPI_Mem_AllocateMemoryPool(PL_CompilerAllocSize(PL_PackageTaskersState));
	PLSysAPI_MemoryClearZero(ptrState,PL_CompilerAllocSize(PL_PackageTaskersState));
	ptrState->cbSize = PL_CompilerAllocSize(PL_PackageTaskersState);
	//PL_PackageTaskersState
	return (HPKGTaskersObjAndle)ptrState;
}
void_pl Eg_RefurbishPackageTaskers(HPKGTaskersObjAndle hAndle){
	PL_PackageTaskersState * ptrState;
	if(hAndle == NULL_PL)
		return;
	ptrState = (PL_PackageTaskersState *)hAndle;


}
void_pl Eg_DestoryPackageTaskersObject(HPKGTaskersObjAndle hAndle){
	PL_PackageTaskersState * ptrState;
	if(hAndle == NULL_PL)
		return;
	ptrState = (PL_PackageTaskersState *)hAndle;
	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrState);
	ptrState = NULL_PL;
}


/*
HResourceSysAndle Eg_CreateResourceSystem(intV_pl iAllMode){
	PL_ResourceSystem * ptrResSys;
	if(ptrResSys == NULL_PL)
		return NULL_PL;
	ptrResSys = (PL_ResourceSystem *)PLSysAPI_Mem_AllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceSystem));
	PLSysAPI_MemoryClearZero(ptrResSys,PL_CompilerAllocSize(PL_ResourceSystem));




	return (HResourceSysAndle)ptrResSys;
}
void_pl Eg_RefurbishResourceSystem(HResourceSysAndle hAndle){

}


void_pl Eg_DestoryResourceSystem(HResourceSysAndle hAndle){
	PL_ResourceSystem * ptrResSys;
	ptrResSys = (PL_ResourceSystem *)hAndle;
	if(ptrResSys == NULL_PL)
		return;

	PLSysAPI_Mem_FreeMemoryPool(ptrResSys);
}
HPL_Result Eg_OpenTrusteeshipPKG(HResourceSysAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){


	return HPLResult_OK;
}
void_pl Eg_CloseTrusteeshipPKG(HResourceSysAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){

}
void_pl Eg_CloseAllTrusteeshipPKG(HResourceSysAndle hAndle){

}
void_pl Eg_ForceCloseTrusteeshipPKG(HResourceSysAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){

}
void_pl Eg_ForceCloseAllTrusteeshipPKG(HResourceSysAndle hAndle){

}
HResourceMgrItemAndle Eg_CreateResourceSystemItem(HResourceSysAndle hAndle,ePL_ResourceMgrType eType,intV_pl iPool,const_pl char_pl * ptrKey,intV_pl iKeySize){
	return NULL_PL;
}
void_pl Eg_ReleaseResourceSystemItem(HResourceMgrItemAndle hAndle){

}
HPL_Result Eg_DestoryResourceSystemItem(HResourceMgrItemAndle hAndle){
	return HPLResult_OK;
}
HPL_Result Eg_TryLockResourceItemData(HResourceMgrItemAndle hAndle){
	return HPLResult_OK;
}
void_pl Eg_UnLockResourceItemData(HResourceMgrItemAndle hAndle){

}
HPL_Result Eg_AllocateResourceSystemItemData(HResourceMgrItemAndle hAndle,intV_pl iDataSize){
	PL_ResourceMgrItem * ptrItem;
	PL_ResourceSystem * ptrSystem;
	//PL_ResourceManager *
	//PL_ResourceSystem *
	ptrItem = (PL_ResourceMgrItem *)hAndle;
	if(ptrItem->iPool != PLRL_ConstID_RS_TrusteeshipSystemPool)
		return HPLResult_Fail;
//
	//ptrSystem = (ptrItem-> )
	if(HResulPL_FAILED(Eg_TryLockResourceItemData(hAndle))==true_pl)
		return HPLResult_Fail;
	if((ptrItem->iDBMaxSize>iDataSize) && ((ptrItem->iDBMaxSize/iDataSize)>=3)){

	}else{

	}
	Eg_FreeResourceSystemItemData(hAndle);
	return HPLResult_OK;
}
HPL_Result Eg_FreeResourceSystemItemData(HResourceMgrItemAndle hAndle){
	return HPLResult_OK;
}
*/
bool_pl __native_InsertFITableMap(PL_RLPoolMap * ptrMap,PL_RLItem * ptrItem){
	PL_RLItem * ptrFItem;
	uintV_pl uHKey;
	uHKey = ptrMap->hashfunc(ptrItem->item.FileName,*((intV_pl *)(&(ptrItem->item.iLSize)))
														,ptrMap->iSlotMapMaxSize);
	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if(((*((intV_pl *)(&(ptrFItem->item.iLSize))))==(*((intV_pl *)(&(ptrItem->item.iLSize)))))
				&& (PLSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrItem->item.FileName,(*((intV_pl *)(&(ptrItem->item.iLSize))))) == 0))
			break;
		ptrFItem = (PL_RLItem *)(ptrFItem->ptrNext);
	}
	if(ptrFItem!=NULL_PL){
		PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
		return false_pl;
	}
	ptrItem->ptrNext = ptrMap->ptrRLItem[uHKey];
	ptrMap->ptrRLItem[uHKey] = ptrItem;
	ptrMap->iCount++;
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
	return true_pl;
}
PL_RLItem * __native_RemoveFITableMap(PL_RLPoolMap * ptrMap,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_RLItem * ptrFItem;
	PL_RLItem * ptrPreFItem;
	uintV_pl uHKey;
	uHKey = ptrMap->hashfunc(ptrKey,iKeySize,ptrMap->iSlotMapMaxSize);
	ptrPreFItem = NULL_PL;
	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if((*((intV_pl *)(&(ptrFItem->item.iLSize))))==iKeySize
				&& (PLSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrKey,iKeySize) == 0))
			break;
		ptrPreFItem = ptrFItem;
		ptrFItem = (PL_RLItem *)(ptrFItem->ptrNext);
	}
	if(ptrFItem==NULL_PL){
		PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
		return NULL_PL;
	}
	if(ptrPreFItem==NULL_PL){
		ptrMap->ptrRLItem[uHKey] = (PL_RLItem *)(ptrFItem->ptrNext);
	}else{
		ptrPreFItem->ptrNext = ptrFItem->ptrNext;
	}
	ptrMap->iCount--;
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
	return ptrFItem;
}
bool_pl __native_DestoryFITableMap(PL_RLPoolMap * ptrMap,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_RLItem * ptrFItem;
	PL_RLItem * ptrPreFItem;
	uintV_pl uHKey;
	uHKey = ptrMap->hashfunc(ptrKey,iKeySize,ptrMap->iSlotMapMaxSize);
	ptrPreFItem = NULL_PL;

	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if((*((intV_pl *)(&(ptrFItem->item.iLSize))))==iKeySize
				&& (PLSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrKey,iKeySize) == 0))
			break;
		ptrPreFItem = ptrFItem;
		ptrFItem = (PL_RLItem *)(ptrFItem->ptrNext);
	}
	if(ptrFItem==NULL_PL){
		PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);
		return false_pl;
	}
	if(ptrPreFItem==NULL_PL){
		ptrMap->ptrRLItem[uHKey] = (PL_RLItem *)(ptrFItem->ptrNext);
	}else{
		ptrPreFItem->ptrNext = ptrFItem->ptrNext;
	}
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMap->lockList[uHKey]);

	if((ptrFItem->iRLItemMode & PLRL_ConstID_IdenticalAllocate_PKGItem) != PLRL_ConstID_IdenticalAllocate_PKGItem){
		if((ptrMap->iStoreMode & PLRL_ConstID_PKExteriorLinkIndex) == PLRL_ConstID_PKExteriorLinkIndex){
			if(ptrFItem->hFileAndle!=NULL_PL){
				PLSysAPI_SystemIO_Close(ptrFItem->hFileAndle);
				ptrFItem->hFileAndle = NULL_PL;
			}
		}
		if((ptrFItem->iRLItemMode & PLRL_ConstID_LocalAllocate_PKGItem) == PLRL_ConstID_LocalAllocate_PKGItem){
			PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrFItem);
		}else{
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrFItem);
		}
		ptrFItem = NULL_PL;
	}
	ptrMap->iCount--;
	return true_pl;
}
PL_RLItem * __native_SearchFITableMap(PL_RLPoolMap * ptrMap,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_RLItem * ptrFItem;
	uintV_pl uHKey;
	uHKey = ptrMap->hashfunc(ptrKey,iKeySize,ptrMap->iSlotMapMaxSize);
	PLSysAPI_Syn_AcquireRWLockReadWF(ptrMap->lockList[uHKey]);
	ptrFItem = ptrMap->ptrRLItem[uHKey];
	while(ptrFItem){
		if((*((intV_pl *)(&(ptrFItem->item.iLSize))))==iKeySize
				&& (PLSysAPI_MemoryCmp(ptrFItem->item.FileName,ptrKey,iKeySize) == 0))
			break;
		ptrFItem = (PL_RLItem *)(ptrFItem->ptrNext);
	}
	PLSysAPI_Syn_ReleaseRWLockReadWF(ptrMap->lockList[uHKey]);
	return ptrFItem;
}
void_pl __native_RemoveAllFITableMap(PL_RLPoolMap * ptrMap){
	PL_RLItem * ptrFItem;
	for(intV_pl iCount =0;iCount<ptrMap->iSlotMapMaxSize;iCount++){
		PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[iCount]);
		ptrFItem = ptrMap->ptrRLItem[iCount];
		while(ptrFItem){
			ptrMap->iCount--;
			ptrFItem = (PL_RLItem *)(ptrFItem->ptrNext);
		}
		ptrMap->ptrRLItem[iCount] = NULL_PL;
		PLSysAPI_Syn_ReleaseRWLockReadWF(ptrMap->lockList[iCount]);
	}
}
void_pl __native_DestoryAllFITableMap(PL_RLPoolMap * ptrMap){
	PL_RLItem * ptrFItem;
	PL_RLItem * ptrReleaseItem;
	for(intV_pl iCount =0;iCount<ptrMap->iSlotMapMaxSize;iCount++){
		PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMap->lockList[iCount]);
		ptrFItem = ptrMap->ptrRLItem[iCount];
		ptrMap->ptrRLItem[iCount] = NULL_PL;
		while(ptrFItem){
			ptrReleaseItem = ptrFItem;
			ptrFItem = (PL_RLItem *)(ptrFItem->ptrNext);
			ptrMap->iCount--;
			if((ptrReleaseItem->iRLItemMode & PLRL_ConstID_IdenticalAllocate_PKGItem) != PLRL_ConstID_IdenticalAllocate_PKGItem){
				if((ptrMap->iStoreMode & PLRL_ConstID_PKExteriorLinkIndex) == PLRL_ConstID_PKExteriorLinkIndex){
					if(ptrFItem->hFileAndle!=NULL_PL){
						PLSysAPI_SystemIO_Close(ptrFItem->hFileAndle);
						ptrFItem->hFileAndle = NULL_PL;
					}
				}
				if((ptrReleaseItem->iRLItemMode & PLRL_ConstID_LocalAllocate_PKGItem) == PLRL_ConstID_LocalAllocate_PKGItem){
					PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrReleaseItem);
				}else{
					PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrReleaseItem);
				}
			}
		}
		PLSysAPI_Syn_ReleaseRWLockReadWF(ptrMap->lockList[iCount]);
	}
}
intV_pl __native_GetCountFITableMap(PL_RLPoolMap * ptrMap){
	return ptrMap->iCount;
}

uintV_pl __native_hash(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange){
	uintV_pl uHKey;
	uHKey = 0;
	for(intV_pl iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}
