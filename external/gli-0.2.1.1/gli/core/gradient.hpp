///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/gradient.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_GRADIENT_INCLUDED
#define GLI_GRADIENT_INCLUDED

#include "image.hpp"

namespace gli
{
	image radial(
		glm::uvec2 const & Size, 
		glm::vec2 const & Center,
		float const & Radius,
		glm::vec2 const & Focal);

	image linear(
		glm::uvec2 const & Size, 
		glm::vec2 const & Point0, 
		glm::vec2 const & Point1);

}//namespace gli

#include "gradient.inl"

#endif//GLI_GRADIENT_INCLUDED
