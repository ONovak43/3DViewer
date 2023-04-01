#pragma once

#include "Matrix.hpp"
#include "MatrixTransform.hpp"

namespace VL
{
	// Integer matrices 
	using mat2i = VL::Matrix<int32_t, 2>;
	using mat3i = VL::Matrix<int32_t, 3>;
	using mat4i = VL::Matrix<int32_t, 4>;

	// Float matrices
	using mat2 = VL::Matrix<float, 2>;
	using mat3 = VL::Matrix<float, 3>;
	using mat4 = VL::Matrix<float, 4>;

	// Double matrices
	using mat2d = VL::Matrix<double, 2>;
	using mat3d = VL::Matrix<double, 3>;
	using mat4d = VL::Matrix<double, 4>;
}