/*
 * PLEngineSysSTLArithmeticAPIInface.h
 *
 *  Created on: 2009-10-13
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINESYSSTLARITHMETICAPIINFACE_H_
#define PLENGINESYSSTLARITHMETICAPIINFACE_H_
	#define HSHashMap void_pl *

	typedef _CallStack_default_ void_pl * (*__stl_allocatememory__PL__)				(void_pl *,intV_pl);
	typedef _CallStack_default_ void_pl   (*__stl_freememory__PL__)					(void_pl *,void_pl *);
	typedef _CallStack_default_ const_pl char_pl * (*__stl_allocatenewstring__PL__) (const_pl char_pl *,intV_pl,void_pl *,__stl_allocatememory__PL__);
	typedef _CallStack_default_ void_pl   (*__stl_freestring__PL__)					(const_pl char_pl *,intV_pl,void_pl *,__stl_freememory__PL__);
	typedef _CallStack_default_ uintV_pl  (*__stl_hashstringFunc__PL__)				(const_pl char_pl *,intV_pl,intV_pl);
#endif /* PLENGINESYSSTLARITHMETICAPIINFACE_H_ */
