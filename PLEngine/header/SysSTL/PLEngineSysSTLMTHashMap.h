/*
 * PLEngineSysSTLMTHashMap.h
 *
 *  Created on: 2010-4-21
 *      Author: wl
 */
#include "../PLEngineH.h"
#include "../PLEngineBaseDataType.h"
#include "../PLEngineSysAPI.h"
#include "../PLEngineDefine.h"
#include "../PLEngineInface.h"
#include "../PLEngineMemoryPool.h"
#ifndef PLENGINESYSSTLMTHASHMAP_H_
#define PLENGINESYSSTLMTHASHMAP_H_

#pragma pack(4)

template <typename MtKey , typename MTItem>
	struct __plstl__MTHashMapItem_{
		struct __plstl__MTHashMapItem_<MtKey , MTItem>  * ptrNext;
		MtKey						  tKey;
		int                           iKeySize;
		MTItem                        itemdata;
	};
template <typename MtSlotKey , typename MTSlotItem , typename MtSlotlock>
	struct __plstl__MTHashMapSlot_{
		struct __plstl__MTHashMapItem_<MtSlotKey, MTSlotItem> * ptrNext;
		MtSlotlock lock;
		volatile_pl intV_pl iCount;
	};
template<typename nkey ,typename nData,typename Slotlock ,typename nHashItem = __plstl__MTHashMapItem_ < nkey ,nData > >
	struct __plstl__MTHashMap_CmpFunc {
		static inline uintV_pl Calculate_hash(nkey key,intV_pl iSize,intV_pl iRange){
			uintV_pl uHKey;
			uHKey = 0;
			for(intV_pl iCount = 0;iCount < iSize;iCount++){
				uHKey = key[iCount] + (uHKey << 6) + (uHKey << 16) - uHKey;
			}
			return (uHKey % iRange); //uHKey & (iRange-1);
		}
		static inline bool KeyEqule(nkey key,intV_pl iKey,nkey newkey ,intV_pl iNewKey){
			return ((iKey == iNewKey) && PLSysAPI_SysStringCmp(key,newkey,iKey)==0) ? true : false;
		}
		static inline void InitializeHashItem(nHashItem * ptrHItem){
			PLSysAPI_MemoryClearZero((void *)ptrHItem,sizeof(nHashItem));
		};
		static inline void DestoryHashItem(nHashItem * ptrHItem){
			PLSysAPI_MemoryClearZero((void *)ptrHItem,sizeof(nHashItem));
		}
		static inline intV_pl LockSlot(Slotlock & lock){

			return 0;
		}
		static inline intV_pl UnLockSlot(Slotlock & lock){
			return 0;
		}
		static inline intV_pl InitializeSlotLock(Slotlock & lock){
			return 0;
		}
		static inline void_pl DestorySlotLock(Slotlock & lock){

		}
	};
#pragma pack()

template <typename TKey,typename TItem, typename TSlot ,typename _disposal_func = __plstl__MTHashMap_CmpFunc< TKey , TItem , TSlot> >
class __plstl_MTHashMap_class{
public:
	typedef struct __Iterator{
		__plstl__MTHashMapItem_<TKey , TItem> * ptrItem;
		intV_pl iIndex;
	}Iterator_pl;

	__plstl_MTHashMap_class(void){
		m_iItemCount = 0;
		m_iHashRange = 512;
		m_ptrMapList = NULL;
		m_bInitialize = false_pl;
	}
	~__plstl_MTHashMap_class(void){
		Release();
	}
	HPL_Result Initialize(){
		intV_pl iStructSize;
		intV_pl iCount;
		HPL_Result hResult;
		if(m_bInitialize == true_pl)
			return false_pl;
		hResult = HPLResult_Fail;
		iStructSize = sizeof(struct __plstl__MTHashMapSlot_< TKey , TItem ,TSlot>);
		m_ptrMapList = (struct __plstl__MTHashMapSlot_< TKey , TItem ,TSlot>)PLSysAPI_Mem_TLSAllocateMemoryPool(iStructSize * m_iHashRange);
		if(m_ptrMapList == NULL){
			return hResult;
		}
		PLSysAPI_MemoryClearZero((void *)m_ptrMapList,iStructSize * m_iHashRange);
		for(iCount = 0;iCount<m_iHashRange;iCount++){
			if(_disposal_func::InitializeSlotLock(m_ptrMapList[iCount].lock)<0)
				break;
		}
		if(iCount<m_iHashRange){
			while(true){
				iCount--;
				if(iCount<0)
					break;
				_disposal_func::DestorySlotLock(m_ptrMapList[iCount].lock);
			}
			PLSysAPI_Mem_TLPLreeMemoryPool(m_ptrMapList);
			m_ptrMapList = NULL_PL;
		}else{
			m_bInitialize = true_pl;
			hResult = HPLResult_OK;
		}
		return hResult;
	}
	void UnInitialize(){
		if(m_bInitialize == false_pl)
			return;
		clear();

		if(m_ptrMapList!=NULL){
			for(intV_pl iCount = 0;iCount<m_iHashRange;iCount++){
				_disposal_func::DestorySlotLock(m_ptrMapList[iCount].lock);
			}
			PLSysAPI_Mem_TLPLreeMemoryPool((void *)m_ptrMapList);
			m_ptrMapList = NULL;
		}
		m_bInitialize = false_pl;
	}
	void SetHashRange(intV_pl iHashRange){
		if(m_bInitialize == true_pl)
			return;
		m_iHashRange = iHashRange;
	}

	HPL_Result Insert(TKey key,intV_pl iSize,TItem item){
		//struct __plstl__MTHashMapSlot_< TKey , TItem ,TSlot>
		struct __plstl__HashMapItem_< TKey , TItem > * ptrLineItem;
		HPL_Result hResult;
		uintV_pl uIndex;
		intV_pl iLockState;
		hResult = HPLResult_Fail;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
		ptrLineItem = m_ptrMapList[uIndex].ptrNext;
		while(ptrLineItem!=NULL){
			if(_disposal_func::KeyEqule(ptrLineItem->tKey,ptrLineItem->iKeySize,key,iSize) == true)
				break;
			ptrLineItem = ptrLineItem->ptrNext;
		}
		if(ptrLineItem != NULL){
			_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
			return hResult;
		}
		ptrLineItem = (struct __plstl__HashMapItem_< TKey , TItem > *)PLSysAPI_Mem_TLSAllocateMemoryPool(sizeof(struct __plstl__HashMapItem_< TKey , TItem >));
		_disposal_func::InitializeHashItem(ptrLineItem);
		ptrLineItem->iKeySize = iSize;
		ptrLineItem->tKey = key;
		ptrLineItem->itemdata = item;
		ptrLineItem->ptrNext = m_ptrMapList[uIndex];
		m_ptrMapList[uIndex] = ptrLineItem;
		_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
		m_iItemCount++;
		hResult = HPLResult_OK;
		return hResult;
	}
	HPL_Result Remove(TKey key,intV_pl iSize){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrUpItem;
		struct __plstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		HPL_Result hResult;
		intV_pl iLockState;
		uintV_pl uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
		ptrFindItem = m_ptrMapList[uIndex].ptrNext;
		ptrUpItem = NULL;
		hResult = HPLResult_Fail;
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true_pl){
				if(ptrUpItem==NULL){
					m_ptrMapList[uIndex] = ptrFindItem->ptrNext;
				}else{
					ptrUpItem->ptrNext = ptrFindItem->ptrNext;
				}
				_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
				m_iItemCount--;
				_disposal_func::DestoryHashItem(ptrFindItem);
				PLSysAPI_Mem_TLPLreeMemoryPool((void *)ptrFindItem);
				hResult = HPLResult_OK;
				return hResult;
			}
			ptrUpItem = ptrFindItem;
			ptrFindItem = ptrFindItem->ptrNext;
		}
		_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
		return hResult;
	}
	void GetData(TItem * ptrItem,TKey key,intV_pl iSize){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		uintV_pl uIndex;
		intV_pl iLockState;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
		ptrFindItem = m_ptrMapList[uIndex].ptrNext;
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				*ptrItem = ptrFindItem->itemdata;
				break;
			}
			ptrFindItem = ptrFindItem->ptrNext;
		}
		_disposal_func::UnLockSlot(m_ptrMapList[uIndex].lock);
	}
	HPL_Result clear(){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrReleaseItem;
		struct __plstl__HashMapItem_< TKey , TItem > * ptrNextItem;
		intV_pl iLockState;
		HPL_Result hResult;
		if(m_bInitialize == false_pl)
			return;
		if(m_iItemCount<=0)
			return;
		hResult = HPLResult_Fail;
		for(int iLCount = 0;iLCount < m_iHashRange;iLCount++){
			iLockState = _disposal_func::LockSlot(m_ptrMapList[iLCount].lock);
			ptrReleaseItem = m_ptrMapList[iLCount].ptrNext;
			while(ptrReleaseItem != NULL){
				ptrNextItem = ptrReleaseItem->ptrNext;
				_disposal_func::DestoryHashItem(ptrReleaseItem);
				PLSysAPI_Mem_TLPLreeMemoryPool((void *)ptrReleaseItem);
				m_iItemCount--;
				if(m_iItemCount<=0)
					break;
				ptrReleaseItem = ptrNextItem;
			}
			m_ptrMapList[iLCount].ptrNext = NULL_PL;
			m_ptrMapList[iLCount].iCount = 0;
			_disposal_func::UnLockSlot(m_ptrMapList[iLCount].lock);
		}
		hResult = HPLResult_OK;
		return hResult;
	}
	bool_pl first(Iterator_pl * it){
		it->ptrItem = NULL;
		for(it->iIndex = 0;it->iIndex < m_iHashRange;it->iIndex++){
			it->ptrItem = m_ptrMapList[it->iIndex].ptrNext;
			if(it->ptrItem != NULL){
				return true_pl;
			}
		}
		it->iIndex = -1;
		return false_pl;
	}
	bool_pl GetNext(Iterator_pl * it){
		if(it->iIndex>=m_iHashRange)
			return false_pl;
		it->ptrItem = it->ptrItem->ptrNext;
		if(it->ptrItem != NULL)
			return true_pl;
		for(it->iIndex = it->iIndex + 1;it->iIndex < m_iHashRange;it->iIndex++){
			//iLockState = _disposal_func::LockSlot(m_ptrMapList[uIndex].lock);
			it->ptrItem = m_ptrMapList[it->iIndex].ptrNext;
			if(it->ptrItem!=NULL)
				return true_pl;
		}
		return false_pl;
	}
	void GetIteratorData(Iterator_pl * it,TItem * ptrOut){
		if(it->iIndex>=m_iHashRange){
			return;
		}
		if(it->ptrItem!=NULL){
			*ptrOut = it->ptrItem->itemdata;
		}
	}
	bool eraseInterator(Iterator_pl * it){
		if(it->iIndex>=m_iHashRange || it->ptrItem==NULL){
			return false_pl;
		}
		if(m_ptrMapList[it->iIndex] == it->ptrItem){
			m_ptrMapList[it->iIndex].ptrNext = it->ptrItem->ptrNext;
		}else{
			TItem * ptrUpItem;
			ptrUpItem = m_ptrMapList[it->iIndex].ptrNext;
			while(ptrUpItem!=NULL){
				if(ptrUpItem->ptrNext == it->ptrItem)
					break;
				ptrUpItem = ptrUpItem->ptrNext;
			}
			if(ptrUpItem!=NULL){
				ptrUpItem->ptrNext = it->ptrItem->ptrNext;
				return true_pl;
			}
		}
		return false_pl;
	}
	bool_pl isEnd(Iterator_pl * it){
		return (it->iIndex>=m_iHashRange) ? true_pl : false_pl;
	}
protected:
	void Release(){
		UnInitialize();
	}
protected:
	volatile intV_pl  m_iItemCount;
	volatile bool_pl  m_bInitialize;
	intV_pl           m_iHashRange;
//	struct __plstl__HashMapItem_< TKey , TItem > ** m_ptrMapList;
	struct __plstl__MTHashMapSlot_<TKey , TItem , TSlot > * m_ptrMapList;
};

#endif /* PLENGINESYSSTLMTHASHMAP_H_ */
