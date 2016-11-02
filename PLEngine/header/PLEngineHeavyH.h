/*
 * PLEngineHeavyH.h
 *
 *  Created on: 2009-6-30
 *      Author: root
 */

#include "PLEngineBaseDataType.h"
#include "PLEngineMath.h"
#include "PLEngineSysSynchron.h"
#include "PLEngineMemoryPool.h"
#include "PLEngineSysEnvIFM.h"
#include "PLEngineSysIO.h"
#include "PLEngineSysProcess.h"
#ifndef PLENGINEHEAVYH_H_2009_06_30_Default
#define PLENGINEHEAVYH_H_2009_06_30_Default
	/*
	 *
	 * Math API Function Pointer
	 *
	 * */
	#define PLLib_Const_SysMath_Tag_GeometryHead                	0
	#define PLLib_Const_SysMath_InitializNormalizMatrix3x3  	   (PLLib_Const_SysMath_Tag_GeometryHead)
	#define PLLib_Const_SysMath_InitializNormalizMatrix4x4  	   (PLLib_Const_SysMath_Tag_GeometryHead + 1)
	#define PLLib_Const_SysMath_Tag_MaxSize           			   (PLLib_Const_SysMath_Tag_GeometryHead + 2)
//	typedef Aligned(8) struct _StEngineMath_Lib_PL{
//		PL_EngineLibraryHeavyInface Head;
//		fun_pl functionlist[PLLib_Const_SysMath_Tag_MaxSize];
//	}EngineMath_Lib_PL;
	/*
	 *
	 * SystemWith API Function Pointer
	 *
	 * */
	#define PLLib_Const_SysWith_Tag_MemoryHead               	   0
	#define PLLib_Const_SysWith_Tag_MaxSize           			(PLLib_Const_SysWith_Tag_MemoryHead + 1)
	#define PLLib_Const_SysWith_Tag_AppExpansion 				(PLLib_Const_SysWith_Tag_MaxSize)

//	typedef Aligned(8) struct _StEngineSystemIO_Lib_PL{
//		PL_EngineLibraryHeavyInface Head;
//		fun_pl functionlist[PLLib_Const_SysIO_Tag_MaxSize];
//	}EngineSystemIO_Lib_PL;

#endif /* PLENGINEHEAVYH_H_2009_06_30_Default */
