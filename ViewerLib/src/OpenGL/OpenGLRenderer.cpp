#include "pch.hpp"
#include "OpenGLRenderer.hpp"

namespace VL
{
	std::unique_ptr<IRenderer> OpenGLRenderer::create()
	{
		return std::make_unique<OpenGLRenderer>();
	}

	void OpenGLRenderer::setWindowHint()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		#if defined(_DEBUG)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif
	}

	bool OpenGLRenderer::setContext(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize OpenGL context.\n";
			return false;
		}

		return true;
	}
}
