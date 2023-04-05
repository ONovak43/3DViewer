#pragma once
#include "Math/Vectors.hpp"
#include "Renderer/IShaderProgram.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/VertexArray.hpp"

namespace VL
{
	class IRenderer
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;
		IRenderer(const IRenderer&) = delete;
		IRenderer(IRenderer&) = delete;
		IRenderer(IRenderer&&) noexcept = delete;
		IRenderer& operator=(const IRenderer&) = delete;
		IRenderer& operator=(IRenderer&&) noexcept = delete;
		virtual void init() = 0;
		virtual void setWindowHint() = 0;
		virtual bool setContext(GLFWwindow* window) = 0;
		virtual void onResize(uint32_t width, uint32_t height) = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void setClearColor(vec4 color) = 0;
		virtual void clear() = 0;
		virtual void enableDepthTesting() = 0;
		virtual void disableDepthTesting() = 0;
		virtual void enableStencilTesting() = 0;
		virtual void disableStencilTesting() = 0;


		virtual std::shared_ptr<IShaderProgram> createShaderProgram(const std::string& path) = 0;
		virtual std::shared_ptr<Shader> createShader(const std::string& name) = 0;

		virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(uint32_t size) = 0;
		virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(const std::vector<float>& data) = 0;
		virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(const std::vector<uint32_t>& data) = 0;
		virtual std::shared_ptr<VertexArray> createVertexArray() = 0;

		virtual std::shared_ptr<ITexture> createTexture(uint32_t width, uint32_t height, TEXTURE_TYPE type) = 0;
		virtual std::shared_ptr<ITexture> createTexture(const std::string& path, TEXTURE_TYPE type) = 0;

	};
}

