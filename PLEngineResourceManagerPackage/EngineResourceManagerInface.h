/*
 * EngineResourceManagerInface.h
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "PLEngineResourceManagerPKH.h"
#include "EngineResourceManagerI.h"
#ifndef ENGINERESOURCEMANAGERINFACE_H_
#define ENGINERESOURCEMANAGERINFACE_H_
	#define PLRMgr_ConstID_RPolygonMgrMapSlotMaxSize	   8192
	#define PLRMgr_ConstID_RPolygonMgrTaskerListMaxL       1024

	#define PLRMgr_ConstID_RTextureMgrMapSlotMaxSize 	   8192
	#define PLRMgr_ConstID_RTextureMgrTaskerListMaxL       512

	#define PLRMgr_ConstID_RScriptMgrMapSlotMaxSize  	   1024
	#define PLRMgr_ConstID_RScriptMgrTaskerListMaxL        512

	#define PLRMgr_ConstID_RVideoMgrMapSlotMaxSize  	   1024
	#define PLRMgr_ConstID_RVideoMgrTaskerListMaxL         512

	#define PLRMgr_ConstID_RMaterialMgrMapSlotMaxSize  	   1024
	#define PLRMgr_ConstID_RMaterialMgrTaskerListMaxL      512

	#define PLRMgr_ConstID_RSoundMgrMapSlotMaxSize  	   1024
	#define PLRMgr_ConstID_RSoundMgrTaskerListMaxL         512

	#define PLRMgr_ConstID_RWaveMgrMapSlotMaxSize  	       1024
	#define PLRMgr_ConstID_RWaveMgrTaskerListMaxL          512

typedef _CallStack_default_ uintV_pl 	(* __RMgr_HashStringFunc__PL__)			(const_pl char_pl *,intV_pl,intV_pl);
#pragma pack(4)
	typedef  struct Aligned(8) _SPL_ResourceManagerPlusLibraryHeavy{
		PL_EngineLibraryHeavyInface Inface;
		PLConstCharTableHandle hSysConstCharTable;
		HPPLEngine hEngine;
		char_pl pCWD[PL3DSystemFileNameMaxLength];
		intV_pl iCWDSize;
		char_pl pResourceCWD[PL3DSystemFileNameMaxLength];
		intV_pl iResourceCWDSize;
		char_pl pLogCWD[PL3DSystemFileNameMaxLength];
		intV_pl iLogCWDSize;
//		intV_pl iConst_PackageCount;
//		PL_RLPackage * Const_ListPackage;
//		PL_RLPackage * RW_ListPackage;
	}__Aligned(8) PL_ResourceManagerLibraryHeavy;

	typedef  struct Aligned(8) _SPL_ResourceManagerLibraryFunTable{
		PL_EngineLibraryFunTable Inface;
		fun_pl functionlistEx[PLRMgr_Table_FunMaxSize - 1];
	}__Aligned(8) PL_ResourceManagerLibraryFunTable;


	typedef struct Aligned(8) _SPL_ResourcePolygonItem : public PL_ResourcePolygon{
		HPolygonMgrAndle hMgrAndle;
		_SPL_ResourcePolygonItem * ptrMNext;
		_SPL_ResourcePolygonItem * ptrNext;
		volatile_pl intV_pl iRefCount;
		intV_pl iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) PL_ResourcePolygonItem;

	typedef struct Aligned(8) _SPL_ResourceTextureItem : public PL_ResourceTexture{
		HTextureMgrAndle hMgrAndle;
		_SPL_ResourceTextureItem * ptrMNext;
		_SPL_ResourceTextureItem * ptrNext;
		volatile_pl intV_pl iRefCount;
		intV_pl iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) PL_ResourceTextureItem;

	typedef struct Aligned(8) _SPL_ResourceScriptItem : public PL_ResourceScript{
		HScriptMgrAndle hMgrAndle;
		_SPL_ResourceScriptItem * ptrMNext;
		_SPL_ResourceScriptItem * ptrNext;
		volatile_pl intV_pl iRefCount;
		HResDataItemAndle hRDAndle;
	} __Aligned(8) PL_ResourceScriptItem;
	typedef struct Aligned(8) _SPL_ResourceWaveItem : public PL_ResourceWave{
		HWaveMgrAndle hMgrAndle;
		_SPL_ResourceWaveItem * ptrMNext;
		_SPL_ResourceWaveItem * ptrNext;
		volatile_pl intV_pl iRefCount;
		HResDataItemAndle hRDAndle;
	} __Aligned(8) PL_ResourceWaveItem;
	typedef struct Aligned(8) _SPL_ResourceSoundItem : public PL_ResourceSound{
		HSoundMgrAndle hMgrAndle;
		_SPL_ResourceSoundItem * ptrMNext;
		_SPL_ResourceSoundItem * ptrNext;
		volatile_pl intV_pl iRefCount;
		intV_pl iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) PL_ResourceSoundItem;
	typedef struct Aligned(8) _SPL_ResourceMaterialItem : public PL_ResourceMaterial{
		HMaterialMgrAndle hMgrAndle;
		_SPL_ResourceMaterialItem * ptrMNext;
		_SPL_ResourceMaterialItem * ptrNext;
		volatile_pl intV_pl iRefCount;
		intV_pl iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) PL_ResourceMaterialItem;
	typedef struct Aligned(8) _SPL_ResourceVideoItem : public PL_ResourceVideo{
		HVideoMgrAndle hMgrAndle;
		_SPL_ResourceVideoItem * ptrMNext;
		_SPL_ResourceVideoItem * ptrNext;
		volatile_pl intV_pl iRefCount;
		intV_pl iCount;
		HResDataItemAndle hRDAndleList[1];
	} __Aligned(8) PL_ResourceVideoItem;


	typedef struct _SPL_PL_ResourcePolygonSlotItem{
		PL_ResourcePolygonItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}PL_ResourcePolygonSlotItem;
	typedef struct _SPL_PL_ResourceTextureSlotItem{
		PL_ResourceTextureItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}PL_ResourceTextureSlotItem;
	typedef struct _SPL_PL_ResourceScriptSlotItem{
		PL_ResourceScriptItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}PL_ResourceScriptSlotItem;
	typedef struct _SPL_PL_ResourceMaterialSlotItem{
		PL_ResourceMaterialItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}PL_ResourceMaterialSlotItem;
	typedef struct _SPL_PL_ResourceVideoSlotItem{
		PL_ResourceVideoItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}PL_ResourceVideoSlotItem;
	typedef struct _SPL_PL_ResourceWaveSlotItem{
		PL_ResourceWaveItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}PL_ResourceWaveSlotItem;
	typedef struct _SPL_PL_ResourceSoundSlotItem{
		PL_ResourceSoundItem * ptrRoot;
		_Syn_RWLockWF     lock;
	}PL_ResourceSoundSlotItem;


	typedef struct Aligned(8) _SPL_ResourcePolygonManager : public PLResourceManager{
		volatile_pl intV_pl iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		PL_ResourcePolygonSlotItem List[PLRMgr_ConstID_RPolygonMgrMapSlotMaxSize];
		PL_ResourcePolygonItem * TaskList[PLRMgr_ConstID_RPolygonMgrTaskerListMaxL];
		PL_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__PL__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) PL_ResourcePolygonManager;
	typedef struct Aligned(8) _SPL_ResourceTextureManager : public PLResourceManager{
		volatile_pl intV_pl iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		PL_ResourceTextureSlotItem List[PLRMgr_ConstID_RTextureMgrMapSlotMaxSize];
		PL_ResourceTextureItem * TaskList[PLRMgr_ConstID_RTextureMgrTaskerListMaxL];
		PL_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__PL__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) PL_ResourceTextureManager;
	typedef struct Aligned(8) _SPL_ResourceScriptManager  : public PLResourceManager{
		volatile_pl intV_pl iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		PL_ResourceScriptSlotItem List[PLRMgr_ConstID_RScriptMgrMapSlotMaxSize];
		PL_ResourceScriptItem * TaskList[PLRMgr_ConstID_RScriptMgrTaskerListMaxL];
		PL_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__PL__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) PL_ResourceScriptManager;

	typedef struct Aligned(8) _SPL_ResourceMaterialManager : public PLResourceManager{
		volatile_pl intV_pl iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		PL_ResourceMaterialSlotItem List[PLRMgr_ConstID_RMaterialMgrMapSlotMaxSize];
		PL_ResourceMaterialItem * TaskList[PLRMgr_ConstID_RMaterialMgrTaskerListMaxL];
		PL_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__PL__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) PL_ResourceMaterialManager;

	typedef struct Aligned(8) _SPL_ResourceVideoManager : public PLResourceManager{
		volatile_pl intV_pl iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		PL_ResourceVideoSlotItem List[PLRMgr_ConstID_RVideoMgrMapSlotMaxSize];
		PL_ResourceVideoItem * TaskList[PLRMgr_ConstID_RVideoMgrTaskerListMaxL];
		PL_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__PL__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) PL_ResourceVideoManager;

	typedef struct Aligned(8) _SPL_ResourceWaveManager : public PLResourceManager{
		volatile_pl intV_pl iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		PL_ResourceWaveSlotItem List[PLRMgr_ConstID_RWaveMgrMapSlotMaxSize];
		PL_ResourceWaveItem * TaskList[PLRMgr_ConstID_RWaveMgrTaskerListMaxL];
		PL_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__PL__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) PL_ResourceWaveManager;

	typedef struct Aligned(8) _SPL_ResourceSoundManager : public PLResourceManager{
		volatile_pl intV_pl iTkCount;
		_Syn_SpinLock       TkLock;
		_Syn_SpinLock       TkOvLock;
		PL_ResourceSoundSlotItem List[PLRMgr_ConstID_RSoundMgrMapSlotMaxSize];
		PL_ResourceSoundItem * TaskList[PLRMgr_ConstID_RSoundMgrTaskerListMaxL];
		PL_CommResourceBlock * ptrRootCommBlock;
		_Syn_SpinLock          TBLock;
		__RMgr_HashStringFunc__PL__ hashfunc;
		HResDataSystem hRDSystem;
	} __Aligned(8) PL_ResourceSoundManager;
#pragma pack()


#endif /* ENGINERESOURCEMANAGERINFACE_H_ */
