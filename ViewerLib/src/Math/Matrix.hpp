#pragma once

#include <array>
#include <type_traits>
#include <iostream>

namespace VL
{
	/**
	 * @class Matrix
	 * @brief Represents a square matrix.
	 *
	 * This class is used to represent a square matrix.
	 *
	 * @tparam T Type of the matrix elements (float, double or int32_t)
	 * @tparam S Size of the square matrix (float, double or int32_t)
	 */
	template <class T, std::size_t S>
	class Matrix
	{
		using MatrixData1D = std::array<T, S * S>;
		using MatrixData2D = std::array<std::array<T, S>, S>;
	public:
		/**
		 * @brief Default constructor
		 * Initializes the matrix with default values (all elements set to 0)
		 */
		constexpr Matrix();

		/**
		 * @brief Constructor
		 * Initializes the matrix with a given value on the diagonal
		 * @param value Value of type T to set on the diagonal
		 */
		constexpr explicit Matrix(T value);

		/**
		* @brief Constructor
		* Initializes the matrix with a given array (1D) of values
		* @param values Array of S values of type T to initialize the matrix with
		*/
		template<typename ArrayData>
			requires 
				std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<T, S * S>>
		constexpr explicit Matrix(ArrayData&& values);

		/**
		* @brief Constructor
		* Initializes the matrix with a given array (2D) of values
		* @param values Array of 16 values of type T to initialize the matrix with
		*/
		template<typename ArrayData>
			requires 
				std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<std::array<T, S>, S>>
		constexpr explicit Matrix(ArrayData&& values);


		/**
		 * @brief Accesses an element of the matrix
		 * @param row Row index (0-based)
		 * @param column Column index (0-based)
		 * @return Reference to the element at the specified position
		 */
		constexpr T& operator()(std::size_t row, std::size_t column);

		/**
		 * @brief Accesses an element of the matrix
		 * @param row Row index (0-based)
		 * @param column Column index (0-based)
		 * @return Reference to the element at the specified position
		 */
		constexpr const T& operator()(std::size_t row, std::size_t column) const;

		/**
		 * @brief Accesses an element of the matrix
		 * @param i Element index (0-based)
		 * @return Reference to the element at the specified position
		 */
		constexpr T& operator[](std::size_t i);

		/**
		 * @brief Accesses an element of the matrix
		 * @param i Element index (0-based)
		 * @return Reference to the element at the specified position
		 */
		constexpr const T& operator[](std::size_t i) const;

		/**
		 * @brief Conversion to an array of values
		 * @return Array of S*S values of type T representing the matrix
		 */
		 MatrixData2D toArray() const;

	private:
		/**
		* The matrix data.
		*/
		union
		{
			MatrixData1D _mData1D;
			MatrixData2D _mData2D;
		};
	};

	// Free functions

	/**
	* @brief Overloaded operator for matrix addition
	* @param lhs The left matrix
	* @param rhs The right matrix
	* @return New matrix representing the result of the addition
	*/
	template <typename T, std::size_t S>
	constexpr Matrix<T, S> operator+(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs);

	/**
	* @brief Overloaded operator for matrix subtraction
	* @param lhs The left matrix
	* @param rhs The right matrix
	* @return New matrix representing the result of the subtraction
	*/
	template <typename T, std::size_t S>
	constexpr Matrix<T, S> operator-(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs);

	/**
	* @brief Overloaded operator for matrix multiplication
	* @param lhs The left matrix
	* @param rhs The right matrix
	* @return New matrix representing the result of the multiplication
	*/
	template <typename T, std::size_t S>
	constexpr Matrix<T, S> operator*(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs);

	/**
	* @brief Overloaded operator for matrix-scalar multiplication
	* @param lhs The matrix
	* @param scale The scalar to multiply by
	* @return New matrix representing the result of the multiplication
	*/
	template <typename T, std::size_t S>
	constexpr Matrix<T, S> operator*(const VL::Matrix<T, S>& matrix, float scale);

	/** 
	* @brief Overloaded operator for matrix multiplication
	* @param lhs The left matrix
	* @param rhs The right matrix
	* @return New matrix representing the result of the multiplication
	*/
	template <typename T, std::size_t S>
	constexpr Matrix<T, S>& operator*=(Matrix<T, S>& lhs, const Matrix<T, S>& rhs);

	/**
	* @brief Overloaded operator for matrix-scalar multiplication
	* @param lhs The matrix
	* @param scale The scalar to multiply by
	* @return New matrix representing the result of the multiplication
	*/
	template <typename T, std::size_t S>
	constexpr Matrix<T, S>& operator*=(VL::Matrix<T, S>& matrix, float scale);

	/**
	 * @brief Overloaded operator for matrix comparison
	 * @param lhs The left matrix
	 * @param rhs The right matrix
	 * @return True if all elements of the matrices are equal, false otherwise
	 */
	template <typename T, std::size_t S>
	constexpr bool operator==(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs);

	/**
	 * @brief Overloaded operator for matrix comparison
	 * @param lhs The left matrix
	 * @param rhs The right matrix
	 * @return False if all elements of the matrices are equal, true otherwise
	 */
	template <typename T, std::size_t S>
	constexpr bool operator!=(const Matrix<T, S>& lhs, const Matrix<T, S>& rhs);

	// Explicit templates
	template class Matrix<int32_t, 2>;
	template class Matrix<int32_t, 3>;
	template class Matrix<int32_t, 4>;
	template class Matrix<float, 2>;
	template class Matrix<float, 3>;
	template class Matrix<float, 4>;
	template class Matrix<double, 2>;
	template class Matrix<double, 3>;
	template class Matrix<double, 4>;
}

#include "Matrix.inl" // Inclusion model