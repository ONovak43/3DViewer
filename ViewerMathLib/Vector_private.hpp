#ifndef INCLUDE_VECTOR_PRIVATE
#define INCLUDE_VECTOR_PRIVATE

template<class T, std::size_t S>
template<typename ArrayData>
	requires
		std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<T, S>>
constexpr VML::Vector<T, S>::Vector(ArrayData&& values)
	: _vData(std::forward<ArrayData>(values))
{
};

#endif