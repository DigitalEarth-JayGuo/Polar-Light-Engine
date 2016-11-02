/*
 * PLEngineSysThreadPool.cpp
 *
 *  Created on: 2009-11-5
 *      Author: Administrator
 */
#include "header/PLEngineSysThreadPool.h"
HThreadPool __PLSysAPI_SystemProcess_CreateThreadPool(PLThreadPoolParamer * ptrParamer){
	PLThreadPool * ptrTP;
	intV_pl iCount;
	if((ptrParamer==0) || (ptrParamer->iMaxCount<=0) || (ptrParamer->iTaskerMaxCount<=0))
		return NULL_PL;
	ptrTP = (PLThreadPool *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PLThreadPool));
	if(ptrParamer->iTaskerMaxCount<=0){
		ptrParamer->iTaskerMaxCount = PLSysTP_Const_TaskerMaxCount;
	}
	if(ptrTP == NULL_PL)
		return NULL_PL;
	PLSysAPI_MemoryClearZero((void_pl *)ptrTP,PL_CompilerAllocSize(PLThreadPool));
	ptrTP->iMaxCount = ptrParamer->iMaxCount;
	ptrTP->eState    = PLSysTP_Const_TaskerState_UnInitialize;
	ptrTP->ptrItem   = (PLTPoolItem *)PLSysAPI_Mem_TLSAllocateMemoryPool(ptrTP->iMaxCount * PL_CompilerAllocSize(PLTPoolItem));
	ptrTP->storelock = PLSyn_Const_SynSpinLockPass;
	ptrTP->iIdeCount = 0;
	PLSysAPI_MemoryClearZero(ptrTP->ptrItem,ptrTP->iMaxCount * PL_CompilerAllocSize(PLTPoolItem));
	for(iCount = 0;iCount < ptrTP->iMaxCount;iCount++){
		ptrTP->ptrItem[iCount].hAndle 		= NULL_PL;
		ptrTP->ptrItem[iCount].hPool  		= (HThreadPool)ptrTP;
		ptrTP->ptrItem[iCount].statelock 	= PLSyn_Const_SynSpinLockPass;
		ptrTP->ptrItem[iCount].waitlock 	= PLSysAPI_Syn_CreateEventLock();
		ptrTP->ptrItem[iCount].bAtQueue 	= false_pl;
		ptrTP->ptrItem[iCount].eLevelPriority = PLSys_Const_SysThreadPriority_Normal;
		ptrTP->ptrItem[iCount].eState	      = PLSysTP_Const_ThreadItem_Busyness;
		if(ptrTP->ptrItem[iCount].waitlock == NULL_PL){
			break;
		}
	}
	ptrTP->ptrTaskerQueue = ThreadPoolPriorityQueue::CreatePriorityQueue(ptrParamer->iTaskerMaxCount);
	if((ptrTP->ptrTaskerQueue==NULL_PL)  || (iCount<ptrTP->iMaxCount)){
		iCount -= 1;
		while(iCount>=0){
			PLSysAPI_Syn_DestroyEventLock(ptrTP->ptrItem[iCount].waitlock);
			ptrTP->ptrItem[iCount].hAndle = NULL_PL;
			iCount--;
		}
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)(ptrTP->ptrItem));
		ptrTP->ptrItem = NULL_PL;
		if(ptrTP->ptrTaskerQueue!=NULL_PL){
			ptrTP->ptrTaskerQueue->DestoryClass();
			ptrTP->ptrTaskerQueue = NULL_PL;
		}
		PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrTP);
		ptrTP = NULL_PL;
	}
	return (HThreadPool)ptrTP;
}

bool_pl __PLSysAPI_SystemProcess_RunThreadPool(HThreadPool hAndle){
	PLThreadPool * ptrTP;
	PLThreadAttr tattr;
	intV_pl iCount;
	ptrTP = (PLThreadPool *)hAndle;
	if(ptrTP == NULL_PL)
		return false_pl;
	if(ptrTP->eState != PLSysTP_Const_TaskerState_UnInitialize)
		return false_pl;
	PLSysAPI_MemoryClearZero(&tattr,PL_CompilerAllocSize(PLThreadAttr));
	tattr.iStackSize 	= 0;
	tattr.ePolicy 		= PLSys_Const_SysThreadPolicy_SysSched;
	tattr.iPriority 	= PLSys_Const_SysThreadPriority_Normal;
	tattr.uTag 			= PLSys_Const_SysThreadAttr_Policy_Set | PLSys_Const_SysThreadAttr_Priority_Set;
	ptrTP->ptrStoreItem = NULL_PL;
	for(iCount = 0;iCount<ptrTP->iMaxCount;iCount++){
		ptrTP->ptrItem[iCount].bAtQueue = false_pl;
		ptrTP->ptrItem[iCount].eState = PLSysTP_Const_ThreadItem_Busyness;

		__native_PLSysAPI_SystemProcess_PushThreadItem(hAndle,&(ptrTP->ptrItem[iCount]));
		if(HResulPL_FAILED(PLSysAPI_SystemProcess_CreatThread(&(ptrTP->ptrItem[iCount].hAndle),&tattr,__pl_threadpool_callback,(void_pl *)(&(ptrTP->ptrItem[iCount])))) == true_pl){
		}
	}
	ptrTP->eState = PLSysTP_Const_TaskerState_Run;
	return true_pl;
}
void_pl __PLSysAPI_SystemProcess_StopThreadPool(HThreadPool hAndle){
	PLThreadPool * ptrTP;
	PLTPoolItem * ptrItem;
	intV_pl iCount;
	ptrTP = (PLThreadPool *)hAndle;
	if((ptrTP == NULL_PL) || (ptrTP->eState != PLSysTP_Const_TaskerState_Run))
		return;
	if(PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrTP->eState)),
				PLSysTP_Const_TaskerState_Stop,PLSysTP_Const_TaskerState_Run) == false_pl)
		return;
	while((ptrItem = __native_PLSysAPI_SystemProcess_GetThreadItem(hAndle))!=NULL_PL){
	}
	for(iCount = 0;iCount<ptrTP->iMaxCount;iCount++){
		ptrTP->ptrItem[iCount].iExit = 1;
		PLSysAPI_Syn_SendEventLock(ptrTP->ptrItem[iCount].waitlock);
	}
}
HPL_Result  __PLSysAPI_SystemProcess_AddThreadPoolTasker(HThreadPool hAndle,PLTPoolTasker * ptrTasker){
	PLThreadPool * ptrTP;
	PLTPoolItem  * ptrItem;
	ptrTP = (PLThreadPool *)hAndle;
	if((ptrTP == NULL_PL) || (ptrTP->eState != PLSysTP_Const_TaskerState_Run)){
		return HPLResult_Fail;
	}
	if((ptrTasker == NULL_PL) || (HResulPL_FAILED(ptrTP->ptrTaskerQueue->Push(ptrTasker)) == true_pl)){
		return HPLResult_Fail;
	}
	ptrItem = __native_PLSysAPI_SystemProcess_GetThreadItem(hAndle);
	if(ptrItem!=NULL_PL){
		PLSysAPI_Syn_SendEventLock(ptrItem->waitlock);
	}
	return HPLResult_OK;
}
void_pl __PLSysAPI_SystemProcess_ReleaseThreadPoolTasker(HThreadPool hAndle,PLTPoolTasker * ptrTasker){
	if((hAndle == NULL_PL) || (ptrTasker == NULL_PL))
		return;
	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrTasker);
}
PLTPoolTasker * __PLSysAPI_SystemProcess_CreateThreadPoolTasker(HThreadPool hAndle){
	PLThreadPool * ptrTP;
	PLTPoolTasker * ptrTasker;
	ptrTP = (PLThreadPool *)hAndle;
	if(ptrTP == NULL_PL)
		return NULL_PL;
	ptrTasker = (PLTPoolTasker *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PLTPoolTasker));
	if(ptrTasker != NULL_PL){
		PLSysAPI_MemoryClearZero((void_pl *)ptrTasker,PL_CompilerAllocSize(PLTPoolTasker));
		ptrTasker->eLevelPriority = PLSys_Const_SysThreadPriority_CurrentSet;
	}
	return ptrTasker;
}
intV_pl __PLSysAPI_SystemProcess_GetThreadPoolMaxSize(HThreadPool hAndle){
	PLThreadPool * ptrTP;
	ptrTP = (PLThreadPool *)hAndle;
	if(ptrTP == NULL_PL)
		return 0;
	return ptrTP->iMaxCount;
}
intV_pl __PLSysAPI_SystemProcess_GetTaskerCount(HThreadPool hAndle){
	PLThreadPool * ptrTP;
	ptrTP = (PLThreadPool *)hAndle;
	if(ptrTP == NULL_PL)
		return 0;
	return ptrTP->ptrTaskerQueue->GetCurrentItemCount();
}
void_pl __PLSysAPI_SystemProcess_DestoryThreadPool(HThreadPool hAndle){
	PLThreadPool * ptrTP;
	intV_pl iCount;
	ptrTP = (PLThreadPool *)hAndle;
	if(ptrTP == NULL_PL)
		return;
	if(PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrTP->eState)),
					PLSysTP_Const_TaskerState_UnInitialize,PLSysTP_Const_TaskerState_Stop) == false_pl)
		return;
	for(iCount = 0;iCount < ptrTP->iMaxCount ;iCount++){
		ptrTP->ptrItem[iCount].iExit = 1;
		PLSysAPI_Syn_DestroyEventLock(ptrTP->ptrItem[iCount].waitlock);
	}
	ptrTP->storelock = PLSyn_Const_SynSpinLockPass;
	if(ptrTP->ptrTaskerQueue!=NULL_PL){
		ptrTP->ptrTaskerQueue->DestoryClass();
		ptrTP->ptrTaskerQueue = NULL_PL;
	}
	if(ptrTP->ptrItem!=NULL_PL){
		PLSysAPI_Mem_FreeMemoryPool((void_pl *)(ptrTP->ptrItem));
		ptrTP->ptrItem = NULL_PL;
	}
	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrTP);
}
void_pl	__native_PLSysAPI_SystemProcess_PushThreadItem(HThreadPool hAndle,_SPLTPoolItem * ptrItem){
	PLThreadPool * ptrTP;
	ptrTP = (PLThreadPool *)hAndle;
	if((ptrTP == NULL_PL) || (ptrItem == NULL_PL))
		return;
	if((ptrItem->bAtQueue == true_pl) || (ptrItem->eState == PLSysTP_Const_ThreadItem_Exit)
			|| (ptrItem->eState == PLSysTP_Const_ThreadItem_ExceptionalExit))
		return;
	PLSysAPI_Syn_EnterSpinLock(&(ptrTP->storelock));
		if(ptrItem->bAtQueue == true_pl){
			PLSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
			return;
		}
		if(PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eState)),
						PLSysTP_Const_ThreadItem_Ide,PLSysTP_Const_ThreadItem_Busyness) == false_pl){
			PLSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
			return;
		}
		ptrItem->bAtQueue = true_pl;
		ptrItem->ptrUp    = NULL_PL;
		ptrItem->ptrNext  = ptrTP->ptrStoreItem;
		if(ptrTP->ptrStoreItem != NULL_PL){
			ptrTP->ptrStoreItem->ptrUp  = ptrItem;
		}
		ptrTP->ptrStoreItem 		    = ptrItem;
		//iIdeCount
	PLSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
}
PLTPoolItem * __native_PLSysAPI_SystemProcess_GetThreadItem(HThreadPool hAndle){
	PLThreadPool * ptrTP;
	PLTPoolItem * ptrItem;
	PLTPoolItem * ptrRItem;
	ptrTP = (PLThreadPool *)hAndle;
	if(ptrTP == NULL_PL)
		return NULL_PL;
	ptrRItem = NULL_PL;
	PLSysAPI_Syn_EnterSpinLock(&(ptrTP->storelock));
		while(ptrTP->ptrStoreItem!=NULL_PL){
			ptrItem = ptrTP->ptrStoreItem;
			ptrTP->ptrStoreItem = ptrItem->ptrNext;
			if(ptrTP->ptrStoreItem!=NULL_PL){
				ptrTP->ptrStoreItem->ptrUp = NULL_PL;
			}
			ptrItem->bAtQueue   = false_pl;
			ptrItem->ptrNext 	= NULL_PL;
			ptrItem->ptrUp 		= NULL_PL;
			if(PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eState)),
								PLSysTP_Const_ThreadItem_Busyness,PLSysTP_Const_ThreadItem_Ide) == true_pl){
				ptrRItem = ptrItem;
				break;
			}
		}
	PLSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
	return ptrRItem;
}
void_pl __native_PLSysAPI_SystemProcess_PopThreadItemSelf(HThreadPool hAndle,PLTPoolItem * ptrItem){
	PLThreadPool * ptrTP;
	PLTPoolItem *  ptrUpItem;
	PLTPoolItem *  ptrDownItem;
	ptrTP = (PLThreadPool *)hAndle;
	if((ptrTP == NULL_PL) || (ptrItem == NULL_PL))
		return;
	if((ptrItem->eState == PLSysTP_Const_ThreadItem_Exit)
			|| (ptrItem->eState == PLSysTP_Const_ThreadItem_ExceptionalExit))
		return;
	if(ptrItem->bAtQueue == false_pl)
		return;
	PLSysAPI_Syn_EnterSpinLock(&(ptrTP->storelock));
		if(ptrItem->bAtQueue == false_pl){
			PLSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
			return;
		}
		ptrUpItem = ptrItem->ptrUp;
		ptrDownItem = ptrItem->ptrNext;

		if(ptrUpItem != NULL_PL){
			ptrUpItem->ptrNext = ptrDownItem;
		}else{
			if(ptrTP->ptrStoreItem == ptrItem){
				ptrTP->ptrStoreItem = ptrDownItem;
			}
		}
		if(ptrDownItem != NULL_PL){
			ptrDownItem->ptrUp = ptrUpItem;
		}
		ptrItem->bAtQueue 	= false_pl;
		ptrItem->ptrUp 		= NULL_PL;
		ptrItem->ptrNext 	= NULL_PL;
		PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eState)),
							PLSysTP_Const_ThreadItem_Busyness,PLSysTP_Const_ThreadItem_Ide);
	PLSysAPI_Syn_LeaveSpinLock(&(ptrTP->storelock));
}


uint_pl __pl_threadpool_callback(void_pl * ptrData){
	PLTPoolItem * ptrItem;
	PLTPoolTasker * ptrTasker;
	bool_pl bEnter;
	HPL_Result hResult;
	ptrItem = (PLTPoolItem *)ptrData;
	PLThreadVirtualID tid;
	tid = -1;
	PLSysAPI_SystemProcess_GetThreadVirtualID(&tid);
	if(ptrItem == NULL_PL)
		return -1;
	ptrTasker = NULL_PL;
	bEnter = false_pl;
	try{
		while(ptrItem->iExit != 1){
			__native_PLSysAPI_SystemProcess_PushThreadItem(ptrItem->hPool,ptrItem);
			hResult 		= PLSysAPI_Syn_WaitEventLock(ptrItem->waitlock);
			__native_PLSysAPI_SystemProcess_PopThreadItemSelf(ptrItem->hPool,ptrItem);
			if(ptrItem->iExit != 0){
				break;
			}

			while((ptrTasker = ((PLThreadPool *)(ptrItem->hPool))->ptrTaskerQueue->Pop()) != NULL_PL){
				if(ptrTasker->eLevelPriority != PLSys_Const_SysThreadPriority_CurrentSet){
					bEnter = true_pl;
					PLSysAPI_SystemProcess_SetThreadPriority(ptrItem->hAndle,ptrTasker->eLevelPriority);
				}
				ptrTasker->callback(ptrTasker->ptrParmer);
				PLSysAPI_SystemProcess_ReleaseThreadPoolTasker(ptrItem->hPool,ptrTasker);
				ptrTasker = NULL_PL;
			}
			if(bEnter == true_pl){
				bEnter = false_pl;
				PLSysAPI_SystemProcess_SetThreadPriority(ptrItem->hAndle,ptrItem->eLevelPriority);
			}
		}
		ptrItem->eState = PLSysTP_Const_ThreadItem_Exit;
	}catch(...){
		try{
			ptrItem->eState = PLSysTP_Const_ThreadItem_ExceptionalExit;
		}catch(...){

		}
	}
	return 0;
}
