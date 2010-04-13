#ifndef GLI_OPERATION_INCLUDED
#define GLI_OPERATION_INCLUDED

#include "image.hpp"

namespace gli
{
	image duplicate(image const & Image);
	image flip(image const & Image);
	image mirror(image const & Image);
	image crop(
		image const & Image, 
		glm::uvec2 const & Position,
		glm::uvec2 const & Size);

	mipmap duplicate(mipmap const & Mipmap);
	mipmap flip(mipmap const & Mipmap);
	mipmap mirror(mipmap const & Mipmap);
	mipmap crop(
		mipmap const & Mipmap, 
		glm::uvec2 const & Position,
		glm::uvec2 const & Size);

	mipmap copy(
		mipmap const & SrcMipmap, 
		glm::uvec2 const & SrcPosition,
		glm::uvec2 const & SrcSize,
		mipmap & DstMipmap, 
		glm::uvec2 const & DstPosition);

	mipmap swizzle(
		mipmap const & Mipmap, 
		glm::uvec4 const & Channel);

	//mipmap operator+(mipmap const & MipmapA, mipmap const & MipmapB);
	//mipmap operator-(mipmap const & MipmapA, mipmap const & MipmapB);
	//mipmap operator*(mipmap const & MipmapA, mipmap const & MipmapB);
	//mipmap operator/(mipmap const & MipmapA, mipmap const & MipmapB);

}//namespace gli

#include "operation.inl"

#endif//GLI_OPERATION_INCLUDED
