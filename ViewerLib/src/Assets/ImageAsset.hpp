#pragma once
#include "Asset.hpp"
#include "Utils/Utils.hpp"
#include "Utils/Image.hpp"

namespace VL
{
	class ImageAsset :
		public Asset<Utils::Image>
	{
	protected:
		std::shared_ptr<Utils::Image> loadAsset(const std::string& name) override
		{
			return Utils::loadImage(name);
		}
	};
}
