/*
 * PLEngineMemoryPoolInface.h
 *
 *  Created on: 2009-8-2
 *      Author: Administrator
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineResultVD.h"
#include "PLEngineH.h"
#include "PLEngineSysDataMacro.h"
#include "PLEngineSysSynchronInface.h"
#include "PLEngineSysProcessInface.h"
#ifndef PLENGINEMEMORYPOOLINFACE_H_
#define PLENGINEMEMORYPOOLINFACE_H_
	#define PLMem_Const_CPUCacheLineAlignedSize      64
	#define PLMem_Const_MemoryPackageGroupCount      32
	#define PLMem_Const_TLSAllocSmallObjectMaxSize   64
	#define PLMem_Const_GroupAllocObjectMaxSize      1024



	#define PLMem_Const_MemoryIncreaseStep  	     (1024*1024)
	#define PLMem_Const_MemoryBlockSize 		     (16*1024)

	#define PLMem_Const_AllocSmallObjectMinSize      PLMem_Const_CPUCacheLineAlignedSize
	#define PLMem_Const_AllocSmallObjectMaxSize      1024
	#if PLCPU_IAXX == PLCPU_IA32
		#define PLMem_Const_TLSAllocSmallObjectMinSize	   8
		#define PLMem_Const_MemoryManagerMaxItemCount (4*1024)
	#elif PLCPU_IAXX == PLCPU_IA64
		#define PLMem_Const_TLSAllocSmallObjectMinSize	   16
		#define PLMem_Const_MemoryManagerMaxItemCount (16*1024)
	#endif
	#define PLMem_ComputeSubsectionSize(iSubsection) (PLSysAPI_Alignment_Low((PLMem_Const_MemoryBlockSize - PL_CompilerAllocSize(PLMemBlock))/iSubsection,PLMem_Const_CPUCacheLineAlignedSize))
	#define PLMem_ComputeIntervalSubsectionSize(base,iSize,iOrder) ((base) - (6 << 2)	- 4 + (iOrder<<2) + ((iSize - 1)>>(iOrder-2)))
	#define PLMem_Const_MemoryAllocMaxBlockPool      PLMem_ComputeSubsectionSize(2)
	#define PLMem_Const_TLSBigBlckPoolIndexBase         ((PLMem_ComputeIntervalSubsectionSize((PLMem_Const_TLSAllocSmallObjectMaxSize>>3),PLMem_Const_GroupAllocObjectMaxSize,9)) + 1)
	//#define PLMem_Const_Memory
//PLMemPackage

#pragma pack(4)
	typedef  struct _SPLMemFreeObject{
		_SPLMemFreeObject * ptrNextObject;
	}PLMemFreeObject;
#pragma pack()
#pragma pack(8)
	typedef struct _SPLMemBlock : public PLMemFreeObject{
		void_pl    	  * bumpPtr;
		intV_pl         iAllocSize;
	}PLMemBlock;
	typedef  struct Aligned(PLMem_Const_CPUCacheLineAlignedSize) _SPLGMemMapItem{
		_SPLGMemMapItem * ptrNextItem;
		AddresValue_pl AddresValue;
		PLMemBlock * ptrTop;
		PLMemFreeObject * ptrFreeList;
		PLMemFreeObject * ptrBigMFreeList;
		_Syn_SpinLock lock;
	}__Aligned(PLMem_Const_CPUCacheLineAlignedSize) PLGMemMapItem;

	typedef  struct Aligned(PLMem_Const_CPUCacheLineAlignedSize) _SPLMemPackage{
		PLMemBlock * ptrActive;
		PLMemFreeObject * ptrList;
		_SPLMemPackage * ptrPre;
		intV_pl iAllocCount;
		_Syn_SpinLock lock;
	}__Aligned(PLMem_Const_CPUCacheLineAlignedSize) PLMemPackage;

	typedef struct Aligned(PLMem_Const_CPUCacheLineAlignedSize) _SPLMemAllocateOrgan{
		PLMemBlock * ptrTop;
		PLMemPackage PackageList[PLMem_Const_MemoryPackageGroupCount];
	}__Aligned(PLMem_Const_CPUCacheLineAlignedSize) PLMemAllocateOrgan;
	//Memory Map
	typedef  struct Aligned(PLMem_Const_CPUCacheLineAlignedSize) _SPLMemManager{
		intV_pl      iState;
		PLGMemMapItem MapItemList[PLMem_Const_MemoryManagerMaxItemCount];
		PLMemAllocateOrgan  publicAllocOrgan;
	}__Aligned(PLMem_Const_CPUCacheLineAlignedSize) PLMemManager;
#pragma pack()

#endif /* PLENGINEMEMORYPOOLINFACE_H_ */
