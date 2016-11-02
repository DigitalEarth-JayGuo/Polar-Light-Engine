/*
 * PLEngineScriptPackage.h
 *
 *  Created on: 2009-8-14
 *      Author: Administrator
 */
#include "EngineScriptAPI.h"
#ifndef PLENGINESCRIPTPACKAGE_H_
#define PLENGINESCRIPTPACKAGE_H_

	_ScenePLE_lib_c _CallStack_default_  PLLibraryHandle CreateLibraryPL(HPPLEngine,void_pl *);
	_CallStack_default_  bool_pl 	InstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  HPL_Result UnInstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  void_pl	Destory_LibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);

#endif /* PLENGINESCRIPTPACKAGE_H_ */
