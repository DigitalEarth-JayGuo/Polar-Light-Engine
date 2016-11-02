/*
 * PLEngineSysSynchronInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINESYSSYNCHRONINFACE_H_
#define PLENGINESYSSYNCHRONINFACE_H_
	#define _Syn_SpinLock  		 			volatile_pl	PLThreadVirtualID
	#define _Syn_TSpinLock					volatile_pl	PLThreadVirtualID
	#define PLSyn_Const_SynSpinLockPass     PLTd_Const_PLThreadVIDInvalid
	#define PLSyn_Const_SpeediEasyLock		(PLTd_Const_PLThreadVIDInvalid + 1)
	#define PLSyn_Const_SynTSpinLockPass	0
	#define PLSyn_Const_SynTSpinLockInvalid	-1
//	#define _Syn_LWLock          PLThreadVirtualID

	#define PLSyn_Const_SynLWLockPass 		PLTd_Const_PLThreadVIDInvalid
	#define PLSyn_Const_SynLWLockInvalid	-1
#pragma pack(8)
	typedef  struct _PLSt_Syn_LWLock{
		int64_pl iValue;
		int32_pl iCount;
		int32_pl iInterval;
	} _Syn_LWLock;
#pragma pack(8)
//	#define _Syn_CriticalSection
#endif /* PLENGINESYSSYNCHRONINFACE_H_ */
