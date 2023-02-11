#pragma once
#include <numeric>
#include <algorithm>
#include <cstddef>
#include "Vector.hpp"

namespace VML
{
	template<typename T, std::size_t S>
	T dot(const VML::Vector<T, S>& v1, const VML::Vector<T, S>& v2);

	template<typename T>
	VML::Vector<T, 3> cross(const VML::Vector<T, 3>& v1, const VML::Vector<T, 3>& v2);

	template<typename T, std::size_t S>
	auto length(const VML::Vector<T, S>& v);

	template<typename T, std::size_t S>
	VML::Vector<T, S> normalize(const VML::Vector<T, S>& v);
}

#include "VectorTransform.inl"