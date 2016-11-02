/*
 * EngineSysWindowsInface.h
 *
 *  Created on: 2010-2-23
 *      Author: DevLinux
 */
#include "EngineSysWindowsI.h"
#include "PLEngineSysWindowsPKH.h"
//#include "EngineResourceLoadI.h"
//#include "PLEngineResourceLoadPKH.h"
#ifndef ENGINESYSWINDOWSINFACE_H_
#define ENGINESYSWINDOWSINFACE_H_



#pragma pack(4)
	typedef  struct Aligned(8) _SPL_SysWindowsPlusLibraryHeavy{
		PL_EngineLibraryHeavyInface Inface;
		PLConstCharTableHandle hSysConstCharTable;
		HPPLEngine hEngine;

//		char_pl pCWD[PL3DSystemFileNameMaxLength];
//		intV_pl iCWDSize;
//		char_pl pResourceCWD[PL3DSystemFileNameMaxLength];
//		intV_pl iResourceCWDSize;
//		intV_pl iConst_PackageCount;
//		PL_RLPackage * Const_ListPackage;
//		PL_RLPackage * RW_ListPackage;
	}__Aligned(8) PL_SysWindowsLibraryHeavy;

	typedef  struct Aligned(8) _SPL_SysWindowsLibraryFunTable{
		PL_EngineLibraryFunTable Inface;
		fun_pl functionlistEx[PLSysWindows_Table_FunMaxSize - 1];
	}__Aligned(8) PL_SysWindowsLibraryFunTable;
#pragma pack()


#endif /* ENGINESYSWINDOWSINFACE_H_ */
