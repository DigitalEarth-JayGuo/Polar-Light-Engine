/*
 * PLEngineMemoryPool.cpp
 *
 *  Created on: 2009-6-30
 *      Author: root
 */

#include "header/PLEngineMemoryPool.h"
	/*
	 *
	 * SystemWith API Function Pointer
	 *
	 * */
	//	_PLE_lib_Variable __InitializSystemTimerPL__      InitializSystemTimerPL;
/*
PLMemHandle     InitializtionMemoryPool(uint_pl uBlockGranuSize,uint_pl uBlockMaxSize,uint_pl uPageGranuSize,uint_pl uTag){
	PLMMPOOLPtr hmm;
	PLMMPoolPamaSt StSystemPama;
	PLMemoryPageStPtr ptrPage;
	PLMemoryPageTagerHearStPtr ptrPageTager;
	void_pl * pDataAdder;
	uint_pl uInBlockGranuSize;
	uint_pl uInBlockMaxSize;
	uint_pl uInPageGranuSize;
	uint_pl uCount;
	uint_pl uSize;
	if((uBlockGranuSize <=0) || (uPageGranuSize<=0))
		return NULL_PL;
	//clear 0 MMPoolPamaSt struct
	PLSysAPI_MemoryClearZero(&StSystemPama,PL_CompilerAllocSize(PLMMPoolPamaSt));
	//get system about memory allocate param data
	_PL_MemoryPool_GetSystemMMPama(&StSystemPama);
	//test down value is 2^n*1 if everyone is false ,return NULL_PL
	if(PLSysAPI_Exis2logValue(StSystemPama.uSystemAddresALlocateGranuSize)==false_pl || PLSysAPI_Exis2logValue(StSystemPama.uSystemPageGranuSize)==false_pl || PLSysAPI_Exis2logValue(uBlockGranuSize)==false_pl){
		return NULL_PL;
	}

//	uBlockGranuSize = ((uTag & _MemPool_BlockCompel_DataSize)==_MemPool_BlockCompel_DataSize) ? Alignment(uBlockGranuSize,8) : Alignment((uBlockGranuSize + MemoryBlockHeaderSize),8);
	uInBlockGranuSize = uBlockGranuSize;
	uInBlockMaxSize   = uBlockMaxSize;
	uInPageGranuSize  = uPageGranuSize;


//	if((uTag & _MemPool_BlockCompel_DataSize)==_MemPool_BlockCompel_DataSize){
//		uInBlockGranuSize+=_MemoryPool_BlockHeaderSize;
//	}
   //Block gramu size 8 byte alignment
	uInBlockGranuSize = PLSysAPI_Alignment(uInBlockGranuSize,8);


	if(uInBlockMaxSize<uInBlockGranuSize)
		uInBlockMaxSize = uInBlockGranuSize;
	//one Memory Block max size
	uInBlockMaxSize = (PLSysAPI_Alignment(uBlockMaxSize,8));
	//Calculated block array count
	uCount   = uInBlockMaxSize / uBlockGranuSize;
	if(uInBlockMaxSize % uBlockGranuSize){
		uCount++;
	}
	//Calculated Block max size
	uInBlockMaxSize = uCount * uBlockGranuSize;
	if(uCount<=0)
		return NULL_PL;
	uCount++;
	//Get allocae system memorypage granu , must and SystemPageGranu alignment
	uPageGranuSize = PLSysAPI_Alignment(uInPageGranuSize,StSystemPama.uSystemPageGranuSize);
	uInPageGranuSize = uPageGranuSize;
	uSize = PL_CompilerAllocSize(PLMMPOOL) + (PL_CompilerAllocSize(PLMemoryBlockPtr) + PL_CompilerAllocSize(uint32_pl *)) * uCount; //Calculated MemPool Data Struct amount memory space
	hmm = (PLMMPOOLPtr)PLSysAPI_AllocateMemory(uSize);
	PLSysAPI_MemoryClearZero(hmm,uSize);																	 //clear struct data
	//if don't allocate memory is exit . and return NULL_PL value
	if(hmm==NULL_PL){
		return NULL_PL;
	}
	hmm->uSize  = uSize;																			  // struct size
	PLSysAPI_MemoryCpy(&(hmm->StSystemPama),&StSystemPama,PL_CompilerAllocSize(PLMMPoolPamaSt)); //copy getsystempama to struct param
	hmm->uCount = uCount;
	hmm->iGene  = 0;
	hmm->uBasePageGranu        = uInPageGranuSize;
	hmm->uCurrentPageGranu     = uInPageGranuSize;
	hmm->uTag                  = uTag;
	hmm->ptrPageList           = NULL_PL;      // pointer pagehear struct signed link table
	hmm->ptrBlockAlignedlist   = (uint32_pl *)(((uint32_pl)(hmm)) + PL_CompilerAllocSize(PLMMPOOL)); //(unsigned int *)((unsigned int)(hmm->ptrPageList) + sizeof(MemoryPageSt) * uCount);
	hmm->ptrfreelist           = (PLMemoryBlockPtr *)(((uint32_pl)(hmm->ptrBlockAlignedlist)) + (PL_CompilerAllocSize(uint32_pl *) * uCount));
	hmm->ptrPageTagerFirst     = NULL_PL;	   // pointer pageheader use memory space signed link table
	hmm->ptrPageHeaderFreeList = NULL_PL;	   // Unite free pageheader block signed link table
	_PLMemPool_InitializationLock(&(hmm->pagelock));			//initialize lock
	_PLMemPool_InitializationLock(&(hmm->blocklock));
	_PLMemPool_InitializationLock(&(hmm->pageTagerLock));
	_PLMemPool_InitializationLock(&(hmm->pagefreelistLock));
	hmm->uBlockGranuSize     = uInBlockGranuSize;
	hmm->uBlockMaxSize       = uInBlockMaxSize;
	hmm->uTagerSize          = PLSysAPI_Alignment((PL_CompilerAllocSize(PLMemoryPageSt) * 1000 + _PLMemoryPool_PageTagerHeaderSize),hmm->StSystemPama.uSystemPageGranuSize);
	hmm->uSTagerToPageHeaderCount = hmm->uTagerSize / PL_CompilerAllocSize(PLMemoryPageSt);	//Calculated one PageTager stroe pageheader count
	// allocate first pagetager memory space
	ptrPageTager =  _PL_MemoryPool_AllocateMemoryPageTager(&(hmm->ptrPageTagerFirst),hmm->uTagerSize,&(hmm->pageTagerLock));
	//if allocate memory space fail destorymemorypool exit and return NULL_PL value
	if(ptrPageTager==NULL_PL){
		DestoryMemoryPool(hmm);
		return NULL_PL;
	}
	if(_PL_MemoryPool_MemoryUnitsPageTager(ptrPageTager,&(hmm->ptrPageHeaderFreeList),hmm->uSTagerToPageHeaderCount,&(hmm->pagefreelistLock))==false_pl){
		DestoryMemoryPool(hmm);
		return NULL_PL;
	}
	for(uint32_pl uStatCount=0;uStatCount<uCount;uStatCount++){
		if(uStatCount == 0){
			hmm->ptrBlockAlignedlist[uStatCount] = 0;
			continue;
		}
		hmm->ptrBlockAlignedlist[uStatCount] = (hmm->uBlockGranuSize * uStatCount) & 0xfffff;
		ptrPage    = _PL_MemoryPool_InsidePopPagelist(hmm,&(hmm->ptrPageHeaderFreeList),&(hmm->pagefreelistLock)); //AllocateMemoryPage(&(hmm->ptrPageList[uStatCount]) ,hmm->uCurrentPageGranu,&(hmm->pagelock));
		pDataAdder = PLSysAPI_AllocateMemory(hmm->uCurrentPageGranu);
		if((ptrPage==NULL_PL)|| (pDataAdder==NULL_PL)){
			DestoryMemoryPool((PLMemHandle)hmm);
			return NULL_PL;
		}
		ptrPage->uDataSize = hmm->uCurrentPageGranu;
		ptrPage->adder.ptr = pDataAdder;
		_PL_MemoryPool_MemoryUnitsPage(hmm,ptrPage,&(hmm->ptrfreelist[uStatCount]),hmm->ptrBlockAlignedlist[uStatCount],uStatCount,&(hmm->blocklock));
		_PL_MemoryPool_InsidePushPagelist(&(hmm->ptrPageList),ptrPage,&(hmm->pagelock));
	}
	return (PLMemHandle)hmm;
}

HPL_Result   	DestoryMemoryPool(PLMemHandle hmm){
	PLMMPOOLPtr  ptrMM;
	PLMemoryPageTagerHearStPtr ptrPageTager;
	PLMemoryPageStPtr ptrPage;
	if(hmm==NULL_PL)
		return HPLResult_Fail;
	ptrMM = (PLMMPOOLPtr)hmm;
	while(ptrMM->ptrPageList!=NULL_PL){
		ptrPage = 	ptrMM->ptrPageList;
		//PLSysAPI_RWMberrier;
		ptrMM->ptrPageList = ptrPage->next;
		if(ptrPage->adder.ptr!=NULL_PL){
			PLSysAPI_FreeMemory(ptrPage->adder.ptr);
			ptrPage->adder.ptr = NULL_PL;
		}
		--(ptrPage->iBaseCount);
		--(ptrPage->iCount);
	}
	while(ptrMM->ptrPageTagerFirst!=NULL_PL){
		ptrPageTager = ptrMM->ptrPageTagerFirst;
		//PLSysAPI_RWMberrier;
		ptrMM->ptrPageTagerFirst = ptrPageTager->ptrNextPagerTager;
		PLSysAPI_FreeMemory(ptrPageTager);
	}
	ptrMM->ptrfreelist = NULL_PL;
	ptrMM->ptrPageList = NULL_PL;
	ptrMM->ptrPageHeaderFreeList = NULL_PL;
	_PLMemPool_ReleaseLock(&(ptrMM->blocklock));
	_PLMemPool_ReleaseLock(&(ptrMM->pagelock));
	_PLMemPool_ReleaseLock(&(ptrMM->pageTagerLock));
	_PLMemPool_ReleaseLock(&(ptrMM->pagefreelistLock));
	PLSysAPI_FreeMemory(ptrMM);
	return HPLResult_OK;
}

void_pl * InitializtionMemoryPool(PLMemHandle hmm,uint_pl uSize){
	PLMMPOOLPtr ptrMM;
	PLMemoryBlockPtr ptrBlock;
	PLMemoryPageStPtr ptrPage;
	uint_pl uAllocateSize;
	uint_pl uStateCount;
	ptrMM = (PLMMPOOLPtr)hmm;
	uAllocateSize = PLSysAPI_Alignment((uSize + _PLMemoryPool_BlockHeaderSize),ptrMM->uBlockGranuSize);
	if(uAllocateSize>ptrMM->uBlockMaxSize){
		ptrBlock = (PLMemoryBlockPtr)PLSysAPI_AllocateMemory(uAllocateSize);
		if(ptrBlock==NULL_PL)
			return NULL_PL;
		ptrBlock->Tag.ptrCount=NULL_PL;
		ptrBlock->uSize = uAllocateSize;
		return (void_pl *)(ptrBlock->adder.cAdder);
	}
	uStateCount   =  uAllocateSize/ptrMM->uBlockGranuSize;
	_PLMemPool_BeginLock(&(ptrMM->blocklock));
		if(ptrMM->ptrfreelist[uStateCount]==NULL_PL){
			_PLMemPool_EndLock(&(ptrMM->blocklock));
				ptrPage  = _PL_MemoryPool_InsidePopPagelist(hmm,&(ptrMM->ptrPageHeaderFreeList),&(ptrMM->pagefreelistLock));
				if(ptrPage==NULL_PL)
					return NULL_PL;
				ptrPage->uDataSize = ptrMM->ptrBlockAlignedlist[uStateCount];
				ptrPage->adder.ptr = PLSysAPI_AllocateMemory(ptrPage->uDataSize);
				_PL_MemoryPool_MemoryUnitsPage(ptrMM,ptrPage,&(ptrMM->ptrfreelist[uStateCount]),ptrMM->ptrBlockAlignedlist[uStateCount],uStateCount,&(ptrMM->blocklock));
				_PL_MemoryPool_InsidePushPagelist(&(ptrMM->ptrPageList),ptrPage,&(ptrMM->pagelock));
			_PLMemPool_BeginLock(&(ptrMM->blocklock));
		}
		ptrBlock = ptrMM->ptrfreelist[uStateCount];
		ptrMM->ptrfreelist[uStateCount] = ptrBlock->adder.next;
	_PLMemPool_EndLock(&(ptrMM->blocklock));
	return (void_pl *)(ptrBlock->adder.cAdder);
}
void * AllocateMemoryPool(HMWND hmm,uint32_pl uSize){
	PLMMPOOLPtr ptrMM;
	PLMemoryBlockPtr ptrBlock;
	PLMemoryPageStPtr ptrPage;
	uint32_pl uAllocateSize;
	uint32_pl uStateCount;
	ptrMM = (PLMMPOOLPtr)hmm;
	uAllocateSize = PLSysAPI_Alignment((uSize + _PLMemoryPool_BlockHeaderSize),ptrMM->uBlockGranuSize);
	if(uAllocateSize>ptrMM->uBlockMaxSize){
		ptrBlock = (PLMemoryBlockPtr)PLSysAPI_AllocateMemory(uAllocateSize);
		if(ptrBlock==NULL)
			return NULL;
		ptrBlock->Tag.ptrCount=NULL;
		ptrBlock->uSize = uAllocateSize;
		return (void *)(ptrBlock->adder.cAdder);
	}
	uStateCount   =  uAllocateSize/ptrMM->uBlockGranuSize;
	_PLMemPool_BeginLock(&(ptrMM->blocklock));
		if(ptrMM->ptrfreelist[uStateCount]==NULL){
			_PLMemPool_EndLock(&(ptrMM->blocklock));
			ptrPage  = _PL_MemoryPool_InsidePopPagelist(hmm,&(ptrMM->ptrPageHeaderFreeList),&(ptrMM->pagefreelistLock));
			if(ptrPage==NULL)
				return NULL;
			ptrPage->uDataSize = ptrMM->ptrBlockAlignedlist[uStateCount];
			ptrPage->adder.ptr = PLSysAPI_AllocateMemory(ptrPage->uDataSize);
			_PL_MemoryPool_MemoryUnitsPage(ptrMM,ptrPage,&(ptrMM->ptrfreelist[uStateCount]),ptrMM->ptrBlockAlignedlist[uStateCount],uStateCount,&(ptrMM->blocklock));
			_PL_MemoryPool_InsidePushPagelist(&(ptrMM->ptrPageList),ptrPage,&(ptrMM->pagelock));
			_PLMemPool_BeginLock(&(ptrMM->blocklock));
		}
		ptrBlock = ptrMM->ptrfreelist[uStateCount];
		ptrMM->ptrfreelist[uStateCount] = ptrBlock->adder.next;
		_PLMemPool_EndLock(&(ptrMM->blocklock));
	return (void *)(ptrBlock->adder.cAdder);
}
void_pl   FreeMemoryPool(PLMemHandle hmm,void_pl * pPtr){
	PLMMPOOLPtr ptrMM;
	PLMemoryBlockPtr ptrBlock;
	uint_pl uIndex;
	ptrBlock = (PLMemoryBlockPtr) (((uint_pl)pPtr) - _PLMemoryPool_BlockHeaderSize);
	ptrMM    = (PLMMPOOLPtr)hmm;
	if(ptrBlock->uSize > ptrMM->uBlockMaxSize){
		PLSysAPI_FreeMemory(pPtr);
		return;
	}
	uIndex = ptrBlock->uSize/ptrMM->uBlockGranuSize;
	_PL_MemoryPool_InsidePushBlock(&(ptrMM->ptrfreelist[uIndex]),ptrBlock,&(ptrMM->blocklock));
}
void_pl * AllocatePrivateMemoryPool(PLMemHandle hmm,PLMemHandle_PID hPID,uint_pl uSize){
	return AllocateMemoryPool(hmm,uSize);
}
void_pl   FreePrivateMemoryPool(PLMemHandle hmm,PLMemHandle_PID hPID,void_pl * pPtr){
	FreeMemoryPool(hmm,pPtr);
}
HPL_Result TransferMemoryManager(PLMemHandle NewHandle,PLMemHandle OldHandle,void_pl * pPtr){
	return HPLResult_OK;
}
*/
PLMemBlock * distri_PopBlockQueue(intV_pl iSize){
	PLMemBlock * ptrBlock;
	ptrBlock = NULL_PL;

	return ptrBlock;
}
void_pl distri_PushBlockQueue(PLMemBlock * ptrBlock){

}
void_pl * distri_AllocateBigMemory(intV_pl iSize){
	return PLSysAPI_AllocateMemory(iSize);
}
void_pl distri_FreeBigMemory(void_pl * ptrBlock){
	PLSysAPI_FreeMemory(ptrBlock);
}
bool_pl distri_isBigMemory(void_pl * ptrBlock){
	return false_pl;
}
HPL_Result distri_InitializtionMemory_PL(){
	HPL_Result hResult;
	PLMemFreeObject * ptrFObject;
	AddresValue_pl addres;
	hResult = HPLResult_Fail;
	if(g_MemPoolManager.iState > 0)
		return hResult;
	g_MemPoolManager.iState = 2;
	if(g_allocateOrganKey != PLTLSKey_Invalid){
		PLSysAPI_SystemProcess_FreeTLSKey(&g_allocateOrganKey);
		g_allocateOrganKey = PLTLSKey_Invalid;
	}
	if(HResulPL_FAILED(PLSysAPI_SystemProcess_AllocTLSKey(&(g_allocateOrganKey),PLTLSKey_MemoryAllocateOrganKey_Destory)) == true_pl){
		g_allocateOrganKey = PLTLSKey_Invalid;
		return hResult;
	}
	g_iAOMaxSize 	 = 0;
	g_iAOCurrentSize = 0;
	while(g_AllocateOrganFreeList != NULL_PL){
		ptrFObject = g_AllocateOrganFreeList;
		g_AllocateOrganFreeList = g_AllocateOrganFreeList->ptrNextObject;
		addres = (AddresValue_pl)ptrFObject;
		addres = addres - PL_CompilerAllocSize(PLMemFreeObject);
		PLSysAPI_FreeMemory((void_pl *)(((PLMemFreeObject *)addres)->ptrNextObject));
	}
	g_AOFreeListLock = PLSyn_Const_SynSpinLockPass;
	PLSysAPI_MemoryClearZero(g_MemPoolManager.MapItemList,PL_CompilerAllocSize(PLGMemMapItem) * PLMem_Const_MemoryManagerMaxItemCount);
	PLSysAPI_MemoryClearZero(&(g_MemPoolManager.publicAllocOrgan),PL_CompilerAllocSize(PLMemAllocateOrgan));

	g_MemPoolManager.iState = 5;
	return hResult;
}


intV_pl distri_GetIndex(intV_pl iSize){
	intV_pl iIndex;
	if(iSize>PLMem_Const_AllocSmallObjectMaxSize){
		iIndex = (iSize - 1) >> 6;
	}else{
		iIndex = 0;
	}
	return iIndex;
}
intV_pl distri_GetObjectSize(intV_pl iSize){
	intV_pl iObjectSize;

	if(iSize <= PLMem_Const_TLSAllocSmallObjectMaxSize){
		iObjectSize = PLSysAPI_Alignment(iSize,PLMem_Const_TLSAllocSmallObjectMinSize);
	}else{
		iObjectSize = 0;
	}
	return iObjectSize;
}
intV_pl distri_GetTLSIndex(intV_pl iSize){
	intV_pl iIndex;
	//intV_pl iMinSHR;
	if(iSize <= PLMem_Const_TLSAllocSmallObjectMaxSize){
		//iMinSHR = PLSysAPI_GetHotBitPosH2L32(PLMem_Const_TLSAllocSmallObjectMinSize);
		//iIndex >>= iMinSHR;
		iSize = (iSize-1) >> 3;
	}else if(iSize <= PLMem_Const_GroupAllocObjectMaxSize){
		intV_pl iOrder;
		iOrder = PLSysAPI_GetHotBitPosH2L32(iSize - 1);
//			iIndex = (PLMem_Const_TLSAllocSmallObjectMaxSize>>3) - (4*6)
//								- 4 + (4*iOrder) + ((iSize - 1)>>(iOrder-2));
//			iIndex = (PLMem_Const_TLSAllocSmallObjectMaxSize>>3) - (6 << 2)
//								- 4 + (iOrder<<2) + ((iSize - 1)>>(iOrder-2));
		iIndex = PLMem_ComputeIntervalSubsectionSize(PLMem_Const_TLSAllocSmallObjectMaxSize>>3,iSize,iOrder);
	}else{
		//PLMem_Const_TLSBigBlckPoolIndexBase
		iIndex = 31;
	}
	return iIndex;
}
intV_pl distri_GetTLSObjectSizeAligned(intV_pl iSize){
	intV_pl iObjectSize;
	if(iSize <= PLMem_Const_TLSAllocSmallObjectMaxSize){
		iObjectSize = PLSysAPI_Alignment(iSize,PLMem_Const_TLSAllocSmallObjectMinSize);
	}else if(iSize <= PLMem_Const_GroupAllocObjectMaxSize) {
		intV_pl iOrder;
		iOrder = PLSysAPI_GetHotBitPosH2L32(iSize - 1);
		iObjectSize = PLSysAPI_Alignment(iSize,(128 >> (9-(PLSysAPI_GetHotBitPosH2L32(iSize - 1)))));
	}else{
		iObjectSize = iSize;
	}
	return iObjectSize;
}
void_pl * distri_AllocateMemory_PL(intV_pl iSize){
	void_pl * ptrResult;
	intV_pl   iIndex;
	intV_pl   iObjectSize;
	PLMemAllocateOrgan * ptrMAO;
	ptrResult = NULL_PL;

	return PLSysAPI_AllocateMemory(iSize);

	if(distri_NeedBigMemory(iSize) == true_pl)
		return distri_AllocateBigMemory(iSize);
	ptrMAO = &(g_MemPoolManager.publicAllocOrgan);
	ptrResult = PLSysAPI_AllocateMemory(iSize);
	iIndex 	  = distri_GetIndex(iSize);
	iObjectSize = distri_GetObjectSize(iSize);
	if(ptrMAO->PackageList[iIndex].ptrList != NULL_PL){
		ptrResult = ptrMAO->PackageList[iIndex].ptrList;
		ptrMAO->PackageList[iIndex].ptrList = ptrMAO->PackageList[iIndex].ptrList->ptrNextObject;
	}else{
		if(ptrMAO->PackageList[iIndex].ptrActive == NULL_PL){
			ptrMAO->PackageList[iIndex].ptrActive = distri_PopBlockQueue(distri_GetTLSObjectSizeAligned(iObjectSize));
		}
		ptrResult = (PLMemFreeObject *)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr);
		ptrMAO->PackageList[iIndex].ptrActive->bumpPtr = (void_pl *)((AddresValue_pl)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) -  ptrMAO->PackageList[iIndex].ptrActive->iAllocSize);
		if( (AddresValue_pl)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) <  (AddresValue_pl)(ptrMAO->PackageList[iIndex].ptrActive) + PL_CompilerAllocSize(PLMemBlock)){
			ptrMAO->PackageList[iIndex].ptrActive = (PLMemBlock *)ptrMAO->PackageList[iIndex].ptrActive->ptrNextObject;
		}
	}
	return (void_pl *)ptrResult;
}
void_pl distri_FreeMemory_PL(void_pl * ptrMem){
	PLSysAPI_FreeMemory(ptrMem);
	return;
	if(distri_isBigMemory(ptrMem)==true_pl){
		distri_FreeBigMemory(ptrMem);
		return;
	}

}
void_pl * distri_TLSAllocateMemory_PL(intV_pl iSize){
	PLMemAllocateOrgan * ptrMAO;
	PLMemFreeObject * ptrResult;
	intV_pl   iIndex;
	intV_pl   iObjectSize;
	ptrResult = NULL_PL;

	return PLSysAPI_AllocateMemory(iSize);

	ptrMAO = (PLMemAllocateOrgan *)PLSysAPI_SystemProcess_GetTLSValue(&g_allocateOrganKey);
	if(ptrMAO == NULL_PL){
		ptrMAO = distri_GetTLSAllocateOrganMemory();
		if(ptrMAO ==NULL_PL)
			return NULL_PL;
	}
	if(distri_NeedBigMemory(iSize) == true_pl)
		return distri_AllocateBigMemory(iSize);
	//Get Tls allocate mode index
	iIndex = distri_GetTLSIndex(iSize);
	//Get Tls allocate mode ObjectSize
	iObjectSize = distri_GetTLSObjectSizeAligned(iSize);
	//
	if(ptrMAO->PackageList[iIndex].ptrList != NULL_PL){
		ptrResult = ptrMAO->PackageList[iIndex].ptrList;
		ptrMAO->PackageList[iIndex].ptrList = ptrMAO->PackageList[iIndex].ptrList->ptrNextObject;
	}else{
		if(ptrMAO->PackageList[iIndex].ptrActive == NULL_PL){
			ptrMAO->PackageList[iIndex].ptrActive = distri_PopBlockQueue(distri_GetTLSObjectSizeAligned(iObjectSize));
		}
		ptrResult = (PLMemFreeObject *)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr);
		ptrMAO->PackageList[iIndex].ptrActive->bumpPtr = (void_pl *)((AddresValue_pl)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) -  ptrMAO->PackageList[iIndex].ptrActive->iAllocSize);
		if( (AddresValue_pl)(ptrMAO->PackageList[iIndex].ptrActive->bumpPtr) <  (AddresValue_pl)(ptrMAO->PackageList[iIndex].ptrActive) + PL_CompilerAllocSize(PLMemBlock)){
			ptrMAO->PackageList[iIndex].ptrActive = (PLMemBlock *)ptrMAO->PackageList[iIndex].ptrActive->ptrNextObject;
		}
	}
	//ptrResult = PLSysAPI_AllocateMemory(iSize);
	return (void_pl *)ptrResult;
}
void_pl distri_TLPLreeMemory_PL(void_pl * ptrMem){
	PLSysAPI_FreeMemory(ptrMem);
	return;
	if(distri_isBigMemory(ptrMem)==true_pl){
		distri_FreeBigMemory(ptrMem);
		return;
	}

}
HPL_Result distri_DestoryMemory_PL(){
	HPL_Result hResult;
	PLMemFreeObject * ptrObject;
	AddresValue_pl addres;

	hResult = HPLResult_Fail;
	intV_pl iCount;
	if(g_MemPoolManager.iState!=5)
		return hResult;
	distri_DestoryAllocateOrganMemory((PLMemAllocateOrgan *)PLSysAPI_SystemProcess_GetTLSValue(&g_allocateOrganKey));
	PLSysAPI_SystemProcess_SetTLSValue(&g_allocateOrganKey,NULL_PL);
	g_MemPoolManager.iState = 2;
	iCount = 0;
	while(g_iAOCurrentSize != g_iAOMaxSize){
		PLSysAPI_SystemProcess_Sleep(10000000);
		iCount++;
		if(iCount>=5){
			break;
		}
	}
	PLSysAPI_Syn_EnterSpinLock(&g_AOFreeListLock);
	while(g_AllocateOrganFreeList){
		ptrObject = g_AllocateOrganFreeList;
		g_AllocateOrganFreeList = g_AllocateOrganFreeList->ptrNextObject;
		addres = (AddresValue_pl)ptrObject;
		addres = addres - PL_CompilerAllocSize(PLMemFreeObject);
		PLSysAPI_FreeMemory((void_pl *)(((PLMemFreeObject *)addres)->ptrNextObject));
	}
	g_iAOCurrentSize = 0;
	g_iAOMaxSize     = 0;
	PLSysAPI_Syn_LeaveSpinLock(&g_AOFreeListLock);
	g_AOFreeListLock = PLSyn_Const_SynSpinLockPass;

	PLSysAPI_SystemProcess_FreeTLSKey(&g_allocateOrganKey);
	g_allocateOrganKey = PLTLSKey_Invalid;
	PLSysAPI_MemoryClearZero(g_MemPoolManager.MapItemList,PL_CompilerAllocSize(PLGMemMapItem) * PLMem_Const_MemoryManagerMaxItemCount);
	PLSysAPI_MemoryClearZero(&(g_MemPoolManager.publicAllocOrgan),PL_CompilerAllocSize(PLMemAllocateOrgan));
	g_MemPoolManager.iState = 0;
	hResult = HPLResult_OK;
	return hResult;
}
PLMemAllocateOrgan * distri_GetTLSAllocateOrganMemory(){
	PLMemAllocateOrgan * ptrMAO;
	ptrMAO = distri_CreateAllocateOrganMemory();
	if(ptrMAO !=NULL_PL)
		PLSysAPI_SystemProcess_SetTLSValue(&g_allocateOrganKey,(void_pl *)ptrMAO);
	return ptrMAO;
}
PLMemAllocateOrgan * distri_CreateAllocateOrganMemory(){
	PLMemAllocateOrgan * ptrMAO;
	ptrMAO = NULL_PL;
	// lookat free queue have free object ?
	if(g_AllocateOrganFreeList != NULL_PL){
		//get spin lock
		PLSysAPI_Syn_EnterSpinLock(&g_AOFreeListLock);
		ptrMAO = (PLMemAllocateOrgan *)g_AllocateOrganFreeList;
		//get a object
		if(ptrMAO != NULL_PL){
			g_AllocateOrganFreeList = g_AllocateOrganFreeList->ptrNextObject;
		}
		//release spin lock
		PLSysAPI_Syn_LeaveSpinLock(&g_AOFreeListLock);
		PLSysAPI_Syn_AtomInterAdd(&g_iAOCurrentSize,-1);
	}
	if(ptrMAO == NULL_PL){
		intV_pl iAllocateSize;
		AddresValue_pl addres;
		//Compute struct PLMemAllocateOrgan's size and CPUCacheLine's size and a pointer's size
		iAllocateSize = PL_CompilerAllocSize(PLMemAllocateOrgan) + PLMem_Const_CPUCacheLineAlignedSize + PL_CompilerAllocSize(AddresValue_pl);
		ptrMAO = (PLMemAllocateOrgan *)PLSysAPI_AllocateMemory(iAllocateSize);
		if(ptrMAO == NULL_PL)
			return NULL_PL;
		addres = (AddresValue_pl)ptrMAO;
		//memory addres align
		addres = PLSysAPI_Alignment(addres,PLMem_Const_CPUCacheLineAlignedSize);
		//save start' addres
		((PLMemFreeObject *)addres)->ptrNextObject = (PLMemFreeObject *)(ptrMAO);
		//Compute new struct PLMemAllocateOrgan's's pointer addres
		ptrMAO = (PLMemAllocateOrgan *)(addres + PL_CompilerAllocSize(AddresValue_pl));
		PLSysAPI_MemoryClearZero(ptrMAO,PL_CompilerAllocSize(PLMemAllocateOrgan));
		PLSysAPI_Syn_AtomInterAdd(&g_iAOMaxSize,1);
	}
	return ptrMAO;
}
HPL_Result   distri_DestoryAllocateOrganMemory(PLMemAllocateOrgan * ptrMAO){
	if(g_allocateOrganKey == PLTLSKey_Invalid)
		return HPLResult_Fail;
	PLMemFreeObject * ptrFObject;
	ptrFObject = (PLMemFreeObject *)ptrMAO;
	PLSysAPI_Syn_EnterSpinLock(&g_AOFreeListLock);
	if(g_AllocateOrganFreeList!=NULL_PL){
		ptrFObject->ptrNextObject = g_AllocateOrganFreeList;
	}
	g_AllocateOrganFreeList = ptrFObject;
	PLSysAPI_Syn_LeaveSpinLock(&g_AOFreeListLock);
//	PLSysAPI_Syn_AtomInterAdd(&g_iAOCurrentSize,1);
	return HPLResult_OK;
}

void_pl PLTLSKey_MemoryAllocateOrganKey_Destory(void_pl * ptrData){
	PLMemAllocateOrgan * ptrMAO;
	ptrMAO = (PLMemAllocateOrgan *)ptrData;
	if(ptrMAO == NULL_PL)
		return;
	distri_DestoryAllocateOrganMemory(ptrMAO);
}
