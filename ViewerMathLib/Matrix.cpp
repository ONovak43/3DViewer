#include "Matrix.hpp"

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S>::Matrix()
	: _mData1D{}
{

}

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S>::Matrix(T value)
	: _mData1D{}
{
	for (auto i = 0; i < S; ++i) {
		_mData2D[i][i] = value;
	}
}


template<typename T, std::size_t S>
constexpr T& VML::Matrix<T, S>::operator()(std::size_t row, std::size_t column)
{
	return _mData2D[row][column];
}

template<typename T, std::size_t S>
constexpr const T& VML::Matrix<T, S>::operator()(std::size_t row, std::size_t column) const
{
	return _mData2D[row][column];
}

template<typename T, std::size_t S>
constexpr T& VML::Matrix<T, S>::operator[](std::size_t i)
{

	return _mData1D[i];
}

template<typename T, std::size_t S>
constexpr const T& VML::Matrix<T, S>::operator[](std::size_t i) const
{
	return _mData1D[i];
}

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S> VML::operator+(const VML::Matrix<T, S>& lhs, const VML::Matrix<T, S>& rhs)
{
	VML::Matrix<T, S> result;

	for (auto i = 0; i < S * S; ++i) {
		result[i] = lhs[i] + rhs[i];
	}
	return result;
}

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S> VML::operator-(const VML::Matrix<T, S>& lhs, const VML::Matrix<T, S>& rhs)
{
	VML::Matrix<T, S> result;

	for (auto i = 0; i < S * S; ++i) {
		result[i] = lhs[i] - rhs[i];
	}
	return result;
}

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S> VML::operator*(const VML::Matrix<T, S>& lhs, const VML::Matrix<T, S>& rhs)
{
	VML::Matrix<T, S> result;
	for (auto i = 0; i < S; i++) {
		for (auto j = 0; j < S; j++) {
			result(i, j) = 0;
			for (auto k = 0; k < S; k++) {
				result(i, j) += lhs(i, k) * rhs(k, j);
			}
		}
	}
	return result;
}

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S> VML::operator*(const VML::Matrix<T, S>& matrix, float scale)
{
	VML::Matrix<T, S> result;

	for (auto i = 0; i < S * S; ++i) {
		result[i] = matrix[i] * scale;
	}

	return result;
}

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S>& VML::operator*=(VML::Matrix<T, S>& lhs, const VML::Matrix<T, S>& rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

template<typename T, std::size_t S>
constexpr VML::Matrix<T, S>& VML::operator*=(VML::Matrix<T, S>& matrix, float scale)
{
	matrix = matrix * scale;
	return matrix;
}

template<typename T, std::size_t S>
constexpr bool VML::operator==(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
{
	for (auto i = 0; i < S * S; ++i) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}

template<typename T, std::size_t S>
constexpr bool VML::operator!=(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
{
	return !(lhs == rhs);
}
