/*
 * PLEngineSysDataMacro.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */
#include "PLEngineBaseDataType.h"
#ifndef PLENGINESYSDATAMACRO_H_
#define PLENGINESYSDATAMACRO_H_
	typedef enum _ePL_SocketDepictType{
		PLSys_Const_SocketDepict_IPV4 = 0,
		PLSys_Const_SocketDepict_IPV6 = 1,
		PLSys_Const_SocketDepict_RAW
	}PL_SocketDepictType;

	typedef void_pl (* _PLTLSKey_endthreadCallback) (void_pl *);
	#if PLOperat_System == PLOperatSystem_Window
		#include "Windows/PLEngineSysDataMacroWindows.h"
	#elif PLOperat_System == PLOperatSystem_Linux
		#include "Linux/PLEngineSysDataMacroLinux.h"
	#endif
//	#define PL_CompilerStringSize(p) strlen((char_pl *)p)

	#define HSockAddres	void_pl *
	#define HSockPoll void_pl *

	#define HSockCollection void_pl *
#pragma pack(4)

	typedef struct _PLSt_Syn_RWLockRF{
		volatile_pl intV_pl  iRCount;
		_Syn_CriticalSection lock;
	}_Syn_RWLockRF;
	typedef struct _PLSt_Syn_RWLockWF{
		volatile_pl intV_pl  iRCount;
		volatile_pl intV_pl  iWCount;
		_Syn_CriticalSection rlock;
		_Syn_CriticalSection lock;
	}_Syn_RWLockWF;

	typedef struct Aligned(8) _SPL_FDSock{
		PL_FDSockItem stlist[PLSysNet_Const_FDSockMaxSize];
		intV_pl iCount;
	}__Aligned(8) PL_FDSock;
#pragma pack()
#endif /* PLENGINESYSDATAMACRO_H_ */
