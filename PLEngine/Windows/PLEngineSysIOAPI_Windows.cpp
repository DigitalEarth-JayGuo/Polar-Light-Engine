/*
 * PLEngineSysIOAPI_Windows.cpp
 *
 *  Created on: 2009-7-8
 *      Author: root
 */
#include "../header/Windows/PLEngineSysIOAPI_Windows.h"
#if PLOperat_System == PLOperatSystem_Window
//	int_pl PLSysAPI_IO_GetCurrentWD(char_pl * ptrWDB,int_pl iMaxLength){
//		return 0;
//	}
	HPL_Result __PLSysAPI_SystemIO_Create_(PLDeviceHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt){
		DWORD dAccessMode;
		DWORD dShareMode;
		DWORD dCreatDisp;
		DWORD dFlag;
		HANDLE hWinAndle;
		SECURITY_ATTRIBUTES security;
		PLDeviceSysIOSt * ptrSysIOSt;
		int_pl iAllocateSize;
		int_pl iCacheLineSize;
		ptrSysIOSt = NULL;
		//PLDeviceHandle PLDeviceSysIOSt *
		if(ptrhAndle==NULL_PL)
			return HPLResult_Fail;
		(*ptrhAndle)=NULL_PL;
		if((ptrName==NULL_PL) || (iwNSize<=0))
			return HPLResult_Fail;
		PLSysAPI_MemoryClearZero(&security,PL_CompilerAllocSize(SECURITY_ATTRIBUTES));
		security.bInheritHandle = FALSE;
		dAccessMode = 0;
		dCreatDisp = 0;
		dShareMode = 0;
		dFlag      = 0;

		if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Read){
			dAccessMode |= GENERIC_READ;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Write){
			dAccessMode |= GENERIC_WRITE;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_RW){
			dAccessMode |= GENERIC_READ | GENERIC_WRITE;
		}else{
			dAccessMode |= GENERIC_READ;
		}

		if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_CreatAlways){
			dCreatDisp = CREATE_ALWAYS;
		}else{
			dCreatDisp = CREATE_NEW;
		}
		if((uFlag & PLSysIO_Const_ShareMode_Open_Mark) == PLSysIO_Const_ShareMode_Read){
			dShareMode = FILE_SHARE_READ;
		}else if((uFlag & PLSysIO_Const_ShareMode_Open_Mark) == PLSysIO_Const_ShareMode_Write){
			dShareMode = FILE_SHARE_WRITE;
		}else if((uFlag & PLSysIO_Const_ShareMode_Open_Mark) == PLSysIO_Const_ShareMode_RW){
			dShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
		}else{
			dShareMode = FILE_SHARE_READ;
		}
//		if((uFlag & PLSysIO_Const_OpenMode_OpenTreat_Mark) == PLSysIO_Const_OpenMode_Trunc)
//			dCreatDisp |= TRUNCATE_EXISTING;
//		if((uFlag & PLSysIO_Const_OpenMode_OpenTreat_Mark) == PLSysIO_Const_OpenMode_Append){
//		}

//		if((uFlag & PLSysIO_Const_OpenMode_FT_Mark) == PLSysIO_Const_OpenMode_FTDirectory){
//			return HPLResult_Fail;
//		}
		hWinAndle = ::CreateFileW((LPWSTR)ptrName,dAccessMode,dShareMode,NULL_PL,dCreatDisp,dFlag,NULL_PL);
		if(hWinAndle == INVALID_HANDLE_VALUE)
			return HPLResult_Fail;
		iAllocateSize = PL_CompilerAllocSize(PLDeviceSysIOSt);
		iCacheLineSize = PLSys_Const_CPUCacheLineSize;
		iAllocateSize = PLSysAPI_Alignment(iAllocateSize,iCacheLineSize) + iCacheLineSize;
		ptrSysIOSt = (PLDeviceSysIOSt *)PLSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_PL){
			CloseHandle(hWinAndle);
			return HPLResult_Fail;
		}
		PLSysAPI_MemoryClearZero((void_pl *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_pl)hWinAndle;

		PLSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (PLDeviceHandle)ptrSysIOSt;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Open_(PLDeviceHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt){
		DWORD dAccessMode;
		DWORD dShareMode;
		DWORD dCreatDisp;
		DWORD dFlag;
		HANDLE hWinAndle;
		SECURITY_ATTRIBUTES security;
		PLDeviceSysIOSt * ptrSysIOSt;
		intV_pl iAllocateSize;
		intV_pl iCacheLineSize;
		ptrSysIOSt = NULL_PL;
		if(ptrhAndle==NULL_PL)
			return HPLResult_Fail;
		(*ptrhAndle) = NULL_PL;
		if((ptrName==NULL_PL) || (iwNSize<=0))
			return HPLResult_Fail;
		PLSysAPI_MemoryClearZero(&security,PL_CompilerAllocSize(SECURITY_ATTRIBUTES));
		security.bInheritHandle = FALSE;
		dAccessMode = 0;
		dCreatDisp = 0;
		dShareMode = 0;
		dFlag      = 0;

		if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Read){
			dAccessMode |= GENERIC_READ;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Write){
			dAccessMode |= GENERIC_WRITE;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_RW){
			dAccessMode |= GENERIC_READ | GENERIC_WRITE;
		}else{
			dAccessMode |= GENERIC_READ;
		}

//		if((uMode & PLSysIO_Const_Att_URead) == PLSysIO_Const_Att_URead)
//			dAccessMode |= GENERIC_READ;
//		if((uMode & PLSysIO_Const_Att_UWrite) == PLSysIO_Const_Att_UWrite)
//			dAccessMode |= GENERIC_WRITE;
//		if(dAccessMode==0)
//			dAccessMode = GENERIC_READ | GENERIC_WRITE;

		//always Create
		if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_CreatAlways){
			dCreatDisp = CREATE_ALWAYS;
		}//Open
		else if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_NotCreat){
			if((uFlag & PLSysIO_Const_OpenMode_OpenTreat_Mark) == PLSysIO_Const_OpenMode_Trunc){
				dCreatDisp = TRUNCATE_EXISTING;
			}else{
				dCreatDisp = OPEN_EXISTING;
			}
		}
		else if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_Creat){
			dCreatDisp = CREATE_NEW;
		}
		else if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_OpenMust){
			dCreatDisp = OPEN_ALWAYS | CREATE_NEW;
			if((uFlag & PLSysIO_Const_OpenMode_OpenTreat_Mark) == PLSysIO_Const_OpenMode_Trunc)
				dCreatDisp = CREATE_ALWAYS;
		}
		else{
			dCreatDisp = OPEN_ALWAYS;
		}
		dShareMode = FILE_SHARE_READ;
		hWinAndle = ::CreateFileW((LPWSTR)ptrName,dAccessMode,dShareMode,NULL_PL,dCreatDisp,dFlag,NULL_PL);
		if(hWinAndle == INVALID_HANDLE_VALUE)
			return HPLResult_Fail;
		iAllocateSize = PL_CompilerAllocSize(PLDeviceSysIOSt);
		iCacheLineSize = PLSys_Const_CPUCacheLineSize;
		iAllocateSize = PLSysAPI_Alignment(iAllocateSize,iCacheLineSize);
		ptrSysIOSt = (PLDeviceSysIOSt *)PLSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_PL){
			CloseHandle(hWinAndle);
			return HPLResult_Fail;
		}
		PLSysAPI_MemoryClearZero((void_pl *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_pl)hWinAndle;
		PLSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (PLDeviceHandle)ptrSysIOSt;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Read_(PLDeviceHandle hAndle,void_pl * ptrBData ,intV_pl iBSize,intV_pl * ptrRSize,void_pl * pSt){
		DWORD dRSize;
		BOOL  bOK;
		intV_pl iOffSet;
		intV_pl iAlignedSize;
		if(ptrRSize==NULL_PL)
			return HPLResult_Fail;
		(*ptrRSize) = 0;
		if(hAndle==NULL_PL)
			return HPLResult_Fail;
		iOffSet = 0;
		bOK = FALSE;
		iAlignedSize = iBSize & (~(PLSysIO_Const_ReadDataCacheSize - 1));
		while(iOffSet<iAlignedSize){
			bOK = ReadFile((HANDLE)(hAndle->uFD),&(((byte_pl *)ptrBData)[iOffSet]),(DWORD)(PLSysIO_Const_ReadDataCacheSize),&dRSize,NULL_PL);
			if((bOK == FALSE) || (dRSize!=PLSysIO_Const_ReadDataCacheSize))
				break;
			iOffSet += PLSysIO_Const_ReadDataCacheSize;
		}
		if(iOffSet != iAlignedSize){
			if(iOffSet == 0)
				return HPLResult_Fail;
			(*ptrRSize) = iOffSet;
			return HPLResult_OK;
		}
		iAlignedSize = (iBSize & (PLSysIO_Const_ReadDataCacheSize - 1));
		if(iAlignedSize != 0){
			bOK = ReadFile((HANDLE)(hAndle->uFD),&(((byte_pl *)ptrBData)[iOffSet]),(DWORD)(iAlignedSize),&dRSize,NULL_PL);
			if((bOK == TRUE) && (dRSize != 0)){
				iOffSet += dRSize;
			}
		}
		if(iOffSet<=0){
			(*ptrRSize) = 0;
			return HPLResult_Fail;
		}
		(*ptrRSize) = (intV_pl)iOffSet;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Write_(PLDeviceHandle hAndle,const_pl void_pl * ptrWData ,intV_pl iWSize,intV_pl * ptrWSize,void_pl * pSt){
		DWORD dwSize;
		BOOL bOK;
		if(ptrWSize==NULL_PL)
			return HPLResult_Fail;
		(*ptrWSize) = 0;
		if(hAndle==NULL_PL)
			return HPLResult_Fail;
		if(ptrWData == NULL_PL || iWSize<=0)
			return HPLResult_Fail;
		bOK = WriteFile((HANDLE)(hAndle->uFD),ptrWData,(DWORD)iWSize,&dwSize,NULL_PL);
		if(bOK==FALSE)
			return HPLResult_Fail;
		(*ptrWSize) = (int_pl)dwSize;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Close_(PLDeviceHandle hAndle){
		if(hAndle==NULL_PL)
			return HPLResult_Fail;
		PLSysAPI_Syn_ReleaseThreadSpinLock(&(hAndle->lock));
		if(CloseHandle((HANDLE)(hAndle->uFD))==FALSE)
			return HPLResult_Fail;
		PLSysAPI_FreeMemory((void_pl *)hAndle);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Access_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uint_pl uMode){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Mkdir_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uint_pl uMode,void_pl * pSt){
		BOOL bOK;
		SECURITY_ATTRIBUTES security;
		if((ptrName==NULL_PL) || (iwNSize<=0))
			return HPLResult_Fail;
		PLSysAPI_MemoryClearZero(&security,PL_CompilerAllocSize(SECURITY_ATTRIBUTES));
		security.bInheritHandle = FALSE;
		bOK=CreateDirectoryW((LPWSTR)ptrName,&security);
		if(bOK == TRUE)
			return HPLResult_OK;
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemIO_Seek_(PLDeviceHandle hAndle,lint_pl iMov,lint_pl * ptrPos,ePL_SysIOSeekMode eMode,void_pl * pSt){
//		off_t iCurPos;
		DWORD   dMode;
		lint_pl lMov;
		DWORD   dError;
		LARGE_INTEGER StLMov;
		LARGE_INTEGER StRLMov;
		if(hAndle==NULL_PL)
			return HPLResult_Fail;
		if(eMode == PLSys_Const_SystemIO_Seek_Set){
			dMode = FILE_BEGIN;
		}else if(eMode == PLSys_Const_SystemIO_Seek_CUR){
			dMode = FILE_CURRENT;
		}else if(eMode == PLSys_Const_SystemIO_Seek_END){
			dMode = FILE_END;
		}else{
			(*ptrPos) = -1;
			return HPLResult_Fail;
		}
		lMov = 0;
		*ptrPos = -1;

		PLSysAPI_MemoryClearZero(&StLMov,PL_CompilerAllocSize(LARGE_INTEGER));
		PLSysAPI_MemoryClearZero(&StRLMov,PL_CompilerAllocSize(LARGE_INTEGER));
		PLSysAPI_MemoryCpy(&StLMov,&iMov,PL_CompilerAllocSize(lint_pl));
		::SetFilePointerEx((HANDLE)(hAndle->uFD),StLMov,&StRLMov,dMode);
		PLSysAPI_MemoryCpy(&lMov,&StRLMov,PL_CompilerAllocSize(lint_pl));
		if(iMov!=lMov){
			dError = GetLastError();
			return HPLResult_Fail;
		}
		*ptrPos = lMov;
		return HPLResult_OK;
	}
	intV_pl  __PLSysAPI_SystemIO_GetCurWD_(UTF16char_pl * ptrCurWD,intV_pl iMaxLength){
		DWORD dBMaxSize;
		DWORD dBRSize;
		intV_pl iWDLength;
		intV_pl iPos;
		iWDLength = 0;
		dBMaxSize = (DWORD)iMaxLength;
		dBRSize=::GetModuleFileNameW(NULL,(LPWSTR)ptrCurWD,dBMaxSize);
		if(dBRSize>0){
			iPos = PLSysAPI_UTF16_findMarkCharR(ptrCurWD,(intV_pl)(dBRSize),PLSys_ConstChar_URLPathConstDivision);
			if(iPos>0){
				dBRSize = iPos + 1;
			}
			PLSysAPI_SysStringClear(&(ptrCurWD[dBRSize]),(dBMaxSize - dBRSize));
		}
		iWDLength = dBRSize;
		return iWDLength;
	}

#endif
