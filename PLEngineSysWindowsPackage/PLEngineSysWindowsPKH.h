/*
 * PLEngineSysWindowsPKH.h
 *
 *  Created on: 2009-10-27
 *      Author: Administrator
 */
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
#ifndef PLENGINESYSWINDOWSPKH_H_
#define PLENGINESYSWINDOWSPKH_H_

	#ifdef IDESetPrjExport_SysWindows
		//class export define tag
		#define _WinPLE_lib_class    _export_lib_class
		//function export define tag
		#define _WinPLE_lib_c        _export_lib_c
		//variable export define tag
		#define _WinPLE_lib_Variable _export_lib_variable

		#define _WinPLE_lib_VariableDup _export_lib_variableDup

		#define _WinPLE_lib_VariableN _export_lib_variableNormal

	#else
		//class import define tag
		#define _WinPLE_lib_class    _import_lib_class
		//function import define tag
		#define _WinPLE_lib_c        _import_lib_c
		//variable import define tag
		#define _WinPLE_lib_Variable _import_lib_variable

		#define _WinPLE_lib_VariableDup _import_lib_variableDup

		#define _WinPLE_lib_VariableN _import_lib_variableNormal

	#endif

#endif /* PLENGINESYSWINDOWSPKH_H_ */
