#include "Matrix.hpp"
namespace VL
{
	template<typename T, std::size_t S>
	constexpr Matrix<T, S>::Matrix()
		: _mData1D{}
	{

	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S>::Matrix(T value)
		: _mData1D{}
	{
		for (std::size_t i = 0; i < S; ++i) {
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
	inline std::array<std::array<T, S>, S> Matrix<T, S>::toArray() const
	{
		return _mData2D;
	}

	template<class T, std::size_t S>
	inline T* Matrix<T, S>::data()
	{
		return reinterpret_cast<T*>(_mData2D.data());
	}

	template<class T, std::size_t S>
	inline constexpr Matrix<T, S>& operator+=(Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		for (std::size_t i = 0; i < S * S; ++i) {
			lhs[i] += rhs[i];
		}
		return lhs;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator+(Matrix<T, S> lhs, const Matrix<T, S>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template<class T, std::size_t S>
	inline constexpr Matrix<T, S>& operator-=(Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		for (std::size_t i = 0; i < S * S; ++i) {
			lhs[i] -= rhs[i];
		}
		return lhs;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator-(Matrix<T, S> lhs, const Matrix<T, S>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S>& operator*=(Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		Matrix<T, S> result;

		for (std::size_t i = 0; i < S; ++i) {
			for (auto j = 0; j < S; ++j) {
				for (auto k = 0; k < S; ++k) {
					result(i, j) += lhs(i, k) * rhs(k, j);
				}
			}
		}

		lhs = std::move(result);
		return lhs;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S>& operator*=(Matrix<T, S>& matrix, float scale)
	{
		for (std::size_t i = 0; i < S * S; ++i) {
			matrix[i] = static_cast<T>(matrix[i] * scale);
		}
		return matrix;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S>& operator*=(float scale, Matrix<T, S>& matrix)
	{
		matrix *= scale;
		return matrix;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator*(Matrix<T, S> lhs, const Matrix<T, S>& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator*(Matrix<T, S> matrix, float scale)
	{
		matrix *= scale;
		return matrix;
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> operator*(float scale, Matrix<T, S> matrix)
	{
		matrix *= scale;
		return matrix;
	}

	template<typename T, std::size_t S>
	constexpr bool operator==(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs)
	{
		for (std::size_t i = 0; i < S * S; ++i) {
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