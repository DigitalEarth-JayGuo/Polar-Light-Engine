/*
 * PLEngineSceneH.h
 *
 *  Created on: 2009-8-4
 *      Author: DevLinux
 */

#ifndef PLENGINESCENEH_H_
#define PLENGINESCENEH_H_
#include "header/PLEngineBaseDataType.h"
#include "header/PLEngineI.h"
#include "header/PLEngineInface.h"
#include "header/MainLib.h"
#include "header/PLEngineMath.h"
#include "header/PLEngineHeavyH.h"
#include "header/PLEngineMemoryPool.h"
	#ifdef IDESetPrjExport_Scene
		//class export define tag
		#define _ScenePLE_lib_class    _export_lib_class
		//function export define tag
		#define _ScenePLE_lib_c        _export_lib_c
		//variable export define tag
		#define _ScenePLE_lib_Variable _export_lib_variable

		#define _ScenePLE_lib_VariableDup _export_lib_variableDup

		#define _ScenePLE_lib_VariableN _export_lib_variableNormal

	#else
		//class import define tag
		#define _ScenePLE_lib_class    _import_lib_class
		//function import define tag
		#define _ScenePLE_lib_c        _import_lib_c
		//variable import define tag
		#define _ScenePLE_lib_Variable _import_lib_variable

		#define _ScenePLE_lib_VariableDup _import_lib_variableDup

		#define _ScenePLE_lib_VariableN _import_lib_variableNormal

	#endif
#endif /* PLENGINESCENEH_H_ */
