#include "pch.hpp"
#include "Renderer.hpp"

namespace VL
{
	void Renderer::setRenderer(std::string type)
	{
		m_renderer = RendererAPI::createRenderer(type);
	}

	void Renderer::init()
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		m_renderer->init();
	}

	void Renderer::setWindowHint()
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		m_renderer->setWindowHint();
	}

	bool Renderer::setContext(GLFWwindow* window)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->setContext(window);
	}

	void Renderer::swapBuffers(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}

	void Renderer::onResize(uint32_t width, uint32_t height)
	{
		m_renderer->onResize(width, height);
	}

	void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		m_renderer->setViewport(x, y, width, height);
	}

	void Renderer::setClearColor(vec4 color)
	{
		m_renderer->setClearColor(color);
	}

	void Renderer::clear()
	{
		m_renderer->clear();
	}
}
