#pragma once

#include "Vector.hpp"

namespace VML
{
	// Integer vectors 
	using vec2i = VML::Vector<int32_t, 2>;
	using vec3i = VML::Vector<int32_t, 3>;
	using vec4i = VML::Vector<int32_t, 4>;

	// Float vectors
	using vec2 = VML::Vector<float, 2>;
	using vec3 = VML::Vector<float, 3>;
	using vec4 = VML::Vector<float, 4>;

	// Double vectors
	using vec2d = VML::Vector<float, 2>;
	using vec3d = VML::Vector<float, 3>;
	using vec4d = VML::Vector<float, 4>;
}