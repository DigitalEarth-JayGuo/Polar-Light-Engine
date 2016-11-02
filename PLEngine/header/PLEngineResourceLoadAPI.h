/*
 * PLEngineResourceLoadAPI.h
 *
 *  Created on: 2009-9-16+
 *      Author: Administrator
 */
#include "PLEngineH.h"
#include "PLEngineBaseDataType.h"
#include "PLEngineSysAPI.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"

#ifndef PLENGINERESOURCELOADAPI_H_
#define PLENGINERESOURCELOADAPI_H_

	typedef _CallStack_default_ HPKGObjAndle        (* __Rc_CreatePackage__PL__)            (const_pl UTFSyschar_pl *,intV_pl,intV_pl,intV_pl);
	typedef _CallStack_default_ HPKGObjAndle        (* __Rc_OpenPackage__PL__)				(const_pl UTFSyschar_pl *,intV_pl,intV_pl);
	typedef _CallStack_default_ HPL_Result			(* __Rc_LoadPackageFTable__PL__)		(HPKGObjAndle);
	typedef _CallStack_default_ HPL_Result			(* __Rc_CreatePackageFTFindMap__PL__)	(HPKGObjAndle);
	typedef _CallStack_default_ bool_pl				(* __Rc_existPackageFTable__PL__)		(HPKGObjAndle);
	typedef _CallStack_default_ bool_pl				(* __Rc_existPackageFTFindMap__PL__)	(HPKGObjAndle);
	typedef _CallStack_default_ intV_pl				(* __Rc_GetPackageFileItemResType__PL__)(HPKGFileItemAndle);
	typedef _CallStack_default_	intV_pl             (* __Rc_GetPackageFileItemName__PL__)   (HPKGFileItemAndle,const_pl UTFSyschar_pl **);
	typedef _CallStack_default_ intV_pl				(* __Rc_ReadPackageFileItemData__PL__)  (HPKGFileItemAndle,void_pl *,intV_pl,intV_pl);
	typedef _CallStack_default_	int64_pl            (* __Rc_GetPackageFileSize__PL__)       (HPKGObjAndle);
	typedef _CallStack_default_	HPKGFileItemAndle   (* __Rc_GetPackageFileItemObject__PL__) (HPKGObjAndle,const_pl UTFSyschar_pl *,intV_pl);
	typedef _CallStack_default_	HPKGFileItemAndle   (* __Rc_GetPackageFileItemObjectI__PL__)(HPKGObjAndle,intV_pl);
	typedef _CallStack_default_	intV_pl             (* __Rc_GetPackageFileItemCount__PL__)  (HPKGObjAndle);
	typedef _CallStack_default_	intV_pl             (* __Rc_GetPackageFileItemSize__PL__)	(HPKGFileItemAndle);
	typedef _CallStack_default_ void_pl		        (* __Rc_ClosePackage__PL__)				(HPKGObjAndle);

	typedef _CallStack_default_ PL_ResDataSystemCrParamer * (* __Rc_CreateResDataSystemCrParamer__PL__)  		();
	typedef _CallStack_default_ void_pl						(* __Rc_DestoryResDataSystemCrParamer__PL__) 		(PL_ResDataSystemCrParamer *);
	typedef _CallStack_default_ HResDataSystem 				(* __Rc_CreateResourceDataSystem__PL__)		 		(PL_ResDataSystemCrParamer *);
	typedef _CallStack_default_ HResDataPKGMMAndle		    (* __Rc_CreateResourceDataSystemPKGMapping__PL__)   (HResDataSystem,const_pl char_pl * ,intV_pl,intV_pl);
	typedef _CallStack_default_ HPL_Result					(* __Rc_ReleaseResourceDataSystemPKGMapping__PL__)	(HResDataPKGMMAndle);
	typedef _CallStack_default_ HPL_Result					(* __Rc_ReleaseResourceDataSystemPKGMappingN__PL__)	(HResDataSystem,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ HPL_Result					(* __Rc_MappinResourceDataSystemPKG__PL__)			(HResDataSystem,HResDataPKGMMAndle);
	typedef _CallStack_default_ HPL_Result					(* __Rc_MappingResourceDataSystemPKGItem__PL__)		(HResDataSystem,HResDataPKGMMAndle,intV_pl);
	typedef _CallStack_default_ HPL_Result					(* __Rc_RefurbishResourceDataMgrSystem__PL__)		(HResDataSystem);
	typedef _CallStack_default_ void_pl						(* __Rc_DestoryResourceDataSystem__PL__)			(HResDataSystem);
	typedef _CallStack_default_ HResDataItemAndle			(* __Rc_OpenResourceDataItem__PL__)					(HResDataSystem,intV_pl,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ void_pl						(* __Rc_CloseResourceDataItem__PL__)				(HResDataItemAndle);

	_PLE_lib_Variable __Rc_CreatePackage__PL__   				PLSysAPI_RC_CreatePackage;
	_PLE_lib_Variable __Rc_OpenPackage__PL__  	 				PLSysAPI_RC_OpenPackage;
	_PLE_lib_Variable __Rc_LoadPackageFTable__PL__ 				PLSysAPI_RC_LoadPackageFTable;
	_PLE_lib_Variable __Rc_CreatePackageFTFindMap__PL__ 		PLSysAPI_RC_CreatePackageFTFindMap;
	_PLE_lib_Variable __Rc_existPackageFTable__PL__ 			PLSysAPI_RC_existPackageFTable;
	_PLE_lib_Variable __Rc_existPackageFTFindMap__PL__ 			PLSysAPI_RC_existPackageFTFindMap;
	_PLE_lib_Variable __Rc_GetPackageFileItemResType__PL__		PLSysAPI_RC_GetPackageFileItemResType;
	_PLE_lib_Variable __Rc_GetPackageFileItemName__PL__			PLSysAPI_RC_GetPackageFileItemName;
	_PLE_lib_Variable __Rc_ReadPackageFileItemData__PL__		PLSysAPI_RC_ReadPackageFileItemData;
	_PLE_lib_Variable __Rc_GetPackageFileSize__PL__				PLSysAPI_RC_GetPackageFileSize;
	_PLE_lib_Variable __Rc_GetPackageFileItemObject__PL__		PLSysAPI_RC_GetPackageFileItemObject;
	_PLE_lib_Variable __Rc_GetPackageFileItemObjectI__PL__		PLSysAPI_RC_GetPackageFileItemObjectI;
	_PLE_lib_Variable __Rc_GetPackageFileItemCount__PL__    	PLSysAPI_RC_GetPackageFileItemCount;
	_PLE_lib_Variable __Rc_GetPackageFileItemSize__PL__         PLSysAPI_RC_GetPackageFileItemSize;
	_PLE_lib_Variable __Rc_ClosePackage__PL__  	 				PLSysAPI_RC_ClosePackage;

	_PLE_lib_Variable __Rc_CreateResDataSystemCrParamer__PL__   		PLSysAPI_RC_CreateResDataSystemCrParamer;
	_PLE_lib_Variable __Rc_DestoryResDataSystemCrParamer__PL__  		PLSysAPI_RC_DestoryResDataSystemCrParamer;
	_PLE_lib_Variable __Rc_CreateResourceDataSystem__PL__				PLSysAPI_RC_CreateResourceDataSystem;
	_PLE_lib_Variable __Rc_CreateResourceDataSystemPKGMapping__PL__		PLSysAPI_RC_CreateResourceDataSystemPKGMapping;
	_PLE_lib_Variable __Rc_ReleaseResourceDataSystemPKGMapping__PL__	PLSysAPI_RC_ReleaseResourceDataSystemPKGMapping;
	_PLE_lib_Variable __Rc_ReleaseResourceDataSystemPKGMappingN__PL__	PLSysAPI_RC_ReleaseResourceDataSystemPKGMappingN;
	_PLE_lib_Variable __Rc_MappinResourceDataSystemPKG__PL__			PLSysAPI_RC_MappinResourceDataSystemPKG;
	_PLE_lib_Variable __Rc_MappingResourceDataSystemPKGItem__PL__		PLSysAPI_RC_MappingResourceDataSystemPKGItem;
	_PLE_lib_Variable __Rc_RefurbishResourceDataMgrSystem__PL__			PLSysAPI_RC_RefurbishResourceDataMgrSystem;
	_PLE_lib_Variable __Rc_DestoryResourceDataSystem__PL__				PLSysAPI_RC_DestoryResourceDataSystem;
	_PLE_lib_Variable __Rc_OpenResourceDataItem__PL__					PLSysAPI_RC_OpenResourceDataItem;
	_PLE_lib_Variable __Rc_CloseResourceDataItem__PL__					PLSysAPI_RC_CloseResourceDataItem;


#endif /* PLENGINERESOURCELOADAPI_H_ */
