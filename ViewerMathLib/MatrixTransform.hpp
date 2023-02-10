#pragma once
#include <cstddef>
#include <math.h>
#include "Matrix.hpp"

namespace VML
{
	// Matrix functions
	template<typename T>
	inline float determinant(const VML::Matrix<T, 2>& matrix);

	template<typename T>
	float determinant(const VML::Matrix<T, 3>& matrix);

	template<typename T>
	float determinant(const VML::Matrix<T, 4>& matrix);

	template<typename T, std::size_t S>
	VML::Matrix<T, S> transpose(const VML::Matrix<T, S>& matrix);

	template<typename T>
	VML::Matrix<T, 2> inverse(const VML::Matrix<T, 2>& matrix);

	template<typename T>
	VML::Matrix<T, 3> inverse(const VML::Matrix<T, 3>& matrix);

	template<typename T>
	VML::Matrix<T, 4> inverse(const VML::Matrix<T, 4>& matrix);

	// View matrices
	template<typename T>
	VML::Matrix<T, 4> lookAt(T fov, T aspect, T near, T far);

	// Clip space
	template<typename T>
	VML::Matrix<T, 4> ortho(T left, T right, T bottom, T top, T near, T far);

	template<typename T>
	VML::Matrix<T, 4> perspective(T fov, T aspect, T near, T far);
}

#include "MatrixTransform.inl"

