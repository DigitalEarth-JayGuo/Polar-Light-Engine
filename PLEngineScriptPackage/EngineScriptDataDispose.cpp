/*
 * EngineScriptDataDispose.cpp
 *
 *  Created on: 2009-8-25
 *      Author: Administrator
 */
#include "EngineScriptDataDispose.h"

HPL_Result Eg_PushInt32(PLScriptHandle hAndle,int32_pl iValue){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushinteger(((PL_ScriptObject *)hAndle)->ptrState,iValue);
	return hResult;
}
int32_pl Eg_PopInt32(PLScriptHandle hAndle){
	int32_pl iValue;
	iValue = (int32_pl)lua_tointeger(((PL_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((PL_ScriptObject *)hAndle)->ptrState,1);
	return iValue;
}
HPL_Result Eg_PushIntV(PLScriptHandle hAndle,intV_pl iValue){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushinteger(((PL_ScriptObject *)hAndle)->ptrState,iValue);
	return hResult;
}
intV_pl Eg_PopIntV(PLScriptHandle hAndle){
	intV_pl iValue;
	iValue = (intV_pl)lua_tointeger(((PL_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((PL_ScriptObject *)hAndle)->ptrState,1);
	return iValue;
}
HPL_Result Eg_PushString(PLScriptHandle hAndle,const_pl char_pl * ptrString,intV_pl iSize){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushstring(((PL_ScriptObject *)hAndle)->ptrState,ptrString);
	return hResult;
}
intV_pl Eg_PopString(PLScriptHandle hAndle,char_pl * ptrString,intV_pl iMaxSize){
	intV_pl iStrLen;
	lua_State * ptrState;
	const_pl char_pl * ptrSrc;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	iStrLen = (intV_pl)lua_strlen(ptrState,-1);
	if(iStrLen > iMaxSize)
		iStrLen = iMaxSize;
	ptrSrc  = lua_tostring(ptrState,-1);
	PLSysAPI_MemoryCpy(ptrString,ptrSrc,iStrLen);
	lua_pop(ptrState,1);
	return iStrLen;
}
HPL_Result Eg_PushBool(PLScriptHandle hAndle,bool_pl bTure){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushboolean(((PL_ScriptObject *)hAndle)->ptrState,bTure==true_pl ? 1 : 0);
	return hResult;
}
bool_pl Eg_PopBool(PLScriptHandle hAndle){
	bool_pl bValue;
	bValue = lua_toboolean(((PL_ScriptObject *)hAndle)->ptrState,-1) == 0 ? false_pl : true_pl;
	lua_pop((lua_State *)hAndle,1);
	return bValue;
}
HPL_Result Eg_PushPointer(PLScriptHandle hAndle,void_pl * ptrPointer){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushlightuserdata(((PL_ScriptObject *)hAndle)->ptrState,ptrPointer);
	return hResult;
}
void_pl * Eg_PopPointer(PLScriptHandle hAndle){
	void_pl * ptrPointer;
	ptrPointer = (void_pl *)lua_topointer(((PL_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((PL_ScriptObject *)hAndle)->ptrState,1);
	return ptrPointer;
}
HPL_Result Eg_PushDouble(PLScriptHandle hAndle,double_pl fValue){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushnumber(((PL_ScriptObject *)hAndle)->ptrState,fValue);
	return hResult;
}
double_pl Eg_PopDouble(PLScriptHandle hAndle){
	double_pl fValue;
	fValue = lua_tonumber(((PL_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((PL_ScriptObject *)hAndle)->ptrState,1);
	return fValue;
}
HPL_Result Eg_PushFloat(PLScriptHandle hAndle,float_pl fValue){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushinteger(((PL_ScriptObject *)hAndle)->ptrState,*((int32_pl *)(&fValue)));
	return hResult;
}
float_pl Eg_PopFloat(PLScriptHandle hAndle){
	int32_pl iValue;
	iValue = lua_tointeger(((PL_ScriptObject *)hAndle)->ptrState,-1);
	lua_pop(((PL_ScriptObject *)hAndle)->ptrState,1);

	return *((float_pl *)(&iValue));
}
void_pl Eg_Pop(PLScriptHandle hAndle){
	lua_pop(((PL_ScriptObject *)hAndle)->ptrState,1);
}
HPL_Result Eg_CopyStackData(PLScriptHandle hAndle,intV_pl iIndex){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_pushvalue(((PL_ScriptObject *)hAndle)->ptrState,-iIndex);
	return hResult;
}
HPL_Result Eg_MoveStackData(PLScriptHandle hAndle,intV_pl iIndex){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_insert(((PL_ScriptObject *)hAndle)->ptrState,(int_pl)(-iIndex));
	return hResult;
}
HPL_Result Eg_RemoveStackData(PLScriptHandle hAndle,intV_pl iIndex){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_remove(((PL_ScriptObject *)hAndle)->ptrState,(int_pl)(-iIndex));
	return hResult;
}
HPL_Result Eg_ReplaceStackData(PLScriptHandle hAndle,intV_pl iIndex){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_replace(((PL_ScriptObject *)hAndle)->ptrState,(int_pl)(-iIndex));
	return hResult;
}

HPL_Result Eg_PushGTable(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	HPL_Result hResult;
	lua_State * ptrState;
	hResult = HPLResult_OK;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_getglobal(ptrState,ptrName);
	if(lua_type(ptrState,-1) !=  LUA_TTABLE){
		hResult = HPLResult_Fail;
		lua_pop(ptrState,1);
	}
	return hResult;
}
HPL_Result Eg_PushCTable(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	HPL_Result hResult;
	lua_State * ptrState;
	hResult = HPLResult_OK;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,LUA_REGISTRYINDEX,ptrName);
	if(lua_type(ptrState,-1) != LUA_TTABLE){
		hResult = HPLResult_Fail;
		lua_pop(ptrState,1);
	}
	return hResult;
}
HPL_Result Eg_PushTable(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize){
	HPL_Result hResult;
	lua_State * ptrState;
	hResult = HPLResult_OK;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,-iIndex,ptrName);
	if(lua_type(ptrState,-1) != LUA_TTABLE){
		hResult = HPLResult_Fail;
		lua_pop(ptrState,1);
	}
	return hResult;
}
HPL_Result Eg_PushNewTable(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	HPL_Result hResult;
	hResult = HPLResult_OK;
	lua_newtable(((PL_ScriptObject *)hAndle)->ptrState);
	return hResult;
}
void_pl Eg_SetGlobalValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	lua_setglobal(((PL_ScriptObject *)hAndle)->ptrState,ptrName);
}
HPL_Result Eg_GetGlobalValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	lua_getglobal(((PL_ScriptObject *)hAndle)->ptrState,ptrName);
	return HPLResult_OK;
}
void_pl Eg_SetGlobalValueI(PLScriptHandle hAndle,intV_pl iIndex){
	lua_rawseti(((PL_ScriptObject *)hAndle)->ptrState,LUA_GLOBALSINDEX,iIndex);
}
HPL_Result Eg_GetGlobalValueI(PLScriptHandle hAndle,intV_pl iIndex){
	lua_rawgeti(((PL_ScriptObject *)hAndle)->ptrState,LUA_GLOBALSINDEX,iIndex);
	return HPLResult_OK;
}
intV_pl Eg_GetGlobalSize(PLScriptHandle hAndle,intV_pl iIndex){
	return (intV_pl)luaL_getn(((PL_ScriptObject *)hAndle)->ptrState,LUA_GLOBALSINDEX);
}
void_pl Eg_SetRegisterValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	lua_setfield(((PL_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,ptrName);
}
HPL_Result Eg_GetRegisterValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	lua_getfield(((PL_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,ptrName);
	return HPLResult_OK;
}
void_pl Eg_SetRegisterValueI(PLScriptHandle hAndle,intV_pl iIndex){
	lua_rawseti(((PL_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,iIndex);
}
HPL_Result Eg_GetRegisterValueI(PLScriptHandle hAndle,intV_pl iIndex){
	lua_rawgeti(((PL_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX,iIndex);
	return HPLResult_OK;
}
intV_pl Eg_GetRegisterSize(PLScriptHandle hAndle,intV_pl iIndex){
	return (intV_pl)luaL_getn(((PL_ScriptObject *)hAndle)->ptrState,LUA_REGISTRYINDEX);
}
void_pl Eg_SetTableValue(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize){
	lua_setfield(((PL_ScriptObject *)hAndle)->ptrState,-iIndex,ptrName);
}
HPL_Result Eg_GetTableValue(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize){
	lua_getfield(((PL_ScriptObject *)hAndle)->ptrState,-iIndex,ptrName);
	return HPLResult_OK;
}
void_pl Eg_SetTableValueI(PLScriptHandle hAndle,intV_pl iIndex,intV_pl iTIndex){
	lua_rawseti(((PL_ScriptObject *)hAndle)->ptrState,iIndex,iTIndex);
}
HPL_Result Eg_GetTableValueI(PLScriptHandle hAndle,intV_pl iIndex,intV_pl iTIndex){
	lua_rawgeti(((PL_ScriptObject *)hAndle)->ptrState,iIndex,iTIndex);
	return HPLResult_OK;
}
intV_pl Eg_GetTableSize(PLScriptHandle hAndle,intV_pl iIndex){
	return (intV_pl)luaL_getn(((PL_ScriptObject *)hAndle)->ptrState,-iIndex);
}
bool_pl Eg_isGlobalValueNull(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	bool_pl bisNull;
	lua_State * ptrState;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_getglobal(ptrState,ptrName);
	bisNull = (lua_type(ptrState,-1) != LUA_TNIL) ? false_pl : true_pl;
	lua_pop(ptrState,1);
	return bisNull;
}
bool_pl Eg_isRegisterValueNull(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize){
	bool_pl bisNull;
	lua_State * ptrState;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,LUA_REGISTRYINDEX,ptrName);
	bisNull = (lua_type(ptrState,-1) != LUA_TNIL) ? false_pl : true_pl;
	lua_pop(ptrState,1);
	return bisNull;
}
bool_pl Eg_isTableValueNull(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize){
	bool_pl bisNull;
	lua_State * ptrState;
	ptrState = ((PL_ScriptObject *)hAndle)->ptrState;
	lua_getfield(ptrState,-iIndex,ptrName);
	bisNull = (lua_type(ptrState,-1) != LUA_TNIL) ? false_pl : true_pl;
	lua_pop(ptrState,1);
	return bisNull;
}
intV_pl Eg_GetStackElementCount(PLScriptHandle hAndle){
	return (intV_pl)(lua_gettop(((PL_ScriptObject *)hAndle)->ptrState));
}

