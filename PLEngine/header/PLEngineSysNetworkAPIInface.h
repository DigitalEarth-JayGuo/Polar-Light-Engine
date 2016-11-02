/*
 * PLEngineSysNetworkAPIInface.h
 *
 *  Created on: 2009-11-18
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINESYSNETWORKAPIINFACE_H_
#define PLENGINESYSNETWORKAPIINFACE_H_
//	typedef socket HPLSocket;
	typedef enum _ePL_NetAddressFamilyStyle{
		PLSysNet_Const_AF_eINET 	 = 0,
		PLSysNet_Const_AF_eINET6	 = 1,
		PLSysNet_Const_AF_eUnix			,
		PLSysNet_Const_AF_eISO			,
		PLSysNet_Const_AF_eNS           ,
		PLSysNet_Const_AF_eIPX			,
		PLSysNet_Const_AF_eIRDA			,
		PLSysNet_Const_AF_eAPPLETALK	,
		PLSysNet_Const_AF_Unkonw	 = 0x7fffffff
	}PL_NetAddressFamilyStyle;

	typedef enum _ePL_NetSocketType{
		PLSysNet_Const_Socket_Stream	= 0,
		PLSysNet_Const_Socket_RAW		= 1,
		PLSysNet_Const_Socket_Dgram		   ,
		PLSysNet_Const_Socket_Seqpacket	   ,
		PLSysNet_Const_Socket_RDM
	}PL_NetSocketType;

	typedef enum _ePL_MsgSocketMode{
		PLSysNet_Const_MsgMode_Normal   		= 0,
		PLSysNet_Const_MsgMode_DONTROUTE 		= 1
	}PL_MsgSocketMode;

	typedef enum _ePL_SockOperateType{
		PLSysNet_Const_SO_eDebugMode 		= 0 ,
		PLSysNet_Const_SO_eReuseAddr	    = 1 ,
		PLSysNet_Const_SO_eSockTYPE				,
		PLSysNet_Const_SO_Sndbuf				,
		PLSysNet_Const_SO_Rcvbuf				,
		PLSysNet_Const_SO_ValidateKeepAlive		,
		PLSysNet_Const_SO_Error					,
		PLSysNet_Const_SO_SendDataLingerTimer
	}PL_SockOperateType;

	typedef enum _ePL_SockIPOperateType{
		PLSysNet_Const_SOIP_HDRINCL 		= 0 ,
		PLSysNet_Const_SOIP_OPTINOS			= 1 ,
		PLSysNet_Const_SOIP_TOS					,
		PLSysNet_Const_SOIP_TTL
	}PL_SockIPOperateType;

/************************************Begin Protocol define*****************************************************/
/*IPVX*/
	#define PLSysNet_Const_Protocol_TCP				IPPROTO_TCP
	#define PLSysNet_Const_Protocol_UDP				IPPROTO_UDP
	#define PLSysNet_Const_Protocol_ICMP			IPPROTO_ICMP
	#define PLSysNet_Const_Protocol_IDP				IPPROTO_IDP
	#define PLSysNet_Const_Protocol_IGMP			IPPROTO_IGMP
	#define PLSysNet_Const_Protocol_EGP				IPPROTO_EGP
	#define PLSysNet_Const_Protocol_PUP				IPPROTO_PUP
	#define PLSysNet_Const_Protocol_RAW				IPPROTO_RAW
	#define PLSysNet_Const_Protocol_ESP				IPPROTO_ESP
/*IPV4*/
	#define PLSysNet_Const_Protocol_IP				IPPROTO_IP
/*IPV6*/
	#define PLSysNet_Const_Protocol_HOPOPTS			IPPROTO_HOPOPTS
	#define PLSysNet_Const_Protocol_IPV6			IPPROTO_IPV6
	#define PLSysNet_Const_Protocol_ROUTING			IPPROTO_ROUTING
	#define PLSysNet_Const_Protocol_FRAGMENT		IPPROTO_FRAGMENT
	#define PLSysNet_Const_Protocol_NONE			IPPROTO_NONE
	#define PLSysNet_Const_Protocol_DSTOPTS			IPPROTO_DSTOPTS
	#define PLSysNet_Const_Protocol_ICMPV6			IPPROTO_ICMPV6
/************************************End   Protocol define*****************************************************/

/************************************Begin Set/Get Operate Mode************************************************/
	#define PLSysNet_Const_OperMode_Socket			SOL_SOCKET
	#define PLSysNet_Const_OperMode_IPPROTO_IP		PLSysNet_Const_Protocol_IP
	#define PLSysNet_Const_OperMode_IPPROTO_IPV6	PLSysNet_Const_Protocol_IPV6
	#define PLSysNet_Const_OperMode_IPPROTO_TCP		PLSysNet_Const_Protocol_TCP
	#define PLSysNet_Const_OperMode_IPPROTO_UDP		PLSysNet_Const_Protocol_UDP
	#define PLSysNet_Const_OperMode_IPPROTO_IGMP	PLSysNet_Const_Protocol_IGMP
	#define PLSysNet_Const_OperMode_IPPROTO_IGMPV6	PLSysNet_Const_Protocol_ICMPV6
/************************************End Set/Get Operate Mode**************************************************/



/************************************Begin Set/Get Operate Type************************************************/
	#define PLSysNet_Const_OperTy_DebugMode					SO_DEBUG
	#define PLSysNet_Const_OperTy_ReuseAddr					SO_REUSEADDR
	#define PLSysNet_Const_OperTy_SockTYPE					SO_TYPE
	#define PLSysNet_Const_OperTy_Sndbuf					SO_SNDBUF
	#define PLSysNet_Const_OperTy_Rcvbuf					SO_RCVBUF
	#define PLSysNet_Const_OperTy_ValidateKeepAlive			SO_KEEPALIVE
	#define PLSysNet_Const_OperTy_SendDataLingerTimer		SO_LINGER

	#define PLSysNet_Const_OperTy_IPV4TOS					IP_TOS
	#define PLSysNet_Const_OperTy_IPV4TTL					IP_TTL
	#define PLSysNet_Const_OperTy_IPV4MultiCastTTL			IP_MULTICAST_TTL
	#define PLSysNet_Const_OperTy_IPV4DontFragMent			IP_DONTFRAGMENT
	#define PLSysNet_Const_OperTy_IPV4AddSourceMemberShip	IP_ADD_SOURCE_MEMBERSHIP
	#define PLSysNet_Const_OperTy_IPV4DropSourceMemberShip	IP_DROP_SOURCE_MEMBERSHIP
	#define PLSysNet_Const_OperTy_IPV4BlockSource			IP_BLOCK_SOURCE
	#define PLSysNet_Const_OperTy_IPV4UnBlockSource			IP_UNBLOCK_SOURCE

	#define PLSysNet_Const_OperTy_IPV6UncastHops			IPV6_UNICAST_HOPS
	#define PLSysNet_Const_OperTy_IPV6MultiCastHops			IPV6_MULTICAST_HOPS
	#define PLSysNet_Const_OperTy_IPV6JoinGroup				IPV6_JOIN_GROUP
	#define PLSysNet_Const_OperTy_IPV6LeaveGroup			IPV6_LEAVE_GROUP

	#define PLSysNet_Const_OperTy_IPXMultiCastIF			IP_MULTICAST_IF
	#define PLSysNet_Const_OperTy_IPXMultiCastLoop			IP_MULTICAST_LOOP
	#define PLSysNet_Const_OperTy_IPXAddMemberShip 			IPV6_ADD_MEMBERSHIP
	#define PLSysNet_Const_OperTy_IPXDropMemberShip			IP_DROP_MEMBERSHIP
	#define PLSysNet_Const_OperTy_IPXPKTInfo				IP_PKTINFO

/************************************End Set/Get Operate Mode**************************************************/


/*
#define SOCK_STREAM	1
#define SOCK_DGRAM	2
#define SOCK_RAW	3
#define SOCK_RDM	4
#define SOCK_SEQPACKET	5
*/

#pragma pack(4)
//	typedef struct Aligned(8) _SPL_SocketDepict{
//		union{
//
//		}addres;
//	}PL_SocketDepict;
/*
	typedef struct Aligned(8) _SPL_SocketAddres{

	}__Aligned(8) PL_SocketAddr;
*/
	typedef struct Aligned(8) _SPL_SockAddres_base{
		PL_NetAddressFamilyStyle 	eAFStyle;
		intV_pl                     iSysAddrSize;
	}__Aligned(8) PL_SockAddres_Base;

	typedef struct Aligned(8) _SPL_SockAddres_IPV4 : public _SPL_SockAddres_base{
		struct sockaddr_in addr;
	}__Aligned(8) PL_SockAddres_IPV4;
	typedef struct Aligned(8) _SPL_SockAddres_IPV6 : public _SPL_SockAddres_base{
		struct sockaddr_in6 addr;
	}__Aligned(8) PL_SockAddres_IPV6;

	typedef struct Aligned(8) _SPL_SockAddress : public _SPL_SockAddres_base{
		union{
			struct sockaddr_in  addrIPV4;
			struct sockaddr_in6 addrIPV6;
		}sysaddr;
	}__Aligned(8) PL_SockAddress;

	#if PLOperat_System == PLOperatSystem_Linux
		#define PLSysNet_Const_FDSockMaxSize 32
	#elif PLOperat_System == PLOperatSystem_Window
		#define PLSysNet_Const_FDSockMaxSize 32
	#elif PLOperat_System == PLOperatSystem_Unix
		#define PLSysNet_Const_FDSockMaxSize 32
	#elif PLOperat_System == PLOperatSystem_MacOS
		#define PLSysNet_Const_FDSockMaxSize 32
	#endif



#pragma pack()

#endif /* PLENGINESYSNETWORKAPIINFACE_H_ */
