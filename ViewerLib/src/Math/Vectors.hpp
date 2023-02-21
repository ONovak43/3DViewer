#pragma once

#include "Vector.hpp"

namespace VL
{
	// Integer vectors 
	using vec2i = VL::Vector<int32_t, 2>;
	using vec3i = VL::Vector<int32_t, 3>;
	using vec4i = VL::Vector<int32_t, 4>;

	// Float vectors
	using vec2 = VL::Vector<float, 2>;
	using vec3 = VL::Vector<float, 3>;
	using vec4 = VL::Vector<float, 4>;

	// Double vectors
	using vec2d = VL::Vector<float, 2>;
	using vec3d = VL::Vector<float, 3>;
	using vec4d = VL::Vector<float, 4>;
}