/*
 * PLEngineSysProcessAPI_MacOS.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../header/MacOS/PLEngineSysProcessAPI_MacOS.h"
#if PLOperat_System == PLOperatSystem_MacOS
	void_pl __PLSysAPI_SystemProcess_ExitProess_(intV_pl iCode){
		exit(iCode);
	}
	HPL_Result __PLSysAPI_SystemProcess_AllocTLSKey(PLTLSKey * ptrKey,_PLTLSKey_endthreadCallback threadcallback){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_FreeTLSKey(PLTLSKey * ptrKey){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetTLSValue(PLTLSKey * ptrKey,void_pl * ptrValue){
		return HPLResult_OK;
	}
	void_pl *  __PLSysAPI_SystemProcess_GetTLSValue(PLTLSKey * ptrKey){
		return NULL_PL;
	}

	HPL_Result __PLSysAPI_SystemProcess_CreatThread(PLThreadHandle * ptrhWnd,PLThreadAttr * ptrAttr,__pl_thread_callbacktype callback,void_pl * ptrParamer){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_JoinThread(PLThreadHandle hTWnd){

		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority eLevel){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPriority(PLThreadHandle hTWnd,ePL_SysThreadPriority *  ptreLevel){
		retur HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPolicy(PLThreadHandle hTWnd,ePL_SysThreadPolicy *  ptrePolicy){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr){
		return HPLResult_OK;
	}
	void_pl    __PLSysAPI_SystemProcess_GetThreadAttr(PLThreadHandle hTWnd,PLThreadAttr * ptrAttr){
		return;
	}
	HPL_Result __PLSysAPI_SystemProcess_ThreadDetach(PLThreadHandle hTWnd){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_GetThreadPriorityLimit(PLThreadHandle hTWnd,ePL_SysThreadPolicy ePolicy,intV_pl * ptriMaxPriority,intV_pl * ptriMinPriority){
		return HPLResult_OK;
	}
	void_pl __PLSysAPI_SystemProcess_ThreadTermin(PLThreadHandle hTWnd){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_CloseHandle(PLThreadHandle hTWnd){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAffinity(PLThreadHandle hTWnd,uintV_pl uProcessorMark,uintV_pl * ptrOldProcessorMark){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemProcess_SetThreadAdviceProcessor(PLThreadHandle hTWnd,uintV_pl uProcessor){
		return HPLResult_OK;
	}

#endif
