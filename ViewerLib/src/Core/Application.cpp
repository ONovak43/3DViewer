#include "pch.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "Renderer/RendererAPI.hpp"
#include "Renderer/OpenGL/OpenGLRenderer.hpp"
#include "Memory/StackAllocator.hpp"
#include "Event/EventManager.hpp"
#include "GUI.hpp"

namespace VL
{
	class Application::Impl
	{
	public:
		bool m_running;
		bool m_minimized;
		std::shared_ptr<Client> m_client;
		Window m_window;
		Renderer m_renderer;
		EventManager m_eventManager;
		GUI m_gui;
		
	public:
		Impl();
		~Impl() = default;
		void registerEvents();
		float getDeltaTime();
		inline void setLastFrameTime() 
		{ 
			m_lastFrameTime = Clock::now();
		}

	private:
		TimePoint m_lastFrameTime = Clock::now();

	};

	Application::Impl::Impl()
		: m_running(false),
		m_renderer(),
		m_window(),
		m_client(nullptr),
		m_minimized(false),
		m_gui()
	{
	}

	void Application::Impl::registerEvents()
	{
		m_eventManager.subscribe(EventManager::EVENT_TYPE::WINDOW_CLOSE, [](std::shared_ptr<Event> e) {
			Application& app = Application::getInstance();
			app.onClose(std::dynamic_pointer_cast<WindowCloseEvent>(e));
		});

		m_eventManager.subscribe(EventManager::EVENT_TYPE::WINDOW_RESIZE, [](std::shared_ptr<Event> e) {
			Application& app = Application::getInstance();
			app.onResize(std::dynamic_pointer_cast<WindowResizeEvent>(e));
		});

		m_eventManager.subscribe(EventManager::EVENT_TYPE::KEY_PRESSED, [](std::shared_ptr<Event> e) {
			Application& app = Application::getInstance();
			app.onKeyPress(std::dynamic_pointer_cast<KeyPressEvent>(e));
		});
	}

	float Application::Impl::getDeltaTime()
	{
		auto now = Clock::now();
		auto deltaTime = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - m_lastFrameTime).count()) / 1000000000.0f;
		m_lastFrameTime = std::move(now);
		return deltaTime;
	}

	void Application::onClose(std::shared_ptr<WindowCloseEvent> e)
	{
		m_impl->m_client->stop();
		m_impl->m_running = false;
	}

	void Application::onResize(std::shared_ptr<WindowResizeEvent> e)
	{
		if (e->getWidth() == 0 && e->getHeight() == 0)
		{
			m_impl->m_minimized = true;
			return;
		}

		m_impl->m_minimized = false;
		m_impl->m_renderer.onResize(e->getWidth(), e->getHeight());
	}

	void Application::onKeyPress(std::shared_ptr<KeyPressEvent> e)
	{
		auto key = e->getKeyCode();
		if (key == KeyboardEvent::KEY_CODES::ESCAPE) {
			m_impl->m_running = false;
		}
	}

	void Application::setClient(std::shared_ptr<Client> client)
	{
		m_impl->m_client = client;
		m_impl->m_client->setRenderer(&(m_impl->m_renderer));
	}

	Renderer* Application::getRenderer()
	{
		return &m_impl->m_renderer;
	}

	int32_t Application::run()
	{
		ASSERT(m_impl->m_client != nullptr, "You must set the client before running the application.");
		m_impl->m_running = true;
		m_impl->setLastFrameTime();
		m_impl->m_client->start();
		auto stackAllocator = StackAllocator<STACK_ALLOCATOR_SIZE>();

		do
		{
			if (m_impl->m_minimized)
			{
				continue;
			}
			
			auto time = m_impl->getDeltaTime();

			m_impl->m_renderer.setClearColor(vec4(std::array{ 0.2f, 0.3f, 0.3f, 1.0f }));
			m_impl->m_renderer.clear();

			m_impl->m_client->update(stackAllocator, time);

			m_impl->m_gui.beginFrame();
			m_impl->m_client->renderGUI();
			m_impl->m_gui.endFrame();

			// Clean up
			m_impl->m_window.update(m_impl->m_renderer);			
			stackAllocator.clear();

		} while (m_impl->m_running);
		return 0;
	}

	Application::Application()
		: m_impl(std::make_unique<Application::Impl>())
	{
		m_impl->registerEvents();
		RendererAPI::registerRenderer("openGL", OpenGL::OpenGLRenderer::create);

		m_impl->m_renderer.setRenderer("openGL");

		auto winProps = WindowProperties("Viewer", 800, 600);
		m_impl->m_window.create(winProps, m_impl->m_renderer, m_impl->m_eventManager);

		m_impl->m_window.setVSync(false);
		m_impl->m_renderer.init();

		m_impl->m_gui.create(m_impl->m_window);
	}

	Application::~Application()
	{
	}
}