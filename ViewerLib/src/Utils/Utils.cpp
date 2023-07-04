#include "pch.hpp"
#include "Utils.hpp"
#include "Math/Vectors.hpp"
#include "Core/Application.hpp"
#include "Image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace VL
{
	namespace Utils
	{
		std::string readFile(const std::string& path)
		{
			std::ifstream file;

			file.open(path, std::ios::in);

			if (file.fail()) {
				std::cerr << "Failed to open the file: " << path << "\n";
			}

			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();

			return buffer.str();
		}

		std::shared_ptr<Image> loadImage(const std::string& path)
		{
			int32_t width;
			int32_t height;
			int32_t channels;
			const char* pathChar = path.c_str();
			uint8_t* data = stbi_load(pathChar, &width, &height, &channels, 0);

			if (data == nullptr) {
				std::cerr << "UTILS::LOAD_IMAGE::ERROR " << path << "\n";
				return nullptr;
			}

			return std::make_shared<Image>(data, width, height, channels);
		}

		void freeImage(uint8_t* image)
		{
			stbi_image_free(image);
		}
	}
}
