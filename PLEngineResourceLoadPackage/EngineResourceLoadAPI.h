/*
 * EngineResourceLoadAPI.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "PLEngineResourceLoadPKH.h"
#include "EngineResourceLoadInface.h"
#ifndef ENGINERESOURCELOADAPI_H_
#define ENGINERESOURCELOADAPI_H_
	extern PLLibraryHandle g_hLibraryHandle_Resource;
	#define PLRL_Maroc_ConverTypeItemToMgr(iSType) __native_Eg_ConverItemTypeToMgrType(iSType)
	_CallStack_default_ PLLibraryHandle     	Eg_GetLibraryHandle_global();

	_CallStack_default_ HPKGObjAndle            Eg_CreatePackage(const_pl char_pl * ptrKey,intV_pl iKeySize,intV_pl iMode,intV_pl iStoreMode);
	_CallStack_default_ HPKGObjAndle 			Eg_OpenPackage(const_pl char_pl * ptrKey,intV_pl iKeySize,intV_pl iMode);
	_CallStack_default_ HPL_Result	            Eg_LoadPackageFTable(HPKGObjAndle hAndle);
	_CallStack_default_ HPL_Result              Eg_CreatePackageFTFindMap(HPKGObjAndle hAndle);
	_CallStack_default_ bool_pl                 Eg_existPackageFTable(HPKGObjAndle hAndle);
	_CallStack_default_ bool_pl                 Eg_existPackageFTFindMap(HPKGObjAndle hAndle);
	_CallStack_default_ int64_pl                Eg_GetPackageFileSize(HPKGObjAndle hAndle);
	_CallStack_default_ HPKGFileItemAndle       Eg_GetPackageFileItemObject(HPKGObjAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ intV_pl                 Eg_GetPackageFileItemCount(HPKGObjAndle hAndle);
	_CallStack_default_ HPKGFileItemAndle       Eg_GetPackageFileItemObjectI(HPKGObjAndle hAndle,intV_pl iIndex);
	_CallStack_default_ intV_pl                 Eg_GetPackageFileItemSize(HPKGFileItemAndle hAndle);
	_CallStack_default_ intV_pl                 Eg_GetPackageFileItemResType(HPKGFileItemAndle hAndle);
	_CallStack_default_ intV_pl					Eg_GetPackageFileItemName(HPKGFileItemAndle hAndle,const_pl char_pl ** ppBuf);
	_CallStack_default_ intV_pl                 Eg_ReadPackageFileItemData(HPKGFileItemAndle hAndle,void_pl * ptrData,intV_pl iBSize,intV_pl ioffset);
						intV_pl					__native_Eg_ReadFileItemData(HPKGFileItemAndle hAndle,void_pl * ptrData,intV_pl iBSize,intV_pl ioffset);
	_CallStack_default_ void_pl 				Eg_ClosePackage(HPKGObjAndle hAndle);
						ePL_ResourceDataMgrType __native_Eg_ConverItemTypeToMgrType(intV_pl iSpecificType);
	/*********Begin Define Resource Data Manager*********/
	_CallStack_default_ PL_ResDataSystemCrParamer * Eg_CreateResDataSystemCrParamer();
	_CallStack_default_ void_pl						Eg_DestoryResDataSystemCrParamer(PL_ResDataSystemCrParamer * ptrParamer);
	_CallStack_default_ HResDataSystem          	Eg_CreateResourceDataSystem(PL_ResDataSystemCrParamer * ptrParamer);
	//PKG manager not Support multi-thread Sametime call
	_CallStack_default_ HResDataPKGMMAndle     		Eg_CreateResourceDataSystemPKGMapping(HResDataSystem hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,intV_pl iMapping);
	_CallStack_default_ HPL_Result                  Eg_ReleaseResourceDataSystemPKGMapping(HResDataPKGMMAndle hAndle);
	_CallStack_default_ HPL_Result                  Eg_ReleaseResourceDataSystemPKGMappingN(HResDataSystem hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result                  Eg_MappinResourceDataSystemPKG(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle);
	_CallStack_default_ HPL_Result                  Eg_MappingResourceDataSystemPKGItem(HResDataSystem hAndle,HResDataPKGMMAndle hMMAndle,intV_pl iIndex);
	_CallStack_default_ HPL_Result                  Eg_RefurbishResourceDataMgrSystem(HResDataSystem hAndle);
	_CallStack_default_ void_pl                     Eg_DestoryResourceDataSystem(HResDataSystem hAndle);
	_CallStack_default_ HResDataItemAndle           Eg_OpenResourceDataItem(HResDataSystem hAndle,intV_pl iSItemType,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ void_pl                     Eg_CloseResourceDataItem(HResDataItemAndle hAndle);
//	_CallStack_default_ HResDataItemAndle           Eg_CreateResourceDataItemUD(HResDataSystem hAndle,intV_pl iSItemType,const_pl char_pl * ptrName,intV_pl iSize,ePL_ResourceDataOperator eOpera);
//	_CallStack_default_ HPL_Result                  Eg_ReleaseResourceDataItemUD(HResDataSystem hAndle,HResDataItemAndle hItemAndle);
	//_CallStack_default_ HResDataItemAndle           Eg_GetResDataItem(HResDataSystem hAndle,ePL_ResourceDataMgrType eMgr,const_pl char_pl * ptrKey,intV_pl iKeySize);

//	_CallStack_default_
	//HResDataItemAndle
	/*********End Define Resource Data Manager *********/

	_CallStack_default_ HPKGTaskersObjAndle 	Eg_CreatePackageTaskersObject();
	_CallStack_default_ void_pl                 Eg_RefurbishPackageTaskers(HPKGTaskersObjAndle hAndle);
	_CallStack_default_ void_pl                 Eg_DestoryPackageTaskersObject(HPKGTaskersObjAndle hAndle);



	/*********Begin Define Resource Object Manager Module API**********/
//	_CallStack_default_ void_pl * 			    Eg_GetResourceItemData(HResourceItemAndle hAndle);
//	_CallStack_default_ HPL_Result				Eg_TryLockResourceItem(HResourceItemAndle hAndle);
//	_CallStack_default_ void_pl                 Eg_UnLockResourceItem(HResourceItemAndle hAndle);

//	_CallStack_default_  PLRL_ConstID_LocalAllocate_PKGItem
//#define PLSys_ConstID_LThreadManagerPool
//#define PLSys_ConstID_GlobalManagerPool

	/*
	_CallStack_default_ HResourceSysAndle       Eg_CreateResourceSystem(intV_pl iAllMode);
	_CallStack_default_ void_pl                 Eg_DestoryResourceSystem(HResourceSysAndle hAndle);
	_CallStack_default_ HPL_Result              Eg_OpenTrusteeshipPKG(HResourceSysAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ void_pl                 Eg_CloseTrusteeshipPKG(HResourceSysAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ void_pl                 Eg_CloseAllTrusteeshipPKG(HResourceSysAndle hAndle);
	_CallStack_default_ void_pl                 Eg_ForceCloseTrusteeshipPKG(HResourceSysAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ void_pl                 Eg_ForceCloseAllTrusteeshipPKG(HResourceSysAndle hAndle);
	_CallStack_default_ HResourceMgrItemAndle   Eg_CreateResourceSystemItem(HResourceSysAndle hAndle,ePL_ResourceMgrType eType,intV_pl iPool,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ void_pl                 Eg_ReleaseResourceSystemItem(HResourceMgrItemAndle hAndle);
	_CallStack_default_ HPL_Result              Eg_DestoryResourceSystemItem(HResourceMgrItemAndle hAndle);
	_CallStack_default_	HPL_Result				Eg_TryLockResourceItemData(HResourceMgrItemAndle hAndle);
	_CallStack_default_ void_pl                 Eg_UnLockResourceItemData(HResourceMgrItemAndle hAndle);
	_CallStack_default_ HPL_Result				Eg_AllocateResourceSystemItemData(HResourceMgrItemAndle hAndle,intV_pl iDataSize);
	_CallStack_default_ HPL_Result              Eg_FreeResourceSystemItemData(HResourceMgrItemAndle hAndle);
	_CallStack_default_ void_pl                 Eg_RefurbishResourceSystem(HResourceSysAndle hAndle);
*/

	/*********End Define Resource Object Manager Module API************/

	_CallStack_default_ uintV_pl				__native_hash(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange);
	_CallStack_default_ bool_pl                 __native_InsertFITableMap(PL_RLPoolMap * ptrMap,PL_RLItem * ptrItem);
	_CallStack_default_ PL_RLItem *             __native_RemoveFITableMap(PL_RLPoolMap * ptrMap,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ bool_pl                 __native_DestoryFITableMap(PL_RLPoolMap * ptrMap,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_RLItem *             __native_SearchFITableMap(PL_RLPoolMap * ptrMap,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ void_pl                 __native_RemoveAllFITableMap(PL_RLPoolMap * ptrMap);
	_CallStack_default_ void_pl                 __native_DestoryAllFITableMap(PL_RLPoolMap * ptrMap);
	_CallStack_default_ intV_pl                 __native_GetCountFITableMap(PL_RLPoolMap * ptrMap);

	//HPKGTaskersObjAndle
#endif /* ENGINERESOURCELOADAPI_H_ */
