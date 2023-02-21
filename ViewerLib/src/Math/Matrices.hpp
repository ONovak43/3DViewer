#pragma once

#include "Matrix.hpp"
#include "MatrixTransform.hpp"

namespace VL
{
	// Integer matrices 
	using mat2x2i = VL::Matrix<int32_t, 2>;
	using mat3x3i = VL::Matrix<int32_t, 3>;
	using mat4x4i = VL::Matrix<int32_t, 4>;

	// Float matrices
	using mat2x2 = VL::Matrix<float, 2>;
	using mat3x3 = VL::Matrix<float, 3>;
	using mat4x4 = VL::Matrix<float, 4>;

	// Double matrices
	using mat2x2d = VL::Matrix<float, 2>;
	using mat3x3d = VL::Matrix<float, 3>;
	using mat4x4d = VL::Matrix<float, 4>;
}