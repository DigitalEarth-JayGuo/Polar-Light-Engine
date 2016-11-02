/*
 * MainLib.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "PLEngineH.h"
#include "PLEngineI.h"
#include "PLEngineHeavyH.h"
#include "PLEngineSysAPI.h"
#include "PLEngineInface.h"
#include "PLEngineSysProcess.h"
#ifndef MAINLIB_H_
#define MAINLIB_H_
	typedef Aligned(8) struct _SPL_native_ELoadLibrary{
		PLFileCFGHandle hCFGHandle;
		intV_pl         iPlusID;
	}__Aligned(8) PL_native_ELoadLibrary;

	_PLE_lib_c _CallStack_default_ HPPLEngine CreateEngineHandle();
	_PLE_lib_c _CallStack_default_ HPL_Result InitializeEngine(HPPLEngine handle);
	_PLE_lib_c _CallStack_default_ HPL_Result DestoryEngineHandle(HPPLEngine handle);

	HPL_Result __native_LoadLibrary_PL(HPPLEngine hEngine,void_pl * ptrEx,PL_EngineLibraryPlusNode * ptrNode,PL_native_ELoadLibrary * ptrLibParamer);
	HPL_Result __native_ReleaseLoadLibrary_PL(HPPLEngine hEngine,void_pl * ptrEx,PL_EngineLibraryPlusNode * ptrNode);

	#if PLOperat_System == PLOperatSystem_Window

		_export_lib_c BOOL WINAPI DllMain(HMODULE , DWORD , void* );
	#endif

#endif /* MAINLIB_H_ */
