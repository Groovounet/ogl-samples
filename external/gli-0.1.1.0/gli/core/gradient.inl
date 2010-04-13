namespace gli
{
	inline mipmap radial
	(
		glm::uvec2 const & Size, 
		glm::vec2 const & Center,
		float const & Radius,
		glm::vec2 const & Focal
	)
	{
		mipmap Result(Size.x, Size.y, gli::RGB8U);
		glm::u8vec3 * DstData = (glm::u8vec3 *)Result.data();

		for(std::size_t y = 0; y < Result.height(); ++y)
		for(std::size_t x = 0; x < Result.width(); ++x)
		{
			float Value = glm::radialGradient(
				Center, Radius, Focal,
				glm::vec2(x, y));

			std::size_t Index = x + y * Result.width();

			*(DstData + Index) = glm::u8vec3(glm::u8(glm::clamp(Value * 255.f, 0.f, 255.f)));
		}

		return Result;
	}

	inline mipmap linear
	(
		glm::uvec2 const & Size, 
		glm::vec2 const & Point0, 
		glm::vec2 const & Point1
	)
	{
		mipmap Result(Size.x, Size.y, gli::RGB8U);
		glm::u8vec3 * DstData = (glm::u8vec3 *)Result.data();

		for(std::size_t y = 0; y < Result.height(); ++y)
		for(std::size_t x = 0; x < Result.width(); ++x)
		{
			float Value = glm::linearGradient(
				Point0, Point1,
				glm::vec2(x, y));

			std::size_t Index = x + y * Result.width();

			*(DstData + Index) = glm::u8vec3(glm::u8(glm::clamp(Value * 255.f, 0.f, 255.f)));
		}

		return Result;
	}

}//namespace gli
