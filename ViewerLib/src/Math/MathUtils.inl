#include "MathUtils.hpp"
#pragma once

namespace VL
{
	template<typename T>
	constexpr T radians(T degrees)
	{
		return degrees * static_cast<T>(0.01745329251994329576923690768489);
	}
}