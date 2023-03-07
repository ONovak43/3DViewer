#pragma once
#include "IRenderer.hpp"
#include "RendererAPI.hpp"

namespace VL
{
	class Renderer
	{
	public:
		void setRenderer(std::string type);
		void setWindowHint();
		bool setContext(GLFWwindow* window);
		void swapBuffers(GLFWwindow* window);
	private:
		std::unique_ptr<IRenderer> _renderer;
	};
}
