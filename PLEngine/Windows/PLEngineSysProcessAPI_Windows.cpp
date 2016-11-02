/*
 * PLEngineSysProcessAPI_Windows.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../header/Windows/PLEngineSysProcessAPI_Windows.h"
#if PLOperat_System == PLOperatSystem_Window
	uint_pl __stdcall __win_thread_callback(void_pl *);
	void_pl __stdcall __PLSysAPI_SystemProcess_ExitProess_(intV_pl iCode){
		::ExitProcess((UINT)iCode);
	}
	HPL_Result __PLSysAPI_SystemProcess_AllocTLSKey(PLTLSKey * ptrKey,_PLTLSKey_endthreadCallback threadcallback){
		DWORD tKey;
		(*ptrKey) = PLTLSKey_Invalid;
		tKey = TlsAlloc();
		if(tKey!=PLTLSKey_Invalid){
			TlsSetValue(tKey,NULL_PL);
			(*ptrKey) = (PLTLSKey)tKey;
			PLSysAPI_WinLocal_InsertTLSToQueue(g_ptrTLSQueue,&tKey,threadcallback);
			return HPLResult_OK;
		}
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemProcess_FreeTLSKey(PLTLSKey * ptrKey){
		DWORD tKey;
		tKey = (DWORD)(*ptrKey);
		PLSysAPI_WinLocal_RemoveTLSToQueue(g_ptrTLSQueue,&tKey);
		TlsFree(tKey);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetTLSValue(PLTLSKey * ptrKey,void_pl * ptrValue){
		DWORD tKey;
		tKey = (DWORD)(*ptrKey);
		if(TlsSetValue(tKey,ptrValue)==FALSE)
			return HPLResult_Fail;
		return HPLResult_OK;
	}
	void_pl *  __PLSysAPI_SystemProcess_GetTLSValue(PLTLSKey * ptrKey){
		DWORD tKey;
		tKey = (DWORD)(*ptrKey);
		return (void_pl *)TlsGetValue(tKey);
	}

	HPL_Result __PLSysAPI_SystemProcess_CreatThread(PLThreadHandle * ptrhWnd,PLThreadAttr * ptrAttr,
												__pl_thread_callbacktype callback,void_pl * ptrParamer){
		uintV_pl tTid;
		intV_pl iAllocSize;
		uintV_pl uStackSize;
		PLThreadDataPackage * ptrTDP;
		iAllocSize = PL_CompilerAllocSize(PLThreadDataPackage);
		iAllocSize = PLSysAPI_Alignment(iAllocSize,PLSys_Const_CPUCacheLineSize);
		//temporarily allocate memory save PLThreadDataPackage object
		ptrTDP = (PLThreadDataPackage *)PLSysAPI_AllocateMemory(iAllocSize);
		if(ptrTDP==NULL_PL)
			return HPLResult_Fail;
		PLSysAPI_MemoryClearZero((void_pl *)ptrTDP,PL_CompilerAllocSize(PLThreadDataPackage));
		ptrTDP->ptrData  = ptrParamer;
		ptrTDP->callback = callback;
		uStackSize = 0;
		if((ptrAttr!=NULL) && (ptrAttr->uTag!=0)){
			if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Stack_Set) == PLSys_Const_SysThreadAttr_Stack_Set){
				if(ptrAttr->iStackSize>PLTHREAD_STACK_MIN_SIZE)
					uStackSize = ptrAttr->iStackSize;
			}
			if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Policy_Set) == PLSys_Const_SysThreadAttr_Policy_Set){

			}
		}
		//PLTHREAD_STACK_MIN_SIZE
		tTid = _beginthreadex(NULL_PL,uStackSize,__win_thread_callback,(void_pl *)ptrTDP,0,NULL_PL);
		if(tTid==0){
			(*ptrhWnd) = PLThreadHandle_Invalid;
			PLSysAPI_FreeMemory((void_pl *)ptrTDP);
			return HPLResult_Fail;
		}
		(*ptrhWnd) = tTid;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_JoinThread(PLThreadHandle hTWnd){

		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_KillThread(PLThreadHandle hTWnd){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority eLevel){
		HANDLE hAndle;
		intV_pl iPriority;
		if(hTWnd == PLThreadHandle_Invalid)
			return HPLResult_Fail;
		hAndle = (HANDLE)hTWnd;
		/*
#define THREAD_PRIORITY_ERROR_RETURN 2147483647
		*/
		switch(eLevel){
			case PLSys_Const_SysThreadPriority_Normal:{
				iPriority = THREAD_PRIORITY_NORMAL;
			}break;
			case PLSys_Const_SysThreadPriority_Max:{
				iPriority = THREAD_PRIORITY_TIME_CRITICAL;
			}break;
			case PLSys_Const_SysThreadPriority_Min:{
				iPriority = THREAD_PRIORITY_IDLE;
			}break;
			case PLSys_Const_SysThreadPriority_Hight:{
				iPriority = THREAD_PRIORITY_ABOVE_NORMAL;
			}break;
			case PLSys_Const_SysThreadPriority_Hot:{
				iPriority = THREAD_PRIORITY_HIGHEST;
			}break;
			case PLSys_Const_SysThreadPriority_Low:{
				iPriority = THREAD_PRIORITY_BELOW_NORMAL;
			}break;
			case PLSys_Const_SysThreadPriority_Idel:{
				iPriority = THREAD_PRIORITY_LOWEST;
			}break;
			default:
				return HPLResult_Fail;
			break;
		}
		if(SetThreadPriority(hAndle,iPriority)==FALSE)
			return HPLResult_Fail;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority *  ptreLevel){
		HANDLE hAndle;
		intV_pl iPriority;
		if(hTWnd == PLThreadHandle_Invalid)
			return HPLResult_Fail;
		hAndle = (HANDLE)hTWnd;
		iPriority = GetThreadPriority(hAndle);
		if((iPriority ==THREAD_PRIORITY_ERROR_RETURN) || (iPriority>THREAD_PRIORITY_TIME_CRITICAL) || (iPriority<THREAD_PRIORITY_IDLE))
			return HPLResult_Fail;
		if(iPriority == THREAD_PRIORITY_NORMAL){
			(*ptreLevel) =  PLSys_Const_SysThreadPriority_Normal;
		}else if(iPriority > THREAD_PRIORITY_NORMAL){
			if(iPriority<=THREAD_PRIORITY_ABOVE_NORMAL){
				(*ptreLevel) =  PLSys_Const_SysThreadPriority_Hight;
			}else if(iPriority == THREAD_PRIORITY_TIME_CRITICAL){
				(*ptreLevel) =  PLSys_Const_SysThreadPriority_Max;
			}else{
				(*ptreLevel) =  PLSys_Const_SysThreadPriority_Hot;
			}
		}else{
			if(iPriority >= THREAD_PRIORITY_BELOW_NORMAL){
				(*ptreLevel) =  PLSys_Const_SysThreadPriority_Low;
			}else if(iPriority == THREAD_PRIORITY_IDLE){
				(*ptreLevel) =  PLSys_Const_SysThreadPriority_Min;
			}else{
				(*ptreLevel) =  PLSys_Const_SysThreadPriority_Idel;
			}
		}
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy){
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy *  ptrePolicy){
		(*ptrePolicy) = PLSys_Const_SysThreadPolicy_FIFO;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr){
		HANDLE hAndle;
		uintV_pl uTag;
		intV_pl iPriority;
		uTag = 0;
		if(hTWnd == PLThreadHandle_Invalid)
			return HPLResult_Fail;
		hAndle = (HANDLE)hTWnd;
		if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Stack_Set) == PLSys_Const_SysThreadAttr_Stack_Set){
			//ptrAttr->iStackSize = tSize;
			//uTag |= PLSys_Const_SysThreadAttr_Stack_Set;
		}else if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_StackSize_Set) == PLSys_Const_SysThreadAttr_StackSize_Set){
//			ptrAttr->iStackSize = tStackSize;
//			uTag |= PLSys_Const_SysThreadAttr_StackSize_Set;
		}
		//get thread's attrib is policy
		if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Policy_Set) == PLSys_Const_SysThreadAttr_Policy_Set){
//			ptrAttr->ePolicy = PLSys_Const_SysThreadPolicy_FIFO;
//			uTag |= PLSys_Const_SysThreadAttr_Policy_Set;
		}
		//get thread's attrib is priority
		if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Priority_Set) == PLSys_Const_SysThreadAttr_Priority_Set){
			iPriority = ptrAttr->iPriority;
			if(iPriority>THREAD_PRIORITY_TIME_CRITICAL)
				iPriority = THREAD_PRIORITY_TIME_CRITICAL;
			else if(iPriority < THREAD_PRIORITY_IDLE)
				iPriority = THREAD_PRIORITY_IDLE;
			if(SetThreadPriority(hAndle,iPriority)==TRUE){
				if(iPriority!=THREAD_PRIORITY_ERROR_RETURN){
					uTag |= PLSys_Const_SysThreadAttr_Priority_Set;
					ptrAttr->iPriority = iPriority;
				}
			}
		}
		if(uTag==0)
			return HPLResult_Fail;
		ptrAttr->uTag = uTag;
		return HPLResult_OK;
	}
	void_pl    __PLSysAPI_SystemProcess_GetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr){
		HANDLE hAndle;
//		int_pl iMax,iMin;
		intV_pl iPriority;
		uintV_pl uTag;
		uTag = ptrAttr->uTag;
		ptrAttr->uTag = 0;
		if(hTWnd == PLThreadHandle_Invalid)
			return;
		hAndle = (HANDLE)hTWnd;
		if((uTag & PLSys_Const_SysThreadAttr_Stack_Set) == PLSys_Const_SysThreadAttr_Stack_Set){
//			ptrAttr->iStackSize = tSize;
//			ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Stack_Set;
		}else if((uTag & PLSys_Const_SysThreadAttr_StackSize_Set) == PLSys_Const_SysThreadAttr_StackSize_Set){
//				ptrAttr->iStackSize = tStackSize;
//				uTag |= PLSys_Const_SysThreadAttr_StackSize_Set;
		}
		//get thread's attrib is policy
		if((uTag & PLSys_Const_SysThreadAttr_Policy_Set) == PLSys_Const_SysThreadAttr_Policy_Set){
			ptrAttr->ePolicy = PLSys_Const_SysThreadPolicy_FIFO;
			ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Policy_Set;
		}
		//get thread's attrib is priority
		if((uTag & PLSys_Const_SysThreadAttr_Priority_Set) == PLSys_Const_SysThreadAttr_Priority_Set){
			iPriority = GetThreadPriority(hAndle);
			if(iPriority!=THREAD_PRIORITY_ERROR_RETURN){
				ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Priority_Set;
				ptrAttr->iPriority = iPriority;
			}
		}
		return;
	}
	HPL_Result __PLSysAPI_SystemProcess_ThreadDetach(PLThreadHandle hTWnd){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPriorityLimit(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy,int_pl * ptriMaxPriority,int_pl * ptriMinPriority){

		if((ePolicy != PLSys_Const_SysThreadPolicy_FIFO) && (ePolicy != PLSys_Const_SysThreadPolicy_Poll))
			return HPLResult_Fail;
		if(ptriMaxPriority!=NULL_PL)
			(*ptriMaxPriority) =  THREAD_PRIORITY_TIME_CRITICAL;
		if(ptriMinPriority!=NULL_PL)
			(*ptriMinPriority) =  THREAD_PRIORITY_IDLE;
		return HPLResult_OK;
	}
	void_pl __PLSysAPI_SystemProcess_ThreadTermin(PLThreadHandle hTWnd){
		HANDLE hAndle;
		hAndle = (HANDLE)hTWnd;
		if(hAndle == PLThreadHandle_Invalid)
			return;
		TerminateThread(hAndle,0);
		return;
	}
	HPL_Result __PLSysAPI_SystemProcess_CloseHandle(PLThreadHandle hTWnd){
		HANDLE hAndle;
		if(hTWnd == PLThreadHandle_Invalid)
			return HPLResult_Fail;
		hAndle = (HANDLE)hTWnd;
		CloseHandle(hAndle);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAffinity(PLThreadHandle hTWnd,uintV_pl uProcessorMark,uintV_pl * ptrOldProcessorMark){
		HANDLE hAndle;
		uintV_pl uOldProcessorMark;
		if(hTWnd == PLThreadHandle_Invalid)
			return HPLResult_Fail;
		hAndle = (HANDLE)hTWnd;
		uOldProcessorMark = SetThreadAffinityMask(hAndle,uProcessorMark);
		if(ptrOldProcessorMark!=NULL_PL)
			(*ptrOldProcessorMark) = uOldProcessorMark;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAdviceProcessor(PLThreadHandle hTWnd,uintV_pl uProcessor){
		HANDLE hAndle;
		if(hTWnd == PLThreadHandle_Invalid)
			return HPLResult_Fail;
		hAndle = (HANDLE)hTWnd;
		SetThreadIdealProcessor(hAndle,uProcessor);
		return HPLResult_OK;
	}
	void_pl __PLSysAPI_SystemProcess_Sleep(int64_pl iTimer){
		iTimer/=1000000;
		Sleep(*((DWORD *)(&iTimer)));
	}
/**    ------------------Windows Local Function------------------  **/
	PPL_EngineTLSQueue PLSysAPI_WinLocal_InitializeTLSQueue(){
		intV_pl iAllocSize;
		PPL_EngineTLSQueue ptrTLSQueue;
		intV_pl iCount;
		ptrTLSQueue = NULL_PL;
		do{
			iAllocSize = PL_CompilerAllocSize(PL_EngineTLSQueue);
			iAllocSize = PLSysAPI_Alignment(iAllocSize,PLSys_Const_CPUCacheLineSize);
			ptrTLSQueue = (PPL_EngineTLSQueue)PLSysAPI_AllocateMemory(iAllocSize);
			if(ptrTLSQueue==NULL_PL)
				break;
			PLSysAPI_MemoryClearZero((void_pl *)ptrTLSQueue,PL_CompilerAllocSize(PL_EngineTLSQueue));
			for(iCount = 0;iCount<PLEngine_Const_TLSUnitMaxNum;iCount++){
				ptrTLSQueue->TlsKeyList[iCount] = PLTLSKey_Invalid;
				ptrTLSQueue->TlsDataCallBack[iCount] = NULL_PL;
			}
		}while(0);
		return ptrTLSQueue;
	}
	//PPL_EngineTLSQueue,PLTLSKey *,_PLTLSKey_endthreadCallback callback
	HPL_Result PLSysAPI_WinLocal_InsertTLSToQueue(PPL_EngineTLSQueue ptrQueue,PLTLSKey * ptrKey,_PLTLSKey_endthreadCallback callback){
		intV_pl iCount;
		PPL_EngineTLSQueue ptrNext;
		ptrNext = ptrQueue;
		iCount = 0;
		if(ptrQueue==NULL_PL)
			return HPLResult_Fail;
		while(ptrNext!=NULL_PL){
			for(iCount = 0;iCount<PLEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrQueue->TlsKeyList[iCount]==PLTLSKey_Invalid){
					ptrQueue->TlsKeyList[iCount]      = *ptrKey;
					ptrQueue->TlsDataCallBack[iCount] = callback;
					return HPLResult_OK;
				}
			}
		}
		if(iCount >= PLEngine_Const_TLSUnitMaxNum){
			int_pl iAllocSize;
			ptrNext = ptrQueue;
			while(ptrNext->pNext!=NULL_PL)
				ptrNext = ptrNext->pNext;
			iAllocSize = PL_CompilerAllocSize(PL_EngineTLSQueue);
			iAllocSize = PLSysAPI_Alignment(iAllocSize,PLSys_Const_CPUCacheLineSize);
			ptrNext->pNext = (PPL_EngineTLSQueue)PLSysAPI_AllocateMemory(iAllocSize);
			if(ptrNext->pNext==NULL_PL)
				return HPLResult_Fail;
			PLSysAPI_MemoryClearZero((void_pl *)(ptrNext->pNext),PL_CompilerAllocSize(PL_EngineTLSQueue));
			for(iCount = 0;iCount<PLEngine_Const_TLSUnitMaxNum;iCount++){
				ptrNext->pNext->TlsKeyList[iCount] = PLTLSKey_Invalid;
				ptrNext->pNext->TlsDataCallBack[iCount] = NULL_PL;
			}
			ptrNext->pNext->TlsKeyList[0] = *ptrKey;
			ptrNext->pNext->TlsDataCallBack[0] = callback;
		}
		return HPLResult_OK;
	}
	HPL_Result PLSysAPI_WinLocal_RemoveTLSToQueue(PPL_EngineTLSQueue ptrQueue,PLTLSKey * ptrKey){
		PPL_EngineTLSQueue ptrNext;
		intV_pl iCount;
		ptrNext = ptrQueue;
		if(ptrQueue==NULL_PL)
			return HPLResult_Fail;
		while(ptrNext!=NULL_PL){
			for(iCount=0;iCount < PLEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrNext->TlsKeyList[iCount] == (*ptrKey)){
					ptrNext->TlsKeyList[iCount] = PLTLSKey_Invalid;
					ptrNext->TlsDataCallBack[iCount] = NULL_PL;
					break;
				}
			}
			ptrNext = ptrNext->pNext;
		}
		return HPLResult_OK;
	}
	HPL_Result PLSysAPI_WinLocal_DestoryTLSToQueue(PPL_EngineTLSQueue * pptrQueue){
		PPL_EngineTLSQueue ptrQueue;
		PPL_EngineTLSQueue ptrCurQueue;
		if((pptrQueue==NULL_PL) || ((*pptrQueue)==NULL_PL))
			return HPLResult_Fail;
		ptrQueue = (*pptrQueue);
		while(ptrQueue!=NULL_PL){
			ptrCurQueue = ptrQueue;
			ptrQueue = ptrQueue->pNext;
			PLSysAPI_FreeMemory((void_pl *)ptrCurQueue);
		}
		*pptrQueue = NULL_PL;
		return HPLResult_OK;
	}
	HPL_Result PLSysAPI_WinLocal_NotifyTLSDataFree(PPL_EngineTLSQueue ptrQueue,PLTLSKey * ptrKey){
		PPL_EngineTLSQueue ptrNextQueue;
		if((*ptrKey) == PLTLSKey_Invalid)
			return HPLResult_Fail;
		void_pl *          ptrData;
		intV_pl iCount;
		ptrNextQueue = ptrQueue;
		while(ptrNextQueue!=NULL_PL){
			for(iCount = 0;iCount<PLEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrNextQueue->TlsKeyList[iCount]==(*ptrKey)){
					if(ptrNextQueue->TlsDataCallBack[iCount]==NULL_PL)
						return HPLResult_Fail;
					ptrData = (void_pl *)TlsGetValue(ptrNextQueue->TlsKeyList[iCount]);
					ptrNextQueue->TlsDataCallBack[iCount]((void_pl *)ptrData);
					TlsSetValue(ptrNextQueue->TlsKeyList[iCount],NULL_PL);
					return HPLResult_OK;
				}
			}
			ptrNextQueue = ptrNextQueue->pNext;
		}
		return HPLResult_Fail;
	}
	HPL_Result PLSysAPI_WinLocal_NotifyTLSDataAllFree(PPL_EngineTLSQueue ptrQueue){
		PPL_EngineTLSQueue ptrNextQueue;
		void_pl *          ptrData;
		intV_pl iCount;
		ptrNextQueue = ptrQueue;
		while(ptrNextQueue!=NULL_PL){
			for(iCount = 0;iCount<PLEngine_Const_TLSUnitMaxNum;iCount++){
				if(ptrNextQueue->TlsKeyList[iCount]!=PLTLSKey_Invalid){
					if(ptrNextQueue->TlsDataCallBack[iCount]!=NULL_PL){
						ptrData = TlsGetValue(ptrNextQueue->TlsKeyList[iCount]);
						ptrNextQueue->TlsDataCallBack[iCount]((void_pl *)ptrData);
					}
					TlsSetValue(ptrNextQueue->TlsKeyList[iCount],NULL_PL);
				}
			}
			ptrNextQueue = ptrNextQueue->pNext;
		}
		return HPLResult_OK;
	}
	uint_pl __win_thread_callback(void_pl * ptrData){
		PLThreadDataPackage   StTDP;
		intV_pl iAllocSize;
		iAllocSize = PL_CompilerAllocSize(PLThreadDataPackage);
		PLSysAPI_MemoryClearZero((void_pl *)(&StTDP),iAllocSize);
		PLSysAPI_MemoryCpy((void_pl *)(&StTDP),(PLThreadDataPackage *)ptrData,PL_CompilerAllocSize(PLThreadDataPackage));
		PLSysAPI_FreeMemory(ptrData);
		try{
			StTDP.callback(StTDP.ptrData);
		}catch(...){

		}
		return 0;
	}
/**   --------------------End Windows Local Function-----------------------  **/
#endif
