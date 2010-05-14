#include <fstream>

namespace gli{
namespace detail{

	// DirectDraw's structures 
	struct DDPixelFormat
	{
		glm::uint32 size;
		glm::uint32 flags;
		glm::uint32 fourCC;
		glm::uint32 bpp;
		glm::uint32 redMask;
		glm::uint32 greenMask;
		glm::uint32 blueMask;
		glm::uint32 alphaMask;
	};

	struct DDSCaps
	{
		glm::uint32 caps;
		glm::uint32 caps2;
		glm::uint32 caps3;
		glm::uint32 caps4;
	};

	struct DDColorKey
	{
		glm::uint32 lowVal;
		glm::uint32 highVal;
	};

	struct DDSurfaceDesc
	{
		glm::uint32 size;
		glm::uint32 flags;
		glm::uint32 height;
		glm::uint32 width;
		glm::uint32 pitch;
		glm::uint32 depth;
		glm::uint32 mipMapLevels;
		glm::uint32 alphaBitDepth;
		glm::uint32 reserved;
		glm::uint32 surface;

		DDColorKey ckDestOverlay;
		DDColorKey ckDestBlt;
		DDColorKey ckSrcOverlay;
		DDColorKey ckSrcBlt;

		DDPixelFormat format;
		DDSCaps caps;

		glm::uint32 textureStage;
	};

	#define GLI_MAKEFOURCC(ch0, ch1, ch2, ch3) \
	  (glm::uint32)( \
		(((glm::uint32)(glm::uint8)(ch3) << 24) & 0xFF000000) | \
		(((glm::uint32)(glm::uint8)(ch2) << 16) & 0x00FF0000) | \
		(((glm::uint32)(glm::uint8)(ch1) <<  8) & 0x0000FF00) | \
		 ((glm::uint32)(glm::uint8)(ch0)        & 0x000000FF) )

	glm::uint32 const GLI_FOURCC_DXT1 = GLI_MAKEFOURCC('D', 'X', 'T', '1');
	glm::uint32 const GLI_FOURCC_DXT3 = GLI_MAKEFOURCC('D', 'X', 'T', '3');
	glm::uint32 const GLI_FOURCC_DXT5 = GLI_MAKEFOURCC('D', 'X', 'T', '5');

	glm::uint32 const GLI_FOURCC_RXGB                          = 0x42475852;         // RXGB (AKA DOOM III)
	glm::uint32 const GLI_FOURCC_ATI1                          = 0x31495441;         // ATI1
	glm::uint32 const GLI_FOURCC_ATI2                          = 0x32495441;         // ATI2 (AKA 3Dc)
	glm::uint32 const GLI_FOURCC_A2XY                          = 0x59583241;         // A2XY
	glm::uint32 const GLI_FOURCC_DX10                          = 0x30315844;         // DX10
	glm::uint32 const GLI_FOURCC_R16F                          = 0x0000006f;         // 16-bit float Red
	glm::uint32 const GLI_FOURCC_G16R16F                       = 0x00000070;         // 16-bit float Red/Green
	glm::uint32 const GLI_FOURCC_A16B16G16R16F                 = 0x00000071;         // 16-bit float RGBA
	glm::uint32 const GLI_FOURCC_R32F                          = 0x00000072;         // 32-bit float Red
	glm::uint32 const GLI_FOURCC_G32R32F                       = 0x00000073;         // 32-bit float Red/Green
	glm::uint32 const GLI_FOURCC_A32B32G32R32F                 = 0x00000074;         // 32-bit float RGBA

	glm::uint32 const GLI_DDPF_ALPHAPIXELS							= 0x00000001; // The surface has alpha channel information in the pixel format.
	glm::uint32 const GLI_DDPF_ALPHA								= 0x00000002; // The pixel format contains alpha only information
	glm::uint32 const GLI_DDPF_FOURCC                               = 0x00000004; // The FourCC code is valid.
	glm::uint32 const GLI_DDPF_RGB									= 0x00000040; // The RGB data in the pixel format structure is valid.
	glm::uint32 const GLI_DDPF_COMPRESSED							= 0x00000080; // The surface will accept pixel data in the format specified and compress it during the write.
	glm::uint32 const GLI_DDPF_RGBTOYUV								= 0x00000100; // The surface will accept RGB data and translate it during the write to YUV data.
	glm::uint32 const GLI_DDPF_YUV                                  = 0x00000200; // Pixel format is YUV - YUV data in pixel format struct is valid.
	glm::uint32 const GLI_DDPF_ZBUFFER                              = 0x00000400; // Pixel format is a z buffer only surface
	glm::uint32 const GLI_DDPF_ZPIXELS                              = 0x00002000; // The surface contains Z information in the pixels
	glm::uint32 const GLI_DDPF_STENCILBUFFER                        = 0x00004000; // The surface contains stencil information along with Z
	glm::uint32 const GLI_DDPF_ALPHAPREMULT                         = 0x00008000; // Premultiplied alpha format -- the color components have been premultiplied by the alpha component.
	glm::uint32 const GLI_DDPF_LUMINANCE                            = 0x00020000; // Luminance data in the pixel format is valid.
	glm::uint32 const GLI_DDPF_BUMPLUMINANCE                        = 0x00040000; // Use this flag for luminance-only or luminance+alpha surfaces, the bit depth is then ddpf.dwLuminanceBitCount.
	glm::uint32 const GLI_DDPF_BUMPDUDV                             = 0x00080000; // Bump map dUdV data in the pixel format is valid.

	glm::uint32 const GLI_MIPMAPCOUNT = 131072;

	enum dds_format
	{
		GLI_D3DFMT_R8G8B8               = 20,
		GLI_D3DFMT_A8R8G8B8             = 21,
		GLI_D3DFMT_X8R8G8B8             = 22,
		GLI_D3DFMT_A8                   = 28,
		GLI_D3DFMT_A2B10G10R10          = 31,
		GLI_D3DFMT_A8B8G8R8             = 32,
		GLI_D3DFMT_X8B8G8R8             = 33,
		GLI_D3DFMT_G16R16               = 34,
		GLI_D3DFMT_A2R10G10B10          = 35,
		GLI_D3DFMT_A16B16G16R16         = 36,

		GLI_D3DFMT_L8                   = 50,
		GLI_D3DFMT_A8L8                 = 51,

		GLI_D3DFMT_DXT1                 = GLI_MAKEFOURCC('D', 'X', 'T', '1'),
		GLI_D3DFMT_DXT2                 = GLI_MAKEFOURCC('D', 'X', 'T', '2'),
		GLI_D3DFMT_DXT3                 = GLI_MAKEFOURCC('D', 'X', 'T', '3'),
		GLI_D3DFMT_DXT4                 = GLI_MAKEFOURCC('D', 'X', 'T', '4'),
		GLI_D3DFMT_DXT5                 = GLI_MAKEFOURCC('D', 'X', 'T', '5'),

		GLI_D3DFMT_D32                  = 71,
		GLI_D3DFMT_D24S8                = 75,
		GLI_D3DFMT_D24X8                = 77,
		GLI_D3DFMT_D16                  = 80,
		GLI_D3DFMT_L16                  = 81,
		GLI_D3DFMT_D32F_LOCKABLE        = 82,
		GLI_D3DFMT_D24FS8               = 83,

		GLI_D3DFMT_R16F                 = 111,
		GLI_D3DFMT_G16R16F              = 112,
		GLI_D3DFMT_A16B16G16R16F        = 113,

		GLI_D3DFMT_R32F                 = 114,
		GLI_D3DFMT_G32R32F              = 115,
		GLI_D3DFMT_A32B32G32R32F        = 116
	};

	struct DDLoader
	{
		glm::uint32 DivSize;
		glm::uint32 BlockSize;
		gli::format Format;
	};

	//struct DdsLoadInfo {
	//  bool compressed;
	//  bool swap;
	//  bool palette;
	//  unsigned int divSize;
	//  unsigned int blockBytes;
	//  GLenum internalFormat;
	//  GLenum externalFormat;
	//  GLenum type;
	//};

	//DdsLoadInfo loadInfoDXT1 = {
	//  true, false, false, 4, 8, GL_COMPRESSED_RGBA_S3TC_DXT1
	//};
	//DdsLoadInfo loadInfoDXT3 = {
	//  true, false, false, 4, 16, GL_COMPRESSED_RGBA_S3TC_DXT3
	//};
	//DdsLoadInfo loadInfoDXT5 = {
	//  true, false, false, 4, 16, GL_COMPRESSED_RGBA_S3TC_DXT5
	//};
	//DdsLoadInfo loadInfoBGRA8 = {
	//  false, false, false, 1, 4, GL_RGBA8, GL_BGRA, GL_UNSIGNED_BYTE
	//};
	//DdsLoadInfo loadInfoBGR8 = {
	//  false, false, false, 1, 3, GL_RGB8, GL_BGR, GL_UNSIGNED_BYTE
	//};
	//DdsLoadInfo loadInfoBGR5A1 = {
	//  false, true, false, 1, 2, GL_RGB5_A1, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV
	//};
	//DdsLoadInfo loadInfoBGR565 = {
	//  false, true, false, 1, 2, GL_RGB5, GL_RGB, GL_UNSIGNED_SHORT_5_6_5
	//};
	//DdsLoadInfo loadInfoIndex8 = {
	//  false, false, true, 1, 1, GL_RGB8, GL_BGRA, GL_UNSIGNED_BYTE
	//};

	inline image loadDDS(std::string const & Filename)
	{
		std::ifstream FileIn(Filename.c_str(), std::ios::in | std::ios::binary);
		if(FileIn.fail())
			return image();

		DDSurfaceDesc SurfaceDesc;
		char Magic[4]; 

		//* Read magic number and check if valid .dds file 
		FileIn.read((char*)&Magic, sizeof(Magic));

		assert(strncmp(Magic, "DDS ", 4) == 0);

		// Get the surface descriptor 
		FileIn.read((char*)&SurfaceDesc, sizeof(SurfaceDesc));

		std::size_t Width = SurfaceDesc.width;
		std::size_t Height = SurfaceDesc.height;

		//std::size_t Levels = glm::max(glm::highestBit(Width), glm::highestBit(Height));

		DDLoader Loader;
		if(SurfaceDesc.format.flags & GLI_DDPF_FOURCC)
		{
			switch(SurfaceDesc.format.fourCC)
			{
			case GLI_FOURCC_DXT1:
				Loader.DivSize = 4;
				Loader.BlockSize = 8;
				Loader.Format = DXT1;
				break;
			case GLI_FOURCC_DXT3:
				Loader.DivSize = 4;
				Loader.BlockSize = 16;
				Loader.Format = DXT3;
				break;
			case GLI_FOURCC_DXT5:
				Loader.DivSize = 4;
				Loader.BlockSize = 16;
				Loader.Format = DXT5;
				break;
			case GLI_FOURCC_R16F:
				Loader.DivSize = 1;
				Loader.BlockSize = 2;
				Loader.Format = R16F;
				break;
			case GLI_FOURCC_G16R16F:
				Loader.DivSize = 1;
				Loader.BlockSize = 4;
				Loader.Format = RG16F;
				break;
			case GLI_FOURCC_A16B16G16R16F:
				Loader.DivSize = 1;
				Loader.BlockSize = 8;
				Loader.Format = RGBA16F;
				break;
			case GLI_FOURCC_R32F:
				Loader.DivSize = 1;
				Loader.BlockSize = 4;
				Loader.Format = R32F;
				break;
			case GLI_FOURCC_G32R32F:
				Loader.DivSize = 1;
				Loader.BlockSize = 8;
				Loader.Format = RG32F;
				break;
			case GLI_FOURCC_A32B32G32R32F:
				Loader.DivSize = 1;
				Loader.BlockSize = 16;
				Loader.Format = RGBA32F;
				break;

			default:
				assert(0);
				return image();
			}
		}
		else if(SurfaceDesc.format.flags & GLI_DDPF_RGB)
		{
			switch(SurfaceDesc.format.bpp)
			{
			case 8:
				Loader.DivSize = 1;
				Loader.BlockSize = 2;
				Loader.Format = R8U;
				break;
			case 16:
				Loader.DivSize = 1;
				Loader.BlockSize = 2;
				Loader.Format = RG8U;
				break;
			case 24:
				Loader.DivSize = 1;
				Loader.BlockSize = 3;
				Loader.Format = RGB8U;
				break;
			case 32:
				Loader.DivSize = 1;
				Loader.BlockSize = 4;
				Loader.Format = RGBA8U;
				break;
			}
		}
		else
		{


		}

		gli::format Format = Loader.Format;

		std::streamoff Curr = FileIn.tellg();
		FileIn.seekg(0, std::ios_base::end);
		std::streamoff End = FileIn.tellg();
		FileIn.seekg(Curr, std::ios_base::beg);

		std::vector<glm::byte> Data(std::size_t(End - Curr), 0);
		std::size_t Offset = 0;

		FileIn.read((char*)&Data[0], Data.size());

		//image Image(glm::min(MipMapCount, Levels));//SurfaceDesc.mipMapLevels);
		std::size_t MipMapCount = (SurfaceDesc.flags & GLI_MIPMAPCOUNT) ? SurfaceDesc.mipMapLevels : 1;
		//if(Loader.Format == DXT1 || Loader.Format == DXT3 || Loader.Format == DXT5) 
		//	MipMapCount -= 2;
		image Image(MipMapCount);
		for(std::size_t Level = 0; Level < Image.levels() && (Width || Height); ++Level)
		{
			Width = glm::max(std::size_t(Width), std::size_t(1));
			Height = glm::max(std::size_t(Height), std::size_t(1));

			std::size_t MipmapSize = 0;
			if(Loader.Format == DXT1 || Loader.Format == DXT3 || Loader.Format == DXT5)
				MipmapSize = ((Width + 3) >> 2) * ((Height + 3) >> 2) * Loader.BlockSize;
			else
				MipmapSize = Width * Height * Loader.BlockSize;
			std::vector<glm::byte> MipmapData(MipmapSize, 0);

			memcpy(&MipmapData[0], &Data[0] + Offset, MipmapSize);

			image::dimensions_type Dimensions(Width, Height, std::size_t(1));
			Image[Level] = image::mipmap(Dimensions, Format, MipmapData);

			Offset += MipmapSize;
			Width >>= 1;
			Height >>= 1;
		}

		return Image;
	}

	inline image loadTGA(std::string const & Filename)
	{
		std::ifstream FileIn(Filename.c_str(), std::ios::in | std::ios::binary);
		if(!FileIn)
			return image();

		unsigned char IdentificationFieldSize;
		unsigned char ColorMapType;
		unsigned char ImageType;
		unsigned short ColorMapOrigin;
		unsigned short ColorMapLength;
		unsigned char ColorMapEntrySize;
		unsigned short OriginX;
		unsigned short OriginY;
		unsigned short Width;
		unsigned short Height;
		unsigned char TexelSize;
		unsigned char Descriptor;

		FileIn.read((char*)&IdentificationFieldSize, sizeof(IdentificationFieldSize));
		FileIn.read((char*)&ColorMapType, sizeof(ColorMapType));
		FileIn.read((char*)&ImageType, sizeof(ImageType));
		FileIn.read((char*)&ColorMapOrigin, sizeof(ColorMapOrigin));
		FileIn.read((char*)&ColorMapLength, sizeof(ColorMapLength));
		FileIn.read((char*)&ColorMapEntrySize, sizeof(ColorMapEntrySize));
		FileIn.read((char*)&OriginX, sizeof(OriginX));
		FileIn.read((char*)&OriginY, sizeof(OriginY));
		FileIn.read((char*)&Width, sizeof(Width));
		FileIn.read((char*)&Height, sizeof(Height));
		FileIn.read((char*)&TexelSize, sizeof(TexelSize));
		FileIn.read((char*)&Descriptor, sizeof(Descriptor));

		gli::format Format = gli::FORMAT_NULL;
		if(TexelSize == 24)
			Format = gli::RGB8U;
		else if(TexelSize == 32)
			Format = gli::RGBA8U;
		else
			assert(0);

		image::mipmap Mipmap(glm::uvec3(Width, Height, (unsigned short)1), Format);

		if (FileIn.fail() || FileIn.bad())
		{
			assert(0);
			return image();
		}

		switch(ImageType)
		{
		default:
			assert(0);
			return image();

		case 2:
			FileIn.seekg(18 + ColorMapLength, std::ios::beg);

			char* IdentificationField = new char[IdentificationFieldSize + 1];
			FileIn.read(IdentificationField, IdentificationFieldSize);
			IdentificationField[IdentificationFieldSize] = '\0';
			delete[] IdentificationField;

			std::size_t DataSize = Width * Height * (TexelSize >> 3);
			FileIn.read((char*)Mipmap.data(), DataSize);

			if(FileIn.fail() || FileIn.bad())
				return image();
			break;
		}

		FileIn.close();

		image Image(1);
		Image[0] = Mipmap;

		// TGA images are saved in BGR or BGRA format.
		if(TexelSize == 24)
			Image.swizzle<glm::u8vec3>(glm::B, glm::G, glm::R, glm::A);
		if(TexelSize == 32)
			Image.swizzle<glm::u8vec4>(glm::B, glm::G, glm::R, glm::A);

		return Image;
	}

	inline void saveTGA(gli::image const & ImageIn, std::string const & Filename)
	{
		std::ofstream FileOut(Filename.c_str(), std::ios::out | std::ios::binary);
		if (!FileOut)
			return;

		gli::image Image = duplicate(ImageIn);

		unsigned char IdentificationFieldSize = 1;
		unsigned char ColorMapType = 0;
		unsigned char ImageType = 2;
		unsigned short ColorMapOrigin = 0;
		unsigned short ColorMapLength = 0;
		unsigned char ColorMapEntrySize = 0;
		unsigned short OriginX = 0;
		unsigned short OriginY = 0;
		unsigned short Width = Image[0].dimensions().x;
		unsigned short Height = Image[0].dimensions().y;
		unsigned char TexelSize = (unsigned char)(Image[0].value_size() << 3);
		unsigned char Descriptor = 0;

		if(TexelSize == 24)
			Image.swizzle<glm::u8vec3>(glm::B, glm::G, glm::R, glm::A);
		if(TexelSize == 32)
			Image.swizzle<glm::u8vec4>(glm::B, glm::G, glm::R, glm::A);

		FileOut.write((char*)&IdentificationFieldSize, sizeof(IdentificationFieldSize));
		FileOut.write((char*)&ColorMapType, sizeof(ColorMapType));
		FileOut.write((char*)&ImageType, sizeof(ImageType));
		FileOut.write((char*)&ColorMapOrigin, sizeof(ColorMapOrigin));
		FileOut.write((char*)&ColorMapLength, sizeof(ColorMapLength));
		FileOut.write((char*)&ColorMapEntrySize, sizeof(ColorMapEntrySize));
		FileOut.write((char*)&OriginX, sizeof(OriginX));
		FileOut.write((char*)&OriginY, sizeof(OriginY));
		FileOut.write((char*)&Width, sizeof(Width));
		FileOut.write((char*)&Height, sizeof(Height));
		FileOut.write((char*)&TexelSize, sizeof(TexelSize));
		FileOut.write((char*)&Descriptor, sizeof(Descriptor));

		if (FileOut.fail () || FileOut.bad ())
			return;

		FileOut.seekp(18 + ColorMapLength, std::ios::beg);
		char* IdentificationField = new char[IdentificationFieldSize + 1];
		FileOut.write(IdentificationField, IdentificationFieldSize);
		delete[] IdentificationField;
		FileOut.write((char*)Image[0].data(), Image[0].capacity());
		if(FileOut.fail() || FileOut.bad())
			return;

		FileOut.close ();
	}

}//namespace detail

inline image import_as
(
	std::string const & Filename
)
{
	if(Filename.find(".tga") != std::string::npos)
		return detail::loadTGA(Filename);
	else if(Filename.find(".dds") != std::string::npos)
		return detail::loadDDS(Filename);
	else
	{
		assert(0); // Format unknowned
		return image();
	}
}

inline void export_as
(
	image const & Image, 
	std::string const & Filename
)
{
	if(Filename.find(".tga"))
		return detail::saveTGA(Image, Filename);
}

inline void export_as
(
	image const & Image, 
	image::level_type const & Level,
	std::string const & Filename
)
{
	gli::image Mipmap(1);
	Mipmap[0] = Image[Level];
	gli::export_as(Mipmap, Filename);
}

}//namespace gli

