#ifndef INCLUDE_MATRIX_3D_PRIVATE
#define INCLUDE_MATRIX_3D_PRIVATE

template<typename T, std::size_t S>
template<typename ArrayData>
	requires
		std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<T, S * S>>
constexpr VML::Matrix<T, S>::Matrix(ArrayData&& values)
	: _mData1D(std::forward<ArrayData>(values))
{
};

		template<typename T, std::size_t S>
template<typename ArrayData>
	requires
		std::is_same_v<std::remove_cvref_t<ArrayData>, std::array<std::array<T, S>, S>>
constexpr VML::Matrix<T, S>::Matrix(ArrayData&& values)
	: _mData2D(std::forward<ArrayData>(values))
{
};

#endif