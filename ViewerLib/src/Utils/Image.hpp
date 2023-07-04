#pragma once

#include <cstdint>
#include <vector>

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

			Image(uint8_t* data, int32_t width, int32_t height, int32_t channels)
				: data(data), width(width), height(height), channels(channels)
			{
			}

			~Image()
			{
				freeImage(data);
			}
		};
	}
}