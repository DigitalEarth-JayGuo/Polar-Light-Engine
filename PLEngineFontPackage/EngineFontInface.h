/*
 * EngineFontInface.h
 *
 *  Created on: 2010-2-24
 *      Author: DevLinux
 */

#ifndef ENGINEFONTINFACE_H_
#define ENGINEFONTINFACE_H_
	#include "PLEngineFontPKH.h"
	#include "EngineFontI.h"
	#pragma pack(4)
	typedef  struct Aligned(8) _SPL_FontPlusLibraryHeavy{
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
	}__Aligned(8) PL_FontLibraryHeavy;

	typedef  struct Aligned(8) _SPL_FontLibraryFunTable{
		PL_EngineLibraryFunTable Inface;
		fun_pl functionlistEx[PLFont_Table_FunMaxSize - 1];
	}__Aligned(8) PL_FontLibraryFunTable;

#pragma pack()
#endif /* ENGINEFONTINFACE_H_ */
