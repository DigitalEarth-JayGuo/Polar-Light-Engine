/*
 * PLEngineBaseDataType.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */

#ifndef PLENGINEBASEDATATYPE_H_
#define PLENGINEBASEDATATYPE_H_

	//Compiler is MS VC
	#define PLCompiler_MSVC 0
	//Compiler is GCC
	#define PLCompiler_GCC  1
	//define work at OpertSystem
		/*
		 *
		 *windows default use WinXP
		 *Linux default kernel 2.6.4
		 *
		 */
		#define PLOperatSystemVer_Default 0
	#define PLOperatSystem_Window 0
		//#define
	#define PLOperatSystem_Linux  1
		//#define
	#define PLOperatSystem_Unix   2
	#define PLOperatSystem_MacOS  3

	//CPU command Model
	#define PLCPUI_CISC	0
	#define PLCPUI_RISC 1
	//CPU work Model
	#define PLCPU_IA32 0
	#define PLCPU_IA64 1

	//CPU Product
	#define PLCPU_RDefault 0
	#define PLCPU_RIt	 	  1

	//CPU Data Struct  (this project define x86 is smallend data)
	#define PLCPU_DataByteSmallEnd 0
	#define PLCPU_DataByteBigEnd	 1

	//System Default String CharCode
	#define PLEngineSysChar_Unicode8  0
	#define PLEngineSysChar_Unicode16 1
	#define PLEngineSysChar_Unicode32 2


/***(((((((((((((((((((((((((((CPU bit Mode define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(PLCPU_IAXX)) && defined(IDESetCPUIA32)
		#define PLCPU_IAXX PLCPU_IA32
	#endif
	#if (!defined(PLCPU_IAXX)) && defined(IDESetCPUIA64)
		#define PLCPU_IAXX PLCPU_IA64
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***(((((((((((((((((((((((((((CPU dictate collect define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(PLCPUI_XXXX)) && defined(IDESetCPUI_CISC)
		#define PLCPUI_XXXX PLCPUI_CISC
	#endif
	#if (!defined(PLCPUI_XXXX)) && defined(IDESetCPUI_RISC)
		#define PLCPUI_XXXX PLCPUI_RISC
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***(((((((((((((((((((((((((((CPU dictate collect define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(PLCPU_RealmXX)) && defined(IDESetCPURealm_It)
		#define PLCPU_RealmXX PLCPU_RIt
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***(((((((((((((((((((((((((((CPU DataByte SmallEnd or BigEnd define)))))))))))))))))))))))))))))))))))***/
	#if (!defined(PLCPU_DataByteRank)) && defined(IDESetCPUDataByte_SmallEnd)
		#define PLCPU_DataByteRank PLCPU_DataByteSmallEnd
	#endif
	#if (!defined(PLCPU_DataByteRank)) && defined(IDESetCPUDataByte_BigEnd)
		#define PLCPU_DataByteRank PLCPU_DataByteBigEnd
	#endif
/***((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))***/
/***++++++++++++++++++++++++++++++++Compiler define++++++++++++++++++++++++++++++++++***/
	#if (!defined(PLCompiler_Tool)) && defined(IDESetGCCCompiler)
		#define PLCompiler_Tool PLCompiler_GCC
	#endif
	#if (!defined(PLCompiler_Tool)) && defined(IDESetMSVCCompiler)
		#define PLCompiler_Tool PLCompiler_MSVC
	#endif
/***+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++***/
/***------------------------------run OperatSystem define----------------------------***/
	#if (!defined(PLOperat_System)) && defined(IDESetWindowOperatSystem)
		#define PLOperat_System PLOperatSystem_Window
	#endif
	#if (!defined(PLOperat_System)) && defined(IDESetLinuxOperatSystem)
		#define PLOperat_System PLOperatSystem_Linux
	#endif
	#if (!defined(PLOperat_System)) && defined(IDESetUnixOperatSystem)
		#define PLOperat_System PLOperatSystem_Unix
	#endif
	#if (!defined(PLOperat_System)) && defined(IDESetMacOSOperatSystem)
		#define PLOperat_System PLOperatSystem_MacOS
	#endif
/***---------------------------------------------------------------------------------------------***/
/***------------------------------run OperatSystem Ver define----------------------------***/


/***---------------------------------------------------------------------------------------------***/
/***===============================Default define====================================***/
	#if (!defined(PLCompiler_Tool))
		#define PLCompiler_Tool PLCompiler_MSVC
	#endif
	#if (!defined(PLOperat_System))
		#define PLOperat_System PLOperatSystem_Window
	#endif
	#if (!defined(PLOperat_SystemVer))
		#define PLOperat_SystemVer PLOperatSystemVer_Default
	#endif
	#if (!defined(PLCPU_IAXX))
		#define PLCPU_IAXX PLCPU_IA32
	#endif
	#if (!defined(PLCPUI_XXXX))
		#define PLCPUI_XXXX PLCPUI_CISC
	#endif
	#if (!defined(PLCPU_RealmXX))
		#define PLCPU_RealmXX PLCPU_RDefault
	#endif
	#if PLCPUI_XXXX == PLCPUI_CISC
		#define PLCPU_DataByteRank PLCPU_DataByteSmallEnd
	#elif PLCPUI_XXXX == PLCPUI_RISC
		#if (!defined(PLCPU_DataByteRank))
			#define PLCPU_DataByteRank PLCPU_DataByteSmallEnd
		#endif
	#else
		#if (!defined(PLCPU_DataByteRank))
			#define PLCPU_DataByteRank PLCPU_DataByteSmallEnd
		#endif
	#endif
	#if (!defined(PLESystem_CharCodeUXX))
		#define PLESystem_CharCodeUXX PLEngineSysChar_Unicode16
	#endif
/***=============================================================================================***/

	#if PLOperat_System == PLOperatSystem_Window

		#if PLCompiler_Tool == PLCompiler_MSVC

		#elif PLCompiler_Tool == PLCompiler_GCC

		#endif

		#define _import_lib_class 				__declspec(dllimport)
		#define _export_lib_class 				__declspec(dllexport)
		#define _import_lib_c     				extern "C" __declspec(dllimport)
		#define _export_lib_c     				extern "C" __declspec(dllexport)
		#define _import_lib_variable        	extern __declspec(dllimport)
		#define _import_lib_variableDup     	extern
		#define _import_lib_variableNormal  	__declspec(dllimport)
		#define _export_lib_variable        	extern __declspec(dllexport)
		#define _export_lib_variableDup     	extern
		#define _export_lib_variableNormal 		__declspec(dllexport)
		#define _noexport_lib_variablenormal
		#define BOOL_pl  BOOL
		#define TRUE_pl  TRUE
		#define FALSE_pl FALSE
	#elif PLOperat_System == PLOperatSystem_Linux
		#define _import_lib_class
		#define _export_lib_class				 __attribute__((visibility("default")))
		#define _noexprot_lib_class			 __attribute__((visibility("hidden")))
		#define _import_lib_c                extern "C"
		#define _export_lib_c                extern "C" __attribute__((visibility("default")))
		#define _noexprot_lib_c					 __attribute__((visibility("hidden")))
		#define _import_lib_variable         extern
		#define _import_lib_variableNormal
		#define _import_lib_variableDup
		#define _export_lib_variable         extern __attribute__((visibility("default")))
		#define _export_lib_variableDup
		#define _export_lib_variableNormal
		#define _noexport_lib_variablenormal __attribute__((visibility("hidden")))
		#define BOOL_pl  uint_pl
		#define TRUE_pl  1
		#define FALSE_pl 0

		#if PLCompiler_Tool == PLCompiler_MSVC

		#elif PLCompiler_Tool == PLCompiler_GCC

		#endif
	#elif PLOperat_System == PLOperatSystem_Unix

		#if PLCompiler_Tool == PLCompiler_MSVC

		#elif PLCompiler_Tool == PLCompiler_GCC

		#endif
	#elif PLOperat_System == PLOperatSystem_MacOS
		#if PLCompiler_Tool == PLCompiler_MSVC

		#elif PLCompiler_Tool == PLCompiler_GCC

		#endif
	#endif

	#if PLCompiler_Tool == PLCompiler_MSVC //if use MSVC compiler
		#define Aligned(n) __declspec(align(n))
		#define _CallStack_Order_C
		#define _CallStack_stdcall __stdcall
		#define _CPLSysAPI_MemoryCpyallStack_cdecl   __cdecl
		#define _CallStack_pascal
		#define Define_UNSIGNED_Const(v)(v##u)
		#define Define_SIGNED_Const(v)   v
		#define _FL_(n)     (n##f)
		#define NULL_PL  NULL
		#define hfint_pl  short int
		#define uhfint_pl unsigned short int

		#if PLCPU_IAXX == PLCPU_IA32			//if 32 bit mode
			#define int32_pl    int
			#define uint32_pl   unsigned int
			#define byte_pl     byte
			#define char_pl     char
			#define int64_pl    long long
			#define uint64_pl   unsigned long long
			#define float32_pl  float
			#define int16_pl    short int
			#define uint16_pl   unsigned short int
			//#define wchar2
		#elif PLCPU_IAXX == PLCPU_IA64        //if 64 bit mode
			// this is define 64 bit cpu mode
			#define int32_pl    int
			#define uint32_pl   unsigned int
			#define byte_pl     byte
			#define char_pl     char
			#define int64_pl    long long
			#define uint64_pl   unsigned long long
			#define float32_pl  float
			#define int16_pl    short int
			#define uint16_pl   unsigned short int
		#endif
		#define tchar2_pl   uint16_pl
		#define tchar4_pl   uint32_pl
		#define tchar_pl    wchar
		#define bool_pl     bool
		#define true_pl  true
		#define false_pl false
	#elif PLCompiler_Tool == PLCompiler_GCC
		#define Aligned(n) //__attribute__((aligned(n)))
		#define __Aligned(n) 		__attribute__((aligned(n)))
		#define volatile_pl  		volatile
		#define _CallStack_Order_C
		#define _CallStack_stdcall  __attribute__((stdcall))
		#define _CallStack_cdecl    __attribute__((cdecl))
		#define _CallStack_pascal
		#define Define_UNSIGNED_Const(v)(v##u)
		#define Define_SIGNED_Const(v)   v
		#define _FL_(n)     (n##f)
		#define _U_(n)		(n##U)
		#define hfint_pl  short int
		#define uhfint_pl unsigned short int
		#if PLCPU_IAXX == PLCPU_IA32
			#define int32_pl    int
			#define uint32_pl   unsigned int
			#define wchar_pl    unsigned short int
			#define byte_pl     unsigned char
			#define char_pl     char
			#define int64_pl    long long
			#define uint64_pl   unsigned long long
			#define float32_pl  float
			#define int16_pl    short int
			#define uint16_pl   unsigned short int
		#elif PLCPU_IAXX == PLCPU_IA64
			// this is define 64 bit cpu mode
			#define int32_pl     int
			#define uint32_pl   unsigned int
			#define wchar_pl    unsigned short int
			#define byte_pl     char
			#define char_pl     char
			#define int64_pl    long int
			#define uint64_pl   unsigned long int
			#define float32_pl  float
			#define int16_pl    short int
			#define uint16_pl   unsigned short int
		#endif
		#define tchar2_pl   uint16_pl
		#define tchar4_pl   uint32_pl
		#define tchar_pl    wchar_t
		#define bool_pl uint_pl
		#define true_pl  Define_SIGNED_Const(1)
		#define false_pl Define_SIGNED_Const(0)
		#define NULL_PL  0
	#endif
	#define uchar_pl byte_pl
	#define void_pl  void
	#define fun_pl   void_pl *
	#define const_pl const
	#define PL_CompilerAllocSize(p)  sizeof(p)
	#define volatile_pl volatile
	#if PLCPU_IAXX == PLCPU_IA32
		#define float_pl    float32_pl
		#define int_pl      int32_pl
		#define uint_pl     uint32_pl
		#define PAddress_pl void_pl *
		#define lint_pl     int64_pl
		#define luint_pl    uint64_pl
		#define double_pl   double
		#define sizet_pl    size_t
		#define AddresValue_pl uint32_pl
		#define intV_pl     int32_pl
		#define uintV_pl    uint32_pl
		#define PLSys_ConstID_VIntegerMaxValue	(0x7fffffff)
		#define PLSys_ConstID_VIntegerMinValue	(~(0x7ffffffe))
		//this is define 64 bit cpu mode
	#elif PLCPU_IAXX == PLCPU_IA64
		#define PAddress_pl uint64_pl
		#define float_pl    float32_pl
		#define int_pl      int32_pl
		#define uint_pl     uint32_pl
		#define PAddress_pl void_pl *
		#define lint_pl     int64_pl
		#define luint_pl    uint64_pl
		#define double_pl   double
		#define sizet_pl    size_t
		#define AddresValue_pl uint64_pl
		#define intV_pl     int64_pl
		#define uintV_pl    uint64_pl

		#define PLSys_ConstID_VIntegerMaxValue	(0x7fffffffffffffff)
		#define PLSys_ConstID_VIntegerMinValue	(~(0x7ffffffffffffffe))
		// this is define 64 bit cpu mode
	#endif
	//if define IDESetPrjExport at Engine Compiler Mode
	//if nodefine IDESetPrjExport or Other at use Engine Mode
	#ifdef IDESetPrjExport
		//class export define tag
		#define _PLE_lib_class    _export_lib_class
		//class not export define tag
		#define _PLE_lib_classNV  _noexprot_lib_class
		//function export define tag
		#define _PLE_lib_c        _export_lib_c
		//function not export define tag
		#define _PLE_lib_cNV      _noexprot_lib_c
		//variable export define tag
		#define _PLE_lib_Variable _export_lib_variable

		#define _PLE_lib_VariableDup _export_lib_variableDup

		#define _PLE_lib_VariableN   _export_lib_variableNormal
		//variable not export define tag
		#define _PLE_lib_VariableNV _noexport_lib_variablenormal
	#else
		//class import define tag
		#define _PLE_lib_class    _import_lib_class
		//class must not import define tag
		#define _PLE_lib_classNV
		//function import define tag
		#define _PLE_lib_c        _import_lib_c
		//function must not import define tag
		#define _PLE_lib_cNV
		//variable import define tag
		#define _PLE_lib_Variable _import_lib_variable

		#define _PLE_lib_VariableDup _import_lib_variableDup

		#define _PLE_lib_VariableN _import_lib_variableNormal
		//variable must not import define tag
		#define _PLE_lib_VariableNV
	#endif

	#define _SysText(chr) (L##chr)
//	typedef PL_BeginByteAligned_CompilerDefine   #pragma pack
	#define PL_Sizeof PL_CompilerAllocSize
	#define _CallStack_default_ _CallStack_stdcall
	typedef union _un_PLAddresVCompat {
		PAddress_pl __addres_pl;
		AddresValue_pl __addresvalue_pl;
	}AddresVCompat_pl;

#endif /* PLENGINEBASEDATATYPE_H_ */
