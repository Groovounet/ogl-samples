///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2008-10-05
// Licence : This source is under MIT License
// File    : glm/gtx/double_float.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_double_float
// - GLM_GTX_quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////
// Note:
// - This implementation doesn't need to redefine all build-in functions to
// support double based type.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_double_float
#define glm_gtx_double_float

// Dependency:
#include "../glm.hpp"
#include "../gtc/double_float.hpp"
#include "../gtx/quaternion.hpp"

namespace glm
{
	namespace test{
		void main_gtx_double_float();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_double_float extension: Add support for double precision flotting-point types
	namespace double_float
	{
		using namespace gtc::double_float;

		//! Quaternion of single-precision floating-point numbers. 
		//! From GLM_GTX_double extension.
		typedef detail::tquat<float>	fquat;

		//! Quaternion of double-precision floating-point numbers. 
		//! From GLM_GTX_double extension.
		typedef detail::tquat<double>	dquat;

	}//namespace double_float
	}//namespace gtx
}//namespace glm

#include "double_float.inl"

namespace glm{using namespace gtx::double_float;}

#endif//glm_gtx_double_float
