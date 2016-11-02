/*
 * PLEngineSysIOAPI_MacOS.cpp
 *
 *  Created on: 2009-7-15
 *      Author: DevLinux
 */
#include "../header/MacOS/PLEngineSysIOAPI_MacOS.h"
#if PLOperat_System == PLOperatSystem_MacOS
	HPL_Result __PLSysAPI_SystemIO_Create_(PLDeviceHandle * ptrhAndle,const_pl char_pl * ptrName,intV_pl iNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Open_(PLDeviceHandle * ptrhAndle,const_pl char_pl * ptrName,intV_pl iNSize,uintV_pl uFlag,uint_pl uMode,void_pl * pSt){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Read_(PLDeviceHandle hAndle,void_pl * ptrBData ,intV_pl iBSize,intV_pl * ptrRSize,void_pl * pSt){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Write_(PLDeviceHandle hAndle,const_pl void_pl * ptrWData ,intV_pl iWSize,intV_pl * ptrWSize,void_pl * pSt){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Close_(PLDeviceHandle hAndle){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Access_(const_pl char_pl * ptrName,intV_pl iNSize,uint_pl uMode){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Mkdir_(const_pl char_pl * ptrName,intV_pl iNSize,uint_pl uMode,void_pl * pSt){
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_Seek_(PLDeviceHandle hAndle,lint_pl iMov,lint_pl * ptrPos,ePL_SysIOSeekMode eMode,void_pl * pSt){
		return HPLResult_OK;
	}
	intV_pl   __PLSysAPI_SystemIO_GetCurWD_(char_pl * ptrCurWD,intV_pl iMaxLength){
		return 0;
	}
#endif
