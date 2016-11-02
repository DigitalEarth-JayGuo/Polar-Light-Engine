/*
 * PLEngineSysAPI.cpp
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "header/PLEngineSysAPI.h"
	PL_SystemTimer * _MaxSystemTimer_(PL_SystemTimer * ptr1,PL_SystemTimer * ptr2){
		if(ptr1->iday!=ptr2->iday)
			return ptr1->iday<ptr2->iday       ? ptr2 : ptr1;
		if(ptr1->isecond!=ptr2->isecond)
			return ptr1->isecond<ptr2->isecond ? ptr2 : ptr1;
		if(ptr1->ins!=ptr2->ins)
			return ptr1->ins<ptr2->ins         ? ptr2 : ptr1;
		return ptr1;
	}
	void _CalculSysTimerInterval_(PL_SystemTimer * ptrH,PL_SystemTimer * ptrL,PL_SystemTimer * ptrInterval){
		PL_SystemTimer * ptrHI;
		PL_SystemTimer * ptrLI;
		ptrHI = ptrH;
		ptrLI = ptrL;
		if(ptrL->iCalculSymbol != ptrH->iCalculSymbol){
			ptrInterval->ins     = ptrHI->ins     + ptrLI->ins;

			ptrInterval->isecond = ptrHI->isecond + ptrLI->isecond;
			ptrInterval->iday    = ptrHI->iday    + ptrLI->iday;
			if(ptrInterval->ins >= 1000000000){
				ptrInterval->ins -= 1000000000;
				++(ptrInterval->isecond);
			}
			if(ptrInterval->isecond >= 86400 ){
				ptrInterval->isecond -= 86400;
				++(ptrInterval->iday);
			}
//			printf("ptrL->iCalculSymbol != ptrH->iCalculSymbol");
		}else{
			ptrHI  = _MaxSystemTimer_(ptrL,ptrH);
			ptrLI = (ptrL == ptrHI) ? ptrH : ptrL;
			if(ptrHI->ins >= ptrLI->ins){
				ptrInterval->ins = ptrHI->ins - ptrLI->ins;
			}else{
				ptrInterval->ins = 1000000000 - (ptrLI->ins - ptrHI->ins);
				if(ptrHI->isecond==0){
					ptrHI->isecond = 86400-1;
					--(ptrHI->iday);
				}else{
					--(ptrHI->isecond);
				}
			}
			if(ptrHI->isecond >= ptrLI->isecond){
				ptrInterval->isecond = ptrHI->isecond - ptrLI->isecond;
			}else{
				ptrInterval->isecond = 86400 - (ptrLI->isecond - ptrHI->isecond);
				--(ptrHI->iday);
			}
			ptrInterval->iday = ptrHI->iday - ptrLI->iday;
			ptrInterval->iyear = 0;

		}
	}
	void _CalculSysTimerIntervalMaxSubMin_(PL_SystemTimer * ptrH,PL_SystemTimer * ptrL,PL_SystemTimer * ptrInterval){
		PL_SystemTimer * ptrHI;
		PL_SystemTimer * ptrLI;
		ptrHI = ptrH;
		ptrLI = ptrL;
		if(ptrL->iCalculSymbol != ptrH->iCalculSymbol){
			ptrInterval->ins     = ptrHI->ins     + ptrLI->ins;
			ptrInterval->isecond = ptrHI->isecond + ptrLI->isecond;
			ptrInterval->iday    = ptrHI->iday    + ptrLI->iday;
			if(ptrInterval->ins >= 1000000000){
				ptrInterval->ins -= 1000000000;
				++(ptrInterval->isecond);
			}
			if(ptrInterval->isecond >= 86400 ){
				ptrInterval->isecond -= 86400;
				++(ptrInterval->iday);
			}
			printf("ptrL->iCalculSymbol != ptrH->iCalculSymbol");
		}else{
			if(ptrHI->ins >= ptrLI->ins){
				ptrInterval->ins = ptrHI->ins - ptrLI->ins;
			}else{
				ptrInterval->ins = 1000000000 - (ptrLI->ins - ptrHI->ins);
				if(ptrHI->isecond==0){
					ptrHI->isecond = 86400-1;
					--(ptrHI->iday);
				}else{
					--(ptrHI->isecond);
				}
			}
			if(ptrHI->isecond >= ptrLI->isecond){
				ptrInterval->isecond = ptrHI->isecond - ptrLI->isecond;
			}else{
				ptrInterval->isecond = 86400 - (ptrLI->isecond - ptrHI->isecond);
				--(ptrHI->iday);
			}
			ptrInterval->iday = ptrHI->iday - ptrLI->iday;
			ptrInterval->iyear = 0;

		}
	}
	void _CalculSysTimerAdd_(PL_SystemTimer * ptrBase,PL_SystemTimer * ptrAdd){
		ptrBase->ins += ptrAdd->ins;
		if(ptrBase->ins >= 1000000000){
			ptrBase->ins -= 1000000000;
			++(ptrBase->isecond);
		}
		ptrBase->isecond += ptrAdd->isecond;
		if(ptrBase->isecond>=86400){
			ptrBase->isecond -= 86400;
			++(ptrBase->iday);
		}
		ptrBase->iday    += ptrAdd->iday;
		ptrBase->iyear = 0;
	}
	HPL_Result PLSysAPI_Calcul_SysTimerInterval(PL_SystemTimer * ptrLast,PL_SystemTimer * ptrAfter,PL_SystemTimer * ptrInterval){
		if(ptrLast==NULL_PL || ptrAfter==NULL_PL || ptrInterval==NULL_PL)
			return HPLResultF_Paramer_NULL;
		_CalculSysTimerInterval_(ptrLast,ptrAfter,ptrInterval);
		if(ptrLast->iCalculSymbol==ptrAfter->iCalculSymbol){
			ptrInterval->iCalculSymbol = ptrLast->iCalculSymbol;
		}else{
			ptrInterval->iCalculSymbol = _MaxSystemTimer_(ptrLast,ptrAfter)->iCalculSymbol;
		}
		return HPLResult_OK;
	}
	HPL_Result PLSysAPI_Calcul_SysTimerAdd(PL_SystemTimer * ptrBase,PL_SystemTimer * ptrAdd){
		if(ptrBase==NULL_PL || ptrAdd==NULL_PL)
			return HPLResultF_Paramer_NULL;
		if(ptrBase->iCalculSymbol==ptrAdd->iCalculSymbol){
			_CalculSysTimerAdd_(ptrBase,ptrAdd);
		}else{
			PL_SystemTimer Interval;
			Interval.iCalculSymbol=_MaxSystemTimer_(ptrBase,ptrAdd)->iCalculSymbol;
			ptrAdd->iCalculSymbol = ptrBase->iCalculSymbol;
			_CalculSysTimerInterval_(ptrBase,ptrAdd,&Interval);
			ptrBase->iday    = Interval.iday;
			ptrBase->isecond = Interval.isecond;
			ptrBase->ins     = Interval.ins;
		}
		return HPLResult_OK;
	}
	void_pl * PLSysAPI_Lib_SearchLibraryObjectIndex(PLLibModuleHandle hAndle,int_pl iIndex){
		void_pl * addres;
		PL_EngineLibraryHeavyInface * ptrInface;
		PL_EngineLibraryFunTable 	* ptrFunTable;
		addres = NULL_PL;
		ptrInface = (PL_EngineLibraryHeavyInface *)hAndle;
		do{
			ptrFunTable = ptrInface->ptrFunTable;
			if((ptrInface==NULL_PL) || (ptrFunTable==NULL_PL))
				break;
			if((iIndex<0) || (iIndex>=ptrFunTable->iFunCount))
				break;
			addres = ptrFunTable->functionlist[iIndex];
		}while(0);
		return addres;
	}


#if PLCompiler_Tool == PLCompiler_MSVC


	#if PLCPU_IAXX == PLCPU_IA32
		int64_pl __PLSysAPI_GetHotBitPos64_H2LSearch(uint64_pl iValue){
			int64_pl iPos;
			int32_pl bAllZero;
			uint32_pl iH32Value;
			uint32_pl iL32Value;
			iL32Value = *((uint32_pl *)(&iValue));
			iH32Value = *((uint32_pl *)(&iValue)+1);
			iPos = 0;
			__asm{
				mov ebx,iH32Value
				bsr eax,ebx
				sete dl
				add eax,20h
				cmp dl,1
				jnz __end_bsr
				mov ebx,iL32Value
				bsr eax,ebx
				sete dl
				__end_bsr:	movzx edx,dl
				mov iPos,eax
				mov bAllZero,edx
			}
			return bAllZero == 1 ? -1 : iPos;
		}
		int64_pl __PLSysAPI_GetHotBitPos64_L2HSearch(uint64_pl iValue){
			int64_pl iPos;
			int32_pl bAllZero;
			uint32_pl iH32Value;
			uint32_pl iL32Value;
			iL32Value = *((uint32_pl *)(&iValue));
			iH32Value = *((uint32_pl *)(&iValue)+1);
			iPos = 0;
			__asm{
				mov ebx,iL32Value
				bsr eax,ebx
				sete dl
				cmp dl,1
				jnz __end_bsr
				mov ebx,iH32Value
				bsr eax,ebx
				sete dl
				add eax,20h
				__end_bsr:	movzx edx,dl
				mov iPos,eax
				mov bAllZero,edx
			}
			return bAllZero == 1 ? -1 : iPos;
		}
	#elif PLCPU_IAXX == PLCPU_IA64

	#endif

#else
	#if PLCPU_IAXX == PLCPU_IA32
		int64_pl __PLSysAPI_GetHotBitPos64_H2LSearch(uint64_pl iValue){
			int64_pl iPos;
			int32_pl bAllZero;
			uint32_pl iH32Value;
			uint32_pl iL32Value;
			iL32Value = *((uint32_pl *)(&iValue));
			iH32Value = *(((uint32_pl *)(&iValue))+1);
			iPos = 0;
			__asm__ __volatile__("bsr %2,%0\n sete %%cl \n add $32,%0 \n cmp $1,%%cl \n jnz __H2LSearch_end_bsr \n bsr %3,%0 \n sete %%cl \n\t"
					"__H2LSearch_end_bsr: movzx %%cl,%1 ":"=b"((*((int32_pl *)(&iPos)))),"=c"(bAllZero):"a"(iH32Value),"d"(iL32Value):);
			return bAllZero == 1 ? -1 : iPos;
		}
		int64_pl __PLSysAPI_GetHotBitPos64_L2HSearch(uint64_pl iValue){
			int64_pl iPos;
			int32_pl bAllZero;
			uint32_pl iH32Value;
			uint32_pl iL32Value;
			iL32Value = *((uint32_pl *)(&iValue));
			iH32Value = *((uint32_pl *)(&iValue)+1);
			iPos = 0;
			__asm__ __volatile__("bsf %2,%0\n sete %%cl \n cmp $1,%%cl \n jnz __L2HSearch_end_bsr \n bsr %3,%0 \n sete %%cl \n  add $32,%0 \n\t"
					"__L2HSearch_end_bsr: movzx %%cl,%1 ":"=b"((*((int32_pl *)(&iPos)))),"=c"(bAllZero):"a"(iL32Value),"d"(iH32Value):);
			return bAllZero == 1 ? -1 : iPos;
		}
	#elif  PLCPU_IAXX == PLCPU_IA64

	#endif
#endif
