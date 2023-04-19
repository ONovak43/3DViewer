#include "pch.hpp"
#include "Utils.hpp"
#include "lodepng.h"
#include "Math/Vectors.hpp"
#include "Core/Application.hpp"

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
			std::vector<uint8_t> image;
			uint32_t width;
			uint32_t height;
			auto* pathChar = path.c_str();

			auto error = lodepng::decode(image, width, height, pathChar);

			if (error != 0) {
				std::cerr << "UTILS::LOAD_IMAGE::ERROR " << error << ": " << lodepng_error_text(error) << "\n";
				return nullptr;
			}

			return std::make_shared<Image>(image, width, height);
		}
	}
}
