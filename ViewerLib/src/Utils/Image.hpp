#pragma once
#include <cstdint>
#include <vector>

namespace VL
{
	namespace Utils
	{
		struct Image
		{
			uint32_t width;
			uint32_t height;
			std::vector<uint8_t> data;

			Image(std::vector<uint8_t> data, uint32_t width, uint32_t height)
				: data(data), width(width), height(height)
			{
			}
		};
	}
}