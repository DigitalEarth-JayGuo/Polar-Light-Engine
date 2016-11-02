/*
 * PLEngineGraphicsInface.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineBaseH.h"
#ifndef PLENGINEGRAPHICSINFACE_H_
#define PLENGINEGRAPHICSINFACE_H_
#pragma pack(4)
	typedef struct _SPLVector2{
		float_pl x;
		float_pl y;
	}PLVector2;
	typedef struct _SPLVector3 : public _SPLVector2{
		float_pl z;
	} PLVector3;
	typedef  struct _SPLVector4 : public _SPLVector3{
		float_pl w;
	} PLVector4;
	typedef struct _SPLQuaternion{
		float_pl w;
		float_pl x;
		float_pl y;
		float_pl z;
	} PLQuaternion;
	typedef struct _SPLMatrix2x2{
		float_pl m[2][2];
	} PLMatrix2x2;
	typedef struct _SPLMatrix3x3{
		float_pl m[3][3];
	} PLMatrix3x3;
	typedef struct _SPLMatrix4x4{
		float_pl m[4][4];
	} PLMatrix4x4;
	typedef struct _SPLArea{
		uintV_pl uWidth;
		uintV_pl uHeight;
	}PLArea;
	typedef struct _SPLAreaF{
		float_pl fWidht;
		float_pl fHeight;
	}PLAreaF;
	/*
	 * Axis Alignment Box
	 * */
	typedef struct _SPLAABB{
		PLVector3 vMin;
		PLVector3 vMax;
		PLVector3 vCenter;
		PLVector3 vInterval;	//lineal measure
	}PLAABB;
	/*
	 * Orientation's Axis Alignment Box
	 * */
	typedef struct _SPLOBB{
		PLVector3 vCenter;
		PLVector3 vLocal1;
		PLVector3 vLocal2;
		PLVector3 vLocal3;
		PLVector3 vInterval;
	}PLOBB;

	typedef struct _SPLRay3{
		PLVector3 vPostion;
		PLVector3 vNDirection;	//identity of direction vector
		float_pl  fLinearity;	//linear value
	}PLRay3;
#pragma pack()

#endif /* PLENGINEGRAPHICSINFACE_H_ */
