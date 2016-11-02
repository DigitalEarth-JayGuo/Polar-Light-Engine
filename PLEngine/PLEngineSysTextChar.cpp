/*
 * PLEngineSysTextChar.cpp
 *
 *  Created on: 2010-4-29
 *      Author: wl
 */

#include "header/PLEngineSysTextChar.h"
	/*
	 * char ecode mode
	 *	UTF-8:  E4 BD A0　　　　　　　　11100100 10111101 10100000
	 *	Decomposition:  				xxxx0100 xx111101 xx100000
	 *	UTF-16: 4F 60　　　　　　　　   01001111 01100000
	 *	UTF-32: 4F 60 00 00             01001111 01100000 00000000 00000000
	 *	UTF16 Limit   UTF8
	 * 0000-007F    0xxxxxxx
	 * 0080-07FF    110xxxxx 10xxxxxx
	 * 0800-FFFF    1110xxxx 10xxxxxx 10xxxxxx
	 * utf-8 (ef bb bf)
	 * utf-16 (ff fe or fe ff) is BOM tag  (0xfffe big end and 0xfeff small end)
	 * */
	/*
	 * (*ptruFlag) 31 bit : 1 Conver end char,  0 not Conver end char
	 * */
	HPL_Result __PLSysAPI_SystemIO_UT8toUT16_(const_pl UTF8char_pl * ptrUT8,intV_pl iUT8Size,intV_pl * ptriDataPos,UTF16char_pl * ptrUT16,intV_pl * ptriUT16Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag){
		UTF32char_pl dChar;
		UTF32char_pl w8Char;
		intV_pl iUT16Pos;
		intV_pl iCharSize;
		intV_pl iBSize;
		uintV_pl uFlag;
		intV_pl iCount;
//		int_pl iShadowCount;
		if((ptriUT16Size==NULL_PL) || (ptriBSize==NULL_PL) || (ptruFlag==NULL_PL))
			return HPLResult_Fail;
		(*ptriUT16Size) = 0;
		(*ptriBSize)    = 0;
		if((iUT8Size<=0) || (iBMaxLength<=0) || (ptrUT8==NULL_PL) || (ptrUT16==NULL_PL))
			return HPLResult_Fail;
		iUT16Pos = 0;
		iBSize   = 0;
		iCharSize= 0;
		uFlag    = *ptruFlag;
		uFlag   |= PLSysIO_Const_UnicodeMark_SmallEnd;
		for(iCount=0;iCount<iUT8Size;iCount++){
			w8Char = ptrUT8[iCount];
			if((w8Char & 0x80)==0){
				dChar = w8Char;
			}else{
				//if double byte utf8 code
				if(((ptrUT8[iCount] & 0xe0)==0xc0) && ((iCount+1)<=iUT8Size)){
					w8Char = *((UTF16char_pl *)(&(ptrUT8[iCount])));

					if((w8Char & 0xc000) != 0x8000)
						break;
					dChar  = ((w8Char & 0x1f) << 6) | ((w8Char & 0x3f00) >> 8);
					iCount++;
				}//if three byte utf8 code 16 bit
				else if(((ptrUT8[iCount] & 0xf0)==0xe0) && ((iCount+2)<=iUT8Size)){
					dChar = (w8Char & 0x0f) << 12;
					iCount++;
					w8Char = *((UTF16char_pl *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0) != 0x8080){
						iCount--;
						break;
					}
					iCount+=1;
					//if utf8 char is EF,BB,BF , continue
					if((dChar==0xf000) && (w8Char ==0xbfbb) && ((uFlag & PLSysIO_Const_UnicodeMark_ConverEndChar)!=PLSysIO_Const_UnicodeMark_ConverEndChar))
						continue;
					dChar |= (((w8Char & 0x3f) << 6) | ((w8Char & 0x3f00) >> 8));
				}//if four byte utf8 code  21 bit
				else if(((ptrUT8[iCount] & 0xf8)==0xf0) && ((iCount+3)<=iUT8Size)){
					w8Char = *((UTF32char_pl *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c000) != 0x80808000){
						break;
					}
					iCount+=3;
					dChar = 0xd800 | ((w8Char & 3) << 8) | (w8Char & 0x3f00) >> 6 | ((w8Char &  0x300000) >> 2);
					dChar|= (0xdc000000 | ((w8Char & 0x0f0000) << 6) | ((w8Char & 0x3f000000) >> 8));
					if((iBSize+4)>iBMaxLength){
						iCount -=3;
						break;
					}
					*((UTF32char_pl *)(&(ptrUT16[iCharSize]))) = dChar;
					iBSize +=4;
					iCharSize +=2;
					iUT16Pos++;
					continue;
				}//if five byte utf8 code  26 bit
				else if(((ptrUT8[iCount] & 0xfc)==0xf8) && ((iCount+4)<=iUT8Size)){
					dChar = (w8Char & 3) << 24;
					w8Char = *((UTF32char_pl *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c0c0) != 0x80808080)
						break;
					iCount+=4;
					dChar |= (((w8Char & 0x3f)<<18) | ((w8Char & 0x3f00)<<4) | ((w8Char & 0x3f0000)>>10) | ((w8Char & 0x3f000000) >> 24));
					continue;
				}//not utf8 code limite
				else{
					break;
				}
			}
			if((iBSize + 2)>iBMaxLength)
				break;
			ptrUT16[iCharSize] = dChar;
			iUT16Pos +=1;
			iCharSize++;
			iBSize   +=2;
		}
		(*ptriUT16Size) = iUT16Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_UT8toUT32_(const_pl UTF8char_pl * ptrUT8,intV_pl iUT8Size,intV_pl * ptriDataPos,UTF32char_pl * ptrUT32,intV_pl * ptriUT32Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag){
		UTF32char_pl dChar;
		UTF32char_pl w8Char;
		intV_pl iUT32Pos;
		intV_pl iBSize;
		uintV_pl      uFlag;
		intV_pl iCount;
		if((ptriUT32Size==NULL_PL) || (ptriBSize==NULL_PL) || (ptruFlag==NULL_PL))
			return HPLResult_Fail;
		(*ptriUT32Size) = 0;
		(*ptriBSize)    = 0;
		if((ptrUT8 == NULL_PL) || (iUT8Size<=0) || (ptrUT32==NULL_PL) || (iBMaxLength<=0))
			return HPLResult_Fail;
		iUT32Pos = 0;
		iBSize   = 0;
		uFlag    = (*ptruFlag);
		uFlag   |= PLSysIO_Const_UnicodeMark_SmallEnd;
		for(iCount=0;iCount<iUT8Size;iCount++){
			w8Char = ptrUT8[iCount];
			if((w8Char & 0x80)==0){
				dChar = w8Char;
			}else{
				//if double byte utf8 code 11 bit
				if(((ptrUT8[iCount] & 0xe0)==0xc0) && ((iCount+1)<iUT8Size)){
					w8Char = *((UTF16char_pl *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc000) != 0x8000)
						break;
					dChar  = ((w8Char & 0x1f) << 6) | ((w8Char & 0x3f00) >> 8);
					iCount++;
				}//if three byte utf8 code 16 bit
				else if(((ptrUT8[iCount] & 0xf0)==0xe0) && ((iCount+2)<iUT8Size)){
					dChar = (w8Char & 0x0f) << 12;
					iCount+=1;
					w8Char = *((UTF16char_pl *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0) != 0x8080){
						iCount--;
						break;
					}
					iCount+=1;
					//if utf8 char is EF,BB,BF , continue
					if((dChar==0xf000) && (w8Char ==0xbfbb) && ((uFlag & PLSysIO_Const_UnicodeMark_ConverEndChar)!=PLSysIO_Const_UnicodeMark_ConverEndChar))
						continue;
					dChar |= (((w8Char & 0x3f) << 6) | ((w8Char & 0x3f00) >> 8));
				}//if four byte utf8 code 21 bit
				else if(((ptrUT8[iCount] & 0xf8)==0xf0) && ((iCount+3)<iUT8Size)){
					w8Char = *((UTF32char_pl *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c000) != 0x80808000)
						break;
					iCount+=3;
					dChar = ((w8Char & 7) << 18) | ((w8Char & 0x3f00) << 4) | ((w8Char & 0x3f0000) >> 10) | ((w8Char & 0x3f000000) >> 24);
				}//if five byte utf8 code 26 bit
				else if(((ptrUT8[iCount] & 0xfc)==0xf8) && ((iCount+4)<iUT8Size)){
					dChar = (w8Char & 3) << 24;
					w8Char = *((UTF32char_pl *)(&(ptrUT8[iCount])));
					if((w8Char & 0xc0c0c0c0) != 0x80808080)
						break;
					iCount+=4;
					dChar |= (((w8Char & 0x3f)<<18) | ((w8Char & 0x3f00)<<4) | ((w8Char & 0x3f0000)>>10) | ((w8Char & 0x3f000000) >> 24));
				}//if six byte utf8 code 31 bit
//				else if(((ptrSourceB[iCount] & 0xfe)==0xfc) && ((iCount+5)<iUT8Size)){
//
//				}
				//not utf8 code limite
				else{
					break;
				}
			}
			if((iBSize+4) > iBMaxLength)
				break;
			ptrUT32[iUT32Pos] = dChar;
			iUT32Pos++;
			iBSize+=4;
		}
		(*ptriUT32Size) = iUT32Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HPLResult_OK;
	}

	HPL_Result __PLSysAPI_SystemIO_UT16toUT8_(const_pl UTF16char_pl * ptrUT16,intV_pl iUT16Size,intV_pl * ptriDataPos,UTF8char_pl * ptrUT8,intV_pl * ptriUT8Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag){
		intV_pl iUTF8Pos;
		intV_pl iBSize;
		UTF16char_pl wChar;
		UTF32char_pl dConver;
		UTF32char_pl w4Char;
		uintV_pl      uFlag;
		intV_pl       iCount;
		if((ptriUT8Size==NULL_PL) || (ptriBSize==NULL_PL) || (ptruFlag==NULL_PL))
			return HPLResult_Fail;
		(*ptriUT8Size) = 0;
		(*ptriBSize)   = 0;
		if(iUT16Size<=0 || iBMaxLength<=0)
			return HPLResult_Fail;
		iUTF8Pos=0;
		iBSize  =0;
		uFlag   =*ptruFlag;
		for(iCount=0;iCount<iUT16Size;iCount++){
			wChar=ptrUT16[iCount];
			w4Char = 0;
			if((wChar==0xfeff) || (wChar==0xfffe)){
				if(wChar==0xfeff)
					uFlag |= PLSysIO_Const_UnicodeMark_SmallEnd;
				else
					uFlag &= (~PLSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & PLSysIO_Const_UnicodeMark_ConverEndChar) != PLSysIO_Const_UnicodeMark_ConverEndChar)
					continue;
			}
			//21bit
			if(((wChar & 0xfc00)==0xd800) && ((iCount+1)<iUT16Size) && ((ptrUT16[iCount+1] & 0xfc00)==0xdc00)){
				w4Char= *((UTF32char_pl *)(&ptrUT16[iCount]));
				iCount++;
				dConver  = (w4Char >> 18)                  | 0xf0;
				dConver |= ((w4Char>> 4 )     & 0x3f00)    | 0x8000;
				dConver |= ((w4Char<< 10)     & 0x3f0000)  | 0x800000;
				dConver |= ((w4Char << 24)    & 0x3f000000)| 0x80000000;
				*((UTF32char_pl *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}else{
				if((uFlag & PLSysIO_Const_UnicodeMark_SmallEnd) == 0)
					wChar = (wChar >> 8) | ((wChar << 8) & 0xff00);
				// if utf16 value is 0x00 - 0x7f so utf8 one byte
				if(wChar<=0x7f){
					if((iBSize+1)>iBMaxLength)
						break;
					ptrUT8[iBSize] = wChar;
					iBSize+=1;
					iUTF8Pos++;
				}// if utf16 value is 0x80 - 0x7ff so utf8 two byte
				else if(wChar<=0x7ff){
					if((iBSize+2)>iBMaxLength)
						break;
					dConver = (wChar >> 6) | 0xc0;
					dConver |= ((0x80 | (wChar & 0x3f)) << 8);
					*((UTF16char_pl *)(&(ptrUT8[iBSize]))) = dConver;
					iBSize  +=2;
					iUTF8Pos+=1;
				}// if utf16 value is 0x800 - 0xffff so utf8 three byte
//				else if(wChar<=((UTF16char_pl)(0xffff))){
//					if((iBSize+3)>iBMaxLength)
//						break;
//					dConver  = (wChar >> 12) | 0xe0;
//					ptrUT8[iBSize] = dConver;
//					dConver  = ((wChar >> 6) & 0x3f) | 0x80;
//					iBSize+=1;
//					dConver |= ((wChar << 8) & 0x3f00) | 0x8000;
//					*((UTF16char_pl *)(&(ptrUT8[iBSize]))) = dConver;
//					iBSize+=2;
//					iUTF8Pos+=1;
//				}
				else{
					if((iBSize+3)>iBMaxLength)
						break;
					dConver  = (wChar >> 12) | 0xe0;
					ptrUT8[iBSize] = dConver;
					dConver  = ((wChar >> 6) & 0x3f) | 0x80;
					iBSize+=1;
					dConver |= ((wChar << 8) & 0x3f00) | 0x8000;
					*((UTF16char_pl *)(&(ptrUT8[iBSize]))) = dConver;
					iBSize+=2;
					iUTF8Pos+=1;
				}
			}
		}
		(*ptriUT8Size) = iUTF8Pos;
		(*ptriBSize)   = iBSize;
		(*ptruFlag)    = uFlag;
		(*ptriDataPos) = iCount;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_UT16toUT32_(const_pl UTF16char_pl * ptrUT16,intV_pl iUT16Size,intV_pl * ptriDataPos,UTF32char_pl * ptrUT32,intV_pl * ptriUT32Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag){
		UTF32char_pl dChar;
		UTF32char_pl dConver;
		intV_pl       iUTF32Pos;
		intV_pl       iBSize;
		uintV_pl      uFlag;
		intV_pl       iCount;
		if((ptriBSize==NULL_PL) || (ptriUT32Size==NULL_PL) || (ptruFlag==NULL_PL))
			return HPLResult_Fail;
		(*ptriUT32Size) = 0;
		(*ptriBSize)    = 0;
		if((ptrUT16==NULL_PL) || (iUT16Size<=0) || (ptrUT32==NULL_PL) || (iBMaxLength==NULL_PL))
			return HPLResult_Fail;
		iUTF32Pos = 0;
		iBSize    = 0;
		uFlag     = (*ptruFlag);
		for(iCount=0;iCount<iUT16Size;iCount++){
			if((iBSize+4)>iBMaxLength)
				break;
			dChar = (UTF32char_pl)(ptrUT16[iCount]);
			if((dChar==0xfeff) || (dChar==0xfffe)){
				if(dChar==0xfeff)
					uFlag |= PLSysIO_Const_UnicodeMark_SmallEnd;
				else
					uFlag &= (~PLSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & PLSysIO_Const_UnicodeMark_ConverEndChar) != PLSysIO_Const_UnicodeMark_ConverEndChar)
					continue;
			}
			if(((dChar & 0xfc00)==0xd800) && ((iCount+1)<iUT16Size) && ((ptrUT16[iCount+1] & 0xfc00)==0xdc00)){
				iCount++;
				dConver = (dChar & 0x3ff) << 10;
				iBSize +=2;
				dChar   = (UTF32char_pl)ptrUT16[iCount];
				dConver |= (dChar & 0x3ff);
				iBSize +=2;
				ptrUT32[iUTF32Pos] = dConver;
				iUTF32Pos++;
			}else{
				if((uFlag & PLSysIO_Const_UnicodeMark_SmallEnd)!=PLSysIO_Const_UnicodeMark_SmallEnd){
					dConver = (dChar << 16) & 0xffff0000;
				}else{
					dConver = dChar;
				}
				ptrUT32[iUTF32Pos] = dConver;
				iUTF32Pos++;
				iBSize+=4;
			}
		}
		(*ptriUT32Size) = iUTF32Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HPLResult_OK;
	}

	HPL_Result __PLSysAPI_SystemIO_UT32toUT8_(const_pl UTF32char_pl * ptrUT32,intV_pl iUT32Size,intV_pl * ptriDataPos,UTF8char_pl * ptrUT8,intV_pl * ptriUT8Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag){
		UTF32char_pl dChar;
		UTF32char_pl dConver;
		intV_pl iUTF8Pos;
		intV_pl iBSize;
		uintV_pl uFlag;
		intV_pl iCount;
		if((ptriUT8Size == NULL_PL) || (ptriBSize==NULL_PL) || (ptruFlag==NULL_PL))
			return HPLResult_Fail;
		(*ptriUT8Size)=0;
		(*ptriBSize)  =0;
		if((ptrUT32 == NULL_PL) || (iUT32Size<=0) || (ptrUT8 == NULL_PL)  || (iBMaxLength<=0))
			return HPLResult_Fail;
		iUTF8Pos = 0;
		iBSize   = 0;
		uFlag = *ptruFlag;
		for(iCount=0;iCount<iUT32Size;iCount++){
			dChar = ptrUT32[iCount];
			if((dChar==0x0000feff) || (dChar==0xfffe0000)){
				if(dChar==0x0000feff)
					uFlag |= PLSysIO_Const_UnicodeMark_SmallEnd;
				else
					uFlag &= (~PLSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & PLSysIO_Const_UnicodeMark_ConverEndChar) != PLSysIO_Const_UnicodeMark_ConverEndChar )
					continue;
			}
			//if byte Order is 0xfffe,so Conver to 0xfeff Mode
			//utf8 no byte Order ,Conver UTF32 char to 0xfeff Mode
			if((uFlag & PLSysIO_Const_UnicodeMark_SmallEnd)!=PLSysIO_Const_UnicodeMark_SmallEnd)
				dChar = (dChar << 24) | (dChar >> 24) | ((dChar >> 8) & 0x0000ff00) | ((dChar << 8) & 0x00ff0000);
			//7bit
			if(dChar<=0x7f){
				if((iUTF8Pos+1)>iBMaxLength)
					break;
				ptrUT8[iBSize] = (UTF8char_pl)dChar;
				iBSize  +=1;
				iUTF8Pos+=1;
			}//11bit
			else if(dChar<=0x7ff){
				if((iBSize+2)>iBMaxLength)
					break;
				dConver = (dChar >> 6) | 0xc0;
				dConver |= ((0x80 | (dChar & 0x3f)) << 8);
				*((UTF16char_pl *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize  +=2;
				iUTF8Pos+=1;
			}//16bit
			else if(dChar<=0xffff){
				if((iBSize+3)>iBMaxLength)
					break;
				dConver  = (dChar >> 12) | 0xe0;
				ptrUT8[iBSize] = dConver;
				dConver  = ((dChar >> 6) & 0x3f) | 0x80;
				iBSize+=1;
				dConver |= ((dChar << 8) & 0x3f00) | 0x8000;
				*((UTF16char_pl *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=2;
				iUTF8Pos+=1;
			}//21bit
			else if(dChar<=0x1fffff){
				if((iBSize+4)>iBMaxLength)
					break;
				dConver  = (dChar >> 18)                  | 0xf0;
				dConver |= ((dChar>> 4 )     & 0x3f00)    | 0x8000;
				dConver |= ((dChar<< 10)     & 0x3f0000)  | 0x800000;
				dConver |= ((dChar << 24)    & 0x3f000000)| 0x80000000;
				*((UTF32char_pl *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}//26bit
			else if(dChar<=0x3ffffff){
				if((iBSize+5)>iBMaxLength)
					break;
				dConver  = (dChar >> 24) | 0xf8;
				ptrUT8[iBSize] = dConver;
				dConver  = ((dChar >> 18) & 0x3f) | 0x80;
				iBSize+=1;
				dConver |= ((dChar >> 4) & 0x3f00)| 0x8000;
				dConver |= ((dChar << 10) & 0x3f0000) | 0x800000;
				dConver |= ((dChar << 24) & 0x3f000000) | 0x80000000;
				*((UTF32char_pl *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}//31bit
			else if(dChar<=0x7fffffff){
				if((iBSize+6)>iBMaxLength)
					break;
				dConver = (dChar >> 30) | 0xfe;
				dConver = ((dChar >> 16) | 0x3f00) | 0x8000;
				*((UTF16char_pl *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=2;
				dConver |= ((dChar >> 18) & 0x3f) | 0x80;
				dConver |= ((dChar >> 4)  & 0x3f00) | 0x8000;
				dConver |= ((dChar << 10) & 0x3f0000) | 0x800000;
				dConver |= ((dChar << 24) & 0x3f000000) | 0x80000000;
				*((UTF32char_pl *)(&(ptrUT8[iBSize]))) = dConver;
				iBSize+=4;
				iUTF8Pos+=1;
			}else{
				break;
			}
		}
		(*ptriUT8Size)=iUTF8Pos;
		(*ptriBSize)  =iBSize;
		(*ptruFlag)   =uFlag;
		(*ptriDataPos)= iCount;
		return HPLResult_OK;
	}
	HPL_Result __PLSysAPI_SystemIO_UT32toUT16_(const_pl UTF32char_pl * ptrUT32,intV_pl iUT32Size,intV_pl * ptriDataPos,UTF16char_pl * ptrUT16,intV_pl * ptriUT16Size,intV_pl * ptriBSize,intV_pl iBMaxLength,uintV_pl * ptruFlag){
		UTF32char_pl dChar;
		UTF32char_pl dConver;
		intV_pl iUTF16Pos;
		intV_pl iCharSize;
		intV_pl iBSize;
		uintV_pl  uFlag;
		intV_pl iCount;
		if((ptriUT16Size==NULL_PL) || (ptriBSize==NULL_PL) || (ptruFlag==NULL_PL))
			return HPLResult_Fail;
		(*ptriUT16Size) = 0;
		(*ptriBSize)    = 0;
		if((ptrUT32==NULL_PL) || (iUT32Size<=0) || (iBMaxLength<2) || (ptrUT16==NULL_PL))
			return HPLResult_Fail;
		iUTF16Pos = 0;
		iBSize    = 0;
		iCharSize = 0;
		uFlag = *ptruFlag;
		for(iCount=0;iCount<iUT32Size;iCount++){
			dChar = ptrUT32[iCount];
			if((dChar==0x0000feff) || (dChar==0xfffe0000)){
				//big end
				if(dChar==0x0000feff)
					uFlag |= PLSysIO_Const_UnicodeMark_SmallEnd;
				else //small end
					uFlag &= (~PLSysIO_Const_UnicodeMark_SmallEnd);
				if((uFlag & PLSysIO_Const_UnicodeMark_ConverEndChar) != PLSysIO_Const_UnicodeMark_ConverEndChar)
					continue;
			}
			if((uFlag & PLSysIO_Const_UnicodeMark_SmallEnd) == PLSysIO_Const_UnicodeMark_SmallEnd){
				if(dChar<=0xffff){
					if((iBSize+2) > iBMaxLength)
						break;
					ptrUT16[iCharSize] = dChar;
					iUTF16Pos++;
					iBSize+=2;
					iCharSize++;
				}else{
					if((iBSize+4) > iBMaxLength)
						break;
					dConver = (((dChar >> 10) & 0x03ff) | 0xd800) | (((dChar & 0x03ff) | 0xdc00) << 16);
					*((UTF32char_pl *)(&(ptrUT16[iCharSize]))) = dConver;
					iCharSize+=2;
					iBSize+=4;
					iUTF16Pos++;
				}
			}else{
				if((dChar & 0xffff)==0){
					if((iBSize+2) > iBMaxLength)
						break;
					ptrUT16[iCharSize] = ((dChar>>16) & 0xffff);
					iUTF16Pos++;
					iBSize+=2;
					iCharSize++;
				}else{
					if((iBSize+4) > iBMaxLength)
						break;
					dConver = (((dChar >> 10) & 0x03ff) | 0xd800) | (((dChar & 0x03ff) | 0xdc00) << 16);
					*((UTF32char_pl *)(&(ptrUT16[iCharSize]))) = dConver;
					iCharSize+=2;
					iBSize+=4;
					iUTF16Pos++;
				}
			}
		}
		(*ptriUT16Size) = iUTF16Pos;
		(*ptriBSize)    = iBSize;
		(*ptruFlag)     = uFlag;
		(*ptriDataPos)  = iCount;
		return HPLResult_OK;
	}
	bool_pl __PLSysAPI_SystemIO_isLegalUTF8_(const_pl void_pl * ptrSource,intV_pl iSourceLength){
		UTF8char_pl a;
	    const_pl UTF8char_pl* srcptr = (UTF8char_pl *)(((byte_pl *)ptrSource) + iSourceLength);
	    switch (iSourceLength){
	    default:
	        return false_pl;
	    case 4:
	        if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
	            return false_pl;
	    case 3:
	    	a = (*--srcptr);
	        if (a<0x80 || a > 0xBF)
	            return false_pl;
	    case 2:
	        if ((a = (*--srcptr)) > 0xBF)
	            return false_pl;
	        switch (*((byte_pl *)ptrSource)){
	        case 0xE0:
	            if (a < 0xA0)
	                return false_pl; break;
	        case 0xED:
	            if (a > 0x9F)
	                return false_pl; break;
	        case 0xF0:
	            if (a < 0x90)
	                return false_pl; break;
	        case 0xF4:
	            if (a > 0x8F)
	                return false_pl; break;
	        default:
	            if (a < 0x80)
	                return false_pl;
	        }
	    case 1:
	        if ((*((byte_pl *)ptrSource)) >= 0x80 && (*((byte_pl *)ptrSource)) < 0xC2)
	            return false_pl;
	    }
	   if (*((byte_pl *)ptrSource) > 0xF4)
	        return false_pl;
		return true_pl;
	}


	/***********************************************************************************
	 * Anis Code Disposal
	 ***********************************************************************************/
	intV_pl __PLSysAPI_Ansi_findMarkChar(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl cChar){
		intV_pl iPos;
		iPos=-1;
		for(int_pl iCount=0;iCount<iSize;iCount++){
			if(ptrString[iCount] == cChar){
				iPos = iCount;
				break;
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Ansi_findMarkCharR(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl cChar){
		intV_pl iPos;
		iPos = -1;
		while(iSize>0){
			iSize--;
			if(ptrString[iSize] == cChar){
				iPos = iSize;
				break;
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Ansi_findMarkString(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl * ptrMark,intV_pl iMarkSize){
		intV_pl iPos;
		intV_pl iMaxCount;
		iPos = -1;
		if((iMarkSize<=0) && (iSize>=iMarkSize))
			return iPos;
		iMaxCount = iSize - iMarkSize;
		for(int_pl iCount=0;iCount<=iMaxCount;iCount++){
			if(ptrString[iCount] == ptrMark[0]){
				if(PLSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Ansi_findMarkStringR(const_pl char_pl * ptrString,intV_pl iSize,const_pl char_pl * ptrMark,intV_pl iMarkSize){
		intV_pl iPos;
		intV_pl iCount;
		iPos = -1;
		if((iMarkSize<=0) && (iSize>=iMarkSize))
			return iPos;
		iCount = iSize - iMarkSize;
		while(iCount>0){
			iCount--;
			if(ptrString[iCount] == ptrMark[0]){
				if(PLSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_pl    __PLSysAPI_Ansi_StrCpy(char_pl * ptrD,const_pl char_pl * ptrS,intV_pl iwCpySize){
		PLSysAPI_MemoryCpy(ptrD,ptrS,iwCpySize);
		return iwCpySize;
	}
	bool_pl    __PLSysAPI_Ansi_StrCmp(const_pl char_pl * ptrStr1,const_pl char_pl * ptrStr2,intV_pl iwSize){
		return PLSysAPI_MemoryCmp(ptrStr1,ptrStr2,iwSize) == 0 ? true_pl : false_pl;
	}
	intV_pl    __PLSysAPI_Ansi_StringSize(const_pl char_pl * ptrStr,intV_pl iMaxSize){
		intV_pl iNumCount;
		intV_pl iCharSize;
		intV_pl iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_pl iCode;
			iCode = -1;
			#if PLCPU_IAXX == PLCPU_IA32
				uint32_pl * ptrU32;
				uint32_pl   uMark;
				iNumCount = iMaxSize >> 2;
				uMark = 0xffffffff;
				ptrU32 = (uint32_pl *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if PLCPU_DataByteRank == PLCPU_DataByteSmallEnd
						if((ptrU32[iCount] && ((uint32_pl)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#elif PLCPU_DataByteRank == PLCPU_DataByteBigEnd
						if((ptrU32[iCount] && ((uint32_pl)0xff000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff00)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=4;
						}
				}
				iNumCount = iMaxSize & 3;
			#elif PLCPU_IAXX == PLCPU_IA64
				uint64_pl * ptrU64;
				uint64_pl   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_pl *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if PLCPU_DataByteRank == PLCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_pl)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000000000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000000000)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00000000000000)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#elif PLCPU_DataByteRank == PLCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_pl)0xff00000000000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000000000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=8;
						}
				}
				iNumCount = iMaxSize & 7;
			#endif
			if(iCode<0){
				for(iCount = 0;iCount < iNumCount;iCount++){
					if(ptrStr[iCharSize] == ((char_pl)0)){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			}
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (char_pl)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HPL_Result __PLSysAPI_Ansi_StringStarCharSize(const_pl char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,
															intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag){

		return HPLResult_OK;
	}

	/***********************************************************************************
	 * UTF8 Code Disposal
	 ***********************************************************************************/
	intV_pl __PLSysAPI_Unicode8_findMarkChar(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl cChar){
		intV_pl iPos;
		iPos=-1;
		for(int_pl iCount=0;iCount<iwSize;iCount++){
			if(ptrString[iCount] == cChar){
				iPos = iCount;
				break;
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Unicode8_findMarkCharR(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl cChar){
		intV_pl iPos;
		iPos = -1;
		while(iwSize>0){
			iwSize--;
			if(ptrString[iwSize] == cChar){
				iPos = iwSize;
				break;
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Unicode8_findMarkString(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl * ptrMark,intV_pl iwMarkSize){


		return 0;
	}
	intV_pl __PLSysAPI_Unicode8_findMarkStringR(const_pl UTF8char_pl * ptrString,intV_pl iwSize,const_pl UTF8char_pl * ptrMark,intV_pl iwMarkSize){
		return 0;
	}
	intV_pl __PLSysAPI_Unicode8_StrCpy(UTF8char_pl * ptrD,const_pl UTF8char_pl * ptrS,intV_pl iwCpySize){
		PLSysAPI_MemoryCpy(ptrD,ptrS,PLSysAPI_UTF8_CharSize2ByteSize(iwCpySize));
		return iwCpySize;
	}
	bool_pl __PLSysAPI_Unicode8_StrCmp(const_pl UTF8char_pl * ptrStr1,const_pl UTF8char_pl * ptrStr2,intV_pl iwSize){
		return PLSysAPI_MemoryCmp(ptrStr1,ptrStr2,PLSysAPI_UTF8_CharSize2ByteSize(iwSize)) == 0 ? true_pl : false_pl;
	}
	intV_pl    __PLSysAPI_Unicode8_StringSize(const_pl UTF8char_pl * ptrStr,intV_pl iMaxSize){
		intV_pl iNumCount;
		intV_pl iCharSize;
		intV_pl iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_pl iCode;
			iCode = -1;
			#if PLCPU_IAXX == PLCPU_IA32
				uint32_pl * ptrU32;
				uint32_pl   uMark;
				iNumCount = iMaxSize >> 2;
				uMark = 0xffffffff;
				ptrU32 = (uint32_pl *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if PLCPU_DataByteRank == PLCPU_DataByteSmallEnd
						if((ptrU32[iCount] && ((uint32_pl)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#elif PLCPU_DataByteRank == PLCPU_DataByteBigEnd
						if((ptrU32[iCount] && ((uint32_pl)0xff000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff00)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xff)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=4;
						}
				}
				iNumCount = iMaxSize & 3;
			#elif PLCPU_IAXX == PLCPU_IA64
				uint64_pl * ptrU64;
				uint64_pl   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_pl *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if PLCPU_DataByteRank == PLCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_pl)0xff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000000000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000000000)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00000000000000)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#elif PLCPU_DataByteRank == PLCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_pl)0xff00000000000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000000000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff000000)) == 0){
							iCharSize+=4;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff0000)) == 0){
							iCharSize+=5;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff00)) == 0){
							iCharSize+=6;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xff)) == 0){
							iCharSize+=7;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=8;
						}
				}
				iNumCount = iMaxSize & 7;
			#endif
			if(iCode<0){
				for(iCount = 0;iCount < iNumCount;iCount++){
					if(ptrStr[iCharSize] == ((UTF8char_pl)0)){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			}
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (UTF8char_pl)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HPL_Result __PLSysAPI_Unicode8_StringStarCharSize(const_pl UTF8char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag){
		intV_pl iNumCount;

		#if PLCPU_IAXX == PLCPU_IA32
			iNumCount = iSize >> 1;
//			for(intV_pl iCount = 0;iCount < iNumCount;iCount++){
//
//			}
			#if PLCPUI_XXXX == PLCPUI_CISC

			#elif PLCPUI_XXXX == PLCPUI_RISC

			#endif
		#elif PLCPU_IAXX == PLCPU_IA64
			iNumCount = iSize >> 2;
			#if PLCPUI_XXXX == PLCPUI_CISC

			#elif PLCPUI_XXXX == PLCPUI_RISC

			#endif
		#endif
		*ptruNextFlag = uFlag;
		return HPLResult_Fail;
	}
	intV_pl PLSysAPI_TypeConverUTF8_atoi(const_pl UTF8char_pl * ptrValue,intV_pl iSize){
		return 0;
	}
	float_pl PLSysAPI_TypeConverUTF8_atof(const_pl UTF8char_pl * ptrValue,intV_pl iSize){
		return _FL_(0.0);
	}

	/***********************************************************************************
	 * UTF16 Code Disposal
	 ***********************************************************************************/
	intV_pl __PLSysAPI_Unicode16_findMarkChar(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl cChar){
		intV_pl iPos;
		iPos=-1;
		for(intV_pl iCount=0;iCount<iwSize;iCount++){
			if(ptrString[iCount] == cChar){
				iPos = iCount;
				break;
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Unicode16_findMarkCharR(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl cChar){
		intV_pl iPos;
		iPos = -1;
		while(iwSize>0){
			iwSize--;
			if(ptrString[iwSize] == cChar){
				iPos = iwSize;
				break;
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Unicode16_findMarkString(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl * ptrMark,intV_pl iwMarkSize){
		intV_pl iPos;
		intV_pl iMaxCount;
		iPos = -1;
		if((iwMarkSize<=0) && (iwSize>=iwMarkSize))
			return iPos;
		iMaxCount = iwSize - iwMarkSize;
		for(int_pl iCount=0;iCount<=iMaxCount;iCount++){
			if(ptrString[iCount] == ptrMark[0]){
				if(PLSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iwMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Unicode16_findMarkStringR(const_pl UTF16char_pl * ptrString,intV_pl iwSize,const_pl UTF16char_pl * ptrMark,intV_pl iwMarkSize){
		intV_pl iPos;
		intV_pl iCount;
		iPos = -1;
		if((iwMarkSize<=0) && (iwSize>=iwMarkSize))
			return iPos;
		iCount = iwSize - iwMarkSize;
		while(iCount>0){
			iCount--;
			if(ptrString[iCount] == ptrMark[0]){
				if(PLSysAPI_MemoryCmp(&(ptrString[iCount]),ptrMark,iwMarkSize)==0){
					iPos = iCount;
					break;
				}
			}
		}
		return iPos;
	}
	intV_pl __PLSysAPI_Unicode16_StrCpy(UTF16char_pl * ptrD,const_pl UTF16char_pl * ptrS,intV_pl iwCpySize){

		PLSysAPI_MemoryCpy((void_pl *)ptrD,(void_pl *)ptrS,(iwCpySize << 1));
		return iwCpySize;
	}
	bool_pl __PLSysAPI_Unicode16_StrCmp(const_pl UTF16char_pl * ptrStr1,const_pl UTF16char_pl * ptrStr2,intV_pl iwSize){
		return PLSysAPI_MemoryCmp((void_pl *)ptrStr1,(void_pl *)ptrStr2,(iwSize<<1)) == 0 ? true_pl : false_pl;
	}
	intV_pl __PLSysAPI_Unicode16_StringSize(const_pl UTF16char_pl * ptrStr,intV_pl iMaxSize){
		intV_pl iNumCount;
		intV_pl iCharSize;
		intV_pl iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_pl iCode;
			iCode = -1;
			#if PLCPU_IAXX == PLCPU_IA32
				uint32_pl * ptrU32;
				uint32_pl   uMark;
				iNumCount = iMaxSize >> 1;
				uMark = 0xffffffff;
				ptrU32 = (uint32_pl *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if PLCPU_DataByteRank == PLCPU_DataByteSmallEnd
						if((ptrU32[iCount] && ((uint32_pl)0xffff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xffff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#elif PLCPU_DataByteRank == PLCPU_DataByteBigEnd
						if((ptrU32[iCount] && ((uint32_pl)0xffff0000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU32[iCount] && ((uint32_pl)0xffff)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=2;
						}
				}
				iNumCount = iMaxSize & 1;
			#elif PLCPU_IAXX == PLCPU_IA64
				uint64_pl * ptrU64;
				uint64_pl   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_pl *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if PLCPU_DataByteRank == PLCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_pl)0xffff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffff0000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffff00000000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffff000000000000)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#elif PLCPU_DataByteRank == PLCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_pl)0xffff000000000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffff00000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffff0000)) == 0){
							iCharSize+=2;
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffff)) == 0){
							iCharSize+=3;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=4;
						}
				}
				iNumCount = iMaxSize & 3;
			#endif
			if(iCode<0){
				for(iCount = 0;iCount < iNumCount;iCount++){
					if(ptrStr[iCharSize] == ((UTF16char_pl)0)){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			}
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (UTF16char_pl)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HPL_Result __PLSysAPI_Unicode16_StringStarCharSize(const_pl UTF16char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag){
		for(intV_pl iCount = 0;iCount < iSize;iCount++){


			//ptrSrc[]
		}
		//const_pl UTF16char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag
		*ptruNextFlag = uFlag;
		return HPLResult_Fail;
	}
	intV_pl    PLSysAPI_TypeConverUTF16_atoi(const_pl UTF16char_pl * ptrValue,intV_pl iwSize){
		intV_pl iValue;
		iValue = 0;
		for(intV_pl iCount = 0;iCount< iwSize;iCount++){

		}
		return iValue;
	}
	float_pl   PLSysAPI_TypeConverUTF16_atof(const_pl UTF16char_pl * ptrValue,intV_pl iwSize){

		return 0.0;
	}

	/***********************************************************************************
	 * UTF16 Code Disposal
	 ***********************************************************************************/
	intV_pl __PLSysAPI_Unicode32_findMarkChar(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl cChar){
		return 0;
	}
	intV_pl __PLSysAPI_Unicode32_findMarkCharR(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl cChar){
		return 0;
	}
	intV_pl __PLSysAPI_Unicode32_findMarkString(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl * ptrMark,intV_pl iwMarkSize){
		return 0;
	}
	intV_pl __PLSysAPI_Unicode32_findMarkStringR(const_pl UTF32char_pl * ptrString,intV_pl iwSize,const_pl UTF32char_pl * ptrMark,intV_pl iwMarkSize){
		return 0;
	}
	intV_pl __PLSysAPI_Unicode32_StrCpy(UTF32char_pl * ptrD,const_pl UTF32char_pl * ptrS,intV_pl iwCpySize){
		return 0;
	}
	bool_pl __PLSysAPI_Unicode32_StrCmp(const_pl UTF32char_pl * ptrStr1,const_pl UTF32char_pl * ptrStr2,intV_pl iwSize){
		return false_pl;
	}
	intV_pl __PLSysAPI_Unicode32_StringSize(const_pl UTF32char_pl * ptrStr,intV_pl iMaxSize){

		intV_pl iCharSize;
		intV_pl iCount;
		iCharSize = 0;
		if(iMaxSize>0){
			intV_pl iCode;
			iCode = -1;
			#if PLCPU_IAXX == PLCPU_IA32
				for(iCount = 0;iCount < iMaxSize;iCount++){
					if(ptrStr[iCount] == (UTF32char_pl)0){
						iCode = 0;
						break;
					}
					iCharSize++;
				}
			#elif PLCPU_IAXX == PLCPU_IA64
				intV_pl iNumCount;
				uint64_pl * ptrU64;
				uint64_pl   uMark;
				iNumCount = iSize >> 3;
				ptrU64 = (uint64_pl *)ptrStr;
				for(iCount = 0;iCount < iNumCount;iCount++){
					#if PLCPU_DataByteRank == PLCPU_DataByteSmallEnd
						if((ptrU64[iCount] && ((uint64_pl)0xffffffff)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffffffff00000000)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#elif PLCPU_DataByteRank == PLCPU_DataByteBigEnd
						if((ptrU64[iCount] && ((uint64_pl)0xffffffff00000000)) == 0){
							iCode = 0;
							break;
						}else if((ptrU64[iCount] && ((uint64_pl)0xffffffff)) == 0){
							iCharSize+=1;
							iCode = 0;
							break;
						}
					#endif
						else{
							iCharSize+=2;
						}
				}
				if(iCode<0){
					if(ptrStr[iCharSize] == ((UTF32char_pl)0)){
						iCode = 0;
					}
				}
			#endif
			if(iCode<0){
				iCharSize = -1;
			}
		}else{
			while(ptrStr[iCharSize] != (UTF32char_pl)0){
				iCharSize++;
			}
		}
		return iCharSize;
	}
	HPL_Result __PLSysAPI_Unicode32_StringStarCharSize(const_pl UTF32char_pl * ptrSrc,intV_pl iSize,intV_pl * ptriCharSize,intV_pl * ptriPos,uintV_pl uFlag,uintV_pl * ptruNextFlag){

		//HPLResultK_CharCode_StrTrun
		*ptruNextFlag = uFlag;
		return HPLResult_Fail;
	}
	intV_pl PLSysAPI_TypeConverUTF32_atoi(const_pl UTF32char_pl * ptrValue,intV_pl iwSize){
		return 0;
	}
	float_pl PLSysAPI_TypeConverUTF32_atof(const_pl UTF32char_pl * ptrValue,intV_pl iwSize){
		return _FL_(0.0);
	}

