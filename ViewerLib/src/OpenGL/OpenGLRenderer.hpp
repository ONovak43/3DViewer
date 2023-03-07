#pragma once
#include "Renderer/IRenderer.hpp"

namespace VL
{
	class OpenGLRenderer : public IRenderer
	{
	public:
		OpenGLRenderer() = default;
		~OpenGLRenderer() override = default;
		static std::unique_ptr<IRenderer> create();
		void setWindowHint() override;
		bool setContext(GLFWwindow* window) override;
	};
}