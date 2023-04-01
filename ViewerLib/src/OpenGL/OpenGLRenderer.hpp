#pragma once
#include "Renderer/IRenderer.hpp"
#include "Math/Vectors.hpp"

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