#pragma once
#include "IRenderer.hpp"

#include <map>
#include <functional>

namespace VL
{
	class RendererAPI
	{
	public:
		using createCallback = std::function<std::unique_ptr<IRenderer>()>;

		static void registerRenderer(const std::string& type, createCallback cb);
		static void unregisterRenderer(const std::string& type);
		static std::unique_ptr<IRenderer> createRenderer(const std::string& type);

	private:
		using callbackMap = std::map<std::string, createCallback>;
		static callbackMap m_renderers;
	};
}

