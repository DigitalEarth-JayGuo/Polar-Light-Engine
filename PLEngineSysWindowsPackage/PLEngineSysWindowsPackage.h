/*
 * PLEngineSysWindowsPackage.h
 *
 *  Created on: 2009-10-27
 *      Author: Administrator
 */

#ifndef PLENGINESYSWINDOWSPACKAGE_H_
#define PLENGINESYSWINDOWSPACKAGE_H_
	#include "PLEngineSysWindowsPKH.h"
	#include "EngineSysWindowsInface.h"
	_WinPLE_lib_c _CallStack_default_ PLLibraryHandle CreateLibraryPL(HPPLEngine,void_pl *);
	_CallStack_default_  bool_pl InstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  HPL_Result UnInstallLibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
	_CallStack_default_  void_pl Destory_LibraryPL(HPPLEngine,PLLibraryHandle,void_pl *);
#endif /* PLENGINESYSWINDOWSPACKAGE_H_ */
