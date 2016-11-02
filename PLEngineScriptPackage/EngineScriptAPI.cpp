/*
 * EngineScriptAPI.cpp
 *
 *  Created on: 2009-8-14
 *      Author: DevLinux
 */
#include "EngineScriptAPI.h"
PLLibraryHandle        g_hLibraryHandle_Script = NULL_PL;
int __OpenCall(lua_State * ptrState);
PLLibraryHandle Eg_GetLibraryHandle_global(){
	return g_hLibraryHandle_Script;
}
PLScriptHandle  Eg_OpenScript(){
	PLScriptHandle hAndle;
	lua_State * ptrState;
	PL_ScriptObject * ptrScriptObject;
	PLLibraryHandle   hLibraryAndle;
	PL_ScriptLibraryHeavy * ptrLibraryHeavy;
//	PL_ConstSystemInfo * ptrInfo;
//	intV_pl iAllocSize;
	intV_pl iObjectStSize;
//	AddresValue_pl  addresV;
//	intV_pl iCacheLineSize;
	hAndle = NULL_PL;
	hLibraryAndle = Eg_GetLibraryHandle_global();
	if(hLibraryAndle==NULL_PL)
		return NULL_PL;
	ptrLibraryHeavy = (PL_ScriptLibraryHeavy *)hLibraryAndle;
	ptrState = lua_open();
	if(ptrState != NULL_PL){
//		ptrInfo = PLSysAPI_Sys_GetConstSystemInfo(ptrLibraryHeavy->hEngine);
//		iCacheLineSize       = ptrInfo->iCacheLineSize;
		iObjectStSize 		 = PL_CompilerAllocSize(PL_ScriptObject);
//		iAllocSize    		 = PLSysAPI_Alignment(iObjectStSize,iCacheLineSize) + iCacheLineSize;
//		ptrScriptObject      = (PL_ScriptObject *)PLSysAPI_AllocateMemory(iAllocSize);
//		addresV     		 = (AddresValue_pl)ptrScriptObject;
//		addresV    			 = PLSysAPI_Alignment(addresV,iCacheLineSize);
//		((PL_ScriptObject *)addresV)->ptrMem = ptrScriptObject;
//		ptrScriptObject      = (PL_ScriptObject *)addresV;
		ptrScriptObject      = (PL_ScriptObject *)PLSysAPI_Mem_AllocateMemoryPool(iObjectStSize);
		ptrScriptObject->icbSize = iObjectStSize;
		ptrScriptObject->ptrState= ptrState;
		ptrScriptObject->hSysConstCharTable = ptrLibraryHeavy->hSysConstCharTable;
		hAndle = (PL_ScriptObject *)ptrScriptObject;
	}
	return hAndle;
}
HPL_Result Eg_InitializeScriptLib(PLScriptHandle hAndle){
	HPL_Result hResult;
	lua_State * ptrState;
	PL_ScriptObject * ptrScriptObject;
	void_pl         * ptrConstCharRes;
	intV_pl           iConstCharResSize;
	hResult = HPLResult_Fail;
	if(hAndle == NULL_PL)
		return hResult;
	ptrScriptObject = (PL_ScriptObject *)hAndle;
	if(ptrScriptObject->bInitialize == true_pl)
		return hResult;
	ptrState = ptrScriptObject->ptrState;
	luaopen_base(ptrState);
//	luaopen_math(ptrState);
//	luaopen_string(ptrState);
//	luaopen_table(ptrState);
	//set Register Value  (save script handle)
	ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
													,PLScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
	//set Register Value (define new table)
	lua_pushstring(ptrState,(char_pl *)ptrConstCharRes);
	lua_newtable(ptrState);
	lua_settable(ptrState,LUA_REGISTRYINDEX);

//	lua_newthread
	lua_pushlightuserdata(ptrState,(void_pl *)hAndle);
	lua_setfield(ptrState,LUA_REGISTRYINDEX,PLScript_ConstID_ScriptRegisterID_Str);
	hResult = HPLResult_OK;
	ptrScriptObject->bInitialize = true_pl;
	return hResult;
}
PLScriptHandle Eg_ConverScriptHandleToScriptStateHandle(PLScriptStateHandle hAndle){
	PLScriptHandle hSH;
	lua_State * ptrState;
	ptrState = (lua_State *)hAndle;
	lua_getfield(ptrState,LUA_REGISTRYINDEX,PLScript_ConstID_ScriptRegisterID_Str);
	hSH = (PLScriptHandle)lua_topointer(ptrState,-1);
	lua_pop(ptrState,1);
	return hAndle;
}
HPL_Result Eg_RegisterScriptFunc(PLScriptHandle hAndle,const_pl char_pl * ptrScript,intV_pl iScriptSize,
					const_pl char_pl * ptrPackage,intV_pl iPackageSize,void_pl * ptrFunc){
	HPL_Result hResult;
	lua_State * ptrState;
	PL_ScriptNativeReg * ptrSNRData;
	intV_pl iAllocSize;
	int_pl iType;
	hResult = HPLResult_Fail;
	if(hAndle == NULL_PL || ptrScript == NULL_PL || ptrFunc == NULL_PL)
		return hResult;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	iAllocSize = PL_CompilerAllocSize(PL_ScriptNativeReg);
	if(ptrPackage != NULL_PL){
		lua_getglobal(ptrState,ptrPackage);
		iType = lua_type(ptrState,-1);
		if((iType != LUA_TNIL) && (iType != LUA_TTABLE)){
			lua_pop(ptrState,1);
			return hResult;
		}
		if(iType == LUA_TNIL){
			lua_pop(ptrState,1);
			lua_newtable(ptrState);
			lua_pushvalue(ptrState,-1);
			lua_setglobal(ptrState,ptrPackage);
		}
		lua_pushstring(ptrState,ptrScript);
	}
	ptrSNRData = (PL_ScriptNativeReg *)lua_newuserdata(ptrState,iAllocSize);
	PLSysAPI_MemoryClearZero(ptrSNRData,iAllocSize);
	ptrSNRData->hAndle = hAndle;
	ptrSNRData->callfunction = (void_pl *)ptrFunc;
	lua_pushcclosure(ptrState,(lua_CFunction)__Native_ScriptCallBack,1);
	if(ptrPackage != NULL_PL){
		lua_settable(ptrState,-3);
		lua_pop(ptrState,1);
	}else{
		lua_setglobal(ptrState,ptrScript);
	}
	hResult = HPLResult_OK;
	return hResult;
}
intV_pl Eg_RegisterScriptPackageFunc(PLScriptHandle hAndle,const_pl char_pl * ptrPackageName,intV_pl iPackageSize,PL_RegScriptLib * ptrScriptLib,intV_pl iCount){
	lua_State * ptrState;
	intV_pl     iRegisterCount;
	intV_pl     iAllocSize;
	int_pl 		iType;
	PL_ScriptNativeReg * ptrSNRData;
	iRegisterCount = 0;
	if((hAndle==NULL_PL) || (ptrPackageName==NULL_PL) || (iPackageSize<=0)
										|| (ptrScriptLib==NULL_PL) || (iCount<=0))
		return iRegisterCount;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	iAllocSize = PL_CompilerAllocSize(PL_ScriptNativeReg);
	lua_getglobal(ptrState,ptrPackageName);
	iType = lua_type(ptrState,-1);
	if(iType == LUA_TNIL){
		lua_pop(ptrState,1);
		lua_newtable(ptrState);
		lua_pushvalue(ptrState,-1);
		lua_setglobal(ptrState,ptrPackageName);
	}else if((iType != LUA_TNIL) && (iType != LUA_TTABLE)){
		lua_pop(ptrState,1);
		return iRegisterCount;
	}
	for(intV_pl iRegCount;iRegCount < iCount;iRegCount++){
		if(ptrScriptLib[iRegCount].ptrFuncName == NULL_PL)
			continue;
		lua_pushstring(ptrState,ptrScriptLib[iRegCount].ptrFuncName);
		ptrSNRData = (PL_ScriptNativeReg *)lua_newuserdata(ptrState,iAllocSize);
		if(ptrSNRData == NULL_PL){
			lua_pop(ptrState,1);
			break;
		}
		PLSysAPI_MemoryClearZero(ptrSNRData,iAllocSize);
		ptrSNRData->hAndle = hAndle;
		ptrSNRData->callfunction = ptrScriptLib[iRegCount].ptrFuncCall;
		lua_pushcclosure(ptrState,(lua_CFunction)__Native_ScriptCallBack,1);
		lua_settable(ptrState,-3);
		iRegisterCount++;
	}
	lua_pop(ptrState,1);
	return iRegisterCount;
}
HPL_Result Eg_CreateBuildScript(PLScriptHandle hAndle,const_pl char_pl * ptrScript,intV_pl iScriptSize,const_pl char_pl * pRegisterKey){
	HPL_Result hResult;
//	PLScriptCodeHandle hCodehAndle;
	lua_State * ptrState;
	PL_ScriptObject * ptrScriptObject;
	void_pl         * ptrConstCharRes;
	intV_pl           iConstCharResSize;
	int         iCode;
//	hCodehAndle = NULL_PL;
	hResult = HPLResult_Fail;
	do{
		if((hAndle == NULL_PL) || (ptrScript==NULL_PL) || (iScriptSize<=0))
			break;
		ptrScriptObject = (PL_ScriptObject *)hAndle;
		ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
		ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
														,PLScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
		lua_pushstring(ptrState,(char_pl *)ptrConstCharRes);
		lua_gettable(ptrState,LUA_REGISTRYINDEX);
		if(!(lua_istable(ptrState,-1))){
			lua_pop(ptrState,1);
			break;
		}
		lua_pushstring(ptrState,pRegisterKey);
		iCode = luaL_loadbuffer(ptrState,ptrScript,iScriptSize,NULL_PL);
		if(iCode != 0){
			lua_pop(ptrState,3);
			break;
		}
		lua_settable(ptrState,-3);
		lua_pop(ptrState,1);
		hResult = HPLResult_OK;
	}while(0);
	return hResult;
}
HPL_Result Eg_ExecuteBuildScript(PLScriptHandle hAndle,const_pl char_pl * pRegisterKey){
	HPL_Result hResult;
	lua_State * ptrState;
	PL_ScriptObject * ptrScriptObject;
	void_pl         * ptrConstCharRes;
	intV_pl           iConstCharResSize;
	int         	  iCode;
	hResult = HPLResult_Fail;
	do{
		if((hAndle == NULL_PL) || (pRegisterKey == NULL_PL))
			break;
		ptrScriptObject = (PL_ScriptObject *)hAndle;
		ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
		ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
														,PLScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
		lua_pushstring(ptrState,(char_pl *)ptrConstCharRes);
		lua_gettable(ptrState,LUA_REGISTRYINDEX);
		if(!(lua_istable(ptrState,-1))){
			lua_pop(ptrState,1);
			break;
		}
		lua_pushstring(ptrState,pRegisterKey);
		lua_gettable(ptrState,-2);
		iCode = lua_pcall(ptrState,0,0,0);
		if(iCode!=0){
			lua_pop(ptrState,2);
			break;
		}
		lua_pop(ptrState,1);

		hResult = HPLResult_OK;
	}while(0);
	return hResult;
}
HPL_Result Eg_ExecuteBuildNativeFuncScript(PLScriptHandle hAndle,PL_ScriptNativeFuncParamer * ptrSNFP,const_pl char_pl * pRegisterKey){
	HPL_Result hResult;
	lua_State * ptrState;
	int_pl      iType;
	hResult = HPLResult_Fail;
	do{
		ptrState = ((PL_ScriptObject *)hAndle)->ptrState;;
		if((pRegisterKey == NULL_PL))
			break;
		lua_getglobal(ptrState,ptrSNFP->ptrFuncName);
		iType = lua_type(ptrState,-1);
		if(LUA_TFUNCTION != iType){
			lua_pop(ptrState,1);
			break;
		}
		if(ptrSNFP->iInputParamerCount>0)
			lua_insert(ptrState,-(ptrSNFP->iInputParamerCount + 2));
		if(lua_pcall(ptrState,ptrSNFP->iInputParamerCount,ptrSNFP->iResultParamerCount,0) != 0){
			lua_pop(ptrState,1);
			break;
		}
		hResult = HPLResult_OK;
	}while(0);
	return hResult;
}
void_pl Eg_ReleaseBuildScript(PLScriptHandle hAndle,const_pl char_pl * pRegisterKey){
	lua_State * ptrState;
	PL_ScriptObject * ptrScriptObject;
	void_pl         * ptrConstCharRes;
	intV_pl           iConstCharResSize;

	if((hAndle == NULL_PL) || (pRegisterKey == NULL_PL))
		return;
	ptrScriptObject = (PL_ScriptObject *)hAndle;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
													,PLScript_ConstID_RegisterScriptChunkID,&iConstCharResSize);
	lua_pushstring(ptrState,(char_pl *)ptrConstCharRes);
	lua_gettable(ptrState,LUA_REGISTRYINDEX);
	if(!(lua_istable(ptrState,-1))){
		lua_pop(ptrState,1);
		return;
	}
	lua_pushstring(ptrState,pRegisterKey);
	lua_pushnil(ptrState);
	lua_settable(ptrState,-3);
	lua_pop(ptrState,1);
}
PLScriptUDMHandle Eg_AllocCScriptSpaceMemory(PLScriptHandle hAndle,intV_pl iSize){
	PLScriptUDMHandle hMem;
	lua_State * ptrState;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_newuserdata(ptrState,iSize);
	hMem = (PLScriptUDMHandle)luaL_ref(ptrState,LUA_REGISTRYINDEX);
	return hMem;
}
void_pl * Eg_GetCScriptSpaceMemoryPointer(PLScriptHandle hAndle,PLScriptUDMHandle hMem){
	void_pl * ptrPointer;
	lua_State * ptrState;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_rawgeti(ptrState,LUA_REGISTRYINDEX,(int_pl)hMem);
	ptrPointer = (void_pl *)lua_touserdata(ptrState,-1);
	lua_pop(ptrState,1);
	return ptrPointer;
}
void_pl Eg_FreeCScriptSpaceMemory(PLScriptHandle hAndle,PLScriptUDMHandle hMem){
	luaL_unref(((PL_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,(int_pl)hMem);
}
HPL_Result Eg_ExecuteStringScript(PLScriptHandle hAndle,const_pl char_pl * ptrScript,intV_pl iScriptSize){
	HPL_Result hResult;
	lua_State * ptrState;
	PL_ScriptObject * ptrScriptObject;
	void_pl         * ptrConstCharRes;
	intV_pl           iConstCharResSize;
	int         iCode;
	hResult = HPLResult_Fail;
	do{
		if((hAndle == NULL_PL) || (ptrScript == NULL_PL) || (iScriptSize<=0))
			break;
		ptrScriptObject = (PL_ScriptObject *)hAndle;
		ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
		ptrConstCharRes = PLSysAPI_Sys_GetConstCharID(ptrScriptObject->hSysConstCharTable
														,PLScript_ConstID_BuildFormat_Line,&iConstCharResSize);
		iCode = luaL_loadbuffer(ptrState,ptrScript,iScriptSize,(const_pl char_pl *)ptrConstCharRes);
		if(iCode != 0){
			lua_pop(ptrState,1);
			break;
		}
		if(lua_pcall(ptrState,0,0,0) != 0){
			lua_pop(ptrState,1);
			break;
		}
		hResult = HPLResult_OK;
	}while(0);
	return hResult;
}
HPL_Result Eg_ExecuteScript(PLScriptHandle hAndle,PLScriptCodeHandle hCodeHandle){
	HPL_Result hResult;
	hResult = HPLResult_Fail;
	do{
		if((hAndle == NULL_PL) || (hCodeHandle == NULL_PL))
			break;

	}while(0);
	return hResult;
}
void_pl  Eg_CloseScript(PLScriptHandle hAndle){
	lua_State * ptrState;
	PL_ScriptObject * ptrScriptObject;
	if(hAndle == NULL_PL)
		return;
	ptrScriptObject = (PL_ScriptObject *)hAndle;
	ptrState = ptrScriptObject->ptrState;
	lua_close(ptrState);
	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrScriptObject);
//	PLSysAPI_FreeMemory(ptrScriptObject->ptrMem);
}
int __OpenCall(lua_State * ptrState){
	return 0;
}
int_pl __Native_ScriptCallBack(PLScriptStateHandle hState){
	lua_State * ptrState;
	PL_ScriptNativeReg * ptrSNRData;
	ptrState = (lua_State *)hState;
	ptrSNRData = (PL_ScriptNativeReg *)lua_touserdata(ptrState,lua_upvalueindex(1));
	return ((__PL_ScriptFunc_CallBack)(ptrSNRData->callfunction))(ptrSNRData->hAndle);
}
