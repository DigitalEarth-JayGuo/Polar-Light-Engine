/*
 * EngineResourceTextureMgr.cpp
 *
 *  Created on: 2009-10-28
 *      Author: Administrator
 */

#include "EngineResourceManagerAPI.h"
HTextureMgrAndle Eg_CreateTextureManager(HResDataSystem hRDSystem){
	PL_ResourceTextureManager * ptrMgr;
	intV_pl iCount;
	ptrMgr = (PL_ResourceTextureManager *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceTextureManager));
	PLSysAPI_MemoryClearZero(ptrMgr,PL_CompilerAllocSize(PL_ResourceTextureManager));
	ptrMgr->hashfunc = __native_hash;
	ptrMgr->ReclaimLock = PLSyn_Const_SynSpinLockPass;
	ptrMgr->TkLock  	= PLSyn_Const_SynSpinLockPass;
	ptrMgr->TkOvLock    = PLSyn_Const_SynSpinLockPass;
	ptrMgr->TBLock      = PLSyn_Const_SynSpinLockPass;
	ptrMgr->ptrRootCommBlock = NULL_PL;
	for(iCount = 0;iCount<PLRMgr_ConstID_RTextureMgrMapSlotMaxSize;iCount++){
		PLSysAPI_Syn_InitializeRWLockWF(ptrMgr->List[iCount].lock);
	}
	return (HTextureMgrAndle)ptrMgr;
}
PL_ResourceTexture *    Eg_CreateTextureMgrObject(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem *    ptrItem;
	PL_ResourceTextureItem *    ptrNextItem;
	uintV_pl uHash;
	ptrMgr = (PL_ResourceTextureManager *)hAndle;
	ptrItem = NULL_PL;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,PLRMgr_ConstID_RTextureMgrMapSlotMaxSize);

	PLSysAPI_Syn_AcquireRWLockReadWF(ptrMgr->List[uHash].lock);
		ptrNextItem = ptrMgr->List[uHash].ptrRoot;
		while(ptrNextItem!=NULL_PL){
			if((iKeySize == ptrNextItem->iNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrNextItem->ptrName,iKeySize) == 0))
				break;
			ptrNextItem = ptrNextItem->ptrMNext;
		}
	PLSysAPI_Syn_ReleaseRWLockReadWF(ptrMgr->List[uHash].lock);
	if(ptrNextItem != NULL_PL)
		return NULL_PL;

	ptrItem = (PL_ResourceTextureItem *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_ResourceTextureItem));
	if(ptrItem == NULL_PL)
		return NULL_PL;
	PLSysAPI_MemoryClearZero(ptrItem,PL_CompilerAllocSize(PL_ResourceTextureItem));
	ptrItem->iNSize = iKeySize;
	ptrItem->ptrName = (const_pl char_pl *)PLSysAPI_Mem_TLSAllocateMemoryPool(ptrItem->iNSize + 1);
	if(ptrItem->ptrName==NULL_PL){
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrItem);
		return NULL_PL;
	}
	PLSysAPI_MemoryClearZero((char_pl *)(ptrItem->ptrName),ptrItem->iNSize + 1);
	PLSysAPI_MemoryCpy((char_pl *)(ptrItem->ptrName),ptrKey,ptrItem->iNSize);
	ptrItem->eType = PLSys_Const_ResD_ePLTextureMgr;
	ptrItem->iCount = 1;
	ptrItem->iRefCount = 0;
	ptrItem->eState = PLSys_Const_ResLoad_ePLUnLoadComplete;
	ptrItem->hMgrAndle = hAndle;
	ptrItem->eDynamicState = PLSys_Const_RODynamic_eCreate;
	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		ptrNextItem = ptrMgr->List[uHash].ptrRoot;
		while(ptrNextItem!=NULL_PL){
			if((iKeySize == ptrNextItem->iNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrNextItem->ptrName,iKeySize) == 0))
				break;
			ptrNextItem = ptrNextItem->ptrMNext;
		}
		if(ptrNextItem==NULL_PL){
			ptrItem->ptrMNext = ptrMgr->List[uHash].ptrRoot;
			ptrMgr->List[uHash].ptrRoot = ptrItem;
			PLSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),1);
			PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eDynamicState)),
					(intV_pl)PLSys_Const_RODynamic_eNormal,
					(intV_pl)PLSys_Const_RODynamic_eCreate);
		}
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrNextItem != NULL_PL){
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)(ptrItem->ptrName));
		ptrItem->ptrName = NULL_PL;
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrItem);
		ptrItem = NULL_PL;
		return NULL_PL;
	}
	return ptrItem;
}
PL_ResourceTexture * Eg_OpenTextureMgrObject(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem *    ptrItem;
	PL_ResourceTextureItem *    ptrNItem;
	PL_ResourceTextureItem *    ptrRelaseItem;
	PL_ResourceObjectDynamicState eDynamicState;
	intV_pl iRefCount;
	uintV_pl uHash;
	ptrMgr = (PL_ResourceTextureManager *)hAndle;
	if(ptrMgr==NULL_PL || ptrKey==NULL_PL || iKeySize<=0)
		return NULL_PL;
	ptrItem = NULL_PL;
	ptrRelaseItem = NULL_PL;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,PLRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	PLSysAPI_Syn_AcquireRWLockReadWF(ptrMgr->List[uHash].lock);
		ptrNItem = ptrMgr->List[uHash].ptrRoot;
		while(ptrNItem != NULL_PL){
			if((iKeySize == ptrNItem->iNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrNItem->ptrName,iKeySize) == 0)){
				break;
			}
			ptrNItem = ptrNItem->ptrMNext;
		}
	if((ptrNItem != NULL_PL) && (ptrNItem->eDynamicState != PLSys_Const_RODynamic_eReclaim)){
		ptrItem = ptrNItem;
		iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrNItem->iRefCount),1);
		if(iRefCount < 0){
			PLSysAPI_Syn_AtomInterAdd(&(ptrItem->iRefCount),-1);
			eDynamicState = ptrItem->eDynamicState;
			if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eDynamicState)),
					(intV_pl)PLSys_Const_RODynamic_eReclaim,
					(intV_pl)eDynamicState)==true_pl)){
				__native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrItem);
				ptrRelaseItem = ptrItem;
			}
			if(ptrRelaseItem != NULL_PL){
				__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrRelaseItem);
			}
			return NULL_PL;
		}
	}
	PLSysAPI_Syn_ReleaseRWLockReadWF(ptrMgr->List[uHash].lock);
	return (PL_ResourceTexture *)ptrItem;
}
HPL_Result Eg_ReleaseTextureMgrObject(PL_ResourceTexture * ptrItem){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem * ptrPItem;
	PL_ResourceTextureItem * ptrRelaseItem;
	PL_ResourceObjectDynamicState eDynamicState;
	intV_pl iRefCount;
	ptrPItem = (PL_ResourceTextureItem *)ptrItem;
	uintV_pl uHash;
	ptrRelaseItem = NULL_PL;
	if((ptrPItem == NULL_PL) || (ptrPItem->hMgrAndle==NULL_PL))
		return NULL_PL;
	ptrMgr = (PL_ResourceTextureManager *)(ptrPItem->hMgrAndle);
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,PLRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrItem->eDynamicState != PLSys_Const_RODynamic_eReclaim){
			iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			if(iRefCount==0){
				eDynamicState = ptrPItem->eDynamicState;
				if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eDynamicState)),
						(intV_pl)PLSys_Const_RODynamic_eReclaim,
						(intV_pl)eDynamicState)==true_pl)){
					__native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
					ptrRelaseItem = ptrPItem;
				}
			}
		}
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrRelaseItem != NULL_PL){
		__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrRelaseItem);
	}
	return HPLResult_OK;

}
HPL_Result Eg_DestoryTextureMgrObject(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem * ptrItem;
	uintV_pl uHash;
//	PL_ResourceObjectDynamicState eDynamicState;
	ptrMgr = (PL_ResourceTextureManager *)hAndle;
	if((ptrMgr == NULL_PL) || (iKeySize<=0) || (ptrKey == NULL_PL))
		return HPLResult_Fail;
	ptrItem = NULL_PL;
	uHash = ptrMgr->hashfunc(ptrKey,iKeySize,PLRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
		ptrItem = __native_Eg_UnRefMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrKey,iKeySize);
	PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
	if(ptrItem != NULL_PL){
		__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrItem);
	}
	return HPLResult_OK;
}
void_pl Eg_DestoryTextureManager(HTextureMgrAndle hAndle){
	intV_pl iCount;
	intV_pl iNCount;
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem *    ptrItem;
	PL_ResourceTextureItem *    ptrNItem;
	ptrMgr = (PL_ResourceTextureManager *)hAndle;
	if(ptrMgr == NULL_PL)
		return;
	ptrMgr->iTkCount = 0;
	ptrMgr->ptrOverFlowQueueRoot = NULL_PL;
	for(iCount = 0;iCount < PLRMgr_ConstID_RTextureMgrMapSlotMaxSize;iCount++){
		PLSysAPI_Syn_ForceReleaseRWLockWF(ptrMgr->List[iCount].lock);
		ptrNItem = ptrMgr->List[iCount].ptrRoot;
		ptrMgr->List[iCount].ptrRoot = NULL_PL;
		while(ptrNItem!=NULL_PL){

			ptrItem  = ptrNItem;
			ptrNItem = ptrNItem->ptrMNext;
			for(iNCount = 0;iNCount<ptrItem->iCount;iNCount++){
				if(ptrItem->hRDAndleList[iNCount]!=NULL_PL){
					PLSysAPI_RC_CloseResourceDataItem(ptrItem->hRDAndleList[iNCount]);
					ptrItem->hRDAndleList[iNCount] = NULL_PL;
				}
			}
			//PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrItem);
			ptrItem->eDynamicState = PLSys_Const_RODynamic_eReclaim;
			__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrItem);
		}
	}

	while((ptrItem = __native_Eg_PopReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr))!=NULL_PL){
		if(ptrItem->ptrName){
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrItem->ptrName));
		}
		if(ptrItem->ptrData!=NULL_PL){
			PLSysAPI_Mem_FreeMemoryPool(ptrItem->ptrData);
		}
		PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrItem);
	}
	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrMgr);
}

HPL_Result Eg_PushTextureRTaskerQueue(PL_ResourceTexture * ptrItem){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem * ptrPItem;
	PL_ResourceTextureItem * ptrReleaseItem;
	intV_pl iRefCount;
	uintV_pl uHash;
	PL_ResourceObjectDynamicState eDynamicState;
	ptrPItem = (PL_ResourceTextureItem *)ptrItem;
	ptrReleaseItem = NULL_PL;
	if((ptrPItem == NULL_PL) || (ptrPItem->hMgrAndle == NULL_PL))
		return HPLResult_Fail;
	ptrMgr = (PL_ResourceTextureManager *)(ptrPItem->hMgrAndle);
	if((PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eDynamicState)),
			(intV_pl)PLSys_Const_RODynamic_eTasker,
			(intV_pl)PLSys_Const_RODynamic_eNormal)==false_pl)
		|| (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eState)),
			(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad,
			(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete)==false_pl))
		return HPLResult_Fail;
	iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),1);
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,PLRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	if(iRefCount<0){
		PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
			eDynamicState = ptrPItem->eDynamicState;
			if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eDynamicState)),
									(intV_pl)PLSys_Const_RODynamic_eReclaim,
									(intV_pl)eDynamicState)==true_pl)){
				__native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
				ptrReleaseItem = ptrPItem;
			}
		PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrReleaseItem!=NULL_PL){
			__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
		}
		return HPLResult_Fail;
	}
	if(HResulPL_FAILED(PLSysAPI_Syn_TryEnterSpinLock(&(ptrMgr->TkLock))) == true_pl){
		if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_pl){
			iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eState)),
						(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete,
						(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad);
			if(iRefCount == 0){
				PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
					eDynamicState = ptrPItem->eDynamicState;
					if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eDynamicState)),
							(intV_pl)PLSys_Const_RODynamic_eReclaim,
							(intV_pl)eDynamicState)==true_pl)){
						ptrReleaseItem = __native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
					}
				PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
				if(ptrReleaseItem!=NULL_PL){
					__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
				}
			}
			return HPLResult_Fail;
		}
		ptrPItem->ptrNext = (PL_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = ptrPItem;
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		return HPLResult_OK;
	}
	if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrPItem,PLRMgr_ConstID_RTextureMgrTaskerListMaxL)==false_pl){
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
		if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_pl){
			iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eState)),
						(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete,
						(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad);
			if(iRefCount == 0){
				PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
					eDynamicState = ptrPItem->eDynamicState;
					if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eDynamicState)),
							(intV_pl)PLSys_Const_RODynamic_eReclaim,
							(intV_pl)eDynamicState)==true_pl)){
						ptrReleaseItem = __native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
					}
				PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
				if(ptrReleaseItem!=NULL_PL){
					__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
				}
			}
			return HPLResult_Fail;
		}
		ptrPItem->ptrNext = (PL_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = (PL_ResourceItem *)(ptrPItem);
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	}else{
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
	}
	return HPLResult_OK;
}
HPL_Result Eg_PushTextureRTaskerQueueFill(PL_ResourceTexture * ptrItem,PL_CommResourceBlock * ptrBlock){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem * ptrPItem;
	PL_ResourceTextureItem * ptrReleaseItem;
	intV_pl iRefCount;
	uintV_pl uHash;
	PL_ResourceObjectDynamicState eDynamicState;
	ptrReleaseItem = NULL_PL;
	ptrPItem = (PL_ResourceTextureItem *)ptrItem;
	if((ptrPItem == NULL_PL) || (ptrBlock == NULL_PL) || (ptrPItem->hMgrAndle == NULL_PL))
		return HPLResult_Fail;
	ptrMgr = (PL_ResourceTextureManager *)(ptrPItem->hMgrAndle);
	ptrBlock->ptrItem = ptrPItem;
	uHash = ptrMgr->hashfunc(ptrPItem->ptrName,ptrPItem->iNSize,PLRMgr_ConstID_RTextureMgrMapSlotMaxSize);
	iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),1);
	if(iRefCount<0){
		PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		eDynamicState = ptrPItem->eDynamicState;
		PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
			if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eDynamicState)),
					(intV_pl)PLSys_Const_RODynamic_eReclaim,
					(intV_pl)eDynamicState)==true_pl)){
				ptrReleaseItem = __native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
			}
		PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
		if(ptrReleaseItem!=NULL_PL){
			__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
		}
		return HPLResult_Fail;
	}
	if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TBLock))) == true_pl){
		iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
		if(iRefCount<=0){
			PLSysAPI_Syn_AtomInterAdd(&(ptrPItem->iRefCount),-1);
			eDynamicState = ptrPItem->eDynamicState;
			PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
				if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eDynamicState)),
						(intV_pl)PLSys_Const_RODynamic_eReclaim,
						(intV_pl)eDynamicState)==true_pl)){
					ptrReleaseItem = __native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrPItem);
				}
			PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
			if(ptrReleaseItem!=NULL_PL){
				__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrReleaseItem);
			}

		}
		return HPLResult_Fail;
	}
	ptrBlock->ptrNext = ptrMgr->ptrRootCommBlock;
	ptrMgr->ptrRootCommBlock = ptrBlock;
	PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	return HPLResult_OK;
}
HPL_Result Eg_PushTextureRTaskerQueueN(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem * ptrPItem;
	ptrMgr = (PL_ResourceTextureManager *)hAndle;
	if(ptrMgr==NULL_PL)
		return HPLResult_Fail;
	ptrPItem = (PL_ResourceTextureItem *)Eg_OpenTextureMgrObject(hAndle,ptrKey,iKeySize);
	if(ptrPItem == NULL_PL)
		return HPLResult_Fail;
	if(PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eState)),
			(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad,
			(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete)==false_pl){
		Eg_ReleaseTextureMgrObject((PL_ResourceTexture *)ptrPItem);
		return HPLResult_Fail;
	}
	if(HResulPL_FAILED(PLSysAPI_Syn_TryEnterSpinLock(&(ptrMgr->TkLock))) == true_pl){
		if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_pl){
			PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eState)),
						(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete,
						(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad);
			Eg_ReleaseTextureMgrObject((PL_ResourceTexture *)ptrPItem);
			return HPLResult_Fail;
		}
		ptrPItem->ptrNext = (PL_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = ptrPItem;
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		return HPLResult_OK;
	}
	if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrPItem,PLRMgr_ConstID_RTextureMgrTaskerListMaxL)==false_pl){
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
		if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_pl){
			PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPItem->eState)),
						(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete,
						(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad);
			Eg_ReleaseTextureMgrObject((PL_ResourceTexture *)ptrPItem);
			return HPLResult_Fail;
		}
		ptrPItem->ptrNext = (PL_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
		ptrMgr->ptrOverFlowQueueRoot = (PL_ResourceItem *)(ptrPItem->ptrNext);
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
	}else{
		PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
	}
	return HPLResult_OK;
}
HPL_Result Eg_PushTextureRTaskerQueueNFill(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem * ptrItem;
	ptrMgr = (PL_ResourceTextureManager *)hAndle;
	if((ptrMgr == NULL_PL) || (ptrKey == NULL_PL) || (iKeySize <= 0) || (ptrBlock == NULL_PL)){
		return HPLResult_Fail;
	}
	ptrItem = (PL_ResourceTextureItem *)Eg_OpenTextureMgrObject(hAndle,ptrKey,iKeySize);
	if(ptrItem == NULL_PL)
		return HPLResult_Fail;
	ptrBlock->ptrItem = ptrItem;
	if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TBLock))) == true_pl){
		Eg_ReleaseTextureMgrObject((PL_ResourceTexture *)ptrItem);
		return HPLResult_Fail;
	}
	ptrBlock->ptrNext = ptrMgr->ptrRootCommBlock;
	ptrMgr->ptrRootCommBlock = ptrBlock;
	PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TBLock));
	return HPLResult_OK;
}
HPL_Result Eg_RefurbishTextureRBackgroundDispose(HTextureMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer){
	PL_ResourceTextureManager * ptrMgr;
	PL_ResourceTextureItem * ptrItem;
	PL_ResourceTextureItem * ptrRelaseItem;
	PL_ResourceObjectDynamicState eDynamicState;
	//PL_ResourceTextureItem * ptrItem;
	HResDataItemAndle hDIAndle;
	intV_pl iCount;
	intV_pl iRefCount;
	uintV_pl uHash;
	ptrMgr = (PL_ResourceTextureManager *)hAndle;
	if((ptrMgr == NULL_PL) || (ptrParamer == NULL_PL))
		return HPLResult_Fail;
	ptrRelaseItem = NULL_PL;
	if((ptrMgr->ptrOverFlowQueueRoot != NULL_PL) && (ptrMgr->iTkCount<PLRMgr_ConstID_RTextureMgrTaskerListMaxL)){
		ptrItem = NULL_PL;
		if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == false_pl){
			if(ptrMgr->ptrOverFlowQueueRoot!=NULL_PL){
				ptrItem = (PL_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
				ptrMgr->ptrOverFlowQueueRoot = (PL_ResourceItem *)(ptrItem->ptrNext);
			}
			PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkOvLock));
		}
		if(ptrItem != NULL_PL){
			if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkLock))) == false_pl){
				if(__native_Eg_PushPriorityStackSortList(ptrMgr,ptrItem,PLRMgr_ConstID_RTextureMgrTaskerListMaxL)==false_pl){
					if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_pl){
						PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eState)),
									(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete,
									(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad);
						Eg_ReleaseTextureMgrObject((PL_ResourceTexture *)ptrItem);
					}else{
						ptrItem->ptrNext = (PL_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
						ptrMgr->ptrOverFlowQueueRoot = (PL_ResourceItem *)(ptrItem);
						PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
					}
				}
			}else{
				if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkOvLock))) == true_pl){
					PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eState)),
								(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete,
								(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad);
					Eg_ReleaseTextureMgrObject((PL_ResourceTexture *)ptrItem);
				}else{
					ptrItem->ptrNext = (PL_ResourceTextureItem *)(ptrMgr->ptrOverFlowQueueRoot);
					ptrMgr->ptrOverFlowQueueRoot = (PL_ResourceItem *)(ptrItem);
					PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
				}
			}
		}
	}
	if(ptrMgr->iTkCount>0){
		if(HResulPL_FAILED(PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->TkLock)))==false_pl){
			ptrItem = (PL_ResourceTextureItem *)(__native_Eg_PopMaxPriorityStackSort<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr));
			PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->TkLock));
			if(ptrItem != NULL_PL){
				//Background Thread Loading Data
				PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eState)),
							(intV_pl)PLSys_Const_ResLoad_ePLUnLoadComplete,
							(intV_pl)PLSys_Const_ResLoad_ePLBeginLoad);
				iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrItem->iRefCount),-1);
				if(iRefCount==0){
					uHash = ptrMgr->hashfunc(ptrItem->ptrName,ptrItem->iNSize,PLRMgr_ConstID_RTextureMgrMapSlotMaxSize);
					PLSysAPI_Syn_AcquireRWLockWriteWF(ptrMgr->List[uHash].lock);
						eDynamicState = ptrItem->eDynamicState;
						if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eDynamicState)),
								(intV_pl)PLSys_Const_RODynamic_eReclaim,
								(intV_pl)eDynamicState)==true_pl)){
							__native_Eg_RemoveMapItem<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,uHash,ptrItem);
							ptrRelaseItem = ptrItem;
						}
					PLSysAPI_Syn_ReleaseRWLockWriteWF(ptrMgr->List[uHash].lock);
					if(ptrRelaseItem != NULL_PL){
						__native_Eg_PushReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr,ptrItem);
					}
				}
				printf("background thread load item\n");
			}
		}
	}
	if(ptrMgr->ptrReclaimQueueRoot != NULL_PL){
		while((ptrItem = (PL_ResourceTextureItem *)__native_Eg_PopReclaimQueue<PL_ResourceTextureManager,PL_ResourceTextureItem>(ptrMgr))!=NULL_PL){
			printf("background thread free item\n");
			if(ptrItem->ptrData!=NULL_PL){
				PLSysAPI_Mem_FreeMemoryPool(ptrItem->ptrData);
				ptrItem->ptrData = NULL_PL;
			}
			if(ptrItem->ptrName!=NULL_PL){
				PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrItem->ptrName));
				ptrItem->ptrName = NULL_PL;
			}
			for(iCount = 0;iCount < ptrItem->iCount;iCount++){
				hDIAndle = ptrItem->hRDAndleList[iCount];
				if(hDIAndle != NULL_PL){
					PLSysAPI_RC_CloseResourceDataItem(hDIAndle);
					ptrItem->hRDAndleList[iCount] = NULL_PL;
				}
			}
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrItem);
		}
	}
	return HPLResult_OK;
}

