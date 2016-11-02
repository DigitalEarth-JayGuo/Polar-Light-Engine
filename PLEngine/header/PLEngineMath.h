/*
 * PLEngineMath.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
#include "PLEngineBaseDataType.h"
#include "PLEngineGraphicsInface.h"
#include "PLEngineH.h"
#include "PLEngineSysAPI.h"
#ifndef PLENGINEMATH_H_
#define PLENGINEMATH_H_
	#define Math_AnglePI _FL_(3.141592)

	#define Math_Radian(angle) (angle*Math_AnglePI*0.005555556) //_FL_(180.0)
//	_PLE_lib_Variable _CallStack_Order_ bool_pl InitializNormalizMathLibraryPL();


	typedef _CallStack_default_ void_pl (* __Matrix3x3AxisRotation__PL__ )(PLMatrix3x3 *,PLVector3 *,float_pl);
	typedef _CallStack_default_ void_pl (* __InitializNormalizMatrix3x3__PL__)(PLMatrix3x3 *);
	typedef _CallStack_default_ void_pl (* __InitializNormalizMatrix4x4__PL__)(PLMatrix4x4 *);
	typedef _CallStack_default_ void_pl (* __Matrix3x3Mul__PL__ )(PLMatrix3x3 * ,const_pl PLMatrix3x3 * ,const_pl PLMatrix3x3 * );
	typedef _CallStack_default_ void_pl (* __Matrix4x4Mul__PL__ )(PLMatrix4x4 * ,const_pl PLMatrix4x4 * ,const_pl PLMatrix4x4 * );
	typedef _CallStack_default_ void_pl (* __Matrix3x3Transpose__PL__ )(PLMatrix3x3 * ,const_pl PLMatrix3x3 * );
	typedef _CallStack_default_ void_pl (* __Matrix4x4Transpose__PL__ )(PLMatrix4x4 * ,const_pl PLMatrix4x4 * );
	typedef _CallStack_default_ void_pl (* __Matrix4x4TransformV__PL__ )(PLVector4 * ptrOut,const_pl PLMatrix4x4 * ptrTransform,const_pl PLVector4 * ptrInput);

	typedef _CallStack_default_ void_pl  (* __Matrix3x3Cofactor__PL__ )(PLMatrix3x3 *,const_pl PLMatrix3x3 *);
	typedef _CallStack_default_ float_pl (* __Matrix3x3Determinant__PL__ )(const_pl PLMatrix3x3 *);
	typedef _CallStack_default_ void_pl  (* __Matrix4x4Cofactor__PL__ )(PLMatrix4x4 *,const_pl PLMatrix4x4 *);
	typedef _CallStack_default_ float_pl (* __Matrix4x4Determinant__PL__ )(const_pl PLMatrix4x4 *);
	typedef _CallStack_default_ void_pl  (* __MatrixOb__PL__ )(PLMatrix3x3 *,const_pl PLMatrix3x3 *);
	typedef _CallStack_default_ void_pl  (* __Matrix4x4Ob__PL__ )(PLMatrix4x4 *,const_pl PLMatrix4x4 *);

	typedef _CallStack_default_ void_pl (* __InitializQuaternion__PL__ )(PLQuaternion *);
	typedef _CallStack_default_ void_pl (* __QuaternionSlerp__PL__ )(PLQuaternion *,const_pl PLQuaternion *,PLQuaternion *,float_pl);
	typedef _CallStack_default_ void_pl (* __Quaternion_make__PL__)(PLQuaternion *,float_pl,float_pl,float_pl,float_pl);
	typedef _CallStack_default_ void_pl (* __QuaternionAdd__PL__)(PLQuaternion *,const_pl PLQuaternion *,const_pl PLQuaternion *);
	typedef _CallStack_default_ void_pl (* __QuaternionMul__PL__)(PLQuaternion *,const_pl PLQuaternion *,const_pl PLQuaternion *);
	typedef _CallStack_default_ void_pl (* __QuaternionMakeMatrix__PL__)(PLMatrix3x3 *,const_pl PLQuaternion *);
	typedef _CallStack_default_ void_pl (* __QuaternionMakeMatrix4x4__PL__)(PLMatrix4x4 *,const_pl PLQuaternion *,const_pl PLVector4 *);
	typedef _CallStack_default_ void_pl (* __QuaternionNormal__PL__)(PLQuaternion * ptrOut,const_pl PLQuaternion * ptrFirst);

	typedef _CallStack_default_ float_pl (* __VectorDot__PL__)(const_pl PLVector3 *,const_pl PLVector3 *);
	typedef _CallStack_default_ void_pl  (* __VectorCorss__PL__)(PLVector3 *,const_pl PLVector3 *,const_pl PLVector3 *);
	typedef _CallStack_default_ float_pl (* __Vector3Modulus__PL__)(const_pl PLVector3 *);
	typedef _CallStack_default_ float_pl (* __Vector4Modulus__PL__)(const_pl PLVector4 *);
	typedef _CallStack_default_ void_pl (* __Vector3Normal__PL__)(PLVector3 *,const_pl PLVector3 *);
	typedef _CallStack_default_ void_pl (* __Vector4Normal__PL__)(PLVector4 *,const_pl PLVector4 *);

	//	_PLE_lib_Variable _CallStack_Order_ __InitializNormalizMatrix3x3__PL__ InitializNormalizMatrix3x3PL;

	_CallStack_default_ bool_pl InitializDefaultMathLibraryPL();
   //compute Absolute of Value
   inline intV_pl sf_abs(intV_pl iabs){
	   return iabs<0 ? -iabs : iabs;
   }
   inline float_pl sf_absf(float_pl fabs){
	   return fabs<_FL_(0.0000) ? -fabs : fabs;
   }
   //math calculate sin value
   inline float_pl sf_sinf32(float_pl fRadian){
	   return PLSysAPI_SinF(fRadian);
   }
   inline float_pl sf_cosf32(float_pl fRadian){
	   return PLSysAPI_CosF(fRadian);
   }
   inline float_pl sf_tanf32(float_pl fRadian){
	   return PLSysAPI_Tan(fRadian);
   }
   inline float_pl sf_ctgf32(float_pl fRadian){
		 return _FL_(1.0) / PLSysAPI_Tan(fRadian);
   }
   inline float_pl sf_Sqrtf32(float_pl fValue){
	   return PLSysAPI_Sqrt(fValue);
   }
   inline intV_pl  sf_Floor(float_pl fValue){
	   return (intV_pl)(::floorf(fValue));
   }
   inline float_pl  sf_Decimal(float_pl fValue){
	   return (fValue - ::floorf(fValue));
   }
   inline float_pl  sf_Pow(float_pl fValue,float_pl fExp){
	   return (float_pl)(::pow(fValue,fExp));
   }
   _CallStack_default_ void_pl InitializNormalizMatrix3x3(PLMatrix3x3 * ptrMart);
   _CallStack_default_ void_pl InitializNormalizMatrix4x4(PLMatrix4x4 * ptrMart);

   _CallStack_default_ float_pl Vector3Modulus(const_pl PLVector3 * v);
   _CallStack_default_ float_pl Vector4Modulus(const_pl PLVector4 * v);
   _CallStack_default_ void_pl Vector3Normal(PLVector3 * ptrVOut,const_pl PLVector3 * v);
   _CallStack_default_ void_pl Vector4Normal(PLVector4 * ptrVOut,const_pl PLVector4 * v);
   _CallStack_default_ float_pl VectorDot(const_pl PLVector3 * ptr1,const_pl PLVector3 * ptr2);
   _CallStack_default_ void_pl VectorCorssL(PLVector3 * ptrOut,const_pl PLVector3 * ptr1,const_pl PLVector3 * ptr2);
   _CallStack_default_ void_pl VectorCorssR(PLVector3 * ptrOut,const_pl PLVector3 * ptr1,const_pl PLVector3 * ptr2);


   _CallStack_default_ void_pl InitializQuaternion(PLQuaternion * ptrResults);
   _CallStack_default_ void_pl make_Quaternion(PLQuaternion * ptrResults,float_pl fAxisX,float_pl fAxisY,float_pl fAxisZ,float_pl Radian);
   _CallStack_default_ void_pl QuaternionAdd(PLQuaternion * ptrResults,const_pl PLQuaternion * ptrFirst,const_pl PLQuaternion * ptrSecond);
   _CallStack_default_ void_pl QuaternionMul(PLQuaternion * ptrResults,const_pl PLQuaternion * ptrFirst,const_pl PLQuaternion * ptrSecond);
   _CallStack_default_ float_pl QuaternionDot(PLQuaternion * ptrFirst,const_pl PLQuaternion * ptrSecond);
   _CallStack_default_ float_pl QuaternionModulus(const_pl PLQuaternion * ptrFirst);
   _CallStack_default_ void_pl QuaternionNormal(PLQuaternion * ptrOut,const_pl PLQuaternion * ptrFirst);
   _CallStack_default_ void_pl QuaternionReciprocal(PLQuaternion * ptrRecipOut,const_pl PLQuaternion * ptrFirst);

   _CallStack_default_ void_pl QuaternionMakeMatrixSR(PLMatrix3x3 * ptrOut,const_pl PLQuaternion * ptrInput);
   _CallStack_default_ void_pl QuaternionMakeMatrixR(PLMatrix3x3 * ptrOut,const_pl PLQuaternion * ptrInput);
   _CallStack_default_ void_pl QuaternionMakeMatrix4x4SL(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov);
   _CallStack_default_ void_pl QuaternionMakeMatrix4x4L(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov);
   _CallStack_default_ void_pl QuaternionMakeMatrix4x4SR(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov);
   _CallStack_default_ void_pl QuaternionMakeMatrix4x4R(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov);


   _CallStack_default_ void_pl Matrix3x3To4x4L(PLMatrix4x4 * ptrOut,const PLMatrix3x3 * ptrInput,const PLVector4 * ptrMov);
   _CallStack_default_ void_pl Matrix3x3To4x4R(PLMatrix4x4 * ptrOut,const_pl PLMatrix3x3 * ptrInput,const_pl PLVector4 * ptrMov);
   _CallStack_default_ void_pl Matrix3x3To4x4(PLMatrix4x4 * ptrOut,const_pl PLMatrix3x3 * ptrInput);


   // Interval  =  (Q0(begin) of Reciprocal)  mul (Q1(end))
   _CallStack_default_ void_pl QuaternionInterval(PLQuaternion * ptrOut,const_pl PLQuaternion * ptrBegin,const_pl PLQuaternion * ptrEnd);
   // Interval  =  (Q1(end)) mul (Q0(begin) of Reciprocal)
   _CallStack_default_ void_pl QuaternionSlerp(PLQuaternion * ptrOut,const_pl PLQuaternion * ptrBegin,const_pl PLQuaternion * ptrEnd,float_pl fSlerp);
   _CallStack_default_ void_pl Matrix3x3Mul(PLMatrix3x3 * ptrOut,const_pl PLMatrix3x3 * ptrMart1,const_pl PLMatrix3x3 * ptrMart2);
   _CallStack_default_ void_pl Matrix4x4Mul(PLMatrix4x4 * ptrOut,const_pl PLMatrix4x4 * ptrMart1,const_pl PLMatrix4x4 * ptrMart2);
   _CallStack_default_ void_pl Matrix3x3Transpose(PLMatrix3x3 * ptrOut,const_pl PLMatrix3x3 * ptrInput);
   _CallStack_default_ void_pl Matrix4x4Transpose(PLMatrix4x4 * ptrOut,const_pl PLMatrix4x4 * ptrInput);
	//Input Vector Transform to Matrix Space of Coord
   _CallStack_default_ void_pl Matrix4x4TransformVLL(PLVector4 * ptrOut,const_pl PLMatrix4x4 * ptrTransform,const_pl PLVector4 * ptrInput);
   _CallStack_default_ void_pl Matrix4x4TransformVLR(PLVector4 * ptrOut,const_pl PLMatrix4x4 * ptrTransform,const_pl PLVector4 * ptrInput);




   _CallStack_default_ void_pl  Matrix3x3Cofactor(PLMatrix3x3 * ptrOut,const_pl PLMatrix3x3 * ptrMat);
   _CallStack_default_ float_pl Matrix3x3Determinant(const_pl PLMatrix3x3 * ptrMat);
   _CallStack_default_ void_pl  Matrix4x4Cofactor(PLMatrix4x4 * ptrOut,const_pl PLMatrix4x4 * ptrMat);
   _CallStack_default_ float_pl Matrix4x4Determinant(const_pl PLMatrix4x4 * ptrMat);
   _CallStack_default_ void_pl  MatrixOb(PLMatrix3x3 * ptrOut,const_pl PLMatrix3x3 * ptrMat);
   _CallStack_default_ void_pl  Matrix4x4Ob(PLMatrix4x4 * ptrOut,const_pl PLMatrix4x4 * ptrMat);


   _CallStack_default_ void_pl Matrix3x3ZAxisRotationL(PLMatrix3x3 * ptrOut,float_pl fRadian);
   _CallStack_default_ void_pl Matrix3x3YAxisRotationL(PLMatrix3x3 * ptrOut,float_pl fRadian);
   _CallStack_default_ void_pl Matrix3x3XAxisRotationL(PLMatrix3x3 * ptrOut,float_pl fRadian);
   _CallStack_default_ void_pl Matrix3x3XAxisRotationR(PLMatrix3x3 * ptrOut,float_pl fRadian);
   _CallStack_default_ void_pl Matrix3x3YAxisRotationR(PLMatrix3x3 * ptrOut,float_pl fRadian);
   _CallStack_default_ void_pl Matrix3x3ZAxisRotationR(PLMatrix3x3 * ptrOut,float_pl fRadian);
   _CallStack_default_ void_pl Matrix3x3AxisRotation(PLMatrix3x3 * ptrOut,PLVector3 * ptrAix,float_pl fRadian);




/*
 * Base Math Calculate
 * */
	#define PLSysAPI_Math_Abs							 sf_abs
	#define PLSysAPI_Math_AbsF						     sf_absf
	#define PLSysAPI_Math_SinF							 sf_sinf32
	#define PLSysAPI_Math_CosF							 sf_cosf32
	#define PLSysAPI_Math_TanF							 sf_tanf32
	#define PLSysAPI_Math_CtgF							 sf_ctgf32
/*
 * Matrix Calculate
 * */

 	_PLE_lib_Variable __Matrix3x3Mul__PL__               PLSysAPI_Math_Matrix3x3Mul_Native;
	_PLE_lib_Variable __Matrix4x4Mul__PL__               PLSysAPI_Math_Matrix4x4Mul_Native;

	_PLE_lib_Variable __InitializNormalizMatrix3x3__PL__ PLSysAPI_Math_InitializNormalizMatrix3x3;
	_PLE_lib_Variable __InitializNormalizMatrix4x4__PL__ PLSysAPI_Math_InitializNormalizMatrix4x4;
	_PLE_lib_Variable __Matrix3x3Transpose__PL__		 PLSysAPI_Math_Matrix3x3Transpose;
	_PLE_lib_Variable __Matrix4x4Transpose__PL__		 PLSysAPI_Math_Matrix4x4Transpose;
	_PLE_lib_Variable __Matrix4x4TransformV__PL__		 PLSysAPI_Math_Matrix4x4TransformVL;
	_PLE_lib_Variable __Matrix4x4TransformV__PL__		 PLSysAPI_Math_Matrix4x4TransformVR;
	_PLE_lib_Variable __Matrix3x3Cofactor__PL__		 	 PLSysAPI_Math_Matrix3x3Cofactor;
	_PLE_lib_Variable __Matrix3x3Determinant__PL__		 PLSysAPI_Math_Matrix3x3Determinant;
	_PLE_lib_Variable __Matrix4x4Cofactor__PL__		 	 PLSysAPI_Math_Matrix4x4Cofactor;
	_PLE_lib_Variable __Matrix4x4Determinant__PL__		 PLSysAPI_Math_Matrix4x4Determinant;
	_PLE_lib_Variable __MatrixOb__PL__		 			 PLSysAPI_Math_MatrixOb;
	_PLE_lib_Variable __Matrix4x4Ob__PL__		 		 PLSysAPI_Math_Matrix4x4Ob;


	_PLE_lib_Variable __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3XAxisRotationL;
	_PLE_lib_Variable __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3YAxisRotationL;
	_PLE_lib_Variable __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3ZAxisRotationL;
	_PLE_lib_Variable __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3XAxisRotationR;
	_PLE_lib_Variable __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3YAxisRotationR;
	_PLE_lib_Variable __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3ZAxisRotationR;


	_PLE_lib_Variable __InitializQuaternion__PL__		 PLSysAPI_Math_InitializQuaternion;
	_PLE_lib_Variable __QuaternionNormal__PL__			 PLSysAPI_Math_QuaternionNormal;
	_PLE_lib_Variable __Quaternion_make__PL__			 PLSysAPI_Math_MakeQuaternion;
	_PLE_lib_Variable __QuaternionSlerp__PL__            PLSysAPI_Math_QuaternionSlerp;
	_PLE_lib_Variable __QuaternionAdd__PL__            	 PLSysAPI_Math_QuaternionAdd;
	_PLE_lib_Variable __QuaternionMul__PL__              PLSysAPI_Math_QuaternionMul;
	_PLE_lib_Variable __QuaternionMakeMatrix__PL__     	 PLSysAPI_Math_QuaternionMakeMatrix;
	_PLE_lib_Variable __QuaternionMakeMatrix__PL__       PLSysAPI_Math_QuaternionMakeMatrixN;
	_PLE_lib_Variable __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4L;
	_PLE_lib_Variable __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4NL;
	_PLE_lib_Variable __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4R;
	_PLE_lib_Variable __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4NR;

	#define PLSysAPI_Math_Matrix4x4TransformV			 PLSysAPI_Math_Matrix4x4TransformVR
	#define	PLSysAPI_Math_Matrix3x3MulL(out,m1,m2)		 PLSysAPI_Math_Matrix3x3Mul_Native(out,m1,m2)
	#define	PLSysAPI_Math_Matrix3x3MulR(out,m1,m2)		 PLSysAPI_Math_Matrix3x3Mul_Native(out,m2,m1)
	#define PLSysAPI_Math_Matrix4x4MulL(out,m1,m2)		 PLSysAPI_Math_Matrix4x4Mul_Native(out,m1,m2)
	#define	PLSysAPI_Math_Matrix4x4MulR(out,m1,m2)		 PLSysAPI_Math_Matrix4x4Mul_Native(out,m2,m1)
	#define PLSysAPI_Math_Matrix3x3Mul					 PLSysAPI_Math_Matrix3x3MulR
	#define PLSysAPI_Math_Matrix4x4Mul					 PLSysAPI_Math_Matrix4x4MulR

	#define PLSysAPI_Math_Matrix3x3XAxisRotation		 PLSysAPI_Math_Matrix3x3XAxisRotationL
	#define PLSysAPI_Math_Matrix3x3YAxisRotation		 PLSysAPI_Math_Matrix3x3YAxisRotationL
	#define PLSysAPI_Math_Matrix3x3ZAxisRotation		 PLSysAPI_Math_Matrix3x3ZAxisRotationL

	#define PLSysAPI_Math_QuaternionMakeMatrix4x4		 PLSysAPI_Math_QuaternionMakeMatrix4x4R
	#define PLSysAPI_Math_QuaternionMakeMatrix4x4N		 PLSysAPI_Math_QuaternionMakeMatrix4x4NR




/*
 * Vector Calculate
 * */
	_PLE_lib_Variable __VectorDot__PL__					 PLSysAPI_Math_VectorDot;
	_PLE_lib_Variable __VectorCorss__PL__				 PLSysAPI_Math_VectorCorssL;
	_PLE_lib_Variable __VectorCorss__PL__				 PLSysAPI_Math_VectorCorssR;
	#define PLSysAPI_Math_VectorCorss					 PLSysAPI_Math_VectorCorssR
	_PLE_lib_Variable __Vector3Modulus__PL__			 PLSysAPI_Math_Vector3Modulus;
	_PLE_lib_Variable __Vector4Modulus__PL__			 PLSysAPI_Math_Vector4Modulus;
	_PLE_lib_Variable __Vector3Normal__PL__			 	 PLSysAPI_Math_Vector3Normal;
	_PLE_lib_Variable __Vector4Normal__PL__			 	 PLSysAPI_Math_Vector4Normal;




#endif /* PLENGINEMATH_H_ */
