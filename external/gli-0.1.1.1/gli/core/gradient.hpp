#ifndef GLI_GRADIENT_INCLUDED
#define GLI_GRADIENT_INCLUDED

#include "mipmap.hpp"

namespace gli
{
	mipmap radial(
		glm::uvec2 const & Size, 
		glm::vec2 const & Center,
		float const & Radius,
		glm::vec2 const & Focal);

	mipmap linear(
		glm::uvec2 const & Size, 
		glm::vec2 const & Point0, 
		glm::vec2 const & Point1);

}//namespace gli

#include "gradient.inl"

#endif//GLI_GRADIENT_INCLUDED
