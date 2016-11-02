/*
 * PLEngineMemoryPool.h
 *
 *  Created on: 2009-6-30
 *      Author: root
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineGraphicsInface.h"
#include "PLEngineH.h"
#include "PLEngineInface.h"
#include "PLEngineI.h"
#include "PLEngineSysAPI.h"
#include "PLEngineSysProcess.h"
#ifndef PLENGINEMEMORYPOOL_H_
#define PLENGINEMEMORYPOOL_H_

	#define _PLMemPool_MemorySet(p,value,size) 		  PLSysAPI_MemorySet(p,value,size)
	#define _PLMemPool_MemoryCpy(p1,p2,size)  		  PLSysAPI_MemoryCpy(p1,p2,size)
	#define _PLMemPool_MemoryClearZero(p,value,size)  PLSysAPI_MemoryClearZero(p,size);

	#define _PLMemPool_Synchron_Lock  				  _Synchron_Lock
	#define _PLMemPool_InitializationLock(ptrlock)    PLSysAPI_InitAtomLock(ptrlock)
	#define _PLMemPool_BeginLock(ptrlock)             PLSysAPI_BeginAtomLock(ptrlock)
	#define _PLMemPool_EndLock(ptrlock)               PLSysAPI__EndAtomLock(ptrlock)
	#define _PLMemPool_EnterLock(ptrlock)             PLSysAPI_EnterAtomLock(ptrlock)
	#define _PLMemPool_LeaveLock(ptrlock)             PLSysAPI_LeaveAtomLock(ptrlock)
	#define _PLMemPool_ReleaseLock(ptrlock)           PLSysAPI__ReleaseAtomLock(ptrlock)

	#define _PLMemPool_BlockCompel_DataSize             1 //memory pool tag

	#define MemPageGranu 4096	//memorypage default alignment size
	#define MemItemGranu 32		//block default min size
	void_pl PLTLSKey_MemoryAllocateOrganKey_Destory(void_pl *);


//	inline void_pl * PLMacro_AllocateHighMemory(intV_pl iSize);
//	inline HPL_Result PLMacro_FreeHighMemory(void_pl * ptrMem);
/*
	//Memory Page Struct
	typedef Aligned(8) struct _SPLMemoryPage{
		uint_pl uSize;
		union{
			uint_pl  uTag;
			int_pl * ptrCount;
		}Tag;
		int_pl iCount;
		int_pl iBaseCount;
		_SPLMemoryPage * next;
		uint_pl uDataSize;
		union _adder{
			uint_pl uAdder;
			char_pl cAdder[1];
			void_pl * ptr;
		}adder;
	}PLMemoryPageSt,* PLMemoryPageStPtr;
	#define _PLMemoryPool_Page PL_CompilerAllocSize(PLMemoryPageSt)

	typedef Aligned(8) struct _SPLMemoryPageTagerHeader{
		uint_pl uSize;
		int_pl  iCount;
		_SPLMemoryPageTagerHeader * ptrNextPagerTager;
		union _adder{
			uint_pl   uAdder;
			char_pl   cAdder[1];
			void_pl * ptr;
			PLMemoryPageStPtr * ptrFirstPage;
		}adder;
	}PLMemoryPageTagerStHear,* PLMemoryPageTagerHearStPtr;
	#define _PLMemoryPool_PageTagerHeaderSize (PL_CompilerAllocSize(PLMemoryPageTagerStHear) - PL_CompilerAllocSize(PLMemoryPageTagerStHear::_adder))


	typedef Aligned(8) struct _SPLMemoryBlock{
		uint_pl uSize;
		union{
			uint_pl uTag;
			int_pl * ptrCount;
		}Tag;
	    union _adder {
			_SPLMemoryBlock * next;
			char_pl cAdder[1];
		}adder;
	}PLMemoryBlockSt,* PLMemoryBlockPtr;
	#define _PLMemoryPool_BlockHeaderSize (PL_CompilerAllocSize(PLMemoryBlockSt) - PL_CompilerAllocSize(PLMemoryBlockSt::_adder)) //MemoryBlock struct header size

	typedef Aligned(8) struct _SPLMMPoolPama{
		uint_pl uSystemPageGranuSize;           			 //memory page granu size  nomoral size is 4K
		uint_pl uSystemAddresALlocateGranuSize;
	}PLMMPoolPamaSt,* PLMMPoolPamaStPtr;

	typedef Aligned(8) struct _SPLMMPOOL{
		uint_pl           uSize;				   			 // _StMMPOOL Allocate  Struct Size  and ((MemoryPageStPtr Array size and MemoryBlockPtr Array size and unsigned int type size) mul uCount)
		PLMMPoolPamaSt      StSystemPama;        	 		 // system use memory allocate pama and values
		uint_pl             uCurrentPageGranu;				 //current Allocate MemoryPage size
		uint_pl             uBasePageGranu;					 //default Allocate MemoryPage size
		int_pl              iGene;				 			 //default Allocate completx current Alllocate Gene
		_PLMemPool_Synchron_Lock pageTagerLock; 			 //it's ptrPageHeaderFreeList  FreeList Queue Lock
		_PLMemPool_Synchron_Lock pagefreelistLock;			 //it's  the pages free list queue lock
		_PLMemPool_Synchron_Lock pagelock;		 			 //it's ptrPageList Array lock
		_PLMemPool_Synchron_Lock blocklock;	  				 //it's ptrfreelist Array lock
		uint_pl           uBlockGranuSize;	          		 //min block size
		uint_pl           uBlockMaxSize;		             //max block size
		uint_pl           uTag;					             //memory pool runing state and tag
		uint_pl           uTagerSize;                        //
		uint_pl           uSTagerToPageHeaderCount;          //
		PLMemoryPageTagerHearStPtr ptrPageTagerFirst;        //PageHeader Store Memory Pool
		PLMemoryPageStPtr          ptrPageHeaderFreeList;	 //PageHeader Free Block list (Store PageHeader Data) ;
		PLMemoryPageStPtr          ptrPageList;			     //Pointer MemoryPageStPtr Array memory postion
		PLMemoryBlockPtr         * ptrfreelist;			     //Pointer MemoryBlockPtr  Array memory postion
		uint_pl                  * ptrBlockAlignedlist;	     //Pointer
		uint_pl                    uCount;					 //Array Count
	}PLMMPOOL, * PLMMPOOLPtr;
	typedef void * HMWND;


	inline void _PL_MemoryPool_InsidePushBlock(PLMemoryBlockPtr * ptrFirstList,PLMemoryBlockPtr ptrNewBlock,_PLMemPool_Synchron_Lock * ptrLock){
		_PLMemPool_BeginLock(ptrLock);
			ptrNewBlock->adder.next=*ptrFirstList;
			//PLSysAPI_RWMberrier;
			*ptrFirstList=ptrNewBlock;
			--(*(ptrNewBlock->Tag.ptrCount));
		_PLMemPool_EndLock(ptrLock);
	}

	inline PLMemoryBlockPtr _PL_MemoryPool_InsidePopBlock(PLMemoryBlockPtr * ptrFirstList,_PLMemPool_Synchron_Lock * ptrLock){
		PLMemoryBlockPtr ptrBlock;
		_PLMemPool_BeginLock(ptrLock);
			ptrBlock = *ptrFirstList;
			//PLSysAPI_RWMberrier;
			*ptrFirstList = ptrBlock->adder.next;
			if((*(ptrBlock->Tag.ptrCount))<0)
				(*(ptrBlock->Tag.ptrCount)) = 0;
			++(*(ptrBlock->Tag.ptrCount));
		_PLMemPool_EndLock(ptrLock);
		return ptrBlock;
	}
	inline PLMemoryPageTagerHearStPtr _PL_MemoryPool_AllocateMemoryPageTager(PLMemoryPageTagerHearStPtr * ptrFirstPageTager,uint32_pl uSize,_PLMemPool_Synchron_Lock * ptrLock){
		PLMemoryPageTagerHearStPtr ptrTager;
		ptrTager = (PLMemoryPageTagerHearStPtr)PLSysAPI_AllocateMemory(uSize);
		if(ptrTager==NULL_PL)
			return NULL_PL;
		ptrTager->iCount = 100000;
		ptrTager->uSize  = uSize;
		_PLMemPool_BeginLock(ptrLock);
			ptrTager->ptrNextPagerTager = *ptrFirstPageTager;
			//PLSysAPI_RWMberrier;
			*ptrFirstPageTager = ptrTager;
		_PLMemPool_EndLock(ptrLock);
		return ptrTager;
	}

	inline void _PL_MemoryPool_InsidePushPagelist(PLMemoryPageStPtr * ptrFirstList,PLMemoryPageStPtr ptrNewPageHeader,_PLMemPool_Synchron_Lock * ptrLock){
		_PLMemPool_BeginLock(ptrLock);
			ptrNewPageHeader->next = *ptrFirstList;
			//PLSysAPI_RWMberrier;
			*ptrFirstList = ptrNewPageHeader;
			--(*(ptrNewPageHeader->Tag.ptrCount));
		_PLMemPool_EndLock(ptrLock);
	}
	inline bool_pl _PL_MemoryPool_MemoryUnitsPageTager(PLMemoryPageTagerHearStPtr ptrPageTager,PLMemoryPageStPtr * ptrFirstlist,uint32_pl uUnitsCount,_PLMemPool_Synchron_Lock * ptrLock){
		PLMemoryPageStPtr ptrUnit;
		uint32_pl uEndAdder;
		uint32_pl uCurrentAdder;
		ptrPageTager->iCount = 0;
		uEndAdder = ((uint32_pl)ptrPageTager) + ptrPageTager->uSize;
		uCurrentAdder = (uint32_pl)(ptrPageTager->adder.cAdder);
		while((uCurrentAdder + PL_CompilerAllocSize(PLMemoryPageSt)) <= uEndAdder){
			ptrUnit = (PLMemoryPageStPtr)uCurrentAdder;
			ptrUnit->Tag.ptrCount = &(ptrPageTager->iCount);
			ptrUnit->iCount       = 0;
			ptrUnit->iBaseCount   = 0;
			ptrUnit->uSize        = PL_CompilerAllocSize(PLMemoryPageSt);
			_PL_MemoryPool_InsidePushPagelist(ptrFirstlist,ptrUnit,ptrLock);
			uCurrentAdder += PL_CompilerAllocSize(PLMemoryPageSt);
		}
		return true_pl;
	}
	inline PLMemoryPageStPtr  _PL_MemoryPool_InsidePopPagelist(PLMemHandle hmm,PLMemoryPageStPtr * ptrFirstList ,_PLMemPool_Synchron_Lock * ptrLock){
		PLMemoryPageStPtr ptrPage;
		PLMemoryPageTagerHearStPtr ptrPageTager;
		PLMMPOOLPtr ptrMM;
		ptrMM = (PLMMPOOLPtr)hmm;
		_PLMemPool_BeginLock(ptrLock);
			if(*ptrFirstList == NULL_PL){
				_PLMemPool_EndLock(ptrLock);
					ptrPageTager = _PL_MemoryPool_AllocateMemoryPageTager(&(ptrMM->ptrPageTagerFirst),ptrMM->uTagerSize,&(ptrMM->pageTagerLock));
					_PL_MemoryPool_MemoryUnitsPageTager(ptrPageTager,&(ptrMM->ptrPageHeaderFreeList),ptrMM->uSTagerToPageHeaderCount,&(ptrMM->pagefreelistLock));
					_PLMemPool_BeginLock(ptrLock);
			}
			ptrPage=*ptrFirstList;
			//PLSysAPI_RWMberrier;
			*ptrFirstList = ptrPage->next;
			if((*(ptrPage->Tag.ptrCount))<0)
				(*(ptrPage->Tag.ptrCount)) = 0;
			++(*(ptrPage->Tag.ptrCount));
		_PLMemPool_EndLock(ptrLock);
		return ptrPage;
	}

	inline bool_pl _PL_MemoryPool_MemoryUnitsPage(PLMMPOOLPtr hmm,PLMemoryPageStPtr ptrPage,PLMemoryBlockPtr * ptrFirstBlock,uint32_pl uUnitSize,uint32_pl uCurrentIndex,_PLMemPool_Synchron_Lock * ptrLock){
		PLMemoryBlockPtr ptrBlock;
		uint_pl uBaseAdder;
		uint_pl uFreeSpace;
		uint_pl uIndex;
		ptrPage->iCount = 0;
		ptrPage->iBaseCount = 0;
		uBaseAdder  = 0;
		while((uBaseAdder + uUnitSize) <= ptrPage->uDataSize){
			ptrBlock = (PLMemoryBlockPtr)(uBaseAdder + ptrPage->adder.uAdder);
			ptrBlock->Tag.ptrCount = &(ptrPage->iCount);
			++(ptrPage->iBaseCount);
			_PL_MemoryPool_InsidePushBlock(ptrFirstBlock,ptrBlock,ptrLock);
			uBaseAdder += uUnitSize;
		}
		uFreeSpace = uBaseAdder!=ptrPage->uDataSize ? ptrPage->uDataSize - uBaseAdder : 0;
		uIndex = uCurrentIndex - 1;
		while(uFreeSpace >= hmm->uBlockGranuSize){
			if(uFreeSpace >= hmm->ptrBlockAlignedlist[uIndex]){
				ptrBlock = (PLMemoryBlockPtr)(uBaseAdder + ptrPage->adder.uAdder);
				ptrBlock->Tag.ptrCount = &(ptrPage->iCount);
				++(ptrPage->iBaseCount);
				_PL_MemoryPool_InsidePushBlock(&(hmm->ptrfreelist[uIndex]),ptrBlock,ptrLock);
				uBaseAdder += hmm->ptrBlockAlignedlist[uIndex];
				uFreeSpace -= hmm->ptrBlockAlignedlist[uIndex];
			}else{
				--uIndex;
			}
		}
	   return true_pl;
	}
	inline void_pl   _PL_MemoryPool_GetSystemMMPama(PLMMPoolPamaStPtr ptrMMPama){
		#if PLOperat_System == PLOperatSystem_Linux
				ptrMMPama->uSystemAddresALlocateGranuSize = 65536;
				ptrMMPama->uSystemPageGranuSize = 4096;
		#elif PLOperat_System == PLOperatSystem_Window
				ptrMMPama->uSystemAddresALlocateGranuSize = 65536;
				ptrMMPama->uSystemPageGranuSize = 4096;
		#endif
	}

	_PLE_lib_c _CallStack_default_ void_pl * 		AllocateMemoryPool(PLMemHandle hmm,uint_pl uSize);
	_PLE_lib_c _CallStack_default_ void_pl  		FreeMemoryPool(PLMemHandle hmm,void_pl * pPtr);
	_PLE_lib_c _CallStack_default_ PLMemHandle      InitializtionMemoryPool(uint_pl uBlockGranuSize,uint_pl uBlockMaxSize,uint_pl uPageGranuSize,uint_pl uTag);
	_PLE_lib_c _CallStack_default_ HPL_Result    	DestoryMemoryPool(PLMemHandle hmm);
	_PLE_lib_c _CallStack_default_ void_pl * 		AllocatePrivateMemoryPool(PLMemHandle hmm,PLMemHandle_PID hPID,uint_pl uSize);
	_PLE_lib_c _CallStack_default_ void_pl    		FreePrivateMemoryPool(PLMemHandle hmm,PLMemHandle_PID hPID,void_pl * pPtr);
	_PLE_lib_c _CallStack_default_ HPL_Result       TransferMemoryManager(PLMemHandle NewHandle,PLMemHandle OldHandle,void_pl * pPtr);
*/
			   _CallStack_default_ HPL_Result 	    distri_InitializtionMemory_PL();
	_PLE_lib_c _CallStack_default_ void_pl *        distri_AllocateMemory_PL(intV_pl iSize);
	_PLE_lib_c _CallStack_default_ void_pl          distri_FreeMemory_PL(void_pl * ptrMem);
								   intV_pl  		distri_GetIndex(intV_pl iSize);
								   intV_pl  		distri_GetObjectSize(intV_pl iSize);
	_PLE_lib_c _CallStack_default_ void_pl *        distri_TLSAllocateMemory_PL(intV_pl iSize);
	_PLE_lib_c _CallStack_default_ void_pl          distri_TLPLreeMemory_PL(void_pl * ptrMem);
								   intV_pl       	distri_GetTLSIndex(intV_pl iSize);
								   intV_pl      	distri_GetTLSObjectSizeAligned(intV_pl iSize);
			   _CallStack_default_ HPL_Result       distri_DestoryMemory_PL();

	PLMemBlock * 		 distri_PopBlockQueue();
	void_pl 	 		 distri_PushBlockQueue(PLMemBlock * ptrBlock);
	bool_pl 	 	 	 distri_isBigMemory(void_pl * ptrBlock);
	inline bool_pl 		 distri_NeedBigMemory(intV_pl iSize){
		uintV_pl uAlignSize;
		uAlignSize = PLMem_Const_MemoryAllocMaxBlockPool;
		return  *((intV_pl *)(&uAlignSize)) < iSize ? true_pl : false_pl ;
	}
	void_pl            * distri_AllocateBigMemory(intV_pl iSize);
	void_pl      		 	distri_FreeBigMemory(void_pl * ptrBlock);
	PLMemAllocateOrgan * distri_CreateAllocateOrganMemory();
	PLMemAllocateOrgan * distri_GetTLSAllocateOrganMemory();
	HPL_Result   		 	distri_DestoryAllocateOrganMemory(PLMemAllocateOrgan * ptrMAO);
	inline intV_pl       distri_GetTLSIndex_Aligned(intV_pl iSize){
		intV_pl iIndex;
		//if()
		iIndex = 0;
		return iIndex;
	}

	#define  PLSysAPI_Mem_AllocateMemoryPool 		distri_AllocateMemory_PL
	#define  PLSysAPI_Mem_FreeMemoryPool 	 		distri_FreeMemory_PL
	#define  PLSysAPI_Mem_TLSAllocateMemoryPool 	distri_TLSAllocateMemory_PL
	#define  PLSysAPI_Mem_TLPLreeMemoryPool 		distri_TLPLreeMemory_PL
	#define  PLSysAPI_Mem_InitializtionMemoryPool   distri_InitializtionMemory_PL
	#define  PLSysAPI_Mem_DestoryMemoryPool 		distri_DestoryMemory_PL


	#define  PLNewClass(_class)						new (PLSysAPI_Mem_AllocateMemoryPool(PL_Sizeof(_class))) _class()
	#define  PLDeleteClass(obj,_class)				{obj->~_class(); PLSysAPI_Mem_FreeMemoryPool((void_pl *)obj);}
//	#define  PLSysAPI_Mem_GAllocateMemoryPool(uSize)			PLSysAPI_Mem_AllocateMemoryPool(g_ptrCurrentEngineState->hMM,uSize)
//	#define  PLSysAPI_Mem_GFreeMemoryPool(pPtr)	 				PLSysAPI_Mem_FreeMemoryPool(g_ptrCurrentEngineState->hMM,pPtr)
//	#define  PLSysAPI_Mem_GTLSAllocateMemoryPool(hPID,uSize) 	PLSysAPI_Mem_TLSAllocateMemoryPool(g_ptrCurrentEngineState->hMM,hPID,uSize)
//	#define  PLSysAPI_Mem_GTLPLreeMemoryPool(hPID,pPtr)			PLSysAPI_Mem_TLPLreeMemoryPool(g_ptrCurrentEngineState->hMM,hPID,pPtr)

#endif /* PLENGINEMEMORYPOOL_H_ */
