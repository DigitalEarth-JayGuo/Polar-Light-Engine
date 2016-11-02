/*
 * PLEngineSysTextChar.h
 *
 *  Created on: 2010-4-29
 *      Author: wl
 */
#include "PLEngineBaseH.h"
#include "PLEngineSysAPI.h"
#include "PLEngineDefine.h"
#include "PLEngineInface.h"
#ifndef PLENGINESYSTEXTCHAR_H_
#define PLENGINESYSTEXTCHAR_H_
	/***********************************
	 * Multibyte Code Conver
	 ***********************************/
	/**System default use Unicode16 small end (0xff ,0xfe) **/
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_UT8toUT16_(const_pl UTF8char_pl * ptrUT8,intV_pl iUT8Size,intV_pl * ptriDataPos,UTF16char_pl * ptrUT16,intV_pl * ptriUT16Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_UT8toUT32_(const_pl UTF8char_pl * ptrUT8,intV_pl iUT8Size,intV_pl * ptriDataPos,UTF32char_pl * ptrUT32,intV_pl * ptriUT32Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_UT16toUT8_(const_pl UTF16char_pl * ptrUT16,intV_pl iUT16Size,intV_pl * ptriDataPos,UTF8char_pl * ptrUT8,intV_pl * ptriUT8Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_UT16toUT32_(const_pl UTF16char_pl * ptrUT16,intV_pl iUT16Size,intV_pl * ptriDataPos,UTF32char_pl * ptrUT32,intV_pl * ptriUT32Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_UT32toUT8_(const_pl UTF32char_pl * ptrUT32,intV_pl iUT32Size,intV_pl * ptriDataPos,UTF8char_pl * ptrUT8,intV_pl * ptriUT8Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_UT32toUT16_(const_pl UTF32char_pl * ptrUT32,intV_pl iUT32Size,intV_pl * ptriDataPos,UTF16char_pl * ptrUT16,intV_pl * ptriUT16Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_SystemIO_isLegalUTF8_(const_pl void_pl * ptrUT8,intV_pl iBMaxLength);


	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Ansi_findMarkChar(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Ansi_findMarkCharR(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Ansi_findMarkString(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl * ptrMark,intV_pl iMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Ansi_findMarkStringR(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl * ptrMark,intV_pl iMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Ansi_StrCpy(char_pl * ptrD,const_pl char_pl * ptrS,intV_pl iwCpySize);
	_PLE_lib_c _CallStack_default_ bool_pl    __PLSysAPI_Ansi_StrCmp(const_pl char_pl * ptrStr1,const_pl char_pl * ptrStr2,intV_pl iwSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Ansi_StringSize(const_pl char_pl * ptrStr,intV_pl iMaxSize);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_Ansi_StringStarCharSize(const_pl char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag);
	_PLE_lib_c _CallStack_default_ intV_pl      PLSysAPI_TypeConverAnsi_atoi(const_pl char_pl * ptrValue,intV_pl iSize);
	_PLE_lib_c _CallStack_default_ float_pl     PLSysAPI_TypeConverAnsi_atof(const_pl char_pl * ptrValue,intV_pl iSize);

	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode8_findMarkChar(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode8_findMarkCharR(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode8_findMarkString(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl * ptrMark,intV_pl iwMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode8_findMarkStringR(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl * ptrMark,intV_pl iwMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode8_StrCpy(UTF8char_pl * ptrD,const_pl UTF8char_pl * ptrS,intV_pl iwCpySize);
	_PLE_lib_c _CallStack_default_ bool_pl    __PLSysAPI_Unicode8_StrCmp(const_pl UTF8char_pl * ptrStr1,const_pl UTF8char_pl * ptrStr2,intV_pl iwSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode8_StringSize(const_pl UTF8char_pl * ptrStr,intV_pl iMaxSize);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_Unicode8_StringStarCharSize(const_pl UTF8char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag);
	_PLE_lib_c _CallStack_default_ intV_pl      PLSysAPI_TypeConverUTF8_atoi(const_pl UTF8char_pl * ptrValue,intV_pl iSize);
	_PLE_lib_c _CallStack_default_ float_pl     PLSysAPI_TypeConverUTF8_atof(const_pl UTF8char_pl * ptrValue,intV_pl iSize);

	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode16_findMarkChar(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode16_findMarkCharR(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode16_findMarkString(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl * ptrMark,intV_pl iwMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode16_findMarkStringR(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl * ptrMark,intV_pl iwMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode16_StrCpy(UTF16char_pl * ptrD,const_pl UTF16char_pl * ptrS,intV_pl iwCpySize);
	_PLE_lib_c _CallStack_default_ bool_pl    __PLSysAPI_Unicode16_StrCmp(const_pl UTF16char_pl * ptrStr1,const_pl UTF16char_pl * ptrStr2,intV_pl iwSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode16_StringSize(const_pl UTF16char_pl * ptrStr,intV_pl iMaxSize);
	//real char count
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_Unicode16_StringStarCharSize(const_pl UTF16char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag);
	_PLE_lib_c _CallStack_default_ intV_pl      PLSysAPI_TypeConverUTF16_atoi(const_pl UTF16char_pl * ptrValue,intV_pl iwSize);
	_PLE_lib_c _CallStack_default_ float_pl     PLSysAPI_TypeConverUTF16_atof(const_pl UTF16char_pl * ptrValue,intV_pl iwSize);


	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode32_findMarkChar(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode32_findMarkCharR(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl cChar);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode32_findMarkString(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl * ptrMark,intV_pl iwMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode32_findMarkStringR(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl * ptrMark,intV_pl iwMarkSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode32_StrCpy(UTF32char_pl * ptrD,const_pl UTF32char_pl * ptrS,intV_pl iwCpySize);
	_PLE_lib_c _CallStack_default_ bool_pl    __PLSysAPI_Unicode32_StrCmp(const_pl UTF32char_pl * ptrStr1,const_pl UTF32char_pl * ptrStr2,intV_pl iwSize);
	_PLE_lib_c _CallStack_default_ intV_pl    __PLSysAPI_Unicode32_StringSize(const_pl UTF32char_pl * ptrStr,intV_pl iMaxSize);
	_PLE_lib_c _CallStack_default_ HPL_Result __PLSysAPI_Unicode32_StringStarCharSize(const_pl UTF32char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag);
	_PLE_lib_c _CallStack_default_ intV_pl      PLSysAPI_TypeConverUTF32_atoi(const_pl UTF32char_pl * ptrValue,intV_pl iwSize);
	_PLE_lib_c _CallStack_default_ float_pl     PLSysAPI_TypeConverUTF32_atof(const_pl UTF32char_pl * ptrValue,intV_pl iwSize);



	typedef _CallStack_default_ HPL_Result (* __PLSysAPI_SystemIO_UT8toUT16__Enter)    (const_pl UTF8char_pl *,intV_pl,intV_pl *,UTF16char_pl *,intV_pl *,intV_pl *,int_pl,uintV_pl *);
	typedef _CallStack_default_ HPL_Result (* __PLSysAPI_SystemIO_UT8toUT32__Enter)    (const_pl UTF8char_pl *,intV_pl,intV_pl *,UTF32char_pl *,intV_pl *,intV_pl *,int_pl,uintV_pl *);
	typedef _CallStack_default_ HPL_Result (* __PLSysAPI_SystemIO_UT16toUT8__Enter)    (const_pl UTF16char_pl *,intV_pl,intV_pl *,UTF8char_pl *,intV_pl *,intV_pl *,int_pl,uintV_pl *);
	typedef _CallStack_default_ HPL_Result (* __PLSysAPI_SystemIO_UT16toUT32__Enter)   (const_pl UTF16char_pl *,intV_pl,intV_pl *,UTF32char_pl *,intV_pl *,intV_pl *,int_pl,uintV_pl *);
	typedef _CallStack_default_ HPL_Result (* __PLSysAPI_SystemIO_UT32toUT8__Enter)    (const_pl UTF32char_pl *,intV_pl,intV_pl *,UTF8char_pl *,intV_pl *,intV_pl *,int_pl,uintV_pl *);
	typedef _CallStack_default_ HPL_Result (* __PLSysAPI_SystemIO_UT32toUT16__Enter)   (const_pl UTF32char_pl *,intV_pl,intV_pl *,UTF16char_pl *,intV_pl *,intV_pl *,int_pl,uintV_pl *);
/*
	typedef _CallStack_default_ int_pl     (* __PLSysAPI_Ansi_findMarkChar__Enter) 	   (const_pl char_pl *,intV_pl,char_pl);
	typedef _CallStack_default_ int_pl     (* __PLSysAPI_Ansi_findMarkCharR__Enter)    (const_pl char_pl *,intV_pl,char_pl);
	typedef _CallStack_default_ int_pl     (* __PLSysAPI_Ansi_findMarkString__Enter)   (const_pl char_pl *,intV_pl,const_pl char_pl *,intV_pl);
	typedef _CallStack_default_ int_pl     (* __PLSysAPI_Ansi_findMarkStringR__Enter)  (const_pl char_pl *,intV_pl,const_pl char_pl *,intV_pl);
*/


	#define PLSysAPI_SysIO_UTF8toUTF16          __PLSysAPI_SystemIO_UT8toUT16_
	#define PLSysAPI_SysIO_UTF8toUTF32          __PLSysAPI_SystemIO_UT8toUT32_
	#define PLSysAPI_SysIO_UTF16toUTF8          __PLSysAPI_SystemIO_UT16toUT8_
	#define PLSysAPI_SysIO_UTF16toUTF32         __PLSysAPI_SystemIO_UT16toUT32_
	#define PLSysAPI_SysIO_UTF32toUTF8          __PLSysAPI_SystemIO_UT32toUT8_
	#define PLSysAPI_SysIO_UTF32toUTF16         __PLSysAPI_SystemIO_UT32toUT16_

	#define PLSysAPI_Ansi_findMarkChar			  __PLSysAPI_Ansi_findMarkChar
	#define PLSysAPI_Ansi_findMarkCharR			  __PLSysAPI_Ansi_findMarkCharR
	#define PLSysAPI_Ansi_findMarkString		  __PLSysAPI_Ansi_findMarkString
	#define PLSysAPI_Ansi_findMarkStringR		  __PLSysAPI_Ansi_findMarkStringR


	#define PLSysAPI_UTF8_findMarkChar				__PLSysAPI_Unicode8_findMarkChar
	#define PLSysAPI_UTF8_findMarkCharR				__PLSysAPI_Unicode8_findMarkCharR
	#define PLSysAPI_UTF8_findMarkString			__PLSysAPI_Unicode8_findMarkString
	#define PLSysAPI_UTF8_findMarkStringR			__PLSysAPI_Unicode8_findMarkStringR
	#define PLSysAPI_UTF8_StrCpy						__PLSysAPI_Unicode8_StrCpy
	#define PLSysAPI_UTF8_StrCmp						__PLSysAPI_Unicode8_StrCmp
	#define PLSysAPI_UTF8_ConstStringSize(p)  	((PL_CompilerAllocSize(p))-1)
	#define PLSysAPI_UTF8_StringSize(p)				__PLSysAPI_Unicode8_StringSize(p,0)
	#define PLSysAPI_UTF8_StringStarCharSize		__PLSysAPI_Unicode8_StringStarCharSize
	#define PLSysAPI_UTF8_ClearString(p,tsize)	PLSysAPI_MemoryClearZero(p,(tsize))
	#define PLSysAPI_UTF8_CharByteSize			1
	#define PLSysAPI_UTF8_Byte2CharUnit(s)    	(s)
	#define PLSysAPI_UTF8_CharSize2ByteSize(s)  (s)

	#define PLSysAPI_UTF16_findMarkChar				__PLSysAPI_Unicode16_findMarkChar
	#define PLSysAPI_UTF16_findMarkCharR			__PLSysAPI_Unicode16_findMarkCharR
	#define PLSysAPI_UTF16_findMarkString			__PLSysAPI_Unicode16_findMarkString
	#define PLSysAPI_UTF16_findMarkStringR			__PLSysAPI_Unicode16_findMarkStringR
	#define PLSysAPI_UTF16_StrCpy					__PLSysAPI_Unicode16_StrCpy
	#define PLSysAPI_UTF16_StrCmp					__PLSysAPI_Unicode16_StrCmp
	#define PLSysAPI_UTF16_ConstStringSize(p) 		(((PL_CompilerAllocSize(p)) >> 1)-1)
	#define PLSysAPI_UTF16_StringSize(p)			__PLSysAPI_Unicode16_StringSize(p,0)
	#define PLSysAPI_UTF16_StringStarCharSize		__PLSysAPI_Unicode16_StringStarCharSize
	#define PLSysAPI_UTF16_ClearString(p,tsize)		PLSysAPI_MemoryClearZero(p,(tsize<<1))
	#define PLSysAPI_UTF16_CharByteSize				2
	#define PLSysAPI_UTF16_Byte2CharUnit(s)    		(s>>1)
	#define PLSysAPI_UTF16_CharSize2ByteSize(s)  	(s<<1)

	#define PLSysAPI_UTF32_findMarkChar				__PLSysAPI_Unicode32_findMarkChar
	#define PLSysAPI_UTF32_findMarkCharR			__PLSysAPI_Unicode32_findMarkCharR
	#define PLSysAPI_UTF32_findMarkString			__PLSysAPI_Unicode32_findMarkString
	#define PLSysAPI_UTF32_findMarkStringR			__PLSysAPI_Unicode32_findMarkStringR
	#define PLSysAPI_UTF32_StrCpy					__PLSysAPI_Unicode32_StrCpy
	#define PLSysAPI_UTF32_StrCmp					__PLSysAPI_Unicode32_StrCmp
	#define PLSysAPI_UTF32_ConstStringSize(p) 		((PL_CompilerAllocSize(p)) >> 2)-1)
	#define PLSysAPI_UTF32_StringSize(p)			__PLSysAPI_Unicode32_StringSize(p,0)
	#define PLSysAPI_UTF32_StringStarCharSize		__PLSysAPI_Unicode32_StringStarCharSize
	#define PLSysAPI_UTF32_ClearString(p,tsize)		PLSysAPI_MemoryClearZero(p,(tsize<<2))
	#define PLSysAPI_UTF32_CharByteSize				4
	#define PLSysAPI_UTF32_Byte2CharUnit(s)    		(s>>2)
	#define PLSysAPI_UTF32_CharSize2ByteSize(s)  	(s<<2)

	#define PLSysAPI_ConverAnsiChar								_SysAnsiChar
	#define PLSysAPI_ConverUTF8Char								_SysUTF8Char
	#define PLSysAPI_ConverUTF16Char							_SysUTF16Char
	#define PLSysAPI_ConverUTF32Char							_SysUTF32Char


	#define PLSysAPI_SysStringCpy 								PLSysAPI_UTF16_StrCpy
	#define PLSysAPI_SysStringCmp								PLSysAPI_UTF16_StrCmp
	//const string
	#define PLSysAPI_SysConstStringSize		 					PLSysAPI_UTF16_ConstStringSize
	//dynamic allocate string
	#define PLSysAPI_SysStringSize	  							PLSysAPI_UTF16_StringSize
	//real char count
	#define PLSysAPI_SysStringStarCharSize						PLSysAPI_UTF16_StringStarCharSize
	#define PLSysAPI_SysStringClear			 					PLSysAPI_UTF16_ClearString
	#define PLSysAPI_SysCharAllocSize() 						PLSysAPI_UTF16_CharByteSize
	#define PLSysAPI_SysByte2CharUnit 							PLSysAPI_UTF16_Byte2CharUnit
	#define PLSysAPI_SysCharSize2ByteSize						PLSysAPI_UTF16_CharSize2ByteSize
	#define PLSysAPI_SysTypeConverAtoi							PLSysAPI_TypeConverUTF16_atoi
	#define PLSysAPI_SysTypeConverAtof							PLSysAPI_TypeConverUTF16_atof
	#define PLSysAPI_SysString_findMarkChar						PLSysAPI_UTF16_findMarkChar
	#define PLSysAPI_SysString_findMarkCharR					PLSysAPI_UTF16_findMarkCharR
	#define PLSysAPI_SysString_findMarkString					PLSysAPI_UTF16_findMarkString
	#define PLSysAPI_SysString_findMarkStringR					PLSysAPI_UTF16_findMarkStringR

	#define PLSysAPI_ConverUTFSysChar							_SysUTF16Char
#endif /* PLENGINESYSTEXTCHAR_H_ */
