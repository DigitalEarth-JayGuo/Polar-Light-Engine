/*
 * PLEngineH.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "PLEngineBaseDataType.h"
#ifndef PLENGINEH_H_
#define PLENGINEH_H_
	#ifndef PLOperat_System
		#define PLOperat_System PLOperatSystem_Linux
	#endif
	#if PLOperat_System == PLOperatSystem_Window
		#include "PLEngineWindowH.h"
	#elif PLOperat_System == PLOperatSystem_Linux
		#include "PLEngineLinuxH.h"
	#endif
	#include "PLEngineSysDataMacro.h"
#endif /* PLENGINEH_H_ */
