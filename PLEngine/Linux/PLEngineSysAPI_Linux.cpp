/*
 * PLEngineSysAPI_Linux.cpp
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "../header/Linux/PLEngineSysAPI_Linux.h"
#if PLOperat_System == PLOperatSystem_Linux

	inline void _OperatSysTimerAndEngineSysTimerLinker_(struct  timeval * ptrOSysTimer ,PL_SystemTimer * ptrESysTimer){
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
	}
	inline void _OperatSysTimerToEngineSysTimer_(struct  timeval * ptrOSysTimer ,PL_SystemTimer * ptrESysTimer){
		_OperatSysTimerAndEngineSysTimerLinker_(ptrOSysTimer,ptrESysTimer);
		ptrESysTimer->ins      = (uint_pl)(ptrOSysTimer->tv_usec % 1000000) * 1000;
		ptrESysTimer->isecond  = (uint_pl)(ptrOSysTimer->tv_sec  % 86400);
		ptrOSysTimer->tv_sec   = (uint_pl)(ptrOSysTimer->tv_sec  / 86400);
		ptrESysTimer->iday     = (uint_pl)(ptrOSysTimer->tv_sec);
		ptrOSysTimer->tv_sec   = (uint_pl)(ptrOSysTimer->tv_usec / 1000000);
		if(ptrOSysTimer->tv_sec>0){
			ptrESysTimer->isecond += (uint_pl)(ptrOSysTimer->tv_sec);
			if(ptrESysTimer->isecond  >= 86400){
				ptrESysTimer->isecond -= 86400;
				++(ptrESysTimer->iday);
			}
		}
	}
	HPL_Result PLSysAPI_InitializSystemTimer(PLSystemTimerHandle hAndle){
		PL_SystemTimerObject * ptrObject;
		struct  timeval      TimerVal;
		ptrObject = hAndle;
		if(hAndle == NULL_PL)
			return HPLResultF_Paramer_NULL;
		PLSysAPI_MemoryClearZero(ptrObject,PL_CompilerAllocSize(PL_SystemTimerObject));
		ptrObject->cbSize = PL_CompilerAllocSize(PL_SystemTimerObject);
		ptrObject->CycleTimerH = 0;
		ptrObject->CycleTImerL = 0;
		gettimeofday(&TimerVal,0);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,&(ptrObject->AfterSystemTimerKey));
		ptrObject->LastSystemTimerKey 		 	= ptrObject->AfterSystemTimerKey;
		return HPLResult_OK;
	}
/*
	HPL_Result PLSysAPI_GetSystemLastTimerKey(PLSystemTimerHandle hAndle,PL_SystemTimer * ptrLastTimer){
		PL_SystemTimerObject * ptrObject;
		struct timeval         TimerVal;
		PL_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		gettimeofday(&TimerVal,0);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,&LastTimer);
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
		struct timeval         TimerVal;
		PL_SystemTimer         TimerStep,LastTimer;

		ptrObject = hAndle;
		gettimeofday(&TimerVal,0);
		_OperatSysTimerToEngineSysTimer_(&TimerVal,&LastTimer);
		TimerStep.iCalculSymbol = 0;
		if( _MaxSystemTimer_(&LastTimer , &(ptrObject->AfterSystemTimerKey))== (&LastTimer)){
			ptrObject->LastSystemTimerKey  = LastTimer;
			_CalculSysTimerInterval_(&(ptrObject->LastSystemTimerKey),&(ptrObject->AfterSystemTimerKey),&TimerStep);
			ptrObject->ElapseTimer = TimerStep;
		}else{
			PLSysAPI_MemoryClearZero(&TimerStep,PL_CompilerAllocSize(PL_SystemTimer));
			_CalculSysTimerAdd_((&(ptrObject->ElapseTimer)),(&TimerStep));
		}
		*ptrLastTimer=ptrObject->ElapseTimer;
		return HPLResult_OK;
	}


	HPL_Result PLSysAPI_Lib_OpenLibrary(PLLibModuleHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength,int_pl iTag){
		PLLibModuleHandle hAndle;
		UTF8char_pl pLocalName[PL3DSystemFilePathNameMaxLength];
		intV_pl iLNameSize;
		intV_pl iDataPos;
		intV_pl iCvrBSize;
		uintV_pl uCvrFlag;
		if(ptrName==NULL_PL || iwNameLength<=0)
			return HPLResultF_Paramer_NULL;

		PLSysAPI_UTF8_ClearString(pLocalName,PL3DSystemFilePathNameMaxLength);
		uCvrFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		PLSysAPI_SysIO_UTF16toUTF8(ptrName,iwNameLength,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,PL3DSystemFilePathNameMaxLength,&uCvrFlag);
		iLNameSize = PLSysAPI_UTF8_Byte2CharUnit(iCvrBSize);


		hAndle = (PLLibModuleHandle)::dlopen((const_pl char_pl *)pLocalName,RTLD_LAZY);
		(*ptrhAndle) = hAndle;
		return HPLResult_OK;
	}
	HPL_Result PLSysAPI_Lib_CloseLibrary(PLLibModuleHandle hAndle){
		if(hAndle==NULL_PL)
			return HPLResultF_Paramer_NULL;
		dlclose((void_pl *)hAndle);
		return HPLResult_Fail;
	}
	void_pl *  PLSysAPI_Lib_SearchLibraryObject(PLLibModuleHandle hAndle,const_pl UTFSyschar_pl * ptrSymbol,intV_pl iwSymbolLength){
		UTF8char_pl pLocalName[PL3DSystemFilePathNameMaxLength];
		intV_pl iLNameSize;
		intV_pl iDataPos;
		intV_pl iCvrBSize;
		uintV_pl uCvrFlag;
		if((hAndle==NULL_PL) || (ptrSymbol==NULL_PL) || (iwSymbolLength<=0))
			return NULL_PL;
		PLSysAPI_UTF8_ClearString(pLocalName,PL3DSystemFilePathNameMaxLength);
		uCvrFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		PLSysAPI_SysIO_UTF16toUTF8(ptrSymbol,iwSymbolLength,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,PL3DSystemFilePathNameMaxLength,&uCvrFlag);
		iLNameSize = PLSysAPI_UTF8_Byte2CharUnit(iCvrBSize);

		return dlsym((void_pl *)hAndle,(const_pl char_pl *)pLocalName);
	}
	int_pl PLSysAPI_Sys_GetProcessNumber(){
		return sysconf(_SC_NPROCESSORS_ONLN);
	}
	lint_pl PLSysAPI_Sys_GetPhysPagesNumber(){
		return sysconf(_SC_PHYS_PAGES);
	}
	intV_pl PLSysAPI_Sys_GetPhysPageSize(){
		return sysconf(_SC_PAGE_SIZE);
	}
	lint_pl PLSysAPI_Sys_GetSpaceMemory(){
		struct sysinfo tInfo;
		lint_pl lMem;
		if(sysinfo(&tInfo)!=0)
			return -1;
		lMem = 0;
//		lMem=tInfo.freehigh;
//  	lMem <<=32;
		lMem |= tInfo.freeram;
		lMem =lMem * tInfo.mem_unit;
		return lMem;
	}
	intV_pl    PLSysAPI_Sys_GetCPUCacheShareUnit(){
		return 64;
	}
	intV_pl    PLSysAPI_Sys_GetSysAllocMemoryGrain(){
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
		//UTFSyschar_pl
		ptrEnv->iwCWDSize = PLSysAPI_SystemIO_GetCurWD(ptrEnv->pCWD,PL3DSystemFilePathNameMaxLength);
		if(ptrEnv->iwCWDSize<=0)
			return HPLResult_Fail;
		ptrEnv->iwPlusCWDSize = ptrEnv->iwCWDSize;
		PLSysAPI_SysStringCpy(ptrEnv->pPlusCWD,ptrEnv->pCWD,ptrEnv->iwPlusCWDSize);
		return HPLResult_OK;
	}
	intV_pl PLSysAPI_Sys_GetLastError(){
		return (intV_pl)errno;
	}

#endif

