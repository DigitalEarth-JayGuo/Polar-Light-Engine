/*
 * PLEngineSysProcessAPI_Linux.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../header/Linux/PLEngineSysProcessAPI_Linux.h"
#if PLOperat_System == PLOperatSystem_Linux
	//if thread end callback free tls data
	//posix thread callback compatible uesr callback
	void_pl *  __posix_thread_callback(void_pl *);
	void_pl __PLSysAPI_SystemProcess_ExitProess_(int_pl iCode){
		exit(iCode);
	}
	HPL_Result __PLSysAPI_SystemProcess_AllocTLSKey(PLTLSKey * ptrKey,_PLTLSKey_endthreadCallback threadcallback){
		pthread_key_t tKey;
		(*ptrKey) = PLTLSKey_Invalid;
		if(pthread_key_create(&tKey,threadcallback)==0){
			if(pthread_setspecific(tKey,NULL_PL)!=0){
				pthread_key_delete(tKey);
				tKey = PLTLSKey_Invalid;
				(*ptrKey) = (PLTLSKey)tKey;
				return HPLResult_Fail;
			}
			(*ptrKey) = (PLTLSKey)tKey;
			return HPLResult_OK;
		}
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemProcess_FreeTLSKey(PLTLSKey * ptrKey){
		pthread_key_t tKey;
		tKey = (pthread_key_t)(*ptrKey);
		if(tKey == PLTLSKey_Invalid)
			return HPLResult_Fail;
		pthread_setspecific(tKey,NULL_PL);
		if(pthread_key_delete(tKey)!=0)
			return HPLResult_Fail;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetTLSValue(PLTLSKey * ptrKey,void_pl * ptrValue){
		if(pthread_setspecific((pthread_key_t)(*ptrKey),(void_pl *)ptrValue)==0){
			return HPLResult_OK;
		}
		return HPLResult_Fail;
	}
	void_pl *  __PLSysAPI_SystemProcess_GetTLSValue(PLTLSKey * ptrKey){
		return (void_pl *)pthread_getspecific((pthread_key_t)(*ptrKey));
	}

	HPL_Result __PLSysAPI_SystemProcess_CreatThread(PLThreadHandle * ptrhWnd,PLThreadAttr * ptrAttr,__pl_thread_callbacktype callback,void_pl * ptrParamer){
		pthread_t tTid;
		pthread_attr_t tAttr;
		pthread_attr_t * ptrTAttr;
		intV_pl iAllocSize;
		PLThreadDataPackage * ptrTDP;
		ptrTAttr = NULL_PL;
		if(pthread_attr_init(&tAttr)==0){
			do{
				ptrTAttr = &tAttr;
				if(ptrAttr==NULL_PL || ptrAttr->uTag==0){
					if(pthread_attr_setinheritsched(&tAttr,PTHREAD_INHERIT_SCHED)!=0){
						pthread_attr_destroy(&tAttr);
						ptrTAttr = NULL_PL;
					}
					break;
				}
				if(pthread_attr_setinheritsched(&tAttr,PTHREAD_EXPLICIT_SCHED)!=0){
					pthread_attr_destroy(&tAttr);
					ptrTAttr = NULL_PL;
					break;
				}
			#ifdef _POSIX_THREAD_ATTR_STACKADDR
				if(((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Stack_Set) == PLSys_Const_SysThreadAttr_Stack_Set) && (ptrAttr->iStackSize>=PLTHREAD_STACK_MIN_SIZE) && (ptrAttr->ptrStack==NULL_PL)){
					size_t tSize;
					tSize = (size_t)(ptrAttr->iStackSize);
					pthread_attr_setstack(&tAttr,ptrAttr->ptrStack,tSize);
				}
				#ifdef _POSIX_THREAD_ATTR_STACKSIZE
					else
				#endif
			#endif
			#ifdef _POSIX_THREAD_ATTR_STACKSIZE
				if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_StackSize_Set) == PLSys_Const_SysThreadAttr_StackSize_Set){
					size_t tSize;
					tSize = ptrAttr->iStackSize;
					if(tSize<PLTHREAD_STACK_MIN_SIZE)
						tSize = PLTHREAD_STACK_MIN_SIZE;
					pthread_attr_setstacksize(&tAttr,tSize);
				}
			#endif
				if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Policy_Set) == PLSys_Const_SysThreadAttr_Policy_Set){
					int_pl iPolicy;
					if(ptrAttr->ePolicy == PLSys_Const_SysThreadPolicy_Poll){
						iPolicy = SCHED_RR;
					}else if(ptrAttr->ePolicy == PLSys_Const_SysThreadPolicy_FIFO){
						iPolicy = SCHED_FIFO;
					}else{
						iPolicy = SCHED_OTHER;
					}
					pthread_attr_setschedpolicy(&tAttr,iPolicy);
				}
				if((ptrAttr->uTag & PLSys_Const_SysThreadAttr_Priority_Set) == PLSys_Const_SysThreadAttr_Priority_Set){
					if((ptrAttr->ePolicy == PLSys_Const_SysThreadPolicy_Poll)
									|| (ptrAttr->ePolicy == PLSys_Const_SysThreadPolicy_FIFO)){
						struct sched_param param;
						PLSysAPI_MemoryClearZero((void_pl *)(&param),PL_CompilerAllocSize(struct sched_param));
						param.__sched_priority = ptrAttr->iPriority;
						pthread_attr_setschedparam(&tAttr,&param);
					}
				}
			}while(0);
		}
		iAllocSize = PL_CompilerAllocSize(PLThreadDataPackage);
		iAllocSize = PLSysAPI_Alignment(iAllocSize,PLSys_Const_CPUCacheLineSize);
		//temporarily allocate memory save PLThreadDataPackage object
		ptrTDP = (PLThreadDataPackage *)PLSysAPI_AllocateMemory(iAllocSize);
		if(ptrTDP==NULL_PL)
			return HPLResult_Fail;
		//(pthread_attr_setinheritsched(&tAttr,PTHREAD_EXPLICIT_SCHED)!=0)
		PLSysAPI_MemoryClearZero((void_pl *)ptrTDP,PL_CompilerAllocSize(PLThreadDataPackage));
		ptrTDP->ptrData  = ptrParamer;
		ptrTDP->callback = callback;
		if(pthread_create(&tTid,ptrTAttr,__posix_thread_callback,(void_pl *)ptrTDP)!=0){
			PLSysAPI_FreeMemory((void_pl *)ptrTDP);
			if(ptrTAttr!=NULL_PL)
				pthread_attr_destroy(&tAttr);
			return HPLResult_Fail;
		}
		if(ptrTAttr!=NULL_PL)
			pthread_attr_destroy(&tAttr);
		(*ptrhWnd) = tTid;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_JoinThread(PLThreadHandle hTWnd){
		pthread_t tid;
		tid = (pthread_t)hTWnd;
		if(tid == NULL_PL)
			return HPLResult_Fail;
		pthread_kill(tid,0);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr){
		pthread_attr_t tAttr;
		struct sched_param param;
		uintV_pl uTag;
		if(pthread_attr_init(&tAttr)!=0)
			return HPLResult_Fail;
		uTag = ptrAttr->uTag;
		ptrAttr->uTag = 0;
#ifdef _POSIX_THREAD_ATTR_STACKADDR
		if(((uTag & PLSys_Const_SysThreadAttr_Stack_Set) == PLSys_Const_SysThreadAttr_Stack_Set) && (ptrAttr->iStackSize>=PLTHREAD_STACK_MIN_SIZE) && (ptrAttr->ptrStack==NULL_PL)){
			size_t tSize;
			tSize = (size_t)(ptrAttr->iStackSize);
			if(pthread_attr_setstack(&tAttr,ptrAttr->ptrStack,tSize)==0){
				ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Stack_Set;
			}
		}
	#ifdef _POSIX_THREAD_ATTR_STACKSIZE
		else
	#endif
#endif
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
		if((uTag & PLSys_Const_SysThreadAttr_StackSize_Set) == PLSys_Const_SysThreadAttr_StackSize_Set){
			size_t tSize;
			tSize = (size_t)(ptrAttr->iStackSize);
			if(tSize<PLTHREAD_STACK_MIN_SIZE)
				tSize = PLTHREAD_STACK_MIN_SIZE;
			if(pthread_attr_setstacksize(&tAttr,tSize)==0){
				ptrAttr->uTag |= PLSys_Const_SysThreadAttr_StackSize_Set;
			}
		}
#endif
		if((uTag & PLSys_Const_SysThreadAttr_Policy_Set) == PLSys_Const_SysThreadAttr_Policy_Set){
			if((ptrAttr->ePolicy==PLSys_Const_SysThreadPolicy_FIFO)
							|| (ptrAttr->ePolicy==PLSys_Const_SysThreadPolicy_Poll)
							|| (ptrAttr->ePolicy==PLSys_Const_SysThreadPolicy_SysSched)){
				int_pl iPolicy;
				if(ptrAttr->ePolicy == PLSys_Const_SysThreadPolicy_FIFO){
					iPolicy = SCHED_FIFO;
				}else if(ptrAttr->ePolicy == PLSys_Const_SysThreadPolicy_Poll){
					iPolicy = SCHED_RR;
				}else{
					iPolicy = SCHED_OTHER;
				}
				if(pthread_attr_setschedpolicy(&tAttr,iPolicy)==0){
					ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Policy_Set;
				}
			}
		}
		if((uTag & PLSys_Const_SysThreadAttr_Priority_Set) == PLSys_Const_SysThreadAttr_Priority_Set){
			int_pl iPolicy;
			if((pthread_attr_getschedpolicy(&tAttr,&iPolicy)==0) && ((iPolicy == SCHED_RR) || (iPolicy == SCHED_FIFO))){
				PLSysAPI_MemoryClearZero((void_pl *)(&param),PL_CompilerAllocSize(struct sched_param));
				param.__sched_priority = ptrAttr->iPriority;
				if(pthread_attr_setschedparam(&tAttr,&param) == 0){
					ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Priority_Set;
				}
			}
		}
		pthread_attr_destroy(&tAttr);
		return HPLResult_OK;
	}
	void_pl __PLSysAPI_SystemProcess_GetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr){
		pthread_attr_t tAttr;
		struct sched_param param;
//		int_pl iMax,iMin;
		intV_pl iPolicy;
		uintV_pl uTag;
		size_t tStackSize;
		uTag = ptrAttr->uTag;
		ptrAttr->uTag = 0;
		if(pthread_attr_init(&tAttr)!=0)
			return;
#ifdef _POSIX_THREAD_ATTR_STACKADDR
		if((uTag & PLSys_Const_SysThreadAttr_Stack_Set) == PLSys_Const_SysThreadAttr_Stack_Set){
			size_t tSize;
			if(pthread_attr_getstack(&tAttr,&(ptrAttr->ptrStack),&tSize)==0){
				ptrAttr->iStackSize = tSize;
				ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Stack_Set;
			}
		}
	#ifdef _POSIX_THREAD_ATTR_STACKSIZE
		else
	#endif
#endif
			//get thread's attrib is stacksize
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
			if((uTag & PLSys_Const_SysThreadAttr_StackSize_Set) == PLSys_Const_SysThreadAttr_StackSize_Set){
				if(pthread_attr_getstacksize(&tAttr,&tStackSize) == 0){
					ptrAttr->iStackSize = tStackSize;
					ptrAttr->uTag |= PLSys_Const_SysThreadAttr_StackSize_Set;
				}
			}
#endif
			//get thread's attrib is policy
			if((uTag & PLSys_Const_SysThreadAttr_Policy_Set) == PLSys_Const_SysThreadAttr_Policy_Set){
				if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)==0){
					if(iPolicy == SCHED_RR){
						ptrAttr->ePolicy = PLSys_Const_SysThreadPolicy_Poll;
					}else if(iPolicy == SCHED_FIFO){
						ptrAttr->ePolicy = PLSys_Const_SysThreadPolicy_FIFO;
					}else{
						ptrAttr->ePolicy = PLSys_Const_SysThreadPolicy_SysSched;
					}
					ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Policy_Set;
				}
			}
			//get thread's attrib is priority
			if((uTag & PLSys_Const_SysThreadAttr_Priority_Set) == PLSys_Const_SysThreadAttr_Priority_Set){
				if((pthread_attr_getschedpolicy(&tAttr,&iPolicy)==0) && ((iPolicy == SCHED_RR) || (iPolicy == SCHED_FIFO))){
					if(pthread_attr_getschedparam(&tAttr,&param)==0){
						ptrAttr->uTag |= PLSys_Const_SysThreadAttr_Priority_Set;
						ptrAttr->iPriority = param.__sched_priority;
					}
				}
			}
//			pthread_attr_getschedpolicy(&tAttr,&iPolicy);
		pthread_attr_destroy(&tAttr);
		return;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority eLevel){
		pthread_attr_t tAttr;
		intV_pl iPolicy;
		intV_pl iMax,iMin,iMid;
		intV_pl iOldPriority;
		struct sched_param param;
		if(pthread_attr_init(&tAttr)!=0)
			return HPLResult_Fail;
		iMax = iMin = -1;
		//get sched policy
		if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)!=0)
			return HPLResult_Fail;
		if(((iPolicy!=SCHED_RR) && (iPolicy!=SCHED_FIFO)) || (((iMax = sched_get_priority_max(iPolicy))<0) || ((iMin = sched_get_priority_min(iPolicy))<0))){
			pthread_attr_destroy(&tAttr);
			return HPLResult_Fail;
		}
		iOldPriority = pthread_attr_getschedparam(&tAttr,&param)==0 ? param.__sched_priority : 0x7fffffff;
		PLSysAPI_MemoryClearZero((void_pl *)(&param),PL_CompilerAllocSize(struct sched_param));
		switch(eLevel){
			case  PLSys_Const_SysThreadPriority_Normal:{
					param.__sched_priority =  (iMax - iMin)/2 + iMin;
			}break;
			case PLSys_Const_SysThreadPriority_Hight:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = (iMax - iMid)/4 + iMid;
			}break;
			case PLSys_Const_SysThreadPriority_Hot:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = (iMax - iMid)/2 + iMid;
			}break;
			case PLSys_Const_SysThreadPriority_Low:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = iMid - (iMid - iMin)/4;
			}break;
			case PLSys_Const_SysThreadPriority_Idel:{
				iMid = (iMax - iMin)/2 + iMin;
				param.__sched_priority = iMid - (iMid - iMin)/2;
			}break;
			case PLSys_Const_SysThreadPriority_Max:{
				param.__sched_priority = iMax;
			}break;
			case PLSys_Const_SysThreadPriority_Min:{
				param.__sched_priority = iMin;
			}break;
			case PLSys_Const_SysThreadPriority_CurrentSet:
			default:{
				pthread_attr_destroy(&tAttr);
				return HPLResult_Fail;
			}break;
		}
		pthread_attr_setschedparam(&tAttr,&param);
		pthread_attr_destroy(&tAttr);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority *  ptreLevel){
		pthread_attr_t tAttr;
		struct sched_param param;
		intV_pl iPolicy;
		intV_pl iPriority;
		intV_pl iMax,iMin;
		if(pthread_attr_init(&tAttr)!=0)
			return HPLResult_Fail;
		do{
			if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)!=0)
				break;
			if((iPolicy != SCHED_RR) && (iPolicy != SCHED_FIFO))
				break;
			if(pthread_attr_getschedparam(&tAttr,&param)!=0)
				break;
			iPriority = param.__sched_priority;
			iMax = sched_get_priority_max(iPolicy);
			iMin = sched_get_priority_min(iPolicy);

			//param.sched_param
		}while(0);
		pthread_attr_destroy(&tAttr);
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy){
		pthread_attr_t tAttr;
		intV_pl iPolicy;
		if((pthread_attr_init(&tAttr) != 0))
			return HPLResult_Fail;
		do{
			if(ePolicy == PLSys_Const_SysThreadPolicy_Poll){
				iPolicy = SCHED_RR;
			}else if(ePolicy == PLSys_Const_SysThreadPolicy_FIFO){
				iPolicy = SCHED_FIFO;
			}else if(ePolicy == PLSys_Const_SysThreadPolicy_SysSched){
				iPolicy = SCHED_OTHER;
			}else{
				break;
			}
			if(pthread_attr_setschedpolicy(&tAttr,iPolicy)!=0)
				break;
			pthread_attr_destroy(&tAttr);
			return HPLResult_OK;
		}while(0);
		pthread_attr_destroy(&tAttr);
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy * ptrePolicy){
		intV_pl iPolicy;
		pthread_attr_t tAttr;
		if(pthread_attr_init(&tAttr)!=0)
			return HPLResult_Fail;
		do{
			if(pthread_attr_getschedpolicy(&tAttr,&iPolicy)!=0)
				break;
			if(iPolicy==SCHED_RR){
				(*ptrePolicy) = PLSys_Const_SysThreadPolicy_Poll;
			}else if (iPolicy==SCHED_FIFO){
				(*ptrePolicy) = PLSys_Const_SysThreadPolicy_FIFO;
			}else if(iPolicy==SCHED_OTHER){
				(*ptrePolicy) = PLSys_Const_SysThreadPolicy_SysSched;
			}else{
				break;
			}
			pthread_attr_destroy(&tAttr);
			return HPLResult_OK;
		}while(0);
		pthread_attr_destroy(&tAttr);
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemProcess_ThreadDetach(PLThreadHandle hTWnd){
		pthread_t tTid;
		tTid = (pthread_t)hTWnd;
		pthread_detach(tTid);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPriorityLimit(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy,int_pl * ptriMaxPriority,int_pl * ptriMinPriority){
		intV_pl iMax;
		intV_pl iMin;
		intV_pl iPolicy;
		iMax = iMin = -1;
		if(ePolicy == PLSys_Const_SysThreadPolicy_FIFO){
			iPolicy = SCHED_FIFO;
		}else if(ePolicy == PLSys_Const_SysThreadPolicy_Poll){
			iPolicy = SCHED_RR;
		}else{
			iPolicy = SCHED_OTHER;
		}
		if((iPolicy!=SCHED_RR) && (iPolicy!=SCHED_FIFO)){
			(*ptriMaxPriority) = -1;
			(*ptriMinPriority) = -1;
			return HPLResult_Fail;
		}
		iMax = sched_get_priority_max(iPolicy);
		iMin = sched_get_priority_min(iPolicy);
		if((iMax<0) || (iMin<0)){
			(*ptriMaxPriority) = -1;
			(*ptriMinPriority) = -1;
			return HPLResult_Fail;
		}
		(*ptriMaxPriority) = iMax;
		(*ptriMinPriority) = iMin;
		return HPLResult_OK;
	}
	void_pl __PLSysAPI_SystemProcess_ThreadTermin(PLThreadHandle hTWnd){
		pthread_kill(hTWnd,SIGKILL);
		return;
	}
	void_pl __PLSysAPI_SystemProcess_ThreadDeathSelf(){
		pthread_detach(pthread_self());
	}
	HPL_Result __PLSysAPI_SystemProcess_CloseHandle(PLThreadHandle hTWnd){

		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAffinity(PLThreadHandle hTWnd,uint_pl uProcessorMark,uint_pl * ptrOldProcessorMark){
		cpu_set_t tCpu;
		pthread_attr_t tAttr;
		if(pthread_attr_init(&tAttr)!=0)
			return HPLResult_Fail;
		CPU_ZERO(&tCpu);
		CPU_SET(*ptrOldProcessorMark,&tCpu);
		if(pthread_attr_setaffinity_np(&tAttr,PL_CompilerAllocSize(cpu_set_t),&tCpu)!=0){
			pthread_attr_destroy(&tAttr);
			return HPLResult_Fail;
		}
		pthread_attr_destroy(&tAttr);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAdviceProcessor(PLThreadHandle hTWnd,uint_pl uProcessor){

		return HPLResult_OK;
	}
	void_pl __PLSysAPI_SystemProcess_Sleep(int64_pl iTimer){

	}
	/***Start Linux Local Function***/
	void_pl * __posix_thread_callback(void_pl * ptrData){
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
		__PLSysAPI_SystemProcess_ThreadDeathSelf();
		return NULL_PL;
	}
	/***End Linux Local Function***/
#endif
