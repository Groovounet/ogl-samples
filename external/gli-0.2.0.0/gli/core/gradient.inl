namespace gli
{
	inline image radial
	(
		glm::uvec2 const & Size, 
		glm::vec2 const & Center,
		float const & Radius,
		glm::vec2 const & Focal
	)
	{
		image::mipmap Result(image::dimensions_type(Size, glm::uint(1)), gli::RGB8U);
		glm::u8vec3 * DstData = (glm::u8vec3 *)Result.data();

		for(std::size_t y = 0; y < Result.dimensions().y; ++y)
		for(std::size_t x = 0; x < Result.dimensions().x; ++x)
		{
			float Value = glm::radialGradient(
				Center * glm::vec2(Size), 
				Radius, 
				Focal * glm::vec2(Size),
				glm::vec2(x, y));

			std::size_t Index = x + y * Result.dimensions().x;

			*(DstData + Index) = glm::u8vec3(glm::u8(glm::clamp(Value * 255.f, 0.f, 255.f)));
		}

		gli::image Image(1);
		Image[0] = Result;
		return Image;
	}

	inline image linear
	(
		glm::uvec2 const & Size, 
		glm::vec2 const & Point0, 
		glm::vec2 const & Point1
	)
	{
		image::mipmap Result(image::dimensions_type(Size, glm::uint(1)), gli::RGB8U);
		glm::u8vec3 * DstData = (glm::u8vec3 *)Result.data();

		for(std::size_t y = 0; y < Result.dimensions().y; ++y)
		for(std::size_t x = 0; x < Result.dimensions().x; ++x)
		{
			float Value = glm::linearGradient(
				Point0 * glm::vec2(Size), 
				Point1 * glm::vec2(Size),
				glm::vec2(x, y));

			std::size_t Index = x + y * Result.dimensions().x;

			*(DstData + Index) = glm::u8vec3(glm::u8(glm::clamp(Value * 255.f, 0.f, 255.f)));
		}

		gli::image Image(1);
		Image[0] = Result;
		return Image;
	}

}//namespace gli
