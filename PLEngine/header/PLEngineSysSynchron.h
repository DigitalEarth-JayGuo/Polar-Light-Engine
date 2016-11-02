/*
 * PLEngineSysSynchron.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineGraphicsInface.h"
#include "PLEngineH.h"
#include "PLEngineInface.h"
#include "PLEngineI.h"
#include "PLEngineSysAPI.h"
#ifndef PLENGINESYSSYNCHRON_H_
#define PLENGINESYSSYNCHRON_H_
/*
	inline void __PLSysAPI_Synchron_InitAtomLock(_Synchron_Lock * lock){
		*lock = 0;
	}
	inline bool_pl  __PLSysAPI_Synchron_BeginAtomLock(_Synchron_Lock * lock){
		if(LockedCAS(lock,1,0)==false_pl){
			while(true_pl){
				if((*lock)==0){
					if(LockedCAS(lock,1,0)==true_pl){
						break;
					}
				}else if((*lock)==2){
					return false_pl;
				}
			}
		}
		return true_pl;
	}
	inline void __PLSysAPI_Synchron_EndAtomLock(_Synchron_Lock * lock){
		LockedCAS(lock,0,1);
	}
	inline HPL_Result __PLSysAPI_Synchron_EnterAtomLock(_Synchron_Lock * lock,int_pl iCount){
		if(LockedCAS(lock,1,0)==true_pl)
			return HPLResult_OK;
		while(iCount>0){
			if((*lock)==0){
				if(LockedCAS(lock,1,0)==true_pl){
					return HPLResult_OK;
				}
			}else if((*lock)==2){
				return HPLResult_Lock_NotExist;
			}
			iCount--;
		}
		return HPLResult_Lock_TimerOut;
	}
	inline void    __PLSysAPI_Synchron_ReleaseAtomLock(_Synchron_Lock * lock){
		*lock = 2;
	}
	inline bool_pl __PLSysAPI_Synchron_CheckAtomLock(_Synchron_Lock * lock){
		return LockedCAS(lock,1,0);
	}
*/
	inline int32_pl __PLSysAPI_Synchron_AtomVIntegerAdd32(volatile_pl int32_pl * ptrObject,int32_pl iAdd){
		int32_pl iValue;
		#if PLCompiler_Tool == PLCompiler_MSVC
			__asm{
				push eax
				mov eax,iAdd
				lock xadd [ptrOut],eax
				mov iValue,eax
				pop eax
			}
		#elif PLCompiler_Tool == PLCompiler_GCC
			__asm__ __volatile__ ("lock xadd %2,%1 \n movl %2,%0 \n\t" : "=r"(iValue) : "m"(*ptrObject),"r"(iAdd) : "memory");
		#else
			*ptrObject += iAdd;
			iValue = *ptrObject;
		#endif
		return iValue;
	}

	inline int64_pl __PLSysAPI_Synchron_AtomVIntegerAdd64(volatile_pl int64_pl * ptrObject,int64_pl iAdd){
		int64_pl iValue;
		#if PLCompiler_Tool == PLCompiler_MSVC
			__asm{
				push rax
				mov rax,iAdd
				lock xadd [ptrObject],rax
				mov iValue,rax
				pop rax
			}
		#elif PLCompiler_Tool == PLCompiler_GCC
			__asm__ __volatile__ ("lock xadd %2,%1 \n movq %2,%0 \n\t" : "=r"(iValue) : "m"(*ptrObject),"r"(iAdd) : "memory");
		#else
			*ptrObject += iAdd;
			iValue = *ptrObject;
		#endif
		return iValue;
	}

	inline int32_pl __PLSysAPI_Synchron_AtomExchangeInteger32(volatile_pl int32_pl * ptrOld,int32_pl iNValue){
		int32_pl iValue;
		#if PLCompiler_Tool == PLCompiler_MSVC
			__asm{
				push eax
				mov  eax,iNewValue
				lock xchg [ptrOldValue],eax
				mov iValue,eax
				pop eax
			}
		#elif PLCompiler_Tool == PLCompiler_GCC
			__asm__ __volatile__ ("lock xchg %2,%1 \n movl %2,%0 \n\t" : "=r"(iValue) : "m"(*ptrOld),"r"(iNValue) : "memory");
		#else

		#endif
		return iValue;
	}


	_PLE_lib_c _CallStack_default_  HPL_Result 			 __PLSysAPI_Synchron_EnterSpinLock(_Syn_SpinLock * ptrLock);
	_PLE_lib_c _CallStack_default_  HPL_Result 			 __PLSysAPI_Synchron_TryEnterSpinLock(_Syn_SpinLock * ptrLock);
	_PLE_lib_c _CallStack_default_  void_pl    			 __PLSysAPI_Synchron_LeaveSpinLock(_Syn_SpinLock * ptrLock);

	_PLE_lib_c _CallStack_default_  HPL_Result 			 __PLSysAPI_Synchron_InitializeLWLock(_Syn_LWLock * ptrLock,int32_pl iInterval);
	_PLE_lib_c _CallStack_default_  HPL_Result 			 __PLSysAPI_Synchron_EnterLWLock(_Syn_LWLock * ptrLock,intV_pl iCount);
	_PLE_lib_c _CallStack_default_  void_pl				 __PLSysAPI_Synchron_LeaveLWLock(_Syn_LWLock * ptrLock);
	_PLE_lib_c _CallStack_default_  void_pl     		 __PLSysAPI_Synchron_ReleaseLWLock(_Syn_LWLock * ptrLock);


	_PLE_lib_c _CallStack_default_	HPL_Result  		 __PLSysAPI_Synchron_InitializeCriticalSectionLock(_Syn_CriticalSection * ptrlock);
	_PLE_lib_c _CallStack_default_  HPL_Result  		 __PLSysAPI_Synchron_EnterCriticalSectionLock	 (_Syn_CriticalSection * ptrlock);
	_PLE_lib_c _CallStack_default_  bool_pl     		 __PLSysAPI_Synchron_TryEnterCriticalSectionLock  (_Syn_CriticalSection * ptrlock);
	_PLE_lib_c _CallStack_default_  void_pl     		 __PLSysAPI_Synchron_LeaveCriticalSectionLock	 (_Syn_CriticalSection * ptrlock);
	_PLE_lib_c _CallStack_default_  void_pl     		 __PLSysAPI_Synchron_ReleaseCriticalSectionLock	 (_Syn_CriticalSection * ptrlock);

	_PLE_lib_c _CallStack_default_  _Syn_SysMutexLock	 __PLSysAPI_Synchron_CreateMutexLock(const_pl char_pl * ptrName,intV_pl iSize);
	_PLE_lib_c _CallStack_default_  HPL_Result  		 __PLSysAPI_Synchron_WaitMutexLock(_Syn_SysMutexLock lock);
	_PLE_lib_c _CallStack_default_  HPL_Result  		 __PLSysAPI_Synchron_WaitTimerMutexLock(_Syn_SysMutexLock lock,intV_pl iWaitTimer);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_ReleaseMutexLock(_Syn_SysMutexLock lock);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_DestroyMutexLock(_Syn_SysMutexLock lock);

	_PLE_lib_c _CallStack_default_  _Syn_SysEventLock	 __PLSysAPI_Synchron_CreateEventLock();
	_PLE_lib_c _CallStack_default_  _Syn_SysEventLock	 __PLSysAPI_Synchron_CreateEventLockN(const_pl char_pl * ptrName,intV_pl iSize);
	_PLE_lib_c _CallStack_default_  HPL_Result  		 __PLSysAPI_Synchron_WaitEventLock(_Syn_SysEventLock lock);
	_PLE_lib_c _CallStack_default_  HPL_Result  		 __PLSysAPI_Synchron_WaitTimerEventLock(_Syn_SysEventLock lock,intV_pl iWaitTimer);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_SendEventLock(_Syn_SysEventLock lock);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_DestroyEventLock(_Syn_SysEventLock lock);

	_PLE_lib_c _CallStack_default_  _Syn_SemaphoreLock	 __PLSysAPI_Synchron_CreateSemaphore(const_pl char_pl * ptrName,intV_pl iSize,intV_pl iCount);
	_PLE_lib_c _CallStack_default_  HPL_Result  		 	 __PLSysAPI_Synchron_WaitSemaphore(_Syn_SemaphoreLock lock);
	_PLE_lib_c _CallStack_default_  HPL_Result  		 	 __PLSysAPI_Synchron_WaitTimerSemaphore(_Syn_SemaphoreLock lock,intV_pl iWaitTimer);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_ReleaseSemaphore(_Syn_SemaphoreLock lock);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_ReleaseSemaphoreCount(_Syn_SemaphoreLock lock,intV_pl iCount);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_DestroySemaphore(_Syn_SemaphoreLock lock);

	_PLE_lib_c _CallStack_default_  bool_pl              __PLSysAPI_Synchron_InitializeRWLockRF(_Syn_RWLockRF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_AcquireRWLockReadRF(_Syn_RWLockRF & lock);
	_PLE_lib_c _CallStack_default_  void_pl				  __PLSysAPI_Synchron_ReleaseRWLockReadRF(_Syn_RWLockRF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_AcquireRWLockWriteRF(_Syn_RWLockRF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_TryAcquireRWLockWriteRF(_Syn_RWLockRF & lock);
	_PLE_lib_c _CallStack_default_  void_pl 			 	  __PLSysAPI_Synchron_ReleaseRWLockWriteRF(_Syn_RWLockRF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_ReleaseRWLockRF(_Syn_RWLockRF & lock);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_ForceReleaseRWLockRF(_Syn_RWLockRF & lock);

	_PLE_lib_c _CallStack_default_  bool_pl              __PLSysAPI_Synchron_InitializeRWLockWF(_Syn_RWLockWF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_AcquireRWLockReadWF(_Syn_RWLockWF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_TryAcquireRWLockReadWF(_Syn_RWLockWF & lock);
	_PLE_lib_c _CallStack_default_  void_pl				  __PLSysAPI_Synchron_ReleaseRWLockReadWF(_Syn_RWLockWF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_AcquireRWLockWriteWF(_Syn_RWLockWF & lock);
	_PLE_lib_c _CallStack_default_  void_pl 			 	  __PLSysAPI_Synchron_ReleaseRWLockWriteWF(_Syn_RWLockWF & lock);
	_PLE_lib_c _CallStack_default_  HPL_Result           __PLSysAPI_Synchron_ReleaseRWLockWF(_Syn_RWLockWF & lock);
	_PLE_lib_c _CallStack_default_  void_pl              __PLSysAPI_Synchron_ForceReleaseRWLockWF(_Syn_RWLockWF & lock);

	_PLE_lib_c _CallStack_default_  HPL_Result 			 __PLSysAPI_Synchron_InitializeThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_PLE_lib_c _CallStack_default_  HPL_Result 			 __PLSysAPI_Synchron_EnterThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_PLE_lib_c _CallStack_default_  HPL_Result 			 __PLSysAPI_Synchron_TryEnterThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_PLE_lib_c _CallStack_default_  void_pl    			 __PLSysAPI_Synchron_LeaveThreadSpinLock(_Syn_TSpinLock * ptrLock);
	_PLE_lib_c _CallStack_default_  void_pl    			 __PLSysAPI_Synchron_ReleaseThreadSpinLock(_Syn_TSpinLock * ptrLock);
//	typedef struct Aligned(8) SPL_ResourceItem {
//		_Syn_SpinLock loadLock;						//
//		_Syn_SpinLock relaseLock;					//
//		HResourceMagrItemAndle hAndle;
//	}__Aligned(8) PL_ResourceItem;
	//	#ifdef __PL_Synchron_DataType_
//#define  PLTSys_Mutex  _Syn_SysMutexLock
//#define  PLTSys_Signal _Syn_SysSignalLock


	#define PLSysAPI_Syn_InitAtomLock		 __PLSysAPI_Synchron_InitAtomLock
	#define PLSysAPI_Syn_BeginAtomLock       __PLSysAPI_Synchron_BeginAtomLock
	#define PLSysAPI_Syn_EndAtomLock		 __PLSysAPI_Synchron_EndAtomLock
	#define PLSysAPI_Syn_EnterAtomLock		 __PLSysAPI_Synchron_EnterAtomLock
	#define PLSysAPI_Syn_ReleaseAtomLock	 __PLSysAPI_Synchron_ReleaseAtomLock
	#define PLSysAPI_Syn_CheckAtomLock 		 __PLSysAPI_Synchron_CheckAtomLock
	#define PLSysAPI_Syn_LeaveAtomLock       PLSysAPI_Syn_EndAtomLock

	#define PLSysAPI_Syn_AtomInterAdd32      __PLSysAPI_Synchron_AtomVIntegerAdd32
	#define PLSysAPI_Syn_AtomInterAdd64      __PLSysAPI_Synchron_AtomVIntegerAdd64

	#define PLSysAPI_Syn_AtomInterExchange32 __PLSysAPI_Synchron_AtomExchangeInteger32

	#define PLSysAPI_Syn_InitializeLWLock    __PLSysAPI_Synchron_InitializeLWLock
	#define PLSysAPI_Syn_EnterLWLock		 __PLSysAPI_Synchron_EnterLWLock
	#define PLSysAPI_Syn_LeaveLWLock		 __PLSysAPI_Synchron_LeaveLWLock

	#define PLSysAPI_Syn_EnterSpinLock       __PLSysAPI_Synchron_EnterSpinLock
	#define PLSysAPI_Syn_TryEnterSpinLock	 __PLSysAPI_Synchron_TryEnterSpinLock
	#define PLSysAPI_Syn_LeaveSpinLock       __PLSysAPI_Synchron_LeaveSpinLock

	#define PLSysAPI_Syn_InitializeCriticalSectionLock 		__PLSysAPI_Synchron_InitializeCriticalSectionLock
	#define PLSysAPI_Syn_EnterCriticalSectionLock			__PLSysAPI_Synchron_EnterCriticalSectionLock
	#define PLSysAPI_Syn_TryEnterCriticalSectionLock		__PLSysAPI_Synchron_TryEnterCriticalSectionLock
	#define PLSysAPI_Syn_LeaveCriticalSectionLock			__PLSysAPI_Synchron_LeaveCriticalSectionLock
	#define PLSysAPI_Syn_ReleaseCriticalSectionLock			__PLSysAPI_Synchron_ReleaseCriticalSectionLock

	#define PLSysAPI_Syn_CreateMutexLock					__PLSysAPI_Synchron_CreateMutexLock
	#define PLSysAPI_Syn_WaitMutexLock				  		__PLSysAPI_Synchron_WaitMutexLock
	#define PLSysAPI_Syn_WaitTimerMutexLock					__PLSysAPI_Synchron_WaitTimerMutexLock
	#define PLSysAPI_Syn_RestMutexLock						__PLSysAPI_Synchron_RestMutexLock
	#define PLSysAPI_Syn_DestroyMutexLock					__PLSysAPI_Synchron_DestroyMutexLock

	#define PLSysAPI_Syn_CreateEventLock					__PLSysAPI_Synchron_CreateEventLock
	#define PLSysAPI_Syn_CreateEventLockN					__PLSysAPI_Synchron_CreateEventLockN
	#define PLSysAPI_Syn_WaitEventLock				  		__PLSysAPI_Synchron_WaitEventLock
	#define PLSysAPI_Syn_WaitTimerEventLock					__PLSysAPI_Synchron_WaitTimerEventLock
	#define PLSysAPI_Syn_SendEventLock						__PLSysAPI_Synchron_SendEventLock
	#define PLSysAPI_Syn_DestroyEventLock					__PLSysAPI_Synchron_DestroyEventLock

	#define PLSysAPI_Syn_CreateSemaphore					__PLSysAPI_Synchron_CreateSemaphore
	#define PLSysAPI_Syn_WaitSemaphore						__PLSysAPI_Synchron_WaitSemaphore
	#define PLSysAPI_Syn_WaitTimerSemaphore					__PLSysAPI_Synchron_WaitTimerSemaphore
	#define PLSysAPI_Syn_ReleaseSemaphore              		__PLSysAPI_Synchron_ReleaseSemaphore
	#define PLSysAPI_Syn_ReleaseSemaphoreCount				__PLSysAPI_Synchron_ReleaseSemaphoreCount
	#define PLSysAPI_Syn_DestroySemaphore					__PLSysAPI_Synchron_DestroySemaphore

	#define PLSysAPI_Syn_InitializeRWLockRF					__PLSysAPI_Synchron_InitializeRWLockRF
	#define PLSysAPI_Syn_AcquireRWLockReadRF				__PLSysAPI_Synchron_AcquireRWLockReadRF
	#define PLSysAPI_Syn_ReleaseRWLockReadRF				__PLSysAPI_Synchron_ReleaseRWLockReadRF
	#define PLSysAPI_Syn_TryAcquireRWLockWriteRF			__PLSysAPI_Synchron_TryAcquireRWLockWriteRF
	#define PLSysAPI_Syn_AcquireRWLockWriteRF				__PLSysAPI_Synchron_AcquireRWLockWriteRF
	#define PLSysAPI_Syn_ReleaseRWLockWriteRF				__PLSysAPI_Synchron_ReleaseRWLockWriteRF
	#define PLSysAPI_Syn_ReleaseRWLockRF					__PLSysAPI_Synchron_ReleaseRWLockRF
	#define PLSysAPI_Syn_ForceReleaseRWLockRF				__PLSysAPI_Synchron_ForceReleaseRWLockRF

	#define PLSysAPI_Syn_InitializeRWLockWF				__PLSysAPI_Synchron_InitializeRWLockWF
	#define PLSysAPI_Syn_TryAcquireRWLockReadWF			__PLSysAPI_Synchron_TryAcquireRWLockReadWF
	#define PLSysAPI_Syn_AcquireRWLockReadWF				__PLSysAPI_Synchron_AcquireRWLockReadWF
	#define PLSysAPI_Syn_ReleaseRWLockReadWF				__PLSysAPI_Synchron_ReleaseRWLockReadWF
	#define PLSysAPI_Syn_AcquireRWLockWriteWF				__PLSysAPI_Synchron_AcquireRWLockWriteWF
	#define PLSysAPI_Syn_ReleaseRWLockWriteWF				__PLSysAPI_Synchron_ReleaseRWLockWriteWF
	#define PLSysAPI_Syn_ReleaseRWLockWF					__PLSysAPI_Synchron_ReleaseRWLockWF
	#define PLSysAPI_Syn_ForceReleaseRWLockWF				__PLSysAPI_Synchron_ForceReleaseRWLockWF

	#define PLSysAPI_Syn_InitializeThreadSpinLock		__PLSysAPI_Synchron_InitializeThreadSpinLock
	#define PLSysAPI_Syn_EnterThreadSpinLock				__PLSysAPI_Synchron_EnterThreadSpinLock
	#define PLSysAPI_Syn_TryEnterThreadSpinLock			__PLSysAPI_Synchron_TryEnterThreadSpinLock
	#define PLSysAPI_Syn_LeaveThreadSpinLock				__PLSysAPI_Synchron_LeaveThreadSpinLock
	#define PLSysAPI_Syn_ReleaseThreadSpinLock			__PLSysAPI_Synchron_ReleaseThreadSpinLock

	#define PLSysAPI_Syn_InitializeResourceItem			__PLSysAPI_Synchron_InitializeResourceItem
	#define PLSysAPI_Syn_ReleaseResourceItem				__PLSysAPI_Synchron_ReleaseResourceItem
	#if PLCPU_IAXX == PLCPU_IA32
		#define PLSysAPI_Syn_AtomInterAdd PLSysAPI_Syn_AtomInterAdd32
		#define PLSysAPI_Syn_AtomInterExchange PLSysAPI_Syn_AtomInterExchange32
	#elif  PLCPU_IAXX == PLCPU_IA32
		#define PLSysAPI_Syn_AtomInterAdd PLSysAPI_Syn_AtomInterAdd64
		#define PLSysAPI_Syn_AtomInterExchange
	#endif
	//#define PLSysAPI_Syn_AtomVIntegerAdd
//	#define

#endif /* PLENGINESYSSYNCHRON_H_ */
