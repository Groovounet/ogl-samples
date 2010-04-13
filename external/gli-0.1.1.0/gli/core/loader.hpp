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
	image loadImage(std::string const & Filename);

	void saveImage(image const & Image, std::string const & Filename);
}

#include "loader.inl"

#endif//GLI_LOADER_INCLUDED
