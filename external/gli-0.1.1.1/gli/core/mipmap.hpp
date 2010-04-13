#ifndef GLI_MIPMAP_INCLUDED
#define GLI_MIPMAP_INCLUDED

// STD
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

// Boost
//#include <boost/shared_array.hpp>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/raw_data.hpp>
#include <glm/gtx/gradient_paint.hpp>
#include <glm/gtx/number_precision.hpp>

namespace gli
{
	enum format
	{
		FORMAT_NULL,

		// Unsigned integer formats
		R8U,
		RG8U,
		RGB8U,
		RGBA8U,

		R16U,
		RG16U,
		RGB16U,
		RGBA16U,

		R32U,
		RG32U,
		RGB32U,
		RGBA32U,

		// Signed integer formats
		R8I,
		RG8I,
		RGB8I,
		RGBA8I,

		R16I,
		RG16I,
		RGB16I,
		RGBA16I,

		R32I,
		RG32I,
		RGB32I,
		RGBA32I,

		// Floating formats
		R16F,
		RG16F,
		RGB16F,
		RGBA16F,

		R32F,
		RG32F,
		RGB32F,
		RGBA32F,

		// Packed formats
		RGBE8,
		RGB9E5,
		RG11B10F,
		RGB565,
		RGBA4,
		RGB10A2,

		// Depth formats
		D16,
		D24X8,
		D24S8,
		D32F,
		D32FS8X24,

		// Compressed formats
		DXT1,
		DXT3,
		DXT5,
		ATI1N,
		ATI2N,

		FORMAT_MAX
	};

	class mipmap
	{
	public:
		typedef size_t size_type;
		typedef glm::byte value_type;

        mipmap();
		mipmap(mipmap const & Mipmap);

        mipmap(
			size_type Width, 
			size_type Height, 
			gli::format Format);

		template <typename genType>
		mipmap(
			size_type Width, 
			size_type Height, 
			gli::format Format, 
			genType const & Value);

		mipmap(
			size_type Width, 
			size_type Height, 
			gli::format Format, 
			std::vector<glm::byte> const & Data);

		//mipmap(
		//	size_type Width, 
		//	size_type Height, 
		//	gli::format Format, 
		//	boost::shared_array<glm::byte> const & Data);

        ~mipmap();

		mipmap& operator=(mipmap const & Mipmap);

		size_type value_size() const;
		size_type size() const;
		size_type width() const;
		size_type height() const;
		size_type depth() const;
		size_type components() const;
		gli::format format() const;
		
		template <typename genType>
		genType fetch(glm::vec2 const & TexCoord) const;

		glm::byte * data();
		glm::byte const * const data() const;

	private:
        glm::byte * Data;
		size_type Width;
		size_type Height;
		gli::format Format;
	};

}//namespace gli

#include "mipmap.inl"

#endif//GLI_MIPMAP_INCLUDED
