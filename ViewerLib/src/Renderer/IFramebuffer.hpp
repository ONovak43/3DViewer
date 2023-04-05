#pragma once
#include <cstdint>
#include "Math/Vectors.hpp"

namespace VL
{
	class IFramebuffer
	{
	public:
		virtual ~IFramebuffer() = default;

		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void clearColor(const vec4& color, float depth, uint32_t stencil, bool clearColor) = 0;
		virtual void clearDepth(float depth) = 0;
		virtual void clearStencil(int32_t stencil) = 0;
	};
}
