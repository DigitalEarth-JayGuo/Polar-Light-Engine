/*
 * PLEngineFontPKH.h
 *
 *  Created on: 2010-2-24
 *      Author: DevLinux
 */

#ifndef PLENGINEFONTPKH_H_
#define PLENGINEFONTPKH_H_
	#include "header/PLEngineBaseDataType.h"
	#include "header/PLEngineI.h"
	#include "header/PLEngineInface.h"
	#include "header/MainLib.h"
	#include "header/PLEngineMath.h"
	#include "header/PLEngineHeavyH.h"
	#include "header/PLEngineMemoryPool.h"
	#include "header/PLEngineResultVD.h"
	#include "header/PLEngineSysIO.h"
	#include "header/PLEngineSysSTLArithmeticAPI.h"
	#include "header/PLEngineRenderAPI.h"
	#ifdef IDESetPrjExport_SysFont
		//class export define tag
		#define _FonPLE_lib_class    _export_lib_class
		//class not export define tag
		#define _FonPLE_lib_classNV  _PLE_lib_classNV
		//function export define tag
		#define _FonPLE_lib_c        _export_lib_c
		//function not export define tag
		#define _FonPLE_lib_cNV      _PLE_lib_cNV
		//variable export define tag
		#define _FonPLE_lib_Variable _export_lib_variable

		#define _FonPLE_lib_VariableDup _export_lib_variableDup

		#define _FonPLE_lib_VariableN _export_lib_variableNormal
		//variable not export define tag
		#define _FonPLE_lib_VariableNV _PLE_lib_VariableNV
	#else
		//class import define tag
		#define _FonPLE_lib_class    _import_lib_class
		//class not import define tag
		#define _FonPLE_lib_classNV  _PLE_lib_classNV
		//function import define tag
		#define _FonPLE_lib_c        _import_lib_c
		//function not import define tag
		#define _FonPLE_lib_cNV      _PLE_lib_cNV
		//variable import define tag
		#define _FonPLE_lib_Variable _import_lib_variable

		#define _FonPLE_lib_VariableDup _import_lib_variableDup

		#define _FonPLE_lib_VariableN _import_lib_variableNormal
		//variable not import define tag
		#define _FonPLE_lib_VariableNV _PLE_lib_VariableNV

	#endif

#endif /* PLENGINEFONTPKH_H_ */
