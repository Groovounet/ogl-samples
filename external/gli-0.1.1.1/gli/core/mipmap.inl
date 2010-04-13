namespace gli{
namespace detail
{
	std::size_t const NA = -1;

	inline std::size_t getComponents(gli::format Format)
	{
		static std::size_t Component[FORMAT_MAX] =
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

	inline std::size_t getBitPerTexels(gli::format Format)
	{
		static std::size_t BitsPerTexels[FORMAT_MAX] =
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

inline mipmap::mipmap() :
	Data(0),
	Width(0),
    Height(0),
	Format(FORMAT_NULL)
{}

inline mipmap::mipmap
(
	mipmap const & Mipmap2D
) :
	//Data(Mipmap2D.Data),
	Width(Mipmap2D.Width),
    Height(Mipmap2D.Height),
	Format(Mipmap2D.Format)
{
	Data = new glm::byte[Mipmap2D.size()];
	memcpy(Data, Mipmap2D.data(), Mipmap2D.size());
}

inline mipmap::mipmap    
(
    mipmap::size_type Width, 
    mipmap::size_type Height,
	gli::format Format
) :
	Data(new glm::byte[Width * Height * detail::getBitPerTexels(Format) / 8]),
	Width(Width),
    Height(Height),
	Format(Format)
{}

//template <typename genType>
//inline mipmap::mipmap
//(
//    mipmap::size_type Width, 
//    mipmap::size_type Height,
//    genType const & Value
//) :
//	Data(new glm::byte[Width * Height * sizeof(Value)]),
//	Width(Width),
//    Height(Height),
//	Format()
//{
//	fill(Value);
//}

inline mipmap::mipmap
(
    mipmap::size_type Width, 
    mipmap::size_type Height,
	gli::format Format,
    std::vector<glm::byte> const & Data
) :
	Data(new glm::byte[Data.size()]),
	Width(Width),
    Height(Height),
	Format(Format)
{
	memcpy(this->Data, &Data[0], Data.size());
}

//inline mipmap::mipmap
//(
//    mipmap::size_type Width, 
//    mipmap::size_type Height,
//	gli::format Format,
//    boost::shared_array<glm::byte> const & Data
//) :
//	Data(Data),
//	Width(Width),
//    Height(Height),
//	Format(Format)
//{}

inline mipmap::~mipmap()
{
	delete[] Data;
	Data = 0;
}

inline mipmap& mipmap::operator=(mipmap const & Mipmap)
{
	this->Data = new glm::byte[Mipmap.size()];
	memcpy(this->Data, Mipmap.data(), Mipmap.size());
	this->Width = Mipmap.Width;
	this->Height = Mipmap.Height;
	this->Format = Mipmap.Format;
	return *this;
}

inline mipmap::size_type mipmap::value_size() const
{
	return detail::getBitPerTexels(Format) / 8;
}

inline mipmap::size_type mipmap::size() const
{
	std::size_t MipmapSize = 0;
	if(this->format() == DXT1 || this->format() == DXT3 || this->format() == DXT5)
		MipmapSize = ((Width + 3) >> 2) * ((Height + 3) >> 2) * (this->format() == DXT1 ? 8 : 16);
	else
		MipmapSize = Width * Height * detail::getBitPerTexels(Format) / 8;
	return MipmapSize;
}

inline mipmap::size_type mipmap::width() const
{
	return Width;
}

inline mipmap::size_type mipmap::height() const
{
	return Height;
}

inline mipmap::size_type mipmap::depth() const
{
	return 1;
}

inline mipmap::size_type mipmap::components() const
{
	return detail::getComponents(Format);
}

inline gli::format mipmap::format() const
{
	return Format;
}

inline glm::byte * mipmap::data()
{
	return Data;
}

inline glm::byte const * const mipmap::data() const
{
	return Data;
}

template <typename genType>
inline genType mipmap::fetch(glm::vec2 const & TexCoord) const
{
	assert(Format == R8U || Format == RG8U || Format == RGB8U || Format == RGBA8U);

	std::size_t s_below = std::size_t(glm::floor(TexCoord.s * float(width () - 1)));
	std::size_t s_above = std::size_t(glm::ceil( TexCoord.s * float(width () - 1)));
	std::size_t t_below = std::size_t(glm::floor(TexCoord.t * float(height() - 1)));
	std::size_t t_above = std::size_t(glm::ceil( TexCoord.t * float(height() - 1)));

	float s_step = 1.0f / float(width ());
	float t_step = 1.0f / float(height ());

	float s_below_normalized = s_below / float(width());
	float s_above_normalized = s_above / float(width());
	float t_below_normalized = t_below / float(height());
	float t_above_normalized = t_above / float(height());

	genType value1 = reinterpret_cast<genType*>(this->Data)[s_below + t_below * width()];
	genType value2 = reinterpret_cast<genType*>(this->Data)[s_above + t_below * width()];
	genType value3 = reinterpret_cast<genType*>(this->Data)[s_above + t_above * width()];
	genType value4 = reinterpret_cast<genType*>(this->Data)[s_below + t_above * width()];

	glm::vec3 BlendA = glm::vec3(TexCoord.s - s_below_normalized) * float(width () - 1);
	glm::vec3 BlendB = glm::vec3(TexCoord.s - s_below_normalized) * float(width () - 1);
	glm::vec3 BlendC = glm::vec3(TexCoord.t - t_below_normalized) * float(height() - 1);

	//genType valueA = genType(glm::mix(glm::vec3(value1), glm::vec3(value2), BlendA));
	//genType valueB = genType(glm::mix(glm::vec3(value4), glm::vec3(value3), BlendB));
	//genType valueC = genType(glm::mix(glm::vec3(valueA), glm::vec3(valueB), BlendC));

	genType valueA = genType(glm::mix(value1, value2, BlendA));
	genType valueB = genType(glm::mix(value4, value3, BlendB));
	genType valueC = genType(glm::mix(valueA, valueB, BlendC));

	return valueC;
}

}//namespace gli
