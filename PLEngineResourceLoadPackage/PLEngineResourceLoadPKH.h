/*
 * PLEngineResrouceLoadPKH.h
 *
 *  Created on: 2009-9-16
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
#include "header/PLEngineResourceLoadAPI.h"
#include "header/PLEngineSysIO.h"
#include "header/PLEngineSysSTLArithmeticAPI.h"
#include "header/PLEngineRenderAPI.h"
#ifndef PLENGINERESROUCELOADPKH_H_
#define PLENGINERESROUCELOADPKH_H_

	#ifdef IDESetPrjExport_ResLoad
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

#endif /* PLENGINERESROUCELOADPKH_H_ */
