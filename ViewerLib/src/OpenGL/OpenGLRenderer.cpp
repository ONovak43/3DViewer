#include "pch.hpp"
#include "OpenGLRenderer.hpp"

namespace VL
{
	namespace OpenGL
	{
		std::unique_ptr<IRenderer> OpenGLRenderer::create()
		{
			return std::make_unique<OpenGLRenderer>();
		}

        void OpenGLRenderer::init()
        {
            #ifdef _DEBUG
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(onOpenGLMessage, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            #endif // _DEBUG

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
                {
                    glViewport(0, 0, width, height);
                }); // REMOVE

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cerr << "Failed to initialize OpenGL context.\n";
				return false;
			}
			return true;
		}

		void OpenGLRenderer::onResize(uint32_t width, uint32_t height)
		{
			glViewport(0, 0, width, height);
		}

        void OpenGLRenderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
			glViewport(x, y, width, height);
		}

        void OpenGLRenderer::setClearColor(vec4 color)
        {
			glClearColor(color[0], color[1], color[2], color[3]);
		}

        void OpenGLRenderer::clear()
        {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void GLAPIENTRY onOpenGLMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
            std::cerr << "-----------------\n";
            std::cerr << "DEBUG MESSAGE (" << id << "): " << message << "\n";

            if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            {
                return;
            }

            switch (source) {
            case GL_DEBUG_SOURCE_API:
                std::cerr << "Source: API";
                break;

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                std::cerr << "Source: WINDOW SYSTEM";
                break;

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                std::cerr << "Source: SHADER COMPILER";
                break;

            case GL_DEBUG_SOURCE_THIRD_PARTY:
                std::cerr << "Source: THIRD PARTY";
                break;

            case GL_DEBUG_SOURCE_APPLICATION:
                std::cerr << "Source: APPLICATION";
                break;

            case GL_DEBUG_SOURCE_OTHER:
                std::cerr << "Source: UNKNOWN";
                break;

            default:
                std::cerr << "Source: UNKNOWN";
                break;
            }

            std::cerr << "\n";

            switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                std::cerr << "Type: ERROR";
                break;

            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                std::cerr << "Type: DEPRECATED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                std::cerr << "Type: UDEFINED BEHAVIOR";
                break;

            case GL_DEBUG_TYPE_PORTABILITY:
                std::cerr << "Type: PORTABILITY";
                break;

            case GL_DEBUG_TYPE_PERFORMANCE:
                std::cerr << "Type: PERFORMANCE";
                break;

            case GL_DEBUG_TYPE_OTHER:
                std::cerr << "Type: OTHER";
                break;

            case GL_DEBUG_TYPE_MARKER:
                std::cerr << "Type: MARKER";
                break;

            default:
                std::cerr << "Type: UNKNOWN";
                break;
            }

            std::cerr << "\n";

            switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                std::cerr << "Severity: HIGH";
                break;

            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cerr << "Severity: MEDIUM";
                break;

            case GL_DEBUG_SEVERITY_LOW:
                std::cerr << "Severity: LOW";
                break;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                std::cerr << "Severity: NOTIFICATION";
                break;

            default:
                std::cerr << "Severity: UNKNOWN";
                break;
            }

            std::cerr << "-----------------\n";
            std::cerr << "\n";
		}
	}
}