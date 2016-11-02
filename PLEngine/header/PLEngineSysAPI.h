/*
 * PLEngineSysAPI.h
 *
 *  Created on: 2009-7-1
 *      Author: root
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineGraphicsInface.h"
#include "PLEngineH.h"
#include "PLEngineResultVD.h"
#include "PLEngineInface.h"
#ifndef PLENGINESYSAPI_H_
#define PLENGINESYSAPI_H_
	/*
	 * here define c and c++ Standard Library function
	 * */
	//Data Struct
//	#define  PLTSys_Mutex  _Syn_SysMutexLock
//	#define  PLTSys_Signal _Syn_SysSignalLock

	/*
	 * down define operting system Unique  system api
	 * */
	PL_SystemTimer * _MaxSystemTimer_(PL_SystemTimer * ptr1,PL_SystemTimer * ptr2);
	void _CalculSysTimerInterval_(PL_SystemTimer * ptrH,PL_SystemTimer * ptrL,PL_SystemTimer * ptrInterval);
	void _CalculSysTimerIntervalMaxSubMin_(PL_SystemTimer * ptrH,PL_SystemTimer * ptrL,PL_SystemTimer * ptrInterval);
	void _CalculSysTimerAdd_(PL_SystemTimer * ptrBase,PL_SystemTimer * ptrAdd);

	/* Initializ Engine Timer handle
	 * Frist Paramer   is Timer Strurct Pointer*/
	_PLE_lib_c _CallStack_default_ HPL_Result PLSysAPI_InitializSystemTimer(PLSystemTimerHandle);
	/* Get Current Engine Timer
	 * Frist  Paramer  is Engine Timer handle
	 * Second Paramer  is Current Engine Timer Strurct Pointer */
	_PLE_lib_c _CallStack_default_ HPL_Result PLSysAPI_GetSystemLastTimerKey(PLSystemTimerHandle,PL_SystemTimer *);
	/* Calcul Engine Timer Interval
	 * Frist  Paramer  is last Timer Value Pointer
	 * Second Paramer  is after Timer Value Pointer
	 * Third  Paramer  is Result Calcul Complete Timer Interval*/
	_PLE_lib_c _CallStack_default_ HPL_Result PLSysAPI_Calcul_SysTimerInterval(PL_SystemTimer*,PL_SystemTimer*,PL_SystemTimer*);
	/* Calcul Engine Timer Add , Cumulative To Base
	 * First  Paramer  is Base Timer Value
	 * Second Paramer  is Cumulative Timer Interval*/
	_PLE_lib_c _CallStack_default_ HPL_Result PLSysAPI_Calcul_SysTimerAdd(PL_SystemTimer * ptrBase,PL_SystemTimer * ptrAdd);


	_PLE_lib_c _CallStack_default_ HPL_Result PLSysAPI_Lib_OpenLibrary(PLLibModuleHandle * ptrhAndle,const_pl UTFSyschar_pl * ptrName,intV_pl iwNameLength,int_pl iTag);
	_PLE_lib_c _CallStack_default_ HPL_Result PLSysAPI_Lib_CloseLibrary(PLLibModuleHandle hAndle);
	_PLE_lib_c _CallStack_default_ void_pl *  PLSysAPI_Lib_SearchLibraryObject(PLLibModuleHandle hAndle,const_pl UTFSyschar_pl * ptrFunName ,intV_pl iwFNSize);
	_PLE_lib_c _CallStack_default_ void_pl *  PLSysAPI_Lib_SearchLibraryObjectIndex(PLLibModuleHandle hAndle,int_pl iIndex);
	#define PLSysAPI_SysIO_isLegalUTF8  __PLSysAPI_SystemIO_isLegalUTF8_

	#if PLOperat_System == PLOperatSystem_Linux
		#include "Linux/PLEngineSysAPI_Linux.h"
	#elif PLOperat_System == PLOperatSystem_Window
		#include "Windows/PLEngineSysAPI_Windows.h"
	#endif

	/*
	 * Code with Compiler
	 * */
	#if PLCompiler_Tool == PLCompiler_MSVC
		#ifndef PLSysAPI_berrier
			#define PLSysAPI_berrier
		#endif
		#ifndef PLSysAPI_RMberrier __asm lfence
			#define PLSysAPI_RMberrier //read memory data command berrier
		#endif
		#ifndef PLSysAPI_WMberrier __asm sfence
			#define PLSysAPI_WMberrier // write memory data command berrier
		#endif
		#ifndef PLSysAPI_RWMberrier
			#define PLSysAPI_RWMberrier __asm mfence // read and write memory data command berrier
		#endif

		//CAS command mode like windows's interlockedexchange..  if artvalue == destvalue  set dest = newValue  CF=1 ,  sete command is set cf to uValue , else cf=0 destvalue no change
		inline bool_pl PLSysAPI_LockedCAS_32(uint32_pl * ptrlOldValue,uint32_pl lnewValue,uint32_pl lartValue){
			bool_pl uValue;
			__asm{
					mov eax,lartValue;
					mov ebx,lnewValue;
					lock cmpxchg [ptrlOldValue],ebx;
					sete al;
					mov uValue,al;
			}
			return uValue;
		}
		inline bool_pl PLSysAPI_LockedCAS2_32(uint64_pl * ptrllOldValue,uint32_pl uLownewValue,uint32_pl uHignewValue,uint32_pl uLowArtValue,uint32_pl uHigArtValue){
			bool_pl uValue;
			__asm{
				mov eax,uLowArtValue
				mov edx,uHigArtValue
				mov ebx,uLownewValue
				mov ecx,uHignewValue
				mov edi,ptrllOldValue
				lock cmpxchg8b dword ptr [edi]
				sete al
				mov uValue,al
			}
			return uValue;
		}
		inline bool_pl PLSysAPI_LockedCAS2_64(uint64_pl * ptrllOldValue,uint64_pl lNewValue,uint64_pl lArtValue){
			bool_pl uValue;
			uint32_pl * ptrPN;
			uint32_pl * ptrPA;
			ptrPN = (uint32_pl *)(&lNewValue);
			ptrPA = (uint32_pl *)(&lArtValue);
			__asm{
				mov eax,[ptrPA]
				mov edx,[ptrPA + 4]
				mov ebx,[ptrPN]
				mov ecx,[ptrPN + 4]
				mov edi,ptrllOldValue
				lock cmpxchg8b dword ptr [edi]
				sete al
				mov uValue,al
			}
			return uValue;
		}

		inline int32_pl __PLSysAPI_GetHotBitPos32_H2LSearch(uint32_pl iValue){
			int32_pl iPos;
			int32_pl bAllZero;
			__asm{
				mov ebx,iValue
				bsr eax,ebx
				sete dl
				mov iPos,eax
				movzx edx,dl
			}
			return bAllZero ==1 ? -1 : iPos;
		}
		inline int32_pl __PLSysAPI_GetHotBitPos32_L2HSearch(uint32_pl iValue){
			int32_pl iPos;
			int32_pl bAllZero;
			__asm{
				mov ebx,iValue
				bsf eax,ebx
				sete dl
				mov iPos,eax
				movzx edx,dl
			}
			return bAllZero ==1 ? -1 : iPos;
		}
	#elif PLCompiler_Tool == PLCompiler_GCC
		//
		#ifndef PLSysAPI_berrier
			#define PLSysAPI_berrier    __asm__ __volatile__ ("lock; add $1,%%eax":::"memory")
		#endif
		#ifndef PLSysAPI_RMberrier
			#define PLSysAPI_RMberrier  __asm__ __volatile__ ("lfence":::"memory")  //read memory data command berrier
		#endif
		#ifndef PLSysAPI_WMberrier
			#define PLSysAPI_WMberrier  __asm__ __volatile__ ("sfence":::"memory") // write memory data command berrier
		#endif
		#ifndef PLSysAPI_RWMberrier
			#define PLSysAPI_RWMberrier __asm__ __volatile__ ("mfence":::"memory") // read and write memory data command berrier
		#endif

		//CAS command mode like windows's interlockedexchange..  if artvalue == destvalue  set dest = newValue  CF=1 ,  sete command is set cf to uValue , else cf=0 destvalue no change
		inline bool_pl PLSysAPI_LockedCAS_32(volatile_pl int32_pl * ptrlOldValue,int32_pl lnewValue,int32_pl lartValue){
			int32_pl uValue;//__volatile__
			__asm__ __volatile__ ("lock cmpxchg %2,%1 \n\t""sete %%al\n\t""movzx %%al,%0" : "=a"(uValue) : "m"(*ptrlOldValue),"b"(lnewValue),"0"(lartValue) : "memory");
			return uValue;
		}
		inline bool_pl PLSysAPI_LockedCAS2_32(volatile_pl uint64_pl * ptrllOldValue,uint32_pl uLownewValue,uint32_pl uHignewValue,uint32_pl uLowArtValue,uint32_pl uHigArtValue){
			int32_pl uValue;
			__asm__ __volatile__("lock cmpxchg8b %1 \n\t""sete %%al\n\t""movzx %%al,%0" : "=a"(uValue):"m"(*ptrllOldValue),"0"(uLowArtValue),"d"(uHigArtValue),"b"(uLownewValue),"c"(uHignewValue) : "memory");
			return uValue;
		}
		inline bool_pl PLSysAPI_LockedCAS2_64(volatile_pl int64_pl * ptrllOldValue,int64_pl lNewValue,int64_pl lArtValue){
			int32_pl uValue;
			int32_pl * ptrN;
			int32_pl * ptrA;
			ptrN = (int32_pl *)(&lNewValue);
			ptrA = (int32_pl *)(&lArtValue);
			__asm__ __volatile__("lock cmpxchg8b %1 \n\t""sete %%al\n\t""movzx %%al,%0" : "=a"(uValue):"m"(*ptrllOldValue),"0"(*ptrA),"d"(*(++ptrA)),"b"(*ptrN),"c"(*(++ptrN)) : "memory");
			return uValue;
		}
		inline int32_pl __PLSysAPI_GetHotBitPos32_H2LSearch(uint32_pl iValue){
			int32_pl iPos;
			int32_pl  bAllZero;
			__asm__ __volatile__("bsr %2,%0\n sete %%cl \n movzx %%cl,%1 ":"=b"(iPos),"=c"(bAllZero):"a"(iValue));
			return bAllZero == 1 ? -1 : iPos;
		}
		inline int32_pl __PLSysAPI_GetHotBitPos32_L2HSearch(uint32_pl iValue){
			int32_pl iPos;
			int32_pl  bAllZero;
			__asm__ __volatile__("bsf %2,%0\n sete %%cl \n movzx %%cl,%1 ":"=b"(iPos),"=c"(bAllZero):"a"(iValue));
			return bAllZero == 1 ? -1 : iPos;
		}
		inline int32_pl __PLSysAPI_GetHotBitPos32_H2LSearch_Predigest(uint32_pl iValue){
			int32_pl iPos;
			__asm__ __volatile__("bsr %1,%0":"=r"(iPos):"r"(iValue));
			return iPos;
		}
		inline int32_pl __PLSysAPI_GetHotBitPos32_L2HSearch_Predigest(uint32_pl iValue){
			int32_pl iPos;
			__asm__ __volatile__("bsf %1,%0\n":"=r"(iPos):"r"(iValue));
			return iPos;
		}
	#endif

	_PLE_lib_c _CallStack_default_ int64_pl __PLSysAPI_GetHotBitPos64_H2LSearch(uint64_pl iValue);
	_PLE_lib_c _CallStack_default_ int64_pl __PLSysAPI_GetHotBitPos64_L2HSearch(uint64_pl iValue);
	#define PLSysAPI_GetHotBitPosH2L32  	__PLSysAPI_GetHotBitPos32_H2LSearch
	#define PLSysAPI_GetHotBitPosL2H32  	__PLSysAPI_GetHotBitPos32_L2HSearch
	#define PLSysAPI_GetHotBitPosH2L64  	__PLSysAPI_GetHotBitPos64_H2LSearch
	#define PLSysAPI_GetHotBitPosL2H64  	__PLSysAPI_GetHotBitPos64_L2HSearch
	#define PLSysAPI_GetHotBitPosH2L32Pre	__PLSysAPI_GetHotBitPos32_H2LSearch_Predigest
	#define PLSysAPI_GetHotBitPosL2H32Pre   __PLSysAPI_GetHotBitPos32_L2HSearch_Predigest


	//math system api define
	#define PLSysAPI_CosF(v)   cosf(v)
	#define PLSysAPI_SinF(v)   sinf(v)
	#define PLSysAPI_Sqrt(v)   sqrt(v)
	#define PLSysAPI_FAbs(v)   fabs(v)
	#define PLSysAPI_Abs(v)    abs(v)
	#define PLSysAPI_Exp(v)    exp(v)
	#define PLSysAPI_Tan(v)    tan(v)
	#define PLSysAPI_Pow(x,y)  pow(x,y)
	#define PLSysAPI_Modf(v,z) modf(v,z)

	#define PLSysAPI_Exis2logValue(value) ((value & (value - 1)) == 0)
	#define PLSysAPI_Alignment(A,ALIGNMENTSIZE) 	((A + (ALIGNMENTSIZE  -1)) & (~(ALIGNMENTSIZE - 1))) //meomry byte alignment,and ALIGNMENTSIZE must = 2^n
	#define PLSysAPI_Alignment_Low(A,ALIGNMENTSIZE) (A & (~(ALIGNMENTSIZE - 1)))						 //low addres alignment,and ALIGNMENTSIZE must = 2^n

	#define PLSysAPI_IntV2UIntV(v) (*((uintV_pl *)(&v)))	//intV_pl data type conver uintV_pl data type

	/*
	 *
	 * Memory operting
	 *
	 * */
	#define PLSysAPI_MemorySet(p,value,size) ::memset(p,value,size)
	#define PLSysAPI_MemoryCpy(p1,p2,size)   ::memcpy(p1,p2,size)
	#define PLSysAPI_MemoryClearZero(p,size) ::memset(p,0x0,size)
	#define PLSysAPI_MemoryCmp(p1,p2,size)   ::memcmp(p1,p2,size)


	#if PLCPU_IAXX == PLCPU_IA32
		#define PLSysAPI_LockedCAS(ptrOldValue,newValue,artValue) PLSysAPI_LockedCAS_32(ptrOldValue,newValue,artValue)
		#define _Synchron_Lock uint32_pl
		#define PLSysAPI_GetHotBitPosH2LV	PLSysAPI_GetHotBitPosH2L32
		#define PLSysAPI_GetHotBitPosL2HV	PLSysAPI_GetHotBitPosL2H32
	#elif PLCPU_IAXX == PLCPU_IA64
		#define PLSysAPI_LockedCAS(ptrOldValue,newValue,artValue) PLSysAPI_LockedCAS2_64(ptrOldValue,newValue,artValue)
		#define _Synchron_Lock uint64_pl
		#define _Synchron_SysMutex_lock
		#define PLSysAPI_GetHotBitPosH2LV	PLSysAPI_GetHotBitPosH2L64
		#define PLSysAPI_GetHotBitPosL2HV	PLSysAPI_GetHotBitPosL2H64
	#endif
	#define PLSysAPI_JudgeSetValueInt PLSysAPI_LockedCAS
#endif /* PLENGINESYSAPI_H_ */
