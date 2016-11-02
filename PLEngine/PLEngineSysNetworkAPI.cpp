/*
 * PLEngineSysNetworkAPI.cpp
 *
 *  Created on: 2009-11-18
 *      Author: Administrator
 */

#include "header/PLEngineSysNetworkAPI.h"

	int_pl _native_Net_ConverAddressFamilyStyle(PL_NetAddressFamilyStyle eAFStyle){
		int iaf;
		iaf = -1;
		switch(eAFStyle){
		case PLSysNet_Const_AF_eINET:
			iaf = AF_INET;
			break;
		case PLSysNet_Const_AF_eINET6:
			iaf = AF_INET6;
			break;
		case PLSysNet_Const_AF_eUnix:
			iaf = AF_UNIX;
			break;
//		case PLSysNet_Const_AF_eISO:
//			iaf = AF_ISO;
//			break;
//		case PLSysNet_Const_AF_eNS:
//			iaf = AF_NS;
//			break;
		case PLSysNet_Const_AF_eIPX:
			iaf = AF_IPX;
			break;
		case PLSysNet_Const_AF_eIRDA:
			iaf = AF_IRDA;
			break;
		case PLSysNet_Const_AF_eAPPLETALK:
			iaf = AF_APPLETALK;
			break;
		case PLSysNet_Const_AF_Unkonw:
			iaf = -1;
		default:
			break;
		}
		return iaf;
	}
	PL_NetAddressFamilyStyle _native_Net_UnConverAddressFamilyStyle(int_pl iStyle){
		PL_NetAddressFamilyStyle eStyle;
		switch(iStyle){
		case AF_INET:
			eStyle = PLSysNet_Const_AF_eINET;
			break;
		case AF_INET6:
			eStyle = PLSysNet_Const_AF_eINET6;
			break;
		case AF_UNIX:
			eStyle = PLSysNet_Const_AF_eUnix;
			break;
//		case AF_ISO:
//			eStyle = PLSysNet_Const_AF_eISO;
//			break;
//		case AF_NS:
//			eStyle = PLSysNet_Const_AF_eNS;
//			break;
		case AF_IPX:
			eStyle = PLSysNet_Const_AF_eIPX;
			break;
		case AF_IRDA:
			eStyle = PLSysNet_Const_AF_eIRDA;
			break;
		case AF_APPLETALK:
			eStyle = PLSysNet_Const_AF_eAPPLETALK;
			break;
		default:
			eStyle = PLSysNet_Const_AF_Unkonw;
			break;
		}
		return eStyle;
	}

	int_pl _native_Net_ConverSocketType(PL_NetSocketType eType){
		int_pl itype;
		itype = -1;
		switch(eType){
		case PLSysNet_Const_Socket_Stream:
			itype = SOCK_STREAM;
			break;
		case PLSysNet_Const_Socket_RAW:
			itype = SOCK_RAW;
			break;
		case PLSysNet_Const_Socket_Dgram:
			itype = SOCK_DGRAM;
			break;
		case PLSysNet_Const_Socket_Seqpacket:
			itype = SOCK_SEQPACKET;
			break;
		case PLSysNet_Const_Socket_RDM:
			itype = SOCK_RDM;
			break;
		default:
			break;
		}
		return itype;
	}

	HSockAddres	__PLSysAPI_Net_CreateSockAddres(PL_SocketDepict * ptrDepict){
		HSockAddres hSA;
		PL_SockAddress * ptrSKAddress;
		int_pl iAF;
		hSA = NULL_PL;
		ptrSKAddress = NULL_PL;
		if(ptrDepict == NULL_PL)
			return hSA;
		iAF = _native_Net_ConverAddressFamilyStyle(ptrDepict->eAFStyle);
		if(iAF == -1)
			return hSA;
		hSA = __PLSysAPI_Net_CreateEmptySockAddres();
		if(hSA == NULL_PL)
			return NULL_PL;
		if(HResulPL_FAILED(__PLSysAPI_Net_ConverSockAddres(hSA,ptrDepict)) == true_pl){
			__PLSysAPI_Net_DestroySockAddres(hSA);
			hSA = NULL_PL;
		}
		return hSA;
	}
	HSockAddres  __PLSysAPI_Net_CreateEmptySockAddres(){
		PL_SockAddress * ptrSKAddress;
		ptrSKAddress =	(PL_SockAddress *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(PL_SockAddress));
		if(HResulPL_FAILED(__PLSysAPI_Net_RestSockAddresToEmpty(ptrSKAddress)) == true_pl){
			if(ptrSKAddress != NULL_PL){
				PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)ptrSKAddress);
				ptrSKAddress = NULL_PL;
			}
		}
		return (HSockAddres)ptrSKAddress;
	}
	HPL_Result	__PLSysAPI_Net_RestSockAddresToEmpty(HSockAddres hSA){
		PL_SockAddress * ptrSKAddress;
		ptrSKAddress = (PL_SockAddress *)hSA;
		if(ptrSKAddress == NULL_PL)
			return HPLResult_Fail;
		PLSysAPI_MemoryClearZero((void_pl *)ptrSKAddress,PL_CompilerAllocSize(PL_SockAddress));
		ptrSKAddress->eAFStyle = PLSysNet_Const_AF_Unkonw;
		return HPLResult_OK;
	}
	void_pl __PLSysAPI_Net_DestroySockAddres(HSockAddres hAddres){
		PL_SockAddres_Base * ptrSABase;
		if(hAddres == NULL_PL)
			return;
		ptrSABase = (PL_SockAddres_Base *)hAddres;
		PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrSABase);
	}
