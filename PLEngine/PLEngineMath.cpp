/*
 * PLEngineMath.cpp
 *
 *  Created on: 2009-6-29
 *      Author: root
 */
#include "header/PLEngineMath.h"
	/*
	 *
	 * Math API Function Pointer
	 *
	 * */
	_PLE_lib_VariableN __InitializQuaternion__PL__		  PLSysAPI_Math_InitializQuaternion			= InitializQuaternion;
	_PLE_lib_VariableN __QuaternionNormal__PL__			  PLSysAPI_Math_QuaternionNormal			= QuaternionNormal;
	_PLE_lib_VariableN __Quaternion_make__PL__			  PLSysAPI_Math_MakeQuaternion 				= make_Quaternion;
	_PLE_lib_VariableN __QuaternionSlerp__PL__            PLSysAPI_Math_QuaternionSlerp 			= NULL_PL;
	_PLE_lib_VariableN __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3AxisRotation 		= NULL_PL;
	_PLE_lib_VariableN __QuaternionAdd__PL__              PLSysAPI_Math_QuaternionAdd 				= QuaternionAdd;
	_PLE_lib_VariableN __QuaternionMul__PL__              PLSysAPI_Math_QuaternionMul 				= QuaternionMul;
	_PLE_lib_VariableN __QuaternionMakeMatrix__PL__       PLSysAPI_Math_QuaternionMakeMatrix 		= QuaternionMakeMatrixSR;
	_PLE_lib_VariableN __QuaternionMakeMatrix__PL__       PLSysAPI_Math_QuaternionMakeMatrixN 		= QuaternionMakeMatrixR;
	_PLE_lib_VariableN __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4L 	= QuaternionMakeMatrix4x4SL;
	_PLE_lib_VariableN __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4NL 	= QuaternionMakeMatrix4x4L;
	_PLE_lib_VariableN __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4R 	= QuaternionMakeMatrix4x4SR;
	_PLE_lib_VariableN __QuaternionMakeMatrix4x4__PL__    PLSysAPI_Math_QuaternionMakeMatrix4x4NR 	= QuaternionMakeMatrix4x4R;

	_PLE_lib_VariableN __InitializNormalizMatrix3x3__PL__ PLSysAPI_Math_InitializNormalizMatrix3x3 = InitializNormalizMatrix3x3;
	_PLE_lib_VariableN __InitializNormalizMatrix4x4__PL__ PLSysAPI_Math_InitializNormalizMatrix4x4 = InitializNormalizMatrix4x4;
	_PLE_lib_VariableN __Matrix3x3Mul__PL__               PLSysAPI_Math_Matrix3x3Mul_Native = Matrix3x3Mul;
	_PLE_lib_VariableN __Matrix4x4Mul__PL__               PLSysAPI_Math_Matrix4x4Mul_Native = Matrix4x4Mul;
	_PLE_lib_VariableN __Matrix3x3Transpose__PL__		  PLSysAPI_Math_Matrix3x3Transpose  = Matrix3x3Transpose;
	_PLE_lib_VariableN __Matrix4x4Transpose__PL__		  PLSysAPI_Math_Matrix4x4Transpose  = Matrix4x4Transpose;
	_PLE_lib_VariableN __Matrix4x4TransformV__PL__	  	  PLSysAPI_Math_Matrix4x4TransformVL = Matrix4x4TransformVLL;
	_PLE_lib_VariableN __Matrix4x4TransformV__PL__	  	  PLSysAPI_Math_Matrix4x4TransformVR = Matrix4x4TransformVLR;

	_PLE_lib_VariableN __Matrix3x3Cofactor__PL__		  PLSysAPI_Math_Matrix3x3Cofactor	= Matrix3x3Cofactor;
	_PLE_lib_VariableN __Matrix3x3Determinant__PL__		  PLSysAPI_Math_Matrix3x3Determinant= Matrix3x3Determinant;
	_PLE_lib_VariableN __Matrix4x4Cofactor__PL__		  PLSysAPI_Math_Matrix4x4Cofactor	= Matrix4x4Cofactor;
	_PLE_lib_VariableN __Matrix4x4Determinant__PL__	  	  PLSysAPI_Math_Matrix4x4Determinant= Matrix4x4Determinant;
	_PLE_lib_VariableN __MatrixOb__PL__		 			  PLSysAPI_Math_MatrixOb 			= MatrixOb;
	_PLE_lib_VariableN __Matrix4x4Ob__PL__		 		  PLSysAPI_Math_Matrix4x4Ob			= Matrix4x4Ob;


	_PLE_lib_VariableN __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3XAxisRotationL = NULL_PL;
	_PLE_lib_VariableN __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3YAxisRotationL = NULL_PL;
	_PLE_lib_VariableN __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3ZAxisRotationL = NULL_PL;
	_PLE_lib_VariableN __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3XAxisRotationR = NULL_PL;
	_PLE_lib_VariableN __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3YAxisRotationR = NULL_PL;
	_PLE_lib_VariableN __Matrix3x3AxisRotation__PL__      PLSysAPI_Math_Matrix3x3ZAxisRotationR = NULL_PL;



	_PLE_lib_VariableN __VectorDot__PL__				  PLSysAPI_Math_VectorDot  	 = VectorDot;
	_PLE_lib_VariableN __VectorCorss__PL__				  PLSysAPI_Math_VectorCorssL = VectorCorssL;
	_PLE_lib_VariableN __VectorCorss__PL__				  PLSysAPI_Math_VectorCorssR = VectorCorssR;
	_PLE_lib_VariableN __Vector3Modulus__PL__			  PLSysAPI_Math_Vector3Modulus = Vector3Modulus;
	_PLE_lib_VariableN __Vector4Modulus__PL__			  PLSysAPI_Math_Vector4Modulus = Vector4Modulus;
	_PLE_lib_VariableN __Vector3Normal__PL__			  PLSysAPI_Math_Vector3Normal  = Vector3Normal;
	_PLE_lib_VariableN __Vector4Normal__PL__			  PLSysAPI_Math_Vector4Normal  = Vector4Normal;

    void_pl InitializNormalizMatrix3x3(PLMatrix3x3 * ptrMart){
 	   ptrMart->m[0][0] = _FL_(1.0);
	   ptrMart->m[0][1] = _FL_(0.0);
	   ptrMart->m[0][2] = _FL_(0.0);

	   ptrMart->m[1][0] = _FL_(0.0);
	   ptrMart->m[1][1] = _FL_(1.0);
 	   ptrMart->m[1][2] = _FL_(0.0);

	   ptrMart->m[2][0] = _FL_(0.0);
 	   ptrMart->m[2][1] = _FL_(0.0);
	   ptrMart->m[2][2] = _FL_(1.0);
    }
    void_pl InitializNormalizMatrix4x4(PLMatrix4x4 * ptrMart){
	   ptrMart->m[0][0] = _FL_(1.0);
	   ptrMart->m[0][1] = _FL_(0.0);
	   ptrMart->m[0][2] = _FL_(0.0);
	   ptrMart->m[0][3] = _FL_(0.0);

	   ptrMart->m[1][0] = _FL_(0.0);
	   ptrMart->m[1][1] = _FL_(1.0);
	   ptrMart->m[1][2] = _FL_(0.0);
	   ptrMart->m[1][3] = _FL_(0.0);

	   ptrMart->m[2][0] = _FL_(0.0);
	   ptrMart->m[2][1] = _FL_(0.0);
	   ptrMart->m[2][2]= _FL_(1.0);
	   ptrMart->m[2][3]= _FL_(0.0);

	   ptrMart->m[3][0]= _FL_(0.0);
	   ptrMart->m[3][1]= _FL_(0.0);
	   ptrMart->m[3][2]= _FL_(0.0);
	   ptrMart->m[3][3]= _FL_(1.0);
    }
   //compute Vector's Modulus
   float_pl Vector3Modulus(const_pl PLVector3 * v){
	   return PLSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    }
   float_pl Vector4Modulus(const_pl PLVector4 * v){
	   return PLSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z) / v->w;
    }
   //compute Vector Normalization
   void_pl Vector3Normal(PLVector3 * ptrVOut,const_pl PLVector3 * v){
		float_pl  Modulus;
		Modulus = _FL_(1.0) / PLSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
		ptrVOut->x *= Modulus;
		ptrVOut->y *= Modulus;
		ptrVOut->z *= Modulus;
    }
   void_pl Vector4Normal(PLVector4 * ptrVOut,const_pl PLVector4 * v){
		float_pl  Modulus;
		Modulus = _FL_(1.0) / (PLSysAPI_Sqrt(v->x * v->x + v->y * v->y + v->z * v->z)*ptrVOut->w);
		ptrVOut->x *= Modulus;
		ptrVOut->y *= Modulus;
		ptrVOut->z *= Modulus;
		ptrVOut->w  = _FL_(1.0);
    }
  /* if unit Vector
   * cos(angle) = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z
   * if no unit Vector
   * |v1||v2|cos(angle) = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z
    * */
   float_pl VectorDot(const_pl PLVector3 * ptr1,const_pl PLVector3 * ptr2){
		  return ptr1->x*ptr2->x + ptr1->y*ptr2->y + ptr1->z*ptr2->z;
    }

   /*
   * x = v2.y*v1.z - v1.y*v2.z
   * y = v2.z*v1.x - v1.z*v2.x
   * z = v2.x*v1.y - v1.x*v2.y
   * CorssV = |v2|*|v1|*sin(angle)*n
   * Vector Clockwise Sort ,Corss Vector Pointer To Your (in to out)
   */
   void_pl VectorCorssL(PLVector3 * ptrOut,const_pl PLVector3 * ptr1,const_pl PLVector3 * ptr2){
	   PLVector3 vOut;
	   vOut.x = ptr2->y*ptr1->z - ptr1->y*ptr2->z;
	   vOut.y = ptr2->z*ptr1->x - ptr1->z*ptr2->x;
	   vOut.z = ptr2->x*ptr1->y - ptr1->x*ptr2->y;
	   *ptrOut=vOut;


   }
   /*
   * x = v1.y*v2.z - v2.y*v1.z
   * y = v1.z*v2.x - v2.z*v1.x
   * z = v1.x*v2.y - v2.x*v1.y
   * CorssV = |v1|*|v2|*sin(angle)*n
   * Vector Clockwise Sort ,Corss Vector Pointer To Your (in to out)
    */
   _CallStack_default_ void_pl VectorCorssR(PLVector3 * ptrOut,const_pl PLVector3 * ptr1,const_pl PLVector3 * ptr2){
	   PLVector3 vOut;
	   vOut.x = ptr1->y*ptr2->z - ptr2->y*ptr1->z;
	   vOut.y = ptr1->z*ptr2->x - ptr2->z*ptr1->x;
	   vOut.z = ptr1->x*ptr2->y - ptr2->x*ptr1->y;
	   *ptrOut=vOut;
   }

   void_pl InitializQuaternion(PLQuaternion * ptrResults){
	   make_Quaternion(ptrResults,_FL_(1.0),_FL_(0.0),_FL_(0.0),_FL_(0.0));
   }
   //(Rotation Axis)'s Value and (Rotation angle) make Quaternion
   void_pl make_Quaternion(PLQuaternion * ptrResults,float_pl fAxisX,float_pl fAxisY,float_pl fAxisZ,float_pl Radian){
	   float_pl halfRadian;
	   halfRadian = Radian*_FL_(0.5);
		ptrResults->w = sf_cosf32(halfRadian);
		halfRadian = sf_sinf32(halfRadian);
		ptrResults->x = fAxisX * halfRadian;
		ptrResults->y = fAxisY * halfRadian;
		ptrResults->z = fAxisZ * halfRadian;
    }
    //two Quaternion Add
   void_pl QuaternionAdd(PLQuaternion * ptrResults,const PLQuaternion * ptrFirst,const PLQuaternion * ptrSecond){
	   ptrResults->w = ptrFirst->w + ptrSecond->w;
	   ptrResults->x = ptrFirst->x + ptrSecond->x;
	   ptrResults->y = ptrFirst->y + ptrSecond->y;
	   ptrResults->z = ptrFirst->z + ptrSecond->z;
    }
   //Results = (q1.w * q2.w + (q1.xyz dot q2.xyz)) , q1.w * q2.xyz + q2.w * q1.xyz + (q2.xyz cross q1.xyz))
   void_pl QuaternionMul(PLQuaternion * ptrResults,const PLQuaternion * ptrFirst,const PLQuaternion * ptrSecond){
	   PLQuaternion q;
	   q = *ptrFirst;
	   ptrResults->w = q.w * ptrSecond->w - q.x * ptrSecond->x - q.y * ptrSecond->y  - q.z * ptrSecond->z;
	   ptrResults->x = q.w * ptrSecond->x + q.x * ptrSecond->w + (q.y * ptrSecond->z - ptrSecond->y * q.z);
	   ptrResults->y = q.w * ptrSecond->y + q.y * ptrSecond->w + (q.z * ptrSecond->x - ptrSecond->z * q.x);
	   ptrResults->z = q.w * ptrSecond->z + q.z * ptrSecond->w + (q.x * ptrSecond->y - ptrSecond->x * q.y);
    }
    //Results = q1 dot q2
   float_pl QuaternionDot(PLQuaternion * ptrFirst,const_pl PLQuaternion * ptrSecond){
		return ptrFirst->w * ptrSecond->w + ptrFirst->x * ptrSecond->x + ptrFirst->y * ptrSecond->y + ptrFirst->z * ptrSecond->z;
    }
    //Results = sqrt( q1 dot q1)		Quaternion m_TestModelZQ;
   float_pl QuaternionModulus(const_pl PLQuaternion * ptrFirst){
	   return PLSysAPI_Sqrt(ptrFirst->x * ptrFirst->x + ptrFirst->y * ptrFirst->y + ptrFirst->z * ptrFirst->z + ptrFirst->w * ptrFirst->w);
	}
   //Results = q1 / modulus (compute QUaternion normalization)
   void_pl QuaternionNormal(PLQuaternion * ptrOut,const_pl PLQuaternion * ptrFirst){
	    float_pl fModulus;
		fModulus = _FL_(1.0)/QuaternionModulus(ptrFirst);
		ptrOut->w *= fModulus;
		ptrOut->x *= fModulus;
		ptrOut->y *= fModulus;
		ptrOut->z *= fModulus;
    }
    //((w , v) * (w, -v)) = (Modulus)*(Modulus)
   //Quaternion Reciprocal =  (w , - v ) / ((w , v) * (w, -v))
   void_pl QuaternionReciprocal(PLQuaternion * ptrRecipOut,const PLQuaternion * ptrFirst){
		float_pl fModulusx2;
		fModulusx2 = ptrFirst->w * ptrFirst->w + ptrFirst->x * ptrFirst->x + ptrFirst->y * ptrFirst->y + ptrFirst->z * ptrFirst->z;
		fModulusx2 = _FL_(1.0) / fModulusx2;
		ptrRecipOut->w = ptrFirst->w * fModulusx2;
		ptrRecipOut->x = -(ptrFirst->x * fModulusx2);
		ptrRecipOut->y = -(ptrFirst->y * fModulusx2);
		ptrRecipOut->z = -(ptrFirst->z * fModulusx2);
    }
   //  right Coord
   //  [ w*w+x*x-y*y-z*z , 2xy-2wz , 2xz+2wy ]
   //  [ 2xy+2wz , w*w-x*x-y*y-z*z , 2yz-2wx ]
   //  [ 2xz-2wy , 2yz+2wx , w*w-x*x-y*y-z*z ]
   void_pl QuaternionMakeMatrixSR(PLMatrix3x3 * ptrOut,const_pl PLQuaternion * ptrInput){
	   ptrOut->m[0][0] = ptrInput->w * ptrInput->w + ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
    }

   //  if Unit Quaternion
   //  [ 1-2(y*y)-2(z*z) , 2xy-2wz , 2xz+2wy ]
   //  [ 2xy+2wz , 1-2(x*x)-2(z*z) , 2yz-2wx ]
   //  [ 2xz-2wy , 2yz+2wx , 1-2(x*x)-2(y*y) ]
   void_pl QuaternionMakeMatrixR(PLMatrix3x3 * ptrOut,const_pl PLQuaternion * ptrInput){
	   ptrOut->m[0][0] = _FL_(1.0) - _FL_(2.0)*(ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z);
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->z * ptrInput->z);
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y);
    }

   void_pl QuaternionMakeMatrix4x4SL(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov){
	   ptrOut->m[0][0] = ptrInput->w * ptrInput->w + ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;

   }

   void_pl QuaternionMakeMatrix4x4L(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov){
	   ptrOut->m[0][0] = _FL_(1.0) - _FL_(2.0)*(ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z);
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[0][3] = _FL_(0.0);

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->z * ptrInput->z);
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);
	   ptrOut->m[1][3] = _FL_(0.0);

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y);
	   ptrOut->m[2][3] = _FL_(0.0);

	   ptrOut->m[3][0] = ptrMov->x;
	   ptrOut->m[3][1] = ptrMov->y;
	   ptrOut->m[3][2] = ptrMov->z;
	   ptrOut->m[3][3] = _FL_(1.0);
   }
   void_pl QuaternionMakeMatrix4x4SR(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov){
	   ptrOut->m[0][0] = ptrInput->w * ptrInput->w + ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[0][3] = ptrMov->x;

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);
	   ptrOut->m[1][3] = ptrMov->y;

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = ptrInput->w * ptrInput->w - ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z;
	   ptrOut->m[2][3] = ptrMov->z;

	   ptrOut->m[3][0] = _FL_(0.0);
	   ptrOut->m[3][1] = _FL_(0.0);
	   ptrOut->m[3][2] = _FL_(0.0);
	   ptrOut->m[3][3] = _FL_(1.0);
   }
   void_pl QuaternionMakeMatrix4x4R(PLMatrix4x4 * ptrOut,const_pl PLQuaternion * ptrInput,const_pl PLVector4 * ptrMov){
	   ptrOut->m[0][0] = _FL_(1.0) - _FL_(2.0)*(ptrInput->y * ptrInput->y - ptrInput->z * ptrInput->z);
	   ptrOut->m[0][1] = _FL_(2.0)*(ptrInput->x * ptrInput->y - ptrInput->w * ptrInput->z);
	   ptrOut->m[0][2] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[0][3] = ptrMov->x;

	   ptrOut->m[1][0] = _FL_(2.0)*(ptrInput->x * ptrInput->y + ptrInput->w * ptrInput->z);
	   ptrOut->m[1][1] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->z * ptrInput->z);
	   ptrOut->m[1][2] = _FL_(2.0)*(ptrInput->y * ptrInput->z - ptrInput->w * ptrInput->x);
	   ptrOut->m[1][3] = ptrMov->y;

	   ptrOut->m[2][0] = _FL_(2.0)*(ptrInput->x * ptrInput->z + ptrInput->w * ptrInput->y);
	   ptrOut->m[2][1] = _FL_(2.0)*(ptrInput->y * ptrInput->z + ptrInput->w * ptrInput->x);
	   ptrOut->m[2][2] = _FL_(1.0) - _FL_(2.0)*(ptrInput->x * ptrInput->x - ptrInput->y * ptrInput->y);
	   ptrOut->m[2][3] = ptrMov->z;

	   ptrOut->m[3][0] = _FL_(0.0);
	   ptrOut->m[3][1] = _FL_(0.0);
	   ptrOut->m[3][2] = _FL_(0.0);
	   ptrOut->m[3][3] = _FL_(1.0);
   }
   void_pl Matrix3x3To4x4L(PLMatrix4x4 * ptrOut,const PLMatrix3x3 * ptrInput,const PLVector4 * ptrMov){
	   ptrOut->m[0][0] = ptrInput->m[0][0];
	   ptrOut->m[0][1] = ptrInput->m[0][1];
	   ptrOut->m[0][2] = ptrInput->m[0][2];
	   ptrOut->m[0][3] = _FL_(0.0);

	   ptrOut->m[1][0] = ptrInput->m[1][0];
	   ptrOut->m[1][1] = ptrInput->m[1][1];
	   ptrOut->m[1][2] = ptrInput->m[1][2];
	   ptrOut->m[1][3] = _FL_(0.0);

	   ptrOut->m[2][0] = ptrInput->m[2][0];
	   ptrOut->m[2][1] = ptrInput->m[2][1];
	   ptrOut->m[2][2]= ptrInput->m[2][2];
	   ptrOut->m[2][3]= _FL_(0.0);

	   ptrOut->m[3][0]= ptrMov->x;
	   ptrOut->m[3][1]= ptrMov->y;
	   ptrOut->m[3][2]= ptrMov->z;
	   ptrOut->m[3][3]= ptrMov->w;
    }
   void_pl Matrix3x3To4x4R(PLMatrix4x4 * ptrOut,const PLMatrix3x3 * ptrInput,const PLVector4 * ptrMov){
	   PLMatrix4x4 martOut;
	   martOut.m[0][0] = ptrInput->m[0][0];
	   martOut.m[0][1] = ptrInput->m[0][1];
	   martOut.m[0][2] = ptrInput->m[0][2];
	   martOut.m[0][3] = ptrMov->x;

	   martOut.m[1][0] = ptrInput->m[1][0];
	   martOut.m[1][1] = ptrInput->m[1][1];
	   martOut.m[1][2] = ptrInput->m[1][2];
	   martOut.m[1][3] = ptrMov->y;

	   martOut.m[2][0] = ptrInput->m[2][0];
	   martOut.m[2][1] = ptrInput->m[2][1];
	   martOut.m[2][2] = ptrInput->m[2][2];
	   martOut.m[2][3] = ptrMov->z;

	   martOut.m[3][0]= _FL_(0.0);
	   martOut.m[3][1]= _FL_(0.0);
	   martOut.m[3][2]= _FL_(0.0);
	   martOut.m[3][3]= ptrMov->w;
	   (*ptrOut) = martOut;

    }
   void_pl Matrix3x3To4x4(PLMatrix4x4 * ptrOut,const PLMatrix3x3 * ptrInput){
	   PLMatrix4x4 martOut;
	   martOut.m[0][0] = ptrInput->m[0][0];
	   martOut.m[0][1] = ptrInput->m[0][1];
	   martOut.m[0][2] = ptrInput->m[0][2];
	   martOut.m[0][3] = _FL_(0.0);

	   martOut.m[1][0] = ptrInput->m[1][0];
	   martOut.m[1][1] = ptrInput->m[1][1];
	   martOut.m[1][2] = ptrInput->m[1][2];
	   martOut.m[1][3] = _FL_(0.0);

	   martOut.m[2][0] = ptrInput->m[2][0];
	   martOut.m[2][1] = ptrInput->m[2][1];
	   martOut.m[2][2] = ptrInput->m[2][2];
	   martOut.m[2][3] = _FL_(0.0);

	   martOut.m[3][0] = _FL_(0.0);
	   martOut.m[3][1] = _FL_(0.0);
	   martOut.m[3][2] = _FL_(0.0);
	   martOut.m[3][3] = _FL_(1.0);
	   (*ptrOut) = martOut;
    }


   // Interval  =  (Q0(begin) of Reciprocal)  mul (Q1(end))
   void_pl QuaternionInterval(PLQuaternion * ptrOut,const PLQuaternion * ptrBegin,const PLQuaternion * ptrEnd){
	   ptrOut->w = ptrBegin->w;
	   ptrOut->y = -ptrBegin->y;
	   ptrOut->x = -ptrBegin->x;
	   ptrOut->z = -ptrBegin->z;
	   QuaternionMul(ptrOut,ptrOut,ptrEnd);
    }
    void_pl QuaternionSlerp(PLQuaternion * ptrOut,const_pl PLQuaternion * ptrBegin,const_pl PLQuaternion * ptrEnd,float_pl fSlerp){

    }

   //Matrix mul compute
    void_pl Matrix3x3Mul(PLMatrix3x3 * ptrOut,const_pl PLMatrix3x3 * ptrMart1,const_pl PLMatrix3x3 * ptrMart2){
		PLMatrix3x3 martOut;
		martOut.m[0][0] = ptrMart1->m[0][0]*ptrMart2->m[0][0] + ptrMart1->m[0][1]*ptrMart2->m[1][0] + ptrMart1->m[0][2]*ptrMart2->m[2][0];
		martOut.m[0][1] = ptrMart1->m[0][0]*ptrMart2->m[0][1] + ptrMart1->m[0][1]*ptrMart2->m[1][1] + ptrMart1->m[0][2]*ptrMart2->m[2][1];
		martOut.m[0][2] = ptrMart1->m[0][0]*ptrMart2->m[0][2] + ptrMart1->m[0][1]*ptrMart2->m[1][2] + ptrMart1->m[0][2]*ptrMart2->m[2][2];

		martOut.m[1][0] = ptrMart1->m[1][0]*ptrMart2->m[0][0] + ptrMart1->m[1][1]*ptrMart2->m[1][0] + ptrMart1->m[1][2]*ptrMart2->m[2][0];
		martOut.m[1][1] = ptrMart1->m[1][0]*ptrMart2->m[0][1] + ptrMart1->m[1][1]*ptrMart2->m[1][1] + ptrMart1->m[1][2]*ptrMart2->m[2][1];
		martOut.m[1][2] = ptrMart1->m[1][0]*ptrMart2->m[0][2] + ptrMart1->m[1][1]*ptrMart2->m[1][2] + ptrMart1->m[1][2]*ptrMart2->m[2][2];

		martOut.m[2][0] = ptrMart1->m[2][0]*ptrMart2->m[0][0] + ptrMart1->m[2][1]*ptrMart2->m[1][0] + ptrMart1->m[2][2]*ptrMart2->m[2][0];
		martOut.m[2][1] = ptrMart1->m[2][0]*ptrMart2->m[0][1] + ptrMart1->m[2][1]*ptrMart2->m[1][1] + ptrMart1->m[2][2]*ptrMart2->m[2][1];
		martOut.m[2][2] = ptrMart1->m[2][0]*ptrMart2->m[0][2] + ptrMart1->m[2][1]*ptrMart2->m[1][2] + ptrMart1->m[2][2]*ptrMart2->m[2][2];
		*ptrOut = martOut;
	}
    void_pl Matrix4x4Mul(PLMatrix4x4 * ptrOut,const_pl PLMatrix4x4 * ptrMart1,const_pl PLMatrix4x4 * ptrMart2){
		PLMatrix4x4 martOut;
		martOut.m[0][0]  = ptrMart1->m[0][0]*ptrMart2->m[0][0] + ptrMart1->m[0][1]*ptrMart2->m[1][0] + ptrMart1->m[0][2]*ptrMart2->m[2][0] + ptrMart1->m[0][3]*ptrMart2->m[3][0];
		martOut.m[0][1]  = ptrMart1->m[0][0]*ptrMart2->m[0][1] + ptrMart1->m[0][1]*ptrMart2->m[1][1] + ptrMart1->m[0][2]*ptrMart2->m[2][1] + ptrMart1->m[0][3]*ptrMart2->m[3][1];
		martOut.m[0][2]  = ptrMart1->m[0][0]*ptrMart2->m[0][2] + ptrMart1->m[0][1]*ptrMart2->m[1][2] + ptrMart1->m[0][2]*ptrMart2->m[2][2] + ptrMart1->m[0][3]*ptrMart2->m[3][2];
		martOut.m[0][3]  = ptrMart1->m[0][0]*ptrMart2->m[0][3] + ptrMart1->m[0][1]*ptrMart2->m[1][3] + ptrMart1->m[0][2]*ptrMart2->m[2][3] + ptrMart1->m[0][3]*ptrMart2->m[3][3];

		martOut.m[1][0]  = ptrMart1->m[1][0]*ptrMart2->m[0][0] + ptrMart1->m[1][1]*ptrMart2->m[1][0] + ptrMart1->m[1][2]*ptrMart2->m[2][0] + ptrMart1->m[1][3]*ptrMart2->m[3][0];
		martOut.m[1][1]  = ptrMart1->m[1][0]*ptrMart2->m[0][1] + ptrMart1->m[1][1]*ptrMart2->m[1][1] + ptrMart1->m[1][2]*ptrMart2->m[2][1] + ptrMart1->m[1][3]*ptrMart2->m[3][1];
		martOut.m[1][2]  = ptrMart1->m[1][0]*ptrMart2->m[0][2] + ptrMart1->m[1][1]*ptrMart2->m[1][2] + ptrMart1->m[1][2]*ptrMart2->m[2][2] + ptrMart1->m[1][3]*ptrMart2->m[3][2];
		martOut.m[1][3]  = ptrMart1->m[1][0]*ptrMart2->m[0][3] + ptrMart1->m[1][1]*ptrMart2->m[1][3] + ptrMart1->m[1][2]*ptrMart2->m[2][3] + ptrMart1->m[1][3]*ptrMart2->m[3][3];

		martOut.m[2][0]  = ptrMart1->m[2][0]*ptrMart2->m[0][0] + ptrMart1->m[2][1]*ptrMart2->m[1][0] + ptrMart1->m[2][2]*ptrMart2->m[2][0] + ptrMart1->m[2][3]*ptrMart2->m[3][0];
		martOut.m[2][1]  = ptrMart1->m[2][0]*ptrMart2->m[0][1] + ptrMart1->m[2][1]*ptrMart2->m[1][1] + ptrMart1->m[2][2]*ptrMart2->m[2][1] + ptrMart1->m[2][3]*ptrMart2->m[3][1];
		martOut.m[2][2]  = ptrMart1->m[2][0]*ptrMart2->m[0][2] + ptrMart1->m[2][1]*ptrMart2->m[1][2] + ptrMart1->m[2][2]*ptrMart2->m[2][2] + ptrMart1->m[2][3]*ptrMart2->m[3][2];
		martOut.m[2][3]  = ptrMart1->m[2][0]*ptrMart2->m[0][3] + ptrMart1->m[2][1]*ptrMart2->m[1][3] + ptrMart1->m[2][2]*ptrMart2->m[2][3] + ptrMart1->m[2][3]*ptrMart2->m[3][3];

		martOut.m[3][0]  = ptrMart1->m[3][0]*ptrMart2->m[0][0] + ptrMart1->m[3][1]*ptrMart2->m[1][0] + ptrMart1->m[3][2]*ptrMart2->m[2][0] + ptrMart1->m[3][3]*ptrMart2->m[3][0];
		martOut.m[3][1]  = ptrMart1->m[3][0]*ptrMart2->m[0][1] + ptrMart1->m[3][1]*ptrMart2->m[1][1] + ptrMart1->m[3][2]*ptrMart2->m[2][1] + ptrMart1->m[3][3]*ptrMart2->m[3][1];
		martOut.m[3][2]  = ptrMart1->m[3][0]*ptrMart2->m[0][2] + ptrMart1->m[3][1]*ptrMart2->m[1][2] + ptrMart1->m[3][2]*ptrMart2->m[2][2] + ptrMart1->m[3][3]*ptrMart2->m[3][2];
		martOut.m[3][3]  = ptrMart1->m[3][0]*ptrMart2->m[0][3] + ptrMart1->m[3][1]*ptrMart2->m[1][3] + ptrMart1->m[3][2]*ptrMart2->m[2][3] + ptrMart1->m[3][3]*ptrMart2->m[3][3];
		*ptrOut = martOut;
	}
	//Transpose 3x3 Matrix
    void_pl Matrix3x3Transpose(PLMatrix3x3 * ptrOut,const PLMatrix3x3 * ptrInput){
		PLMatrix3x3 martOut;
		martOut.m[0][0] = ptrInput->m[0][0];
		martOut.m[0][1] = ptrInput->m[1][0];
		martOut.m[0][2] = ptrInput->m[2][0];
		martOut.m[1][0] = ptrInput->m[0][1];
		martOut.m[1][1] = ptrInput->m[1][1];
		martOut.m[1][2] = ptrInput->m[2][1];
		martOut.m[2][0] = ptrInput->m[0][2];
		martOut.m[2][1] = ptrInput->m[1][2];
		martOut.m[2][2] = ptrInput->m[2][2];
		*ptrOut = martOut;
	}
	//Transpose 4x4 Matrix
    void_pl Matrix4x4Transpose(PLMatrix4x4 * ptrOut,const PLMatrix4x4 * ptrInput){
		PLMatrix4x4 martOut;
		martOut.m[0][0] = ptrInput->m[0][0];
		martOut.m[0][1] = ptrInput->m[1][0];
		martOut.m[0][2] = ptrInput->m[2][0];
		martOut.m[0][3] = ptrInput->m[3][0];

		martOut.m[1][0] = ptrInput->m[0][1];
		martOut.m[1][1] = ptrInput->m[1][1];
		martOut.m[1][2] = ptrInput->m[2][1];
		martOut.m[1][3] = ptrInput->m[3][1];

		martOut.m[2][0] = ptrInput->m[0][2];
		martOut.m[2][1] = ptrInput->m[1][2];
		martOut.m[2][2] = ptrInput->m[2][2];
		martOut.m[2][3] = ptrInput->m[3][2];

		martOut.m[3][0] = ptrInput->m[0][3];
		martOut.m[3][1] = ptrInput->m[1][3];
		martOut.m[3][2] = ptrInput->m[2][3];
		martOut.m[3][3] = ptrInput->m[3][3];
		*ptrOut = martOut;
	}
	//Input Vector Transform to Matrix Space of Coord
    void_pl Matrix4x4TransformVLL(PLVector4 * ptrOut,const_pl PLMatrix4x4 * ptrTransform,const_pl PLVector4 * ptrInput){
		PLVector4 vResult;
		vResult.x = ptrInput->x*ptrTransform->m[0][0] + ptrInput->y*ptrTransform->m[1][0] + ptrInput->z*ptrTransform->m[2][0] + ptrInput->w*ptrTransform->m[3][0];
		vResult.y = ptrInput->x*ptrTransform->m[0][1] + ptrInput->y*ptrTransform->m[1][1] + ptrInput->z*ptrTransform->m[2][1] + ptrInput->w*ptrTransform->m[3][1];
		vResult.z = ptrInput->x*ptrTransform->m[0][2] + ptrInput->y*ptrTransform->m[1][2] + ptrInput->z*ptrTransform->m[2][2] + ptrInput->w*ptrTransform->m[3][2];
		vResult.w = ptrInput->x*ptrTransform->m[0][3] + ptrInput->y*ptrTransform->m[1][3] + ptrInput->z*ptrTransform->m[2][3] + ptrInput->w*ptrTransform->m[3][3];
		vResult.w = _FL_(1.0)/vResult.w;
		vResult.x *= vResult.w;
		vResult.y *= vResult.w;
		vResult.z *= vResult.w;
		vResult.w = _FL_(1.0);
		*ptrOut = vResult;
	}
    void_pl Matrix4x4TransformVLR(PLVector4 * ptrOut,const_pl PLMatrix4x4 * ptrTransform,const_pl PLVector4 * ptrInput){
		PLVector4 vResult;
		vResult.x = ptrTransform->m[0][0]*ptrInput->x + ptrTransform->m[0][1]*ptrInput->y + ptrTransform->m[0][2]*ptrInput->z + ptrTransform->m[0][3]*ptrInput->w;
		vResult.y = ptrTransform->m[1][0]*ptrInput->x + ptrTransform->m[1][1]*ptrInput->y + ptrTransform->m[1][2]*ptrInput->z + ptrTransform->m[1][3]*ptrInput->w;
		vResult.z = ptrTransform->m[2][0]*ptrInput->x + ptrTransform->m[2][1]*ptrInput->y + ptrTransform->m[2][2]*ptrInput->z + ptrTransform->m[2][3]*ptrInput->w;
		vResult.w = ptrTransform->m[3][0]*ptrInput->x + ptrTransform->m[3][1]*ptrInput->y + ptrTransform->m[3][2]*ptrInput->z + ptrTransform->m[3][3]*ptrInput->w;
		vResult.w = _FL_(1.0)/vResult.w;
		vResult.x *= vResult.w;
		vResult.y *= vResult.w;
		vResult.z *= vResult.w;
		vResult.w = _FL_(1.0);
		*ptrOut=vResult;
	}
    void_pl Matrix3x3Cofactor(PLMatrix3x3 * ptrOut,const_pl PLMatrix3x3 * ptrMat){
    	PLMatrix3x3 martResult;
    	martResult.m[0][0] = ptrMat->m[1][1] * ptrMat->m[2][2] - ptrMat->m[1][2] * ptrMat->m[2][1];
    	martResult.m[0][1] = -ptrMat->m[1][0] * ptrMat->m[2][2] + ptrMat->m[1][2] * ptrMat->m[2][0];
    	martResult.m[0][2] = ptrMat->m[1][0] * ptrMat->m[2][1] - ptrMat->m[1][1] * ptrMat->m[2][0];

    	martResult.m[1][0] = -(ptrMat->m[0][1] * ptrMat->m[2][2] - ptrMat->m[0][2] * ptrMat->m[2][1]);
    	martResult.m[1][1] = ptrMat->m[0][0] * ptrMat->m[2][2] - ptrMat->m[0][2] * ptrMat->m[2][0];
    	martResult.m[1][2] = -(ptrMat->m[0][0] * ptrMat->m[2][1] - ptrMat->m[0][1] * ptrMat->m[2][0]);

    	martResult.m[2][0] = ptrMat->m[0][1] * ptrMat->m[1][2] - ptrMat->m[0][2] * ptrMat->m[1][1];
    	martResult.m[2][1] = -ptrMat->m[0][0] * ptrMat->m[1][2] + ptrMat->m[0][2] * ptrMat->m[1][0];
    	martResult.m[2][2] = ptrMat->m[0][0] * ptrMat->m[1][1] - ptrMat->m[0][1] * ptrMat->m[1][0];
    	*ptrOut = martResult;
    }
    float_pl Matrix3x3Determinant(const_pl PLMatrix3x3 * ptrMat){

    	return _FL_(0.0);
    }
    void_pl Matrix4x4Cofactor(PLMatrix4x4 * ptrOut,const_pl PLMatrix4x4 * ptrMat){
    	PLMatrix4x4 martResult;

    }
    float_pl Matrix4x4Determinant(const_pl PLMatrix4x4 * ptrMat){
    	return _FL_(0.0);
    }

    void_pl MatrixOb(PLMatrix3x3 * ptrOut,const_pl PLMatrix3x3 * ptrMat){

    }
    void_pl Matrix4x4Ob(PLMatrix4x4 * ptrOut,const_pl PLMatrix4x4 * ptrMat){

    }


	/*
	 *  [ cos(radian) , sin(radian) , 0.0 ]
	 *  [ -sin(radian), cos(radian) , 0.0 ]
	 *  [ 0.0         ,  0.0    	, 1.0 ]
	 */
    void_pl Matrix3x3ZAxisRotationL(PLMatrix3x3 * ptrOut,float_pl fRadian){
		ptrOut->m[0][0] = sf_cosf32(fRadian);
		ptrOut->m[0][1] = sf_sinf32(fRadian);
		ptrOut->m[0][2] = _FL_(0.0);

		ptrOut->m[1][0] = -sf_sinf32(fRadian);
		ptrOut->m[1][1] = sf_cosf32(fRadian);
		ptrOut->m[1][2] = _FL_(0.0);

		ptrOut->m[2][0] = _FL_(0.0);
		ptrOut->m[2][1] = _FL_(0.0);
		ptrOut->m[2][2] = _FL_(1.0);
	}
	/*
	 *  [cos(radian), 0.0 , -sin(radian)]
	 *  [sin(radian), 0.0 , cos(radian) ]
	 *  [0.0        , 1.0 ,  0.0        ]
	 */
    void_pl Matrix3x3YAxisRotationL(PLMatrix3x3 * ptrOut,float_pl fRadian){
		ptrOut->m[0][0] = sf_cosf32(fRadian);
		ptrOut->m[0][1] = _FL_(0.0);
		ptrOut->m[0][2] = -sf_sinf32(fRadian);

		ptrOut->m[1][0] = _FL_(0.0);
		ptrOut->m[1][1] = _FL_(1.0);
	    ptrOut->m[1][2] = _FL_(0.0);

	    ptrOut->m[2][0] = sf_sinf32(fRadian);
	    ptrOut->m[2][1] = _FL_(0.0);
	    ptrOut->m[2][2] = sf_cosf32(fRadian);
	}
	/*
	 * [1.0 ,  0.0         , 0.0         ]
	 * [0.0 , cos(radian)  , sin(radian) ]
	 * [0.0 , -sin(radian) , cos(radian) ]
	 */
    void_pl Matrix3x3XAxisRotationL(PLMatrix3x3 * ptrOut,float_pl fRadian){
		ptrOut->m[0][0] = _FL_(1.0);
		ptrOut->m[0][1] = _FL_(0.0);
		ptrOut->m[0][2] = _FL_(0.0);

		ptrOut->m[1][0] = _FL_(0.0);
		ptrOut->m[1][1] = sf_cosf32(fRadian);
		ptrOut->m[1][2] = sf_sinf32(fRadian);

		ptrOut->m[2][0] = _FL_(0.0);
		ptrOut->m[2][1] = -sf_sinf32(fRadian);
		ptrOut->m[2][2] = sf_cosf32(fRadian);
	}
	/*
	 *  [ 1.0  ,  0.0         ,  0.0 		 ]
	 *  [ 0.0  ,  cos(radian) , -sin(radian) ]
	 *  [ 0.0  ,  sin(radian) , cos(radian)  ]
	 */
    void_pl Matrix3x3XAxisRotationR(PLMatrix3x3 * ptrOut,float_pl fRadian){
		Matrix3x3XAxisRotationL(ptrOut,fRadian);
		Matrix3x3Transpose(ptrOut,ptrOut);
	}
	/*
	 *  [cos(radian), 0.0 ,  sin(radian) ]
	 *  [0.0        , 1.0 ,  0.0    	 ]
	 *  [-sin(radian), 0.0 , cos(radian) ]
     *
	 */
    void_pl Matrix3x3YAxisRotationR(PLMatrix3x3 * ptrOut,float_pl fRadian){
		Matrix3x3YAxisRotationL(ptrOut,fRadian);
		Matrix3x3Transpose(ptrOut,ptrOut);
	}
	/*
	 * [cos(radian), -sin(radian) , 0.0 ]
	 * [sin(radian), cos(radian)  , 0.0 ]
	 * [0.0        , 0.0		  , 1.0 ]
	 */
    void_pl Matrix3x3ZAxisRotationR(PLMatrix3x3 * ptrOut,float_pl fRadian){
		Matrix3x3ZAxisRotationL(ptrOut,fRadian);
		Matrix3x3Transpose(ptrOut,ptrOut);
	}

    void_pl Matrix3x3AxisRotation(PLMatrix3x3 * ptrOut,PLVector3 * ptrAix,float_pl fRadian){

    }


	bool_pl InitializDefaultMathLibraryPL(){
		//InitializNormalizMatrix3x3PL = InitializNormalizMatrix3x3;
		//InitializNormalizMatrix4x4PL = InitializNormalizMatrix4x4;
		/*make_Matrix4x4SPL;
		make_Matrix4x4PL;
		QuaternionSlerpPL;
		Matrix3x3MulPL;
		Matrix4x4MulPL;
		Matrix3x3AxisRotationPL;*/
		return true_pl;
	}



