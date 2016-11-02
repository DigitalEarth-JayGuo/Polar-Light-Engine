/*
 * PLEngineSysIOAPI_Linux.cpp
 *
 *  Created on: 2009-7-8
 *      Author: root
 */
#include "../header/Linux/PLEngineSysIOAPI_Linux.h"
#if PLOperat_System == PLOperatSystem_Linux
//	int_pl PLSysAPI_IO_GetCurrentWD(char_pl * ptrWDB,int_pl iMaxLength){
//		return 0;
//	}
	HPL_Result __PLSysAPI_LocalSystemIO_Access_(const_pl UTF8char_pl * ptrName,intV_pl iNSize,uint_pl uMode);
	HPL_Result __PLSysAPI_SystemIO_Create_(PLDeviceHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt){
		intV_pl iFD;
		intV_pl iFlag;
		intV_pl iMode;
		PLDeviceSysIOSt * ptrSysIOSt;
		intV_pl iAllocateSize;
		intV_pl iCacheLineSize;
		UTF8char_pl pLocalName[PL3DSystemFilePathNameMaxLength];
		intV_pl iLNameSize;
		intV_pl iDataPos;
		intV_pl iCvrBSize;
		intV_pl iCvrBMaxLength;
		uintV_pl uCvrFlag;

		if(ptrhAndle==NULL_PL || ptrName==NULL_PL)
			return HPLResultF_Paramer_NULL;
		iFlag = 0;
		iMode = 0;
		if((uMode & PLSysIO_Const_Att_URead) == PLSysIO_Const_Att_URead)
			iMode |= S_IRUSR;
		if((uMode & PLSysIO_Const_Att_UWrite) == PLSysIO_Const_Att_UWrite)
			iMode |= S_IWUSR;
		if((uMode & PLSysIO_Const_Att_UExecute) == PLSysIO_Const_Att_UExecute)
			iMode |= S_IXUSR;
		if((uMode & PLSysIO_Const_Att_UGRead) == PLSysIO_Const_Att_UGRead)
			iMode |= S_IRGRP;
		if((uMode & PLSysIO_Const_Att_UGWrite) == PLSysIO_Const_Att_UGWrite)
			iMode |= S_IWGRP;
		if((uMode & PLSysIO_Const_Att_UGExecute) == PLSysIO_Const_Att_UGExecute)
			iMode |= S_IXGRP;
		if((uMode & PLSysIO_Const_Att_ORead) == PLSysIO_Const_Att_ORead)
			iMode |= S_IROTH;
		if((uMode & PLSysIO_Const_Att_OWrite) == PLSysIO_Const_Att_OWrite)
			iMode |= S_IWOTH;
		if((uMode & PLSysIO_Const_Att_OExecute) == PLSysIO_Const_Att_OExecute)
			iMode |= S_IXOTH;
		if(iMode==0)
			iMode = S_IRUSR;
		if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Read){
			iFlag |= O_RDONLY;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Write){
			iFlag |= O_WRONLY;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_RW){
			iFlag |= O_RDWR;
		}else{
			iFlag |= O_RDONLY;
		}
		if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_CreatAlways){
			iFlag |= O_TRUNC;
			iFlag |= O_CREAT;
		}else{
			iFlag |= O_CREAT;
		}
		PLSysAPI_UTF8_ClearString(pLocalName,PL3DSystemFilePathNameMaxLength);
		uCvrFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = PL3DSystemFilePathNameMaxLength;
		PLSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = PLSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		iFD = (intV_pl)open((const_pl char_pl *)pLocalName,iFlag,iMode);
		if(iFD==-1){
			if(HResulPL_FAILED(__PLSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,PLSysIO_Const_AccessMode_Create)))
				return HPLResultF_IO_NotAccessLevel;
			return HPLResult_Fail;
		}
		iAllocateSize = PL_CompilerAllocSize(PLDeviceSysIOSt);
		iCacheLineSize = PLSys_Const_CPUCacheLineSize;
		iAllocateSize = PLSysAPI_Alignment(iAllocateSize,iCacheLineSize);
		ptrSysIOSt = (PLDeviceSysIOSt *)PLSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_PL){
			close(iFD);
			return HPLResult_Fail;
		}
		PLSysAPI_MemoryClearZero((void_pl *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_pl)iFD;
		PLSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (PLDeviceHandle)ptrSysIOSt;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Open_(PLDeviceHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt){
		intV_pl iFlag;
		intV_pl iFD;
		intV_pl iMode;
		PLDeviceSysIOSt * ptrSysIOSt;
		intV_pl iAllocateSize;
		intV_pl iCacheLineSize;
		UTF8char_pl pLocalName[PL3DSystemFilePathNameMaxLength];
		intV_pl iLNameSize;
		intV_pl iDataPos;
		intV_pl iCvrBSize;
		intV_pl iCvrBMaxLength;
		uintV_pl uCvrFlag;
		iFlag = 0;
		iMode = 0;
		if((uMode & PLSysIO_Const_Att_URead) == PLSysIO_Const_Att_URead)
			iMode |= S_IRUSR;
		if((uMode & PLSysIO_Const_Att_UWrite) == PLSysIO_Const_Att_UWrite)
			iMode |= S_IWUSR;
		if((uMode & PLSysIO_Const_Att_UExecute) == PLSysIO_Const_Att_UExecute)
			iMode |= S_IXUSR;
		if((uMode & PLSysIO_Const_Att_UGRead) == PLSysIO_Const_Att_UGRead)
			iMode |= S_IRGRP;
		if((uMode & PLSysIO_Const_Att_UGWrite) == PLSysIO_Const_Att_UGWrite)
			iMode |= S_IWGRP;
		if((uMode & PLSysIO_Const_Att_UGExecute) == PLSysIO_Const_Att_UGExecute)
			iMode |= S_IXGRP;
		if((uMode & PLSysIO_Const_Att_ORead) == PLSysIO_Const_Att_ORead)
			iMode |= S_IROTH;
		if((uMode & PLSysIO_Const_Att_OWrite) == PLSysIO_Const_Att_OWrite)
			iMode |= S_IWOTH;
		if((uMode & PLSysIO_Const_Att_OExecute) == PLSysIO_Const_Att_OExecute)
			iMode |= S_IXOTH;
		if(iMode==0)
			iMode = S_IRUSR;
		if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Read){
			iFlag |= O_RDONLY;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_Write){
			iFlag |= O_WRONLY;
		}else if((uFlag & PLSysIO_Const_OpenOperat_Open_Mark) == PLSysIO_Const_OpenOperat_RW){
			iFlag |= O_RDWR;
		}else{
			iFlag |= O_RDONLY;
		}
		PLSysAPI_UTF8_ClearString(pLocalName,PL3DSystemFilePathNameMaxLength);
		uCvrFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = PL3DSystemFilePathNameMaxLength;
		PLSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = PLSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		if((uFlag & PLSysIO_Const_OpenMode_OpenTreat_Mark) == PLSysIO_Const_OpenMode_Trunc)
			iFlag |= O_TRUNC;
		if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_Creat){
			iFlag |= O_CREAT;
			iFlag |= O_EXCL;
		}else if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_CreatAlways){
			iFlag |= O_CREAT;
			iFlag |= O_TRUNC;
		}else if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_OpenMust){
			iFlag |= O_CREAT;
		}else if((uFlag & PLSysIO_Const_OpenMode_Creat_Mark) == PLSysIO_Const_OpenMode_NotCreat){
			if(HResulPL_FAILED(__PLSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,PLSysIO_Const_AccessMode_Read)))
				return HPLResultF_IO_NotAccessLevel;
			iFlag |= O_CREAT;
		}else{
			if(HResulPL_FAILED(__PLSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,PLSysIO_Const_AccessMode_Read)))
				return HPLResultF_IO_NotAccessLevel;
			iFlag |= O_CREAT;
		}
		iFD = (intV_pl)open((const_pl char_pl *)pLocalName,iFlag,iMode);
		if(iFD==-1){
			if(HResulPL_FAILED(__PLSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,PLSysIO_Const_AccessMode_Create)))
				return HPLResultF_IO_NotAccessLevel;
			return HPLResult_Fail;
		}
		iAllocateSize = PL_CompilerAllocSize(PLDeviceSysIOSt);
		iCacheLineSize = PLSys_Const_CPUCacheLineSize;
		iAllocateSize = PLSysAPI_Alignment(iAllocateSize,iCacheLineSize);
		ptrSysIOSt = (PLDeviceSysIOSt *)PLSysAPI_AllocateMemory(iAllocateSize);
		if(ptrSysIOSt==NULL_PL){
			close(iFD);
			return HPLResult_Fail;
		}
		PLSysAPI_MemoryClearZero((void_pl *)ptrSysIOSt,iAllocateSize);
		ptrSysIOSt->uFD = (uint_pl)iFD;
		PLSysAPI_Syn_InitializeThreadSpinLock(&(ptrSysIOSt->lock));
		(*ptrhAndle) = (PLDeviceHandle)ptrSysIOSt;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Read_(PLDeviceHandle hAndle,void_pl * ptrBData ,intV_pl iBSize,intV_pl * ptrRSize,void_pl * pSt){
		intV_pl iRSize;
		if(ptrRSize==NULL_PL)
			return HPLResult_Fail;
		*ptrRSize = 0;
		if(hAndle == NULL_PL || ptrBData==NULL_PL || iBSize<=0)
			return HPLResult_Fail;
		iRSize = read((int_pl)(hAndle->uFD),ptrBData,iBSize);
		(*ptrRSize)=iRSize;
		if(iRSize<=-1)
			return HPLResult_Fail;
		if(iRSize==0)
			return HPLResultK_IO_EOF;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Write_(PLDeviceHandle hAndle,const_pl void_pl * ptrWData ,intV_pl iWSize,intV_pl * ptrWSize,void_pl * pSt){
		intV_pl iRWSize;
		if(ptrWSize==NULL_PL)
			return HPLResult_Fail;
		(*ptrWSize) = 0;
		if(hAndle == NULL_PL || ptrWData==NULL_PL || iWSize<=0)
			return HPLResult_Fail;
		iRWSize=write((int_pl)(hAndle->uFD),ptrWData,iWSize);
		(*ptrWSize) = iRWSize;
		if(iRWSize==-1)
			return HPLResult_Fail;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Close_(PLDeviceHandle hAndle){
		intV_pl ierror;
		if(hAndle==NULL_PL)
			return HPLResultF_Paramer_NULL;
		PLSysAPI_Syn_ReleaseThreadSpinLock(&(hAndle->lock));
		ierror=close((int_pl)(hAndle->uFD));
		if(ierror!=0)
			return HPLResult_Fail;
		PLSysAPI_FreeMemory((void_pl *)hAndle);
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_LocalSystemIO_Access_(const_pl UTF8char_pl * ptrName,intV_pl iNSize,uint_pl uMode){
		int iMode;
		int iError;
		if(ptrName==NULL_PL || iNSize<=0)
			return HPLResult_Fail;
		iMode = 0;
		if((uMode & PLSysIO_Const_AccessMode_Create)==PLSysIO_Const_AccessMode_Create)
			iMode |= W_OK;
		if((uMode & PLSysIO_Const_AccessMode_Read)==PLSysIO_Const_AccessMode_Read)
			iMode |= R_OK;
		if((uMode & PLSysIO_Const_AccessMode_Write)==PLSysIO_Const_AccessMode_Write)
			iMode |= R_OK;
		if((uMode & PLSysIO_Const_AccessMode_Execute)==PLSysIO_Const_AccessMode_Execute)
			iMode |= X_OK;
		if(iMode==0)
			return HPLResultF_IO_ModeError;
		iError = ::access((const_pl char_pl *)ptrName,iMode);
		if(iError==0)
			return HPLResult_OK;
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemIO_Access_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uint_pl uMode){
		UTF8char_pl pLocalName[PL3DSystemFilePathNameMaxLength];
		intV_pl iLNameSize;
		intV_pl iDataPos;
		intV_pl iCvrBSize;
		intV_pl iCvrBMaxLength;
		uintV_pl uCvrFlag;
		if(ptrName == NULL_PL || iwNSize<=0)
			return HPLResult_Fail;
		PLSysAPI_UTF8_ClearString(pLocalName,PL3DSystemFilePathNameMaxLength);
		uCvrFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = PL3DSystemFilePathNameMaxLength;
		PLSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = PLSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		return __PLSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,uMode);
	}
	HPL_Result __PLSysAPI_SystemIO_Mkdir_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uint_pl uMode,void_pl * pSt){
		int iMode;
		int ierror;
		UTF8char_pl pLocalName[PL3DSystemFilePathNameMaxLength];
		intV_pl iLNameSize;
		intV_pl iDataPos;
		intV_pl iCvrBSize;
		intV_pl iCvrBMaxLength;
		uintV_pl uCvrFlag;

		if((ptrName==NULL_PL) || (iwNSize<=0))
			return HPLResult_Fail;
		iMode = 0;
		if((uMode & PLSysIO_Const_Att_URead) == PLSysIO_Const_Att_URead)
			iMode |= S_IRUSR;
		if((uMode & PLSysIO_Const_Att_UWrite) == PLSysIO_Const_Att_UWrite)
			iMode |= S_IWUSR;
		if((uMode & PLSysIO_Const_Att_UExecute) == PLSysIO_Const_Att_UExecute)
			iMode |= S_IXUSR;
		if((uMode & PLSysIO_Const_Att_UGRead) == PLSysIO_Const_Att_UGRead)
			iMode |= S_IRGRP;
		if((uMode & PLSysIO_Const_Att_UGWrite) == PLSysIO_Const_Att_UGWrite)
			iMode |= S_IWGRP;
		if((uMode & PLSysIO_Const_Att_UGExecute) == PLSysIO_Const_Att_UGExecute)
			iMode |= S_IXGRP;
		if((uMode & PLSysIO_Const_Att_ORead) == PLSysIO_Const_Att_ORead)
			iMode |= S_IROTH;
		if((uMode & PLSysIO_Const_Att_OWrite) == PLSysIO_Const_Att_OWrite)
			iMode |= S_IWOTH;
		if((uMode & PLSysIO_Const_Att_OExecute) == PLSysIO_Const_Att_OExecute)
			iMode |= S_IXOTH;
		if(iMode==0)
			iMode = S_IRUSR;
		PLSysAPI_UTF8_ClearString(pLocalName,PL3DSystemFilePathNameMaxLength);
		uCvrFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		iCvrBMaxLength = PL3DSystemFilePathNameMaxLength;
		PLSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iDataPos,pLocalName,&iLNameSize,&iCvrBSize,iCvrBMaxLength,&uCvrFlag);
		iLNameSize = PLSysAPI_UTF8_Byte2CharUnit(iCvrBSize);
		ierror = mkdir((const_pl char_pl *)pLocalName,iMode);
		if(ierror!=-1)
			return HPLResult_OK;
		if(HResulPL_FAILED(__PLSysAPI_LocalSystemIO_Access_(pLocalName,iLNameSize,PLSysIO_Const_AccessMode_Create)))
			return HPLResultF_IO_NotAccessLevel;
		return HPLResult_Fail;
	}
	HPL_Result __PLSysAPI_SystemIO_Seek_(PLDeviceHandle hAndle,lint_pl iMov,lint_pl * ptrPos,ePL_SysIOSeekMode eMode,void_pl * pSt){
		off_t iCurPos;
		int_pl   iMode;
		if(hAndle==NULL_PL)
			return HPLResult_Fail;
		if(eMode == PLSys_Const_SystemIO_Seek_Set){
			iMode = SEEK_SET;
		}else if(eMode == PLSys_Const_SystemIO_Seek_CUR){
			iMode = SEEK_CUR;
		}else if(eMode == PLSys_Const_SystemIO_Seek_END){
			iMode = SEEK_END;
		}else{
			(*ptrPos) = -1;
			return HPLResult_Fail;
		}
		iCurPos = lseek((int_pl)(hAndle->uFD),iMov,iMode);
		if(iCurPos==-1){
			(*ptrPos) = -1;
			//errno
			return HPLResult_Fail;
		}
		(*ptrPos) = (lint_pl)iCurPos;
		return HPLResult_OK;
	}

	intV_pl   __PLSysAPI_SystemIO_GetCurWD_(UTFSyschar_pl * ptrCurWD,intV_pl iMaxLength){
		UTF8char_pl pLocalCWD[PL3DSystemFilePathNameMaxLength];
		intV_pl iLCWDSize;
		intV_pl iWDLength;
		intV_pl iDataPos;
		intV_pl iCvrBSize;
		uintV_pl uCvrFlag;
		//intV_pl i
		iWDLength = 0;
		PLSysAPI_UTF8_ClearString(pLocalCWD,PL3DSystemFilePathNameMaxLength);
		getcwd((char_pl *) pLocalCWD,PL3DSystemFilePathNameMaxLength);
		iLCWDSize = PLSysAPI_UTF8_StringSize((const_pl UTF8char_pl *)pLocalCWD);
		uCvrFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
		PLSysAPI_SysIO_UTF8toUTF16(pLocalCWD,iLCWDSize,&iDataPos,ptrCurWD,&iWDLength,&iCvrBSize,iMaxLength,&uCvrFlag);
		iWDLength = PLSysAPI_SysByte2CharUnit(iCvrBSize);
		if(iWDLength>0){
			if(ptrCurWD[iWDLength - 1]!=PLSys_ConstChar_URLPathConstDivision){
				ptrCurWD[iWDLength] = PLSys_ConstChar_URLPathConstDivision;
				iWDLength++;
			}
		}
		return iWDLength;
	}
#endif
