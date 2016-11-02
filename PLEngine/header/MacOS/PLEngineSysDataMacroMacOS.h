/*
 * PLEngineSysDataMacroMacOS.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "../PLEngineBaseDataType.h"
#include "../PLEngineGraphicsInface.h"
#include "../PLEngineH.h"
#include "../PLEngineInface.h"
#if PLOperat_System != PLOperatSystem_MacOS
	#define PLENGINESYSDATAMACROMACOS_H_
#endif
#ifndef PLENGINESYSDATAMACROMACOS_H_
#define PLENGINESYSDATAMACROMACOS_H_
	#ifndef PLTHREAD_STACK_MIN_SIZE
		#ifndef PTHREAD_STACK_MIN
			#define PTHREAD_STACK_MIN 16384
		#endif
		#define PLTHREAD_STACK_MIN_SIZE PTHREAD_STACK_MIN
	#endif
	#define PLSysAPI_AllocateMemory(size) ::malloc(size)
	#define PLSysAPI_FreeMemory(ptr)      ::free(ptr)
//	#define PLLibModuleHandle void_pl *
	#define HPLSocket int_pl
	#define Invalid_PLSocket	(-1)

	#ifndef __PL_Synchron_DataType_
		#define __PL_Synchron_DataType_
		#define _Synchron_SysMutex_Lock pthread_mutex_t
		#define _Synchron_SysSignal_Lock pthread_cond_t
	#endif
	#define PLSys_ConstChar_SystemCWDPartition '/'
#pragma pack(4)
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
#pragma pack()
#endif /* PLENGINESYSDATAMACROMACOS_H_ */
