#pragma once
#include "Event/Event.hpp"
#include "Client/Client.hpp"
#include "Renderer/Renderer.hpp"

#include <chrono>

namespace VL 
{
	class Window;
	

	class Application
	{
	public:
		Application(const Application&) = delete;
		Application(Application&) = delete;
		Application(Application&&) noexcept = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) noexcept = delete;

		static Application& getInstance() {
			static Application instance;
			return instance;
		};

		int32_t run();
		void stop();
		
		// Events
		void onClose(const std::shared_ptr<WindowCloseEvent>& e);
		void onResize(const std::shared_ptr<WindowResizeEvent>& e);
		void onKeyPress(const std::shared_ptr<KeyPressEvent>& e);
		void onKeyRelease(const std::shared_ptr<KeyReleaseEvent>& e);
		void onMouseMove(const std::shared_ptr<MouseMovedEvent>& e);

		void setClient(const std::shared_ptr<Client>& client);
		Renderer* getRenderer();

	private:
		using Clock = std::chrono::steady_clock;
		using TimePoint = std::chrono::time_point<Clock, std::chrono::nanoseconds>;
		Application();
		~Application();
		class Impl;
		std::unique_ptr<Impl> m_impl;
	};
}

