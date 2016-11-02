/*
 * PLEngineI.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineGraphicsInface.h"
#include "PLEngineH.h"
#include "PLEngineInface.h"
#include "PLEngineResultVD.h"

#ifndef PLENGINEI_H_
#define PLENGINEI_H_
	/*
	 * EngineConstID.chr
	 * FileKeyID  4byte 0x2E 0x63 0x68 0x72
	 * Const Char Item Count  8 byte
	 *
	 * */
	//PLCPUI_XXXX PLCPUI_RISC
	#if PLCPUI_XXXX == PLCPUI_RISC
		#define PLSys_ConstChar_FileHeaderMark           0x2e636872
	#else
		#define PLSys_ConstChar_FileHeaderMark           0x7268632e
	#endif
	#define PLSys_ConstChar_EngineCFG                0
	#define PLSys_ConstChar_CreateLibraryFunN        1
	#define PLSys_ConstChar_CreateLibraryFun         2
	#define PLSys_ConstChar_CreateLibraryEnter       3
	#define PLSys_ConstChar_PlusLable                4
	#define PLSys_ConstChar_DebugInformationFileName 5
	#define PLSys_ConstChar_ScenePlus                6
	#define PLSys_ConstChar_ScriptPlus               7
	#define PLSys_ConstChar_RenderSystemPlus         8
	#define PLSys_ConstChar_AIPlus                   9
	#define PLSys_ConstChar_PhysicsPlus              10
	#define PLSys_ConstChar_PlusCWD                  11
	#define PLSys_ConstChar_ResourcePlus             12
	#define PLSys_ConstChar_ResourceCWD              13
	#define PLSys_ConstChar_PathLable                14
	#define PLSys_ConstChar_LogPlus                  15
	#define PLSys_ConstChar_LogCWD                   16
	#define PLSys_ConstChar_ResourceMgrPlus          17
	#define PLSys_ConstChar_ConstChrCWD				 18
	#define PLSys_ConstChar_DownloadCWD				 19

	/*
	 * Engine_DebugConstID.chr
	 * FileKeyID  4byte 0x2E 0x63 0x68 0x72
	 * Const Char Item Count  8 byte
	 *
	 * */
	#define PLSys_ConstChar_CreateEngineHandle_Dbg 0
	#define PLSys_ConstChar_OK_Dbg                 1
	#define PLSys_ConstChar_Fail_Dbg               2
	#define PLSys_ConstChar_DestoryEngineHandl_Dbg 3

	_PLE_lib_Variable PL_EngineState 			* g_ptrCurrentEngineState;
	_PLE_lib_Variable PLConstCharTableHandle 	  g_hDbgCharTable;
//	static PLGMemMapItem g_MapItemList[PLMem_Const_MemoryManagerMaxItemCount] = {0};
	extern PLThreadVirtualID	 	g_ThreadAllID;
	extern PLMemManager  	 	 	g_MemPoolManager;
	extern PLTLSKey     	 	 	g_allocateOrganKey;
	extern PLTLSKey      		 	g_ThreadVirtualIDKey;
	extern PLMemFreeObject     * 	g_AllocateOrganFreeList;
	extern _Syn_SpinLock         	g_AOFreeListLock;
	extern volatile_pl intV_pl   	g_iAOMaxSize;
	extern volatile_pl intV_pl   	g_iAOCurrentSize;

	const_pl UTF16char_pl g_strEngineConstFile[]={L'E',L'n',L'g',L'i',L'n',L'e',L'C',L'o',L'n',L's',L't',L'I',L'D',L'.',L'c',L'h',L'r',00};
	#define PLSys_ConstChar_EngineConstFile          g_strEngineConstFile //L"EngineConstID.chr\0"
	#define PLSys_ConstChar_URLPathConstDivision     PLSys_ConstChar_SystemCWDPartition

	#define PLSys_ConstChar_ExpandSplitSymbol        ((UTF16char_pl)(0x2e))

#endif /* PLENGINEI_H_ */
