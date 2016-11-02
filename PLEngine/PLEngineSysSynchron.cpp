/*
 * PLEngineSysSynchron.cpp
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */

#include "header/PLEngineSysSynchron.h"
#include "header/PLEngineSysProcess.h"
HPL_Result __PLSysAPI_Synchron_InitializeLWLock(_Syn_LWLock * ptrLock,int32_pl iInterval){
	PLSysAPI_MemoryClearZero(ptrLock,PL_CompilerAllocSize(_Syn_LWLock));
	ptrLock->iInterval = iInterval;
	ptrLock->iValue = PLSyn_Const_SynLWLockPass;
	return HPLResult_OK;
}
HPL_Result 	__PLSysAPI_Synchron_EnterLWLock(_Syn_LWLock * ptrLock,intV_pl iCount){
	HPL_Result hResult;
	PLThreadVirtualID vID;
	hResult = HPLResult_OK;
	if(HResulPL_FAILED(PLSysAPI_SystemProcess_GetThreadVirtualID(&vID))){
		return HPLResult_Fail;
	}
#if PLCPU_IAXX == PLCPU_IA32
	while(PLSysAPI_LockedCAS( (int32_pl *)(&(ptrLock->iValue)),vID,PLSyn_Const_SynSpinLockPass) == false){
		if((*((int32_pl *)(&ptrLock->iValue))) == vID)
#elif PLCPU_IAXX == PLCPU_IA64
	while(PLSysAPI_LockedCAS(&(ptrLock->iValue),vID,PLSyn_Const_SynSpinLockPass) == false){
		if(ptrLock->iValue == vID)
#endif
		{
			ptrLock->iCount++;
			break;
		}else if(ptrLock->iValue == PLSyn_Const_SynLWLockInvalid){
			ptrLock->iCount--;
			return HPLResult_Lock_UnInited;
		}
	}
	return HPLResult_OK;
}
void_pl		__PLSysAPI_Synchron_LeaveLWLock(_Syn_LWLock * ptrLock){
//	PLThreadVirtualID vID;
	ptrLock->iCount--;
	if(ptrLock->iCount<=0){
		ptrLock->iCount = 0;
		ptrLock->iValue = PLSyn_Const_SynLWLockPass;
	}
}
void_pl     __PLSysAPI_Synchron_ReleaseLWLock(_Syn_LWLock * ptrLock){
	ptrLock->iInterval  = 0;
	ptrLock->iValue 	= PLSyn_Const_SynLWLockInvalid;
	ptrLock->iCount 	= 0;
}

bool_pl __PLSysAPI_Synchron_InitializeRWLockRF(_Syn_RWLockRF & lock){
	lock.iRCount = 0;
	PLSysAPI_Syn_InitializeCriticalSectionLock(&(lock.lock));
	return true_pl;
}
HPL_Result __PLSysAPI_Synchron_AcquireRWLockReadRF(_Syn_RWLockRF & lock){
	intV_pl iValue;
	intV_pl iCount;
	iCount = 0;
	while(true_pl){
		if(lock.iRCount < 0){
			iCount++;
			if(iCount>=50){
				PLSysAPI_SystemProcess_Sleep(0);
				iCount = 0;
			}
			continue;
		}
		iValue = PLSysAPI_Syn_AtomInterAdd(&(lock.iRCount),1);
		if(iValue>=0)
			break;
	}
	return HPLResult_OK;
}
void_pl	__PLSysAPI_Synchron_ReleaseRWLockReadRF(_Syn_RWLockRF & lock){
	PLSysAPI_Syn_AtomInterAdd(&(lock.iRCount),-1);
}
HPL_Result __PLSysAPI_Synchron_AcquireRWLockWriteRF(_Syn_RWLockRF & lock){
	intV_pl iCount;
	iCount = 0;
	PLSysAPI_Syn_EnterCriticalSectionLock(&(lock.lock));
	while(PLSysAPI_LockedCAS(&(lock.iRCount) ,-10000000,0) == false_pl){
		iCount++;
		if(iCount<50)
			continue;
		PLSysAPI_SystemProcess_Sleep(0);
		iCount = 0;
	}
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_TryAcquireRWLockWriteRF(_Syn_RWLockRF & lock){
	if(lock.iRCount!=0)
		return HPLResult_Fail;
	if(PLSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))==false_pl)
		return HPLResult_Fail;
	if(PLSysAPI_LockedCAS(&(lock.iRCount) ,-10000000,0) == false_pl){
		PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
		return HPLResult_Fail;
	}
	return HPLResult_OK;
}
void_pl __PLSysAPI_Synchron_ReleaseRWLockWriteRF(_Syn_RWLockRF & lock){
	if(lock.iRCount<0)
		lock.iRCount = 0;
	PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
}
HPL_Result __PLSysAPI_Synchron_ReleaseRWLockRF(_Syn_RWLockRF & lock){
	//lock.iRCount = 0;
	if(false == PLSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))){
		return HPLResult_Fail;
	}
	PLSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
	return HPLResult_OK;
}
void_pl __PLSysAPI_Synchron_ForceReleaseRWLockRF(_Syn_RWLockRF & lock){
	lock.iRCount = 0;
	PLSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
}


bool_pl __PLSysAPI_Synchron_InitializeRWLockWF(_Syn_RWLockWF & lock){
	lock.iRCount = 0;
	lock.iWCount = 0;
	PLSysAPI_Syn_InitializeCriticalSectionLock(&(lock.rlock));
	PLSysAPI_Syn_InitializeCriticalSectionLock(&(lock.lock));
	return true_pl;
}
HPL_Result __PLSysAPI_Synchron_AcquireRWLockReadWF(_Syn_RWLockWF & lock){
//	intV_pl iValue;
	PLSysAPI_Syn_EnterCriticalSectionLock(&(lock.rlock));
		//iValue = PLSysAPI_Syn_AtomInterAdd(&(lock.iRCount),1);
		lock.iRCount++;
	PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_TryAcquireRWLockReadWF(_Syn_RWLockWF & lock){

	if(PLSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.rlock)) == false){
		if(lock.iWCount>0)
			return HPLResult_Fail;
		if(PLSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))== false)
			return HPLResult_Fail;
		PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
	}
	lock.iRCount++;
	PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
	return HPLResult_OK;
}
void_pl	__PLSysAPI_Synchron_ReleaseRWLockReadWF(_Syn_RWLockWF & lock){
	lock.iRCount--;
}
HPL_Result __PLSysAPI_Synchron_AcquireRWLockWriteWF(_Syn_RWLockWF & lock){
	intV_pl iOldValue;
	intV_pl iCount;
	iCount = 0;
	PLSysAPI_Syn_EnterCriticalSectionLock(&(lock.lock));
//	printf("writelock acquire Write lock!! \n");
	iOldValue = PLSysAPI_Syn_AtomInterAdd(&(lock.iWCount),1);
	if(iOldValue == 0){

//		printf("need lock read lock!!\n");
		PLSysAPI_Syn_EnterCriticalSectionLock(&(lock.rlock));
//		printf("lock read lock!!\n");
	}
	while(lock.iRCount>0){
//		printf("write lock wait iRCount=%d \n",lock.iRCount);
		iCount++;
		if(iCount<50)
			continue;
		PLSysAPI_SystemProcess_Sleep(0);
		iCount = 0;
	}
	return HPLResult_OK;
}
void_pl __PLSysAPI_Synchron_ReleaseRWLockWriteWF(_Syn_RWLockWF & lock){
	intV_pl iOldValue;
	iOldValue = PLSysAPI_Syn_AtomInterAdd(&(lock.iWCount),-1);
	if(iOldValue<=1)
		PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
	PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
}
HPL_Result __PLSysAPI_Synchron_ReleaseRWLockWF(_Syn_RWLockWF & lock){
	if((lock.iRCount>0) || (lock.iWCount>0)){
		return HPLResult_Fail;
	}
	if(PLSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.lock))==false_pl){
		return HPLResult_Fail;
	}
	if(PLSysAPI_Syn_TryEnterCriticalSectionLock(&(lock.rlock))==false_pl){
		PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
		return HPLResult_Fail;
	}
	if((lock.iRCount>0) || (lock.iWCount>0)){
		PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.lock));
		PLSysAPI_Syn_LeaveCriticalSectionLock(&(lock.rlock));
		return HPLResult_Fail;
	}
	PLSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
	PLSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.rlock));
	return HPLResult_OK;
}
void_pl __PLSysAPI_Synchron_ForceReleaseRWLockWF(_Syn_RWLockWF & lock){
	lock.iRCount = 0;
	lock.iWCount = 0;
	PLSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.lock));
	PLSysAPI_Syn_ReleaseCriticalSectionLock(&(lock.rlock));
}
HPL_Result __PLSysAPI_Synchron_InitializeThreadSpinLock(_Syn_TSpinLock * ptrLock){
	*ptrLock = PLSyn_Const_SynTSpinLockInvalid;
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_EnterThreadSpinLock(_Syn_TSpinLock * ptrLock){
	PLThreadVirtualID vID;
	if(HResulPL_FAILED(PLSysAPI_SystemProcess_GetThreadVirtualID(&vID)))
		return HPLResult_Fail;
	while(true_pl){
		if((*ptrLock) == PLSyn_Const_SynTSpinLockPass){
			intV_pl iCount;
			iCount = 0;
			while(PLSysAPI_LockedCAS(ptrLock,vID,PLSyn_Const_SynTSpinLockPass) == false_pl){
				if((*ptrLock) == PLSyn_Const_SynTSpinLockInvalid){
					return HPLResult_Fail;
				}
				iCount+=1;
				if(iCount > 100){
					PLSysAPI_SystemProcess_Sleep(0);
					iCount = 0;
				}
			}
		}else if((*ptrLock) == PLSyn_Const_SynTSpinLockInvalid){
			return HPLResult_Fail;
		}else if((*ptrLock) == vID){
			break;
		}
	}
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_TryEnterThreadSpinLock(_Syn_TSpinLock * ptrLock){
	PLThreadVirtualID vID;
	if(HResulPL_FAILED(PLSysAPI_SystemProcess_GetThreadVirtualID(&vID)))
		return HPLResult_Fail;
	if((*ptrLock) == PLSyn_Const_SynTSpinLockPass){
		if(PLSysAPI_LockedCAS(ptrLock,vID,PLSyn_Const_SynTSpinLockPass) == true_pl)
			return HPLResult_OK;
	}else if((*ptrLock) ==  PLSyn_Const_SynTSpinLockInvalid){
		return HPLResult_Fail;
	}
	return HPLResult_Fail;
}
void_pl __PLSysAPI_Synchron_LeaveThreadSpinLock(_Syn_TSpinLock * ptrLock){
	PLThreadVirtualID vID;
	if(HResulPL_FAILED(PLSysAPI_SystemProcess_GetThreadVirtualID(&vID)))
		return;
	PLSysAPI_LockedCAS(ptrLock,PLSyn_Const_SynTSpinLockPass,vID);
}
void_pl __PLSysAPI_Synchron_ReleaseThreadSpinLock(_Syn_TSpinLock * ptrLock){
	*ptrLock = PLSyn_Const_SynTSpinLockInvalid;
}
HPL_Result __PLSysAPI_Synchron_EnterSpinLock(_Syn_SpinLock * ptrLock){
	while(PLSysAPI_LockedCAS(ptrLock,PLSyn_Const_SpeediEasyLock,PLSyn_Const_SynSpinLockPass) == false_pl){
		if(*ptrLock==-1){
			return HPLResult_Fail;
		}
	}
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_TryEnterSpinLock(_Syn_SpinLock * ptrLock){
	return PLSysAPI_LockedCAS(ptrLock,PLSyn_Const_SpeediEasyLock,PLSyn_Const_SynSpinLockPass) == false_pl ? HPLResult_Fail : HPLResult_OK ;
}
void_pl    __PLSysAPI_Synchron_LeaveSpinLock(_Syn_SpinLock * ptrLock){
	PLSysAPI_LockedCAS(ptrLock,PLSyn_Const_SynSpinLockPass,PLSyn_Const_SpeediEasyLock);
}

