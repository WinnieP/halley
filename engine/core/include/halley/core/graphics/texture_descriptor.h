#pragma once

#include <halley/maths/vector2.h>
#include "halley/file_formats/image.h"

namespace Halley
{
	enum class TextureFormat
	{
		Indexed,
		RGB,
		RGBA,
		DEPTH
	};

	template <>
	struct EnumNames<TextureFormat> {
		constexpr std::array<const char*, 4> operator()() const {
			return{{
				"indexed",
				"rgb",
				"rgba",
				"depth"
			}};
		}
	};

	enum class PixelDataFormat
	{
		Image,
		Precompiled
	};

	
	class TextureDescriptorImageData
	{
	public:
		TextureDescriptorImageData();
		TextureDescriptorImageData(std::unique_ptr<Image> img);
		TextureDescriptorImageData(Bytes&& bytes);
		TextureDescriptorImageData(TextureDescriptorImageData&& other) noexcept;
		TextureDescriptorImageData(gsl::span<const gsl::byte> bytes);

		TextureDescriptorImageData& operator=(TextureDescriptorImageData&& other) noexcept;

		bool empty() const;
		Byte* getBytes();

		Bytes moveBytes();

	private:
		std::unique_ptr<Image> img;
		Bytes rawBytes;
		bool isRaw = false;
	};

	class TextureDescriptor
	{
	public:
		Vector2i size;
		size_t padding = 0;
		TextureFormat format = TextureFormat::RGBA;
		PixelDataFormat pixelFormat = PixelDataFormat::Image;
		bool useMipMap = false;
		bool useFiltering = false;
		TextureDescriptorImageData pixelData;

		static int getBitsPerPixel(TextureFormat format);

		TextureDescriptor() {}
		TextureDescriptor(Vector2i size, TextureFormat format = TextureFormat::RGBA)
			: size(size)
			, format(format)
		{}
	};
}
