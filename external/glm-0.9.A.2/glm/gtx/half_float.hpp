///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtx/half_float.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_half_float
// - GLM_GTX_quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_half_float
#define glm_gtx_half_float

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtx/quaternion.hpp"

namespace glm
{
	namespace test{
		void main_ext_gtx_half_float();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_half_float extension: Add support for half precision flotting-point types
	namespace half_float
	{
		using namespace gtc::half_float;
		using namespace gtx::quaternion;

		//! Quaternion of half-precision floating-point numbers.
		//! From GLM_GTX_half_float extension.
		typedef detail::tquat<detail::thalf>	hquat;

	}//namespace half_float
	}//namespace gtx
}//namespace glm

#include "half_float.inl"

namespace glm{using namespace gtx::half_float;}

#endif//glm_gtx_half_float
