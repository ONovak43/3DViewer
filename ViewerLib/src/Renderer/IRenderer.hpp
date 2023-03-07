#pragma once
namespace VL
{
	class IRenderer
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;
		IRenderer(const IRenderer&) = delete;
		IRenderer(IRenderer&) = delete;
		IRenderer(IRenderer&&) noexcept = delete;
		IRenderer& operator=(const IRenderer&) = delete;
		IRenderer& operator=(IRenderer&&) noexcept = delete;
		virtual void setWindowHint() {};
		virtual bool setContext(GLFWwindow* window) { return true; };
		
	};
}

