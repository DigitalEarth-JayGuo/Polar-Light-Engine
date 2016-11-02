/*
 * PLEngineSysProcess.h
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "PLEngineH.h"
#include "PLEngineSysAPI.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#include "PLEngineSysSynchron.h"
//#include "PLEngineHeavyH.h"
#ifndef PLENGINESYSPROCESS_H_
#define PLENGINESYSPROCESS_H_
//	#ifndef PTHREAD_STACK_MIN
//		#define PTHREAD_STACK_MIN 16384
//	#endif
/*
	#if PLOperat_System == PLOperatSystem_Window

		#define PLTLSKey DWORD
		#define PLTLSKey_Invalid ((DWORD)(~0))
		#define PLThreadHandle_Invalid 0
		#define PLThread_Handle uint_pl
		#define PLThreadHandle  PLThread_Handle
		#define PLEngine_Const_TLSUnitMaxNum TLS_MINIMUM_AVAILABLE * 2
		typedef struct _SPL_TLSQueue{
			_SPL_TLSQueue * pNext;
			PLTLSKey TlsKeyList[PLEngine_Const_TLSUnitMaxNum];
			_PLTLSKey_endthreadCallback TlsDataCallBack[PLEngine_Const_TLSUnitMaxNum];
		}PL_EngineTLSQueue,* PPL_EngineTLSQueue;
		_PLE_lib_Variable PPL_EngineTLSQueue g_ptrTLSQueue;
		_CallStack_default_ PPL_EngineTLSQueue PLSysAPI_WinLocal_InitializeTLSQueue();
		_CallStack_default_ HPL_Result PLSysAPI_WinLocal_InsertTLSToQueue(PPL_EngineTLSQueue,PLTLSKey *,_PLTLSKey_endthreadCallback);
		_CallStack_default_ HPL_Result PLSysAPI_WinLocal_RemoveTLSToQueue(PPL_EngineTLSQueue,PLTLSKey*);
		_CallStack_default_ HPL_Result PLSysAPI_WinLocal_DestoryTLSToQueue(PPL_EngineTLSQueue*);

		_CallStack_default_ HPL_Result PLSysAPI_WinLocal_NotifyTLSDataFree(PPL_EngineTLSQueue,PLTLSKey*);
		_CallStack_default_ HPL_Result PLSysAPI_WinLocal_NotifyTLSDataAllFree(PPL_EngineTLSQueue);
	#else
		#define PLThread_Handle     pthread_t
		#define PLThreadHandle      PLThread_Handle
		#define PLTLSKey 				 pthread_key_t
		#define PLTLSKey_Invalid    ((pthread_key_t)(~0))
		#define PLThreadHandle_Invalid 0
	#endif
*/

//	typedef struct _SPLThreadLocalKey{
//		PLTLSKey tKey;
//		_PLTLSKey_endthreadCallback callback;
//		void_pl * ptrData;
//	}PLThreadLocalKey,* PPLThreadLocalKey;
	void_pl PLTLSKey_ThreadVirtualID_Destory(void_pl *);
	typedef uint_pl (* __pl_thread_callbacktype)(void_pl *);
#pragma pack(8)
	typedef  struct Aligned(8)_SPLThreadDataPackage{
		void_pl * ptrData;
		__pl_thread_callbacktype callback;
	}__Aligned(8) PLThreadDataPackage;
#pragma pack()
	//typedef
	_PLE_lib_c _CallStack_default_ void_pl    __PLSysAPI_SystemProcess_ExitProess_(intV_pl iCode);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_AllocTLSKey(PLTLSKey * ptrKey,_PLTLSKey_endthreadCallback threadcallback);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_FreeTLSKey(PLTLSKey * ptrKey);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_SetTLSValue(PLTLSKey * ptrKey,void_pl * ptrValue);
	_PLE_lib_c _CallStack_default_ void_pl *  __PLSysAPI_SystemProcess_GetTLSValue(PLTLSKey * ptrKey);

	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_CreatThread(PLThreadHandle * ptrhWnd,PLThreadAttr * ptrAttr,__pl_thread_callbacktype callback,void_pl * ptrParamer);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_JoinThread(PLThreadHandle hTWnd);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_KillThread(PLThreadHandle hTWnd);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_SetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr);
	_PLE_lib_c _CallStack_default_ void_pl    __PLSysAPI_SystemProcess_GetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_SetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority eLevel);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_GetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority *  ptreLevel);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_SetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_GetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy *  ptrePolicy);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_GetThreadPriorityLimit(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy,intV_pl * ptriMaxPriority,intV_pl * ptriMinPriority);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_ThreadDetach(PLThreadHandle hTWnd);
	_PLE_lib_c _CallStack_default_ void_pl    __PLSysAPI_SystemProcess_ThreadTermin(PLThreadHandle hTWnd);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_CloseHandle(PLThreadHandle hTWnd);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_SetThreadAffinity(PLThreadHandle hTWnd,uintV_pl uProcessorMark,uintV_pl * ptrOldProcessorMark);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_SetThreadAdviceProcessor(PLThreadHandle hTWnd,uintV_pl uProcessor);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_GetThreadVirtualID(PLThreadVirtualID * ptrVID);
								   PLThreadVirtualID __PLSysAPI_SystemProcess_AllocateThreadVID();
	_PLE_lib_c _CallStack_default_ PLThreadID __PLSysAPI_SystemProcess_GetThreadSelfID();
	_PLE_lib_c _CallStack_default_ PLThreadID __PLSysAPI_SystemProcess_GetThreadID(PLThreadHandle hAndle);

	_PLE_lib_c _CallStack_default_ void_pl    __PLSysAPI_SystemProcess_Sleep(int64_pl iTimer);

	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemProcess_InitializeProcessLibrary();
	_PLE_lib_c _CallStack_default_ void_pl    __PLSysAPI_SystemProcess_ReleaseProcessLibrary();


	#define PLSysAPI_SystemProcess_ExitProess    			__PLSysAPI_SystemProcess_ExitProess_
	#define PLSysAPI_SystemProcess_AllocTLSKey          	__PLSysAPI_SystemProcess_AllocTLSKey
	#define PLSysAPI_SystemProcess_FreeTLSKey           	__PLSysAPI_SystemProcess_FreeTLSKey
	#define PLSysAPI_SystemProcess_SetTLSValue          	__PLSysAPI_SystemProcess_SetTLSValue
	#define PLSysAPI_SystemProcess_GetTLSValue         		__PLSysAPI_SystemProcess_GetTLSValue
	#define PLSysAPI_SystemProcess_CreatThread          	__PLSysAPI_SystemProcess_CreatThread
	#define PLSysAPI_SystemProcess_SetThreadAttr        	__PLSysAPI_SystemProcess_SetThreadAttr
	#define PLSysAPI_SystemProcess_GetThreadAttr        	__PLSysAPI_SystemProcess_GetThreadAttr
	#define PLSysAPI_SystemProcess_ThreadDetach         	__PLSysAPI_SystemProcess_ThreadDetach
	#define PLSysAPI_SystemProcess_GetThreadPriorityLimit 	__PLSysAPI_SystemProcess_GetThreadPriorityLimit
	#define PLSysAPI_SystemProcess_SetThreadPriority        __PLSysAPI_SystemProcess_SetThreadPriority
	#define PLSysAPI_SystemProcess_SetThreadAffinity		__PLSysAPI_SystemProcess_SetThreadAffinity
	#define PLSysAPI_SystemProcess_SetThreadAdviceProcessor	__PLSysAPI_SystemProcess_SetThreadAdviceProcessor
	#define PLSysAPI_SystemProcess_GetThreadVirtualID       __PLSysAPI_SystemProcess_GetThreadVirtualID
	#define PLSysAPI_SystemProcess_AllocateThreadVID        __PLSysAPI_SystemProcess_AllocateThreadVID
	#define PLSysAPI_SystemProcess_Sleep			 		__PLSysAPI_SystemProcess_Sleep
	#define PLSysAPI_SystemProcess_InitializeProcessLibrary __PLSysAPI_SystemProcess_InitializeProcessLibrary
	#define PLSysAPI_SystemProcess_ReleaseProcessLibrary    __PLSysAPI_SystemProcess_ReleaseProcessLibrary
	//PLSysAPI_SystemProcess
#endif /* PLENGINESYSPROCESS_H_ */
