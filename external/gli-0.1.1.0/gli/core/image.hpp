#ifndef GLI_IMAGE_INCLUDED
#define GLI_IMAGE_INCLUDED

#include "mipmap.hpp"

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

	class image
	{
	public:
		image();
		image(std::size_t Levels);
		image(mipmap const & Mipmap, bool GenerateMipmaps = false);

		~image();

		mipmap & operator[] (std::size_t Level);
		mipmap const & operator[] (std::size_t Level) const;

		std::size_t width() const;
		std::size_t height() const;
		std::size_t depth() const;

		std::size_t levels() const;
		gli::format format() const;

		template <typename genType>
		void swizzle(glm::comp X, glm::comp Y, glm::comp Z, glm::comp W);

		//ToDo
		//template <typename genType>
		//genType textureLod(glm::vec2 const & texcoord, float lod) const;

		//ToDo
		//template <typename genType>
		//genType texelFetch(glm::ivec2 const & texcoord, int lod) const;

		bool generateMipmaps(std::size_t BaseLevel);

	private:
		std::vector<mipmap> Mipmaps;
	};

}//namespace gli

#include "image.inl"

#endif//GLI_IMAGE_INCLUDED
