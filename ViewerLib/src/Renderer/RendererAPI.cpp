#include "pch.hpp"
#include "RendererAPI.hpp"

namespace VL
{
	using createCallback = std::function<std::unique_ptr<IRenderer>()>;
	std::map<std::string, createCallback> RendererAPI::_renderers = {};

	void RendererAPI::registerRenderer(const std::string& type, createCallback cb)
	{
		_renderers[type] = cb;
	}

	void RendererAPI::unregisterRenderer(const std::string& type)
	{
		_renderers.erase(type);
	}

	std::unique_ptr<IRenderer> RendererAPI::createRenderer(const std::string& type)
	{
		auto rendererIt = _renderers.find(type);

		if (rendererIt != _renderers.end()) {
			return rendererIt->second();
		}
		
		return nullptr;
	}
}
