#include "pch.hpp"
#include "Window.hpp"
#include "Renderer/Renderer.hpp"
#include "Event/EventManager.hpp"
#include <Event/Events.hpp>

namespace VL
{
	class Window::Impl
	{
	public:
		void setCallbacks(IEventManager& eventManager);
	public:
		bool m_vSync = false;
		static Window* m_instancePtr;
		GLFWwindow* m_window = nullptr;
		WindowProperties m_props = WindowProperties();
	};

	Window* Window::Impl::m_instancePtr = nullptr;

	void Window::Impl::setCallbacks(IEventManager& eventManager) {
		glfwSetWindowUserPointer(m_window, &eventManager);
	
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			auto eventManager = static_cast<IEventManager*>(glfwGetWindowUserPointer(window));
			eventManager->notify(IEventManager::EVENT_TYPE::WINDOW_CLOSE, std::make_shared<WindowCloseEvent>());
		});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			auto eventManager = static_cast<IEventManager*>(glfwGetWindowUserPointer(window));
			eventManager->notify(IEventManager::EVENT_TYPE::WINDOW_RESIZE, std::make_shared<WindowResizeEvent>(width, height));
		});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y) {
			auto eventManager = static_cast<IEventManager*>(glfwGetWindowUserPointer(window));
			eventManager->notify(IEventManager::EVENT_TYPE::WINDOW_MOVE, std::make_shared<WindowMoveEvent>(x, y));
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto eventManager = static_cast<IEventManager*>(glfwGetWindowUserPointer(window));
			auto keyCasted = static_cast<KeyboardEvent::KEY_CODES>(key);
			switch (action) {
			case GLFW_PRESS:
				eventManager->notify(IEventManager::EVENT_TYPE::KEY_PRESSED, std::make_shared<KeyPressEvent>(keyCasted));
				break;
			case GLFW_RELEASE:
				eventManager->notify(IEventManager::EVENT_TYPE::KEY_RELEASED, std::make_shared<KeyReleaseEvent>(keyCasted));
				break;
			/*case GLFW_REPEAT:
				eventManager->notify(IEventManager::EVENT_TYPE::KEY_REPEAT, std::make_shared<KeyRepeatEvent>(key));
				break;*/
			}
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			auto eventManager = static_cast<IEventManager*>(glfwGetWindowUserPointer(window));
			eventManager->notify(IEventManager::EVENT_TYPE::MOUSE_MOVED, std::make_shared<MouseMoveEvent>(xpos, ypos));
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			auto eventManager = static_cast<IEventManager*>(glfwGetWindowUserPointer(window));
			auto btnCasted = static_cast<MouseButtonEvent::MOUSE_CODES>(button);

			switch (action)
			{
			case GLFW_PRESS:
				eventManager->notify(IEventManager::EVENT_TYPE::MOUSE_BUTTON_PRESSED, std::make_shared<MouseButtonPressEvent>(btnCasted));
				break;
			case GLFW_RELEASE:
				eventManager->notify(IEventManager::EVENT_TYPE::MOUSE_BUTTON_RELEASED, std::make_shared<MouseButtonReleaseEvent>(btnCasted));
				break;
			}
		});
	}

	Window::Window()
		: m_impl(std::make_unique<Window::Impl>())
	{
		ASSERT(m_impl->m_instancePtr == nullptr, "The VL supports only one window.");
		m_impl->m_instancePtr = this;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_impl->m_window);
		m_impl->m_window = nullptr;
		m_impl->m_instancePtr = nullptr;
		glfwTerminate();
	}

	Window::ERROR_CODE Window::create(const WindowProperties& props, Renderer& renderer, IEventManager& eventManager)
	{
		ASSERT(m_impl->m_window == nullptr, "The window is already instantiated.");

		if (glfwInit() == GLFW_FALSE) {
			std::cerr << "GLFW_INIT FAILED\n";
			glfwTerminate();
		};

		renderer.setWindowHint();
		
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		m_impl->m_window = glfwCreateWindow(
			(int)props.width,
			(int)props.height,
			props.name.c_str(),
			nullptr,
			nullptr
		);

		if (!m_impl->m_window)
		{
			std::cerr << "WINDOW CREATION FAILED\n";
			glfwTerminate();
		}

		renderer.setContext(m_impl->m_window);

		m_impl->setCallbacks(eventManager);		

		return ERROR_CODE::NONE;
	}

	Window::ERROR_CODE Window::update(Renderer& renderer)
	{
		renderer.swapBuffers(m_impl->m_window);
		glfwPollEvents();
		return ERROR_CODE::NONE;
	}

	uint32_t Window::getWidth() const
	{
		return m_impl->m_props.width;
	}

	void Window::setWidth(uint32_t width)
	{
		m_impl->m_props.width = width;
	}

	uint32_t Window::getHeight() const
	{
		return m_impl->m_props.height;
	}

	void Window::setHeight(uint32_t height)
	{
		m_impl->m_props.height = height;
	}

	GLFWwindow* Window::getContext()
	{
		return m_impl->m_window;
	}

	void Window::setVSync(bool enable)
	{
		glfwSwapInterval(enable);
		m_impl->m_vSync = enable;
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(m_impl->m_window);
	}

	void Window::setCursorVisible(bool visible)
	{
		if (visible == false)
		{
			glfwSetInputMode(m_impl->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else 
		{
			glfwSetInputMode(m_impl->m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}
