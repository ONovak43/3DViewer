#include "pch.hpp"
#include "Image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace VL
{
	namespace Utils
	{
		Image::Image(const std::string& path)
			: width(0), height(0), channels(0), data(nullptr)
		{
			const char* pathChar = path.c_str();
			data = stbi_load(pathChar, &width, &height, &channels, 0);

			if (data == nullptr) {
				std::cerr << "UTILS::LOAD_IMAGE::ERROR " << path << "\n";
			}
		}

		Image::~Image()
		{
			freeImage();	
		}

		void Image::freeImage()
		{
			if (data != nullptr) {
				stbi_image_free(data);
				data = nullptr;
			}
		}
	}
}