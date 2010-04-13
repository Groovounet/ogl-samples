///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/loader.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_LOADER_INCLUDED
#define GLI_LOADER_INCLUDED

#include "image.hpp"
#include "operation.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/number_precision.hpp"
#include "glm/gtx/bit.hpp"

#include <string>

namespace gli
{
	image import_as(
		std::string const & Filename);

	void export_as(
		image const & Image, 
		std::string const & Filename);

	void export_as(
		image const & Image,
		image::level_type const & Level,
		std::string const & Filename);
}

#include "loader.inl"

#endif//GLI_LOADER_INCLUDED
