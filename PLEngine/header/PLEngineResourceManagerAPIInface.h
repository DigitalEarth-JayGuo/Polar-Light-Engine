/*
 * PLEngineResourceManagerAPIInface.h
 *
 *  Created on: 2009-10-23
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#ifndef PLENGINERESOURCEMANAGERAPIINFACE_H_
#define PLENGINERESOURCEMANAGERAPIINFACE_H_
	#define HPolygonMgrAndle 	void_pl *
	#define HTextureMgrAndle 	void_pl *
	#define HScriptMgrAndle  	void_pl *
	#define HVideoMgrAndle   	void_pl *
	#define HMaterialMgrAndle   void_pl *
	#define HWaveMgrAndle       void_pl *
	#define HSoundMgrAndle      void_pl *
#pragma pack(4)



	typedef struct Aligned(8) _SPL_ResourceItem {
		volatile_pl ePL_ResourceLoadState eState;
		volatile_pl PL_ResourceObjectDynamicState eDynamicState;
		ePL_ResourceDataMgrType eType;
		intV_pl iDataSpecificType;
		const_pl char_pl * ptrName;
		intV_pl iNSize;
		void_pl * ptrData;
		const_pl intV_pl iPRI;
	} __Aligned(8) PL_ResourceItem;

	typedef struct Aligned(8) _SPL_ResourcePolygon : public PL_ResourceItem{
		HRdrPolygonObject hRdrAndle;

	} __Aligned(8) PL_ResourcePolygon;
	typedef struct Aligned(8) _SPL_ResourceTexture : public PL_ResourceItem{
		HRdrTextureObject hRdrAndle;

	} __Aligned(8) PL_ResourceTexture;
	typedef struct Aligned(8) _SPL_ResourceScript : public PL_ResourceItem{

	} __Aligned(8) PL_ResourceScript;
	typedef struct Aligned(8) _SPL_ResourceWave: public PL_ResourceItem{

	} __Aligned(8) PL_ResourceWave;
	typedef struct Aligned(8) _SPL_ResourceSound: public PL_ResourceItem{

	} __Aligned(8) PL_ResourceSound;
	typedef struct Aligned(8) _SPL_ResourceMaterial: public PL_ResourceItem{

	} __Aligned(8) PL_ResourceMaterial;
	typedef struct Aligned(8) _SPL_ResourceVideo: public PL_ResourceItem{

	} __Aligned(8) PL_ResourceVideo;

	typedef struct Aligned(8) _SPL_ResourceManager{
		volatile_pl intV_pl iCount;
		PL_ResourceItem * ptrOverFlowQueueRoot;
		_Syn_SpinLock     ReclaimLock;
		PL_ResourceItem * ptrReclaimQueueRoot;
	} __Aligned(8) PLResourceManager;

	typedef struct Aligned(8) _SPL_ResourceBgDisposeParamer{
		intV_pl iSecond;
	} __Aligned(8) PL_ResourceBgDisposeParamer;

	typedef struct Aligned(8) _SPL_CommResourceBlock{
		PL_ResourceItem * ptrItem;
		_SPL_CommResourceBlock * ptrNext;
		lint_pl   lMov;
		void_pl * ptrBuffer;
		intV_pl   iMaxB;
		_Syn_SpinLock RLock;
	}PL_CommResourceBlock;
#pragma pack()
#endif /* PLENGINERESOURCEMANAGERAPIINFACE_H_ */
