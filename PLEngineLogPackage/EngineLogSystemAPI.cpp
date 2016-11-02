/*
 * EngineLogSystemAPI.cpp
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "EngineLogSystemAPI.h"
PLLibraryHandle g_hLibraryHandle_Log = NULL_PL;
PLLibraryHandle     Eg_GetLibraryHandle_global(){
	return g_hLibraryHandle_Log;
}

PLLogSystemHandle Eg_CreateLogSystem(){
	PL_LogSystem * ptrLogSys;

	ptrLogSys = (PL_LogSystem *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_LogSystem));
	if(ptrLogSys == NULL_PL)
		return NULL_PL;
	PLSysAPI_MemoryClearZero((void_pl *)ptrLogSys,PL_CompilerAllocSize(PL_LogSystem));
	ptrLogSys->eState = PLSysLog_Const_LogSys_UnInitialize;

	return (PLLogSystemHandle)ptrLogSys;
}
void_pl Eg_SetLogSystemHeaderName(PLLogSystemHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	PL_LogSystem * ptrLogSys;
	ptrLogSys = (PL_LogSystem *)hAndle;
	if(ptrLogSys == NULL_PL)
		return;
	ptrLogSys->iHNSize = 0;
	PLSysAPI_MemoryClearZero(ptrLogSys->pHeaderName,PLLog_ConstID_HeaderNameMaxSize);
	if((iSize <= 0) || (ptrName == NULL_PL))
		return;
	ptrLogSys->iHNSize = iSize;
	PLSysAPI_MemoryCpy(ptrLogSys->pHeaderName,ptrName,ptrLogSys->iHNSize);
}
/*
 *
*/
void_pl Eg_DestroyLogSystem(PLLogSystemHandle hAndle){
	PL_LogSystem * ptrLogSys;
	ptrLogSys = (PL_LogSystem *)hAndle;
	if(ptrLogSys == NULL_PL)
		return;

	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrLogSys);
}

