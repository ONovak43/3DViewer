#pragma once
#include <cstddef>
#include <math.h>
#include "Matrix.hpp"
#include "VectorTransform.hpp"

namespace VL
{
	// Matrix functions
	template<typename T>
	float determinant(const VL::Matrix<T, 2>& matrix);

	template<typename T>
	float determinant(const VL::Matrix<T, 3>& matrix);

	template<typename T>
	float determinant(const VL::Matrix<T, 4>& matrix);

	template<typename T, std::size_t S>
	VL::Matrix<T, S> transpose(const VL::Matrix<T, S>& matrix);

	template<typename T>
	VL::Matrix<T, 2> inverse(const VL::Matrix<T, 2>& matrix);

	template<typename T>
	VL::Matrix<T, 3> inverse(const VL::Matrix<T, 3>& matrix);

	template<typename T>
	VL::Matrix<T, 4> inverse(const VL::Matrix<T, 4>& matrix);

	// View matrices
	template<typename T>
	VL::Matrix<T, 4> lookAt(Vector<T, 3> position, Vector<T, 3> target, Vector<T, 3> upVector);

	// Clip space
	template<typename T>
	VL::Matrix<T, 4> ortho(T left, T right, T bottom, T top, T near, T far);

	template<typename T>
	VL::Matrix<T, 4> perspective(T fov, T aspect, T near, T far);
}

#include "MatrixTransform.inl"

