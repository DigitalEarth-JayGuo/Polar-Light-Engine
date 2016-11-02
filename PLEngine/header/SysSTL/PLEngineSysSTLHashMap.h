/*
 * PLEngineSysSTLHashMap.h
 *
 *  Created on: 2009-10-13
 *      Author: Administrator
 */
#include "../PLEngineH.h"
#include "../PLEngineBaseDataType.h"
#include "../PLEngineSysAPI.h"
#include "../PLEngineDefine.h"
#include "../PLEngineInface.h"
#include "../PLEngineMemoryPool.h"

#ifndef PLENGINESYSSTLHASHMAP_H_
#define PLENGINESYSSTLHASHMAP_H_

/*
#pragma pack(4)

	typedef struct _StSHashMapItem{
		_StSHashMapItem  * ptrNext;
		const_pl char_pl * ptrNameID;
		intV_pl 		   iNIDSize;
		void_pl  		 * pData;
	}SHashMapItem;
	typedef struct _StSHashMapItemRoot{
		SHashMapItem * ptrRoot;
		_Syn_RWLockRF  lock;
	}SHashMapItemRoot;
	typedef struct Aligned(8) _StSHashMap{
		intV_pl          iLength;
		intV_pl 		 iCount;
		void_pl        * ptrFuncData;
		__stl_allocatememory__PL__ 		allocatememory;
		__stl_freememory__PL__     		freememory;
		__stl_allocatenewstring__PL__ 	allstring;
		__stl_freestring__PL__          freestring;
		__stl_hashstringFunc__PL__      hsshfunc;
		SHashMapItemRoot ItemList[1];
	}__Aligned(8) SHashMap;
	typedef struct Aligned(8) _StSHashMapParamer{
		void_pl * ptrData;
		__stl_allocatememory__PL__ 		allocatememory;
		__stl_freememory__PL__     		freememory;
		__stl_allocatenewstring__PL__ 	allstring;
		__stl_freestring__PL__          freestring;
		__stl_hashstringFunc__PL__      hsshfunc;
	}SHashMapParamer;

#pragma pack()

//	typedef _CallStack_default_ void_pl * (*__stl_allocatememory__PL__)				(void_pl *,intV_pl);
//	typedef _CallStack_default_ void_pl   (*__stl_freememory__PL__)					(void_pl *,void_pl *);
//	typedef _CallStack_default_ const_pl char_pl * (*__stl_allocatenewstring__PL__) (const_pl char_pl *,intV_pl,void_pl *,__stl_allocatememory__PL__);
//	typedef _CallStack_default_ void_pl   (*__stl_freestring__PL__)					(const_pl char_pl *,intV_pl,void_pl *,__stl_freememory__PL__);
	_CallStack_default_	void_pl * __stl_native_allocatememory__				(void_pl * ptrData,intV_pl iSize);
	_CallStack_default_	void_pl	  __stl_native_freememory__					(void_pl * ptrData,void_pl * ptrFree);
	_CallStack_default_ const_pl char_pl * __stl_native_allocatenewstring__ (const_pl char_pl * ptrSrc,intV_pl iSrcSize,void_pl * ptrData,__stl_allocatememory__PL__ afunc);
	_CallStack_default_ void_pl  __stl_native_freestring__					(const_pl char_pl * ptrSrc,intV_pl iSrcSize,void_pl * ptrData,__stl_freememory__PL__ ffunc);

	_CallStack_default_ uintV_pl  __stl_native_hashstringFunc__PL__(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange);
	_PLE_lib_c _CallStack_default_ HSHashMap __PLSysAPI_STL_CreateSHashMap_(intV_pl iItemCount,SHashMapParamer & paramer);
	_PLE_lib_c _CallStack_default_ bool_pl   __PLSysAPI_STL_InsertSHashMapData_(HSHashMap hAndle,const_pl char_pl * ptrNameID,intV_pl iSize,void_pl * ptrData);
	_PLE_lib_c _CallStack_default_ void_pl * __PLSysAPI_STL_GetSHashMapData_(HSHashMap hAndle,const_pl char_pl * ptrNameID,intV_pl iSize);
	_PLE_lib_c _CallStack_default_ void_pl   __PLSysAPI_STL_DestorySHashMap_(HSHashMap hAndle);

	#define PLSysAPI_STL_CreateSHashMap 	__PLSysAPI_STL_CreateSHashMap_
	#define PLSysAPI_STL_DestorySHashMap	__PLSysAPI_STL_DestorySHashMap_
	#define PLSysAPI_STL_InsertSHashMapData __PLSysAPI_STL_InsertSHashMapData_
	#define PLSysAPI_STL_GetSHashMapData    __PLSysAPI_STL_GetSHashMapData_
*/




#pragma pack(4)

template <typename MtKey , typename MTItem>
	struct __plstl__HashMapItem_{
		struct __plstl__HashMapItem_<MtKey , MTItem>  * ptrNext;
	//	struct __plstl__HashMapItem_<typename MtKey,typename MTItem>  * ptrUp;
		MtKey						  tKey;
		int                           iKeySize;
		MTItem                        itemdata;
	};

	template<typename nkey ,typename nData ,typename nHashItem = __plstl__HashMapItem_ < nkey ,nData > >
	struct __plstl__HashMap_CmpFunc {
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
		static inline void DestoryHashItem(nHashItem * ptrHItem,void_pl * ptrSupportData){
			ReleaseItemData(&(ptrHItem->itemdata),ptrSupportData);
			PLSysAPI_MemoryClearZero((void *)ptrHItem,sizeof(nHashItem));
		}
		static inline void ReleaseItemData(nData * ptrData,void_pl * ptrSupportData){

		}
		static inline intV_pl LockTable(void_pl * lock){
			return 0;
		}
		static inline intV_pl UnLockTable(void_pl * lock){
			return 0;
		}
	};
#pragma pack()

template <typename TKey,typename TItem,typename _disposal_func = __plstl__HashMap_CmpFunc< TKey , TItem > >
class __plstl_HashMap_class{
public:
	typedef struct __Iterator{
		__plstl__HashMapItem_<TKey , TItem> * ptrItem;
		intV_pl iIndex;
	}Iterator_pl;
	__plstl_HashMap_class(void){
		m_iItemCount = 0;
		m_iHashRange = 512;
		m_ptrMapList = NULL_PL;
		m_bInitialize = false_pl;
		m_ptrSupportData = NULL_PL;
	}
	~__plstl_HashMap_class(void){
		Release();
	}
	void SetSupportData(void_pl * ptrData){
		m_ptrSupportData = NULL_PL;
	}
	bool Initialize(){
		intV_pl iStructSize;
		if(m_bInitialize == true_pl)
			return false_pl;
		iStructSize = sizeof(struct __plstl__HashMapItem_< TKey , TItem > *);
		m_ptrMapList = (struct __plstl__HashMapItem_< TKey , TItem > **)PLSysAPI_Mem_TLSAllocateMemoryPool(iStructSize * m_iHashRange);
		if(m_ptrMapList == NULL){
			return false_pl;
		}
		PLSysAPI_MemoryClearZero((void *)m_ptrMapList,iStructSize * m_iHashRange);
		m_bInitialize = true_pl;
		return true_pl;
	}
	void UnInitialize(){
		if(m_bInitialize == false_pl)
			return;
		clear();
		if(m_ptrMapList!=NULL){
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

	bool Insert(TKey key,intV_pl iSize,TItem item){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrLineItem;
		uintV_pl uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);


		ptrLineItem = m_ptrMapList[uIndex];
		while(ptrLineItem!=NULL){
			if(_disposal_func::KeyEqule(ptrLineItem->tKey,ptrLineItem->iKeySize,key,iSize) == true)
				break;
			ptrLineItem = ptrLineItem->ptrNext;
		}
		if(ptrLineItem != NULL){
			return false_pl;
		}
		ptrLineItem = (struct __plstl__HashMapItem_< TKey , TItem > *)PLSysAPI_Mem_TLSAllocateMemoryPool(sizeof(struct __plstl__HashMapItem_< TKey , TItem >));
		_disposal_func::InitializeHashItem(ptrLineItem);
		ptrLineItem->iKeySize = iSize;
		ptrLineItem->tKey = key;
		ptrLineItem->itemdata = item;
		ptrLineItem->ptrNext = m_ptrMapList[uIndex];
		m_ptrMapList[uIndex] = ptrLineItem;
		m_iItemCount++;
		return true_pl;
	}
	void Remove(TKey key,intV_pl iSize){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrUpItem;
		struct __plstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		uintV_pl uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		ptrFindItem = m_ptrMapList[uIndex];
		ptrUpItem = NULL;
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				if(ptrUpItem==NULL){
					m_ptrMapList[uIndex] = ptrFindItem->ptrNext;
				}else{
					ptrUpItem->ptrNext = ptrFindItem->ptrNext;
				}
				_disposal_func::DestoryHashItem(ptrFindItem,m_ptrSupportData);
				PLSysAPI_Mem_TLPLreeMemoryPool((void *)ptrFindItem);
				m_iItemCount--;
				break;
			}
			ptrUpItem = ptrFindItem;
			ptrFindItem = ptrFindItem->ptrNext;
		}
	}
	void GetData(TItem * ptrItem,TKey key,intV_pl iSize){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		uintV_pl uIndex;
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		ptrFindItem = m_ptrMapList[uIndex];
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				*ptrItem = ptrFindItem->itemdata;
				break;
			}
			ptrFindItem = ptrFindItem->ptrNext;
		}
	}
	TItem GetData(TKey key,intV_pl iSize){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrFindItem;
		TItem TUserData;
		uintV_pl uIndex;
		PLSysAPI_MemoryClearZero(&TUserData,PL_Sizeof(TItem));
		uIndex = _disposal_func::Calculate_hash(key,iSize,m_iHashRange);
		ptrFindItem = m_ptrMapList[uIndex];
		while(ptrFindItem != NULL){
			if(_disposal_func::KeyEqule(ptrFindItem->tKey,ptrFindItem->iKeySize,key,iSize) == true){
				TUserData = ptrFindItem->itemdata;
				break;
			}
			ptrFindItem = ptrFindItem->ptrNext;
		}
		return TUserData;
	}
	void clear(){
		struct __plstl__HashMapItem_< TKey , TItem > * ptrReleaseItem;
		struct __plstl__HashMapItem_< TKey , TItem > * ptrNextItem;
		if(m_bInitialize == false_pl)
			return;
		if(m_iItemCount<=0)
			return;
		for(int iLCount = 0;iLCount < m_iHashRange;iLCount++){
			ptrReleaseItem = m_ptrMapList[iLCount];
			while(ptrReleaseItem != NULL){
				ptrNextItem = ptrReleaseItem->ptrNext;
				_disposal_func::DestoryHashItem(ptrReleaseItem,m_ptrSupportData);
				PLSysAPI_Mem_TLPLreeMemoryPool((void *)ptrReleaseItem);
				m_iItemCount--;
				if(m_iItemCount<=0)
					break;
				ptrReleaseItem = ptrNextItem;

			}
		}
		PLSysAPI_MemoryClearZero(m_ptrMapList,sizeof(sizeof(struct __plstl__HashMapItem_< TKey , TItem > *)) * m_iHashRange);
	}
	bool first(Iterator_pl * it){
		it->ptrItem = NULL;
		for(it->iIndex = 0;it->iIndex < m_iHashRange;it->iIndex++){
			it->ptrItem = m_ptrMapList[it->iIndex];
			if(it->ptrItem != NULL){
				return true_pl;
			}
		}
		return false_pl;
	}
	bool GetNext(Iterator_pl * it){
		if(it->iIndex>=m_iHashRange)
			return false_pl;
		it->ptrItem = it->ptrItem->ptrNext;
		if(it->ptrItem != NULL)
			return true_pl;
		for(it->iIndex = it->iIndex + 1;it->iIndex < m_iHashRange;it->iIndex++){
			it->ptrItem = m_ptrMapList[it->iIndex];
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
			m_ptrMapList[it->iIndex] = it->ptrItem->ptrNext;
		}else{
			TItem * ptrUpItem;
			ptrUpItem = m_ptrMapList[it->iIndex];
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
	void_pl         * m_ptrSupportData;
	struct __plstl__HashMapItem_< TKey , TItem > ** m_ptrMapList;
};
#endif /* PLENGINESYSSTLHASHMAP_H_ */
