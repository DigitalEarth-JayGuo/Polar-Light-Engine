/*
 * EngineScriptDataDispose.h
 *
 *  Created on: 2009-8-25
 *      Author: Administrator
 */
#include "PLEngineScriptPKH.h"
#include "EngineScriptInface.h"
#ifndef ENGINESCRIPTDATADISPOSE_H_
#define ENGINESCRIPTDATADISPOSE_H_

	_CallStack_default_ HPL_Result          Eg_PushInt32(PLScriptHandle hAndle,int32_pl iValue);
	_CallStack_default_ int32_pl            Eg_PopInt32(PLScriptHandle hAndle);
	_CallStack_default_ HPL_Result          Eg_PushIntV(PLScriptHandle hAndle,intV_pl iValue);
	_CallStack_default_ intV_pl             Eg_PopIntV(PLScriptHandle hAndle);
	_CallStack_default_ HPL_Result          Eg_PushString(PLScriptHandle hAndle,const_pl char_pl * ptrString,intV_pl iSize);
	_CallStack_default_ intV_pl             Eg_PopString(PLScriptHandle hAndle,char_pl * ptrString,intV_pl iMaxSize);
	_CallStack_default_ HPL_Result          Eg_PushBool(PLScriptHandle hAndle,bool_pl bTure);
	_CallStack_default_ bool_pl             Eg_PopBool(PLScriptHandle hAndle);
	_CallStack_default_ HPL_Result          Eg_PushDouble(PLScriptHandle hAndle,double_pl fValue);
	_CallStack_default_ double_pl           Eg_PopDouble(PLScriptHandle hAndle);
	_CallStack_default_ HPL_Result          Eg_PushFloat(PLScriptHandle hAndle,float_pl fValue);
	_CallStack_default_ float_pl            Eg_PopFloat(PLScriptHandle hAndle);
	_CallStack_default_ HPL_Result          Eg_PushPointer(PLScriptHandle hAndle,void_pl * ptrPointer);
	_CallStack_default_ void_pl *           Eg_PopPointer(PLScriptHandle hAndle);
	_CallStack_default_ void_pl             Eg_Pop(PLScriptHandle hAndle);



	_CallStack_default_ HPL_Result          Eg_CopyStackData(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ HPL_Result          Eg_MoveStackData(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ HPL_Result          Eg_RemoveStackData(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ HPL_Result          Eg_ReplaceStackData(PLScriptHandle hAndle,intV_pl iIndex);

	//Get global table's elment data(must is table type) and push stacktop
	_CallStack_default_ HPL_Result          Eg_PushGTable(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	//Get register table's elment data(must is table type) and push tacktop
	_CallStack_default_ HPL_Result          Eg_PushCTable(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ HPL_Result          Eg_PushTable(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ HPL_Result          Eg_PushNewTable(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	//Get Stack Element Count
	_CallStack_default_ intV_pl             Eg_GetStackElementCount(PLScriptHandle hAndle);

	_CallStack_default_ void_pl             Eg_SetGlobalValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ HPL_Result          Eg_GetGlobalValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ void_pl             Eg_SetGlobalValueI(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ HPL_Result          Eg_GetGlobalValueI(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ intV_pl             Eg_GetGlobalSize(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ void_pl             Eg_SetRegisterValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ HPL_Result          Eg_GetRegisterValue(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ void_pl             Eg_SetRegisterValueI(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ HPL_Result          Eg_GetRegisterValueI(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ intV_pl             Eg_GetRegisterSize(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ void_pl             Eg_SetTableValue(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ HPL_Result          Eg_GetTableValue(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ void_pl             Eg_SetTableValueI(PLScriptHandle hAndle,intV_pl iIndex,intV_pl iTIndex);
	_CallStack_default_ HPL_Result          Eg_GetTableValueI(PLScriptHandle hAndle,intV_pl iIndex,intV_pl iTIndex);
	_CallStack_default_ intV_pl             Eg_GetTableSize(PLScriptHandle hAndle,intV_pl iIndex);
	_CallStack_default_ bool_pl          	Eg_isGlobalValueNull(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ bool_pl             Eg_isRegisterValueNull(PLScriptHandle hAndle,const_pl char_pl * ptrName,intV_pl iSize);
	_CallStack_default_ bool_pl             Eg_isTableValueNull(PLScriptHandle hAndle,intV_pl iIndex,const_pl char_pl * ptrName,intV_pl iSize);
	//  LUA_GLOBALSINDEX
//lua_setfield
//lua_getfield
#endif /* ENGINESCRIPTDATADISPOSE_H_ */
