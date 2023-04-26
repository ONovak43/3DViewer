#include "MatrixTransform.hpp"
namespace VL
{
	template<typename T>
	constexpr float determinant(const Matrix<T, 2>& matrix)
	{
		return static_cast<float>(matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0));
	}

	template<typename T>
	constexpr float determinant(const Matrix<T, 3>& matrix)
	{
		// Cramer's Rule is used for calculating the determinant 

		// Cofactors (det 2x2 matrix)
		auto c11 = matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1);
		auto c12 = matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0);
		auto c13 = matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0);

		return static_cast<float>(matrix(0, 0) * c11 - matrix(0, 1) * c12 + matrix(0, 2) * c13);
	}

	template<typename T>
	constexpr float determinant(const Matrix<T, 4>& matrix)
	{
		// Cramer's Rule is used for calculating the determinant 

		// Cofactors (det 2x2 matrix)
		auto s11 = matrix(2, 2) * matrix(3, 3) - matrix(2, 3) * matrix(3, 2);
		auto s12 = matrix(2, 1) * matrix(3, 3) - matrix(2, 3) * matrix(3, 1);
		auto s13 = matrix(2, 1) * matrix(3, 2) - matrix(2, 2) * matrix(3, 1);
		auto s14 = matrix(2, 0) * matrix(3, 3) - matrix(2, 3) * matrix(3, 0);
		auto s15 = matrix(2, 0) * matrix(3, 2) - matrix(2, 2) * matrix(3, 0);
		auto s16 = matrix(2, 0) * matrix(3, 1) - matrix(3, 0) * matrix(2, 1);

		// Cofactors (det 3x3 matrix)
		auto c21 = matrix(1, 1) * s11 - matrix(1, 2) * s12 + matrix(1, 3) * s13;
		auto c22 = matrix(1, 0) * s11 - matrix(1, 2) * s14 + matrix(1, 3) * s15;
		auto c23 = matrix(1, 0) * s12 - matrix(1, 1) * s14 + matrix(1, 3) * s16;
		auto c24 = matrix(1, 0) * s13 - matrix(1, 1) * s15 + matrix(1, 2) * s16;

		return static_cast<float>(matrix(0, 0) * c21 - matrix(0, 1) * c22 + matrix(0, 2) * c23 - matrix(0, 3) * c24);
	}

	template<typename T, std::size_t S>
	constexpr Matrix<T, S> transpose(const Matrix<T, S>& matrix)
	{
		Matrix<T, S> result;
		for (auto i = 0; i < S; ++i) {
			for (auto j = 0; j < S; ++j) {
				result(i, j) = matrix(j, i);
			}
		}
		return result;
	}

	template<typename T>
	constexpr Matrix<T, 2> inverse(const Matrix<T, 2>& matrix)
	{
		auto det = determinant(matrix);

		if (det == 0) {
			throw std::runtime_error("Matrix is singular and cannot be inverted.");
		}

		// Transposed Cofactor's Matrix
		Matrix<T, 2> result;

		// Transposing and calculating det 2x2 divided by the determinant
		result(0, 0) = matrix(1, 1);
		result(1, 0) = -matrix(1, 0);
		result(0, 1) = -matrix(0, 1);
		result(1, 1) = matrix(0, 0);

		result *= 1.f / det;

		return result;
	}

	template<typename T>
	constexpr Matrix<T, 3> inverse(const Matrix<T, 3>& matrix)
	{
		auto det = determinant(matrix);

		if (det == 0) {
			throw std::runtime_error("Matrix is singular and cannot be inverted.");
		}

		// Transposed Cofactor's Matrix
		Matrix<T, 3> result;

		// Transposing and calculating det 2x2 divided by the determinant
		result(0, 0) = +(matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1));
		result(1, 0) = -(matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0));
		result(2, 0) = +(matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0));

		result(0, 1) = -(matrix(0, 1) * matrix(2, 2) - matrix(0, 2) * matrix(2, 1));
		result(1, 1) = +(matrix(0, 0) * matrix(2, 2) - matrix(0, 2) * matrix(2, 0));
		result(2, 1) = -(matrix(0, 0) * matrix(2, 1) - matrix(0, 1) * matrix(2, 0));

		result(0, 2) = +(matrix(0, 1) * matrix(1, 2) - matrix(0, 2) * matrix(1, 1));
		result(1, 2) = -(matrix(0, 0) * matrix(1, 2) - matrix(0, 2) * matrix(1, 0));
		result(2, 2) = +(matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0));

		result *= 1.f / det;

		return result;
	}

	template<typename T>
	constexpr Matrix<T, 4> inverse(const Matrix<T, 4>& matrix)
	{
		auto det = determinant(matrix);

		if (det == 0) {
			throw std::runtime_error("Matrix is singular and cannot be inverted.");
		}

		// Cofactors (det 2x2 matrix)
		auto s01 = matrix(2, 2) * matrix(3, 3) - matrix(2, 3) * matrix(3, 2);
		auto s02 = matrix(2, 1) * matrix(3, 3) - matrix(2, 3) * matrix(3, 1);
		auto s03 = matrix(2, 1) * matrix(3, 2) - matrix(2, 2) * matrix(3, 1);
		auto s04 = matrix(2, 0) * matrix(3, 3) - matrix(2, 3) * matrix(3, 0);
		auto s05 = matrix(2, 0) * matrix(3, 2) - matrix(2, 2) * matrix(3, 0);
		auto s06 = matrix(2, 0) * matrix(3, 1) - matrix(3, 0) * matrix(2, 1);
		auto s07 = matrix(1, 2) * matrix(3, 3) - matrix(1, 3) * matrix(3, 2);
		auto s08 = matrix(1, 1) * matrix(3, 3) - matrix(1, 3) * matrix(3, 1);
		auto s09 = matrix(1, 1) * matrix(3, 2) - matrix(1, 2) * matrix(3, 1);
		auto s10 = matrix(1, 0) * matrix(3, 3) - matrix(1, 3) * matrix(3, 0);
		auto s11 = matrix(1, 0) * matrix(3, 2) - matrix(1, 2) * matrix(3, 0);
		auto s12 = matrix(1, 0) * matrix(3, 1) - matrix(1, 1) * matrix(3, 0);
		auto s13 = matrix(1, 2) * matrix(2, 3) - matrix(1, 3) * matrix(2, 2);
		auto s14 = matrix(1, 1) * matrix(2, 3) - matrix(1, 3) * matrix(2, 1);
		auto s15 = matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1);
		auto s16 = matrix(1, 0) * matrix(2, 3) - matrix(1, 3) * matrix(2, 0);
		auto s17 = matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0);
		auto s18 = matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0);

		// Transposed Cofactor's Matrix
		Matrix<T, 4> result;

		result(0, 0) = +(matrix(1, 1) * s01 - matrix(1, 2) * s02 + matrix(1, 3) * s03);
		result(1, 0) = -(matrix(1, 0) * s01 - matrix(1, 2) * s04 + matrix(1, 3) * s05);
		result(2, 0) = +(matrix(1, 0) * s02 - matrix(1, 1) * s04 + matrix(1, 3) * s06);
		result(3, 0) = -(matrix(1, 0) * s03 - matrix(1, 1) * s05 + matrix(1, 2) * s06);

		result(0, 1) = -(matrix(0, 1) * s01 - matrix(0, 2) * s02 + matrix(0, 3) * s03);
		result(1, 1) = +(matrix(0, 0) * s01 - matrix(0, 2) * s04 + matrix(0, 3) * s05);
		result(2, 1) = -(matrix(0, 0) * s02 - matrix(0, 1) * s04 + matrix(0, 3) * s06);
		result(3, 1) = +(matrix(0, 0) * s03 - matrix(0, 1) * s05 + matrix(0, 2) * s06);

		result(0, 2) = +(matrix(0, 1) * s07 - matrix(0, 2) * s08 + matrix(0, 3) * s09);
		result(1, 2) = -(matrix(0, 0) * s07 - matrix(0, 2) * s10 + matrix(0, 3) * s11);
		result(2, 2) = +(matrix(0, 0) * s08 - matrix(0, 1) * s10 + matrix(0, 3) * s12);
		result(3, 2) = -(matrix(0, 0) * s09 - matrix(0, 1) * s11 + matrix(0, 2) * s12);

		result(0, 3) = -(matrix(0, 1) * s13 - matrix(0, 2) * s14 + matrix(0, 3) * s15);
		result(1, 3) = +(matrix(0, 0) * s13 - matrix(0, 2) * s16 + matrix(0, 3) * s17);
		result(2, 3) = -(matrix(0, 0) * s14 - matrix(0, 1) * s16 + matrix(0, 3) * s18);
		result(3, 3) = +(matrix(0, 0) * s15 - matrix(0, 1) * s17 + matrix(0, 2) * s18);

		result *= 1.f / det;

		return result;
	}

	template<typename T>
	constexpr VL::Matrix<T, 4> translate(const Matrix<T, 4>& matrix, const Vector<T, 3>& vector)
	{
		auto result = matrix;

		result(3, 0) = matrix[0] * vector[0] + matrix[4] * vector[1] + matrix[8] * vector[2] + matrix[12];
		result(3, 1) = matrix[1] * vector[0] + matrix[5] * vector[1] + matrix[9] * vector[2] + matrix[13];
		result(3, 2) = matrix[2] * vector[0] + matrix[6] * vector[1] + matrix[10] * vector[2] + matrix[14];
		result(3, 3) = matrix[3] * vector[0] + matrix[7] * vector[1] + matrix[11] * vector[2] + matrix[15];

		return result;
	}

	template<typename T>
	constexpr VL::Matrix<T, 4> scale(const Matrix<T, 4>& matrix, const Vector<T, 3>& vector)
	{
		VL::Matrix<T, 4> result = matrix;
		result(0, 0) *= vector[0];
		result(0, 1) *= vector[0];
		result(0, 2) *= vector[0];
		result(0, 3) *= vector[0];

		result(1, 0) *= vector[1];
		result(1, 1) *= vector[1];
		result(1, 2) *= vector[1];
		result(1, 3) *= vector[1];

		result(2, 0) *= vector[2];
		result(2, 1) *= vector[2];
		result(2, 2) *= vector[2];
		result(2, 3) *= vector[2];

		return result;
	}

	template<typename T>
	constexpr VL::Matrix<T, 4> rotate(const Matrix<T, 4>& matrix, T angle, const Vector<T, 3>& vector)
	{
		T c = std::cos(angle);
		T s = std::sin(angle);
		T x = vector[0];
		T y = vector[1];
		T z = vector[2];		

		Vector<T, 3> axis(VL::normalize(vector));

		T oneMinusC = static_cast<T>(1) - c;
		Vector<T, 3> temp = axis * oneMinusC;

		Matrix<T, 4> rotationMatrix(1);
		rotationMatrix(0, 0) = temp[0] * axis[0] + c;
		rotationMatrix(0, 1) = temp[0] * axis[1] + axis[2] * s;
		rotationMatrix(0, 2) = temp[0] * axis[2] - axis[1] * s;

		rotationMatrix(1, 0) = temp[1] * axis[0] - axis[2] * s;
		rotationMatrix(1, 1) = temp[1] * axis[1] + c;
		rotationMatrix(1, 2) = temp[1] * axis[2] + axis[0] * s;

		rotationMatrix(2, 0) = temp[2] * axis[0] + axis[1] * s;
		rotationMatrix(2, 1) = temp[2] * axis[1] - axis[0] * s;
		rotationMatrix(2, 2) = temp[2] * axis[2] + c;

		Matrix<T, 4> result = rotationMatrix * matrix;

		return result;
	}

	template<typename T>
	constexpr Matrix<T, 4> lookAt(Vector<T, 3> position, Vector<T, 3> target, Vector<T, 3> upVector)
	{
		// Gram-Schmidt process to get orthonormalized camera coordinates
		const auto d = normalize(target - position);
		const auto r = normalize(cross(d, upVector));
		const auto u = cross(r, d);

		// Rotation * Translation
		Matrix<T, 4> result(1);

		result(0, 0) = r[0];
		result(0, 1) = r[1];
		result(0, 2) = r[2];

		result(1, 0) = u[0];
		result(1, 1) = u[1];
		result(1, 2) = u[2];		

		result(2, 0) = -d[0];
		result(2, 1) = -d[1];
		result(2, 2) = -d[2];

		result(3, 0) = -dot(u, position);
		result(3, 1) = -dot(r, position);
		result(3, 2) = dot(d, position);

		return result;
	}

	template<typename T>
	constexpr Matrix<T, 4> ortho(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		// (Scale matrix) * (Translation matrix)
		Matrix<T, 4> result;

		// Set diagonal
		result(0, 0) = static_cast<T>(2) / (right - left);
		result(1, 1) = static_cast<T>(2) / (bottom - top);
		result(2, 2) = static_cast<T>(-2) / (zFar - zNear);
		result(3, 3) = static_cast<T>(2);

		// Set 4th column
		result(0, 3) = (left - right) / (right - left);
		result(1, 3) = (top - bottom) / (bottom - top);
		result(2, 3) = (zNear - zFar) / (zFar - zNear);

		return result;
	};

	template<typename T>
	constexpr Matrix<T, 4> perspective(T fov, T aspect, T zNear, T zFar)
	{
		// Perspective projection
		// (Orthographic matrix) * (Perspective matrix)
		Matrix<T, 4> result;

		auto f = static_cast<T>(1) / tan(fov / static_cast<T>(2));

		// Set diagonal
		result(0, 0) = f / aspect;
		result(1, 1) = f;
		result(2, 2) = -(zFar + zNear) / (zFar - zNear);

		// Set other columns
		result(2, 3) = -static_cast<T>(1);
		result(3, 2) = -(static_cast<T>(2) * zNear * zFar) / (zFar - zNear);

		return result;
	}
}