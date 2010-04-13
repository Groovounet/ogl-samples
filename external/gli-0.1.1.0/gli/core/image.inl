namespace gli
{
	namespace detail
	{

	}//namespace detail

	inline image::image()
	{}

	inline image::image
	(
		std::size_t Levels
	)
	{
		Mipmaps.resize(Levels);
	}

	inline image::image
	(
		mipmap const & Mipmap, 
		bool GenerateMipmaps // ToDo
	)
	{
		std::size_t Levels = !GenerateMipmaps ? 1 : std::size_t(glm::log2(float(glm::max(Mipmap.width(), Mipmap.height()))));
		Mipmaps.resize(Levels);
		Mipmaps[0] = Mipmap;

		if(GenerateMipmaps)
			generateMipmaps(0);
	}

	inline image::~image()
	{}

	inline mipmap & image::operator[] (std::size_t Level)
	{
		return Mipmaps[Level];
	}

	inline mipmap const & image::operator[] (std::size_t Level) const
	{
		return Mipmaps[Level];
	}

	inline std::size_t image::width() const
	{
		return Mipmaps.empty() ? 0 : Mipmaps[0].width();
	}

	inline std::size_t image::height() const
	{
		return Mipmaps.empty() ? 0 : Mipmaps[0].height();
	}

	inline std::size_t image::depth() const
	{
		return Mipmaps.empty() ? 0 : Mipmaps[0].depth();
	}

	inline std::size_t image::levels() const
	{
		return Mipmaps.size();
	}

	inline gli::format image::format() const
	{
		return Mipmaps.empty() ? FORMAT_NULL : Mipmaps[0].format();
	}

	template <typename genType>
	inline void image::swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W)
	{
		for(std::size_t Level = 0; Level < Mipmaps.size(); ++Level)
		{
			genType * Data = reinterpret_cast<genType*>(Mipmaps[Level].data());
			std::size_t Components = detail::getComponents(Mipmaps[Level].format());

			std::size_t Size = (Mipmaps[Level].width() * Mipmaps[Level].height() * Components) / sizeof(genType);

			for(std::size_t i = 0; i < Size; ++i)
			{
				genType Copy = Data[i];
				if(Components > 0)
					Data[i][0] = Copy[X];
				if(Components > 1)
					Data[i][1] = Copy[Y];
				if(Components > 2)
					Data[i][2] = Copy[Z];
				if(Components > 3)
					Data[i][3] = Copy[W];
			}
		}
	}

	inline bool image::generateMipmaps(std::size_t BaseLevel)
	{
		assert(BaseLevel < Mipmaps.size());

		gli::format Format = Mipmaps[BaseLevel].format();

		assert(Format == R8U || Format == RG8U || Format == RGB8U || Format == RGBA8U);

		std::size_t Levels = std::size_t(glm::log2(float(glm::max(Mipmaps[0].width(), Mipmaps[0].height()))));
		Mipmaps.resize(Levels);

		for(std::size_t Level = BaseLevel; Level < Levels - 1; ++Level)
		{
			std::size_t BaseWidth = Mipmaps[Level + 0].width();

			std::size_t Width  = Mipmaps[Level + 0].height() >> 1;
			std::size_t Height = Mipmaps[Level + 0].width()  >> 1;
			std::size_t ValueSize = Mipmaps[Level + 0].value_size();
			std::size_t Components = Mipmaps[Level + 0].components();

			std::vector<glm::u8> Data(
				(Mipmaps[Level + 0].width() >> 1) * (Mipmaps[Level + 0].height() >> 1) * Mipmaps[Level + 0].value_size());
			void * Pointer = &Data[0];

			for(std::size_t j = 0; j < Height; ++j)
			for(std::size_t i = 0; i < Width;  ++i)
			for(std::size_t c = 0; c < Components; ++c)
			{
				std::size_t x = (i << 1);
				std::size_t y = (j << 1);

				std::size_t Index00 = ((x + 0) + (y + 0) * BaseWidth) * Components + c;
				std::size_t Index01 = ((x + 0) + (y + 1) * BaseWidth) * Components + c;
				std::size_t Index11 = ((x + 1) + (y + 1) * BaseWidth) * Components + c;
				std::size_t Index10 = ((x + 1) + (y + 0) * BaseWidth) * Components + c;

				glm::u32 Data00 = reinterpret_cast<glm::u8*>(Mipmaps[Level + 0].data())[Index00];
				glm::u32 Data01 = reinterpret_cast<glm::u8*>(Mipmaps[Level + 0].data())[Index01];
				glm::u32 Data11 = reinterpret_cast<glm::u8*>(Mipmaps[Level + 0].data())[Index11];
				glm::u32 Data10 = reinterpret_cast<glm::u8*>(Mipmaps[Level + 0].data())[Index10];

				glm::u8 Result = (Data00 + Data01 + Data11 + Data10) >> 2;
				*(reinterpret_cast<glm::u8*>(Pointer) + ((i + j * Width) * Components + c)) = Result;
			}

			Mipmaps[Level + 1] = mipmap(Width, Height, Format, Data);
		}

		return true;
	}

/*
	template <typename T>
	inline T image<T>::texture2D(float x, float y) const
	{
        size_type x_below = size_type(std::floor(x * (_width - 1)));
		size_type x_above = size_type(std::ceil(x * (_width - 1)));
        size_type y_below = size_type(std::floor(y * (_height - 1)));
        size_type y_above = size_type(std::ceil(y * (_height - 1)));

        float x_step = 1.0f / float(_width);
        float y_step = 1.0f / float(_height);

        float x_below_normalized = float(x_below) / float(_width - 1);
        float x_above_normalized = float(x_above) / float(_width - 1);
        float y_below_normalized = float(y_below) / float(_height - 1);
        float y_above_normalized = float(y_above) / float(_height - 1);
		
		T value1 = _data[x_below + y_below * _width];
		T value2 = _data[x_above + y_below * _width];
		T value3 = _data[x_above + y_above * _width];
		T value4 = _data[x_below + y_above * _width];

		T valueA = glm::mix(value1, value2, x - x_below_normalized);
		T valueB = glm::mix(value4, value3, x - x_below_normalized);
		T valueC = glm::mix(valueA, valueB, y - y_below_normalized);
		return valueC;
	}
*/
/*
	template <typename T>
	inline T texture2D(const image<T>& Image2D, const glm::vec2& TexCoord)
	{
		image<T>::size_type s_below = image<T>::size_type(std::floor(TexCoord.s * (Image2D.width() - 1)));
		image<T>::size_type s_above = image<T>::size_type(std::ceil(TexCoord.s * (Image2D.width() - 1)));
        image<T>::size_type t_below = image<T>::size_type(std::floor(TexCoord.t * (Image2D.height() - 1)));
        image<T>::size_type t_above = image<T>::size_type(std::ceil(TexCoord.t * (Image2D.height() - 1)));

		glm::vec2::value_type s_step = 1.0f / glm::vec2::value_type(Image2D.width());
        glm::vec2::value_type t_step = 1.0f / glm::vec2::value_type(Image2D.height());

        glm::vec2::value_type s_below_normalized = glm::vec2::value_type(s_below) / glm::vec2::value_type(Image2D.width() - 1);
        glm::vec2::value_type s_above_normalized = glm::vec2::value_type(s_above) / glm::vec2::value_type(Image2D.width() - 1);
        glm::vec2::value_type t_below_normalized = glm::vec2::value_type(t_below) / glm::vec2::value_type(Image2D.height() - 1);
        glm::vec2::value_type t_above_normalized = glm::vec2::value_type(t_above) / glm::vec2::value_type(Image2D.height() - 1);
		
		T value1 = Image2D[s_below + t_below * Image2D.width()];
		T value2 = Image2D[s_above + t_below * Image2D.width()];
		T value3 = Image2D[s_above + t_above * Image2D.width()];
		T value4 = Image2D[s_below + t_above * Image2D.width()];

		T valueA = glm::mix(value1, value2, TexCoord.s - s_below_normalized);
		T valueB = glm::mix(value4, value3, TexCoord.s - s_below_normalized);
		T valueC = glm::mix(valueA, valueB, TexCoord.t - t_below_normalized);
		return valueC;
	}

	template <typename T>
	inline T texture2DNearest(const image<T>& Image2D, const glm::vec2& TexCoord)
	{
		image<T>::size_type s = image<T>::size_type(glm::roundGTX(TexCoord.s * (Image2D.width() - 1)));
        image<T>::size_type t = image<T>::size_type(std::roundGTX(TexCoord.t * (Image2D.height() - 1)));

		return Image2D[s + t * Image2D.width()];
	}
*/
}//namespace gli

