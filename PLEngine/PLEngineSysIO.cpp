/*
 * PLEngineSysIO.cpp
 *
 *  Created on: 2009-7-8
 *      Author: root
 */

#include "header/PLEngineSysIO.h"
#include "header/PLEngineSysSynchron.h"

	HPL_Result __PLSysAPI_SystemIO_EnterFOperateLock(PLDeviceHandle hAndle){
		HPL_Result hResult;
		hResult = PLSysAPI_Syn_EnterThreadSpinLock(&(hAndle->lock));
		return hResult;
	}
	HPL_Result __PLSysAPI_SystemIO_TryEnterFOperateLock(PLDeviceHandle hAndle){
		HPL_Result hResult;
		hResult = PLSysAPI_Syn_TryEnterThreadSpinLock(&(hAndle->lock));
		return hResult;
	}
	void_pl	  __PLSysAPI_SystemIO_LeaveFOperateLock(PLDeviceHandle hAndle){
		PLSysAPI_Syn_LeaveThreadSpinLock(&(hAndle->lock));
	}

	FILEStream * __PLSysAPI_SystemIO_fopen_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,intV_pl iMode){
		FILE * ptrStream;
		char_pl pMode[4];
		UTF8char_pl pLocalFileName[PL3DSystemFilePathNameMaxLength];
		intV_pl iwLFileNameSize;
		intV_pl iLFileNameByteSize;
		intV_pl iSrcDataPos;
		uintV_pl uFlag;

		ptrStream=NULL_PL;
		PLSysAPI_MemoryClearZero(pMode,4);
		if(iMode == PLSysIO_Const_FOpenOperat_Read){
			pMode[0] = (char_pl)0x72;
		}else if(iMode == PLSysIO_Const_FOpenOperat_Write){
			pMode[0] = (char_pl)0x77;
		}else if(iMode == PLSysIO_Const_FOpenOperat_RW){
			pMode[0] = (char_pl)0x77;
			pMode[1] = (char_pl)0x2b;
		}else if(iMode == PLSysIO_Const_FOpenOperat_ReadBin){
			pMode[0] = (char_pl)0x72;
			pMode[1] = (char_pl)0x62;
		}else if(iMode == PLSysIO_Const_FOpenOperat_WriteBin){
			pMode[0] = (char_pl)0x77;
			pMode[1] = (char_pl)0x62;
		}else if(iMode == PLSysIO_Const_FOpenOperat_RWBin){
			pMode[0] = (char_pl)0x77;
			pMode[1] = (char_pl)0x62;
			pMode[2] = (char_pl)0x2b;
		}else if(iMode == PLSysIO_Const_FOpenOperat_WEAdd){
			pMode[0] = (char_pl)0x61;
		}else if(iMode == PLSysIO_Const_FOpenOperat_WBEAdd){
			pMode[0] = (char_pl)0x61;
			pMode[1] = (char_pl)0x62;
		}else if(iMode == PLSysIO_Const_FOpenOperat_RWEndAdd){
			pMode[0] = (char_pl)0x61;
			pMode[1] = (char_pl)0x2b;
		}else if(iMode == PLSysIO_Const_FOpenOperat_RWBEndAdd){
			pMode[0] = (char_pl)0x61;
			pMode[1] = (char_pl)0x62;
			pMode[2] = (char_pl)0x2b;
		}else{
			iMode = 0;
		}
		PLSysAPI_MemoryClearZero(pLocalFileName,PL3DSystemFilePathNameMaxLength);
		iwLFileNameSize = 0;
		iLFileNameByteSize = 0;
		if(pMode[0]==0){
			pMode[0] = 0x72;
			pMode[1] = 0x00;
		}
		uFlag = PLSysIO_Const_UnicodeMark_SmallEnd;

		PLSysAPI_SysIO_UTF16toUTF8(ptrName,iwNSize,&iSrcDataPos,pLocalFileName,&iwLFileNameSize, \
												&iLFileNameByteSize,PL3DSystemFilePathNameMaxLength,&uFlag);
		ptrStream = fopenXX((const_pl char_pl *)pLocalFileName,pMode);
		return ptrStream;
	}
	intV_pl __PLSysAPI_SystemIO_fread_(FILEStream * ptrStream,void_pl * ptrData,intV_pl iSize,intV_pl iRCount){
		intV_pl iRead;
		iRead = 0;
		iRead = freadXX(ptrData,iSize,iRCount,ptrStream);
		if(iRead>0)
			iRead *= iSize;
		return iRead;
	}
	intV_pl __PLSysAPI_SystemIO_fwrite_(FILEStream * ptrStream,const void_pl * ptrData,intV_pl iSize,intV_pl iWCount){
		intV_pl iWrite;
		iWrite = 0;
		iWrite = fwriteXX(ptrData,iSize,iWCount,ptrStream);
		if(iWrite>0)
			iWrite *= iSize;
		return iWrite;
	}
	lint_pl __PLSysAPI_SystemIO_fseek_(FILEStream * ptrStream,lint_pl iMov,ePL_SysIOSeekMode eMode){
		lint_pl iCurPos;
		intV_pl iMode;
		iCurPos=-1;
		if(eMode == PLSys_Const_SystemIO_Seek_Set){
			iMode = SEEK_SET;
		}else if(eMode == PLSys_Const_SystemIO_Seek_CUR){
			iMode = SEEK_CUR;
		}else if(eMode == PLSys_Const_SystemIO_Seek_END){
			iMode = SEEK_END;
		}else{
			return iCurPos;
		}
		fseekXX(ptrStream,(long)iMov,iMode);
		iCurPos = ftellXX(ptrStream);
		return iCurPos;
	}
	void_pl  __PLSysAPI_SystemIO_fclose_(FILEStream * ptrStream){
		fcloseXX(ptrStream);
	}
	void_pl  __PLSysAPI_SystemIO_fflush_(FILEStream * ptrStream){
		fflushXX(ptrStream);
	}
	intV_pl  __PLSysAPI_SystemIO_feof_(FILEStream * ptrStream){
		return feofXX(ptrStream);
	}
	lint_pl __PLSysAPI_SystemIO_fGetFileCurPos_(FILEStream * ptrStream){
		lint_pl iCurPos;
		iCurPos = (lint_pl)ftellXX(ptrStream);
		return iCurPos;
	}
	intV_pl    PLSysAPI_TypeConverAnsi_atoi(const_pl char_pl * ptrValue,intV_pl iSize){
		intV_pl iValue;
		iValue = atoiXX(ptrValue);
		return iValue;
	}
	float_pl   PLSysAPI_TypeConverAnsi_atof(const_pl char_pl * ptrValue,intV_pl iSize){
		float_pl fValue;
		fValue = atofXX(ptrValue);
		return fValue;
	}

