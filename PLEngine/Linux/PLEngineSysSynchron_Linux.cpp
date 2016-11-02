/*
 * PLEngineSysSynchron_Linux.cpp
 *
 *  Created on: 2009-8-7
 *      Author: Administrator
 */
#include "../header/Linux/PLEngineSysSynchron_Linux.h"
#if PLOperat_System == PLOperatSystem_Linux

HPL_Result  __PLSysAPI_Synchron_InitializeCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	int ierror;
	ierror = pthread_mutex_init(ptrlock,NULL_PL);
	return ierror ==0 ? HPLResult_OK : HPLResult_Fail;
}
HPL_Result __PLSysAPI_Synchron_EnterCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	pthread_mutex_lock(ptrlock);
	return HPLResult_OK;
}
bool_pl __PLSysAPI_Synchron_TryEnterCriticalSectionLock  (_Syn_CriticalSection * ptrlock){
	int ierror;
	ierror = pthread_mutex_trylock(ptrlock);
	return ierror != EBUSY ? true_pl : false_pl;
}
void_pl __PLSysAPI_Synchron_LeaveCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	pthread_mutex_unlock(ptrlock);
}
void_pl __PLSysAPI_Synchron_ReleaseCriticalSectionLock(_Syn_CriticalSection * ptrlock){
	pthread_mutex_destroy(ptrlock);
}

_Syn_SysMutexLock __PLSysAPI_Synchron_CreateMutexLock(const_pl char_pl * ptrName,intV_pl iSize){
	_Syn_SysMutexLock lock;
	lock = sem_open(ptrName,O_CREAT,0644,1);//O_RDWR|
	if(lock == SEM_FAILED){
		lock = sem_open(ptrName,O_EXCL,0644,1);
		if(lock == SEM_FAILED)
			lock = NULL_PL;
	}
	return lock;
}
HPL_Result __PLSysAPI_Synchron_WaitMutexLock(_Syn_SysMutexLock lock){
	HPL_Result hResult;
	int ierror;
	hResult = HPLResult_OK;
	ierror = sem_wait(lock);
	if(ierror != 0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HPLResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HPLResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HPLResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
HPL_Result __PLSysAPI_Synchron_WaitTimerMutexLock(_Syn_SysMutexLock lock,intV_pl iWaitTimer){
	HPL_Result hResult;
	intV_pl nSec;
	int ierror;
	struct timespec ts;
	ierror = sem_trywait(lock);
	if(ierror == 0){
		return HPLResult_OK;
	}else if(ierror == EINVAL){
		return HPLResult_Lock_NotExist;
	}
	hResult = HPLResult_OK;
	clock_gettime(CLOCK_REALTIME,&ts);
	nSec = (iWaitTimer % 1000) * 1000;
	ts.tv_nsec += nSec;
	ts.tv_sec  += iWaitTimer/1000;
	ierror = sem_timedwait(lock,&ts);
	if(ierror !=0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HPLResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HPLResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HPLResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
void_pl __PLSysAPI_Synchron_ReleaseMutexLock(_Syn_SysMutexLock lock){
	sem_post(lock);
}

void_pl __PLSysAPI_Synchron_DestroyMutexLock(_Syn_SysMutexLock lock){
	sem_close((sem_t*)lock);
}

_Syn_SysEventLock __PLSysAPI_Synchron_CreateEventLockN(const_pl char_pl * ptrName,intV_pl iSize){
	return NULL_PL;
}
_Syn_SysEventLock __PLSysAPI_Synchron_CreateEventLock(){
	PLSynEvent_Linux * ptrEvent;
	ptrEvent = (PLSynEvent_Linux *)PLSysAPI_AllocateMemory(PL_CompilerAllocSize(PLSynEvent_Linux));
	if(ptrEvent == NULL_PL)
		return NULL_PL;

	PLSysAPI_MemoryClearZero((void_pl *)ptrEvent , PL_CompilerAllocSize(PLSynEvent_Linux));
	pthread_mutex_init(&(ptrEvent->mutex),NULL_PL);
	pthread_cond_init(&(ptrEvent->cond),NULL_PL);
	ptrEvent->iFlag = 0;

	return (_Syn_SysEventLock)ptrEvent;
}

HPL_Result __PLSysAPI_Synchron_WaitEventLock(_Syn_SysEventLock lock){
	PLSynEvent_Linux * ptrEvent;
	HPL_Result hResult;
	ptrEvent = (PLSynEvent_Linux *)lock;
	hResult = HPLResult_OK;
	if(ptrEvent==NULL_PL)
		return HPLResult_Fail;
	pthread_mutex_lock(&(ptrEvent->mutex));
	pthread_cond_wait(&(ptrEvent->cond),&(ptrEvent->mutex));
	pthread_mutex_unlock(&(ptrEvent->mutex));
	return hResult;
}
HPL_Result __PLSysAPI_Synchron_WaitTimerEventLock(_Syn_SysEventLock lock,intV_pl iWaitTimer){
	PLSynEvent_Linux * ptrEvent;
	HPL_Result hResult;
	struct timespec ts;
	intV_pl nSec;
	int iWV;

	ptrEvent = (PLSynEvent_Linux *)lock;
	hResult = HPLResult_OK;
	if(ptrEvent==NULL_PL)
		return HPLResult_Fail;
	clock_gettime(CLOCK_REALTIME,&ts);
	nSec = (iWaitTimer % 1000) * 1000;
	ts.tv_nsec += nSec;
	ts.tv_sec  += iWaitTimer/1000;
	pthread_mutex_lock(&(ptrEvent->mutex));
		iWV = pthread_cond_timedwait(&(ptrEvent->cond),&(ptrEvent->mutex),&ts);
		//ETIMEDOUT
	pthread_mutex_unlock(&(ptrEvent->mutex));
	return hResult;
}
HPL_Result __PLSysAPI_Synchron_SendEventLock(_Syn_SysEventLock lock){
	PLSynEvent_Linux * ptrEvent;
	ptrEvent = (PLSynEvent_Linux *)lock;
	if(ptrEvent == NULL_PL)
		return HPLResult_Fail;
	pthread_cond_broadcast(&(ptrEvent->cond));
	return HPLResult_OK;
}
void_pl __PLSysAPI_Synchron_DestroyEventLock(_Syn_SysEventLock lock){
	PLSynEvent_Linux * ptrEvent;
	ptrEvent = (PLSynEvent_Linux *)lock;
	if(ptrEvent == NULL_PL)
		return;
	pthread_cond_destroy(&(ptrEvent->cond));
	pthread_mutex_destroy(&(ptrEvent->mutex));

	PLSysAPI_FreeMemory((void_pl *)ptrEvent);
}
_Syn_SemaphoreLock	__PLSysAPI_Synchron_CreateSemaphore(const_pl char_pl * ptrName,intV_pl iSize,intV_pl iCount){
	_Syn_SemaphoreLock lock;
	uint32_pl uCount;
	uCount = (uint32_pl)iCount;
	lock = sem_open(ptrName,O_CREAT,0644,uCount);//O_RDWR|
	if(lock == SEM_FAILED){
		lock = sem_open(ptrName,O_EXCL,0644,uCount);
		if(lock == SEM_FAILED)
			lock = NULL_PL;
	}
	return lock;
}
HPL_Result __PLSysAPI_Synchron_WaitSemaphore(_Syn_SemaphoreLock lock){
	HPL_Result hResult;
	int ierror;
	hResult = HPLResult_OK;
	ierror = sem_wait(lock);
	if(ierror != 0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HPLResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HPLResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HPLResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
HPL_Result __PLSysAPI_Synchron_WaitTimerSemaphore(_Syn_SemaphoreLock lock,intV_pl iWaitTimer){
	HPL_Result hResult;
	intV_pl nSec;
	int ierror;
	struct timespec ts;
	ierror = sem_trywait(lock);
	if(ierror == 0){
		return HPLResult_OK;
	}else if(ierror == EINVAL){
		return HPLResult_Lock_NotExist;
	}
	hResult = HPLResult_OK;
	clock_gettime(CLOCK_REALTIME,&ts);
	nSec = (iWaitTimer % 1000) * 1000;
	ts.tv_nsec += nSec;
	ts.tv_sec  += iWaitTimer/1000;
	ierror = sem_timedwait(lock,&ts);
	if(ierror !=0){
		switch(ierror){
		case ETIMEDOUT:
			hResult = HPLResult_Lock_TimerOut;
			break;
		case EINVAL:
			hResult = HPLResult_Lock_NotExist;
			break;
		case EAGAIN:
		default:
			hResult = HPLResult_Lock_BlockFail;
			break;
		}
	}
	return hResult;
}
void_pl __PLSysAPI_Synchron_ReleaseSemaphore(_Syn_SemaphoreLock lock){
	sem_post(lock);
}
void_pl __PLSysAPI_Synchron_ReleaseSemaphoreCount(_Syn_SemaphoreLock lock,intV_pl iCount){
	for(intV_pl iNativeCount = 0;iNativeCount<iCount;iNativeCount++){
		sem_post(lock);
	}
}
void_pl __PLSysAPI_Synchron_DestroySemaphore(_Syn_SemaphoreLock lock){
	sem_close(lock);
}

#endif
