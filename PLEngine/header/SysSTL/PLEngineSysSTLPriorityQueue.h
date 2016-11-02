/*
 * PLEngineSysSTLPriorityQueue.h
 *
 *  Created on: 2009-11-5
 *      Author: Administrator
 */
#include "../PLEngineH.h"
#include "../PLEngineBaseDataType.h"
#include "../PLEngineSysAPI.h"
#include "../PLEngineDefine.h"
#include "../PLEngineInface.h"
#include "../PLEngineMemoryPool.h"
#ifndef PLENGINESYSSTLPRIORITYQUEUE_H_
#define PLENGINESYSSTLPRIORITYQUEUE_H_

	template<typename _plstl_Node__ >
	struct Aligned(8) __stl_PriorityQueue_CmpFunc {
		inline bool_pl MovUp(_plstl_Node__ * & key1,_plstl_Node__ * & key2){
			return false_pl;
		}
	}__Aligned(8);

	template<typename _plstl_Node__ , typename _plstl_CmpFunc__ = __stl_PriorityQueue_CmpFunc < _plstl_Node__ > >
	class __plstl_PriorityQueue_class{
		public:
			static __plstl_PriorityQueue_class * CreatePriorityQueue(intV_pl iTaskMaxCount){
				__plstl_PriorityQueue_class * prrPQObject;
				void_pl * prrObject;
				prrObject = NULL_PL;
				prrPQObject = NULL_PL;
				prrObject = (__plstl_PriorityQueue_class *)PLSysAPI_Mem_TLSAllocateMemoryPool(PL_CompilerAllocSize(__plstl_PriorityQueue_class));
				if(prrObject != NULL_PL){
					prrPQObject = new(prrObject) __plstl_PriorityQueue_class();
					if(HResulPL_FAILED(prrPQObject->InitializeClass(iTaskMaxCount))==true_pl){
						PLSysAPI_Mem_TLPLreeMemoryPool((void_pl *)prrPQObject);
						prrPQObject = NULL_PL;
					}
				}
				return prrPQObject;
			}
			virtual ~__plstl_PriorityQueue_class(){
				if(m_ppList != NULL_PL){
					PLSysAPI_Mem_FreeMemoryPool((void_pl *)m_ppList);
					m_ppList = NULL_PL;
				}
				m_iCurrentCount = 0;
				m_lock = PLSyn_Const_SynSpinLockPass;
				PLSysAPI_Mem_FreeMemoryPool((void_pl *)this);
			}
			void_pl DestoryClass(){
				this->~__plstl_PriorityQueue_class();
			}
			HPL_Result Push(_plstl_Node__ * ptrNode){
				_plstl_Node__ * ptrSwap;
				intV_pl iTarget;
				intV_pl iRTarget;
				intV_pl iUp;
				intV_pl iRUp;
				if(ptrNode == NULL_PL)
					return HPLResult_Fail;
				PLSysAPI_Syn_EnterSpinLock(&m_lock);
				if((m_iCurrentCount+1)>m_iTaskMaxCount){
					PLSysAPI_Syn_LeaveSpinLock(&m_lock);
					return HPLResult_Fail;
				}
				m_ppList[m_iCurrentCount] = ptrNode;
				m_iCurrentCount+=1;
				iUp 	 = m_iCurrentCount;
				iTarget  = m_iCurrentCount;
				iUp = iTarget >> 1;
				while(iUp!=0){
					iRTarget = iTarget - 1;
					iRUp	 = iUp - 1;
					if(m_cmpfunc.MovUp(m_ppList[iRUp],m_ppList[iRTarget])==false_pl)
						break;
					ptrSwap = m_ppList[iRUp];
					m_ppList[iRUp] = m_ppList[iRTarget];
					m_ppList[iRTarget] = ptrSwap;
					iTarget = iUp;
					iUp = iUp >> 1;
				}
				PLSysAPI_Syn_LeaveSpinLock(&m_lock);
				return HPLResult_OK;
			}
			_plstl_Node__ * Pop(){
				_plstl_Node__ * ptrSwap;
				_plstl_Node__ * ptrNode;
				intV_pl iIndex;
				intV_pl iMIndex;
				intV_pl iLIndex;
				intV_pl iMLIndex;
				intV_pl iRIndex;
				intV_pl iMRIndex;
				PLSysAPI_Syn_EnterSpinLock(&m_lock);
				if(m_iCurrentCount<=0){
					PLSysAPI_Syn_LeaveSpinLock(&m_lock);
					return NULL_PL;
				}
				ptrNode = m_ppList[0];
				m_iCurrentCount -= 1;
				m_ppList[0] = m_ppList[m_iCurrentCount];
				iIndex  = 1;
				iMIndex = 0;
				while((iLIndex = (iIndex << 1)) <= m_iCurrentCount){
					iRIndex = (iIndex << 1) + 1;
					iMLIndex= (iIndex << 1) - 1;
					iMRIndex= iIndex << 1;
					if(iRIndex <= m_iCurrentCount){
						if(m_cmpfunc.MovUp(m_ppList[iMLIndex],m_ppList[iMRIndex])==true_pl){
							iLIndex = iRIndex;
							iMLIndex= iMRIndex;
						}
					}
					if(m_cmpfunc.MovUp(m_ppList[iMIndex],m_ppList[iMLIndex]) == false_pl)
						break;
					ptrSwap = m_ppList[iMIndex];
					m_ppList[iMIndex] = m_ppList[iMLIndex];
					m_ppList[iMLIndex] = ptrSwap;
					iIndex = iLIndex;
					iMIndex= iMLIndex;
				}
				PLSysAPI_Syn_LeaveSpinLock(&m_lock);
				return ptrNode;
			}
			intV_pl GetCurrentItemCount(){
				return m_iCurrentCount;
			}
		protected:
			__plstl_PriorityQueue_class(){
				m_lock = PLSyn_Const_SynSpinLockPass;
			}
			HPL_Result InitializeClass(intV_pl iTaskMaxCount){
				intV_pl iAllocSize;
				if(iTaskMaxCount<=0)
					return HPLResult_Fail;
				iAllocSize = iTaskMaxCount * PL_CompilerAllocSize(_plstl_Node__ *);
				m_ppList = (_plstl_Node__ **)PLSysAPI_Mem_TLSAllocateMemoryPool(iAllocSize);
				if(m_ppList == NULL_PL)
					return HPLResult_Fail;
				PLSysAPI_MemoryClearZero(m_ppList,iAllocSize);
				m_iTaskMaxCount = iTaskMaxCount;
				m_lock = PLSyn_Const_SynSpinLockPass;
				return HPLResult_OK;
			}
		protected:
		_plstl_Node__ ** m_ppList;
		_Syn_SpinLock    m_lock;
		intV_pl          m_iTaskMaxCount;
		intV_pl          m_iCurrentCount;
		_plstl_CmpFunc__ m_cmpfunc;
	};

#endif /* PLENGINESYSSTLPRIORITYQUEUE_H_ */
