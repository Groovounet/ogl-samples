///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-12-19
// Updated : 2010-09-08
// Licence : This source is under MIT License
// File    : gli/core/size.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	inline texture2D::size_type size
	(
		image const & Mipmap,
		size_type const & SizeType
	)
	{
		switch(SizeType)
		{
		case LINEAR_SIZE:
			return detail::sizeLinear(Mipmap);
		case BLOCK_SIZE:
			return detail::sizeBlock(Mipmap.format());
		case BIT_PER_PIXEL:
			return detail::sizeBitPerPixel(Mipmap.format());
		case COMPONENT:
			return detail::sizeComponent(Mipmap.format());
		default:
			assert(0);
			return 0;
		};
	}

	inline texture2D::size_type size
	(
		texture2D const & Image,
		size_type const & SizeType
	)
	{
		switch(SizeType)
		{
		case LINEAR_SIZE:
			return detail::sizeLinear(Image);
		case BLOCK_SIZE:
			return detail::sizeBlock(Image.format());
		case BIT_PER_PIXEL:
			return detail::sizeBitPerPixel(Image.format());
		case COMPONENT:
			return detail::sizeComponent(Image.format());
		default:
			assert(0);
			return 0;
		};
	}

}//namespace
