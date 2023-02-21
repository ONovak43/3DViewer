#pragma once

namespace VL {
	template<typename T, std::size_t S>
	constexpr Matrix<T, S>::Matrix()
		: _mData1D{}
	{

	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S>::Matrix(T value)
		: _mData1D{}
	{
		for (auto i = 0; i < S; ++i) {
			_mData2D[i][i] = value;
		}
	}

	template<typename T, std::size_t S>
	template<typename ArrayData>
		requires
	std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<T, S* S>>
	constexpr Matrix<T, S>::Matrix(ArrayData&& values)
		: _mData1D(std::forward<ArrayData>(values))
	{
	};

	template<typename T, std::size_t S>
	template<typename ArrayData>
		requires
	std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<std::array<T, S>, S>>
	constexpr Matrix<T, S>::Matrix(ArrayData&& values)
		: _mData2D(std::forward<ArrayData>(values))
	{
	};

	template<typename T, std::size_t S>
	constexpr T& Matrix<T, S>::operator()(std::size_t row, std::size_t column)
	{
		return _mData2D[row][column];
	}

	template<typename T, std::size_t S>
	constexpr const T& Matrix<T, S>::operator()(std::size_t row, std::size_t column) const
	{
		return _mData2D[row][column];
	}

	template<typename T, std::size_t S>
	constexpr T& Matrix<T, S>::operator[](std::size_t i)
	{

		return _mData1D[i];
	}

	template<typename T, std::size_t S>
	constexpr const T& Matrix<T, S>::operator[](std::size_t i) const
	{
		return _mData1D[i];
	}

	template<class T, std::size_t S>
	std::array<std::array<T, S>, S> Matrix<T, S>::toArray() const
	{
		return _mData2D;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator+(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		Matrix<T, S> result;

		for (auto i = 0; i < S * S; ++i) {
			result[i] = lhs[i] + rhs[i];
		}
		return result;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator-(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		Matrix<T, S> result;

		for (auto i = 0; i < S * S; ++i) {
			result[i] = lhs[i] - rhs[i];
		}
		return result;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator*(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		Matrix<T, S> result;
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
	constexpr Matrix<T, S> operator*(const Matrix<T, S>& matrix, float scale)
	{
		Matrix<T, S> result;

		for (auto i = 0; i < S * S; ++i) {
			result[i] = static_cast<T>(matrix[i] * scale);
		}

		return result;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S>& operator*=(Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S>& operator*=(Matrix<T, S>& matrix, float scale)
	{
		matrix = matrix * scale;
		return matrix;
	}

	template<typename T, std::size_t S>
	constexpr bool operator==(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		for (auto i = 0; i < S * S; ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}

	template<typename T, std::size_t S>
	constexpr bool operator!=(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		return !(lhs == rhs);
	}
}