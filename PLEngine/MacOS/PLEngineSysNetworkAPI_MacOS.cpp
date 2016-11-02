/*
 * PLEngineSysNetworkAPI_MacOS.cpp
 *
 *  Created on: 2009-11-19
 *      Author: Administrator
 */
#include "../header/MacOS/PLEngineSysNetworkAPI_MacOS.h"
#if PLOperat_System == PLOperatSystem_MacOS
	HPL_Result __PLSysAPI_Net_InitializeNetEnviron(HPPLEngine hEngine){
		PL_EngineState * ptrState;
		ptrState = (PL_EngineState *)hEngine;
		if(ptrState == NULL_PL)
			return HPLResult_Fail;
		if(ptrState->bNetworkInitialize == true_pl)
			return HPLResult_OK;
		ptrState->bNetworkInitialize = true_pl;
		return HPLResult_OK;
	}
	bool_pl	  __PLSysAPI_Net_CompleteInitialize(HPPLEngine hEngine){
		PL_EngineState * ptrState;
		ptrState = (PL_EngineState *)hEngine;
		if(ptrState == NULL_PL)
			return false_pl;
		return ptrState->bNetworkInitialize;
	}
	void_pl	  __PLSysAPI_Net_DestroyNetEnviron(HPPLEngine hEngine){
		PL_EngineState * ptrState;
		ptrState = (PL_EngineState *)hEngine;
		if(ptrState == NULL_PL)
			return;
		if(ptrState->bNetworkInitialize == false_pl)
			return;
		ptrState->bNetworkInitialize = false_pl;
	}
	HPLSocket  __PLSysAPI_Net_CreateSocket(PL_NetAddressFamilyStyle eAFStyle,PL_NetSocketType eType,intV_pl iProtocol){
		HPLSocket hSK;
		int iaf;
		int itype;
		iaf   = _native_Net_ConverAddressFamilyStyle(eAFStyle);
		itype = _native_Net_ConverSocketType(eType);
		if((iaf == -1) || (itype == -1))
			return Invalid_PLSocket;
		hSK = socket(iaf,itype,iProtocol);
		return hSK;
	}

	HPL_Result __PLSysAPI_Net_BindSocket(HPLSocket hSK,HSockAddres hAddr){
		HPL_Result hResult;
		PL_SockAddress * ptrSKAddress;
		socklen_t tLen;

		ptrSKAddress = (PL_SockAddress *)hAddr;
		hResult = HPLResult_Fail;
		if((hSK == Invalid_PLSocket) || (ptrSKAddress == NULL_PL)){
			return hResult;
		}
		if(ptrSKAddress->eAFStyle == PLSysNet_Const_AF_Unkonw){
			return hResult;
		}
		tLen = (socklen_t)ptrSKAddress->iSysAddrSize;
		if(::bind(hSK,(const struct sockaddr*)(&(ptrSKAddress->sysaddr)),tLen) != 0){
			hResult = HPLResult_OK;
		}else{

		}
		return hResult;
	}

	HPL_Result __PLSysAPI_Net_ConnectSocket(HPLSocket hSK,HSockAddres hAddr){
		HPL_Result hResult;
		PL_SockAddress * ptrSKAddress;
		socklen_t tLen;


		ptrSKAddress = (PL_SockAddress *)hAddr;
		hResult = HPLResult_Fail;
		if((hSK == Invalid_PLSocket) || (ptrSKAddress == NULL_PL)){
			return hResult;
		}
		if(ptrSKAddress->eAFStyle == PLSysNet_Const_AF_Unkonw){
			return hResult;
		}
		tLen = (socklen_t)ptrSKAddress->iSysAddrSize;
		if(::connect(hSK,(const_pl struct sockaddr *)(&(ptrSKAddress->sysaddr)),tLen) != 0){
			hResult = HPLResult_OK;
		}else{

		}
		return hResult;
	}
	HPL_Result 	__PLSysAPI_Net_AcceptSocket(HPLSocket & hClientSK,HPLSocket hSK,HSockAddres hAddr){
		HPL_Result hResult;
		PL_SockAddress * ptrSKAddress;
		socklen_t tLen;

		hClientSK = Invalid_PLSocket;
		ptrSKAddress = (PL_SockAddress *)hAddr;
		hResult = HPLResult_Fail;
		if((hSK == Invalid_PLSocket) || (ptrSKAddress == NULL_PL))
			return hResult;
		hClientSK = ::accept(hSK,(struct sockaddr *)(&(ptrSKAddress->sysaddr)),&tLen);
		if(hClientSK != Invalid_PLSocket){
			hResult = HPLResult_OK;
			ptrSKAddress->iSysAddrSize = (intV_pl)tLen;
		}else{
			hResult = HPLResult_Fail;
		}
		return hResult;
	}

	HPL_Result   __PLSysAPI_Net_SendSocket(HPLSocket hSK,const_pl char_pl * ptrData,intV_pl iDataSize,PL_MsgSocketMode eMode,intV_pl * ptrSDataSize){
		HPL_Result hResult;
		int iFlags;
		int iSendSize;
		int ierron;
		hResult = HPLResult_Fail;
		iFlags = 0;
		if(eMode != PLSysNet_Const_MsgMode_Normal)
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		iSendSize = ::send(hSK,ptrData,(int)iDataSize,iFlags);
		ierron = errno;
		if(iSendSize != 0){
			if(ptrSDataSize != NULL_PL){
				(*ptrSDataSize) = iSendSize;
			}
			hResult = HPLResult_OK;
		}else{

		}
		return hResult;
	}
	HPL_Result   __PLSysAPI_Net_RecvSocket(HPLSocket hSK,char_pl * ptrRData,intV_pl iMaxSize,PL_MsgSocketMode eMode,intV_pl * ptrRSize){
		HPL_Result hResult;
		int iFlags;
		int iRecvSize;
		int ierron;
		hResult = HPLResult_Fail;
		iFlags = 0;
		if(eMode != PLSysNet_Const_MsgMode_Normal){
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		}
		iRecvSize = ::recv(hSK,ptrRData,iMaxSize,iFlags);
		ierron = errno;
		if(iRecvSize != 0){
			if(ptrRSize != NULL_PL){
				(*ptrRSize) = iRecvSize;
			}
			hResult = HPLResult_OK;
		}else{

		}
		return hResult;
	}
	HPL_Result   __PLSysAPI_Net_SendMsgSocket(HPLSocket hSK,HSockAddres hAddr,const_pl char_pl * ptrData,intV_pl iDataSize,PL_MsgSocketMode eMode,intV_pl * ptrSDataSize){
		HPL_Result hResult;
		PL_SockAddress * ptrSKAddress;
		socklen_t tLen;
		int iFlags;
		int iSendSize;
		int ierron;
		hResult = HPLResult_Fail;
		iFlags  = 0;
		ptrSKAddress = (PL_SockAddress *)hAddr;
		if(eMode != PLSysNet_Const_MsgMode_Normal){
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		}
		if((ptrSKAddress == NULL_PL) || (ptrSKAddress->eAFStyle == PLSysNet_Const_AF_Unkonw))
			return hResult;
		tLen = (socklen_t)(ptrSKAddress->iSysAddrSize);
		iSendSize = ::sendto(hSK,ptrData,iDataSize,iFlags,(const_pl struct sockaddr *)(&(ptrSKAddress->sysaddr)),tLen);
		ierron = errno;
		if(iSendSize != 0){
			hResult = HPLResult_OK;
			if(ptrSDataSize!=NULL_PL)
				(*ptrSDataSize) = iSendSize;
		}else{
			//hResult = HPLResult_Fail;
		}
		return hResult;
	}
	HPL_Result   __PLSysAPI_Net_RecvMsgSocket(HPLSocket hSK,HSockAddres hAddr,char_pl * ptrRData,intV_pl iMaxSize,PL_MsgSocketMode eMode,intV_pl * ptrRDataSize){
		HPL_Result hResult;
		PL_SockAddress * ptrSKAddress;
		int_pl iFlags;
		int_pl iRecvSize;
		socklen_t tLen;
		int ierron;

		hResult = HPLResult_Fail;
		iFlags = 0;
		ptrSKAddress = (PL_SockAddress *)hAddr;
		if(eMode != PLSysNet_Const_MsgMode_Normal){
			iFlags = (int)_native_Net_ConverMsgMode(eMode);
		}
		if((ptrSKAddress == NULL_PL) || (ptrSKAddress->eAFStyle == PLSysNet_Const_AF_Unkonw))
			return hResult;
		iRecvSize = ::recvfrom(hSK,ptrRData,iMaxSize,iFlags,(struct sockaddr *)(&(ptrSKAddress->sysaddr)),&tLen);
		ierron = errno;
		if(iRecvSize != 0){
			ptrSKAddress->iSysAddrSize = (intV_pl)tLen;
			ptrSKAddress->eAFStyle = _native_Net_UnConverAddressFamilyStyle((intV_pl)(ptrSKAddress->sysaddr.addrIPV4.sin_family));
		}else{
			ptrSKAddress->eAFStyle = PLSysNet_Const_AF_Unkonw;
			//hResult = HPLResult_Fail;
		}
		return hResult;
	}


	HPL_Result __PLSysAPI_Net_ListenSocket(HPLSocket hSK,intV_pl iMaxConnectSize){
		HPL_Result hResult;
		if(::listen(hSK,(int_pl)iMaxConnectSize)==0){
			hResult = HPLResult_OK;
		}else{
			hResult = HPLResult_Fail;
		}
		return hResult;
	}
	void_pl    __PLSysAPI_Net_CloseSocket(HPLSocket hsk){
		if(hsk == Invalid_PLSocket)
			return;
		::close(hsk);
	}
	HPL_Result   __PLSysAPI_Net_SetSocketOperate_Bool(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,bool_pl bEnable){
		HPL_Result hResult;
		BOOL_pl    bValue;
		intV_pl iType;
		intV_pl iOperMode;
		intV_pl iError;
		socklen_t tLen;

		hResult = HPLResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if(HResulPL_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_pl){
			return hResult;
		}
		bValue = ((bEnable == true_pl) ? TRUE_pl : FALSE_pl);
		tLen = PL_CompilerAllocSize(BOOL_pl);
		iError = ::setsockopt(hSK,iOperMode,iType,(const_pl char_pl *)(&bValue),tLen);
		if(iError == 0){
			hResult = HPLResult_OK;
		}else{
			hResult = HPLResult_Fail;
//			switch(PLSysAPI_Sys_GetNetLastError()){
//			case :
//				break;
//			default:
//				break;
//			}
		}
		return hResult;
	}
	HPL_Result   __PLSysAPI_Net_SetSocketOperate_Integer(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,intV_pl iValue){
		HPL_Result hResult;
		intV_pl iType;
		intV_pl iOperMode;
		intV_pl iError;
		socklen_t tLen;

		hResult = HPLResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if(HResulPL_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_pl){
			return hResult;
		}
		tLen = PL_CompilerAllocSize(int_pl);
		iError = ::setsockopt(hSK,iOperMode,iType,(const_pl char_pl *)(&iValue),tLen);
		if(iError == 0){
			hResult = HPLResult_OK;
		}else{
			hResult = HPLResult_Fail;
		}
		return hResult;
	}
	HPL_Result   __PLSysAPI_Net_SetSocketOperate_ULong(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,luint_pl iValue){
		HPL_Result 		hResult;
		struct linger 	lg;
		uintV_pl    	iVBitSize;
		luint_pl    	uMark;
		intV_pl 		iError;
		intV_pl iType;
		intV_pl iOperMode;
		socklen_t tLen;

		hResult = HPLResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if(HResulPL_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_pl){
			return hResult;
		}
		iVBitSize = PL_CompilerAllocSize(luint_pl)<<3;
		iVBitSize = iVBitSize >> 1;
		uMark = (1<<iVBitSize) - 1;
		PLSysAPI_MemoryClearZero(&lg,PL_CompilerAllocSize(linger));
		lg.l_onoff = iValue & uMark;
		lg.l_linger= ((iValue >> iVBitSize) & uMark);
		tLen = PL_CompilerAllocSize(linger);
		iError = ::setsockopt(hSK,iOperMode,iType,(const_pl char_pl *)(&lg),tLen);
		if(iError == 0){
			hResult = HPLResult_OK;
		}else{
			hResult = HPLResult_Fail;
		}
		return hResult;
	}

	HPL_Result __PLSysAPI_Net_GetSocketOperate_Bool(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,bool_pl * ptrbEnable){
		HPL_Result hResult;
		intV_pl iType;
		intV_pl iOperMode;
		intV_pl iError;
		BOOL_pl bValue;
		intV_pl iSize;
		socklen_t tLen;

		hResult = HPLResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if((ptrbEnable == NULL_PL) || (HResulPL_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_pl)){
			return hResult;
		}
		iError = ::getsockopt(hSK,iOperMode,iType,(char_pl *)(&bValue),&tLen);
		iSize = (intV_pl)tLen;
		if(iError == 0){
			hResult = HPLResult_OK;
			(*ptrbEnable) = ((bValue == TRUE_pl) ?  true_pl: false_pl);
		}else{
			(*ptrbEnable) = false_pl;
		}
		return hResult;
	}
	HPL_Result __PLSysAPI_Net_GetSocketOperate_Integer(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,intV_pl * ptriValue){
		HPL_Result hResult;
		intV_pl iType;
		intV_pl iOperMode;
		intV_pl iError;
		intV_pl iSize;
		socklen_t tLen;

		hResult = HPLResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if((ptriValue == NULL_PL) || (HResulPL_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_pl)){
			return hResult;
		}
		iError = ::getsockopt(hSK,iOperMode,iType,(char_pl *)ptriValue,&tLen);
		iSize = (intV_pl)tLen;
		if(iError == (-1)){
			hResult = HPLResult_OK;
		}else{
			(*ptriValue) = -1;
		}

		return hResult;
	}
	HPL_Result __PLSysAPI_Net_GetSocketOperate_ULong(HPLSocket hSK,intV_pl iMode,intV_pl iOperType,luint_pl * ptriValue){
		HPL_Result hResult;
		intV_pl iType;
		intV_pl iOperMode;
		intV_pl iError;
		luint_pl    	uMark;
		struct linger 	lg;
		uintV_pl    	iVBitSize;
		intV_pl 		iSize;
		socklen_t tLen;

		hResult = HPLResult_Fail;
		iOperMode = iMode;
		iType = iOperType;
		if((ptriValue == NULL_PL) || (HResulPL_FAILED(_native_Net_ConverSOOptType(iOperMode,iType)) == true_pl)){
			return hResult;
		}
		PLSysAPI_MemoryClearZero(&lg,PL_CompilerAllocSize(linger));
		iError = ::getsockopt(hSK,iOperMode,iType,(char_pl *)(&lg),&tLen);
		iSize = (intV_pl)tLen;
		if(iError == 0){
			iVBitSize = PL_CompilerAllocSize(luint_pl)<<3;
			iVBitSize = iVBitSize >> 1;
			uMark = (1<<iVBitSize) - 1;
			(*ptriValue) = lg.l_onoff & uMark;
			(*ptriValue) = (*ptriValue) << iVBitSize;
			(*ptriValue) += (lg.l_linger & uMark);
			hResult = HPLResult_OK;
		}else{
			(*ptriValue) = -1;
		}
		return hResult;
	}

	HPL_Result 	__PLSysAPI_Net_SetSockBlockMode(HPLSocket hSK){
		HPL_Result hResult;
		intV_pl    iError;
		intV_pl    iFlags;
		hResult = HPLResult_Fail;
		if(hSK == Invalid_PLSocket){
			return hResult;
		}
		iError = ::fcntl(hSK,F_GETFL,0);
		if(iError == (-1)){
			return hResult;
		}
		iFlags = iError;
		iFlags &= (~O_NONBLOCK);
		iError = ::fcntl(hSK,F_SETFL,iFlags);
		if(iError != (-1)){
			hResult = HPLResult_OK;
		}else{

		}
		return hResult;
	}
	HPL_Result 	__PLSysAPI_Net_SetSockNoBlockMode(HPLSocket hSK){
		HPL_Result hResult;
		intV_pl    iError;
		intV_pl    iFlags;
		hResult = HPLResult_Fail;
		if(hSK == Invalid_PLSocket){
			return hResult;
		}
		iError = ::fcntl(hSK,F_GETFL,0);
		if(iError == (-1)){
			return hResult;
		}
		iFlags = iError;
		iFlags |= O_NONBLOCK;
		iError = ::fcntl(hSK,F_SETFL,iFlags);
		if(iError != (-1)){
			hResult = HPLResult_OK;
		}else{

		}
		return hResult;
	}



	HPL_Result  __PLSysAPI_Net_ConverSockAddres(HSockAddres hSA,PL_SocketDepict * ptrDepict){
		HPL_Result hResult;
		PL_SockAddress * ptrSKAddress;
		int_pl iAF;

		hResult = HPLResult_Fail;
		ptrSKAddress = (PL_SockAddress *)hSA;
		if((ptrSKAddress == NULL_PL) || (ptrDepict == NULL_PL)){
			return hResult;
		}
		iAF = _native_Net_ConverAddressFamilyStyle(ptrDepict->eAFStyle);
		if(iAF == -1){
			return hResult;
		}
		if(HResulPL_FAILED(__PLSysAPI_Net_RestSockAddresToEmpty((HSockAddres)ptrSKAddress)) == true_pl){
			return hResult;
		}
		switch(ptrDepict->eAFStyle){
		case PLSysNet_Const_AF_eINET:{
				ptrSKAddress->eAFStyle 						= ptrDepict->eAFStyle;
				ptrSKAddress->sysaddr.addrIPV4.sin_family	= iAF;
				ptrSKAddress->sysaddr.addrIPV4.sin_port		= ptrDepict->uPort;
				ptrSKAddress->iSysAddrSize     				= PL_CompilerAllocSize(sockaddr_in);
				PLSysAPI_MemoryCpy((void_pl *)(&(ptrSKAddress->sysaddr.addrIPV4.sin_addr.s_addr)),ptrDepict->addres._addr_u8,PL_CompilerAllocSize(in_addr));
			}break;
		case PLSysNet_Const_AF_eINET6:{
				ptrSKAddress->eAFStyle						= ptrDepict->eAFStyle;
				ptrSKAddress->sysaddr.addrIPV6.sin6_family  = _native_Net_ConverAddressFamilyStyle(ptrSKAddress->eAFStyle);
				ptrSKAddress->sysaddr.addrIPV6.sin6_port	= ptrDepict->uPort;
				ptrSKAddress->iSysAddrSize 					= PL_CompilerAllocSize(sockaddr_in6);
				PLSysAPI_MemoryCpy((void_pl *)(&(ptrSKAddress->sysaddr.addrIPV6.sin6_addr.__in6_u.__u6_addr8)),ptrDepict->addres._addr_u8,PL_CompilerAllocSize(in6_addr));
			}break;
		default:

			break;
		}

		return hResult;
	}

	intV_pl 	__PLSysAPI_Net_GetHostName(HPLSocket hSK,char_pl * ptrName,intV_pl iNMaxSize){
		return 0;
	}


	intV_pl _native_Net_ConverMsgMode(PL_MsgSocketMode eMode){
		if(eMode == PLSysNet_Const_MsgMode_Normal)
			return 0;
		if(eMode == PLSysNet_Const_MsgMode_DONTROUTE){
			return MSG_DONTROUTE;
		}
		return 0;
	}
	HPL_Result _native_Net_ConverSOOptType(intV_pl & iMode,intV_pl & iOperType){
		HPL_Result hResult;
		hResult = HPLResult_OK;
		if(iMode == PLSysNet_Const_OperMode_Socket){

		}else if(iMode == PLSysNet_Const_OperMode_IPPROTO_IP){

		}else if(iMode == PLSysNet_Const_OperMode_IPPROTO_IPV6){

		}else if(iMode == PLSysNet_Const_OperMode_IPPROTO_TCP){

		}else if(iMode == PLSysNet_Const_OperMode_IPPROTO_UDP){

		}else if(iMode == PLSysNet_Const_OperMode_IPPROTO_IGMP){

		}else if(iMode == PLSysNet_Const_OperMode_IPPROTO_IGMPV6){

		}else{
			hResult = HPLResult_Fail;
		}
		return hResult;
	}

#endif
