/*
 * PLEngineResourceManagerAPI.h
 *
 *  Created on: 2009-10-23
 *      Author: Administrator
 */
#include "PLEngineH.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineSysAPI.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#include "PLEngineResourceLoadAPI.h"
#ifndef PLENGINERESOURCEMANAGERAPI_H_
#define PLENGINERESOURCEMANAGERAPI_H_
	typedef _CallStack_default_ HPolygonMgrAndle        (* __RMgr__CreatePolygonManager__PL__)      		(HResDataSystem hRDSystem);
	typedef _CallStack_default_ void_pl      			(* __RMgr__DestoryPolygonManager__PL__)     		(HPolygonMgrAndle);
	typedef _CallStack_default_ PL_ResourcePolygon *    (* __RMgr__CreatePolygonMgrObject__PL__)  			(HPolygonMgrAndle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ PL_ResourcePolygon *    (* __RMgr__OpenPolygonMgrObject__PL__)				(HPolygonMgrAndle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result			    (* __RMgr__ReleasePolygonMgrObject__PL__)			(PL_ResourcePolygon *);
	typedef _CallStack_default_ HPL_Result			    (* __RMgr__DestoryPolygonMgrObject__PL__) 			(HPolygonMgrAndle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_	HPL_Result              (* __RMgr__PushPolygonRTaskerQueue__PL__)			(PL_ResourcePolygon *);
	typedef _CallStack_default_	HPL_Result              (* __RMgr__PushPolygonRTaskerQueueFill__PL__)		(PL_ResourcePolygon *,PL_CommResourceBlock *);
	typedef _CallStack_default_	HPL_Result              (* __RMgr__PushPolygonRTaskerQueueN__PL__)			(HPolygonMgrAndle,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_	HPL_Result              (* __RMgr__PushPolygonRTaskerQueueNFill__PL__)		(HPolygonMgrAndle,const_pl char_pl *,intV_pl,PL_CommResourceBlock *);
	typedef _CallStack_default_ HPL_Result              (* __RMgr__RefurbishPolygonRBackgroundDispose__PL__)(HPolygonMgrAndle,PL_ResourceBgDisposeParamer *);


	typedef _CallStack_default_ HTextureMgrAndle        (* __RMgr_CreateTextureManager__PL__)		(HResDataSystem hRDSystem);
	typedef _CallStack_default_ void_pl        			(* __RMgr_DestoryTextureManager__PL__)		(HTextureMgrAndle);



	typedef _CallStack_default_ HScriptMgrAndle			(* __RMgr_CreateScriptManager__PL__)		(HResDataSystem hRDSystem);
	typedef _CallStack_default_ void_pl					(* __RMgr_DestoryScriptManager__PL__)		(HScriptMgrAndle);



	_PLE_lib_Variable __RMgr__CreatePolygonManager__PL__   				PLSysAPI_RMgr_CreatePolygonManager;
	_PLE_lib_Variable __RMgr__DestoryPolygonManager__PL__   			PLSysAPI_RMgr_DestoryPolygonManager;
	_PLE_lib_Variable __RMgr__CreatePolygonMgrObject__PL__				PLSysAPI_RMgr_CreatePolygonMgrObject;
	_PLE_lib_Variable __RMgr__OpenPolygonMgrObject__PL__				PLSysAPI_RMgr_OpenPolygonMgrObject;
	_PLE_lib_Variable __RMgr__ReleasePolygonMgrObject__PL__				PLSysAPI_RMgr_ReleasePolygonMgrObject;
	_PLE_lib_Variable __RMgr__DestoryPolygonMgrObject__PL__		   	    PLSysAPI_RMgr_DestoryPolygonMgrObject;
	_PLE_lib_Variable __RMgr__PushPolygonRTaskerQueue__PL__				PLSysAPI_RMgr_PushPolygonRTaskerQueue;
	_PLE_lib_Variable __RMgr__PushPolygonRTaskerQueueFill__PL__			PLSysAPI_RMgr_PushPolygonRTaskerQueueFill;
	_PLE_lib_Variable __RMgr__PushPolygonRTaskerQueueN__PL__			PLSysAPI_RMgr_PushPolygonRTaskerQueueN;
	_PLE_lib_Variable __RMgr__PushPolygonRTaskerQueueNFill__PL__		PLSysAPI_RMgr_PushPolygonRTaskerQueueNFill;
	_PLE_lib_Variable __RMgr__RefurbishPolygonRBackgroundDispose__PL__  PLSysAPI_RMgr_RefurbishPolygonRBgDispose;




	_PLE_lib_Variable __RMgr_CreateTextureManager__PL__   				PLSysAPI_RMgr_CreateTextureManager;
	_PLE_lib_Variable __RMgr_DestoryTextureManager__PL__   				PLSysAPI_RMgr_DestoryTextureManager;


	_PLE_lib_Variable __RMgr_CreateScriptManager__PL__   				PLSysAPI_RMgr_CreateScriptManager;
	_PLE_lib_Variable __RMgr_DestoryScriptManager__PL__   				PLSysAPI_RMgr_DestoryScriptManager;

#endif /* PLENGINERESOURCEMANAGERAPI_H_ */
