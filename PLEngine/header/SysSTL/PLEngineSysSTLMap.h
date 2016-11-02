/*
 * PLEngineSysSTLMap.h
 *
 *  Created on: 2010-3-5
 *      Author: DevLinux
 */
#include "../PLEngineH.h"
#include "../PLEngineBaseDataType.h"
#include "../PLEngineSysAPI.h"
#include "../PLEngineDefine.h"
#include "../PLEngineInface.h"
#include "../PLEngineMemoryPool.h"
#ifndef PLENGINESYSSTLMAP_H_
#define PLENGINESYSSTLMAP_H_
	template<typename _plstl_Key,typename _plstl_Node__>
	struct Aligned(8) __stl_RBMap_CmpFunc {
		inline bool_pl Priority(_plstl_Node__ * & key1,_plstl_Node__ * & key2){
			return false_pl;
		}
	}__Aligned(8);
	template <typename _plstl_Key,typename _plstl_Node__,typename _stldisposal_func = __stl_RBMap_CmpFunc<_plstl_Key , _plstl_Node__> >
	class __plstl_RBMap_class{
		public:
			__plstl_RBMap_class(){

			}
			virtual ~__plstl_RBMap_class(){

			}
		protected:

	};
#endif /* PLENGINESYSSTLMAP_H_ */
