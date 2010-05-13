///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/fetch.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_FETCH_INCLUDED
#define GLI_FETCH_INCLUDED

namespace gli
{
	template <typename genType>
	genType texelFetch(
		image const & Image, 
		glm::ivec2 const & TexCoord,
		image::level_type const & Level);

	template <typename genType>
	genType textureLod(
		image const & Image, 
		glm::vec2 const & TexCoord,
		image::level_type const & Level);

	template <typename genType>
	void texelWrite(
		image & Image,
		glm::uvec2 const & Texcoord,
		image::level_type const & Level,
		genType const & Color);

}//namespace gli

#include "fetch.inl"

#endif//GLI_FETCH_INCLUDED
