/*
 * PLEngineSysEnvIFM.cpp
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "header/PLEngineSysEnvIFM.h"

HPPLEngine PLSysAPI_Sys_GetGlobalEngineHandle(){
	return (HPPLEngine)g_ptrCurrentEngineState;
}
PL_OperatSysEnvSet * PLSysAPI_Sys_GetOperatSystemEnv(HPPLEngine hAndle){
	PL_EngineState * ptrState;
	ptrState = (PL_EngineState *)hAndle;
	if(ptrState == NULL_PL)
		return NULL_PL;
	return &(ptrState->OperatEnv);
}
PL_ConstSystemInfo * PLSysAPI_Sys_GetConstSystemInfo(HPPLEngine hAndle){
	PL_EngineState * ptrState;
	ptrState = (PL_EngineState *)hAndle;
	if(ptrState == NULL_PL)
		return NULL_PL;
	return &(ptrState->ConstSysInfo);
}
PLConstCharTableHandle 	PLSysAPI_Sys_GetEngineConstCharTable(HPPLEngine hAndle){
	PL_EngineState * ptrState;
	ptrState = (PL_EngineState *)hAndle;
	if(ptrState == NULL_PL)
		return NULL_PL;
	return ptrState->hSysConstCharTable;
}

PLFileCFGHandle __PLSysAPI_Sys_OpenCfgFile_Unicode8(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength){
	PL_FileCfgHeader * ptrhAndle;
	PL_FileCfgTable  * ptrCfgTable;
	PL_FileCfgTable  * ptrPrvCfgTable;
	FILEStream * hFile;
	UTF8char_pl pRData[PLSysIO_Const_TextLineMaxLength];
	UTF8char_pl pFileMark[PLSysChar_Const_UTF8MarkSize];
	UTF8char_pl pTable[PLCfg_Const_LableNameMaxSize];
	intV_pl iTableSize;
	intV_pl iAllocSize;
	intV_pl iStSize;
	intV_pl iCacheLineSize;
	intV_pl iReadSize;
	intV_pl iCount;
	intV_pl iMark;
	lint_pl lFilePos;
	intV_pl iBegin;
	AddresValue_pl  addresV;
	bool_pl bFileEnd;
	bool_pl bMarkLine;
	ptrhAndle = NULL_PL;
	lFilePos = 0;
	do{
		if(ptrName==NULL_PL || iwNameLength<=0)
			break;
		hFile = PLSysAPI_SystemIO_fopen(ptrName,iwNameLength,PLSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_PL)
			break;
		iReadSize = PLSysAPI_UTF16_CharSize2ByteSize(PLSysChar_Const_UTF8MarkSize);
		if(PLSysAPI_SystemIO_fread(hFile,pFileMark,iReadSize,1)!=iReadSize){
			PLSysAPI_SystemIO_fclose(hFile);
			break;
		}
		if(PLSysAPI_UTF8_StrCmp(pFileMark,PUTF8IOMark,iReadSize) == false_pl){
			PLSysAPI_SystemIO_fclose(hFile);
			break;
		}
		lFilePos = iReadSize;
		iCacheLineSize = PLSys_Const_CPUCacheLineSize;
		iStSize    = PL_Sizeof(PL_FileCfgHeader);
		iAllocSize = PLSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrhAndle  = (PL_FileCfgHeader *)PLSysAPI_AllocateMemory(iAllocSize);
		PLSysAPI_MemoryClearZero((void_pl *)ptrhAndle,iAllocSize);
		if(ptrhAndle==NULL_PL){
			PLSysAPI_SystemIO_fclose(hFile);
			break;
		}
		addresV = (AddresValue_pl)ptrhAndle;
		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
		((PL_FileCfgHeader *)(addresV))->ptrMem = (void_pl *)ptrhAndle;
		ptrhAndle = (PL_FileCfgHeader *)addresV;
		ptrhAndle->hFile = hFile;
		ptrhAndle->cbSize = iStSize;
		ptrhAndle->eCharCode = PLSys_Const_Unicode8;
		ptrhAndle->iLableAMount = 0;
		ptrCfgTable = &(ptrhAndle->Tables);
		ptrPrvCfgTable = NULL_PL;
		iReadSize = 0;
		iMark     = 0;
		bFileEnd = false_pl;
		while(bFileEnd==false_pl){
			PLSysAPI_UTF8_ClearString(pRData,PLSysIO_Const_TextLineMaxLength);
			iReadSize = PLSysAPI_SystemIO_fread(hFile,pRData,1,PLSysIO_Const_TextLineMaxLength);
			if(iReadSize<=0){
				if((iReadSize<0) || (PLSysAPI_SystemIO_feof(hFile)==0))
					break;
				iReadSize = PLSysAPI_UTF8_StringSize(pRData);
				bFileEnd = true_pl;
			}
			bMarkLine = true_pl;
			iBegin = 0;
			for(iCount = 0;iCount<iReadSize;iCount++){
				if((iMark & 2) == 2){
					iMark &= (~2);
					if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
						if(pRData[iCount] == 0x0d)
							iMark |= 2;
						continue;
					}
					if(bMarkLine == true_pl){
						if((iMark & 1) == 1){
							if(iTableSize>=PLCfg_Const_LableNameMaxSize){
								bMarkLine = false_pl;
								continue;
							}
							pTable[iTableSize] = pRData[iCount];
							iTableSize++;
							if(iTableSize>=PLCfg_Const_LableNameMaxSize){
								bMarkLine = false_pl;
							}
						}else{
							bMarkLine = false_pl;
						}
					}
				}else{
					if(bMarkLine == false_pl){
						if(pRData[iCount]==0x0a){
							bMarkLine = true_pl;
							iBegin = iCount + 1;
							if((iMark & 4) == 4){
								iMark &= (~4);
								if(ptrCfgTable->iLableCount>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount - 1] = lFilePos + iCount + 1;
								}
							}
							iMark = 0;
						}else if(pRData[iCount]=='\\'){
							iMark |= 2;
						}
					}else{
						if((iMark & 1) == 1){
							if(pRData[iCount] != ']'){
								if(pRData[iCount] == '\\'){
									iMark |= 2;
									continue;
								}else if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
									bMarkLine = false_pl;
									iCount--;
									continue;
								}else if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)
										|| ((pRData[iCount]==0xfe)&&(iCount+1<iCount)&&(pRData[iCount]==0x09))){
									bMarkLine = false_pl;
									continue;
								}
								pTable[iTableSize] = pRData[iCount];
								iTableSize++;
								if(iTableSize>=PLCfg_Const_LableNameMaxSize){
									bMarkLine = false_pl;
								}
							}else{
								//iMark &= (~1);
								if(iTableSize>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount] 	= lFilePos + iCount + 1;
									ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount] = ((~0)>>1);
									if(ptrCfgTable->iLableCount>0){
										ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos + iBegin;
									}
									iMark |= 4;
									#if PLESystem_CharCodeUXX == PLEngineSysChar_Unicode16
										intV_pl iConverDataPos;
										intV_pl iConverSize;
										intV_pl iConverBSize;
										uintV_pl uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
										PLSysAPI_SysIO_UTF8toUTF16((const_pl UTF8char_pl *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize, \
												PLSysAPI_UTF16_CharSize2ByteSize(PLCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  PLSysAPI_UTF16_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											PLSysAPI_UTF16_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),PLCfg_Const_LableNameMaxSize);
										}
									#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode32
										intV_pl iConverDataPos;
										intV_pl iConverSize;
										intV_pl iConverBSize;
										uintV_pl uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
										PLSysAPI_SysIO_UTF8toUTF32((const_pl UTF8char_pl *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize, \
												PLSysAPI_UTF32_CharSize2ByteSize(PLCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  PLSysAPI_UTF32_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											PLSysAPI_UTF32_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),PLCfg_Const_LableNameMaxSize);
										}
									#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode8
										PLSysAPI_UTF8_StrCpy(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0]),pTable,iTableSize);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] 	= iTableSize;
									#endif
									(ptrCfgTable->iLableCount)++;
									(ptrhAndle->iLableAMount)++;
									if(ptrCfgTable->iLableCount>=PLCfg_Const_LableMaxCount){
										iStSize    = PL_Sizeof(PL_FileCfgTable);
										ptrCfgTable->ptrNext = (PL_FileCfgTable *)PLSysAPI_AllocateMemory(iStSize);
										if(ptrCfgTable->ptrNext==NULL_PL){
											goto _jmp_pl_endCfgRead;
										}
										ptrPrvCfgTable = ptrCfgTable;
										ptrCfgTable = ptrPrvCfgTable->ptrNext;
										PLSysAPI_MemoryClearZero(ptrCfgTable,iStSize);
									}
								}
								bMarkLine = false_pl;
							}
						}else{
							if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)
									|| ((pRData[iCount]==0xfe)&&(iCount+1<iCount)&&(pRData[iCount]==0x09))){
								continue;
							}
							if(pRData[iCount] == '\\'){
								iMark |= 2;
							}
							else if(pRData[iCount] != '['){
								bMarkLine = false_pl;
								iCount--;
							}else{
								iMark |= 1;
								iTableSize = 0;
							}
						}
					}
				}
			}
			lFilePos += iCount;
			if((bFileEnd == true_pl) && (ptrCfgTable->iLableCount>0)){
				ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos;
			}
		}
	}while(0);
_jmp_pl_endCfgRead:
	return ptrhAndle;
}

intV_pl __PLSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(PL_FileCfgHeader * ptrFileHeader,const_pl UTF8char_pl * ptrID,intV_pl iIDSize,UTF8char_pl * ptrValue,intV_pl iMaxSize,lint_pl iLength){
	UTF8char_pl pRData[PLSysIO_Const_TextLineMaxLength];
	intV_pl iReadSize;
	intV_pl iIDBSize;
	intV_pl iValueSize;
	intV_pl iMark;
	intV_pl iCount;
	iValueSize = 0;
	iMark = 0;
	if(iLength > PLSysIO_Const_TextLineMaxLength){
		iReadSize = PLSysIO_Const_TextLineMaxLength;
		iLength -= PLSysIO_Const_TextLineMaxLength;
	}else{
		iReadSize = iLength;
		iLength = 0;
	}
	iIDBSize = 0;
	iValueSize = 0;
	/*  if ((iMark & 1) == 1) Fill Value String
	 *  if ((iMark & 8) == 8) find end line char
	 *  if ((iMark & 2) == 2) Conver char
	 *  if ((iMark & 4) == 4) Begin Key String
	 *  if ((iMark & 16)==16) ID find end
	 * */
	while((iReadSize>0) && (PLSysAPI_SystemIO_fread(ptrFileHeader->hFile,pRData,1,iReadSize)==iReadSize)){
		for(iCount=0; iCount < iReadSize ;iCount++){
			if((iMark & 2) == 2){
				iMark &= (~2);
				if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
					if(pRData[iCount] == 0x0d)
						iMark |= 2;
					continue;
				}
				if((iMark & 8) == 8)
					continue;
				if((iMark & 1) == 1){
					if((iMark & 4) != 4){
						iValueSize = 0;
						return iValueSize;
					}else{
						if(iValueSize>=iMaxSize)
							return iValueSize;
						ptrValue[iValueSize] = pRData[iCount];
						iValueSize++;
					}
				}else{
					if((iMark & 16) == 16){
						iMark |= 8;
					}else if((iMark & 4)!=4){
						iMark |= 4;
						iCount--;
					}else{
						if((iIDBSize>=iIDSize) || (pRData[iCount]!=ptrID[iIDBSize])){
							iMark |= 8;
						}else{
							iIDBSize++;
						}
					}
				}
			}else{
				if((iMark & 8) == 8){
					if(pRData[iCount] == '\\'){
						iMark |= 2;
					}else if(pRData[iCount] == 0x0a){
						iMark = 0;
						iIDBSize = 0;
					}
				}else if((iMark & 1) == 1){
					if((iMark & 4)!=4){
						if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){
							continue;
						}
						if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if(pRData[iCount] == '"'){
							iMark |= 4;
						}else{
							iValueSize = 0;
							return iValueSize;
						}
					}else{
						if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if(pRData[iCount] == '"'){
							return iValueSize;
						}else if((pRData[iCount] == 0x0d) || (pRData[iCount] == 0x0a)){
							iValueSize = 0;
							return iValueSize;
						}else{
							if(iValueSize>=iMaxSize){
								return iValueSize;
							}
							ptrValue[iValueSize] = pRData[iCount];
							iValueSize++;
						}
					}
				}else{
					if((iMark & 16) == 16){
						if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){

						}else if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if(pRData[iCount] == '='){
							iMark = 1;
						}else{
							iMark |= 8;
						}
					}else if((iMark & 4) != 4){
						if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){
							continue;
						}
						if(pRData[iCount] == 0x0d || pRData[iCount] == 0x0a){
							iMark |= 8;
							iCount--;
						}else if(pRData[iCount] == '='){
							iMark |= 8;
						}else if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else{
							iMark |= 4;
							iCount--;
						}
					}else{
						if(pRData[iCount] == '\\'){
							iMark |= 2;
						}else if((pRData[iCount]==0x20) || (pRData[iCount]==0x09)){
							if(iIDBSize == iIDSize){
								iMark |= 16;
							}else{
								iMark |= 8;
							}
						}else if(pRData[iCount] == '='){
							if(iIDBSize == iIDSize){
								iMark = 1;
							}else{
								iMark |= 8;
							}
						}else if((pRData[iCount]==0x0d) || (pRData[iCount]==0x0a)){
							iMark |= 8;
							iCount--;
						}else{
							if((ptrID[iIDBSize] == pRData[iCount]) && (iIDBSize<iIDSize)){
								iIDBSize++;
							}else{
								iMark |= 8;
							}
						}
					}
				}
			}
		}
		if(iLength > PLSysIO_Const_TextLineMaxLength){
			iReadSize = PLSysIO_Const_TextLineMaxLength;
			iLength -= PLSysIO_Const_TextLineMaxLength;
		}else{
			iReadSize = iLength;
			iLength = 0;
		}
	}
	return iValueSize;
}
intV_pl __PLSysAPI_Sys_GetCfgFiletoString_Unicode8(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize,UTF8char_pl * ptrString,intV_pl iMaxSize){
	intV_pl iDataSize;
	intV_pl iCount;
	lint_pl lLength;
	PL_FileCfgHeader * ptrFileHeader;
	PL_FileCfgTable  * ptrCfgTable;
	ptrFileHeader = (PL_FileCfgHeader *)hAndle;
	iDataSize = 0;
	ptrCfgTable = &(ptrFileHeader->Tables);
	while(ptrCfgTable!=NULL_PL){
		for(iCount = 0;iCount<ptrCfgTable->iLableCount;iCount++){
			if((iwLabelNSize == ptrCfgTable->iTableSize[iCount]) && (iwLabelNSize!=0) && (PLSysAPI_SysStringCmp(ptrLabelN,&(ptrCfgTable->pTableN[iCount][0]),iwLabelNSize) == true_pl)){
				PLSysAPI_SystemIO_fseek(ptrFileHeader->hFile,ptrCfgTable->lTablePos[iCount],PLSys_Const_SystemIO_Seek_Set);
				if(ptrCfgTable->lTableEndPos[iCount] > ptrCfgTable->lTablePos[iCount]){
					lLength = ptrCfgTable->lTableEndPos[iCount] - ptrCfgTable->lTablePos[iCount];
					#if PLESystem_CharCodeUXX == PLEngineSysChar_Unicode16
						UTF8char_pl pConvID[PLCfg_Const_IDNameMaxSize];
						intV_pl iConverDataPos;
						intV_pl iConverSize;
						intV_pl iConverBSize;
						uintV_pl uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
						PLSysAPI_UTF8_ClearString(pConvID,PLCfg_Const_IDNameMaxSize);
						PLSysAPI_SysIO_UTF16toUTF8((const_pl UTF16char_pl *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,PLSysAPI_UTF8_CharSize2ByteSize(PLCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = PLSysAPI_UTF8_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iDataSize = __PLSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iMaxSize,lLength);
						if((iMaxSize - iDataSize) > 0){
							PLSysAPI_UTF8_ClearString(&(ptrString[iDataSize]),(iMaxSize - iDataSize));
						}
					#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode8
						iwDataSize = __PLSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(ptrFileHeader,ptrID,iwIDSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							PLSysAPI_UTF8_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode32
						UTF8char_pl pConvID[PLCfg_Const_IDNameMaxSize];
						intV_pl iConverDataPos;
						intV_pl iConverSize;
						intV_pl iConverBSize;
						uintV_pl uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
						PLSysAPI_UTF8_ClearString(pConvID,PLCfg_Const_IDNameMaxSize);
						PLSysAPI_SysIO_UTF32toUTF8((const_pl UTF32char_pl *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,PLSysAPI_UTF8_CharSize2ByteSize(PLCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = PLSysAPI_UTF8_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iwDataSize = __PLSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							PLSysAPI_UTF8_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#endif
				}
				break;
			}
		}
		ptrCfgTable = ptrCfgTable->ptrNext;
	}

	return iDataSize;
}
intV_pl __PLSysAPI_Sys_GetCfgFiletoInt__Unicode8(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize){
	UTF8char_pl pValue[64];
	intV_pl  iwValueSize;
	intV_pl  iValue;
	iValue = 0;
	PLSysAPI_UTF8_ClearString(pValue,64);
	iwValueSize = __PLSysAPI_Sys_GetCfgFiletoString_Unicode8(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		iValue = PLSysAPI_TypeConverUTF8_atoi(pValue,iwValueSize);
	}
	return iValue;
}
float_pl __PLSysAPI_Sys_GetCfgFiletoFloat__Unicode8(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize){
	UTF8char_pl pValue[64];
	intV_pl  iwValueSize;
	float_pl fValue;
	fValue = _FL_(0.0);
	PLSysAPI_UTF8_ClearString(pValue,64);
	iwValueSize = __PLSysAPI_Sys_GetCfgFiletoString_Unicode8(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		fValue = PLSysAPI_TypeConverUTF8_atof(pValue,iwValueSize);
	}
	return fValue;
}
HPL_Result __PLSysAPI_Sys_CloseCfgFile__Unicode8(PLFileCFGHandle hAndle){
	PL_FileCfgHeader * ptrhAndle;
	PL_FileCfgTable  * ptrCfgTables;
	PL_FileCfgTable  * ptrFreeCfgTables;
	ptrhAndle = (PL_FileCfgHeader *)hAndle;
	if(ptrhAndle==NULL_PL)
		return HPLResult_Fail;
	PLSysAPI_SystemIO_fclose(ptrhAndle->hFile);
	ptrCfgTables = &(ptrhAndle->Tables);
	ptrCfgTables = ptrCfgTables->ptrNext;
	while(ptrCfgTables!=NULL_PL){
		ptrFreeCfgTables = ptrCfgTables;
		ptrCfgTables = ptrFreeCfgTables->ptrNext;
		PLSysAPI_FreeMemory(ptrFreeCfgTables);
	}
	PLSysAPI_FreeMemory(ptrhAndle->ptrMem);
	return HPLResult_OK;
}


PLFileCFGHandle __PLSysAPI_Sys_OpenCfgFile__Unicode16(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength){
	PL_FileCfgHeader * ptrhAndle;
	PL_FileCfgTable  * ptrCfgTable;
	PL_FileCfgTable  * ptrPrvCfgTable;
	FILEStream * hFile;
	UTF16char_pl pRData[PLSysIO_Const_TextLineMaxLength];
	UTF16char_pl pFileMark[PLSysChar_Const_SysStringMarkSize];
	UTF16char_pl pTable[PLCfg_Const_LableNameMaxSize];
	intV_pl iTableSize;
	intV_pl iAllocSize;
	intV_pl iStSize;
	intV_pl iCacheLineSize;
	intV_pl iReadSize;
	intV_pl iBRSize;
	intV_pl iCount;
	intV_pl iMark;
	lint_pl lFilePos;
	intV_pl iBegin;
	AddresValue_pl  addresV;
	bool_pl bFileEnd;
	bool_pl bMarkLine;

	/*  if ((iMark & 1) == 1) Fill Value String
	 *  if ((iMark & 8) == 8) find end line char
	 *  if ((iMark & 2) == 2) Conver char
	 *  if ((iMark & 4) == 4) Begin Key String
	 *  if ((iMark & 16)==16) ID find end
	 * */
	ptrhAndle = NULL_PL;
	lFilePos = 0;
	do{
		intV_pl iCCount;
		if(ptrName==NULL_PL || iwNameLength<=0)
			break;
		//open cfg file
		hFile = PLSysAPI_SystemIO_fopen(ptrName,iwNameLength,PLSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_PL)
			break;
		//utf code mark byte size
		iBRSize = PLSysAPI_UTF16_CharSize2ByteSize(PLSysChar_Const_SysStringMarkSize);
		if(PLSysAPI_SystemIO_fread(hFile,pFileMark,iBRSize,1)!=iBRSize){
			PLSysAPI_SystemIO_fclose(hFile);
			break;
		}
		//Test file utf code mark is systemchar mark
		if(PLSysAPI_UTF16_StrCmp(pFileMark,PSysStringIOMark,PLSysChar_Const_SysStringMarkSize)==false_pl){
			PLSysAPI_SystemIO_fclose(hFile);
			break;
		}
		//set current file pointer posltion
		lFilePos = iBRSize;
		//allocate
		iCacheLineSize = PLSys_Const_CPUCacheLineSize;
		iStSize    = PL_CompilerAllocSize(PL_FileCfgHeader);
		iAllocSize = PLSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrhAndle  = (PL_FileCfgHeader *)PLSysAPI_AllocateMemory(iAllocSize);
		PLSysAPI_MemoryClearZero((void_pl *)ptrhAndle,iAllocSize);
		if(ptrhAndle==NULL_PL){
			PLSysAPI_SystemIO_fclose(hFile);
			break;
		}
		addresV = (AddresValue_pl)ptrhAndle;
		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
		((PL_FileCfgHeader *)(addresV))->ptrMem = (void_pl *)ptrhAndle;
		ptrhAndle = (PL_FileCfgHeader *)addresV;
		ptrhAndle->hFile = hFile;
		ptrhAndle->cbSize = iStSize;
		ptrhAndle->eCharCode = PLSys_Const_Unicode16;
		ptrhAndle->iLableAMount = 0;
		ptrCfgTable = &(ptrhAndle->Tables);
		ptrPrvCfgTable = NULL_PL;
		iReadSize = 0;
		iMark     = 0;
		bFileEnd = false_pl;
		//if don't read file end enter while
		while(bFileEnd==false_pl){
			//clear Text Data Buffer
			PLSysAPI_UTF16_ClearString(pRData,PLSysIO_Const_TextLineMaxLength);
			//byte size of Text Data Buffer
			iBRSize = PLSysAPI_UTF16_CharSize2ByteSize(PLSysIO_Const_TextLineMaxLength);
			iReadSize = PLSysAPI_SystemIO_fread(hFile,pRData,1,iBRSize);
			//Data Buffer equle SystemChar Count
			iCCount = PLSysAPI_SysByte2CharUnit(iReadSize);
			if(iReadSize<=0){
				if((iReadSize<0) || (PLSysAPI_SystemIO_feof(hFile)==0))
					break;
				iReadSize = PLSysAPI_SysStringSize(pRData);
				bFileEnd = true_pl;
			}
			bMarkLine = true_pl;
			iBegin = 0;

			for(iCount = 0;iCount<iCCount;iCount++){
				//Conver Char State
				if((iMark & 2) == 2){
					iMark &= (~2);
					//if Conver Char is EnterChar is Leave State and continue while ,if Conver Char is NewLineChar is continue while
					if((pRData[iCount] == PLCfg_ConstChar_EnterChar) || (pRData[iCount] == PLCfg_ConstChar_NewLineChar)){
						if(pRData[iCount] == PLCfg_ConstChar_EnterChar)
							iMark |= 2;
						continue;
					}
					if(bMarkLine == true_pl){
						if((iMark & 1) == 1){
							if(iTableSize>=PLCfg_Const_LableNameMaxSize){
								bMarkLine = false_pl;
								continue;
							}
							pTable[iTableSize] = pRData[iCount];
							iTableSize++;
							if(iTableSize>=PLCfg_Const_LableNameMaxSize){
								bMarkLine = false_pl;
							}
						}else{
							bMarkLine = false_pl;
						}
					}
				}else{
					if(bMarkLine == false_pl){
						if(pRData[iCount]==PLCfg_ConstChar_NewLineChar){
							bMarkLine = true_pl;
							iBegin = iCount + 1;
							if((iMark & 4) == 4){
								iMark &= (~4);
								if(ptrCfgTable->iLableCount>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount - 1] = lFilePos + PLSysAPI_SysCharAllocSize()*(iCount + 1);
								}
							}
							iMark = 0;
						}else if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
							iMark |= 2;
						}
					}else{
						if((iMark & 1) == 1){
							if(pRData[iCount] != PLCfg_ConstChar_EndTableChar){
								if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
									iMark |= 2;
									continue;
								}else if((pRData[iCount] == PLCfg_ConstChar_EnterChar) || (pRData[iCount] == PLCfg_ConstChar_NewLineChar)){
									bMarkLine = false_pl;
									iCount--;
									continue;
								}else if((pRData[iCount]==PLCfg_ConstChar_BlankChar) || (pRData[iCount]==PLCfg_ConstChar_TabChar)){
									bMarkLine = false_pl;
									continue;
								}
								pTable[iTableSize] = pRData[iCount];
								iTableSize++;
								if(iTableSize>=PLCfg_Const_LableNameMaxSize){
									bMarkLine = false_pl;
								}
							}else{
								//iMark &= (~1);
								if(iTableSize>0){
									ptrCfgTable->lTablePos[ptrCfgTable->iLableCount] = lFilePos + PLSysAPI_UTF16_CharSize2ByteSize((iCount + 1));
									ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount] = ((~0) >> 1);
									if(ptrCfgTable->iLableCount>0){
										ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos + PLSysAPI_UTF16_CharSize2ByteSize(iBegin);
									}
									iMark |= 4;
									#if PLESystem_CharCodeUXX == PLEngineSysChar_Unicode16
										PLSysAPI_SysStringCpy((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),pTable,iTableSize);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] = iTableSize;
									#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode8
										intV_pl iConverDataPos;
										intV_pl iConverSize;
										intV_pl iConverBSize;
										uintV_pl uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
										PLSysAPI_SysIO_UTF16toUTF8((const_pl UTF16char_pl *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize, \
												PLSysAPI_UTF8_CharSize2ByteSize(PLCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  PLSysAPI_UTF8_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											PLSysAPI_UTF8_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),PLCfg_Const_LableNameMaxSize);
										}
									#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode32
										intV_pl iConverDataPos;
										intV_pl iConverSize;
										intV_pl iConverBSize;
										uintV_pl uConverFlag;
										iConverDataPos = 0;
										iConverSize = 0;
										iConverBSize = 0;
										uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
										PLSysAPI_SysIO_UTF16toUTF32((const_pl UTF16char_pl *)pTable,iTableSize,&iConverDataPos, \
												(&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),&iConverSize,&iConverBSize,  \
												PLSysAPI_UTF32_CharSize2ByteSize(PLCfg_Const_LableNameMaxSize),&uConverFlag);
										ptrCfgTable->iTableSize[ptrCfgTable->iLableCount] =  PLSysAPI_UTF32_Byte2CharUnit(iConverBSize);
										if(ptrCfgTable->iTableSize[ptrCfgTable->iLableCount]<=0){
											PLSysAPI_UTF32_ClearString((&(ptrCfgTable->pTableN[ptrCfgTable->iLableCount][0])),PLCfg_Const_LableNameMaxSize);
										}
									#endif
									(ptrCfgTable->iLableCount)++;
									(ptrhAndle->iLableAMount)++;
									if(ptrCfgTable->iLableCount>=PLCfg_Const_LableMaxCount){
										iStSize    = PL_Sizeof(PL_FileCfgTable);
										ptrCfgTable->ptrNext  = (PL_FileCfgTable *)PLSysAPI_AllocateMemory(iStSize);
										if(ptrCfgTable->ptrNext==NULL_PL){
											goto _jmp_pl_endCfgRead;
										}
										ptrPrvCfgTable = ptrCfgTable;
										ptrCfgTable = ptrPrvCfgTable->ptrNext;
										PLSysAPI_MemoryClearZero((void_pl *)ptrCfgTable,iStSize);
									}
								}
								bMarkLine = false_pl;
							}
						}else{
							if((pRData[iCount]==PLCfg_ConstChar_BlankChar) || (pRData[iCount]==PLCfg_ConstChar_TabChar)){
								continue;
							}
							if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
								iMark |= 2;
							}
							else if(pRData[iCount] != PLCfg_ConstChar_BeginTableChar){
								bMarkLine = false_pl;
								iCount--;
							}else{
								iMark |= 1;
								iTableSize = 0;
							}
						}
					}
				}
			}
			lFilePos += (PLSysAPI_UTF16_CharSize2ByteSize(iCount));
			if((bFileEnd == true_pl) && (ptrCfgTable->iLableCount>0)){
				ptrCfgTable->lTableEndPos[ptrCfgTable->iLableCount - 1] = lFilePos;
			}
		}
	}while(0);
_jmp_pl_endCfgRead:
	return ptrhAndle;
}
int_pl __PLSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(PL_FileCfgHeader * ptrFileHeader, const_pl UTF16char_pl * ptrID,intV_pl iwIDSize,UTF16char_pl * ptrValue,intV_pl iwMaxSize,lint_pl lLength){
	UTF16char_pl pRData[PLSysIO_Const_TextLineMaxLength];
	intV_pl iReadSize;
	intV_pl iBRSize;
	intV_pl iIDBSize;
	intV_pl iValueSize;
	intV_pl iMark;
	intV_pl iCount;
	intV_pl iCCount;
	iValueSize = 0;
	iMark = 0;
	iBRSize = PLSysAPI_UTF16_CharSize2ByteSize(PLSysIO_Const_TextLineMaxLength);
	if(lLength > iBRSize){
		lLength -= iBRSize;
	}else{
		iBRSize = lLength;
		lLength = 0;
	}
	iIDBSize = 0;
	iValueSize = 0;
	/*  if ((iMark & 1) == 1) Fill Value String
	 *  if ((iMark & 8) == 8) find end line char
	 *  if ((iMark & 2) == 2) Conver char
	 *  if ((iMark & 4) == 4) Begin Key String
	 *  if ((iMark & 16)==16) ID find end
	 * */
	while((iBRSize>0) && ((iReadSize = PLSysAPI_SystemIO_fread(ptrFileHeader->hFile,pRData,1,iBRSize))>0)){
		iCCount = PLSysAPI_UTF16_Byte2CharUnit(iReadSize);
		for(iCount=0; iCount < iCCount;iCount++){
			if((iMark & 2) == 2){
				iMark &= (~2);
				if((pRData[iCount] == PLCfg_ConstChar_EnterChar) || (pRData[iCount] == PLCfg_ConstChar_NewLineChar)){
					if(pRData[iCount] == PLCfg_ConstChar_EnterChar)
						iMark |= 2;
					continue;
				}
				if((iMark & 8) == 8)
					continue;
				if((iMark & 1) == 1){
					if((iMark & 4) != 4){
						iValueSize = 0;
						return iValueSize;
					}else{
						if(iValueSize>=iwMaxSize)
							return iValueSize;
						ptrValue[iValueSize] = pRData[iCount];
						iValueSize++;
					}
				}else{
					if((iMark & 16) == 16){
						iMark |= 8;
					}else if((iMark & 4)!=4){
						iMark |= 4;
						iCount--;
					}else{
						if((iIDBSize>=iwIDSize) || (pRData[iCount]!=ptrID[iIDBSize])){
							iMark |= 8;
						}else{
							iIDBSize++;
						}
					}
				}
			}else{
				if((iMark & 8) == 8){
					if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
						iMark |= 2;
					}else if(pRData[iCount] == PLCfg_ConstChar_NewLineChar){
						iMark = 0;
						iIDBSize = 0;
					}
				}else if((iMark & 1) == 1){
					if((iMark & 4)!=4){
						if((pRData[iCount]==PLCfg_ConstChar_BlankChar) || (pRData[iCount]==PLCfg_ConstChar_TabChar)){
							continue;
						}
						if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if(pRData[iCount] == PLCfg_ConstChar_ScopeLimitChar){
							iMark |= 4;
						}else{
							iValueSize = 0;
							return iValueSize;
						}
					}else{
						if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if(pRData[iCount] == PLCfg_ConstChar_ScopeLimitChar){
							return iValueSize;
						}else if((pRData[iCount] == PLCfg_ConstChar_EnterChar) || (pRData[iCount] == PLCfg_ConstChar_NewLineChar)){
							iValueSize = 0;
							return iValueSize;
						}else{
							if(iValueSize>=iwMaxSize){
								return iValueSize;
							}
							ptrValue[iValueSize] = pRData[iCount];
							iValueSize++;
						}
					}
				}else{
					if((iMark & 16) == 16){
						if((pRData[iCount]==PLCfg_ConstChar_BlankChar) || (pRData[iCount]==PLCfg_ConstChar_TabChar)){

						}else if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if(pRData[iCount] == PLCfg_ConstChar_EvaluateChar){
							iMark = 1;
						}else{
							iMark |= 8;
						}
					}else if((iMark & 4) != 4){
						if((pRData[iCount]==PLCfg_ConstChar_BlankChar) || (pRData[iCount]==PLCfg_ConstChar_TabChar)){
							continue;
						}
						if((pRData[iCount] == PLCfg_ConstChar_EnterChar) || (pRData[iCount] == PLCfg_ConstChar_NewLineChar)){
							iMark |= 8;
							iCount--;
						}else if(pRData[iCount] == PLCfg_ConstChar_EvaluateChar){
							iMark |= 8;
						}else if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else{
							iMark |= 4;
							iCount--;
						}
					}else{
						if(pRData[iCount] == PLCfg_ConstChar_ConverChar){
							iMark |= 2;
						}else if((pRData[iCount]==PLCfg_ConstChar_BlankChar) || (pRData[iCount]==PLCfg_ConstChar_TabChar)){
							if(iIDBSize == iwIDSize){
								iMark |= 16;
							}else{
								iMark |= 8;
							}
						}else if(pRData[iCount] == PLCfg_ConstChar_EvaluateChar){
							if(iIDBSize == iwIDSize){
								iMark = 1;
							}else{
								iMark |= 8;
							}
						}else if((pRData[iCount]==PLCfg_ConstChar_EnterChar) || (pRData[iCount]==PLCfg_ConstChar_NewLineChar)){
							iMark |= 8;
							iCount--;
						}else{
							if((ptrID[iIDBSize] == pRData[iCount]) && (iIDBSize<iwIDSize)){
								iIDBSize++;
							}else{
								iMark |= 8;
							}
						}
					}
				}
			}
		}
		iBRSize = PLSysAPI_UTF16_CharSize2ByteSize(PLSysIO_Const_TextLineMaxLength);
		if(lLength > iBRSize){
			lLength -= iBRSize;
		}else{
			iBRSize = lLength;
			lLength = 0;
		}
	}
	return iValueSize;
}
intV_pl __PLSysAPI_Sys_GetCfgFiletoString__Unicode16(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize,UTF16char_pl * ptrString,intV_pl iwMaxSize){
	intV_pl iwDataSize;
	intV_pl iCount;
	lint_pl lLength;
	PL_FileCfgHeader * ptrFileHeader;
	PL_FileCfgTable  * ptrCfgTable;
	ptrFileHeader = (PL_FileCfgHeader *)hAndle;
	iwDataSize = 0;
	ptrCfgTable = &(ptrFileHeader->Tables);
	while(ptrCfgTable!=NULL_PL){
		for(iCount = 0;iCount<ptrCfgTable->iLableCount;iCount++){
			if((iwLabelNSize == ptrCfgTable->iTableSize[iCount]) && (iwLabelNSize!=0) && (PLSysAPI_SysStringCmp(ptrLabelN,&(ptrCfgTable->pTableN[iCount][0]),iwLabelNSize) == true_pl)){
				PLSysAPI_SystemIO_fseek(ptrFileHeader->hFile,ptrCfgTable->lTablePos[iCount],PLSys_Const_SystemIO_Seek_Set);
				if(ptrCfgTable->lTableEndPos[iCount] > ptrCfgTable->lTablePos[iCount]){
					lLength = ptrCfgTable->lTableEndPos[iCount] - ptrCfgTable->lTablePos[iCount];
					#if PLESystem_CharCodeUXX == PLEngineSysChar_Unicode8
						UTF16char_pl pConvID[PLCfg_Const_IDNameMaxSize];
						intV_pl iConverDataPos;
						intV_pl iConverSize;
						intV_pl iConverBSize;
						uintV_pl uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
						PLSysAPI_UTF16_ClearString(pConvID,PLCfg_Const_IDNameMaxSize);
						PLSysAPI_SysIO_UTF8toUTF16((const_pl UTF8char_pl *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,PLSysAPI_UTF16_CharSize2ByteSize(PLCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = PLSysAPI_UTF16_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iwDataSize = __PLSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							PLSysAPI_UTF16_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode16
						iwDataSize = __PLSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(ptrFileHeader,ptrID,iwIDSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							PLSysAPI_UTF16_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#elif PLESystem_CharCodeUXX == PLEngineSysChar_Unicode32
						UTF16char_pl pConvID[PLCfg_Const_IDNameMaxSize];
						intV_pl iConverDataPos;
						intV_pl iConverSize;
						intV_pl iConverBSize;
						uintV_pl uConverFlag;
						iConverDataPos = 0;
						iConverSize = 0;
						iConverBSize = 0;
						uConverFlag = PLSysIO_Const_UnicodeMark_SmallEnd;
						PLSysAPI_UTF16_ClearString(pConvID,PLCfg_Const_IDNameMaxSize);

						PLSysAPI_SysIO_UTF32toUTF16((const_pl UTF32char_pl *)ptrID,iwIDSize,&iConverDataPos, \
								pConvID,&iConverSize,&iConverBSize,PLSysAPI_UTF16_CharSize2ByteSize(PLCfg_Const_IDNameMaxSize), \
								&uConverFlag);
						iConverSize = PLSysAPI_UTF16_Byte2CharUnit(iConverBSize);
						if(iConverSize<=0){
							break;
						}
						iwDataSize = __PLSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(ptrFileHeader,pConvID,iConverSize,ptrString,iwMaxSize,lLength);
						if((iwMaxSize - iwDataSize) > 0){
							PLSysAPI_UTF16_ClearString(&(ptrString[iwDataSize]),(iwMaxSize - iwDataSize));
						}
					#endif
				}
				break;
			}
		}
		ptrCfgTable = ptrCfgTable->ptrNext;
	}

	return iwDataSize;
}
int_pl __PLSysAPI_Sys_GetCfgFiletoInt__Unicode16(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize){
	UTF16char_pl pValue[64];
	intV_pl  iwValueSize;
	intV_pl  iValue;
	iValue = 0;
	PLSysAPI_UTF16_ClearString(pValue,64);
	iwValueSize = __PLSysAPI_Sys_GetCfgFiletoString__Unicode16(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		iValue = PLSysAPI_TypeConverUTF16_atoi(pValue,iwValueSize);
	}
	return iValue;
}
float_pl __PLSysAPI_Sys_GetCfgFiletoFloat__Unicode16(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize){
	UTF16char_pl pValue[64];
	intV_pl  iwValueSize;
	float_pl fValue;
	fValue = _FL_(0.0);
	PLSysAPI_UTF16_ClearString(pValue,64);
	iwValueSize = __PLSysAPI_Sys_GetCfgFiletoString__Unicode16(hAndle,ptrLabelN,iwLabelNSize,ptrID,iwIDSize,pValue,63);
	if(iwValueSize>0){
		fValue = PLSysAPI_TypeConverUTF16_atof(pValue,iwValueSize);
	}
	return fValue;
}
HPL_Result __PLSysAPI_Sys_CloseCfgFile__Unicode16(PLFileCFGHandle hAndle){
	PL_FileCfgHeader * ptrhAndle;
	PL_FileCfgTable  * ptrCfgTable;
	PL_FileCfgTable  * ptrFreeCfgTable;
	ptrhAndle = (PL_FileCfgHeader *)hAndle;
	if(ptrhAndle==NULL_PL)
		return HPLResult_Fail;
	PLSysAPI_SystemIO_fclose(ptrhAndle->hFile);
	ptrCfgTable = &(ptrhAndle->Tables);
	ptrCfgTable = ptrCfgTable->ptrNext;
	while(ptrCfgTable!=NULL_PL){
		ptrFreeCfgTable = ptrCfgTable;
		ptrCfgTable = ptrFreeCfgTable->ptrNext;
		PLSysAPI_FreeMemory((void_pl *)ptrFreeCfgTable);
	}
	PLSysAPI_FreeMemory(ptrhAndle->ptrMem);
	return HPLResult_OK;
}

PLConstCharTableHandle 	__PLSysAPI_Sys_OpenConstCharTable__Unicode8(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength){
	PL_EngineConstCharTable * ptrTable;
	PL_FileConstCharResource  FileHeader;
	AddresValue_pl  addresV;
	FILEStream * hFile;
	intV_pl iAllocSize;
	intV_pl iStSize;
	intV_pl iCacheLineSize;
	int32_pl iConstCharCount;
	uchar_pl pRData[PLSysIO_Const_TextLineMaxLength];
	intV_pl  iReadSize;
	intV_pl  iCount;
	lint_pl  lDataPos;
	intV_pl  iDataPos;
	intV_pl  iDataSize;
	intV_pl  iLineSize;
	intV_pl  iMaxCount;
	intV_pl  iACount;

	ptrTable = NULL_PL;
	hFile = NULL_PL;
	iCacheLineSize = PLSys_Const_CPUCacheLineSize;
	do{
		iConstCharCount = 0;
		lDataPos = 0;
		hFile = PLSysAPI_SystemIO_fopen(ptrName,iwNameLength,PLSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_PL)
			break;
		iReadSize = PL_CompilerAllocSize(PL_FileConstCharResource);
		if((PLSysAPI_SystemIO_fread(hFile,(void_pl *)(&FileHeader),iReadSize,1)!=iReadSize) || (FileHeader.uFileMark!=PLSys_ConstChar_FileHeaderMark)
				|| (FileHeader.iCount<=0))
			break;
		lDataPos = iReadSize;
		iDataPos = iReadSize;
		iDataSize = 0;

		iStSize    = PL_CompilerAllocSize(PL_EngineConstCharTable) + PL_CompilerAllocSize(PL_EngineConstCharResource) * (FileHeader.iCount - 1);
		iAllocSize = PLSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (PL_EngineConstCharTable *)PLSysAPI_AllocateMemory(iAllocSize);
		if(ptrTable == NULL_PL)
			break;
		PLSysAPI_MemoryClearZero((void_pl *)ptrTable,iAllocSize);
		addresV = (AddresValue_pl)ptrTable;
		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
		((PL_EngineConstCharTable *)addresV)->ptrMem = ptrTable;
		ptrTable = (PL_EngineConstCharTable *)addresV;
		ptrTable->icbSize	 = iStSize;
		ptrTable->iMaxCount  = FileHeader.iCount;
		iMaxCount = FileHeader.iCount;
		iACount   = 0;
		PLSysAPI_MemoryClearZero(pRData,PLSysIO_Const_TextLineMaxLength);
		iLineSize = 0;
		while((iReadSize = PLSysAPI_SystemIO_fread(hFile,(void_pl *)(&pRData),1,PLSysIO_Const_TextLineMaxLength))>0){
			for(iCount = 0; iCount<iReadSize ;iCount++){
				if(pRData[iCount] == 0x00){
					ptrTable->pTable[iACount].BSize.iUTF8Size = iLineSize;
					ptrTable->pTable[iACount]._Pointer.ptrUTF8Resource = (uchar_pl *)(iDataSize + iCount - iLineSize);
					iLineSize = 0;
					iACount++;
					if(iACount>=iMaxCount){
						iDataSize+=iCount;
						break;
					}
				}else{
					iLineSize++;
				}
			}
			if(iCount>=iReadSize){
				iDataSize+=iReadSize;
				PLSysAPI_MemoryClearZero(pRData,PLSysIO_Const_TextLineMaxLength);
			}
		}
		if(iACount<iMaxCount){
			for(iCount = 0; iCount<iReadSize ;iCount++){
				if(pRData[iCount] == 0x00){
					ptrTable->pTable[iACount].BSize.iUTF8Size = iLineSize;
					ptrTable->pTable[iACount]._Pointer.ptrUTF8Resource = (uchar_pl *)(iDataSize + iCount - iLineSize);
					iLineSize = 0;
					iACount++;
					if(iACount>=iMaxCount){
						iDataSize+=iCount;
						break;
					}
				}else{
					iLineSize++;
				}
			}
		}
		ptrTable->iCount = iACount;
		ptrTable->ptrConstCharData = NULL_PL;
		ptrTable->ptrConstCharMem  = NULL_PL;
		if((iACount>0) && (iDataSize>0)){
			iAllocSize = PLSysAPI_Alignment(iDataSize,iCacheLineSize) + iCacheLineSize;
			ptrTable->ptrConstCharMem  = PLSysAPI_AllocateMemory(iAllocSize);
			if(ptrTable->ptrConstCharMem == NULL_PL)
				break;
			addresV = (AddresValue_pl)(ptrTable->ptrConstCharMem);
			ptrTable->ptrConstCharData = (void_pl *)PLSysAPI_Alignment(addresV,iCacheLineSize);
			PLSysAPI_SystemIO_fseek(hFile,lDataPos,PLSys_Const_SystemIO_Seek_Set);
			if(PLSysAPI_SystemIO_fread(hFile,ptrTable->ptrConstCharData,iDataSize,1)!=iDataSize){
				PLSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
				ptrTable->ptrConstCharData = NULL_PL;
				ptrTable->ptrConstCharMem  = NULL_PL;
				break;
			}
			addresV = (AddresValue_pl)(ptrTable->ptrConstCharData);
			for(iCount = 0; iCount < iACount ;iCount++){
				ptrTable->pTable[iCount]._Pointer.ptrUTF8Resource  = (UTF8char_pl *)(((AddresValue_pl)ptrTable->pTable[iCount]._Pointer.Addres) + addresV);
			}
		}
	}while(0);
	if(hFile!=NULL_PL){
		PLSysAPI_SystemIO_fclose(hFile);
		hFile = NULL_PL;
	}
	return (PLConstCharTableHandle)ptrTable;
}
UTF8char_pl * __PLSysAPI_Sys_GetConstCharID__Unicode8(PLConstCharTableHandle hAndle,intV_pl iIndex,intV_pl * ptrIDSize){
	UTF8char_pl * ptrResource;
	PL_EngineConstCharTable * ptrTable;
	ptrResource = NULL_PL;
	ptrTable = (PL_EngineConstCharTable *)hAndle;
	do{
		if((ptrTable == NULL_PL) || (ptrIDSize == NULL_PL) || (ptrTable->ptrConstCharData == NULL_PL))
			break;
		if(ptrTable->iCount <= iIndex)
			break;
		ptrResource  = ptrTable->pTable[iIndex]._Pointer.ptrUTF8Resource;
		(*ptrIDSize) = ptrTable->pTable[iIndex].BSize.iUTF8Size;
	}while(0);
	return ptrResource;
}
void_pl __PLSysAPI_Sys_ReleaseConstCharTable__Unicode8(PLConstCharTableHandle hAndle){
	PL_EngineConstCharTable * ptrTable;
	ptrTable = (PL_EngineConstCharTable *)hAndle;
	if(ptrTable==NULL_PL)
		return;
	if(ptrTable->ptrConstCharMem!=NULL_PL && ptrTable->ptrConstCharData!=NULL_PL){
		PLSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
	}
	ptrTable->ptrConstCharData = NULL_PL;
	ptrTable->ptrConstCharMem  = NULL_PL;
	if(ptrTable->ptrMem!=NULL_PL)
		PLSysAPI_FreeMemory(ptrTable->ptrMem);
}
PLConstCharTableHandle __PLSysAPI_Sys_OpenConstCharTable__Unicode16(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength){
	PL_EngineConstCharTable * ptrTable;
	PL_FileConstCharResource  FileHeader;
	AddresValue_pl  addresV;
	FILEStream * hFile;
	intV_pl iAllocSize;
	intV_pl iStSize;
	intV_pl iCacheLineSize;
	int32_pl iConstCharCount;
	UTF16char_pl pRData[PLSysIO_Const_TextLineMaxLength];
	intV_pl  iReadSize;
	intV_pl  iCount;
	lint_pl  lDataPos;
	intV_pl iDataSize;
	intV_pl  iwLineSize;
	intV_pl  iMaxCount;
	intV_pl  iACount;
	intV_pl  iRTextLineSize;
	intV_pl  iEcBDataPos;
	intV_pl  iAEcCount;
	intV_pl  iSigleCharSize;
	ptrTable = NULL_PL;
	hFile = NULL_PL;
	iCacheLineSize = PLSys_Const_CPUCacheLineSize;
	do{
		iConstCharCount = 0;
		lDataPos = 0;
		hFile = PLSysAPI_SystemIO_fopen(ptrName,iwNameLength,PLSysIO_Const_FOpenOperat_ReadBin);
		if(hFile==NULL_PL)
			break;
		iReadSize = PL_CompilerAllocSize(PL_FileConstCharResource);
		//test file format ID
		if((PLSysAPI_SystemIO_fread(hFile,(void_pl *)(&FileHeader),iReadSize,1)!=iReadSize) || (FileHeader.uFileMark!=PLSys_ConstChar_FileHeaderMark)
				|| (FileHeader.iCount<=0))
			break;
		lDataPos = iReadSize;
		iDataSize = 0;
		//allocate memory for what the const table of file
		iStSize    = PL_CompilerAllocSize(PL_EngineConstCharTable) + PL_CompilerAllocSize(PL_EngineConstCharResource) * (FileHeader.iCount - 1);
		iAllocSize = PLSysAPI_Alignment(iStSize,iCacheLineSize) + iCacheLineSize;
		ptrTable   = (PL_EngineConstCharTable *)PLSysAPI_AllocateMemory(iAllocSize);
		if(ptrTable == NULL_PL)
			break;
		PLSysAPI_MemoryClearZero((void_pl *)ptrTable,iAllocSize);
		addresV = (AddresValue_pl)ptrTable;
		addresV = PLSysAPI_Alignment(addresV,iCacheLineSize);
		((PL_EngineConstCharTable *)addresV)->ptrMem = ptrTable;
		ptrTable = (PL_EngineConstCharTable *)addresV;
		ptrTable->icbSize	 = iStSize;
		ptrTable->iMaxCount  = FileHeader.iCount;
		iMaxCount = FileHeader.iCount;
		PLSysAPI_SystemIO_fseek(hFile,FileHeader.lFillDataSize,PLSys_Const_SystemIO_Seek_CUR);
		lDataPos += FileHeader.lFillDataSize;
		iACount   = 0;
		//clear read buffer
		PLSysAPI_UTF16_ClearString(pRData,PLSysIO_Const_TextLineMaxLength);
		iwLineSize = 0;
		iSigleCharSize = PLSysAPI_UTF16_CharByteSize;
		//Text buffer byte size
		iRTextLineSize = PLSysIO_Const_TextLineMaxLength * iSigleCharSize;
		ptrTable->pTable[0].BSize.iUTF16Size = 0;
		ptrTable->pTable[0]._Pointer.ptrUTF16Resource = 0;
		iEcBDataPos = 0;
		iDataSize = 0;
		//Test every one item of const char is 'UTFSyschar_pl' Count
		while((iReadSize = PLSysAPI_SystemIO_fread(hFile,(void_pl *)(&(pRData[iEcBDataPos])),1,iRTextLineSize))>0){
			iReadSize += iEcBDataPos;
			iEcBDataPos = 0;
			iAEcCount = PLSysAPI_UTF16_Byte2CharUnit(iReadSize);
			for(iCount = 0; iCount<iAEcCount;iCount++){
				if(pRData[iCount] == 0){
					ptrTable->pTable[iACount].BSize.iUTF16Size = iwLineSize;
					//add buffer offset
					iEcBDataPos += iSigleCharSize;
					//Find a item
					iACount++;
					if(iACount>=iMaxCount){
						iDataSize+=iEcBDataPos;
						goto __OCCharTable_EncodeComplete;
					}
					//next item
					ptrTable->pTable[iACount].BSize.iUTF16Size = 0;
					ptrTable->pTable[iACount]._Pointer.Addres = (AddresValue_pl)(iDataSize + iEcBDataPos);
					iwLineSize = 0;
				}else{
					iwLineSize++;
					iEcBDataPos += iSigleCharSize;
				}
			}
			if(iEcBDataPos>=iReadSize){
				iDataSize+=iReadSize;
				iEcBDataPos = 0;
			}else{
				iDataSize+=iEcBDataPos;
				PLSysAPI_MemoryCpy(pRData,&(pRData[iEcBDataPos]),(iReadSize - iEcBDataPos));
				iEcBDataPos = iReadSize - iEcBDataPos;
			}
		}
		if(iACount<iMaxCount){
			for(iCount = iACount;iCount < iMaxCount;iCount++){
				ptrTable->pTable[iCount].BSize.iUTF16Size = 0;
				ptrTable->pTable[iCount]._Pointer.ptrUTF16Resource = NULL_PL;
			}
		}
	__OCCharTable_EncodeComplete:
		ptrTable->iCount = iACount;
		ptrTable->ptrConstCharData = NULL_PL;
		ptrTable->ptrConstCharMem  = NULL_PL;
		if((iACount>0) && (iDataSize>0)){
			iAllocSize = PLSysAPI_Alignment(iDataSize,iCacheLineSize) + iCacheLineSize;
			ptrTable->ptrConstCharMem  = PLSysAPI_AllocateMemory(iAllocSize);
			if(ptrTable->ptrConstCharMem == NULL_PL)
				break;
			addresV = (AddresValue_pl)(ptrTable->ptrConstCharMem);
			ptrTable->ptrConstCharData = (void_pl *)PLSysAPI_Alignment(addresV,iCacheLineSize);
			lDataPos += FileHeader.lFillDataSize;
			//go to the table of const char
			PLSysAPI_SystemIO_fseek(hFile,lDataPos,PLSys_Const_SystemIO_Seek_Set);
			//read the table of const char  to memory
			if(PLSysAPI_SystemIO_fread(hFile,ptrTable->ptrConstCharData,iDataSize,1)!=iDataSize){
				PLSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
				ptrTable->ptrConstCharData = NULL_PL;
				ptrTable->ptrConstCharMem  = NULL_PL;
				break;
			}
			//get the table of const char memory begin addres
			addresV = (AddresValue_pl)(ptrTable->ptrConstCharData);
			//calculate every one item of const char memory addres
			for(iCount = 0; iCount < iACount ;iCount++){
				ptrTable->pTable[iCount]._Pointer.ptrUTF16Resource = (UTF16char_pl *)(((AddresValue_pl)(ptrTable->pTable[iCount]._Pointer.ptrUTF16Resource )) + addresV);
			}
		}
	}while(0);
	if(hFile!=NULL_PL){
		PLSysAPI_SystemIO_fclose(hFile);
		hFile = NULL_PL;
	}
	return (PLConstCharTableHandle)ptrTable;
}
UTF16char_pl * __PLSysAPI_Sys_GetConstCharID__Unicode16(PLConstCharTableHandle hAndle, intV_pl iIndex,intV_pl * ptrIDSize){
	UTF16char_pl * ptrResource;
	PL_EngineConstCharTable * ptrTable;

	ptrResource = NULL_PL;
	ptrTable = (PL_EngineConstCharTable *)hAndle;
	do{
		if((ptrTable->ptrConstCharData == NULL_PL) || (ptrTable->iCount <= iIndex))
			break;
		ptrResource  = ptrTable->pTable[iIndex]._Pointer.ptrUTF16Resource;
		(*ptrIDSize) = ptrTable->pTable[iIndex].BSize.iUTF16Size;
	}while(0);
	return ptrResource;
}
void_pl __PLSysAPI_Sys_ReleaseConstCharTable__Unicode16(PLConstCharTableHandle hAndle){
	PL_EngineConstCharTable * ptrTable;
	ptrTable = (PL_EngineConstCharTable *)hAndle;
	if(ptrTable==NULL_PL)
		return;
	if(ptrTable->ptrConstCharMem!=NULL_PL && ptrTable->ptrConstCharData!=NULL_PL){
		PLSysAPI_FreeMemory(ptrTable->ptrConstCharMem);
	}
	ptrTable->ptrConstCharData = NULL_PL;
	ptrTable->ptrConstCharMem  = NULL_PL;
	if(ptrTable->ptrMem!=NULL_PL){
		PLSysAPI_FreeMemory(ptrTable->ptrMem);
	}
}

