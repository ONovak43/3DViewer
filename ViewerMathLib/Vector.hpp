#pragma once

#include <array>
#include <span>
#include <type_traits>
#include <iostream>

namespace VML
{
	/**
	* @class Vector
	* @brief Represents a vector.
	*
	* This class is used to represent a 4D vector in a homogeneous coordinate system.
	*
	* @tparam T Type of the vector elements (float, double or int)
	* @tparam S Size of vector (int)
	*/
	template <class T, std::size_t S>
	class Vector
	{
		using VectorData = std::array<T, S>;
	public:
		/*
		 * @brief Default constructor
		 * Initializes the vector with default values (all elements set to 0)
		 */
		constexpr Vector();

		/**
		 * @brief Constructor
		 * Initializes the vector with a given array of values
		 * @param values Array of 4 values of type T to initialize the vector with
		 */
		template<typename ArrayData>
			requires
				std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<T, S>>
		constexpr explicit Vector(ArrayData&& values);

		/**
		 * @brief Accesses an element of the vector
		 * @param i Element index (0-based)
		 * @return Reference to the element at the specified position
		 */
		constexpr T& operator[](std::size_t i);

		/**
		 * @brief Accesses an element of the vector
		 * @param i Element index (0-based)
		 * @return Reference to the element at the specified position
		 */
		constexpr const T& operator[](std::size_t i) const;

		/**
		 * @brief Conversion to an array of values
		 * @return Array of 4 values of type T representing the vector
		 */
		constexpr VectorData toArray() const noexcept;

	private:
		/**
		* The vector data.
		*/
		VectorData _vData;
	};

	// Free functions

	/**
	 * @brief Addition operator
	 * Adds a given vector to the current vector
	 * @param lhs Vector to add
	 * @param rhs Vector to add
	 * @return The resulting vector
	 */
	template <class T, std::size_t S>
	constexpr Vector<T, S> operator+(const Vector<T, S>& lhs, const Vector<T, S>& rhs);

	/**
	 * @brief Subtraction operator
	 * Subtracts a given vector from the current vector
	 * @param lhs Vector to subtract from
	 * @param rhs Vector to subtract
	 * @return The resulting vector
	 */
	template <class T, std::size_t S>
	constexpr Vector<T, S> operator-(const Vector<T, S>& lhs, const Vector<T, S>& rhs);

	/**
	 * @brief Multiplication operator
	 * Multiplies the current vector by a given scalar
	 * @param lhs Vector to multiply
	 * @param scalar Scalar to multiply by
	 * @return The resulting vector
	 */
	template <class T, std::size_t S>
	constexpr Vector<T, S> operator*(const Vector<T, S>& lhs, float scalar);

	/**
	 * @brief Addition-assignment operator
	 * Adds a given vector to the current vector
	 * @param lhs Vector to add
	 * @param rhs Vector to add
	 * @return Reference to the current vector
	 */
	template <class T, std::size_t S>
	constexpr Vector<T, S>& operator+=(Vector<T, S>& lhs, const Vector<T, S>& rhs);

	/**
	 * @brief Subtraction-assignment operator
	 * Subtracts a given vector from the current vector
	 * @param lhs Vector to subtract from
	 * @param rhs Vector to subtract
	 * @return Reference to the current vector
	 */
	template <class T, std::size_t S>
	constexpr Vector<T, S>& operator-=(Vector<T, S>& lhs, const Vector<T, S>& rhs);

	/**
	 * @brief Multiplication-assignment operator
	 * Multiplies the current vector by a given scalar
	 * @param lhs Vector to multiply
	 * @param scalar Scalar to multiply by
	 * @return Reference to the current vector
	 */
	template <class T, std::size_t S>
	constexpr Vector<T, S>& operator*=(Vector<T, S>& lhs, float scalar);

	// Explicit templates
	template class Vector<int, 1>;
	template class Vector<int, 2>;
	template class Vector<int, 3>;
	template class Vector<int, 4>;
	template class Vector<float, 1>;
	template class Vector<float, 2>;
	template class Vector<float, 3>;
	template class Vector<float, 4>;
	template class Vector<double, 1>;
	template class Vector<double, 2>;
	template class Vector<double, 3>;
	template class Vector<double, 4>;
}

#include "Vector.inl" // Inclusion model