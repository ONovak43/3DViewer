#include "pch.hpp"
#include "RendererAPI.hpp"

namespace VL
{
	using createCallback = std::function<std::unique_ptr<IRenderer>()>;
	std::map<std::string, createCallback> RendererAPI::m_renderers = {};

	void RendererAPI::registerRenderer(const std::string& type, createCallback cb)
	{
		m_renderers[type] = cb;
	}

	void RendererAPI::unregisterRenderer(const std::string& type)
	{
		m_renderers.erase(type);
	}

	std::unique_ptr<IRenderer> RendererAPI::createRenderer(const std::string& type)
	{
		auto rendererIt = m_renderers.find(type);

		if (rendererIt != m_renderers.end()) {
			return rendererIt->second();
		}
		
		return nullptr;
	}
}
