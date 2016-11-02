/*
 * PLEngineSysTextCharInface.h
 *
 *  Created on: 2010-5-7
 *      Author: wl
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineH.h"
#ifndef PLENGINESYSTEXTCHARINFACE_H_
#define PLENGINESYSTEXTCHARINFACE_H_
	#define UTF8char_pl  uchar_pl
	#define UTF16char_pl tchar2_pl
	#define UTF32char_pl tchar4_pl

	#if PLESystem_CharCodeUXX == PLEngineSysChar_Unicode16
		#define UTFSyschar_pl UTF16char_pl
	#else
		#define UTFSyschar_pl UTF16char_pl
	#endif

	//UnicodeMark
	#define PLSysIO_Const_UnicodeMark_SmallEnd         1
	#define PLSysIO_Const_UnicodeMark_ConverEndChar	 0x80000000

	#define PLSysIO_Const_ReadDataCacheSize (1<<10)

	typedef enum _ePL_CharCodeStyle{
		PLSys_Const_Unicode8 = 0,
		PLSys_Const_Unicode16,
		PLSys_Const_Unicode32
	}ePL_CharCodeStyle;

	#define PLSysChar_Const_UTF8MarkSize     3
	#define PLSysChar_Const_UTF16MarkSize    1
	#define PLSysChar_Const_UTF32MarkSize    1
	#define PLSysChar_Const_SysStringMarkSize PLSysChar_Const_UTF16MarkSize



	const_pl UTF8char_pl  PUTF8IOMark[PLSysChar_Const_UTF8MarkSize + 1]={0xef,0xbb,0xbf,0x00};
	const_pl UTF16char_pl PUTF16IOMark[PLSysChar_Const_UTF16MarkSize+1]={0xfeff,0x00};
	const_pl UTF32char_pl PUTF32IOMark[PLSysChar_Const_UTF32MarkSize+1]={0xfeff,0x00};
	#define PSysStringIOMark PUTF16IOMark


#pragma pack(4)
	const_pl UTF16char_pl g_PLConstAnisTableUTF16[] = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30, 						 \
		31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,  				 \
		61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,  				 \
		91,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120, \
		121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150, \
		151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180, \
		181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210, \
		211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240, \
		241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
	};
	const_pl UTF32char_pl g_PLConstAnisTableUTF32[] = {
			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30, 						 \
			31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,  				 \
			61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,  				 \
			91,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120, \
			121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150, \
			151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180, \
			181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210, \
			211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240, \
			241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
		};
#pragma pack()
	#define _SysAnsiChar(c)   c
	#define _SysUTF8Char(c)  ((UTF8char_pl)_SysAnsiChar(c))
	#define _SysUTF16Char(c) (g_PLConstAnisTableUTF16[((intV_pl)c)])
	#define _SysUTF32Char(c) (g_PLConstAnisTableUTF32[((intV_pl)c)])

/*
 *	define  base char of System code
 * */
	#define PLWChar_SlashHL						_SysText('\\')
	#define PLWChar_SlashLH                  	_SysText('/')
	#define PLWChar_MBracketL					_SysText('[')
	#define PLWChar_MBracketR					_SysText(']')
	#define PLWChar_BBracketL                 	_SysText('{')
	#define PLWChar_BBracketR					_SysText('}')
	#define PLWChar_SBracketL					_SysText('(')
	#define PLWChar_SBracketR					_SysText(')')
	#define PLWChar_OR							_SysText('|')
	#define PLWChar_AND							_SysText('&')
	#define PLWChar_Reverse						_SysText('~')
	#define PLWChar_Underline					_SysText('_')
	#define PLWChar_Equal 						_SysText('=')
	#define PLWChar_DbQuotation 				_SysText('"')
	#define PLWChar_SQuotation					_SysText('\'')
	#define PLWChar_Add 						_SysText('+')
	#define PLWChar_Sub							_SysText('-')
	#define PLWChar_Mul							_SysText('*')
	#define PLWChar_Percent						_SysText('%')
	#define PLWChar_WellMark					_SysText('#')
	#define PLWChar_AinPen						_SysText('@')
	#define PLWChar_Low							_SysText('<')
	#define PLWChar_Great						_SysText('>')
	#define PLWChar_Comma					  	_SysText(',')
	#define PLWChar_Point						_SysText('.')
	#define PLWChar_Question					_SysText('?')
	#define PLWChar_1                         	_SysText('1')
	#define PLWChar_2                         	_SysText('2')
	#define PLWChar_3                         	_SysText('3')
	#define PLWChar_4                         	_SysText('4')
	#define PLWChar_5                         	_SysText('5')
	#define PLWChar_6                         	_SysText('6')
	#define PLWChar_7                         	_SysText('7')
	#define PLWChar_8                         	_SysText('8')
	#define PLWChar_9                         	_SysText('9')
	#define PLWChar_NewLine						(0xa)
	#define PLWChar_SoftEnter	   				(0xd)
	#define PLWChar_Tab      					(0x9)
	#define PLWChar_Blank 						(0x20)


	#define PLSysChar_SlashHL					PLWChar_SlashHL
	#define PLSysChar_SlashLH                   PLWChar_SlashLH
	#define PLSysChar_MBracketL					PLWChar_MBracketL
	#define PLSysChar_MBracketR					PLWChar_MBracketR
	#define PLSysChar_BBracketL                 PLWChar_BBracketL
	#define PLSysChar_BBracketR					PLWChar_BBracketL
	#define PLSysChar_SBracketL					PLWChar_BBracketL
	#define PLSysChar_SBracketR					PLWChar_BBracketL
	#define PLSysChar_OR						PLWChar_BBracketL
	#define PLSysChar_AND						PLWChar_BBracketL
	#define PLSysChar_Reverse					PLWChar_BBracketL
	#define PLSysChar_Underline					PLWChar_BBracketL
	#define PLSysChar_Equal 					PLWChar_BBracketL
	#define PLSysChar_DbQuotation 				PLWChar_BBracketL
	#define PLSysChar_SQuotation				PLWChar_BBracketL
	#define PLSysChar_Add 						PLWChar_BBracketL
	#define PLSysChar_Sub						PLWChar_BBracketL
	#define PLSysChar_Mul						PLWChar_BBracketL
	#define PLSysChar_Percent					PLWChar_BBracketL
	#define PLSysChar_WellMark					PLWChar_BBracketL
	#define PLSysChar_AinPen					PLWChar_BBracketL
	#define PLSysChar_Low						PLWChar_BBracketL
	#define PLSysChar_Great						PLWChar_BBracketL
	#define PLSysChar_Comma						PLWChar_BBracketL
	#define PLSysChar_Point						PLWChar_BBracketL
	#define PLSysChar_Question					PLWChar_BBracketL
	#define PLSysChar_1                         PLWChar_BBracketL
	#define PLSysChar_2                         PLWChar_BBracketL
	#define PLSysChar_3                         PLWChar_BBracketL
	#define PLSysChar_4                         PLWChar_BBracketL
	#define PLSysChar_5                         PLWChar_BBracketL
	#define PLSysChar_6                         PLWChar_BBracketL
	#define PLSysChar_7                         PLWChar_BBracketL
	#define PLSysChar_8                         PLWChar_BBracketL
	#define PLSysChar_9                         PLWChar_BBracketL
	#define PLSysChar_NewLine					PLWChar_BBracketL
	#define PLSysChar_SoftEnter	   				PLWChar_BBracketL
	#define PLSysChar_Tab      					PLWChar_BBracketL
	#define PLSysChar_Blank 					PLWChar_BBracketL



#endif /* PLENGINESYSTEXTCHARINFACE_H_ */
