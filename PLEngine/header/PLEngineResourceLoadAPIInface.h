/*
 * PLEngineResourceAPIInface.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINERESOURCEAPIINFACE_H_
#define PLENGINERESOURCEAPIINFACE_H_
	#define HPKGObjAndle 		void_pl *
	#define HPKGFileItemAndle 	void_pl *
	#define HResDataItemAndle   void_pl *
	#define HResDataPKGMMAndle  void_pl *
	#define HPKGTaskersObjAndle void_pl *
//	#define HResourceMgrAndle   void_pl *
//	#define HResourceSysAndle   void_pl *
	#define HResDataSystem void_pl *
	#define PLRL_ConstID_PackagePoolIndexMapMaxCount 8
		#define PLRL_ConstID_PolygonIndexMap          0
		#define PLRL_ConstID_TexIndexMap              1
		#define PLRL_ConstID_WavIndexMap              2
		#define PLRL_ConstID_VideoIndexMap  		    3
		#define PLRL_ConstID_ScriptIndexMap           4
		#define PLRL_ConstID_MaterialDepictIndexMap   5
		#define PLRL_ConstID_DataIndexMap             6

	/***************Define Package File Item type*******************/
	#define PLRL_ConstID_PackageItemTypeMare              0xff
		#define PLRL_Marco_PackageItemMasterTypeMark(i)   (i<<3)
		#define PLRL_ConstID_PKGItemType_Polygon          (PLRL_Marco_PackageItemMasterTypeMark(0)+ 0)
		#define PLRL_ConstID_PKGItemType_Bone             (PLRL_Marco_PackageItemMasterTypeMark(0)+ 1)
		#define PLRL_ConstID_PKGItemType_Tex              (PLRL_Marco_PackageItemMasterTypeMark(1)+ 0)
		#define PLRL_ConstID_PKGItemType_WavEffect        (PLRL_Marco_PackageItemMasterTypeMark(2)+ 0)
		#define PLRL_ConstID_PKGItemType_Sound            (PLRL_Marco_PackageItemMasterTypeMark(2)+ 1)
		#define PLRL_ConstID_PKGItemType_Video            (PLRL_Marco_PackageItemMasterTypeMark(3)+ 0)
		#define PLRL_ConstID_PKGItemType_Script           (PLRL_Marco_PackageItemMasterTypeMark(4)+ 0)
		#define PLRL_ConstID_PKGItemType_MaterialDepict   (PLRL_Marco_PackageItemMasterTypeMark(5)+ 0)
		#define PLRL_ConstID_PKGItemType_Text             (PLRL_Marco_PackageItemMasterTypeMark(6)+ 0)
		#define PLRL_ConstID_PKGItemType_Data1            (PLRL_Marco_PackageItemMasterTypeMark(10)+ 0)
		#define PLRL_ConstID_PKGItemType_Data2            (PLRL_Marco_PackageItemMasterTypeMark(10)+ 1)
	/***************End Define Package File Item type****************/

	//#define PLRL_ConstID_PKStoreDisk                0
	/****************Begin Define Store mode mark****************/
	#define PLRL_ConstID_PKStoreNetWork               (1<<0)		//NetWork Load resource mode
	#define PLRL_ConstID_PKExteriorLinkIndex		  (1<<1)		//pakage file is store file link data,file swaraj store
	/****************End Define Store struct mode mark***********/
	/****************Begin Define FileItem mode mark***************************/
	#define PLRL_ConstID_LocalAllocate_PKGItem     (1<<0)			//local thread allocate memory
	#define PLRL_ConstID_IdenticalAllocate_PKGItem (1<<1)			//consolidate allocate a big memory block partition
	//#define PLRL_ConstID_Local
	/****************End Define FileItem mode mark*****************************/


	/********************Begin Define -- OpenPackage open Mode*******************************/
	#define PLRL_ConstID_PackageOpenMode_LocalAllocate    (1<<0)//default use global allocate memory , if define it  use  local thread allocate memory mode
																// and must at call local thread closepackage
	#define PLRL_ConstID_PackageOpenMode_UserDefineRangeMark 0xf000ffff
	#define PLLR_ConstID_PackageOpenMode_CreateNewPackage    (1<<16)
	#define PLLR_ConstID_PackageOpenMode_NotCreateFTable     (1<<17)
	#define PLLR_ConstID_PackageOpenMode_NotCreateFTFindMap  (1<<18)
	//#define PLRL_ConstID_Package
	/********************End Define -- OpenPackage open Mode **************************/

	/********************Begin Define Resource Manager Pool****************************/
	#define PLRL_ConstID_RS_TrusteeshipSystemPool 0
	#define PLRL_ConstID_RS_UserPool   		      1
	/********************End Define ResourceManager Pool*******************************/
	typedef enum eSPL_ResourceDataOperator{
		PLSys_Const_ResDOpert_ReadOnly = 0 ,
		PLSys_Const_ResDOpert_WriteOnly= 1 ,
		PLSys_Const_ResDOpert_RW       = 2
	}ePL_ResourceDataOperator;

	typedef enum eSPL_ResourceDataMgrType {
		PLSys_Const_ResD_ePLPolygonMgr  	 = 0,
		PLSys_Const_ResD_ePLBoneMgr          = 1,
		PLSys_Const_ResD_ePLTextureMgr	    	,
		PLSys_Const_ResD_ePLWaveMgr       		,
		PLSys_Const_ResD_ePLSoundMgr      		,
		PLSys_Const_ResD_ePLScriptMgr     		,
		PLSys_Const_ResD_ePLMaterialMgr    		,
		PLSys_Const_ResD_ePLVideoMgr      		,
		PLSys_Const_ResD_ePLTextMgr				,
		PLSys_Const_ResD_eData                  ,
		PLSys_Const_ResD_ePLMgrMaxCount
	}ePL_ResourceDataMgrType;
	/********************Begin Define Resource Item Type*****************/
		#define PLRL_ConstID_RDI_Polygon       		      PLRL_ConstID_PKGItemType_Polygon
		#define PLRL_ConstID_RDI_Bone             		  PLRL_ConstID_PKGItemType_Bone
		#define PLRL_ConstID_RDI_Tex              		  PLRL_ConstID_PKGItemType_Tex
		#define PLRL_ConstID_RDI_WavEffect        		  PLRL_ConstID_PKGItemType_WavEffect
		#define PLRL_ConstID_RDI_Sound            		  PLRL_ConstID_PKGItemType_Sound
		#define PLRL_ConstID_RDI_Video            		  PLRL_ConstID_PKGItemType_Video
		#define PLRL_ConstID_RDI_Script           		  PLRL_ConstID_PKGItemType_Script
		#define PLRL_ConstID_RDI_MaterialDepict   		  PLRL_ConstID_PKGItemType_MaterialDepict
		#define PLRL_ConstID_RDI_Text             		  PLRL_ConstID_PKGItemType_Text
		#define PLRL_ConstID_RDI_Data1            		  PLRL_ConstID_PKGItemType_Data1
		#define PLRL_ConstID_RDI_Data2            		  PLRL_ConstID_PKGItemType_Data2
	/********************End   Define Resource Item Type*****************/

	typedef enum eSPL_ResourceLoadState{
		PLSys_Const_ResLoad_ePLUnLoadComplete  	 = 0,
		PLSys_Const_ResLoad_ePLLoadComplete			,
		PLSys_Const_ResLoad_ePLBeginUnLoad  		,
		PLSys_Const_ResLoad_ePLUnLoading    		,
		PLSys_Const_ResLoad_ePLBeginLoad   			,
		PLSys_Const_ResLoad_ePLLoading

	}ePL_ResourceLoadState;

	typedef enum eSPL_ResourceObjectDynamicState{
		PLSys_Const_RODynamic_eNormal = 0,	//Normal State
		PLSys_Const_RODynamic_eCreate = 1,	//Createing
		PLSys_Const_RODynamic_eTasker    ,  //
		PLSys_Const_RODynamic_eReclaim
	}PL_ResourceObjectDynamicState;

	typedef enum eSPL_TexureRGBFormat{
		PLSys_Const_Pic_eA8R8G8B8 = 0
		//PLSys_Const_Pic_e
	}PL_eTextureRGBFormat;

#pragma pack(4)
	typedef struct _SPL_ResDataSystemCrParamer{
		intV_pl iAllMode;
	}PL_ResDataSystemCrParamer;

#pragma pack()
#endif /* PLENGINERESOURCEAPIINFACE_H_ */
