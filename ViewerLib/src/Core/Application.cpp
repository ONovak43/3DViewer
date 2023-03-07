#include "pch.hpp"
#include "Application.hpp"

namespace VL
{
	class Application::Impl
	{
	public:
		Impl();
		~Impl() = default;
		void registerEvents();
	public:
		bool running;
		Window window;
		Renderer renderer;
		EventManager eventManager;
	};

	Application::Impl::Impl()
		: running(false),
		renderer(),
		window()
	{
	}

	void Application::Impl::registerEvents()
	{
		eventManager.subscribe(EventManager::EVENT_TYPE::WINDOW_CLOSE, [](std::shared_ptr<IEvent> e) {
			Application& a = Application::getInstance();
			a.close(std::dynamic_pointer_cast<WindowCloseEvent>(e));
		});
	}

	void Application::close(std::shared_ptr<WindowCloseEvent> e)
	{
		_impl->running = false;
	}

	Application::Application()
		: _impl(std::make_unique<Application::Impl>())
	{
		_impl->registerEvents();
		RendererAPI::registerRenderer("openGL", OpenGLRenderer::create);

		_impl->renderer.setRenderer("openGL");

		auto winProps = WindowProperties("Viewer", 800, 600);
		_impl->window.create(winProps, _impl->renderer, _impl->eventManager);
	}

	Application::~Application()
	{
	}

	int32_t Application::run()
	{
		_impl->running = true;
		while (_impl->running)
		{
			_impl->window.update(_impl->renderer);
		}
		return 0;
	}
}