/*
 * PLEngineSysNetworkAPI.h
 *
 *  Created on: 2009-11-18
 *      Author: Administrator
 */
#include "PLEngineH.h"
#include "PLEngineSysAPI.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#include "PLEngineMemoryPool.h"
#include "PLEngineSysSynchron.h"
#include "PLEngineSysProcess.h"
#include "PLEngineSysDataMacro.h"
#include "PLEngineSysEnvIFM.h"
#ifndef PLENGINESYSNETWORKAPI_H_
#define PLENGINESYSNETWORKAPI_H_



	_PLE_lib_c _CallStack_default_ HPL_Result 		__PLSysAPI_Net_InitializeNetEnviron(HPPLEngine hEngine);
	_PLE_lib_c _CallStack_default_ bool_pl	   		__PLSysAPI_Net_CompleteInitialize(HPPLEngine hEngine);
	_PLE_lib_c _CallStack_default_ void_pl	   		__PLSysAPI_Net_DestroyNetEnviron(HPPLEngine hEngine);
	_PLE_lib_c _CallStack_default_ HPLSocket  		__PLSysAPI_Net_CreateSocket(PL_NetAddressFamilyStyle eAFStyle,PL_NetSocketType eType,intV_pl iProtocol);
	_PLE_lib_c _CallStack_default_ HPL_Result 		__PLSysAPI_Net_BindSocket(HPLSocket hSK,HSockAddres hAddr);
	_PLE_lib_c _CallStack_default_ HPL_Result 		__PLSysAPI_Net_ConnectSocket(HPLSocket hSK,HSockAddres hAddr);
	_PLE_lib_c _CallStack_default_ HPL_Result 		__PLSysAPI_Net_ListenSocket(HPLSocket hSK,intV_pl iMaxConnectSize);
	_PLE_lib_c _CallStack_default_ HPL_Result 		__PLSysAPI_Net_AcceptSocket(HPLSocket & hClientSK,HPLSocket hSK,HSockAddres hAddr);
	_PLE_lib_c _CallStack_default_ HPL_Result   		__PLSysAPI_Net_SendSocket(HPLSocket hSK,const_pl char_pl * ptrData,intV_pl iDataSize,PL_MsgSocketMode eMode,intV_pl * ptrSDataSize);
	_PLE_lib_c _CallStack_default_ HPL_Result   		__PLSysAPI_Net_RecvSocket(HPLSocket hSK,char_pl * ptrRData,intV_pl iMaxSize,PL_MsgSocketMode eMode,intV_pl * ptrRSize);
	_PLE_lib_c _CallStack_default_ HPL_Result   		__PLSysAPI_Net_SendMsgSocket(HPLSocket hSK,HSockAddres hAddr,const_pl char_pl * ptrData,intV_pl iDataSize,PL_MsgSocketMode eMode,intV_pl * ptrSDataSize);
	_PLE_lib_c _CallStack_default_ HPL_Result   		__PLSysAPI_Net_RecvMsgSocket(HPLSocket hSK,HSockAddres hAddr,char_pl * ptrRData,intV_pl iMaxSize,PL_MsgSocketMode eMode,intV_pl * ptrRDataSize);
	_PLE_lib_c _CallStack_default_ HPL_Result 		__PLSysAPI_Net_SetSockBlockMode(HPLSocket hSK);
	_PLE_lib_c _CallStack_default_ HPL_Result 		__PLSysAPI_Net_SetSockNoBlockMode(HPLSocket hSK);

	_PLE_lib_c _CallStack_default_ HSockCollection  __PLSysAPI_Net_CreateSockCollection();
	_PLE_lib_c _CallStack_default_ HPL_Result      	__PLSysAPI_Net_AddSocketToCollection(HSockCollection hColl,HPLSocket hSK);
	_PLE_lib_c _CallStack_default_ HPL_Result       __PLSysAPI_Net_RemoveSocketForCollection(HSockCollection hColl,HPLSocket hSK);
	_PLE_lib_c _CallStack_default_ HPL_Result       __PLSysAPI_Net_ClearSocketForCollection(HSockCollection hColl);
	_PLE_lib_c _CallStack_default_ intV_pl          __PLSysAPI_Net_GetSockCollectionCurrentSize(HSockCollection hColl);
	_PLE_lib_c _CallStack_default_ intV_pl          __PLSysAPI_Net_GetSockCollectionMaxSize(HSockCollection hColl);
	_PLE_lib_c _CallStack_default_ void_pl          __PLSysAPI_Net_DestroyCollection(HSockCollection hColl);

	_PLE_lib_c _CallStack_default_ void_pl    	__PLSysAPI_Net_CloseSocket(HPLSocket hsk);

	_PLE_lib_c _CallStack_default_ HPL_Result   __PLSysAPI_Net_SetSocketOperate_Bool(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,bool_pl bEnable);
	_PLE_lib_c _CallStack_default_ HPL_Result   __PLSysAPI_Net_SetSocketOperate_Integer(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,intV_pl iValue);
	_PLE_lib_c _CallStack_default_ HPL_Result   __PLSysAPI_Net_SetSocketOperate_ULong(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,luint_pl iValue);
	_PLE_lib_c _CallStack_default_ HPL_Result   __PLSysAPI_Net_GetSocketOperate_Bool(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,bool_pl * ptrbEnable);
	_PLE_lib_c _CallStack_default_ HPL_Result   __PLSysAPI_Net_GetSocketOperate_Integer(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,intV_pl * ptriValue);
	_PLE_lib_c _CallStack_default_ HPL_Result   __PLSysAPI_Net_GetSocketOperate_ULong(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,luint_pl * ptriValue);

//	_PLE_lib_c _CallStack_default_ HPL_Result 	__PLSysAPI_Net_SetSocketPort(HPLSocket hSK,uintV_pl uPort);
//	_PLE_lib_c _CallStack_default_ uintV_pl   	__PLSysAPI_Net_GetSocketPort(HPLSocket hSK);
	_PLE_lib_c _CallStack_default_ intV_pl 	    __PLSysAPI_Net_GetHostName(HPLSocket hSK,char_pl * ptrName,intV_pl iNMaxSize);
//	_PLE_lib_c _CallStack_default_ intV_pl    	__PLSysAPI_Net_GetSocketBindIP(HPLSocket hSK,char_pl * ptrIPAddr,intV_pl iMaxSize);

	_PLE_lib_c _CallStack_default_ HSockAddres	__PLSysAPI_Net_CreateSockAddres(PL_SocketDepict * ptrDepict);
	_PLE_lib_c _CallStack_default_ HSockAddres  __PLSysAPI_Net_CreateEmptySockAddres();
	_PLE_lib_c _CallStack_default_ HPL_Result	__PLSysAPI_Net_RestSockAddresToEmpty(HSockAddres hSA);
	_PLE_lib_c _CallStack_default_ HPL_Result   __PLSysAPI_Net_ConverSockAddres(HSockAddres hSA,PL_SocketDepict * ptrDepict);
	_PLE_lib_c _CallStack_default_ void_pl      __PLSysAPI_Net_DestroySockAddres(HSockAddres hAddres);


//	_PLE_lib_c _CallStack_default_

	int_pl 					 _native_Net_ConverAddressFamilyStyle(PL_NetAddressFamilyStyle eAFStyle);
	PL_NetAddressFamilyStyle _native_Net_UnConverAddressFamilyStyle(int_pl iStyle);
	int_pl 					 _native_Net_ConverSocketType(PL_NetSocketType eType);
	intV_pl 				 _native_Net_ConverMsgMode(PL_MsgSocketMode eMode);
	HPL_Result 				 _native_Net_ConverSOOptType(intV_pl & iMode,intV_pl & iOperType);

	#define PLSysAPI_Net_InitializeNetEnviron 			__PLSysAPI_Net_InitializeNetEnviron
	#define PLSysAPI_Net_CompleteInitialize				__PLSysAPI_Net_CompleteInitialize
	#define PLSysAPI_Net_DestroyNetEnviron				__PLSysAPI_Net_DestroyNetEnviron
	#define PLSysAPI_Net_CreateSocket					__PLSysAPI_Net_CreateSocket
	#define PLSysAPI_Net_BindSocket						__PLSysAPI_Net_BindSocket
	#define PLSysAPI_Net_ConnectSocket					__PLSysAPI_Net_ConnectSocket
	#define PLSysAPI_Net_ListenSocket					__PLSysAPI_Net_ListenSocket
	#define PLSysAPI_Net_AcceptSocket					__PLSysAPI_Net_AcceptSocket
	#define PLSysAPI_Net_SendSocket						__PLSysAPI_Net_SendSocket
	#define PLSysAPI_Net_RecvSocket						__PLSysAPI_Net_RecvSocket
	#define PLSysAPI_Net_SendMsgSocket					__PLSysAPI_Net_SendMsgSocket
	#define PLSysAPI_Net_RecvMsgSocket					__PLSysAPI_Net_RecvMsgSocket
	#define PLSysAPI_Net_SetSockBlockMode				__PLSysAPI_Net_SetSockBlockMode
	#define PLSysAPI_Net_SetSockNoBlockMode				__PLSysAPI_Net_SetSockNoBlockMode
	#define PLSysAPI_Net_CloseSocket					__PLSysAPI_Net_CloseSocket

	#define PLSysAPI_Net_SetSocketOperate_Bool			__PLSysAPI_Net_SetSocketOperate_Bool
	#define PLSysAPI_Net_SetSocketOperate_Integer		__PLSysAPI_Net_SetSocketOperate_Integer
	#define PLSysAPI_Net_SetSocketOperate_Timer			__PLSysAPI_Net_SetSocketOperate_ULong
	#define PLSysAPI_Net_GetSocketOperate_Bool			__PLSysAPI_Net_GetSocketOperate_Bool
	#define PLSysAPI_Net_GetSocketOperate_Integer		__PLSysAPI_Net_GetSocketOperate_Integer
	#define PLSysAPI_Net_GetSocketOperate_Timer			__PLSysAPI_Net_GetSocketOperate_ULong

	#define PLSysAPI_Net_CreateSockAddres				__PLSysAPI_Net_CreateSockAddres
	#define PLSysAPI_Net_CreateEmptySockAddres			__PLSysAPI_Net_CreateEmptySockAddres
	#define PLSysAPI_Net_RestSockAddresToEmpty			__PLSysAPI_Net_RestSockAddresToEmpty
	#define PLSysAPI_Net_ConverSockAddres				__PLSysAPI_Net_ConverSockAddres
	#define PLSysAPI_Net_DestroySockAddres				__PLSysAPI_Net_DestroySockAddres



#if PLOperat_System == PLOperatSystem_Window
	#define PLSysAPI_Sys_GetNetLastError	WSAGetLastError
#elif PLOperat_System == PLOperatSystem_Linux
	#define PLSysAPI_Sys_GetNetLastError	PLSysAPI_Sys_GetLastError
#elif PLOperat_System == PLOperatSystem_Unix
	#define PLSysAPI_Sys_GetNetLastError	PLSysAPI_Sys_GetLastError
#elif PLOperat_System == PLOperatSystem_MacOS
	#define PLSysAPI_Sys_GetNetLastError	PLSysAPI_Sys_GetLastError
#endif


//


#endif /* PLENGINESYSNETWORKAPI_H_ */
