//============================================================================
// Name        : PLEngineTest.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TProjectH.h"
using namespace std;
void_pl _TLSKeyFree(void_pl * ptrData);
uint_pl _thread_func(void_pl * ptrData);
uint_pl _Fthread_func(void_pl * ptrData);
PLTLSKey tKey;
volatile_pl static intV_pl g_Value;
volatile_pl static intV_pl g_TCount;
char_pl upath[]{0x2f,0x68,0x6f,0x6d,0x65,0x2f,0x44,0x65,0x76,0x2f,
					   0xe4,0xbd,0xa0,0xe5,0xa5,0xbd,0x00};
int main(int argc,char * args[]) {
	HPPLEngine hState;
	hState = NULL_PL;
	hState = CreateEngineHandle();

	InitializeEngine(hState);

/*
	HPKGObjAndle hPKGAndle;
	HPKGFileItemAndle hPKGItemAndle;
	intV_pl iAllocate;
	char_pl * ptrData;

	hPKGAndle = PLSysAPI_RC_OpenPackage("X.pkg",strlen("X.pkg"),0);
	if(hPKGAndle!=NULL_PL){
		hPKGItemAndle = PLSysAPI_RC_GetPackageFileItemObject(hPKGAndle,"000VC01_YX86H.x",strlen("000VC01_YX86H.x"));
		do{
			if(hPKGItemAndle == NULL_PL)
				break;
			iAllocate = PLSysAPI_RC_GetPackageFileItemSize(hPKGItemAndle);
			if(iAllocate<=0)
				break;
			ptrData = (char_pl *)PLSysAPI_Mem_AllocateMemoryPool(iAllocate);
			if(ptrData == NULL_PL)
				break;

			PLSysAPI_RC_ReadPackageFileItemData(hPKGAndle,hPKGItemAndle,ptrData,iAllocate,0);
			PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrData);
		}while(0);
		PLSysAPI_RC_ClosePackage(hPKGAndle);
	}*/
//	PLSysAPI_SystemIO_Mkdir(upath,17,
//			PLSysIO_Const_Att_URead  |	PLSysIO_Const_Att_UGRead  | PLSysIO_Const_Att_ORead  |
//			PLSysIO_Const_Att_UWrite | PLSysIO_Const_Att_UGWrite | PLSysIO_Const_Att_OWrite
//			,NULL_PL);

	_Syn_RWLockWF lock;
	PLThreadHandle ThWnd[10];
	PLThreadAttr tattr;
	intV_pl iCount;
	g_Value = 0;
	g_TCount = 0;
	PLSysAPI_Syn_InitializeRWLockWF(lock);
	PLSysAPI_MemoryClearZero(&tattr,PL_CompilerAllocSize(PLThreadAttr));
	for(iCount = 0;iCount<10;iCount++){
		PLSysAPI_SystemProcess_CreatThread(&(ThWnd[iCount]),&tattr,_Fthread_func,&lock);
		g_TCount++;
	}
	for(iCount = 0;iCount<10;iCount++){
		printf("Thread Write Value getlock \n");
		PLSysAPI_Syn_AcquireRWLockWriteWF(lock);

		g_Value += 2;
		printf("Thread Write Value = %d \n",g_Value);

		printf("Thread Write Value releaselock \n");
		PLSysAPI_Syn_ReleaseRWLockWriteWF(lock);
		PLSysAPI_SystemProcess_Sleep(0);
	}

	while(g_TCount >0){
		printf("WThread wait ....\n");
	}

	PLSysAPI_Syn_ReleaseRWLockWF(lock);

	printf("Thread Close \n");

   DestoryEngineHandle(hState);
   return 0;
 }
uint_pl _Fthread_func(void_pl * ptrData){
	PLThreadVirtualID tid;
	_Syn_RWLockWF * ptrlock;
	tid = -1;
	while(g_TCount<10){
		break;
	}
	PLSysAPI_SystemProcess_GetThreadVirtualID(&tid);
	ptrlock = (_Syn_RWLockWF *)ptrData;
	for(intV_pl iCount = 0;iCount < 100;iCount++){
//		printf("ThreadID = %d get lock \n");
		PLSysAPI_Syn_AcquireRWLockReadWF(*ptrlock);
			printf("ThreadID = %d , readValue = %d \n",tid,g_Value);
//		printf("ThreadID = %d releaselock \n");
		PLSysAPI_Syn_ReleaseRWLockReadWF(*ptrlock);
		PLSysAPI_SystemProcess_Sleep(0);
//		if(iCount ==88){
//			PLSysAPI_SystemProcess_Sleep(10000000);
//		}
	}
	g_TCount--;
	return NULL_PL;
}
