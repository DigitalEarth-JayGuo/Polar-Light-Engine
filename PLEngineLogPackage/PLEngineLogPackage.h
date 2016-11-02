/*
 * PLEngineLogPackage.h
 *
 *  Created on: 2009-9-28
 *      Author: Administrator
 */
#include "PLEngineLogPKH.h"
#include "EngineLogSystemInface.h"
#include "EngineLogSystemI.h"
#include "EngineLogSystemAPI.h"
#ifndef PLENGINELOGPACKAGE_H_
#define PLENGINELOGPACKAGE_H_

	_ScenePLE_lib_c _CallStack_default_  PLLibraryHandle CreateLibraryPL(HPPLEngine,void_pl *);
	_CallStack_default_  bool_pl 	InstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  HPL_Result UnInstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  void_pl	Destory_LibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);

#endif /* PLENGINELOGPACKAGE_H_ */
