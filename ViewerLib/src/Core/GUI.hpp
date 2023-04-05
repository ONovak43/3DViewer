#pragma once
#include "Window.hpp"

namespace VL
{
	class GUI
	{
	public:
		enum class ERROR_CODE
		{
			NONE,
			GLFW_INIT_FAILED
		};

		GUI() = default;
		~GUI();
		GUI(const GUI&) = delete;
		GUI(GUI&) = delete;
		GUI(GUI&&) noexcept = delete;
		GUI& operator=(GUI&) = delete;
		GUI& operator=(GUI&&) noexcept = delete;
		
		void create(Window& window);
		void beginFrame();
		void endFrame();
	};
}

