/*
 * PLEngineFontPackage.h
 *
 *  Created on: 2010-2-24
 *      Author: DevLinux
 */
#include "PLEngineFontPKH.h"
#ifndef PLENGINEFONTPACKAGE_H_
#define PLENGINEFONTPACKAGE_H_
	#include "PLEngineFontPKH.h"
	#include "EngineFontInface.h"
	_FonPLE_lib_c _CallStack_default_ PLLibraryHandle CreateLibraryPL(HPPLEngine,void_pl *);
	_CallStack_default_  bool_pl InstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  HPL_Result UnInstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  void_pl Destory_LibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);

#endif /* PLENGINEFONTPACKAGE_H_ */
