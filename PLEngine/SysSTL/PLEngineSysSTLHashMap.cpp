/*
 * PLEngineSysSTLHashMap.cpp
 *
 *  Created on: 2009-10-13
 *      Author: Administrator
 */
#include "../header/SysSTL/PLEngineSysSTLHashMap.h"

/*
HSHashMap __PLSysAPI_STL_CreateSHashMap_(intV_pl iItemCount,SHashMapParamer & paramer){
	SHashMap * ptrHMap;
	intV_pl iAllocSize;
	intV_pl iPos;
	ptrHMap = NULL_PL;
	if((iItemCount<=0) || ((iPos = PLSysAPI_GetHotBitPosH2LV(iItemCount))<0))
		return NULL_PL;
	if(iPos>0)
		iItemCount = (iItemCount + ((1<<iPos)-1)) & (~((1<<iPos)-1));
	iAllocSize = PL_CompilerAllocSize(SHashMap) +  PL_CompilerAllocSize(SHashMapItemRoot)*(iItemCount - 1);
	ptrHMap = (SHashMap *)PLSysAPI_Mem_AllocateMemoryPool(iAllocSize);
	if(ptrHMap == NULL_PL)
		return NULL_PL;
	PLSysAPI_MemoryClearZero((void_pl *)ptrHMap,iAllocSize);

	ptrHMap->iLength = iItemCount;
	ptrHMap->allocatememory = paramer.allocatememory != NULL_PL ? paramer.allocatememory : __stl_native_allocatememory__;
	ptrHMap->freememory     = paramer.freememory     != NULL_PL ? paramer.freememory     : __stl_native_freememory__;
	ptrHMap->allstring      = paramer.allstring		 != NULL_PL ? paramer.allstring      : __stl_native_allocatenewstring__;
	ptrHMap->freestring     = paramer.freestring	 != NULL_PL ? paramer.freestring     : __stl_native_freestring__;
	ptrHMap->hsshfunc       = paramer.hsshfunc       != NULL_PL ? paramer.hsshfunc       : __stl_native_hashstringFunc__PL__;
	ptrHMap->iCount         = 0;
	for(intV_pl iCount = 0;iCount < iItemCount;iCount++){
		PLSysAPI_Syn_InitializeRWLockRF(ptrHMap->ItemList[iCount].lock);
	}
	return (HSHashMap)ptrHMap;
}
bool_pl   __PLSysAPI_STL_InsertSHashMapData_(HSHashMap hAndle,const_pl char_pl * ptrNameID,intV_pl iSize,void_pl * ptrData){
	SHashMap * ptrHMap;
	SHashMapItem * ptrItem;
	uintV_pl   uKey;
	intV_pl iAllocSize;
	bool_pl    bInsert;
	if((hAndle == NULL_PL) || (ptrNameID == NULL_PL) || (iSize<=0))
		return false_pl;
	bInsert = false_pl;
	ptrHMap = (SHashMap *)hAndle;
	uKey = ptrHMap->hsshfunc(ptrNameID,iSize,ptrHMap->iLength);

	PLSysAPI_Syn_AcquireRWLockWriteRF(ptrHMap->ItemList[uKey].lock);
		ptrItem = ptrHMap->ItemList[uKey].ptrRoot;
		while(ptrItem!=NULL_PL){
			if((iSize == ptrItem->iNIDSize) && (PLSysAPI_MemoryCmp(ptrItem->ptrNameID,ptrNameID,iSize)==0))
				break;
		}
		if(ptrItem != NULL_PL){
			iAllocSize = PL_CompilerAllocSize(SHashMapItem);
			ptrItem = (SHashMapItem *)(ptrHMap->allocatememory(ptrHMap->ptrFuncData,iAllocSize));
			if(ptrItem!=NULL_PL){
				PLSysAPI_MemoryClearZero((void_pl *)ptrItem,iAllocSize);
				ptrItem->iNIDSize = iSize;

				if(ptrHMap->allstring == NULL_PL){
					ptrItem->ptrNameID = (const_pl char_pl *)ptrHMap->allocatememory(ptrHMap->ptrFuncData,iSize+1);
					if(ptrItem->ptrNameID!=NULL_PL){
						PLSysAPI_MemoryClearZero((void_pl *)(ptrItem->ptrNameID),iSize+1);
						PLSysAPI_MemoryCpy((void_pl *)(ptrItem->ptrNameID),ptrNameID,iSize);
					}
				}else{
					ptrItem->ptrNameID = ptrHMap->allstring(ptrNameID,iSize,ptrHMap->ptrFuncData,ptrHMap->allocatememory);
				}
				if(ptrItem->ptrNameID==NULL_PL){
					ptrHMap->freememory(ptrHMap->ptrFuncData,(void_pl *)ptrItem);
					ptrItem = NULL_PL;
				}else{
					ptrItem->ptrNext = ptrHMap->ItemList[uKey].ptrRoot;
					ptrHMap->ItemList[uKey].ptrRoot = ptrItem;
					bInsert = true_pl;
				}
			}
		}
	PLSysAPI_Syn_ReleaseRWLockWriteRF(ptrHMap->ItemList[uKey].lock);
	return bInsert;
}
void_pl * __PLSysAPI_STL_GetSHashMapData_(HSHashMap hAndle,const_pl char_pl * ptrNameID,intV_pl iSize){
	SHashMap * ptrHMap;
	SHashMapItem * ptrItem;
	void_pl * ptrData;
	uintV_pl  uKey;
	ptrData = NULL_PL;
	if((hAndle == NULL_PL) || (ptrNameID == NULL_PL) || (iSize<=0))
		return NULL_PL;
	ptrHMap = (SHashMap *)hAndle;
	uKey = ptrHMap->hsshfunc(ptrNameID,iSize,ptrHMap->iLength);
	PLSysAPI_Syn_AcquireRWLockReadRF(ptrHMap->ItemList[uKey].lock);
		ptrItem = ptrHMap->ItemList[uKey].ptrRoot;
		while(ptrItem!=NULL_PL){
			if((iSize == ptrItem->iNIDSize) && (PLSysAPI_MemoryCmp(ptrItem->ptrNameID,ptrNameID,iSize)==0)){
				ptrData = ptrItem->pData;
				break;
			}
		}
	PLSysAPI_Syn_ReleaseRWLockReadRF(ptrHMap->ItemList[uKey].lock);
	return ptrData;
}
void_pl   __PLSysAPI_STL_DestorySHashMap_(HSHashMap hAndle){
	SHashMap * ptrHMap;
	SHashMapItem * ptrItem;
	SHashMapItem * ptrNext;
	if(hAndle == NULL_PL)
		return;
	ptrHMap = (SHashMap *)hAndle;
	for(intV_pl iCount = 0;iCount<ptrHMap->iLength;iCount++){
		PLSysAPI_Syn_ReleaseRWLockRF(ptrHMap->ItemList[iCount].lock);
		ptrNext = ptrHMap->ItemList[iCount].ptrRoot;
		ptrHMap->ItemList[iCount].ptrRoot = NULL_PL;
		while(ptrNext!=NULL_PL){
			ptrItem = ptrNext;
			ptrNext = ptrNext->ptrNext;

//			if(ptrHMap->freestring == NULL_PL){
//				ptrHMap->freememory(ptrHMap->ptrFuncData,(void_pl *)(ptrItem->ptrNameID));
//			}else{
				ptrHMap->freestring(ptrItem->ptrNameID,ptrItem->iNIDSize,ptrHMap->ptrFuncData,ptrHMap->freememory);
//			}
			ptrHMap->freememory(ptrHMap->ptrFuncData,(void_pl *)ptrItem);
		}
	}
	PLSysAPI_Mem_FreeMemoryPool((void_pl *)ptrHMap);
}
uintV_pl  __stl_native_hashstringFunc__PL__(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange){
	uintV_pl uHKey;
	uHKey = 0;
	for(intV_pl iCount = 0;iCount < iSize;iCount++){
		uHKey = ptrKey[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
	}
	return uHKey & (iRange-1);
}
void_pl * __stl_native_allocatememory__				(void_pl * ptrData,intV_pl iSize){
	return PLSysAPI_Mem_TLSAllocateMemoryPool(iSize);
}
void_pl	  __stl_native_freememory__					(void_pl * ptrData,void_pl * ptrFree){
	PLSysAPI_Mem_FreeMemoryPool(ptrFree);
}
const_pl char_pl * __stl_native_allocatenewstring__ (const_pl char_pl * ptrSrc,intV_pl iSrcSize,void_pl * ptrData,__stl_allocatememory__PL__ afunc){
	char_pl * ptrDest;
	ptrDest = (char_pl *)afunc(ptrData,iSrcSize+1);
	if(ptrDest != NULL_PL){
		PLSysAPI_MemoryClearZero(ptrDest,iSrcSize + 1);
		PLSysAPI_MemoryCpy(ptrDest,ptrSrc,iSrcSize);
	}
	return (const_pl char_pl *)ptrDest;
}
void_pl  __stl_native_freestring__					(const_pl char_pl * ptrSrc,intV_pl iSrcSize,void_pl * ptrData,__stl_freememory__PL__ ffunc){
	ffunc(ptrData,(void_pl *)ptrSrc);
}
*/

