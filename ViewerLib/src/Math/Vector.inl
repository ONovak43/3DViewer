#pragma once

template<class T, std::size_t S>
constexpr VML::Vector<T, S>::Vector()
	: _vData{}
{
}

template<class T, std::size_t S>
template<typename ArrayData>
	requires
std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<T, S>>
constexpr VML::Vector<T, S>::Vector(ArrayData&& values)
	: _vData(std::forward<ArrayData>(values))
{
};

template<class T, std::size_t S>
constexpr T& VML::Vector<T, S>::operator[](std::size_t i)
{
	return _vData[i];
}

template<class T, std::size_t S>
constexpr const T& VML::Vector<T, S>::operator[](std::size_t i) const
{
	return _vData[i];
}

template<class T, std::size_t S>
constexpr std::array<T, S> VML::Vector<T, S>::toArray() const noexcept
{
	return _vData;
}

template <class T, std::size_t S>
constexpr VML::Vector<T, S> VML::operator+(const VML::Vector<T, S>& lhs, const VML::Vector<T, S>& rhs)
{
	VML::Vector<T, S> result;

	for (auto i = 0; i < S; ++i)
	{
		result[i] = lhs[i] + rhs[i];
	}

	return result;
}

template <class T, std::size_t S>
constexpr VML::Vector<T, S> VML::operator-(const VML::Vector<T, S>& lhs, const VML::Vector<T, S>& rhs)
{
	Vector<T, S> result;

	for (auto i = 0; i < S; ++i)
	{
		result[i] = lhs[i] - rhs[i];
	}

	return result;
}

template <class T, std::size_t S>
constexpr VML::Vector<T, S> VML::operator*(const VML::Vector<T, S>& lhs, float rhs)
{
	Vector<T, S> result;

	for (auto i = 0; i < S; ++i)
	{
		result[i] = lhs[i] * rhs;
	}

	return result;
}

template <class T, std::size_t S>
constexpr VML::Vector<T, S>& VML::operator+=(VML::Vector<T, S>& lhs, const VML::Vector<T, S>& rhs)
{
	for (auto i = 0; i < S; i++)
	{
		lhs[i] += rhs[i];
	}

	return lhs;
}

template <class T, std::size_t S>
constexpr VML::Vector<T, S>& VML::operator-=(VML::Vector<T, S>& lhs, const VML::Vector<T, S>& rhs)
{
	for (std::size_t i = 0; i < S; i++)
	{
		lhs[i] -= rhs[i];
	}

	return lhs;
}

template <class T, std::size_t S>
constexpr VML::Vector<T, S>& VML::operator*=(VML::Vector<T, S>& lhs, float rhs)
{
	for (auto i = 0; i < S; i++)
	{
		lhs[i] *= rhs;
	}

	return lhs;
}

