namespace gli
{
	template <typename genType>
	inline genType texelFetch
	(
		image const & Image, 
		glm::ivec2 const & TexCoord,
		image::level_type const & Level
	)
	{
		assert(Image[Level].format() == R8U || Image[Level].format() == RG8U || Image[Level].format() == RGB8U || Image[Level].format() == RGBA8U);

		image::dimensions_type Dimensions = Image[Level].dimensions();
		image::value_type const * const Data = Image[Level].data();

		return reinterpret_cast<genType const * const>(Data)[TexCoord.x + TexCoord.y * Dimensions.x];
	}

	template <typename genType>
	inline genType textureLod
	(
		image const & Image, 
		glm::vec2 const & TexCoord, 
		image::level_type const & Level
	)
	{
		assert(Image[Level].format() == R8U || Image[Level].format() == RG8U || Image[Level].format() == RGB8U || Image[Level].format() == RGBA8U);

		image::dimensions_type Dimensions = Image[Level].dimensions();
		image::value_type const * const Data = Image[Level].data();

		std::size_t s_below = std::size_t(glm::floor(TexCoord.s * float(Dimensions.x - 1)));
		std::size_t s_above = std::size_t(glm::ceil( TexCoord.s * float(Dimensions.x - 1)));
		std::size_t t_below = std::size_t(glm::floor(TexCoord.t * float(Dimensions.y - 1)));
		std::size_t t_above = std::size_t(glm::ceil( TexCoord.t * float(Dimensions.y - 1)));

		float s_step = 1.0f / float(Dimensions.x);
		float t_step = 1.0f / float(Dimensions.y);

		float s_below_normalized = s_below / float(Dimensions.x);
		float s_above_normalized = s_above / float(Dimensions.x);
		float t_below_normalized = t_below / float(Dimensions.y);
		float t_above_normalized = t_above / float(Dimensions.y);

		genType value1 = reinterpret_cast<genType const * const>(Data)[s_below + t_below * Dimensions.x];
		genType value2 = reinterpret_cast<genType const * const>(Data)[s_above + t_below * Dimensions.x];
		genType value3 = reinterpret_cast<genType const * const>(Data)[s_above + t_above * Dimensions.x];
		genType value4 = reinterpret_cast<genType const * const>(Data)[s_below + t_above * Dimensions.x];

		glm::vec3 BlendA = glm::vec3(TexCoord.s - s_below_normalized) * float(Dimensions.x - 1);
		glm::vec3 BlendB = glm::vec3(TexCoord.s - s_below_normalized) * float(Dimensions.x - 1);
		glm::vec3 BlendC = glm::vec3(TexCoord.t - t_below_normalized) * float(Dimensions.y - 1);

		glm::vec3 valueA = glm::vec3(glm::mix(value1, value2, BlendA));
		glm::vec3 valueB = glm::vec3(glm::mix(value4, value3, BlendB));

		return genType(glm::mix(valueA, valueB, BlendC));
	}

	template <typename genType>
	void texelWrite
	(
		image & Image,
		glm::uvec2 const & Texcoord,
		image::level_type const & Level,
		genType const & Color
	)
	{
		genType * Data = (genType*)Image[Level].data();
		std::size_t Index = Texcoord.x + Texcoord.y * Image[Level].dimensions().x;
		
		assert(Index * sizeof(genType) < Image[Level].capacity());

		*(Data + Index) = Color;
	}
}// namespace gli
