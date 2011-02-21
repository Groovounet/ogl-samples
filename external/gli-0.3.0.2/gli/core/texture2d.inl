///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-27
// Updated : 2010-09-27
// Licence : This source is under MIT License
// File    : gli/core/texture2D.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace gli
{
	namespace detail
	{
		struct format_desc
		{
			texture2D::size_type BlockSize;
			texture2D::size_type BBP;
			texture2D::size_type Component;
		};

		inline format_desc getFormatInfo(format const & Format)
		{
			format_desc Desc[FORMAT_MAX] =
			{
				{  0,  0,  0},	//FORMAT_NULL

				// Unsigned integer formats
				{  1,   8,  1},	//R8U,
				{  2,  16,  2},	//RG8U,
				{  3,  24,  3},	//RGB8U,
				{  4,  32,  4},	//RGBA8U,

				{  2,  16,  1},	//R16U,
				{  4,  32,  2},	//RG16U,
				{  6,  48,  3},	//RGB16U,
				{  8,  64,  4},	//RGBA16U,

				{  4,  32,  1},	//R32U,
				{  8,  64,  2},	//RG32U,
				{ 12,  96,  3},	//RGB32U,
				{ 16, 128,  4},	//RGBA32U,

				//// Signed integer formats
				{  4,  32,  1},	//R8I,
				{  8,  64,  2},	//RG8I,
				{ 12,  96,  3},	//RGB8I,
				{ 16, 128,  4},	//RGBA8I,

				{  2,  16,  1},	//R16I,
				{  4,  32,  2},	//RG16I,
				{  6,  48,  3},	//RGB16I,
				{  8,  64,  4},	//RGBA16I,

				{  4,  32,  1},	//R32I,
				{  8,  64,  2},	//RG32I,
				{ 12,  96,  3},	//RGB32I,
				{ 16, 128,  4},	//RGBA32I,

				//// Floating formats
				{  2,  16,  1},	//R16F,
				{  4,  32,  2},	//RG16F,
				{  6,  48,  3},	//RGB16F,
				{  8,  64,  4},	//RGBA16F,

				{  4,  32,  1},	//R32F,
				{  8,  64,  2},	//RG32F,
				{ 12,  96,  3},	//RGB32F,
				{ 16, 128,  4},	//RGBA32F,

				//// Packed formats
				{  4,  32,  3},	//RGBE8,
				{  4,  32,  3},	//RGB9E5,
				{  4,  32,  3},	//RG11B10F,
				{  2,  16,  3},	//R5G6B5,
				{  2,  16,  4},	//RGBA4,
				{  4,  32,  3},	//RGB10A2,

				//// Depth formats
				{  2,  16,  1},	//D16,
				{  4,  32,  1},	//D24X8,
				{  4,  32,  2},	//D24S8,
				{  4,  32,  1},	//D32F,
				{  8,  64,  2},	//D32FS8X24,

				//// Compressed formats
				{  8,   4,  4},	//DXT1,
				{ 16,   8,  4},	//DXT3,
				{ 16,   8,  4},	//DXT5,
				{  8,   4,  1},	//ATI1N_UNORM,
				{  8,   4,  1},	//ATI1N_SNORM,
				{ 16,   8,  2},	//ATI2N_UNORM,
				{ 16,   8,  2},	//ATI2N_SNORM,
				{ 16,   8,  3},	//BP_UF16,
				{ 16,   8,  3},	//BP_SF16,
				{ 16,   8,  4},	//BP,
			};

			return Desc[Format];
		};

		inline texture2D::size_type sizeBlock
		(
			format const & Format
		)
		{
			return getFormatInfo(Format).BlockSize;
		}

		inline texture2D::size_type sizeBitPerPixel
		(
			format const & Format
		)
		{
			return getFormatInfo(Format).BBP;
		}

		inline texture2D::size_type sizeComponent
		(
			format const & Format
		)
		{
			return getFormatInfo(Format).Component;
		}

		inline texture2D::size_type sizeLinear
		(
			image const & Mipmap
		)
		{
			texture2D::dimensions_type Dimension = Mipmap.dimensions();
			Dimension = glm::max(Dimension, texture2D::dimensions_type(1));

			texture2D::size_type BlockSize = sizeBlock(Mipmap.format());
			texture2D::size_type BPP = sizeBitPerPixel(Mipmap.format());
			texture2D::size_type BlockCount = 0;
			if((BlockSize << 3) == BPP)
				BlockCount = Dimension.x * Dimension.y;
			else
				BlockCount = ((Dimension.x + 3) >> 2) * ((Dimension.y + 3) >> 2);			

			return BlockCount * BlockSize;
		}

		inline texture2D::size_type sizeLinear
		(
			texture2D const & Image
		)
		{
			texture2D::size_type Result = 0;
			for(texture2D::level_type Level = 0; Level < Image.levels(); ++Level)
				Result += sizeLinear(Image[Level]);
			return Result;
		}
	}//namespace detail

	inline texture2D::image_impl::image_impl() :
		Data(0),
		Dimensions(0),
		Format(FORMAT_NULL)
	{}

	inline texture2D::image_impl::image_impl
	(
		texture2D::image const & Image
	) :
		Data(Image.Data),
		Dimensions(Image.Dimensions),
		Format(Image.Format)
	{}

	inline texture2D::image_impl::image_impl    
	(
		dimensions_type const & Dimensions,
		format_type const & Format
	) :
		Data(new value_type[(glm::compMul(Dimensions) * detail::sizeBitPerPixel(Format)) >> 3]),
		Dimensions(Dimensions),
		Format(Format)
	{
		std::size_t Size = (glm::compMul(Dimensions) * detail::sizeBitPerPixel(Format)) >> 3;
	}

	inline texture2D::image_impl::image_impl
	(
		dimensions_type const & Dimensions,
		format_type const & Format,
		std::vector<value_type> const & Data
	) :
		Data(new value_type[Data.size()]),
		Dimensions(Dimensions),
		Format(Format)
	{
		memcpy(this->Data.get(), &Data[0], Data.size());
	}

	inline texture2D::image_impl::image_impl
	(
		dimensions_type const & Dimensions,
		format_type const & Format,
		data_type const & Data
	) :
		Data(Data),
		Dimensions(Dimensions),
		Format(Format)
	{}

	inline texture2D::image_impl::~image_impl()
	{}

	template <typename genType>
	inline void texture2D::image_impl::setPixel
	(
		dimensions_type const & TexelCoord,
		genType const & TexelData
	)
	{
		size_type Index = this->dimensions().x * sizeof(genType) * TexelCoord.y + sizeof(genType) * TexelCoord.x;
		memcpy(this->data() + Index, &TexelData[0], sizeof(genType));
	}

	inline texture2D::size_type texture2D::image_impl::value_size() const
	{
		return detail::sizeBitPerPixel(this->format());
	}

	inline texture2D::size_type texture2D::image_impl::capacity() const
	{
		return detail::sizeLinear(*this);
	}

	inline texture2D::dimensions_type texture2D::image_impl::dimensions() const
	{
		return this->Dimensions;
	}

	inline texture2D::size_type texture2D::image_impl::components() const
	{
		return detail::sizeComponent(this->format());
	}

	inline texture2D::format_type texture2D::image_impl::format() const
	{
		return this->Format;
	}

	inline texture2D::value_type * texture2D::image_impl::data()
	{
		return this->Data.get();
	}

	inline texture2D::value_type const * const texture2D::image_impl::data() const
	{
		return this->Data.get();
	}

	namespace detail
	{

	}//namespace detail

	inline texture2D::texture2D()
	{}

	inline texture2D::texture2D
	(
		level_type const & Levels
	)
	{
		this->Images.resize(Levels);
	}

	//inline texture2D::texture2D
	//(
	//	image const & Mipmap, 
	//	bool GenerateMipmaps // ToDo
	//)
	//{
	//	//std::size_t Levels = !GenerateMipmaps ? 1 : std::size_t(glm::log2(float(glm::max(Mipmap.width(), Mipmap.height()))));
	//	texture2D::level_type Levels = !GenerateMipmaps ? 1 : std::size_t(glm::log2(float(glm::compMax(Mipmap.dimensions()))));
	//	this->Mipmaps.resize(Levels);
	//	this->Mipmaps[0] = Mipmap;

	//	if(GenerateMipmaps)
	//		this->generateMipmaps(0);
	//}

	inline texture2D::~texture2D()
	{}

	inline texture2D::image & texture2D::operator[] (level_type const & Level)
	{
		return this->Images[Level];
	}

	inline texture2D::image const & texture2D::operator[] (level_type const & Level) const
	{
		return this->Images[Level];
	}

	inline bool texture2D::empty() const
	{
		return this->Images.size() == 0;
	}

	inline texture2D::level_type texture2D::levels() const
	{
		return this->Images.size();
	}

	inline texture2D::format_type texture2D::format() const
	{
		return this->Images.empty() ? FORMAT_NULL : this->Images[0].format();
	}

	template <typename genType>
	inline void texture2D::swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W)
	{
		for(texture2D::level_type Level = 0; Level < this->levels(); ++Level)
		{
			genType * Data = reinterpret_cast<genType*>(this->Images[Level].data());
			texture2D::size_type Components = this->Images[Level].components();
			//gli::detail::getComponents(this->Images[Level].format());
			texture2D::size_type Size = (glm::compMul(this->Images[Level].dimensions()) * Components) / sizeof(genType);

			for(texture2D::size_type i = 0; i < Size; ++i)
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
	inline T texture2D<T>::texture2D(float x, float y) const
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
	inline T texture2D(const texture2D<T>& Image2D, const glm::vec2& TexCoord)
	{
		texture2D<T>::size_type s_below = texture2D<T>::size_type(std::floor(TexCoord.s * (Image2D.width() - 1)));
		texture2D<T>::size_type s_above = texture2D<T>::size_type(std::ceil(TexCoord.s * (Image2D.width() - 1)));
        texture2D<T>::size_type t_below = texture2D<T>::size_type(std::floor(TexCoord.t * (Image2D.height() - 1)));
        texture2D<T>::size_type t_above = texture2D<T>::size_type(std::ceil(TexCoord.t * (Image2D.height() - 1)));

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
	inline T texture2DNearest(const texture2D<T>& Image2D, const glm::vec2& TexCoord)
	{
		texture2D<T>::size_type s = texture2D<T>::size_type(glm::roundGTX(TexCoord.s * (Image2D.width() - 1)));
        texture2D<T>::size_type t = texture2D<T>::size_type(std::roundGTX(TexCoord.t * (Image2D.height() - 1)));

		return Image2D[s + t * Image2D.width()];
	}
*/

namespace wip
{
	////////////////
	// image
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
	typename texture2D<genType, surface>::value_type & 
	texture2D<genType, surface>::image_impl<coordType>::operator() 
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
	typename texture2D<genType, surface>::value_type const & 
	texture2D<genType, surface>::image_impl::operator()
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
	void texture2D<genType, surface>::image_impl::operator()
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
	//typename texture2D<genType, surface>::value_type const & 
	//texture2D<genType, surface>::image_impl::operator()
	//(
	//	coordType const & Coord
	//) const
	//{
	//	return value_type(0);
	//}

	//////////////////
	//// texture2D

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename texture2D<genType, surface>::level_type texture2D<genType, surface>::levels() const
	//{
	//	return this->Mipmaps.size();
	//}

	//// 
	//template
	//<
	//	typename genType, 
	//	template <typename> class surface
	//>
	//typename texture2D<genType, surface>::image & texture2D<genType, surface>::operator[] 
	//(
	//	typename texture2D<genType, surface>::level_type Level
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
	//typename texture2D<genType, surface>::image const & texture2D<genType, surface>::operator[] 
	//(
	//	typename texture2D<genType, surface>::level_type Level
	//) const
	//{
	//	return this->Mipmaps[Level];
	//}

}//namespace wip
}//namespace gli
