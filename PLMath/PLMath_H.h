/*
 * PLMath_H.h
 *
 *  Created on: 2009-6-25
 *      Author: root
 */
#include "../PLEngine/PLEngineBaseDataType.h"
#include "../PLEngine/PLEngineI.h"
#ifndef PLMATH_H_H_
#define PLMATH_H_H_
	#ifndef PLOperat_System
		#define PLOperat_System PLOperatSystem_Linux
	#endif
	#if PLOperat_System == PLOperatSystem_Window
		#include "PLMath_WindowH.h"
	#elif PLOperat_System == PLOperatSystem_Linux
		#include "PLMath_LinuxH.h"
	#endif
#endif /* PLMATH_H_H_ */
