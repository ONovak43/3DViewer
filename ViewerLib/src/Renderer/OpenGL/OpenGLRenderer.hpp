#pragma once
#include "Renderer/IRenderer.hpp"
#include "Renderer/IShaderProgram.hpp"
#include "Renderer/IShader.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/VertexArray.hpp"

namespace VL
{
	namespace OpenGL
	{
		class OpenGLRenderer : public IRenderer
		{
		public:
			OpenGLRenderer() = default;
			~OpenGLRenderer() override = default;
			static std::unique_ptr<IRenderer> create();
			void init() override;
			void setWindowHint() override;
			bool setContext(GLFWwindow* window) override;
			void onResize(uint32_t width, uint32_t height) override;
			void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
			void setClearColor(vec4 color) override;
			void clear() override;
			void enableDepthTesting() override;
			void disableDepthTesting() override;
			void enableStencilTesting() override;
			void disableStencilTesting() override;

			std::shared_ptr<IShaderProgram> createShaderProgram(const std::string& path) override;
			std::shared_ptr<IShader> createShader(const std::string& name) override;

			std::shared_ptr<IVertexBuffer> createVertexBuffer() override;
			std::shared_ptr<IVertexBuffer> createVertexBuffer(uint32_t size) override;
			std::shared_ptr<IVertexBuffer> createVertexBuffer(const std::vector<float>& data) override;
			std::shared_ptr<IIndexBuffer> createIndexBuffer(const std::vector<uint32_t>& data) override;
			std::shared_ptr<IVertexArray> createVertexArray() override;

			std::shared_ptr<ITexture> createTexture(uint32_t width, uint32_t height, TEXTURE_TYPE type) override;
			std::shared_ptr<ITexture> loadTexture(const std::string& path, TEXTURE_TYPE type) override;

		private:
			uint32_t depthTesting = 0;
			uint32_t stencilTesting = 0;
		};

		void onOpenGLMessage(
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam
		);
	}
}