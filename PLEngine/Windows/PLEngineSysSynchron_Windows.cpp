/*
 * PLEngineSysSynchron_Windows.cpp
 *
 *  Created on: 2009-8-7
 *      Author: Administrator
 */
#include "../header/Windows/PLEngineSysSynchron_Windows.h"
#if PLOperat_System == PLOperatSystem_Window
HPL_Result  __PLSysAPI_Synchron_InitializeCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	InitializeCriticalSection(ptrlock);
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_EnterCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	EnterCriticalSection(ptrlock);
	return HPLResult_OK;
}
bool_pl __PLSysAPI_Synchron_TryEnterCriticalSectionLock  (_Syn_CriticalSection * ptrlock){
	return TryEnterCriticalSection(ptrlock) == TRUE ? true_pl : false_pl ;
}
void_pl __PLSysAPI_Synchron_LeaveCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	LeaveCriticalSection(ptrlock);
}
void_pl __PLSysAPI_Synchron_ReleaseCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	DeleteCriticalSection(ptrlock);
}
_Syn_SysMutexLock  __PLSysAPI_Synchron_CreateMutexLock(const_pl char_pl * ptrName,intV_pl iSize){
	_Syn_SysMutexLock lock;
	lock = OpenMutex(MUTEX_ALL_ACCESS,FALSE,ptrName);
	if(lock == NULL_PL){
		SECURITY_ATTRIBUTES sec_attr;
		PLSysAPI_MemoryClearZero(&sec_attr,PL_CompilerAllocSize(SECURITY_ATTRIBUTES));
		sec_attr.bInheritHandle = FALSE;
		lock = CreateMutex(&sec_attr,FALSE,ptrName);
	}
	return lock;
}
HPL_Result __PLSysAPI_Synchron_WaitMutexLock(_Syn_SysMutexLock lock){
	HPL_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,INFINITE);
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HPLResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HPLResult_Lock_TimerOut;
		break;
	default:
		hResult = HPLResult_OK;
		break;
	}
	return hResult;
}
HPL_Result __PLSysAPI_Synchron_WaitTimerMutexLock(_Syn_SysMutexLock lock,intV_pl iWaitTimer){
	HPL_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,*((int32_pl *)(&iWaitTimer)));
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HPLResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HPLResult_Lock_TimerOut;
		break;
	case WAIT_FAILED:
		hResult = HPLResult_Lock_BlockFail;
	case WAIT_OBJECT_0:
	default:
		hResult = HPLResult_OK;
	}
	return hResult;
}
void_pl __PLSysAPI_Synchron_ReleaseMutexLock(_Syn_SysMutexLock lock){
	ReleaseMutex(lock);
}
void_pl __PLSysAPI_Synchron_DestroyMutexLock(_Syn_SysMutexLock lock){
	CloseHandle(lock);
}

_Syn_SysEventLock __PLSysAPI_Synchron_CreateEventLock(){
	HANDLE hAndle;
	SECURITY_ATTRIBUTES attr;
	hAndle = NULL_PL;
	PLSysAPI_MemoryClearZero(&attr,PL_CompilerAllocSize(SECURITY_ATTRIBUTES));
	attr.bInheritHandle = FALSE;
	hAndle = CreateEvent(&attr,TRUE,FALSE,0);
	return hAndle;
}
_Syn_SysEventLock __PLSysAPI_Synchron_CreateEventLockN(const_pl char_pl * ptrName,intV_pl iSize){
	HANDLE hAndle;
	SECURITY_ATTRIBUTES attr;
	hAndle = NULL_PL;
	PLSysAPI_MemoryClearZero(&attr,PL_CompilerAllocSize(SECURITY_ATTRIBUTES));
	attr.bInheritHandle = FALSE;
	hAndle = CreateEvent(&attr,FALSE,FALSE,ptrName);
	return NULL_PL;
}
HPL_Result __PLSysAPI_Synchron_WaitEventLock(_Syn_SysEventLock lock){
	HANDLE hAndle;
	DWORD  dSOV;
	hAndle = lock;
	if(hAndle == NULL_PL)
		return HPLResult_Fail;
	dSOV = WaitForSingleObject(hAndle,INFINITE);
//	ResetEvent(hAndle);
	if(dSOV != WAIT_OBJECT_0){
		if(dSOV == WAIT_TIMEOUT){

			return HPLResult_Lock_TimerOut;
		}else if(dSOV == WAIT_FAILED){
			return HPLResult_Lock_NotExist;
		}
	}
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_WaitTimerEventLock(_Syn_SysEventLock lock,intV_pl iWaitTimer){
	HANDLE hAndle;
	DWORD  dSOV;
	hAndle = lock;
	if(hAndle == NULL_PL)
		return HPLResult_Fail;
	dSOV = WaitForSingleObject(hAndle,*((int32_pl *)(&iWaitTimer)));
//	ResetEvent(hAndle);
	if(dSOV != WAIT_OBJECT_0){
		if(dSOV == WAIT_FAILED){
			return HPLResult_Lock_NotExist;
		}
	}
	return HPLResult_OK;
}
HPL_Result __PLSysAPI_Synchron_SendEventLock(_Syn_SysEventLock lock){
	SetEvent(lock);
	return HPLResult_OK;
}
void_pl __PLSysAPI_Synchron_DestroyEventLock(_Syn_SysEventLock lock){
	CloseHandle(lock);
}

_Syn_SemaphoreLock	__PLSysAPI_Synchron_CreateSemaphore(const_pl char_pl * ptrName,intV_pl iSize,intV_pl iCount){
	_Syn_SemaphoreLock lock;
	LONG lCount;
	SECURITY_ATTRIBUTES sec_attr;
	lock = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,ptrName);
	if(lock==NULL_PL){
		lCount = (LONG)iCount;
		PLSysAPI_MemoryClearZero(&sec_attr,PL_CompilerAllocSize(SECURITY_ATTRIBUTES));
		lock = CreateSemaphore(&sec_attr,0,lCount,ptrName);
	}
	return lock;
}
HPL_Result __PLSysAPI_Synchron_WaitSemaphore(_Syn_SemaphoreLock lock){
	HPL_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,INFINITE);
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HPLResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HPLResult_Lock_TimerOut;
		break;
	case WAIT_FAILED:
		hResult = HPLResult_Lock_BlockFail;
		break;
	case WAIT_OBJECT_0:
	default:
		hResult = HPLResult_OK;
		break;
	}
	return hResult;
}
HPL_Result __PLSysAPI_Synchron_WaitTimerSemaphore(_Syn_SemaphoreLock lock,intV_pl iWaitTimer){
	HPL_Result hResult;
	DWORD dError;
	dError = WaitForSingleObject(lock,*((int32_pl *)(&iWaitTimer)));
	switch(dError){
	case WAIT_ABANDONED:
		hResult = HPLResult_Lock_NotExist;
		break;
	case WAIT_TIMEOUT:
		hResult = HPLResult_Lock_TimerOut;
		break;
	case WAIT_FAILED:
		hResult = HPLResult_Lock_BlockFail;
	case WAIT_OBJECT_0:
	default:
		hResult = HPLResult_OK;
	}
	return hResult;
}
void_pl __PLSysAPI_Synchron_ReleaseSemaphore(_Syn_SemaphoreLock lock){
	LONG lRCount;
	ReleaseSemaphore(lock,1,&lRCount);
}
void_pl __PLSysAPI_Synchron_ReleaseSemaphoreCount(_Syn_SemaphoreLock lock,intV_pl iCount){
	LONG lRCount;
	if(iCount<=0)
		return;
	ReleaseSemaphore(lock,(LONG)iCount,&lRCount);
}
void_pl __PLSysAPI_Synchron_DestroySemaphore(_Syn_SemaphoreLock lock){
	CloseHandle(lock);
}

#endif
