#pragma once
#include <cstdint>

namespace VL
{
	class IShader
	{
	public:
		virtual ~IShader() = default;
		virtual uint32_t getId() const = 0;
	};
}