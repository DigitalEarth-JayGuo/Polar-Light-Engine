/*
 * PLEngineResrouceLoadPackage.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "PLEngineResourceLoadPKH.h"
#include "EngineResourceLoadInface.h"
#include "EngineResourceLoadAPI.h"
#ifndef PLENGINERESROUCELOADPACKAGE_H_
#define PLENGINERESROUCELOADPACKAGE_H_

	_ScenePLE_lib_c _CallStack_default_  PLLibraryHandle CreateLibraryPL(HPPLEngine,void_pl *);
	_CallStack_default_  bool_pl 	InstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  HPL_Result UnInstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  void_pl	Destory_LibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
#endif /* PLENGINERESROUCELOADPACKAGE_H_ */
