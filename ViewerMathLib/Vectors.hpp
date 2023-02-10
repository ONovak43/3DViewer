#pragma once

#include "Vector.hpp"

namespace VML
{
	// Integer matrices 
	using vec2i = VML::Vector<int, 2>;
	using vec3i = VML::Vector<int, 3>;
	using vec4i = VML::Vector<int, 4>;

	// Float matrices
	using vec2 = VML::Vector<float, 2>;
	using vec3 = VML::Vector<float, 3>;
	using vec4 = VML::Vector<float, 4>;

	// Double matrices
	using vec2d = VML::Vector<float, 2>;
	using vec3d = VML::Vector<float, 3>;
	using vec4d = VML::Vector<float, 4>;
}