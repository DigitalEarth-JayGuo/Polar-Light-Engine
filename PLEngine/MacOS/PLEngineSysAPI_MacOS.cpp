/*
 * PLEngineSysAPI_MacOS.cpp
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "../header/MacOS/PLEngineSysAPI_MacOS.h"
#if PLOperat_System == PLOperatSystem_MacOS
	HPL_Result PLSysAPI_InitializSystemTimer(PLSystemTimerHandle){
		return HPLResult_OK;
	}
	HPL_Reuslt PLSysAPI_Lib_OpenLibrary(PLLibModuleHandle * ptrhAndle,char_pl * ptrName,int_pl iNameLength,int_pl iTag){

		return HPLResult_Fail;
	}
	HPL_Result PLSysAPI_Lib_CloseLibrary(PLLibModuleHandle){
		return HPLResult_Fail;
	}
	void_pl *  PLSysAPI_Lib_SearchLibraryObject(PLLibModuleHandle,char_pl * ptrSymbol,intV_pl iSymbolLength){
		return NULL_PL;
	}

	intV_pl     PLSysAPI_Sys_GetSysAllocMemoryGrain(){
		return 65536;
	}
	HPL_Result PLSysAPI_Sys_GetOperatSystemInfo(PL_OperatSystemInfo * ptrInfo){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_Sys_GetConstSystemInfo__Private(PL_ConstSystemInfo * ptrInfo){
		ptrInfo->lProcessNumber = sysconf(_SC_NPROCESSORS_ONLN);
		ptrInfo->iCacheLineSize = 64;
		ptrInfo->iAllocationGranularity = 65536;
		ptrInfo->lPhysPageSize = sysconf(_SC_PAGE_SIZE);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_Sys_GetOperatSystemEnv__Private(PL_OperatSysEnvSet * ptrEnv){
		ptrEnv->iCWDSize = PLSysAPI_SystemIO_GetCurWD(ptrEnv->pCWD,PL3DSystemFileNameMaxLength);
		if(ptrEnv->iCWDSize<=0)
			return HPLResult_Fail;
		ptrEnv->iPlusCWDSize = ptrEnv->iCWDSize;
		PLSysAPI_MemoryCpy(ptrEnv->pPlusCWD,ptrEnv->pCWD,ptrEnv->iPlusCWDSize * PL_CompilerAllocSize(uchar_pl));
		return HPLResult_OK;
	}
#endif
