/*
 * PLEngineSysIOInface.h
 *
 *  Created on: 2009-8-4
 *      Author: Administrator
 */
#include "PLEngineBaseH.h"
#include "PLEngineSysDataMacro.h"

#ifndef PLENGINESYSIOINFACE_H_
#define PLENGINESYSIOINFACE_H_

	#define HPPLEngine PAddress_pl
	#if PLCPU_IAXX == PLCPU_IA32
		#define FILEStream FILE

		#define fopenXX   fopen
		#define freadXX   fread
		#define fwriteXX  fwrite
		#define fseekXX   fseek
		#define ftellXX   ftell
		#define fcloseXX  fclose
		#define fflushXX  fflush
		#define feofXX    feof
		#define atoiXX    atoi
		#define atofXX    atof
	#elif  PLCPU_IAXX == PLCPU_IA64
		#define FILEStream FILE64

		#define fopenXX   fopen64
		#define freadXX   fread64
		#define fwriteXX  fwrite64
		#define fseekXX   fseek64
		#define ftellXX   ftell64
		#define fcloseXX  fclose64
		#define fflushXX  fflush64
		#define feofXX    feof64
		#define atoiXX    atoi64
		#define atofXX    atof64
	#endif
	#define PLSysIO_Const_TextLineMaxLength 1024

#pragma pack(8)
	typedef  struct Aligned(8) _PLDevice_SysIO_St{
		uint_pl uFD;
		_Syn_TSpinLock lock;
	}__Aligned(8) PLDeviceSysIOSt;
	#define PLDeviceHandle PLDeviceSysIOSt *
#pragma pack()


	//File seek Mode Default
	typedef enum _ePL_SysIOSeekMode{
		PLSys_Const_SystemIO_Seek_Set = 0,
		PLSys_Const_SystemIO_Seek_CUR ,
		PLSys_Const_SystemIO_Seek_END
	}ePL_SysIOSeekMode;

	//Mode
	#define PLSysIO_Const_AccessMode_Create   	Define_UNSIGNED_Const(1<<0)
	#define PLSysIO_Const_AccessMode_Read 		Define_UNSIGNED_Const(1<<1)
	#define PLSysIO_Const_AccessMode_Write   	Define_UNSIGNED_Const(1<<2)
	#define PLSysIO_Const_AccessMode_Execute 	Define_UNSIGNED_Const(1<<3)
	//Open Flag
	#define PLSysIO_Const_OpenMode_OpenTreat_Mark 	Define_UNSIGNED_Const(7<<0)	  //(0bit ~ 2bit)
			#define PLSysIO_Const_OpenMode_Trunc    Define_UNSIGNED_Const(1<<0)	   // open file and Trunc file Data
	#define PLSysIO_Const_OpenMode_FT_Mark        	Define_UNSIGNED_Const(7<<3)    //(3bit ~ 5bit) FT = FileType
		#define PLSysIO_Const_OpenMode_File        	Define_UNSIGNED_Const(0<<3)    //File Open Mode Flag availability
	#define PLSysIO_Const_OpenMode_Creat_Mark     	Define_UNSIGNED_Const(7<<6)	 //(6bit ~ 8bit)
		#define PLSysIO_Const_OpenMode_NotCreat    	Define_UNSIGNED_Const(0<<6)	   //Not Create so OpenOnly
		#define PLSysIO_Const_OpenMode_Creat       	Define_UNSIGNED_Const(1<<6)     //CreatNew
		#define PLSysIO_Const_OpenMode_CreatAlways 	Define_UNSIGNED_Const(2<<6)     //Always Creat if File exist overlay
		#define PLSysIO_Const_OpenMode_OpenMust    	Define_UNSIGNED_Const(3<<6)     //Must Open if File exist overlay
	//(9bit ~ 10bit)
	#define PLSysIO_Const_ShareMode_Open_Mark          	Define_UNSIGNED_Const(3<<9)
		#define PLSysIO_Const_ShareMode_Read            Define_UNSIGNED_Const(1<<9)
		#define PLSysIO_Const_ShareMode_Write           Define_UNSIGNED_Const(2<<9)
		#define PLSysIO_Const_ShareMode_RW 				Define_UNSIGNED_Const(3<<9)
	//(11bit ~ 12bit)
	#define PLSysIO_Const_OpenOperat_Open_Mark          Define_UNSIGNED_Const(3<<11)
		#define PLSysIO_Const_OpenOperat_Read           Define_UNSIGNED_Const(1<<11)
		#define PLSysIO_Const_OpenOperat_Write          Define_UNSIGNED_Const(2<<11)
		#define PLSysIO_Const_OpenOperat_RW 			Define_UNSIGNED_Const(3<<11)
	// Attrib Mode
	#define PLSysIO_Const_Att_URead        Define_UNSIGNED_Const(1<<0)
	#define PLSysIO_Const_Att_UWrite       Define_UNSIGNED_Const(1<<1)
	#define PLSysIO_Const_Att_UExecute     Define_UNSIGNED_Const(1<<2)
	#define PLSysIO_Const_Att_UGRead       Define_UNSIGNED_Const(1<<3)
	#define PLSysIO_Const_Att_UGWrite  	   Define_UNSIGNED_Const(1<<4)
	#define PLSysIO_Const_Att_UGExecute    Define_UNSIGNED_Const(1<<5)
	#define PLSysIO_Const_Att_ORead        Define_UNSIGNED_Const(1<<6)
	#define PLSysIO_Const_Att_OWrite       Define_UNSIGNED_Const(1<<7)
	#define PLSysIO_Const_Att_OExecute     Define_UNSIGNED_Const(1<<8)


	#define __native_PLSysIO_Const_FOpenOMode_Read		 1
	#define __native_PLSysIO_Const_FOpenOMode_Write      (1<<1)
	#define __native_PLSysIO_Const_FOpenOMode_Bin		 (1<<2)
	#define __native_PLSysIO_Const_FOpenOMode_EndAdd	 (1<<3)

	#define PLSysIO_Const_FOpenOperat_Read  		__native_PLSysIO_Const_FOpenOMode_Read
	#define PLSysIO_Const_FOpenOperat_Write 		__native_PLSysIO_Const_FOpenOMode_Write
	#define PLSysIO_Const_FOpenOperat_RW 	 		(__native_PLSysIO_Const_FOpenOMode_Read | __native_PLSysIO_Const_FOpenOMode_Write)
	#define PLSysIO_Const_FOpenOperat_ReadBin 		(__native_PLSysIO_Const_FOpenOMode_Read | __native_PLSysIO_Const_FOpenOMode_Bin)
	#define PLSysIO_Const_FOpenOperat_WriteBin      (__native_PLSysIO_Const_FOpenOMode_Write | __native_PLSysIO_Const_FOpenOMode_Bin)
	#define PLSysIO_Const_FOpenOperat_RWBin	        (__native_PLSysIO_Const_FOpenOMode_Read | __native_PLSysIO_Const_FOpenOMode_Write | __native_PLSysIO_Const_FOpenOMode_Bin)
	#define PLSysIO_Const_FOpenOperat_WEAdd		    (__native_PLSysIO_Const_FOpenOMode_Write | __native_PLSysIO_Const_FOpenOMode_EndAdd)
	#define PLSysIO_Const_FOpenOperat_WBEAdd        (__native_PLSysIO_Const_FOpenOMode_Write | __native_PLSysIO_Const_FOpenOMode_Bin | __native_PLSysIO_Const_FOpenOMode_EndAdd)
	#define PLSysIO_Const_FOpenOperat_RWEndAdd      (__native_PLSysIO_Const_FOpenOMode_Read | __native_PLSysIO_Const_FOpenOMode_Write | __native_PLSysIO_Const_FOpenOMode_EndAdd)
	#define PLSysIO_Const_FOpenOperat_RWBEndAdd     (__native_PLSysIO_Const_FOpenOMode_Read | __native_PLSysIO_Const_FOpenOMode_Write | __native_PLSysIO_Const_FOpenOMode_Bin | __native_PLSysIO_Const_FOpenOMode_EndAdd)
	/*
	#define PLSysIO_Const_FOpenOperat_Read  		"r"
	#define PLSysIO_Const_FOpenOperat_Write 		"w"
	#define PLSysIO_Const_FOpenOperat_RW 	 		"w+"
	#define PLSysIO_Const_FOpenOperat_ReadBin 		"rb"
	#define PLSysIO_Const_FOpenOperat_WriteBin      "wb"
	#define PLSysIO_Const_FOpenOperat_RWBin	        "wb+"
	#define PLSysIO_Const_FOpenOperat_WEAdd		    "a"
	#define PLSysIO_Const_FOpenOperat_WBEAdd        "ab"
	#define PLSysIO_Const_FOpenOperat_RWEndAdd      "a+"
	#define PLSysIO_Const_FOpenOperat_RWBEndAdd     "ab+"
	*/

/*
 *	end define  base char of System code
 * */
#endif /* PLENGINESYSIOINFACE_H_ */
