#include "pch.hpp"
#include "Window.hpp"

namespace VL
{
	class Window::Impl
	{
	public:
		void setCallbacks(IEventManager& eventManager);
	public:
		static Window* instancePtr;
		GLFWwindow* window = nullptr;
		WindowProperties props = WindowProperties();
	};

	Window* Window::Impl::instancePtr = nullptr;

	void closeWindowCallback(GLFWwindow* window) {
		auto eventManager = static_cast<IEventManager*>(glfwGetWindowUserPointer(window));
		eventManager->notify(IEventManager::EVENT_TYPE::WINDOW_CLOSE, std::make_shared<WindowCloseEvent>());
	}

	void Window::Impl::setCallbacks(IEventManager& eventManager) {
		glfwSetWindowUserPointer(window, &eventManager);
		glfwSetWindowCloseCallback(window, closeWindowCallback);
	}

	Window::Window()
		: _impl(std::make_unique<Window::Impl>())
	{
		ASSERT(_impl->instancePtr == nullptr, "The VL supports only one window.");
		_impl->instancePtr = this;
	}

	Window::~Window()
	{
		glfwDestroyWindow(_impl->window);
		_impl->window = nullptr;
		_impl->instancePtr = nullptr;
		glfwTerminate();
	}

	Window::ERROR_CODE Window::create(const WindowProperties& props, Renderer& renderer, IEventManager& eventManager)
	{
		ASSERT(_impl->window == nullptr, "The window is already instantiated.");

		if (glfwInit() == GLFW_FALSE) {
			std::cerr << "GLFW_INIT FAILED\n";
			glfwTerminate();
		};

		renderer.setWindowHint();
		
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		_impl->window = glfwCreateWindow(
			(int)props.width,
			(int)props.height,
			props.name.c_str(),
			nullptr,
			nullptr
		);

		if (!_impl->window)
		{
			std::cerr << "WINDOW CREATION FAILED\n";
			glfwTerminate();
		}

		renderer.setContext(_impl->window);

		_impl->setCallbacks(eventManager);
		return ERROR_CODE::NONE;
	}

	Window::ERROR_CODE Window::update(Renderer& renderer)
	{
		renderer.swapBuffers(_impl->window);
		glfwPollEvents();
		return ERROR_CODE();
	}

	uint32_t Window::getWidth() const
	{
		return _impl->props.width;
	}

	void Window::setWidth(uint32_t width)
	{
		_impl->props.width = width;
	}

	uint32_t Window::getHeight() const
	{
		return _impl->props.height;
	}

	void Window::setHeight(uint32_t height)
	{
		_impl->props.height = height;
	}

	GLFWwindow* Window::getContext()
	{
		return _impl->window;
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(_impl->window);
	}
}
