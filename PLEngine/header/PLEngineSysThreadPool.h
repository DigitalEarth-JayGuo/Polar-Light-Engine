/*
 * PLEngineSysThreadPool.h
 *
 *  Created on: 2009-11-5
 *      Author: Administrator
 */
#include "PLEngineH.h"
#include "PLEngineSysAPI.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#include "PLEngineMemoryPool.h"
#include "PLEngineSysSynchron.h"
#include "PLEngineSysProcess.h"
#include "PLEngineSysSTLArithmeticAPI.h"
#ifndef PLENGINESYSTHREADPOOL_H_
#define PLENGINESYSTHREADPOOL_H_
#pragma pack(8)

	typedef struct Aligned(8) _SPLTPoolItem{
		HThreadPool hPool;
		_SPLTPoolItem *        ptrUp;
		_SPLTPoolItem * 		ptrNext;
		PLThreadHandle 			hAndle;
		_Syn_SysEventLock		waitlock;
		ePL_SysThreadPriority   eLevelPriority;
		uintV_pl                uCpuMark;
		volatile_pl bool_pl     bAtQueue;
		volatile_pl intV_pl     iExit;
		_Syn_SpinLock 			statelock;
		volatile_pl ePL_SysTPThreadItemState eState;
	}__Aligned(8) PLTPoolItem;
	typedef struct Aligned(8) _SPLTPoolTasker{
		__pl_thread_callbacktype callback;
		void_pl * ptrParmer;
		intV_pl iRPI;
		ePL_SysThreadPriority eLevelPriority;
	}__Aligned(8) PLTPoolTasker;

	struct __stl_ThreadPoolPriorityQueue_CmpFunc{
		inline bool_pl MovUp(PLTPoolTasker * & key1,PLTPoolTasker * & key2){
			return (key1->iRPI < key2->iRPI) ? true_pl : false_pl;
		}
	};

	typedef __plstl_PriorityQueue_class<PLTPoolTasker,__stl_ThreadPoolPriorityQueue_CmpFunc>  ThreadPoolPriorityQueue;

	typedef struct Aligned(8) _SPLThreadPool{
		ePL_SysThreadPoolTaskerState eState;
		intV_pl iMaxCount;
		PLTPoolItem * ptrItem;
		volatile_pl intV_pl iIdeCount;
		PLTPoolItem * ptrStoreItem;
		_Syn_SpinLock storelock;
		ThreadPoolPriorityQueue * ptrTaskerQueue;
	} __Aligned(8) PLThreadPool;

#pragma pack()
	uint_pl __pl_threadpool_callback(void_pl * ptrData);

	_PLE_lib_c _CallStack_default_ HThreadPool 		__PLSysAPI_SystemProcess_CreateThreadPool(PLThreadPoolParamer * ptrParamer);
	_PLE_lib_c _CallStack_default_ bool_pl     		__PLSysAPI_SystemProcess_RunThreadPool(HThreadPool hAndle);
	_PLE_lib_c _CallStack_default_ intV_pl 	   		__PLSysAPI_SystemProcess_GetThreadPoolMaxSize(HThreadPool hAndle);
	_PLE_lib_c _CallStack_default_ intV_pl 	   		__PLSysAPI_SystemProcess_GetTaskerCount(HThreadPool hAndle);
	_PLE_lib_c _CallStack_default_ void_pl     		__PLSysAPI_SystemProcess_StopThreadPool(HThreadPool hAndle);
	_PLE_lib_c _CallStack_default_ HPL_Result  		__PLSysAPI_SystemProcess_AddThreadPoolTasker(HThreadPool hAndle,PLTPoolTasker * ptrTasker);
	_PLE_lib_c _CallStack_default_ void_pl          __PLSysAPI_SystemProcess_ReleaseThreadPoolTasker(HThreadPool hAndle,PLTPoolTasker * ptrTasker);
	_PLE_lib_c _CallStack_default_ PLTPoolTasker *  __PLSysAPI_SystemProcess_CreateThreadPoolTasker(HThreadPool hAndle);
	_PLE_lib_c _CallStack_default_ void_pl 	   		__PLSysAPI_SystemProcess_DestoryThreadPool(HThreadPool hAndle);

	_SPLTPoolItem * 			__native_PLSysAPI_SystemProcess_GetThreadItem(HThreadPool hAndle);
	void_pl			 			__native_PLSysAPI_SystemProcess_PushThreadItem(HThreadPool hAndle,PLTPoolItem * ptrItem);
	void_pl                     __native_PLSysAPI_SystemProcess_PopThreadItemSelf(HThreadPool hAndle,PLTPoolItem * ptrItem);

	#define PLSysAPI_SystemProcess_CreateThreadPool 		__PLSysAPI_SystemProcess_CreateThreadPool
	#define PLSysAPI_SystemProcess_RunThreadPool	 		__PLSysAPI_SystemProcess_RunThreadPool
	#define PLSysAPI_SystemProcess_GetThreadPoolMaxSize		__PLSysAPI_SystemProcess_GetThreadPoolMaxSize
	#define PLSysAPI_SystemProcess_GetTaskerCount			__PLSysAPI_SystemProcess_GetTaskerCount
	#define PLSysAPI_SystemProcess_StopThreadPool	 		__PLSysAPI_SystemProcess_StopThreadPool
	#define PLSysAPI_SystemProcess_CreateThreadPoolTasker	__PLSysAPI_SystemProcess_CreateThreadPoolTasker
	#define PLSysAPI_SystemProcess_AddThreadPoolTasker 		__PLSysAPI_SystemProcess_AddThreadPoolTasker
	#define PLSysAPI_SystemProcess_ReleaseThreadPoolTasker	__PLSysAPI_SystemProcess_ReleaseThreadPoolTasker
	#define PLSysAPI_SystemProcess_DestoryThreadPool 		__PLSysAPI_SystemProcess_DestoryThreadPool



#endif /* PLENGINESYSTHREADPOOL_H_ */
