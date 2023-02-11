#include "MatrixTransform.hpp"
#pragma once

template<typename T>
inline float VML::determinant(const VML::Matrix<T, 2>& matrix)
{
	return static_cast<float>(matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0));
}

template<typename T>
float VML::determinant(const VML::Matrix<T, 3>& matrix)
{
	// Cramer's Rule is used for calculating the determinant 

	// Cofactors (det 2x2 matrix)
	auto c11 = matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1);
	auto c12 = matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0);
	auto c13 = matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0);

	return static_cast<float>(matrix(0, 0) * c11 - matrix(0, 1) * c12 + matrix(0, 2) * c13);
}

template<typename T>
float VML::determinant(const VML::Matrix<T, 4>& matrix)
{
	// Cramer's Rule is used for calculating the determinant 

	// Cofactors (det 2x2 matrix)
	auto s11 = matrix(2, 2) * matrix(3, 3) - matrix(2, 3) * matrix(3, 2);
	auto s12 = matrix(2, 1) * matrix(3, 3) - matrix(2, 3) * matrix(3, 1);
	auto s13 = matrix(2, 1) * matrix(3, 2) - matrix(2, 2) * matrix(3, 1);
	auto s14 = matrix(2, 0) * matrix(3, 3) - matrix(2, 3) * matrix(3, 0);
	auto s15 = matrix(2, 0) * matrix(3, 2) - matrix(2, 2) * matrix(3, 0);
	auto s16 = matrix(2, 0) * matrix(3, 1) - matrix(3, 0) * matrix(2, 1);

	// Cofactors (det 3x3 matrix)
	auto c21 = matrix(1, 1) * s11 - matrix(1, 2) * s12 + matrix(1, 3) * s13;
	auto c22 = matrix(1, 0) * s11 - matrix(1, 2) * s14 + matrix(1, 3) * s15;
	auto c23 = matrix(1, 0) * s12 - matrix(1, 1) * s14 + matrix(1, 3) * s16;
	auto c24 = matrix(1, 0) * s13 - matrix(1, 1) * s15 + matrix(1, 2) * s16;

	return static_cast<float>(matrix(0, 0) * c21 - matrix(0, 1) * c22 + matrix(0, 2) * c23 - matrix(0, 3) * c24);
}

template<typename T, std::size_t S>
VML::Matrix<T, S> VML::transpose(const VML::Matrix<T, S>& matrix)
{
	VML::Matrix<T, S> result;
	for (auto i = 0; i < S; ++i) {
		for (auto j = 0; j < S; ++j) {
			result(i, j) = matrix(j, i);
		}
	}
	return result;
}

template<typename T>
VML::Matrix<T, 2> VML::inverse(const VML::Matrix<T, 2>& matrix)
{
	auto det = VML::determinant(matrix);

	if (det == 0) {
		throw std::runtime_error("Matrix is singular and cannot be inverted.");
	}

	// Transposed Cofactor's Matrix
	VML::Matrix<T, 2> result;

	// Transposing and calculating det 2x2 divided by the determinant
	result(0, 0) = matrix(1, 1);
	result(1, 0) = -matrix(1, 0);
	result(0, 1) = -matrix(0, 1);
	result(1, 1) = matrix(0, 0);

	result *= 1.f / det;

	return result;
}

template<typename T>
VML::Matrix<T, 3> VML::inverse(const VML::Matrix<T, 3>& matrix)
{
	auto det = VML::determinant(matrix);

	if (det == 0) {
		throw std::runtime_error("Matrix is singular and cannot be inverted.");
	}

	// Transposed Cofactor's Matrix
	VML::Matrix<T, 3> result;

	// Transposing and calculating det 2x2 divided by the determinant
	result(0, 0) = +(matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1));
	result(1, 0) = -(matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0));
	result(2, 0) = +(matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0));

	result(0, 1) = -(matrix(0, 1) * matrix(2, 2) - matrix(0, 2) * matrix(2, 1));
	result(1, 1) = +(matrix(0, 0) * matrix(2, 2) - matrix(0, 2) * matrix(2, 0));
	result(2, 1) = -(matrix(0, 0) * matrix(2, 1) - matrix(0, 1) * matrix(2, 0));

	result(0, 2) = +(matrix(0, 1) * matrix(1, 2) - matrix(0, 2) * matrix(1, 1));
	result(1, 2) = -(matrix(0, 0) * matrix(1, 2) - matrix(0, 2) * matrix(1, 0));
	result(2, 2) = +(matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0));

	result *= 1.f / det;

	return result;
}

template<typename T>
VML::Matrix<T, 4> VML::inverse(const VML::Matrix<T, 4>& matrix)
{
	auto det = VML::determinant(matrix);

	if (det == 0) {
		throw std::runtime_error("Matrix is singular and cannot be inverted.");
	}

	// Cofactors (det 2x2 matrix)
	auto s01 = matrix(2, 2) * matrix(3, 3) - matrix(2, 3) * matrix(3, 2);
	auto s02 = matrix(2, 1) * matrix(3, 3) - matrix(2, 3) * matrix(3, 1);
	auto s03 = matrix(2, 1) * matrix(3, 2) - matrix(2, 2) * matrix(3, 1);
	auto s04 = matrix(2, 0) * matrix(3, 3) - matrix(2, 3) * matrix(3, 0);
	auto s05 = matrix(2, 0) * matrix(3, 2) - matrix(2, 2) * matrix(3, 0);
	auto s06 = matrix(2, 0) * matrix(3, 1) - matrix(3, 0) * matrix(2, 1);
	auto s07 = matrix(1, 2) * matrix(3, 3) - matrix(1, 3) * matrix(3, 2);
	auto s08 = matrix(1, 1) * matrix(3, 3) - matrix(1, 3) * matrix(3, 1);
	auto s09 = matrix(1, 1) * matrix(3, 2) - matrix(1, 2) * matrix(3, 1);
	auto s10 = matrix(1, 0) * matrix(3, 3) - matrix(1, 3) * matrix(3, 0);
	auto s11 = matrix(1, 0) * matrix(3, 2) - matrix(1, 2) * matrix(3, 0);
	auto s12 = matrix(1, 0) * matrix(3, 1) - matrix(1, 1) * matrix(3, 0);
	auto s13 = matrix(1, 2) * matrix(2, 3) - matrix(1, 3) * matrix(2, 2);
	auto s14 = matrix(1, 1) * matrix(2, 3) - matrix(1, 3) * matrix(2, 1);
	auto s15 = matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1);
	auto s16 = matrix(1, 0) * matrix(2, 3) - matrix(1, 3) * matrix(2, 0);
	auto s17 = matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0);
	auto s18 = matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0);

	// Transposed Cofactor's Matrix
	VML::Matrix<T, 4> result;

	result(0, 0) = +(matrix(1, 1) * s01 - matrix(1, 2) * s02 + matrix(1, 3) * s03);
	result(1, 0) = -(matrix(1, 0) * s01 - matrix(1, 2) * s04 + matrix(1, 3) * s05);
	result(2, 0) = +(matrix(1, 0) * s02 - matrix(1, 1) * s04 + matrix(1, 3) * s06);
	result(3, 0) = -(matrix(1, 0) * s03 - matrix(1, 1) * s05 + matrix(1, 2) * s06);

	result(0, 1) = -(matrix(0, 1) * s01 - matrix(0, 2) * s02 + matrix(0, 3) * s03);
	result(1, 1) = +(matrix(0, 0) * s01 - matrix(0, 2) * s04 + matrix(0, 3) * s05);
	result(2, 1) = -(matrix(0, 0) * s02 - matrix(0, 1) * s04 + matrix(0, 3) * s06);
	result(3, 1) = +(matrix(0, 0) * s03 - matrix(0, 1) * s05 + matrix(0, 2) * s06);

	result(0, 2) = +(matrix(0, 1) * s07 - matrix(0, 2) * s08 + matrix(0, 3) * s09);
	result(1, 2) = -(matrix(0, 0) * s07 - matrix(0, 2) * s10 + matrix(0, 3) * s11);
	result(2, 2) = +(matrix(0, 0) * s08 - matrix(0, 1) * s10 + matrix(0, 3) * s12);
	result(3, 2) = -(matrix(0, 0) * s09 - matrix(0, 1) * s11 + matrix(0, 2) * s12);

	result(0, 3) = -(matrix(0, 1) * s13 - matrix(0, 2) * s14 + matrix(0, 3) * s15);
	result(1, 3) = +(matrix(0, 0) * s13 - matrix(0, 2) * s16 + matrix(0, 3) * s17);
	result(2, 3) = -(matrix(0, 0) * s14 - matrix(0, 1) * s16 + matrix(0, 3) * s18);
	result(3, 3) = +(matrix(0, 0) * s15 - matrix(0, 1) * s17 + matrix(0, 2) * s18);

	result *= 1.f / det;

	return result;
}

template<typename T>
VML::Matrix<T, 4> VML::lookAt(T position, T target, T upVector)
{
	return VML::Matrix<T, 4>();
}

template<typename T>
VML::Matrix<T, 4> VML::ortho(T left, T right, T bottom, T top, T zNear, T zFar)
{
	// (Scale matrix) * (Translation matrix)
	Matrix<T, 4> result;
	
	// Set diagonal
	result(0, 0) = static_cast<T>(2) / (right - left);
	result(1, 1) = static_cast<T>(2) / (bottom - top);
	result(2, 2) = static_cast<T>(-2) / (zFar - zNear);
	result(3, 3) = static_cast<T>(2);

	// Set 4th column
	result(0, 3) = (left - right) / (right - left);
	result(1, 3) = (top - bottom) / (bottom - top);
	result(2, 3) = (zNear - zFar) / (zFar - zNear);

	return result;
};


template<typename T>
VML::Matrix<T, 4> VML::perspective(T fov, T aspect, T zNear, T zFar)
{
	// Perspective projection
	// (Orthographic matrix) * (Perspective matrix)
	Matrix<T, 4> result;

	auto f = static_cast<T>(1) / tan(fov / static_cast<T>(2));

	// Set diagonal
	result(0, 0) = f / aspect;
	result(1, 1) = f;
	result(2, 2) = - (zFar + zNear) / (zNear - zFar);

	// Set other columns
	result(3, 2) = static_cast<T>(1);
	result(2, 3) = (static_cast<T>(2) * zNear * zFar) / (zNear - zFar);
	
	return result;
}