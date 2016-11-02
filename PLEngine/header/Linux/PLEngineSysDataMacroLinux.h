/*
 * PLEngineSysDataMacroLinux.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "../PLEngineBaseDataType.h"
#include "../PLEngineGraphicsInface.h"
#include "../PLEngineH.h"
#include "../PLEngineInface.h"
#if PLOperat_System != PLOperatSystem_Linux
	#define PLENGINESYSDATAMACROLINUX_H_
#endif
#ifndef PLENGINESYSDATAMACROLINUX_H_
#define PLENGINESYSDATAMACROLINUX_H_
	#ifndef PLTHREAD_STACK_MIN_SIZE
		#ifndef PTHREAD_STACK_MIN
			#define PTHREAD_STACK_MIN 16384
		#endif
		#define PLTHREAD_STACK_MIN_SIZE PTHREAD_STACK_MIN
	#endif
	#define PLSysAPI_AllocateMemory(size) ::malloc(size)
	#define PLSysAPI_FreeMemory(ptr)      ::free(ptr)
	#define PLSysAPI_AllocateMemoryHG(size) ::malloc(size)
	#define PLSysAPI_FreeMemoryHG(ptr,size) ::free(ptr)
	#ifndef __PL_Synchron_DataType_
		#define __PL_Synchron_DataType_
		#define _Syn_SysMutexLock 			sem_t *
		#define _Syn_SysEventLock       	void_pl *
		#define _Syn_SysSignalLock 			pthread_cond_t
		#define _Syn_SemaphoreLock       	sem_t *
		#define _Syn_CriticalSection 		pthread_mutex_t
	#endif

	#define HPLSocket int_pl
	#define Invalid_PLSocket	(-1)
//	#define PLLibModuleHandle   void_pl *
	#define PLThread_Handle     pthread_t
	#define PLThreadHandle      PLThread_Handle
	#define PLTLSKey 			pthread_key_t
	#define PLTLSKey_Invalid    ((pthread_key_t)(~0))
	#define PLThreadHandle_Invalid 0
	#define PLSys_ConstChar_SystemCWDPartition L'/'


	inline void_pl * PLMacro_AllocateHighMemory(intV_pl iSize){
		return malloc(iSize);
	}
	inline HPL_Result PLMacro_FreeHighMemory(void_pl * ptrMem){
		free(ptrMem);
		return HPLResult_OK;
	}


#pragma pack(4)
	typedef struct _SPLSynEvent_Linux{
		intV_pl iFlag;
		pthread_cond_t  cond;
		pthread_mutex_t mutex;
	}PLSynEvent_Linux;
	typedef struct Aligned(8) _SPL_SocketDepict{
		PL_NetAddressFamilyStyle 	eAFStyle;
		uintV_pl 						uPort;
		intV_pl                    iProtocol;
		union {
			uchar_pl 	_addr_u8[16];
			uint16_pl 	_addr_u16[8];
			uint32_pl   _addr_u32[4];
		}addres;
	}PL_SocketDepict;

	typedef struct Aligned(8) _SPL_FDSockItem{
		HPLSocket hSK;
	}__Aligned(8) PL_FDSockItem;

	typedef struct Aligned(8) _SPL_SockCollection{
		fd_set set;

	}__Aligned(8) PL_SockCollection;

#pragma pack()

#endif /* PLENGINESYSDATAMACROLINUX_H_ */
