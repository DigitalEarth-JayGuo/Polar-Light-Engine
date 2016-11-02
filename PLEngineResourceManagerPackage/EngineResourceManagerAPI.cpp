/*
 * EngineResourceManagerAPI.cpp
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "EngineResourceManagerAPI.h"
PLLibraryHandle g_hLibraryHandle_Resource = 0;
uintV_pl __native_hash(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange){
	uintV_pl uHKey;
	uHKey = 0;
	for(intV_pl iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}
