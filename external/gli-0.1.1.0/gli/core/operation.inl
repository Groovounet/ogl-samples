namespace gli
{
	namespace detail
	{


	}//namespace detail

	inline image duplicate(image const & Image2D)
	{
		image Result(Image2D.levels());
		for(std::size_t Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = duplicate(Image2D[Level]);
		return Result;
	}

	inline image flip(image const & Image2D)
	{
		image Result(Image2D.levels());
		for(std::size_t Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = flip(Image2D[Level]);
		return Result;
	}

	inline image mirror(image const & Image2D)
	{
		image Result(Image2D.levels());
		for(std::size_t Level = 0; Level < Image2D.levels(); ++Level)
			Result[Level] = mirror(Image2D[Level]);
		return Result;
	}

	inline image crop
	(
		image const & Image,
		glm::uvec2 const & Position,
		glm::uvec2 const & Size
	)
	{
		image Result(Image.levels());
		for(std::size_t Level = 0; Level < Image.levels(); ++Level)
			Result[Level] = crop(Image[Level], Position >> Level, Size >> Level);
		return Result;
	}

	inline image swizzle
	(
		image const & Image,
		glm::uvec4 const & Channel
	)
	{
		image Result(Image.levels());
		for(std::size_t Level = 0; Level < Image.levels(); ++Level)
			Result[Level] = swizzle(Image[Level], Channel);
		return Result;
	}

	inline mipmap duplicate(mipmap const & Mipmap2D)
	{
		mipmap Result(Mipmap2D.width(), Mipmap2D.height(), Mipmap2D.format());
		memcpy(Result.data(), Mipmap2D.data(), Mipmap2D.size());
		return Result;	
	}

	inline mipmap flip(mipmap const & Mipmap2D)
	{
		mipmap Result(Mipmap2D.width(), Mipmap2D.height(), Mipmap2D.format());
		
		std::size_t ValueSize = Result.value_size();
		glm::byte * DstPtr = Result.data();
		glm::byte const * const SrcPtr = Mipmap2D.data();

		for(std::size_t j = 0; j < Result.height(); ++j)
		for(std::size_t i = 0; i < Result.width(); ++i)
		{
			std::size_t DstIndex = (i + j * Result.height()) * ValueSize;
			std::size_t SrcIndex = (i + (Result.height() - j) * Result.width()) * ValueSize;
			memcpy(DstPtr + DstIndex, SrcPtr + SrcIndex, ValueSize);
		}

		return Result;
	}

	inline mipmap mirror(mipmap const & Mipmap2D)
	{
		mipmap Result(Mipmap2D.width(), Mipmap2D.height(), Mipmap2D.format());

		std::size_t ValueSize = Mipmap2D.value_size();
		glm::byte * DstPtr = Result.data();
		glm::byte const * const SrcPtr = Mipmap2D.data();

		for(std::size_t j = 0; j < Result.height(); ++j)
		for(std::size_t i = 0; i < Result.width(); ++i)
		{
			std::size_t DstIndex = (i + j * Result.width()) * ValueSize;
			std::size_t SrcIndex = ((Result.width() - i) + j * Result.width()) * ValueSize;
			memcpy(DstPtr + DstIndex, SrcPtr + SrcIndex, ValueSize);
		}

		return Result;
	}

	inline mipmap crop
	(
		mipmap const & Mipmap, 
		glm::uvec2 const & Position, 
		glm::uvec2 const & Size
	)
	{
		assert((Position.x + Size.x) <= Mipmap.width() && (Position.y + Size.y) <= Mipmap.height());

		mipmap Result(Size.x, Size.y, Mipmap.format());

		glm::byte* DstData = Result.data();
		glm::byte const * const SrcData = Mipmap.data();

		for(std::size_t j = 0; j < Size.y; ++j)
		{
			std::size_t DstIndex = 0                                + (0          + j) * Size.x         * Mipmap.value_size();
			std::size_t SrcIndex = Position.x * Mipmap.value_size() + (Position.y + j) * Mipmap.width() * Mipmap.value_size();
			memcpy(DstData + DstIndex, SrcData + SrcIndex, Mipmap.value_size() * Size.x);	
		}

		return Result;
	}

	inline mipmap copy
	(
		mipmap const & SrcMipmap, 
		glm::uvec2 const & SrcPosition,
		glm::uvec2 const & SrcSize,
		mipmap & DstMipmap, 
		glm::uvec2 const & DstPosition
	)
	{
		assert((SrcPosition.x + SrcSize.x) <= SrcMipmap.width() && (SrcPosition.y + SrcSize.y) <= SrcMipmap.height());
		assert(SrcMipmap.format() == DstMipmap.format());

		glm::byte * DstData = DstMipmap.data();
		glm::byte const * const SrcData = SrcMipmap.data();

		std::size_t SizeX = std::min(std::size_t(SrcSize.x + SrcPosition.x), std::size_t(DstMipmap.width()  + DstPosition.x));
		std::size_t SizeY = std::min(std::size_t(SrcSize.y + SrcPosition.y), std::size_t(DstMipmap.height() + DstPosition.y));

		for(std::size_t j = 0; j < SizeY; ++j)
		{
			std::size_t DstIndex = DstPosition.x * DstMipmap.value_size() + (DstPosition.y + j) * DstMipmap.width() * DstMipmap.value_size();
			std::size_t SrcIndex = SrcPosition.x * SrcMipmap.value_size() + (SrcPosition.y + j) * SrcMipmap.width() * SrcMipmap.value_size();
			memcpy(DstData + DstIndex, SrcData + SrcIndex, SrcMipmap.value_size() * SizeX);	
		}

		return DstMipmap;
	}

	inline mipmap swizzle
	(
		mipmap const & Mipmap, 
		glm::uvec4 const & Channel
	)
	{
		mipmap Result = duplicate(Mipmap);

		glm::byte * DataDst = Result.data();
		glm::byte const * const DataSrc = Mipmap.data();

		std::size_t CompSize = Mipmap.value_size() / Mipmap.components();
		std::size_t TexelCount = Mipmap.size() / Mipmap.value_size();

		for(std::size_t t = 0; t < TexelCount; ++t)
		for(std::size_t c = 0; c < Mipmap.components(); ++c)
		{
			std::size_t IndexSrc = t * Mipmap.components() + Channel[c];
			std::size_t IndexDst = t * Mipmap.components() + c;

			memcpy(DataDst + IndexDst, DataSrc + IndexSrc, CompSize);
		}

		return Result;
	}

	//inline mipmap operator+(mipmap const & MipmapA, mipmap const & MipmapB)
	//{
	//	
	//}

	//inline mipmap operator-(mipmap const & MipmapA, mipmap const & MipmapB)
	//{
	//	
	//}

	//inline mipmap operator*(mipmap const & MipmapA, mipmap const & MipmapB)
	//{
	//	
	//}

	//inline mipmap operator/(mipmap const & MipmapA, mipmap const & MipmapB)
	//{
	//	
	//}

}//namespace gli
