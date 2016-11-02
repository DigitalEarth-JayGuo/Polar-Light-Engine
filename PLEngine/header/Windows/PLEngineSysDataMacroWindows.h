/*
 * PLEngineSysDataMacroWindows.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "../PLEngineBaseDataType.h"
#include "../PLEngineGraphicsInface.h"
#include "../PLEngineH.h"
#include "../PLEngineInface.h"
#if PLOperat_System != PLOperatSystem_Window
	#define PLENGINESYSDATAMACROWINDOWS_H_
#endif
#ifndef PLENGINESYSDATAMACROWINDOWS_H_
#define PLENGINESYSDATAMACROWINDOWS_H_
	#ifndef PLTHREAD_STACK_MIN_SIZE
		#define PLTHREAD_STACK_MIN_SIZE 1048576
	#endif
	#define PLSysAPI_AllocateMemory(size) ::VirtualAlloc(NULL,size,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE)
	#define PLSysAPI_FreeMemory(ptr)      ::VirtualFree(ptr,0,MEM_RELEASE)
	#define PLSysAPI_AllocateMemoryHG(size) ::VirtualAlloc(NULL,size,MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN,PAGE_READWRITE)
	#define PLSysAPI_FreeMemoryHG(ptr,size) ::VirtualFree(ptr,0,MEM_RELEASE)
	#ifndef __PL_Synchron_DataType_
		#define __PL_Synchron_DataType_
		#define _Syn_SysMutexLock  		HANDLE
		#define _Syn_SysEventLock       HANDLE
		#define _Syn_SysSignalLock 		HANDLE
		#define _Syn_SemaphoreLock      HANDLE
		#define _Syn_CriticalSection 	CRITICAL_SECTION
	#endif
//	#define PLLibModuleHandle HMODULE
	#define HPLSocket SOCKET
	#define Invalid_PLSocket	NULL_PL

	#define PLTLSKey DWORD
	#define PLTLSKey_Invalid ((DWORD)(~0))
	#define PLThreadHandle_Invalid 0
	#define PLThread_Handle uint_pl
	#define PLThreadHandle  PLThread_Handle
	#define PLSys_ConstChar_SystemCWDPartition PLSysChar_SlashHL
	#define PLEngine_Const_TLSUnitMaxNum TLS_MINIMUM_AVAILABLE * 2
	typedef struct _SPL_TLSQueue{
		_SPL_TLSQueue * pNext;
		PLTLSKey TlsKeyList[PLEngine_Const_TLSUnitMaxNum];
		_PLTLSKey_endthreadCallback TlsDataCallBack[PLEngine_Const_TLSUnitMaxNum];
	}PL_EngineTLSQueue,* PPL_EngineTLSQueue;
	_PLE_lib_Variable PPL_EngineTLSQueue g_ptrTLSQueue;
	_CallStack_default_ PPL_EngineTLSQueue PLSysAPI_WinLocal_InitializeTLSQueue();
	_CallStack_default_ HPL_Result PLSysAPI_WinLocal_InsertTLSToQueue(PPL_EngineTLSQueue,PLTLSKey *,_PLTLSKey_endthreadCallback);
	_CallStack_default_ HPL_Result PLSysAPI_WinLocal_RemoveTLSToQueue(PPL_EngineTLSQueue,PLTLSKey*);
	_CallStack_default_ HPL_Result PLSysAPI_WinLocal_DestoryTLSToQueue(PPL_EngineTLSQueue*);
	_CallStack_default_ HPL_Result PLSysAPI_WinLocal_NotifyTLSDataFree(PPL_EngineTLSQueue,PLTLSKey*);
	_CallStack_default_ HPL_Result PLSysAPI_WinLocal_NotifyTLSDataAllFree(PPL_EngineTLSQueue);

	inline void_pl * PLMacro_AllocateHighMemory(intV_pl iSize){
		return VirtualAlloc(NULL, iSize, (MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN), PAGE_READWRITE);
	}
	inline HPL_Result PLMacro_FreeHighMemory(void_pl * ptrMem){
		return VirtualFree(ptrMem,0,MEM_RELEASE) == FALSE ? HPLResult_Fail : HPLResult_OK;
	}

#pragma pack(4)
	typedef struct Aligned(8) _SPL_SocketDepict{
//		u_long sin6_flowinfo;	/* IPv6 traffic class & flow info */
//		u_long sin6_scope_id;	/* set of interfaces for a scope */
/*
		char	sin_zero[8];
//		PL_NetSocketType    		eSKType;
 * */
		PL_NetAddressFamilyStyle 	eAFStyle;
		uintV_pl 					uPort;
		intV_pl                     iProtocol;
		union {
			uchar_pl 	_addr_u8[16];
			uint16_pl 	_addr_u16[8];
			uint32_pl   _addr_u32[4];
		}addres;
	}PL_SocketDepict;
	typedef struct Aligned(8) _SPL_FDSockItem{
		HPLSocket hSK;
	}__Aligned(8) PL_FDSockItem;
#pragma pack()

#endif /* PLENGINESYSDATAMACROWINDOWS_H_ */
