/*
 * EngineResourceLoadInface.h
 *
 *  Created on: 2009-9-16
 *      Author: Administrator
 */
#include "EngineResourceLoadI.h"
#include "PLEngineResourceLoadPKH.h"
#ifndef ENGINERESOURCELOADINFACE_H_
#define ENGINERESOURCELOADINFACE_H_
	#define PLRL_ConstID_PackageFileItemSlotMapMaxSize 512
	#define PLRL_ConstID_PackageFileItemMappingSlotMapMaxSize	128
	#define PLRL_ConstID_ResourceDataMgrMapBaseMaxSize 	    512
	#define PLRL_ConstID_ResourceDataPolygonMgrMapMaxSize  (PLRL_ConstID_ResourceDataMgrMapBaseMaxSize << 4)
	#define PLRL_ConstID_ResourceDataMaterialMgrMapMaxSize (PLRL_ConstID_ResourceDataMgrMapBaseMaxSize << 4)
	#define PLRL_ConstID_ResourceDataTextureMgrMapMaxSize  (PLRL_ConstID_ResourceDataMgrMapBaseMaxSize << 4)
	#define PLRL_ConstID_ResourceDataBoneMgrMapMaxSize     (PLRL_ConstID_ResourceDataMgrMapBaseMaxSize << 2)
	#define PLRL_ConstID_ResourceDataScriptMgrMapMaxSize   (PLRL_ConstID_ResourceDataMgrMapBaseMaxSize << 2)
//	#define PLRL_ConstID_PackageFileItemSlotMapSpeedupMOD (512 - 1)

	typedef _CallStack_default_ uintV_pl 	(* __Rc_HashStringFunc__PL__)			(const_pl char_pl *,intV_pl,intV_pl);
	typedef _CallStack_default_ bool_pl  	(* __Rc_InsertFITableMapFunc__PL__)		(void_pl *,void_pl *);
	typedef _CallStack_default_ void_pl * 	(* __Rc_RemoveFITableMapFunc__PL__)		(void_pl *,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ void_pl  	(* __Rc_RemoveAllFITableMapFunc__PL__)	(void_pl *);
	typedef _CallStack_default_ bool_pl  	(* __Rc_DestoryFITableMapFunc__PL__)		(void_pl *,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ void_pl  	(* __Rc_DestoryAllFITableMapFunc__PL__)		(void_pl *);
	typedef _CallStack_default_ void_pl  *  (* __Rc_SearchFITableMapFunc__PL__)			(void_pl *,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ intV_pl     (* __Rc_GetCountFITableMapFunc__PL__)		(void_pl *);

	#pragma pack(1)
	typedef Aligned(1) struct _SPL_RLPackageFileHeader{
		uint64_pl uFID;
		uint32_pl uLVer;
		uint32_pl uHVer;
		int32_pl  iLHeaderSize;					// File Header size Low 32 bit
		int32_pl  iHHeaderSize;					// File Header size High 32 bit
		int32_pl  iLFileSize;					// File size Low  32 bit
		int32_pl  iHFileSize;					// File size High 32 bit
		int32_pl  iLDataSecOffset;				// File Data Offset Low 32 bit
		int32_pl  iHDataSecOffset;				// File Data Offset High 32 bit
		int32_pl  iLTableSecOffset;				// Table Offset Low 32 bit
		int32_pl  iHTableSecOffset;				// Table Offset High 32 bit
		uint32_pl iLStoreModeF;					// Data Store Mode low 32 bit  (disk or network)
		uint32_pl iHStoreModeF;					// Data Store Mode high 32 bit (disk or network)
		int32_pl  iTableCount;                 // Table Count
		int32_pl  iTableSize;                  // Table Struct Size
		int32_pl  iTableMaxCount;               // Table Item Max Count
		byte_pl   FileCRCCode[PLRL_ConstID_PackageFileCRCCodeMaxSize]; //Package File CRC code
	}__Aligned(1) PL_RLPackageFileHeader;

	typedef Aligned(1) struct _SPL_RLPKFileTableItem{
		int32_pl cbLSize;		// Struct Size low 32bit
		int32_pl cbHSize;		// Struct Size high 32bit
		int32_pl iLFileSize;    // File Data Size low 32bit
		int32_pl iHFileSize;    // File Data Size high 32bit
		int32_pl iLSize;		// string key name size low 32bit
		int32_pl iHSize;		// stirng key name size high 32bit
		int32_pl iLDataOffset;	// File Item Data Section Offset
		int32_pl iHDataOffset;  // File Item Data Section Offset
		uint32_pl uLType;		// File Item Type low 32bit
		uint32_pl uHType;		// File Item Type high 32bit
		uint32_pl uEnCode;
		byte_pl  FileCRCCode[PLRL_ConstID_PackageFileCRCCodeMaxSize]; // File CRC code
		char_pl  FileName[PLRL_ConstID_PackageFileItemNameMaxSize];
	}__Aligned(1) PL_RLPKFileTableItem;

	typedef struct Aligned(1) _SPL_RLItem : public PL_ObjectChainPointer{
		intV_pl 		iRLItemMode;
		PLDeviceHandle hFileAndle;
		HPKGObjAndle 	hPKGAndle;
		PL_RLPKFileTableItem item;
	}__Aligned(1) PL_RLItem;
#pragma pack()

#pragma pack(4)
	typedef  struct Aligned(8) _SPL_ResourceLoadPlusLibraryHeavy{
		PL_EngineLibraryHeavyInface Inface;
		PLConstCharTableHandle hSysConstCharTable;
		HPPLEngine hEngine;
		char_pl pCWD[PL3DSystemFileNameMaxLength];
		intV_pl iCWDSize;
		char_pl pResourceCWD[PL3DSystemFileNameMaxLength];
		intV_pl iResourceCWDSize;
//		intV_pl iConst_PackageCount;
//		PL_RLPackage * Const_ListPackage;
//		PL_RLPackage * RW_ListPackage;
	}__Aligned(8) PL_ResourceLoadLibraryHeavy;
	typedef  struct Aligned(8) _SPL_ResourceLoadLibraryFunTable{
		PL_EngineLibraryFunTable Inface;
		fun_pl functionlistEx[PLRL_Table_FunMaxSize - 1];
	}__Aligned(8) PL_ResourceLoadLibraryFunTable;


	typedef  struct Aligned(8) _SPL_RLPoolMap{
		intV_pl iCount;
		intV_pl iSlotMapMaxSize;
		intV_pl iStoreMode;
//		intV_pl iSpeedupMOD;
		__Rc_HashStringFunc__PL__ 				hashfunc;
		__Rc_InsertFITableMapFunc__PL__ 		insertfunc;
		__Rc_RemoveFITableMapFunc__PL__ 		removefunc;
		__Rc_RemoveAllFITableMapFunc__PL__  	removeallfunc;
		__Rc_DestoryFITableMapFunc__PL__    	destoryfunc;
		__Rc_DestoryAllFITableMapFunc__PL__ 	destoryallfunc;
		__Rc_SearchFITableMapFunc__PL__     	searchtablefunc;
		__Rc_GetCountFITableMapFunc__PL__       getcountfunc;
		PL_RLItem * ptrRLItem[PLRL_ConstID_PackageFileItemSlotMapMaxSize];
		_Syn_RWLockWF lockList[PLRL_ConstID_PackageFileItemSlotMapMaxSize];
		//_Syn_SpinLock lockList[PLRL_ConstID_PackageFileItemSlotMapMaxSize];
	}__Aligned(8) PL_RLPoolMap;
	typedef  struct Aligned(8) _SPL_RLPackage{
		PL_RLPoolMap * RLListMap[PLRL_ConstID_PackagePoolIndexMapMaxCount];
	}__Aligned(8) PL_RLPackage;
	typedef struct Aligned(8) _SPL_PackageObjectState : public PL_ObjectChainPointer{
//		_SPL_PackageObjectState * ptrNext;
		intV_pl iMode;
		PLDeviceHandle hFileAndle;
		char_pl pFullPath[PL3DSystemFileNameMaxLength];
		intV_pl iFPLength;
		PL_RLPackageFileHeader header;
		PL_RLPoolMap * ptrListMap;
		void_pl * ptrTableItemData;
	}__Aligned(8) PL_PackageObjectState;

	typedef struct Aligned(8) _SPL_PackageTaskersState{
		intV_pl cbSize;
//		intV_pl iPKGCount;
		PL_PackageObjectState * ptrPackageObjList_Resource;
	}__Aligned(8) PL_PackageTaskersState;
	//HResourceItemAndle

	typedef struct Aligned(8) _SPL_ResourceDataItem : public PL_ObjectChainPointer{
		ePL_ResourceDataMgrType   eType;				//Resource Data Type
		intV_pl 			  	  iSpecificType; 			//Specific Resource Type
		intV_pl               	  iPool;
		ePL_ResourceDataOperator  eOperator;
		const_pl char_pl 	* 	  ptrName;					//Resource name
		intV_pl 			  	  iNSize;					//Resource name length
		HPKGFileItemAndle     	  hAndle;
		_Syn_SpinLock             lock;
		ePL_ResourceLoadState 	  eLoadState;
		volatile_pl intV_pl   	  iRefCount;				//Resource reference count
//		intV_pl               iDBMaxSize;
//		intV_pl               iDataSize;
//		void_pl 			* ptrData;					//Resource Data
	}__Aligned(8) PL_ResourceDataItem;

	typedef struct Aligned(8) _SPL_PKGMemoryMapping : public PL_ObjectChainPointer{
		_SPL_PKGMemoryMapping * ptrChainUp;
		_SPL_PKGMemoryMapping * ptrChainNext;
		const_pl char_pl * ptrPKGName;
		intV_pl iPKGNSize;
		volatile_pl ePL_ResourceLoadState eLoadState;
		HPKGObjAndle hAndle;
		struct _SPL_ResourceDataSystem * ptrSystem;
		volatile_pl intV_pl iRefCount;
	}__Aligned(8) PL_PKGMemoryMapping;

	/*
	//HResourceMgrAndle
	typedef struct Aligned(8) SPL_ResourceManager{
		HResourceSysAndle hSysAndle;
	}__Aligned(8) PL_ResourceManager;
	//HResourceAndle
	//HResourceSysAndle
	typedef struct Aligned(8) SPL_ResourceSystem{
		PL_ResourceManager MgrList[PLSys_Const_ResD_ePLMgrMaxCount];

		__stl_allocatememory__PL__	allocatememory;
		__stl_freememory__PL__		freememory;
	}__Aligned(8) PL_ResourceSystem;
*/
	typedef struct Aligned(8) _SPL_ResourceDataMapItem{
		PL_ResourceDataItem * ptrRoot;
		_Syn_RWLockWF         lock;
	}__Aligned(8) PL_ResourceDataMapItem ;
//	typedef struct Aligned(8) _SPL_RDPKGMemoryMapping{
//	}PL_RDPKGMemoryMapping;

	typedef struct Aligned(8) _SPL_ResourceDataManager{
		struct _SPL_ResourceDataSystem * ptrSystem;
		const_pl intV_pl iMaxCount;
		__stl_hashstringFunc__PL__ hfunc;
		volatile_pl intV_pl iCount;
		PL_ResourceDataMapItem * ptrList;
	}__Aligned(8) PL_ResourceDataManager;
	typedef struct Aligned(8) _SPL_ResourceDataSystem{
		struct _SPL_PKGMemoryMapping * ptrPKGRoot;
		struct _SPL_PKGMemoryMapping * ptrPKGMapList[PLRL_ConstID_PackageFileItemMappingSlotMapMaxSize];
		_Syn_RWLockWF 					lockPKGMapList[PLRL_ConstID_PackageFileItemMappingSlotMapMaxSize];
		__Rc_HashStringFunc__PL__ 		MappHashfunc;
		struct _SPL_ResourceDataManager MgrList[PLSys_Const_ResD_ePLMgrMaxCount];
		volatile_pl bool_pl bRelease;
	}__Aligned(8) PL_ResourceDataSystem;


#pragma pack()

#endif /* ENGINERESOURCELOADINFACE_H_ */
