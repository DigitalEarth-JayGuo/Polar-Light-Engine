/*
 * PLEngineSysProcessInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINESYSPROCESSINFACE_H_
#define PLENGINESYSPROCESSINFACE_H_

	#define PLSys_Const_SysThreadAttr_StackSize_Set 1<<0
	#define PLSys_Const_SysThreadAttr_Policy_Set    1<<1
	#define PLSys_Const_SysThreadAttr_Priority_Set  1<<2
	#define PLSys_Const_SysThreadAttr_Stack_Set     1<<3
	#define PLThreadVirtualID intV_pl
	#define PLThreadID        intV_pl
	#define PLTd_Const_PLThreadVIDInvalid  0
//	#define PLSys_Const_SysThreadAttr_Death_Set     1<<4

	/*System Process */
	typedef enum _ePL_SysThreadPriority{
		PLSys_Const_SysThreadPriority_CurrentSet = 0,
		PLSys_Const_SysThreadPriority_Normal,
		PLSys_Const_SysThreadPriority_Max,
		PLSys_Const_SysThreadPriority_Hight,
		PLSys_Const_SysThreadPriority_Hot,
		PLSys_Const_SysThreadPriority_Low,
		PLSys_Const_SysThreadPriority_Idel,
		PLSys_Const_SysThreadPriority_Min,
	}ePL_SysThreadPriority;
	typedef enum _ePL_SysThreadPolicy{
		PLSys_Const_SysThreadPolicy_CurrentSet = 0,
		PLSys_Const_SysThreadPolicy_SysSched   ,
		PLSys_Const_SysThreadPolicy_FIFO       , //FIFO Sched Func Thread
		PLSys_Const_SysThreadPolicy_Poll,        //Poll Sched Func Thread
		PLSys_Const_SysThreadPolicy_Unkonw     = 0x7fffffff
	}ePL_SysThreadPolicy;
#pragma pack(4)
	typedef struct Aligned(8) _SPLThreadAttribute{
		uintV_pl iStackSize;
		void_pl * ptrStack;
		ePL_SysThreadPolicy  ePolicy;
		intV_pl  iPriority;
		uintV_pl uTag;
	}__Aligned(8) PLThreadAttr;
//	typedef struct _SPLProcessLibraryData{
//		PLTLSKey key;
//	}PLProcessLibraryData;

#pragma pack()
#endif /* PLENGINESYSPROCESSINFACE_H_ */
