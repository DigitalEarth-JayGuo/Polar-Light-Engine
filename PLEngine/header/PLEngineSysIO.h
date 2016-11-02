/*
 * PLEngineSysIO.h
 *
 *  Created on: 2009-7-8
 *      Author: root
 */
#include "PLEngineBaseH.h"
#include "PLEngineSysAPI.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#include "PLEngineSysTextChar.h"
#ifndef PLENGINESYSIO_H_
#define PLENGINESYSIO_H_

	/*
	 * Mode  0~2 Creat User Access , 3 ~ 5 Group User Access , 6 ~ 8 Other User Access
	 * */
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Create_(PLDeviceHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Open_(PLDeviceHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Read_(PLDeviceHandle hAndle,void_pl * ptrBData ,intV_pl iBSize,intV_pl * ptrRSize,void_pl * pSt);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Write_(PLDeviceHandle hAndle,const_pl void_pl * ptrWData ,intV_pl iWSize,intV_pl * ptrWSize,void_pl * pSt);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Seek_(PLDeviceHandle hAndle,lint_pl iMov,lint_pl * ptrPos,ePL_SysIOSeekMode eMode,void_pl * pSt);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Close_(PLDeviceHandle hAndle);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Access_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uint_pl uMode);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_Mkdir_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,uint_pl uMode,void_pl * pSt);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_EnterFOperateLock(PLDeviceHandle hAndle);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_TryEnterFOperateLock(PLDeviceHandle hAndle);
	_PLE_lib_c _CallStack_default_ void_pl	  __PLSysAPI_SystemIO_LeaveFOperateLock(PLDeviceHandle hAndle);

	_PLE_lib_c _CallStack_default_ FILEStream * __PLSysAPI_SystemIO_fopen_(const_pl UTFSyschar_pl * ptrName,intV_pl iwNSize,intV_pl iMode);
	_PLE_lib_c _CallStack_default_ int_pl       __PLSysAPI_SystemIO_fread_(FILEStream * ptrStream,void_pl * ptrData,intV_pl iSize,intV_pl iRCount);
	_PLE_lib_c _CallStack_default_ int_pl       __PLSysAPI_SystemIO_fwrite_(FILEStream * ptrStream,const_pl void_pl * ptrData,intV_pl iSize,intV_pl iWCount);
	_PLE_lib_c _CallStack_default_ lint_pl      __PLSysAPI_SystemIO_fseek_(FILEStream * ptrStream,lint_pl iMov,ePL_SysIOSeekMode eMode);
	_PLE_lib_c _CallStack_default_ void_pl      __PLSysAPI_SystemIO_fclose_(FILEStream * ptrStream);
	_PLE_lib_c _CallStack_default_ void_pl      __PLSysAPI_SystemIO_fflush_(FILEStream * ptrStream);
	_PLE_lib_c _CallStack_default_ intV_pl      __PLSysAPI_SystemIO_feof_(FILEStream * ptrStream);
	_PLE_lib_c _CallStack_default_ lint_pl      __PLSysAPI_SystemIO_fGetFileCurPos_(FILEStream * ptrStream);
	_PLE_lib_c _CallStack_default_ intV_pl      __PLSysAPI_SystemIO_GetCurWD_(UTF16char_pl * ptrCurWD,int_pl iMaxLength);

	#define PLSysAPI_SystemIO_Create      						__PLSysAPI_SystemIO_Create_
	#define PLSysAPI_SystemIO_Open         						__PLSysAPI_SystemIO_Open_
	#define PLSysAPI_SystemIO_Read          					__PLSysAPI_SystemIO_Read_
	#define PLSysAPI_SystemIO_Write         					__PLSysAPI_SystemIO_Write_
	#define PLSysAPI_SystemIO_Seek          					__PLSysAPI_SystemIO_Seek_
	#define PLSysAPI_SystemIO_Close         					__PLSysAPI_SystemIO_Close_
	#define PLSysAPI_SystemIO_Access        					__PLSysAPI_SystemIO_Access_
	#define PLSysAPI_SystemIO_Mkdir         					__PLSysAPI_SystemIO_Mkdir_
	#define PLSysAPI_SystemIO_EnterFOperateLock					__PLSysAPI_SystemIO_EnterFOperateLock
	#define PLSysAPI_SystemIO_TryEnterFOperateLock     			__PLSysAPI_SystemIO_TryEnterFOperateLock
	#define PLSysAPI_SystemIO_LeaveFOperateLock        			__PLSysAPI_SystemIO_LeaveFOperateLock
	#define PLSysAPI_SystemIO_fopen             				__PLSysAPI_SystemIO_fopen_
	#define PLSysAPI_SystemIO_fread             				__PLSysAPI_SystemIO_fread_
	#define PLSysAPI_SystemIO_fwrite            				__PLSysAPI_SystemIO_fwrite_
	#define PLSysAPI_SystemIO_fseek             				__PLSysAPI_SystemIO_fseek_
	#define PLSysAPI_SystemIO_fclose            				__PLSysAPI_SystemIO_fclose_
	#define PLSysAPI_SystemIO_fflush            				__PLSysAPI_SystemIO_fflush_
	#define PLSysAPI_SystemIO_feof 	            				__PLSysAPI_SystemIO_feof_
	#define PLSysAPI_SystemIO_fGetFileCurPos    				__PLSysAPI_SystemIO_fGetFileCurPos_
	#define PLSysAPI_SystemIO_GetCurWD          				__PLSysAPI_SystemIO_GetCurWD_

#endif /* PLENGINESYSIO_H_ */
