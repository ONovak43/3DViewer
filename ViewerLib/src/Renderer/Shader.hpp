#pragma once
#include <cstdint>

namespace VL
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual uint32_t getId() const = 0;
	};
}