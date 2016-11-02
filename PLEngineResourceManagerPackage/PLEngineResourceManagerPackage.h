/*
 * PLEngineResourceManagerPackage.h
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "PLEngineResourceManagerPKH.h"
#include "EngineResourceManagerInface.h"
#include "EngineResourceManagerAPI.h"
#ifndef PLENGINERESOURCEMANAGERPACKAGE_H_
#define PLENGINERESOURCEMANAGERPACKAGE_H_

	_ScenePLE_lib_c _CallStack_default_  PLLibraryHandle CreateLibraryPL(HPPLEngine,void_pl *);
	_CallStack_default_  bool_pl 	InstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  HPL_Result UnInstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  void_pl	Destory_LibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
#endif /* PLENGINERESOURCEMANAGERPACKAGE_H_ */
