#include "Vector.hpp"
namespace VL
{
	template<class T, std::size_t S>
	constexpr Vector<T, S>::Vector()
		: m_vData{}
	{
	}

	template<class T, std::size_t S>
	constexpr Vector<T, S>::Vector(T value)
		: m_vData{}
	{
		for (auto i = 0; i < S; i++) {
			m_vData[i] = value;
		}
	}

	template<class T, std::size_t S>
	template<typename ArrayData>
		requires
	std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<T, S>>
		constexpr Vector<T, S>::Vector(ArrayData&& values)
		: m_vData(std::forward<ArrayData>(values))
	{
	}

	template<class T, std::size_t S>
	constexpr T& Vector<T, S>::operator[](std::size_t i)
	{
		return m_vData[i];
	}

	template<class T, std::size_t S>
	constexpr const T& Vector<T, S>::operator[](std::size_t i) const
	{
		return m_vData[i];
	}

	template<class T, std::size_t S>
	constexpr std::array<T, S> Vector<T, S>::toArray() const noexcept
	{
		return m_vData;
	}

	template <class T, std::size_t S>
	constexpr Vector<T, S>& operator+=(Vector<T, S>& lhs, const Vector<T, S>& rhs)
	{
		for (std::size_t i = 0; i < S; i++)
		{
			lhs[i] += rhs[i];
		}

		return lhs;
	}

	template <class T, std::size_t S>
	constexpr Vector<T, S> operator+(Vector<T, S> lhs, const Vector<T, S>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T, std::size_t S>
	constexpr Vector<T, S>& operator-=(Vector<T, S>& lhs, const Vector<T, S>& rhs)
	{
		for (std::size_t i = 0; i < S; i++)
		{
			lhs[i] -= rhs[i];
		}

		return lhs;
	}

	template <class T, std::size_t S>
	constexpr Vector<T, S> operator-(Vector<T, S> lhs, const Vector<T, S>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	template <class T, std::size_t S>
	constexpr Vector<T, S>& operator*=(Vector<T, S>& lhs, float rhs)
	{
		for (std::size_t i = 0; i < S; i++)
		{
			lhs[i] *= rhs;
		}

		return lhs;
	}

	template <class T, std::size_t S>
	constexpr Vector<T, S> operator*(Vector<T, S> lhs, float rhs)
	{
		lhs *= rhs;
		return lhs;
	}
}