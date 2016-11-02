/*
 * EngineResourceManagerAPI.h
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "PLEngineResourceManagerPKH.h"
#include "EngineResourceManagerInface.h"
#ifndef ENGINERESOURCEMANAGERAPI_H_
#define ENGINERESOURCEMANAGERAPI_H_
	extern PLLibraryHandle g_hLibraryHandle_Resource;
	_CallStack_default_ uintV_pl __native_hash(const_pl char_pl * ptrKey,intV_pl iSize,intV_pl iRange);

	_CallStack_default_ HPolygonMgrAndle 		Eg_CreatePolygonManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_pl 		 		Eg_DestoryPolygonManager(HPolygonMgrAndle hAndle);
	_CallStack_default_ PL_ResourcePolygon *    Eg_CreatePolygonMgrObject(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_ResourcePolygon *    Eg_OpenPolygonMgrObject(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result			    Eg_ReleasePolygonMgrObject(PL_ResourcePolygon * ptrItem);
	_CallStack_default_ HPL_Result			    Eg_DestoryPolygonMgrObject(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_	HPL_Result              Eg_PushPolygonRTaskerQueue(PL_ResourcePolygon * ptrItem);
	_CallStack_default_ HPL_Result              Eg_PushPolygonRTaskerQueueFill(PL_ResourcePolygon * ptrItem,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_	HPL_Result              Eg_PushPolygonRTaskerQueueN(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result 				Eg_PushPolygonRTaskerQueueNFill(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_ HPL_Result              Eg_RefurbishPolygonRBackgroundDispose(HPolygonMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HTextureMgrAndle 		Eg_CreateTextureManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_pl 		 		Eg_DestoryTextureManager(HTextureMgrAndle hAndle);
	_CallStack_default_ PL_ResourceTexture *    Eg_CreateTextureMgrObject(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_ResourceTexture *    Eg_OpenTextureMgrObject(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result			    Eg_ReleaseTextureMgrObject(PL_ResourceTexture * ptrItem);
	_CallStack_default_ HPL_Result			    Eg_DestoryTextureMgrObject(HTextureMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_	HPL_Result              Eg_PushTextureRTaskerQueue(PL_ResourceTexture * ptrItem);
	_CallStack_default_ HPL_Result              Eg_PushTextureRTaskerQueueFill(PL_ResourcePolygon * ptrItem,lint_pl lMov,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_	HPL_Result              Eg_PushTextureRTaskerQueueN(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result 				Eg_PushTextureRTaskerQueueNFill(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_ HPL_Result              Eg_RefurbishTextureRBackgroundDispose(HTextureMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HScriptMgrAndle			Eg_CreateScriptManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_pl					Eg_DestoryScriptManager(HScriptMgrAndle hAndle);
	_CallStack_default_ PL_ResourceScript  *    Eg_CreateScriptMgrObject(HScriptMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_ResourceScript  *    Eg_OpenScriptMgrObject(HScriptMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result			    Eg_ReleaseScriptMgrObject(PL_ResourceScript * ptrItem);
	_CallStack_default_ HPL_Result			    Eg_DestoryScriptMgrObject(HScriptMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_	HPL_Result              Eg_PushScriptRTaskerQueue(PL_ResourceScript * ptrItem);
	_CallStack_default_ HPL_Result              Eg_PushScriptRTaskerQueueFill(PL_ResourcePolygon * ptrItem,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_	HPL_Result              Eg_PushScriptRTaskerQueueN(HScriptMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result 				Eg_PushScriptRTaskerQueueNFill(HPolygonMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_ HPL_Result              Eg_RefurbishScriptRBackgroundDispose(HScriptMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HMaterialMgrAndle 		Eg_CreateMaterialManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_pl 		 		Eg_DestoryMaterialManager(HMaterialMgrAndle hAndle);
	_CallStack_default_ PL_ResourceMaterial *   Eg_CreateMaterialMgrObject(HMaterialMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_ResourceMaterial *   Eg_OpenMaterialMgrObject(HMaterialMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result			    Eg_ReleaseMaterialMgrObject(PL_ResourceMaterial * ptrItem);
	_CallStack_default_ HPL_Result			    Eg_DestoryMaterialMgrObject(HMaterialMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_	HPL_Result              Eg_PushMaterialRTaskerQueue(PL_ResourceMaterial * ptrItem);
	_CallStack_default_ HPL_Result              Eg_PushMaterialRTaskerQueueFill(PL_ResourceMaterial * ptrItem,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_	HPL_Result              Eg_PushMaterialRTaskerQueueN(HMaterialMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result 				Eg_PushMaterialRTaskerQueueNFill(HMaterialMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_ HPL_Result              Eg_RefurbishMaterialRBackgroundDispose(HMaterialMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HVideoMgrAndle	 		Eg_CreateVideoManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_pl 		 		Eg_DestoryVideoManager(HVideoMgrAndle hAndle);
	_CallStack_default_ PL_ResourceVideo *   	Eg_CreateVideoMgrObject(HVideoMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_ResourceVideo *    	Eg_OpenVideoMgrObject(HVideoMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result			    Eg_ReleaseVideoMgrObject(PL_ResourceVideo * ptrItem);
	_CallStack_default_ HPL_Result			    Eg_DestoryVideoMgrObject(HVideoMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_	HPL_Result              Eg_PushVideoRTaskerQueue(PL_ResourceVideo * ptrItem);
	_CallStack_default_ HPL_Result              Eg_PushVideoRTaskerQueueFill(PL_ResourceVideo * ptrItem,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_	HPL_Result              Eg_PushVideoRTaskerQueueN(HVideoMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result 				Eg_PushVideoRTaskerQueueNFill(HVideoMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_ HPL_Result              Eg_RefurbishVideoRBackgroundDispose(HVideoMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HWaveMgrAndle	 		Eg_CreateWaveManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_pl 		 		Eg_DestoryWaveManager(HWaveMgrAndle hAndle);
	_CallStack_default_ PL_ResourceWave *   	Eg_CreateWaveMgrObject(HWaveMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_ResourceWave *    	Eg_OpenWaveMgrObject(HWaveMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result			    Eg_ReleaseWaveMgrObject(PL_ResourceWave * ptrItem);
	_CallStack_default_ HPL_Result			    Eg_DestoryWaveMgrObject(HWaveMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_	HPL_Result              Eg_PushWaveRTaskerQueue(PL_ResourceWave * ptrItem);
	_CallStack_default_ HPL_Result              Eg_PushWaveRTaskerQueueFill(PL_ResourceWave * ptrItem,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_	HPL_Result              Eg_PushWaveRTaskerQueueN(HWaveMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result 				Eg_PushWaveRTaskerQueueNFill(HWaveMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_ HPL_Result              Eg_RefurbishWaveRBackgroundDispose(HWaveMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HSoundMgrAndle	 		Eg_CreateSoundManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_pl 		 		Eg_DestorySoundManager(HSoundMgrAndle hAndle);
	_CallStack_default_ PL_ResourceSound *   	Eg_CreateSoundMgrObject(HSoundMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ PL_ResourceSound *    	Eg_OpenSoundMgrObject(HSoundMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result			    Eg_ReleaseSoundMgrObject(PL_ResourceSound * ptrItem);
	_CallStack_default_ HPL_Result			    Eg_DestorySoundMgrObject(HSoundMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_	HPL_Result              Eg_PushSoundRTaskerQueue(PL_ResourceSound * ptrItem);
	_CallStack_default_ HPL_Result              Eg_PushSoundRTaskerQueueFill(PL_ResourceSound * ptrItem,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_	HPL_Result              Eg_PushSoundRTaskerQueueN(HSoundMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize);
	_CallStack_default_ HPL_Result 				Eg_PushSoundRTaskerQueueNFill(HSoundMgrAndle hAndle,const_pl char_pl * ptrKey,intV_pl iKeySize,PL_CommResourceBlock * ptrBlock);
	_CallStack_default_ HPL_Result              Eg_RefurbishSoundRBackgroundDispose(HSoundMgrAndle hAndle,PL_ResourceBgDisposeParamer * ptrParamer);


					template<typename Mgr,typename Node>
						bool_pl __native_Eg_PushPriorityStackSortList(Mgr * ptrMgr,Node * ptrItem,intV_pl iMaxCount){
							intV_pl iSerial;
							intV_pl iPSerial;
							Node * ptrSWAP;
							if(ptrMgr->iTkCount>=iMaxCount){
								return false_pl;
							}
							ptrMgr->TaskList[ptrMgr->iTkCount] = ptrItem;
							PLSysAPI_Syn_AtomInterAdd(&(ptrMgr->iTkCount),1);
							//ptrMgr->iTkCount++;
							iSerial = ptrMgr->iTkCount;
							while(true_pl){
								iPSerial = iSerial>>1;
								if((iSerial>>1)<=0)
									break;
								ptrSWAP = ptrMgr->TaskList[iPSerial - 1];
								if(ptrMgr->TaskList[iPSerial - 1]->iPRI>=ptrMgr->TaskList[iSerial - 1]->iPRI)
									break;
								ptrMgr->TaskList[iPSerial - 1] = ptrMgr->TaskList[iSerial - 1];
								ptrMgr->TaskList[iSerial - 1]  = ptrSWAP;
							}
							return true_pl;
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_PopMaxPriorityStackSort(Mgr * ptrMgr){
							Node * ptrRNode;
							Node * ptrSwap;
							intV_pl iSerial;
							intV_pl iChildLSerial;
							intV_pl iChildRSerial;
							intV_pl iChildLIndex;
							intV_pl iChildRIndex;
							intV_pl iIndex;
							if(ptrMgr->iTkCount<=0)
								return NULL_PL;
							ptrRNode = ptrMgr->TaskList[0];
							PLSysAPI_Syn_AtomInterAdd(&(ptrMgr->iTkCount),-1);
							ptrMgr->TaskList[0] = ptrMgr->TaskList[ptrMgr->iTkCount];
							iSerial = 1;
							iIndex  = 0;
							while((iChildLSerial = (iSerial<<1)) <= ptrMgr->iTkCount){
								iChildRSerial =  (iSerial<<1) + 1;
								iChildLIndex  =  iChildLSerial - 1;
								iChildRIndex  =  iChildRSerial - 1;
								if((iChildRSerial <= ptrMgr->iTkCount) && (ptrMgr->TaskList[iChildRIndex]->iPRI > ptrMgr->TaskList[iChildLIndex]->iPRI)){
									iChildLSerial= iChildRSerial;
									iChildLIndex = iChildRIndex;
								}
								if(ptrMgr->TaskList[iIndex]->iPRI >= ptrMgr->TaskList[iChildLIndex]->iPRI)
									break;
								ptrSwap = ptrMgr->TaskList[iChildLIndex];
								ptrMgr->TaskList[iChildLIndex] = ptrMgr->TaskList[iIndex];
								ptrMgr->TaskList[iIndex] = ptrSwap;
								iSerial = iChildLSerial;
								iIndex  = iChildLIndex;
							}
							return ptrRNode;
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_RemoveMapItem(Mgr * ptrMgr,uintV_pl uIndex,Node * ptrItem){
							Node * ptrPUpItem;
							Node * ptrPNItem;
							ptrPNItem = ptrMgr->List[uIndex].ptrRoot;
							ptrPUpItem= ptrMgr->List[uIndex].ptrRoot;
							while(ptrPNItem != NULL_PL){
								if(ptrPNItem == ptrItem){
									if(ptrPNItem == ptrPUpItem){
										ptrMgr->List[uIndex].ptrRoot = ptrPNItem->ptrMNext;
									}else{
										ptrPUpItem->ptrMNext = ptrPNItem->ptrMNext;
									}
									PLSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),-1);
									//ptrPNItem->eDynamicState = PLSys_Const_RODynamic_eReclaim;
									return ptrPNItem;
								}
								ptrPNItem = ptrPNItem->ptrMNext;
								ptrPUpItem= ptrPNItem;
							}
							return NULL_PL;
						}
					//must remove
					template<typename Mgr,typename Node>
						Node * __native_Eg_RemoveMapItem(Mgr * ptrMgr,uintV_pl uIndex,const_pl char_pl * ptrKey,intV_pl iKeySize){
							Node * ptrPUpItem;
							Node * ptrPNItem;
							ptrPNItem = ptrMgr->List[uIndex].ptrRoot;
							ptrPUpItem= ptrMgr->List[uIndex].ptrRoot;
							while(ptrPNItem != NULL_PL){
								if((iKeySize == ptrPNItem->iNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrPNItem->ptrName,iKeySize) == 0)){
									if(ptrPNItem == ptrPUpItem){
										ptrMgr->List[uIndex].ptrRoot = ptrPNItem->ptrMNext;
									}else{
										ptrPUpItem->ptrMNext = ptrPNItem->ptrMNext;
									}
									PLSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),-1);
									ptrPNItem->eDynamicState = PLSys_Const_RODynamic_eReclaim;
									return ptrPNItem;
								}
								ptrPNItem = ptrPNItem->ptrMNext;
								ptrPUpItem= ptrPNItem;
							}
							return NULL_PL;
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_UnRefMapItem(Mgr * ptrMgr,uintV_pl uIndex,const_pl char_pl * ptrKey,intV_pl iKeySize){
							Node * ptrPUpItem;
							Node * ptrPNItem;
							PL_ResourceObjectDynamicState eDynamicState;
							intV_pl iRefCount;
							ptrPNItem = ptrMgr->List[uIndex].ptrRoot;
							ptrPUpItem= ptrMgr->List[uIndex].ptrRoot;
							while(ptrPNItem != NULL_PL){
								if((iKeySize == ptrPNItem->iNSize) && (PLSysAPI_MemoryCmp(ptrKey,ptrPNItem->ptrName,iKeySize) == 0)){
									iRefCount = PLSysAPI_Syn_AtomInterAdd(&(ptrPNItem->iRefCount),-1);
									if(iRefCount<=0){
										eDynamicState = ptrPNItem->eDynamicState;
										if((ptrPNItem != NULL_PL) && (eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrPNItem->eDynamicState)),
												(intV_pl)PLSys_Const_RODynamic_eReclaim,
												(intV_pl)eDynamicState)==true_pl)){
											if(ptrPNItem == ptrPUpItem){
												ptrMgr->List[uIndex].ptrRoot = ptrPNItem->ptrMNext;
											}else{
												ptrPUpItem->ptrMNext = ptrPNItem->ptrMNext;
											}
											PLSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),-1);
											return ptrPNItem;
										}
										break;
									}
								}
								ptrPNItem = ptrPNItem->ptrMNext;
								ptrPUpItem= ptrPNItem;
							}
							return NULL_PL;
						}
					template<typename Mgr,typename Node>
						void_pl __native_Eg_PushReclaimQueue(Mgr * ptrMgr,Node * ptrItem){
							PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->ReclaimLock));
							ptrItem->ptrMNext = (Node *)(ptrMgr->ptrReclaimQueueRoot);
							ptrMgr->ptrReclaimQueueRoot = ptrItem;
							PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->ReclaimLock));
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_PopReclaimQueue(Mgr * ptrMgr){
							Node * ptrItem;
							PLSysAPI_Syn_EnterSpinLock(&(ptrMgr->ReclaimLock));
							ptrItem = (Node *)(ptrMgr->ptrReclaimQueueRoot);
							if(ptrItem!=NULL_PL){
								ptrMgr->ptrReclaimQueueRoot = ptrItem->ptrMNext;
							}
							PLSysAPI_Syn_LeaveSpinLock(&(ptrMgr->ReclaimLock));
							return ptrItem;
						}


					template<typename Mgr,typename Node>
						void_pl __native_Eg_TestReclaim(Mgr * ptrMgr,Node * ptrItem,uintV_pl uHash){
							Node * ptrRelaseItem;
							PL_ResourceObjectDynamicState eDynamicState;
							ptrRelaseItem = NULL_PL;
							eDynamicState = ptrItem->eDynamicState;
							if((eDynamicState != PLSys_Const_RODynamic_eReclaim) && (PLSysAPI_JudgeSetValueInt((volatile_pl intV_pl *)(&(ptrItem->eDynamicState)),
									(intV_pl)PLSys_Const_RODynamic_eReclaim,
									(intV_pl)eDynamicState)==true_pl)){
								__native_Eg_RemoveMapItem<PL_ResourcePolygonManager,PL_ResourcePolygonItem>(ptrMgr,uHash,ptrItem);
								ptrRelaseItem = ptrItem;
							}
							if(ptrRelaseItem != NULL_PL){
								__native_Eg_PushReclaimQueue<PL_ResourcePolygonManager,PL_ResourcePolygonItem>(ptrMgr,ptrRelaseItem);
							}
						}


/*
					uHash = ptrMgr->hashfunc(ptrItem->ptrName,ptrItem->iNSize,PLRMgr_ConstID_RPolygonMgrMapSlotMaxSize);

 */

/*
				void_pl 				 __native_Eg_PushReclaimQueue(PL_ResourcePolygonManager * ptrMgr,PL_ResourcePolygonItem * ptrItem);
				PL_ResourcePolygonItem * __native_Eg_PopReclaimQueue(PL_ResourcePolygonManager * ptrMgr);
 * */

#endif /* ENGINERESOURCEMANAGERAPI_H_ */
