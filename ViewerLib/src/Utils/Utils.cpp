#include "pch.hpp"
#include "Utils.hpp"

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
	}
}
