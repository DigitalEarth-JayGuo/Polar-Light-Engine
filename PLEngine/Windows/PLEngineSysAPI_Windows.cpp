/*
 * PLEngineSysAPI_Windows.cpp
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "../header/Windows/PLEngineSysAPI_Windows.h"
#if PLOperat_System == PLOperatSystem_Window

/*	inline void _OperatSysTimerAndEngineSysTimerLinker_(struct  timeval * ptrOSysTimer ,PL_SystemTimer * ptrESysTimer){
		if(ptrOSysTimer->tv_sec>0){
			ptrESysTimer->iCalculSymbol = 0;
			if (ptrOSysTimer->tv_usec<0){
				--ptrOSysTimer->tv_sec;
				ptrOSysTimer->tv_usec += 1000000;
			}
		}else if(ptrOSysTimer->tv_sec<0){
			ptrESysTimer->iCalculSymbol = -1;
			ptrOSysTimer->tv_sec = -ptrOSysTimer->tv_sec;
			if(ptrOSysTimer->tv_usec<0){
				--ptrOSysTimer->tv_sec;
				ptrOSysTimer->tv_usec += 1000000;
			}
		}else{
			if(ptrOSysTimer->tv_usec < 0){
				ptrESysTimer->iCalculSymbol = -1;
				ptrOSysTimer->tv_usec = -ptrOSysTimer->tv_usec;
			}else{
				ptrESysTimer->iCalculSymbol = 0;
			}
		}
	}*/
	inline void _OperatSysTimerToEngineSysTimer_(LARGE_INTEGER * ptrOSysTimer ,luint_pl  Frequency, PL_SystemTimer * ptrESysTimer){
		LARGE_INTEGER TimerVal;
		//_OperatSysTimerAndEngineSysTimerLinker_(ptrOSysTimer,ptrESysTimer);
		TimerVal.QuadPart = (uint64_pl)((((double_pl)ptrOSysTimer->QuadPart) / ((double_pl)Frequency))*1000000.0);

		ptrESysTimer->ins      = (uint_pl)(TimerVal.QuadPart % 1000000) * 1000;
		TimerVal.QuadPart      = TimerVal.QuadPart / 1000000;
		ptrESysTimer->isecond  = (uint_pl)(TimerVal.QuadPart % 86400);
		TimerVal.QuadPart      = TimerVal.QuadPart / 86400;
		ptrESysTimer->iday     = (uint_pl)(TimerVal.QuadPart);
		ptrESysTimer->iCalculSymbol = 0;
	}
	HPL_Result PLSysAPI_InitializSystemTimer(PLSystemTimerHandle hAndle){
		PL_SystemTimerObject * ptrObject;
		LARGE_INTEGER        TimerFrequency,TimerVal;
		ptrObject = hAndle;
		if(hAndle == NULL_PL)
			return HPLResultF_Paramer_NULL;
		PLSysAPI_MemoryClearZero(ptrObject,PL_CompilerAllocSize(PL_SystemTimerObject));
		ptrObject->cbSize = PL_CompilerAllocSize(PL_SystemTimerObject);
		ptrObject->CycleTimerH = 0;
		ptrObject->CycleTImerL = 0;
		QueryPerformanceFrequency(&TimerFrequency);
		QueryPerformanceCounter(&TimerVal);
		ptrObject->CycleTImerL = TimerFrequency.QuadPart;
		_OperatSysTimerToEngineSysTimer_(&TimerVal,ptrObject->CycleTImerL,&(ptrObject->AfterSystemTimerKey));
		ptrObject->LastSystemTimerKey 		 	= ptrObject->AfterSystemTimerKey;
		return HPLResult_OK;
	}
/*
	HPL_Result PLSysAPI_GetSystemLastTimerKey(PLSystemTimerHandle hAndle,PL_SystemTimer * ptrLastTimer){
		PL_SystemTimerObject * ptrObject;
		LARGE_INTEGER          TimerVal;
		PL_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		QueryPerformanceCounter(&TimerVal);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,ptrObject->CycleTImerL,&LastTimer);
		TimerStep.iCalculSymbol = 0;
		if( _MaxSystemTimer_(&LastTimer , &(ptrObject->AfterSystemTimerKey))== (&LastTimer)){
			ptrObject->AfterSystemTimerKey = ptrObject->LastSystemTimerKey;
			ptrObject->LastSystemTimerKey  = LastTimer;
			_CalculSysTimerInterval_(&(ptrObject->LastSystemTimerKey),&(ptrObject->AfterSystemTimerKey),&TimerStep);
			_CalculSysTimerAdd_((&(ptrObject->ElapseTimer)),(&TimerStep));
		}
		*ptrLastTimer=ptrObject->ElapseTimer;
		return HPLResult_OK;
	}
*/

	HPL_Result PLSysAPI_GetSystemLastTimerKey(PLSystemTimerHandle hAndle,PL_SystemTimer * ptrLastTimer){
		PL_SystemTimerObject * ptrObject;
		LARGE_INTEGER     	   TimerVal;
		PL_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		QueryPerformanceCounter(&TimerVal);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,ptrObject->CycleTImerL,&LastTimer);
		TimerStep.iCalculSymbol = 0;
		if( _MaxSystemTimer_(&LastTimer , &(ptrObject->AfterSystemTimerKey))== (&LastTimer)){
			ptrObject->LastSystemTimerKey  = LastTimer;
			_CalculSysTimerInterval_(&(ptrObject->LastSystemTimerKey),&(ptrObject->AfterSystemTimerKey),&TimerStep);
			ptrObject->ElapseTimer = TimerStep;
		}else{
			PLSysAPI_MemoryClearZero(&TimerStep,PL_CompilerAllocSize(PL_SystemTimer));
			TimerStep.ins = 100;
			_CalculSysTimerAdd_((&(ptrObject->ElapseTimer)),(&TimerStep));
		}
		*ptrLastTimer=ptrObject->ElapseTimer;
		return HPLResult_OK;
	}

	HPL_Result PLSysAPI_Lib_OpenLibrary(PLLibModuleHandle * ptrhAndle,const_pl UTF16char_pl * ptrName,intV_pl iwNameLength,int_pl iTag){
		PLLibModuleHandle hAndle;
		intV_pl ierror;
		if(ptrName==NULL_PL || iwNameLength<=0)
			return HPLResultF_Paramer_NULL;
		hAndle = LoadLibraryExW((const_pl WCHAR *)ptrName,NULL_PL,0);
		if(hAndle == NULL_PL){
			ierror = GetLastError();
		}
		(*ptrhAndle) = hAndle;
		return HPLResult_OK;
	}
	HPL_Result PLSysAPI_Lib_CloseLibrary(PLLibModuleHandle hAndle){
		if(hAndle==NULL_PL)
			return HPLResultF_Paramer_NULL;
		FreeLibrary(hAndle);
		return HPLResult_Fail;
	}
	void_pl *  PLSysAPI_Lib_SearchLibraryObject(PLLibModuleHandle hAndle,const_pl UTF16char_pl * ptrSymbol,intV_pl iwSymbolLength){
		UTF8char_pl pLocalSymbol[PL3DSystemFunSymbolMaxLength];
		intV_pl iwLSymbolSize;
		intV_pl iConverPos;
		intV_pl iConverByteSize;
		uintV_pl uFlag;
		if((hAndle==NULL_PL) || (ptrSymbol==NULL_PL) || (iwSymbolLength<=0))
			return NULL_PL;
		PLSysAPI_MemoryClearZero(pLocalSymbol,PL3DSystemFunSymbolMaxLength);
		uFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		PLSysAPI_SysIO_UTF16toUTF8((const_pl UTF16char_pl *)ptrSymbol,iwSymbolLength,&iConverPos,pLocalSymbol
						,&iwLSymbolSize,&iConverByteSize,PL3DSystemFunSymbolMaxLength,&uFlag);
		return (void *)GetProcAddress(hAndle,(char_pl *)pLocalSymbol);
	}
	int_pl PLSysAPI_Sys_GetProcessNumber(){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return (lint_pl)(info.dwNumberOfProcessors);
	}
	lint_pl PLSysAPI_Sys_GetPhysPagesNumber(){

//		return sysconf(_SC_PHYS_PAGES);
		return 0;
	}
	intV_pl PLSysAPI_Sys_GetPhysPageSize(){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwPageSize;
	}
	intV_pl  PLSysAPI_Sys_GetSysAllocMemoryGrain(){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwAllocationGranularity;
	}
	intV_pl    PLSysAPI_Sys_GetCPUCacheShareUnit(){
		return PLSys_Const_defaultCPUCacheLineSize;
	}
	lint_pl PLSysAPI_Sys_GetSpaceMemory(){
		return 0;
	}

	HPL_Result PLSysAPI_Sys_GetOperatSystemInfo(PL_OperatSystemInfo * ptrInfo){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_Sys_GetConstSystemInfo__Private(PL_ConstSystemInfo * ptrInfo){
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		ptrInfo->lProcessNumber = info.dwNumberOfProcessors;
		ptrInfo->iCacheLineSize = 64;
		ptrInfo->iAllocationGranularity = info.dwAllocationGranularity;
		ptrInfo->lPhysPageSize = info.dwPageSize;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_Sys_GetOperatSystemEnv__Private(PL_OperatSysEnvSet * ptrEnv){

		ptrEnv->iwCWDSize = PLSysAPI_SystemIO_GetCurWD(ptrEnv->pCWD,PL3DSystemFilePathNameMaxLength);
		if(ptrEnv->iwCWDSize<=0)
			return HPLResult_Fail;
		ptrEnv->iwPlusCWDSize = ptrEnv->iwCWDSize;
		PLSysAPI_SysStringCpy(ptrEnv->pPlusCWD,ptrEnv->pCWD,ptrEnv->iwPlusCWDSize);
		ptrEnv->iwResourceCWDSize = ptrEnv->iwCWDSize;
		PLSysAPI_SysStringCpy(ptrEnv->pResourceCWD,ptrEnv->pCWD,ptrEnv->iwResourceCWDSize);
		return HPLResult_OK;
	}
	intV_pl PLSysAPI_Sys_GetLastError(){
		return (intV_pl)GetLastError();
	}
#endif
