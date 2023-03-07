#pragma once
#include "Window.hpp"
#include "Renderer/RendererAPI.hpp"
#include "OpenGL/OpenGLRenderer.hpp"
#include "Event/IEvent.hpp"
#include "Event/Events.hpp"

namespace VL 
{
	class Application
	{
	public:
		Application(const Application&) = delete;
		Application(Application&) = delete;
		Application(Application&&) noexcept = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) noexcept = delete;

		int32_t run();
		void close(std::shared_ptr<WindowCloseEvent> e);

		static Application& getInstance() {
			static Application instance;
			return instance;
		}
	private:
		Application();
		~Application();
		class Impl;
		std::unique_ptr<Impl> _impl;
	};
}

