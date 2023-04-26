#pragma once
#include <memory>
#include <unordered_map>
#include <string>

namespace VL
{
	template<class T>
	class Asset
	{
	public:
		Asset() = default;
		virtual ~Asset() = default;

		std::shared_ptr<T> getAsset(const std::string& name, bool cache = true);

	protected:
		virtual std::shared_ptr<T> loadAsset(const std::string& name) = 0;

	private:
		std::unordered_map<std::string, std::shared_ptr<T>> m_assets;
	};
}

#include "Asset.inl"