#include "pch.hpp"
#include "Renderer.hpp"
#include "Utils/Utils.hpp"

namespace VL
{
	void Renderer::setRenderer(const std::string& type)
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
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		glfwSwapBuffers(window);
	}

	void Renderer::onResize(uint32_t width, uint32_t height)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		m_renderer->onResize(width, height);
	}

	void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		m_renderer->setViewport(x, y, width, height);
	}

	void Renderer::setClearColor(vec4 color)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		m_renderer->setClearColor(color);
	}

	void Renderer::clear()
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		m_renderer->clear();
	}

	std::shared_ptr<IShaderProgram> Renderer::createShaderProgram(const std::string& path)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createShaderProgram(path);
	}

	std::shared_ptr<IShader> Renderer::createShader(const std::string& name)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createShader(name);
	}

	std::shared_ptr<IVertexBuffer> Renderer::createVertexBuffer()
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createVertexBuffer();
	}

	std::shared_ptr<IVertexBuffer> Renderer::createVertexBuffer(uint32_t size)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createVertexBuffer(size);
	}

	std::shared_ptr<IVertexBuffer> Renderer::createVertexBuffer(const std::vector<float>& data)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createVertexBuffer(data);
	}

	std::shared_ptr<IIndexBuffer> Renderer::createIndexBuffer(const std::vector<uint32_t>& data)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createIndexBuffer(data);
	}

	std::shared_ptr<IVertexArray> Renderer::createVertexArray()
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createVertexArray();
	}

	std::shared_ptr<ITexture> Renderer::createTexture(uint32_t width, uint32_t height, TEXTURE_TYPE type)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->createTexture(width, height, type);
	}

	std::shared_ptr<ITexture> Renderer::loadTexture(const std::string& path, TEXTURE_TYPE type)
	{
		ASSERT(m_renderer != nullptr, "Renderer is not set");
		return m_renderer->loadTexture(path, type);
	}


}
