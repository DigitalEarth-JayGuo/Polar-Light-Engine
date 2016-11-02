/*
 * PLEngineInface.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */

#include "PLEngineBaseH.h"
#include "PLEngineGraphicsInface.h"
#include "PLEngineMemoryPoolInface.h"
#include "PLEngineSysTextCharInface.h"
#include "PLEngineSysProcessInface.h"
#include "PLEngineSysIOInface.h"
#include "PLEngineScriptAPIInface.h"
#include "PLEngineSysSynchronInface.h"
#include "PLEngineRenderAPIInface.h"
#include "PLEngineResourceLoadAPIInface.h"
#include "PLEngineSysSchedulerInface.h"
#include "PLEngineLogSystemAPIInface.h"
#include "PLEngineSysSTLArithmeticAPIInface.h"
#include "PLEngineResourceManagerAPIInface.h"
#include "PLEngineSysWindowsAPIInface.h"
#include "PLEngineSysThreadPoolInface.h"
#include "PLEngineSysNetworkAPIInface.h"
//#include "PLEngineHeavyH.h"
#ifndef PLENGINEINFACE_H_
#define PLENGINEINFACE_H_

	#define PL3DSystemFileFNameMaxLength     256
	#define PL3DSystemFilePathNameMaxLength  256
	#define PL3DSystemModuleNameMaxLength 	 64
	#define PL3DSystemHostNameMaxLength 	 125
	#define PL3DSystemFunSymbolMaxLength 	 64
	#define PLTimerHandle   void_pl *
	#define PLMemHandle     void_pl *
	#define PLMemHandle_PID void_pl *
	#define PLLibraryHandle void_pl *
		#define PLLibraryHandle_Invalid NULL_PL

	#define PLFileCFGHandle 		void_pl *
	#define PLConstCharTableHandle  void_pl *

	#define PLSys_Const_defaultCPUCacheLineSize 64
	#define PLSys_Const_CPUHardwareModeAligned PLSys_Const_defaultCPUCacheLineSize
	#if PLCPU_IAXX == PLCPU_IA32
		#define PLSys_Const_CPUDataBitAligned      4
	#else
		#define PLSys_Const_CPUDataBitAligned      8
	#endif

	#define __PLPtrConverDataT__(ty,data) (*((ty*)(&(data))))
	#define __PLTSizetoInt__(v)   v
	#define __PLTSizetoLInt__(v)  v
	#define __PLTSizetoUInt__(v)  v
	#define __PLTSizeToULInt__(v) v
	#if PLOperat_System == PLOperatSystem_Window
		#define PLLibModuleHandle HMODULE
		#define PLSys_ConstChar_CreateLibrary PLSys_ConstChar_CreateLibraryFunN
	#elif PLOperat_System == PLOperatSystem_Linux
		#define PLLibModuleHandle void_pl *
		#define PLSys_ConstChar_CreateLibrary PLSys_ConstChar_CreateLibraryFun
	#elif PLOperat_System == PLOperatSystem_Unix
		#define PLLibModuleHandle void_pl *
	#elif PLOPerat_System == PLOperatSystem_MacOS
		#define PLLibModuleHandle void_pl *
	#endif

	#define PLSys_Const_PlusCreateEnter_NameSize 64

	#define PLCfg_Const_LableNameMaxSize   64
	#define PLCfg_Const_IDNameMaxSize      128
	#define PLCfg_Const_LableMaxCount      256

	/*********Begin Define Manager Memory Level************/
	#define PLSys_ConstID_LThreadManagerPool    1
	#define PLSys_ConstID_GlobalManagerPool     0
	/*********************/

	/***********/
	#define PLChr_ConstID_StringEndChrLength 1
	/***********/
	/*
	 * Function Heavy type
	 */
	typedef enum _ePL_LibraryHeavyStyle{
		PLSys_Const_SystemWith_ePLLibraryHeavyStyle  = 3,
		PLSys_Const_SystemTimer_ePLLibraryHeavyStyle = 5,
		PLSys_Const_Math_ePLLibraryHeavyStyle
	}ePL_LibraryHeavyStyle;

	//use Library install or unintstall action call function
	typedef _CallStack_default_ PLLibraryHandle ( * __Create_Library__PL__ )	(HPPLEngine,void_pl *);
	typedef _CallStack_default_ bool_pl    		(* __Install_Library__PL__  )   (HPPLEngine,PLLibraryHandle,void_pl *);
	typedef _CallStack_default_ HPL_Result 		(* __UnInstall_Library__PL__)   (HPPLEngine,PLLibraryHandle,void_pl *);
	typedef _CallStack_default_ void_pl    		(* __Destory_Library__PL__)	    (HPPLEngine,PLLibraryHandle,void_pl *);

	/*
	 *
	 *
	 *
	 * Base Expand Struct Header
	 * */
//	typedef Aligned(4) struct _SPL_BaseExpandCompatibleHeader{
//		int_pl sheader;					//Header Space Length
//		int_pl sData;					//Data Segment Length
//		int_pl sExpandData;				//Expand Data Segment Length
//		int_pl sReserve;				//Reserve Segment Length
//	}PL_BaseExpandCompatibleHeader;
	/*
	 * Library struct define
	 * */
#pragma pack(8)
	typedef  struct _SPL_Library{
		UTF16char_pl  pFileName[PL3DSystemFileFNameMaxLength];
		intV_pl  iwFileNameLength;
		UTF16char_pl  pModuleName[PL3DSystemModuleNameMaxLength];
		intV_pl  iwModuleNameLength;
		PLLibModuleHandle hModuleAndle;
	}PL_Library;

	//library function table
	typedef  struct Aligned(PLSys_Const_CPUDataBitAligned) SPL_EngineLibrary_FunTable{
		intV_pl cbSize;
		intV_pl iFunCount;
		fun_pl functionlist[1];
	}__Aligned(PLSys_Const_CPUDataBitAligned) PL_EngineLibraryFunTable;
	typedef struct Aligned(8) _SPL_EngineLibraryHeavyInface{
		intV_pl cbSize;
		_SPL_EngineLibraryHeavyInface * ptrNext;
		ePL_LibraryHeavyStyle     eStyle;
		PLLibModuleHandle         hModuleHandle;
		__Install_Library__PL__   InstallLibraryPL;
		__UnInstall_Library__PL__ UnInstallLibraryPL;
		__Destory_Library__PL__   Destory_LibraryPL;
		intV_pl 				  cbExternDataSize;
		void_pl *                   ptrExternData;
		PL_EngineLibraryFunTable  * ptrFunTable;
	}__Aligned(8) PL_EngineLibraryHeavyInface;
	//plus node struct define
	typedef struct Aligned(8) _SPL_EngineLibraryPlusNode{
		intV_pl cbSize;
		_SPL_EngineLibraryPlusNode * ptrNext;
		PL_EngineLibraryHeavyInface * ptrInface;
		UTFSyschar_pl ptrName[PL3DSystemModuleNameMaxLength];
		intV_pl iNSize;
		//volatile_pl intV_pl iRefCount;
	}__Aligned(8) PL_EngineLibraryPlusNode;

	/*
	 * timer struct
	 * */
	typedef  struct _SPL_SystemTimer{
		uintV_pl ins;
		uintV_pl isecond;
		uintV_pl iday;
		uintV_pl iyear; //ten thousand years
		intV_pl  iCalculSymbol;
	}PL_SystemTimer;
	typedef  struct _SPL_SystemTimerObject{
		intV_pl cbSize;
		PL_SystemTimer ElapseTimer;
		PL_SystemTimer AfterSystemTimerKey;
		PL_SystemTimer LastSystemTimerKey;
		luint_pl      CycleTimerH;
		luint_pl      CycleTImerL;
	}PL_SystemTimerObject,* PLSystemTimerHandle;
	typedef  struct _SPL_EHandleInface{
		intV_pl        cbSize;
		void_pl      * ptrMem;
		PL_SystemTimer StVirtualSysT;	//3d system's virtual timer
	} PL_EHandleInface;
	typedef  struct _SPL_OperatSystemInfo{
		lint_pl lFreeMemorySize; //Current Sys Free Memory
	} PL_OperatSystemInfo;
	typedef  struct _SPL_OperatSysEnvSet{
		UTFSyschar_pl pCWD[PL3DSystemFilePathNameMaxLength];
		intV_pl iwCWDSize;
		UTFSyschar_pl pPlusCWD[PL3DSystemFilePathNameMaxLength];
		intV_pl iwPlusCWDSize;
		UTFSyschar_pl pResourceCWD[PL3DSystemFilePathNameMaxLength];
		intV_pl iwResourceCWDSize;
	} PL_OperatSysEnvSet;
	typedef  struct _SPL_EnginePlusStandard{
		UTFSyschar_pl pCreateEnterName[PLSys_Const_PlusCreateEnter_NameSize];
		intV_pl  iwEnterNSize;
	} PL_EnginePlusStandard;
#pragma pack()

#pragma pack(1)
	typedef  struct _SPL_FileConstCharResource{
		uint32_pl uFileMark;
		int32_pl  iCount;
		uint32_pl uParamer1;
		uint32_pl uParamer2;
		uint32_pl uLTag;
		uint32_pl uHTag;
		int64_pl lFillDataSize;
	}PL_FileConstCharResource;
	typedef struct _SPL_ObjectChainPointer{
		_SPL_ObjectChainPointer * ptrNext;
	}PL_ObjectChainPointer;
#pragma pack()

#pragma pack(8)
	typedef  struct _SPL_EngineConstCharResource{
		union {
			UTFSyschar_pl *  ptrResource;
			UTF8char_pl   *  ptrUTF8Resource;
			UTF16char_pl  *  ptrUTF16Resource;
			UTF32char_pl  *  ptrUTF32Resource;
			AddresValue_pl	 Addres;
		}_Pointer;
		union{
			intV_pl    iwBSize;
			intV_pl    iUTF8Size;
			intV_pl    iUTF16Size;
			intV_pl    iUTF32Size;
		}BSize;
	}PL_EngineConstCharResource;
	typedef  struct _SPL_EngineConstCharTable{
		intV_pl   icbSize;
		void_pl * ptrMem;
		void_pl * ptrConstCharData;
		void_pl * ptrConstCharMem;
		intV_pl   iCount;
		intV_pl   iMaxCount;
		PL_EngineConstCharResource pTable[1];
	} PL_EngineConstCharTable;
	typedef struct _SPL_ConstSystemInfo{
		int_pl   lProcessNumber;   //cpu core number
		int_pl   lCPUNumber;       //cpu number
		lint_pl  lMemoryAMount;   //Memory AMount Size
		intV_pl  lPhysPageSize;   //Pages Size
		intV_pl  iCacheLineSize; //CPU Cache Line size
		intV_pl  iAllocationGranularity; //allocate memory granularity
	} PL_ConstSystemInfo;


	/*
	 * 3DEngine Handle
	 * */
	typedef  struct Aligned(PLSys_Const_CPUHardwareModeAligned) _SPL_EngineState{
		PL_EHandleInface head;					//base inface
		PL_ConstSystemInfo    ConstSysInfo; //Const Hard Info
		PL_OperatSystemInfo   SysInfo;		//SystemEnvInfo
		PL_OperatSysEnvSet    OperatEnv;    //OperatSystem Env
		PL_EnginePlusStandard PlusStandard; //Plus define Standard
		PLConstCharTableHandle hSysConstCharTable; //Const String ID Table;
		PLConstCharTableHandle hDbgConstCharTable; //Debug Information Const String ID Table;
		PLSystemTimerHandle * ptrSysT;  		//operting System Timer
//		PL_SystemTimer StSysT;					//operting system timer
		bool_pl                       bInitialize;
		bool_pl                       bNetworkInitialize;
		PL_EngineLibraryPlusNode   ** ptrCurrentPlusNodeList; //current plus node list
		intV_pl 					  iCurPNLCount;			  //current plus node count

		PL_EngineLibraryPlusNode MathPlus; //Math Heavy Library Pointer
		PL_EngineLibraryPlusNode DefaultMathPlus;
		PL_EngineLibraryPlusNode SysWithPlus; //SystemW
		PL_EngineLibraryPlusNode DefaultSysWithPlus;
		PL_EngineLibraryPlusNode ScriptPlus;
		PL_EngineLibraryPlusNode RenderSystemPlus;
		PL_EngineLibraryPlusNode SceneManagerPlus;
		PL_EngineLibraryPlusNode ResourceManagerPlus;
		PL_EngineLibraryPlusNode ResourceLoadPlus;
		PL_EngineLibraryPlusNode LogSystemPlus;
		PL_EngineLibraryPlusNode FontSystemPlus;
	}__Aligned(PLSys_Const_CPUHardwareModeAligned) PL_EngineState;

	typedef  struct _SPL_FileCfgTable{
		_SPL_FileCfgTable * ptrNext;
		UTFSyschar_pl pTableN[PLCfg_Const_LableMaxCount][PLCfg_Const_LableNameMaxSize];
		intV_pl iTableSize[PLCfg_Const_LableMaxCount];
		lint_pl lTablePos[PLCfg_Const_LableMaxCount];
		lint_pl lTableEndPos[PLCfg_Const_LableMaxCount];
		intV_pl iLableCount;
	}PL_FileCfgTable;

	typedef  struct _SPL_FileCfgHeader{
		intV_pl cbSize;
		ePL_CharCodeStyle eCharCode;
		void_pl * ptrMem;
		FILEStream * hFile;
		PL_FileCfgTable Tables;
		intV_pl iLableAMount;
		/*
		UTFSyschar_pl pTableN[PLCfg_Const_LableMaxCount][PLCfg_Const_LableNameMaxSize];
		intV_pl iTableSize[PLCfg_Const_LableMaxCount];
		lint_pl lTablePos[PLCfg_Const_LableMaxCount];
		lint_pl lTableEndPos[PLCfg_Const_LableMaxCount];
		intV_pl iLableCount;
		*/
	}PL_FileCfgHeader;
#pragma pack()
#endif /* PLENGINEINFACE_H_ */
