#pragma once
#include "RendererAPI.hpp"
#include "IShaderProgram.hpp"
#include "IShader.hpp"
#include "Texture.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"

namespace VL
{
	class Renderer
	{
	public:
		void setRenderer(const std::string& type);
		void init();
		void setWindowHint();
		bool setContext(GLFWwindow* window);
		void swapBuffers(GLFWwindow* window);
		void onResize(uint32_t width, uint32_t height);
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void setClearColor(vec4 color);
		void clear();

		std::shared_ptr<IShaderProgram> createShaderProgram(const std::string& path);
		std::shared_ptr<IShader> createShader(const std::string& name);

		std::shared_ptr<IVertexBuffer> createVertexBuffer();
		std::shared_ptr<IVertexBuffer> createVertexBuffer(uint32_t size);
		std::shared_ptr<IVertexBuffer> createVertexBuffer(const std::vector<float>& data);
		std::shared_ptr<IIndexBuffer> createIndexBuffer(const std::vector<uint32_t>& data);
		std::shared_ptr<IVertexArray> createVertexArray();

		std::shared_ptr<ITexture> createTexture(uint32_t width, uint32_t height, TEXTURE_TYPE type);
		std::shared_ptr<ITexture> loadTexture(const std::string& path, TEXTURE_TYPE type);

		void renderTriangles(const std::shared_ptr<IVertexArray>& vertexArray, uint32_t indexCount = 0);
		
	private:
		std::unique_ptr<IRenderer> m_renderer;
	};
}
