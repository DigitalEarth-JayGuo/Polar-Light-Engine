/*
 * PLEngineSysProcess.cpp
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "header/PLEngineSysProcess.h"
//#include "PLEngineSysAPI.h"

HPL_Result __PLSysAPI_SystemProcess_GetThreadVirtualID(PLThreadVirtualID * ptrVID){
	PLThreadVirtualID hID;
	HPL_Result hResult;
	hID = 0;
	hResult = HPLResult_Fail;
	if(g_ThreadVirtualIDKey == PLTLSKey_Invalid)
		return hResult;
	hID = (PLThreadVirtualID)PLSysAPI_SystemProcess_GetTLSValue(&g_ThreadVirtualIDKey);
	if(hID==0){
		hID = PLSysAPI_SystemProcess_AllocateThreadVID();
		PLSysAPI_SystemProcess_SetTLSValue(&g_ThreadVirtualIDKey,(void_pl *)hID);
	}
	*ptrVID = hID;
	hResult = HPLResult_OK;
	return hResult;
}

PLThreadVirtualID  __PLSysAPI_SystemProcess_AllocateThreadVID(){
	return (PLSysAPI_Syn_AtomInterAdd(&g_ThreadAllID,1) + 1);
}


void_pl PLTLSKey_ThreadVirtualID_Destory(void_pl * ptrData){

}
PLThreadID __PLSysAPI_SystemProcess_GetThreadID(PLThreadHandle hAndle){
	return (PLThreadID)hAndle;
}
PLThreadID __PLSysAPI_SystemProcess_GetThreadSelfID(){
	return 0;
}
HPL_Result __PLSysAPI_SystemProcess_InitializeProcessLibrary(){
	return HPLResult_OK;
}
void_pl __PLSysAPI_SystemProcess_ReleaseProcessLibrary(){

}

