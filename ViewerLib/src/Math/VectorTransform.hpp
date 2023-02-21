#pragma once
#include <numeric>
#include <algorithm>
#include <cstddef>
#include "Vector.hpp"

namespace VL
{
	template<typename T, std::size_t S>
	T dot(const VL::Vector<T, S>& v1, const VL::Vector<T, S>& v2);

	template<typename T>
	VL::Vector<T, 3> cross(const VL::Vector<T, 3>& v1, const VL::Vector<T, 3>& v2);

	template<typename T, std::size_t S>
	auto length(const VL::Vector<T, S>& v);

	template<typename T, std::size_t S>
	VL::Vector<T, S> normalize(const VL::Vector<T, S>& v);
}

#include "VectorTransform.inl"