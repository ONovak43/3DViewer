#pragma once

#include "Matrix.hpp"
#include "MatrixTransform.hpp"

namespace VML
{
	// Integer matrices 
	using mat2x2i = VML::Matrix<int, 2>;
	using mat3x3i = VML::Matrix<int, 3>;
	using mat4x4i = VML::Matrix<int, 4>;

	// Float matrices
	using mat2x2 = VML::Matrix<float, 2>;
	using mat3x3 = VML::Matrix<float, 3>;
	using mat4x4 = VML::Matrix<float, 4>;

	// Double matrices
	using mat2x2d = VML::Matrix<float, 2>;
	using mat3x3d = VML::Matrix<float, 3>;
	using mat4x4d = VML::Matrix<float, 4>;
}