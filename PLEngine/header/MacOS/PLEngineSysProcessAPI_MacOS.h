/*
 * PLEngineSysProcessAPI_MacOS.h
 *
 *  Created on: 2009-7-20
 *      Author: DevLinux
 */
#include "../PLEngineBaseDataType.h"
#include "../PLEngineGraphicsInface.h"
#include "../PLEngineH.h"
#include "../PLEngineInface.h"
#include "../PLEngineSysAPI.h"
#include "../PLEngineSysProcess.h"
#include "../PLEngineResultVD.h"
#include "../PLEngineSysEnvIFM.h"
#include "../PLEngineSysSynchron.h"

#if PLOperat_System != PLOperatSystem_MacOS
	#define PLENGINESYSPROCESSAPI_MACOS_H_
#endif
#ifndef PLENGINESYSPROCESSAPI_MACOS_H_
#define PLENGINESYSPROCESSAPI_MACOS_H_
	#ifdef __PL_Synchron_DataType_
		inline HPL_Result __PLSysAPI_TSynchron_MutexLock(PLTSys_Mutex * ptrMutex){
			return HPLResult_OK;
		}
	#endif
#endif /* PLENGINESYSPROCESSAPI_MACOS_H_ */
