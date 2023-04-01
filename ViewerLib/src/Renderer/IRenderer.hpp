#pragma once
#include "Math/Vectors.hpp"

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
		virtual void init() = 0;
		virtual void setWindowHint() = 0;
		virtual bool setContext(GLFWwindow* window) = 0;
		virtual void onResize(uint32_t width, uint32_t height) = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void setClearColor(vec4 color) = 0;
		virtual void clear() = 0;
	};
}

