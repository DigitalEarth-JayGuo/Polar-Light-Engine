/*
 * PLEngineResultVD.h
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "PLEngineBaseDataType.h"
#ifndef PLENGINERESULTVD_H_
#define PLENGINERESULTVD_H_
	#define HPL_Result uintV_pl

	#define HPL_Result_Fail_Tag Define_UNSIGNED_Const(1)
	#define HPL_Result_OK_Tag   Define_UNSIGNED_Const(0)

	#define HPLResult_Type_Mark   Define_UNSIGNED_Const(0xff0000)
	#define HPLResult_Active_Mark Define_UNSIGNED_Const(0xf00)
	#define HPLResult_ID_Mark     Define_UNSIGNED_Const(0xff)
	#define HPLResult_Complete_Mark Define_UNSIGNED_Const(1<<31)
	//Result value application mark
	#define HPLResult_DefineApplication_Mark Define_UNSIGNED_Const(0x000f000)
		//user define application
		#define HPL_Result_UserDefine_Application Define_UNSIGNED_Const(0xf)
		//system define application
		#define HPL_Result_SystemDefine_Application   		Define_UNSIGNED_Const(0x00)
			#define HPL_Result_Type_Paramer 				 		Define_UNSIGNED_Const(0)
				#define HPL_Result_NULL_Tag  				 		Define_UNSIGNED_Const(0)
			#define HPL_Result_Type_HandleObject	    		Define_UNSIGNED_Const(1)
				#define HPL_Result_NotExist_Tag  		 		Define_UNSIGNED_Const(1)
			#define HPL_Result_Type_IO 					 		Define_UNSIGNED_Const(2)
				#define HPL_Active_Create Define_UNSIGNED_Const(0)
					#define HPL_Result_Paramer 			 		Define_UNSIGNED_Const(1)
					#define HPL_Result_NotAccessLevel 	 		Define_UNSIGNED_Const(3)
				#define HPL_Active_Read   Define_UNSIGNED_Const(1)
					#define HPL_Result_IO_EOF            		Define_UNSIGNED_Const(1)
				#define HPL_Active_Write  Define_UNSIGNED_Const(2)
				#define HPL_Active_Access Define_UNSIGNED_Const(3)
					#define HPL_Result_IO_HandleNULL         	Define_UNSIGNED_Const(3)
					#define HPL_Result_IO_PathNameError      	Define_UNSIGNED_Const(4)
					#define HPL_Result_IO_ModeError          	Define_UNSIGNED_Const(5)
					#define HPL_Result_IO_IOError            	Define_UNSIGNED_Const(6)
					#define HPL_Result_IO_NoDirectory        	Define_UNSIGNED_Const(7)
					#define HPL_Result_IO_FileSystemReadOnly 	Define_UNSIGNED_Const(8)
					#define HPL_Result_IO_TimerOut		 	  	Define_UNSIGNED_Const(1)
				#define HPL_Result_Unkown Define_UNSIGNED_Const(0)
			#define HPL_Result_Type_Synchron 			Define_UNSIGNED_Const(5)
				#define HPL_Result_TimerOut_Tag 			Define_UNSIGNED_Const(1)
				#define HPL_Result_UnInited_Tag 			Define_UNSIGNED_Const(2)
				#define HPL_Result_NotExistObject_Tag	Define_UNSIGNED_Const(3)
				#define HPL_Result_BlockFail_Tag			Define_UNSIGNED_Const(4)
			#define HPL_Result_Type_Net 			 	 Define_UNSIGNED_Const(6)
				//#define HPL_Result_Net_TimerOut				Define_UNSIGNED_Const(1)
			//string encode result value
			#define HPL_Result_Type_CharCode			 Define_UNSIGNED_Const(7)
				#define HPL_Active_Conver Define_UNSIGNED_Const(0)
					#define	HPL_Result_CharCode_SourceStrTypeError  Define_UNSIGNED_Const(0)
					#define  HPL_Result_CharCode_BufTooShortError    Define_UNSIGNED_Const(1)
					#define  HPL_Result_CharCode_StrTrun				 Define_UNSIGNED_Const(2)
					//#define  HPL_Result_CharCode_
					//#define  HPL_
//				#define HPL_Active_Conver Define_UNSIGNED_Const(0)
//				#define HPL_Active_Conver Define_UNSIGNED_Const(0)
//

	//marco comb result value
	#define HPL_Result_Type_Define(ok,app,type,active,id) ((ok<<31 & HPLResult_Complete_Mark) | ((app<<12) & HPLResult_DefineApplication_Mark) | ((type <<16) & HPLResult_Type_Mark) | ((active << 8) & HPLResult_Active_Mark) | (id & HPLResult_ID_Mark))

	//Result value is ok
	#define HPLResult_OK   HPL_Result_Type_Define(HPL_Result_OK_Tag,0,0,0,0)
	//Result value is failed
	#define HPLResult_Fail HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,0,0,0)

	//function judge result value is failed
	#define HResulPL_FAILED(v)  ((v & HPLResult_Complete_Mark)==HPLResult_Fail ? true_pl : false_pl)
	#define HResulPL_SUCCESS(v) ((v & HPLResult_Complete_Mark)==HPLResult_Fail ? false_pl : true_pl)
	//get result application pos
	#define GetHResulPLDefineAppValue(v) ((v & HPLResult_DefineApplication_Mark)>>12)

	/*Paramer Data is NULL*/
	#define HPLResultF_Paramer_NULL  HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_Paramer,0,HPL_Result_NULL_Tag)
	/**/
	#define HPLResult_Lock_TimerOut  HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_Synchron,0,HPL_Result_TimerOut_Tag)
	#define HPLResult_Lock_UnInited  HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_Synchron,0,HPL_Result_UnInited_Tag)
	#define HPLResult_Lock_NotExist  HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_Synchron,0,HPL_Result_NotExistObject_Tag)
	#define HPLResult_Lock_BlockFail HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_Synchron,0,HPL_Result_BlockFail_Tag)

	/**/
	#define HPLResultF_IO_CreateFailed HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Create,HPL_Result_Unkown)
	/**/
	#define HPLResultK_IO_CreateOK     HPL_Result_Type_Define(HPL_Result_OK_Tag,0,HPL_Result_Type_IO,HPL_Active_Create,HPL_Result_Unkown)
	/**/
	#define HPLResultF_IO_ReadFailed   HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Read,HPL_Result_Unkown)
	/**/
	#define HPLResultF_IO_WriteFailed  HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Write,HPL_Result_Unkown)
	/*Paramer is Error*/
	#define HPLResultF_IO_CPError      HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Create,HPL_Result_Paramer)
	/**/
	#define HPLResultF_IO_AccessFailed HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_Unkown)
	/**/
	#define HPLResultF_IO_HandleNULL   HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_IO_HandleNULL)
	/*PathName Paramer Error */
	#define HPLResultF_IO_PathNameError HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_IO_PathNameError)
	/*Check Mode Paramer Error*/
	#define HPLResultF_IO_ModeError     HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_IO_ModeError)
	/* IO Error*/
	#define HPLResultF_IO_IOError       HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_IO_IOError)
	/*paramer Description is Directory but is not Directory*/
	#define HPLResultF_IO_NoDirectory    HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_IO_NoDirectory)
	/*FileSystem ReadOnly*/
	#define HPLResultF_IO_ReadOnly       HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_IO_FileSystemReadOnly)
	/*file end*/
	#define HPLResultK_IO_EOF            HPL_Result_Type_Define(HPL_Result_OK_Tag,0,HPL_Result_Type_IO,HPL_Active_Read,HPL_Result_IO_EOF)
	/*No Access Level*/
	#define HPLResultF_IO_NotAccessLevel HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Read,HPL_Result_NotAccessLevel)
	/*I/O Out Timer*/
	#define HPLResultF_IO_IOTimerOut	    HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Active_Access,HPL_Result_IO_TimerOut)

	/*String Trun*/
	#define HPLResultK_CharCode_StrTrun 			HPL_Result_Type_Define(HPL_Result_OK_Tag,0,HPL_Result_Type_CharCode,HPL_Active_Conver,HPL_Result_CharCode_StrTrun)
	/*Char enCode type error*/
	#define HPLResultF_CharCode_StrType				HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_CharCode,HPL_Active_Conver,HPL_Result_CharCode_SourceStrTypeError)
	/*buffer size too short*/
	#define HPLResultF_CharCode_BufferTooShort	HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_CharCode,HPL_Active_Conver,HPL_Result_CharCode_BufTooShortError)


//	#define HPLResultF_CharCode_BufferTooShort	HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_CharCode,HPL_Active_Star,HPL_Result_CharCode_BufTooShortError)


//	#define PL

//	#define HPLResult_IO_CreateFailed HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Result_Read)
//	#define HPLResult_IO_CreateFailed HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Result_Write)
//	#define HPLResult_IO_DeviceEndFailed HPL_Result_Type_Define(HPL_Result_Fail_Tag,0,HPL_Result_Type_IO,HPL_Result_End)

#endif /* PLENGINERESULTVD_H_ */
