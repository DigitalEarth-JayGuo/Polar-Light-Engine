/*
 * PLEngineRenderAPIInface.h
 *
 *  Created on: 2009-9-14
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINERENDERAPIINFACE_H_
#define PLENGINERENDERAPIINFACE_H_
	#define HRdrTextureObject  void_pl *
	#define HRdrPolygonObject  void_pl *

	typedef enum eSPL_RenderResPoolType{
		PLSys_Const_Rdr_eDefaultPool  	 = 0,
		PLSys_Const_Rdr_eManagedPool	 	,
		PLSys_Const_Rdr_eSystemMemPool
	}ePL_RenderResPoolType;


//	typedef enum eSPL_RenderResType{
//
//		PLSys_Const_Res_ePLPolygonMgr
//	}ePL_RenderResType;

//	#define PLRdr_ConstID_
	typedef struct _SPL_RenderResObject{

	}PL_RenderResObject;

	#define PLRdrDeviceHandle void_pl *
/*	typedef enum eSPL_ResourceMgrType {
		PLSys_Const_Res_ePLPolygonMgr  	 = 0,
		PLSys_Const_Res_ePLTextureMgr	    ,
		PLSys_Const_Res_ePLMapDataMgr       ,
		PLSys_Const_Res_ePLWaveMgr       	,
		PLSys_Const_Res_ePLSoundMgr      	,
		PLSys_Const_Res_ePLScriptMgr     	,
		PLSys_Const_Res_ePLMaterialMgr    	,
		PLSys_Const_Res_ePLVideoMgr      	,
		PLSys_Const_Res_ePLMgrMaxCount
	}ePL_ResourceMgrType;*/
#endif /* PLENGINERENDERAPIINFACE_H_ */
