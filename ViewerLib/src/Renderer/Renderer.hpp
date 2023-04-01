#pragma once
#include "IRenderer.hpp"
#include "RendererAPI.hpp"
#include "Math/Vectors.hpp"

namespace VL
{
	class Renderer
	{
	public:
		void setRenderer(std::string type);
		void init();
		void setWindowHint();
		bool setContext(GLFWwindow* window);
		void swapBuffers(GLFWwindow* window);
		void onResize(uint32_t width, uint32_t height);
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void setClearColor(vec4 color);
		void clear();
	private:
		std::unique_ptr<IRenderer> m_renderer;
	};
}
