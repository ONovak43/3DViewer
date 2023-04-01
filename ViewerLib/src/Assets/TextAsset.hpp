#pragma once
#include "Asset.hpp"
#include "Utils/Utils.hpp"

namespace VL
{
	class TextAsset :
		public Asset<std::string>
	{
	protected:
		std::shared_ptr<std::string> loadAsset(const std::string& name) override
		{
			return std::make_shared<std::string>(Utils::readFile(name));
		}
	};
}