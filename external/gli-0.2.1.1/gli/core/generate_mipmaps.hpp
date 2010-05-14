#ifndef GLI_GENERATE_MIPMAPS_INCLUDED
#define GLI_GENERATE_MIPMAPS_INCLUDED

#include "image.hpp"

namespace gli
{
	image generateMipmaps(
		image const & Image, 
		image::level_type const & BaseLevel);

}//namespace gli

#include "generate_mipmaps.inl"

#endif//GLI_GENERATE_MIPMAPS_INCLUDED
