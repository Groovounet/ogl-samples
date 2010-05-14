///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-01-09
// Updated : 2010-01-09
// Licence : This source is under MIT License
// File    : gli/image.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLI_IMAGE_INCLUDED
#define GLI_IMAGE_INCLUDED

// STD
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/number_precision.hpp>
#include <glm/gtx/raw_data.hpp>
#include <glm/gtx/gradient_paint.hpp>
#include <glm/gtx/component_wise.hpp>

// GLI
#include "shared_array.hpp"

namespace gli
{
	//inline bool isPlainFormat(const FORMAT format){
	//	return (format <= FORMAT_RGBA32F);
	//}

	//inline bool isPackedFormat(const FORMAT format){
	//	return (format >= FORMAT_RGBE8 && format <= FORMAT_RGB10A2);
	//}

	//inline bool isCompressedFormat(const FORMAT format){
	//	return (format >= FORMAT_DXT1) && (format <= FORMAT_3DC);
	//}

	//inline bool isFloatFormat(const FORMAT format){
	////	return (format >= FORMAT_R16F && format <= FORMAT_RGBA32F);
	//	return (format >= FORMAT_R16F && format <= FORMAT_RGBE8);
	//}

	//inline int getChannelCount(const FORMAT format){
	//	static int chCount[] = { 0, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 3, 3, 4, 4, 3, 4, 4, 2 };
	//	return chCount[format];
	//}

	//// Accepts only plain formats
	//inline int getBytesPerChannel(const FORMAT format){
	//	if (format <= FORMAT_RGBA8) return 1;
	//	if (format <= FORMAT_RGBA16F) return 2;
	//	return 4;
	//}

	//// Accepts only plain and packed
	//inline int getBytesPerPixel(const FORMAT format){
	//	static int bytesPP[] = { 0, 1, 2, 3, 4, 2, 4, 6, 8, 2, 4, 6, 8, 4, 8, 12, 16, 4, 2, 2, 4 };
	//	return bytesPP[format];
	//}

	//// Accepts only compressed formats
	//inline int getBytesPerBlock(const FORMAT format){
	//	return (format == FORMAT_DXT1)? 8 : 16;
	//}

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

	//template <template <typename> class mem>
	class image
	{
	public:
		typedef glm::uvec3 dimensions_type;
		typedef std::size_t size_type;
		typedef glm::byte value_type;
		typedef gli::format format_type;
		typedef std::size_t level_type;
		typedef shared_array<value_type> data_type;

	private:
		class mipmap_impl
		{
		public:
			mipmap_impl();
			mipmap_impl(
				mipmap_impl const & Mipmap);

			mipmap_impl(
				dimensions_type const & Dimensions,
				format_type Format);

			template <typename genType>
			mipmap_impl(
				dimensions_type const & Dimensions,
				format_type Format, 
				genType const & Value);

			mipmap_impl(
				dimensions_type const & Dimensions,
				format_type Format, 
				std::vector<value_type> const & Data);

			mipmap_impl(
				dimensions_type const & Dimensions,
				format_type Format, 
				data_type const & Data);

			~mipmap_impl();

			size_type value_size() const;
			size_type capacity() const;
			dimensions_type dimensions() const;
			size_type components() const;
			format_type format() const;
			
			value_type * data();
			value_type const * const data() const;

		private:
			data_type Data;
			dimensions_type Dimensions;
			format_type Format;
		};

	public:
		typedef mipmap_impl mipmap;

		image();
		image(level_type const & Levels);
		//image(mipmap const & Mipmap, bool GenerateMipmaps = false);

		~image();

		mipmap & operator[] (
			level_type const & Level);
		mipmap const & operator[] (
			level_type const & Level) const;

		level_type levels() const;
		format_type format() const;

		template <typename genType>
		void swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W);

	private:
		std::vector<mipmap> Mipmaps;
	};

//namespace wip
//{
//	// plain
//	template <typename genType>
//	class plain
//	{
//	public:
//		
//	private:
//		boost::shared_array<genType> Data;
//	};
//
//	// image
//	template
//	<
//		typename genType, 
//		template <typename> class surface = plain
//	>
//	class image
//	{
//	public:
//		typedef genType value_type;
//
//	private:
//		class mipmap_impl
//		{
//		public:
//			template <typename coordType>
//			value_type const & operator() (coordType const & Coord) const;
//
//		private:
//			surface<value_type> Surface;
//		};
//
//	public:
//		typedef mipmap_impl mipmap;
//		typedef std::vector<mipmap> mipmaps;
//		typedef typename mipmaps::size_type level_type;
//
//		level_type levels() const;
//		mipmap & operator[] (level_type Level);
//		mipmap const & operator[] (level_type Level) const;
//
//	private:
//		mipmaps Mipmaps;
//	};
//
//}//namespace wip
}//namespace gli

#include "image.inl"

#endif//GLI_IMAGE_INCLUDED
