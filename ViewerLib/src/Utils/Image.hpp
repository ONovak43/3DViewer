#pragma once
#include <cstdint>


namespace VL
{
	namespace Utils
	{
		struct Image
		{
			int32_t width;
			int32_t height;
			int32_t channels;
			uint8_t* data;

			Image(const std::string& path);
			Image(const Image&) = delete;
			Image& operator=(const Image&) = delete;
			~Image();

			void freeImage();
		};
	}
}