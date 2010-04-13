///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/operation.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_OPERATION_INCLUDED
#define GLI_OPERATION_INCLUDED

#include "image.hpp"

namespace gli
{
	image duplicate(image const & Image);
	image flip(image const & Image);
	image mirror(image const & Image);
	image swizzle(
		image const & Image, 
		glm::uvec4 const & Channel);
	image crop(
		image const & Image, 
		glm::uvec2 const & Position,
		glm::uvec2 const & Size);

	image::mipmap crop(
		image::mipmap const & Mipmap, 
		glm::uvec2 const & Position,
		glm::uvec2 const & Size);

	image::mipmap copy(
		image::mipmap const & SrcMipmap, 
		glm::uvec2 const & SrcPosition,
		glm::uvec2 const & SrcSize,
		image::mipmap & DstMipmap, 
		glm::uvec2 const & DstPosition);

	//mipmap operator+(mipmap const & MipmapA, mipmap const & MipmapB);
	//mipmap operator-(mipmap const & MipmapA, mipmap const & MipmapB);
	//mipmap operator*(mipmap const & MipmapA, mipmap const & MipmapB);
	//mipmap operator/(mipmap const & MipmapA, mipmap const & MipmapB);

	namespace wip
	{
		template <typename GENTYPE, template <typename> class SURFACE>
		GENTYPE fetch(SURFACE<GENTYPE> const & Image)
		{
			return GENTYPE();
		}

		template
		<
			typename GENTYPE, 
			template 
			<
				typename
			>
			class SURFACE,
			template 
			<
				typename, 
				template 
				<
					typename
				>
				class
			> 
			class IMAGE
		>
		GENTYPE fetch(IMAGE<GENTYPE, SURFACE> const & Image)
		{
			return GENTYPE();
		}
	}//namespace wip

}//namespace gli

#include "operation.inl"

#endif//GLI_OPERATION_INCLUDED
