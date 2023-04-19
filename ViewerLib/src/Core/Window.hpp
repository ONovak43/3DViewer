#pragma once
#include "pch.hpp"

namespace VL
{
	class Renderer;
	class IEventManager;
	struct WindowProperties
	{
		uint32_t width;
		uint32_t height;
		std::string name;

		WindowProperties(std::string windowName = "Viewer",
			uint32_t windowWidth = 1920,
			uint32_t windowHeight = 1080)
			: name(windowName), width(windowWidth), height(windowHeight) 
		{
		}
	};

	class Window
	{
	public:
		enum class ERROR_CODE
		{
			NONE,
			GLFW_INIT_FAILED
		};

		Window();
		~Window();
		Window(const Window&) = delete;
		Window(Window&) = delete;
		Window(Window&&) noexcept = delete;
		Window& operator=(Window&) = delete;
		Window& operator=(Window&&) noexcept = delete;

		ERROR_CODE create(const WindowProperties& props, Renderer& renderer, IEventManager& eventManager);
		ERROR_CODE update(Renderer& renderer);

		[[nodiscard]] uint32_t getWidth() const;
		void setWidth(uint32_t width);

		[[nodiscard]] uint32_t getHeight() const;
		void setHeight(uint32_t height);

		[[nodiscard]] GLFWwindow* getContext();

		void setVSync(bool enable = true);
		bool shouldClose() const;

	private:
		class Impl;
		std::unique_ptr<Impl> m_impl;
	};
}

