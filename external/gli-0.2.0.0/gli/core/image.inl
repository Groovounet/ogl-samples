namespace gli
{
	namespace detail
	{
		image::size_type const NA = -1;

		inline image::size_type getComponents(image::format_type const & Format)
		{
			static image::size_type Component[FORMAT_MAX] =
			{
				0,

				//// Unsigned integer formats
				1, //R8U,
				2, //RG8U,
				3, //RGB8U,
				4, //RGBA8U,

				1, //R16U,
				2, //RG16U,
				3, //RGB16U,
				4, //RGBA16U,

				1, //R32U,
				2, //RG32U,
				3, //RGB32U,
				4, //RGBA32U,

				//// Signed integer formats
				1, //R8I,
				2, //RG8I,
				3, //RGB8I,
				4, //RGBA8I,

				1, //R16I,
				2, //RG16I,
				3, //RGB16I,
				4, //RGBA16I,

				1, //R32I,
				2, //RG32I,
				3, //RGB32I,
				4, //RGBA32I,

				//// Floating formats
				1, //R16F,
				2, //RG16F,
				3, //RGB16F,
				4, //RGBA16F,

				1, //R32F,
				2, //RG32F,
				3, //RGB32F,
				4, //RGBA32F,

				//// Packed formats
				NA, //RGBE8,
				NA, //RGB9E5,
				NA, //RG11B10F,
				NA, //RGB565,
				NA, //RGBA4,
				NA, //RGB10A2,

				//// Depth formats
				NA, //D16,
				NA, //D24X8,
				NA, //D24S8,
				NA, //D32F,
				NA, //D32FS8X24,

				//// Compressed formats
				NA, //DXT1,
				NA, //DXT3,
				NA, //DXT5,
				NA, //ATI1N,
				NA  //ATI2N,
			};

			return Component[Format];
		}

		inline image::size_type getBitPerTexels(image::format_type const & Format)
		{
			static image::size_type BitsPerTexels[FORMAT_MAX] =
			{
				0,

				//// Unsigned integer formats
				8, //R8U,
				16, //RG8U,
				24, //RGB8U,
				32, //RGBA8U,

				16, //R16U,
				32, //RG16U,
				48, //RGB16U,
				64, //RGBA16U,

				32, //R32U,
				64, //RG32U,
				96, //RGB32U,
				128, //RGBA32U,

				//// Signed integer formats
				8, //R8I,
				16, //RG8I,
				24, //RGB8I,
				32, //RGBA8I,

				16, //R16I,
				32, //RG16I,
				48, //RGB16I,
				64, //RGBA16I,

				32, //R32I,
				64, //RG32I,
				96, //RGB32I,
				128, //RGBA32I,

				//// Floating formats
				16, //R16F,
				32, //RG16F,
				48, //RGB16F,
				64, //RGBA16F,

				32, //R32F,
				64, //RG32F,
				96, //RGB32F,
				128, //RGBA32F,

				//// Packed formats
				32, //RGBE8,
				32, //RGB9E5,
				32, //RG11B10F,
				16, //RGB565,
				16, //RGBA4,
				32, //RGB10A2,

				//// Depth formats
				16, //D16,
				32, //D24X8,
				32, //D24S8,
				32, //D32F,
				64, //D32FS8X24,

				//// Compressed formats
				4, //DXT1,
				4, //DXT3,
				8, //DXT5,
				NA, //ATI1N,
				NA  //ATI2N,
			};

			return BitsPerTexels[Format];
		}

	}//namespace detail

	inline image::mipmap_impl::mipmap_impl() :
		Data(0),
		Dimensions(0),
		Format(FORMAT_NULL)
	{}

	inline image::mipmap_impl::mipmap_impl
	(
		image::mipmap const & Mipmap2D
	) :
		Data(Mipmap2D.Data),
		Dimensions(Mipmap2D.Dimensions),
		Format(Mipmap2D.Format)
	{}

	inline image::mipmap_impl::mipmap_impl    
	(
		dimensions_type const & Dimensions,
		format_type Format
	) :
		Data(new value_type[glm::compMul(Dimensions) * detail::getBitPerTexels(Format) / 8]),
		Dimensions(Dimensions),
		Format(Format)
	{}

	inline image::mipmap_impl::mipmap_impl
	(
		dimensions_type const & Dimensions,
		format_type Format,
		std::vector<value_type> const & Data
	) :
		Data(new value_type[Data.size()]),
		Dimensions(Dimensions),
		Format(Format)
	{
		memcpy(this->Data.get(), &Data[0], Data.size());
	}

	inline image::mipmap_impl::mipmap_impl
	(
		dimensions_type const & Dimensions,
		format_type Format,
		data_type const & Data
	) :
		Data(Data),
		Dimensions(Dimensions),
		Format(Format)
	{}

	inline image::mipmap_impl::~mipmap_impl()
	{}

	inline image::size_type image::mipmap_impl::value_size() const
	{
		return detail::getBitPerTexels(this->format()) / 8;
	}

	inline image::size_type image::mipmap_impl::capacity() const
	{
		std::size_t MipmapSize = 0;
		if(this->format() == DXT1 || this->format() == DXT3 || this->format() == DXT5)
			MipmapSize = ((this->dimensions().x + 3) >> 2) * ((this->dimensions().y + 3) >> 2) * (this->format() == DXT1 ? 8 : 16);
		else
			MipmapSize = glm::compMul(this->dimensions()) * detail::getBitPerTexels(this->format()) / 8;
		return MipmapSize;
	}

	inline image::dimensions_type image::mipmap_impl::dimensions() const
	{
		return this->Dimensions;
	}

	inline image::size_type image::mipmap_impl::components() const
	{
		return detail::getComponents(this->format());
	}

	inline image::format_type image::mipmap_impl::format() const
	{
		return this->Format;
	}

	inline image::value_type * image::mipmap_impl::data()
	{
		return this->Data.get();
	}

	inline image::value_type const * const image::mipmap_impl::data() const
	{
		return this->Data.get();
	}

	namespace detail
	{

	}//namespace detail

	inline image::image()
	{}

	inline image::image
	(
		level_type const & Levels
	)
	{
		this->Mipmaps.resize(Levels);
	}

	//inline image::image
	//(
	//	mipmap const & Mipmap, 
	//	bool GenerateMipmaps // ToDo
	//)
	//{
	//	//std::size_t Levels = !GenerateMipmaps ? 1 : std::size_t(glm::log2(float(glm::max(Mipmap.width(), Mipmap.height()))));
	//	image::level_type Levels = !GenerateMipmaps ? 1 : std::size_t(glm::log2(float(glm::compMax(Mipmap.dimensions()))));
	//	this->Mipmaps.resize(Levels);
	//	this->Mipmaps[0] = Mipmap;

	//	if(GenerateMipmaps)
	//		this->generateMipmaps(0);
	//}

	inline image::~image()
	{}

	inline image::mipmap & image::operator[] (level_type const & Level)
	{
		return this->Mipmaps[Level];
	}

	inline image::mipmap const & image::operator[] (level_type const & Level) const
	{
		return this->Mipmaps[Level];
	}

	inline image::level_type image::levels() const
	{
		return this->Mipmaps.size();
	}

	inline image::format_type image::format() const
	{
		return this->Mipmaps.empty() ? FORMAT_NULL : this->Mipmaps[0].format();
	}

	template <typename genType>
	inline void image::swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W)
	{
		for(image::level_type Level = 0; Level < this->levels(); ++Level)
		{
			genType * Data = reinterpret_cast<genType*>(this->Mipmaps[Level].data());
			image::size_type Components = detail::getComponents(this->Mipmaps[Level].format());
			image::size_type Size = (glm::compMul(this->Mipmaps[Level].dimensions()) * Components) / sizeof(genType);

			for(image::size_type i = 0; i < Size; ++i)
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

namespace wip
{
	////////////////
	// mipmap
/*
	// 
	template
	<
		typename coordType
	>
	template
	<
		typename genType, 
		template <typename> class surface
	>
	typename image<genType, surface>::value_type & 
	image<genType, surface>::mipmap_impl<coordType>::operator() 
	(
		coordType const & Coord
	)
	{
		
	}
*/
/*
	// 
	template
	<
		typename coordType
	>
	template
	<
		typename genType, 
		template <typename> class surface
	>
	typename image<genType, surface>::value_type const & 
	image<genType, surface>::mipmap_impl::operator()
	(
		coordType const & Coord
	) const
	{
		return value_type(0);
	}
*/
/*
	//
	template
	<
		typename coordType
	>
	template
	<
		typename genType, 
		template <typename> class surface
	>
	void image<genType, surface>::mipmap_impl::operator()
	(
		coordType const & Coord
	) const
	{
		
	}
*/
	////
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//template
	//<
	//	typename coordType
	//>
	//typename image<genType, surface>::value_type const & 
	//image<genType, surface>::mipmap_impl::operator()
	//(
	//	coordType const & Coord
	//) const
	//{
	//	return value_type(0);
	//}

	//////////////////
	//// image

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename image<genType, surface>::level_type image<genType, surface>::levels() const
	//{
	//	return this->Mipmaps.size();
	//}

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename image<genType, surface>::mipmap & image<genType, surface>::operator[] 
	//(
	//	typename image<genType, surface>::level_type Level
	//)
	//{
	//	return this->Mipmaps[Level];
	//}

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename image<genType, surface>::mipmap const & image<genType, surface>::operator[] 
	//(
	//	typename image<genType, surface>::level_type Level
	//) const
	//{
	//	return this->Mipmaps[Level];
	//}

}//namespace wip
}//namespace gli
