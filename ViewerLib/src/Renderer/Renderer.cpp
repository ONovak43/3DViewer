#include "pch.hpp"
#include "Renderer.hpp"

namespace VL
{
	void Renderer::setRenderer(std::string type)
	{
		_renderer = RendererAPI::createRenderer(type);
	}

	void Renderer::setWindowHint()
	{
		ASSERT(_renderer != nullptr, "Renderer is not set");
		_renderer->setWindowHint();
	}

	bool Renderer::setContext(GLFWwindow* window)
	{
		ASSERT(_renderer != nullptr, "Renderer is not set");
		return _renderer->setContext(window);
	}

	void Renderer::swapBuffers(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}
}
