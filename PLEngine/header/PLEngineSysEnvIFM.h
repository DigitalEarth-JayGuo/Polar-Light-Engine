/*
 * PLEngineSysEnvIFM.h
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "PLEngineH.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineSysAPI.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#include "PLEngineI.h"
#include "PLEngineSysIO.h"
#ifndef PLENGINESYSENVIFM_H_
#define PLENGINESYSENVIFM_H_
	#define PLCfg_ConstChar_ConverChar 			PLWChar_SlashHL
	#define PLCfg_ConstChar_BeginTableChar 		PLWChar_MBracketL
	#define PLCfg_ConstChar_EndTableChar 		PLWChar_MBracketR
	#define PLCfg_ConstChar_EvaluateChar 		PLWChar_Equal
	#define PLCfg_ConstChar_ScopeLimitChar 		PLWChar_DbQuotation
	#define PLCfg_ConstChar_NewLineChar 		PLWChar_NewLine
	#define PLCfg_ConstChar_EnterChar   		PLWChar_SoftEnter
	#define PLCfg_ConstChar_TabChar     		PLWChar_Tab
	#define PLCfg_ConstChar_BlankChar			PLWChar_Blank

	_PLE_lib_c _CallStack_default_ int_pl   PLSysAPI_Sys_GetProcessNumber();
	_PLE_lib_c _CallStack_default_ lint_pl  PLSysAPI_Sys_GetPhysPagesNumber();
	_PLE_lib_c _CallStack_default_ intV_pl  PLSysAPI_Sys_GetPhysPageSize();


	_CallStack_default_ HPL_Result __PLSysAPI_Sys_GetOperatSystemEnv__Private(PL_OperatSysEnvSet * ptrEnv);
	_CallStack_default_ HPL_Result __PLSysAPI_Sys_GetConstSystemInfo__Private(PL_ConstSystemInfo * ptrInfo);

	_PLE_lib_c _CallStack_default_ HPL_Result 					PLSysAPI_Sys_GetOperatSystemInfo(PL_OperatSystemInfo * ptrInfo);
	_PLE_lib_c _CallStack_default_ PL_OperatSysEnvSet * 		PLSysAPI_Sys_GetOperatSystemEnv(HPPLEngine hAndle);
	_PLE_lib_c _CallStack_default_ PL_ConstSystemInfo * 		PLSysAPI_Sys_GetConstSystemInfo(HPPLEngine hAndle);
	_PLE_lib_c _CallStack_default_ PLConstCharTableHandle 		PLSysAPI_Sys_GetEngineConstCharTable(HPPLEngine hAndle);
	_PLE_lib_c _CallStack_default_ lint_pl     					PLSysAPI_Sys_GetSpaceMemory();
	_PLE_lib_c _CallStack_default_ intV_pl     					PLSysAPI_Sys_GetCPUCacheShareUnit();
	_PLE_lib_c _CallStack_default_ intV_pl     					PLSysAPI_Sys_GetSysAllocMemoryGrain();

	_PLE_lib_c _CallStack_default_ HPPLEngine  					PLSysAPI_Sys_GetGlobalEngineHandle();


	//Config file must is file of utf8
	_PLE_lib_c _CallStack_default_ PLFileCFGHandle 			__PLSysAPI_Sys_OpenCfgFile_Unicode8(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength);
	_CallStack_default_            intV_pl	       			__PLSysAPI_Sys_GetCfgFileAttValue__Unicode8__Private(PL_FileCfgHeader * ptrFileHeader,const_pl UTF8char_pl * ptrID,intV_pl iIDSize,UTF8char_pl * ptrValue,intV_pl iMaxSize,lint_pl iLength);
	_PLE_lib_c _CallStack_default_ intV_pl 	      			__PLSysAPI_Sys_GetCfgFiletoString_Unicode8(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize,UTF8char_pl * ptrString,intV_pl iMaxSize);
	_PLE_lib_c _CallStack_default_ intV_pl 		  			__PLSysAPI_Sys_GetCfgFiletoInt__Unicode8(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize);
	_PLE_lib_c _CallStack_default_ float_pl        			__PLSysAPI_Sys_GetCfgFiletoFloat__Unicode8(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize);
	_PLE_lib_c _CallStack_default_ HPL_Result      			__PLSysAPI_Sys_CloseCfgFile__Unicode8(PLFileCFGHandle hAndle);
	//Config file must is file of utf16 small end
	_PLE_lib_c _CallStack_default_ PLFileCFGHandle 			__PLSysAPI_Sys_OpenCfgFile__Unicode16(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength);
	_CallStack_default_            intV_pl	       			__PLSysAPI_Sys_GetCfgFileAttValue__Unicode16__Private(PL_FileCfgHeader * ptrFileHeader,const_pl UTF16char_pl * ptrID,intV_pl iwIDSize,UTF16char_pl * ptrValue,intV_pl iwMaxSize,lint_pl iLength);
	_PLE_lib_c _CallStack_default_ intV_pl 	      			__PLSysAPI_Sys_GetCfgFiletoString__Unicode16(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize,UTF16char_pl * ptrString,intV_pl iwMaxSize);
	_PLE_lib_c _CallStack_default_ intV_pl 		  			__PLSysAPI_Sys_GetCfgFiletoInt__Unicode16(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize);
	_PLE_lib_c _CallStack_default_ float_pl        			__PLSysAPI_Sys_GetCfgFiletoFloat__Unicode16(PLFileCFGHandle hAndle,const_pl UTFSyschar_pl * ptrLabelN,intV_pl iwLabelNSize,const_pl UTFSyschar_pl * ptrID,intV_pl iwIDSize);
	_PLE_lib_c _CallStack_default_ HPL_Result      			__PLSysAPI_Sys_CloseCfgFile__Unicode16(PLFileCFGHandle hAndle);

	//Const Char must is file of utf8
	_PLE_lib_c _CallStack_default_ PLConstCharTableHandle 	__PLSysAPI_Sys_OpenConstCharTable__Unicode8(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength);
	_PLE_lib_c _CallStack_default_ UTF8char_pl *           	__PLSysAPI_Sys_GetConstCharID__Unicode8(PLConstCharTableHandle hAndle,intV_pl iIndex,intV_pl * ptrIDSize);
	_PLE_lib_c _CallStack_default_ void_pl      		  	__PLSysAPI_Sys_ReleaseConstCharTable__Unicode8(PLConstCharTableHandle hAndle);
	// Const Char must is file of utf16 small end
	_PLE_lib_c _CallStack_default_ PLConstCharTableHandle 	__PLSysAPI_Sys_OpenConstCharTable__Unicode16(const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength);
	_PLE_lib_c _CallStack_default_ UTF16char_pl *          	__PLSysAPI_Sys_GetConstCharID__Unicode16(PLConstCharTableHandle hAndle,intV_pl iIndex,intV_pl * ptrIDSize);
	_PLE_lib_c _CallStack_default_ void_pl      		  	__PLSysAPI_Sys_ReleaseConstCharTable__Unicode16(PLConstCharTableHandle hAndle);
	_PLE_lib_c _CallStack_default_ intV_pl 					PLSysAPI_Sys_GetLastError();

	//_PLE_lib_c _CallStack_default_
	#define PLSys_Const_CPUCacheLineSize    					PLSysAPI_Sys_GetCPUCacheShareUnit()
	#define PLSys_Const_SysAllocMemGrain    					PLSysAPI_Sys_GetSysAllocMemoryGrain()
	#define PLSysAPI_Sys_CopyConstSystemInfo(ptrDest,ptrSrc) 	PLSysAPI_MemoryCpy(ptrDest,ptrSrc,PL_CompilerAllocSize(PL_ConstSystemInfo))
	#define PLSysAPI_Sys_CopyOperatSystemEnv(ptrDest,ptrSrc) 	PLSysAPI_MemoryCpy(ptrDest,ptrSrc,PL_CompilerAllocSize(PL_OperatSysEnvSet))
	#define PLSysAPI_Sys_CopyOperatSystemInfo(ptrDest,ptrSrc) 	PLSysAPI_MemoryCpy(ptrDest,ptrSrc,PL_CompilerAllocSize(PL_OperatSystemInfo))


	#define PLSysAPI_Sys_OpenCfgFileUTF8 				__PLSysAPI_Sys_OpenCfgFile__Unicode8
	#define PLSysAPI_Sys_GetCfgFiletoStringUTF8 		__PLSysAPI_Sys_GetCfgFiletoString__Unicode8
	#define PLSysAPI_Sys_GetCfgFiletoIntUTF8			__PLSysAPI_Sys_GetCfgFiletoInt__Unicode8
	#define PLSysAPI_Sys_GetCfgFiletoFloatUTF8			__PLSysAPI_Sys_GetCfgFiletoFloat__Unicode8
	#define PLSysAPI_Sys_CloseCfgFileUTF8				__PLSysAPI_Sys_CloseCfgFile__Unicode8

	#define PLSysAPI_Sys_OpenCfgFileUTF16 				__PLSysAPI_Sys_OpenCfgFile__Unicode16
	#define PLSysAPI_Sys_GetCfgFiletoStringUTF16 		__PLSysAPI_Sys_GetCfgFiletoString__Unicode16
	#define PLSysAPI_Sys_GetCfgFiletoIntUTF16			__PLSysAPI_Sys_GetCfgFiletoInt__Unicode16
	#define PLSysAPI_Sys_GetCfgFiletoFloatUTF16			__PLSysAPI_Sys_GetCfgFiletoFloat__Unicode16
	#define PLSysAPI_Sys_CloseCfgFileUTF16				__PLSysAPI_Sys_CloseCfgFile__Unicode16


	#define PLSysAPI_Sys_OpenCfgFile 				PLSysAPI_Sys_OpenCfgFileUTF16
	#define PLSysAPI_Sys_GetCfgFiletoString 		PLSysAPI_Sys_GetCfgFiletoStringUTF16
	#define PLSysAPI_Sys_GetCfgFiletoInt			PLSysAPI_Sys_GetCfgFiletoIntUTF16
	#define PLSysAPI_Sys_GetCfgFiletoFloat			PLSysAPI_Sys_GetCfgFiletoFloatUTF16
	#define PLSysAPI_Sys_CloseCfgFile				PLSysAPI_Sys_CloseCfgFileUTF16

	#define PLSysAPI_Sys_OpenConstCharTable			__PLSysAPI_Sys_OpenConstCharTable__Unicode16
	#define PLSysAPI_Sys_GetConstCharID				__PLSysAPI_Sys_GetConstCharID__Unicode16
	#define PLSysAPI_Sys_ReleaseConstCharTable		__PLSysAPI_Sys_ReleaseConstCharTable__Unicode16


#endif /* PLENGINESYSENVIFM_H_ */
