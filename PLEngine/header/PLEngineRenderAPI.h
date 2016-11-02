/*
 * PLEngineRenderAPI.h
 *
 *  Created on: 2009-9-14
 *      Author: Administrator
 */
#include "PLEngineH.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineSysAPI.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"

#ifndef PLENGINERENDERAPI_H_
#define PLENGINERENDERAPI_H_
	typedef _CallStack_default_ HPL_Result (* __Render_InitializeRenderState__PL__)	();


	_PLE_lib_Variable __Render_InitializeRenderState__PL__	PLRdrAPI_InitializeRenderState;
	//HPL_Result PLSysAPI_Rdr_Initialize
#endif /* PLENGINERENDERAPI_H_ */
