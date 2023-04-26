#include "pch.hpp"

namespace MathTests
{
	namespace MatrixTest
	{
		using VL::Matrix;

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I need to create a new zero matrix.
		//		[Value] So I can later make it a model matrix.
		TEST(MatrixTest, TestDefaultConstructor) {
			// Given
			Matrix<float, 4> m1;

			// Then
			for (auto i = 0; i < 16; ++i) {
				EXPECT_FLOAT_EQ(m1[i], 0);
			}
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I need to create a new identity matrix matrix.
		//		[Value] So I can later make it a model matrix.
		TEST(MatrixTest, TestConstructorWithValue) {
			// Given
			Matrix<float, 4> m2(1.f);

			// Then
			for (auto i = 0; i < 16; ++i) {
				EXPECT_FLOAT_EQ(m2[i], (i % 5 == 0 ? 1.f : 0.f));
			}
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I need to create a new matrix with calculated values.
		//		[Value] So I can use the result to apply transformations to 3D models.
		TEST(MatrixTest, TestConstructorWith1DArray) {
			// Given
			std::array<float, 16> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<float, 4> m3(data);

			// Then
			for (auto i = 0; i < 16; ++i) {
				EXPECT_FLOAT_EQ(m3[i], data[i]);
			}
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I need to create a new matrix with calculated values.
		//		[Value] So I can use the result to apply transformations to 3D models.
		TEST(MatrixTest, TestConstructorWith2DArray) {
			// Given
			std::array<std::array<float, 4>, 4> mdata = { {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}} };
			Matrix<float, 4> m4(mdata);

			// Then
			for (auto i = 0; i < 4; ++i) {
				for (std::size_t j = 0; j < 4; j++) {
					EXPECT_FLOAT_EQ(mdata[i][j], m4(i, j));
				}
			}
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I want to access elements in the matrix using the parenthesis operator.
		//		[Value] So that I can modify and retrieve values in the matrix using row and column indices.
		TEST(MatrixTest, TestParenthesisOperator) {

			// Given
			constexpr std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);

			// When
			auto element = m1(2, 3);

			// Then
			EXPECT_EQ(12, element);

			// When
			m1(1, 2) = 22;

			// Then
			EXPECT_EQ(22, m1(1, 2));
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I want to access elements in the matrix using the subscript operator.
		//		[Value] So that I can modify and retrieve values in the matrix.
		TEST(MatrixTest, TestSubscriptOperator)
		{
			// Given
			constexpr std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);

			// When
			auto element = m1[4];

			// Then
			EXPECT_EQ(mdata[4], element);

			// When
			m1[4] = 10;

			// Then
			EXPECT_EQ(10, m1[4]);
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I want to access elements in the matrix using the subscript operator.
		//		[Value] So that I can modify and retrieve values in the matrix.
		TEST(MatrixTest, TestSubscriptOperator2x2)
		{
			// Given
			constexpr std::array<int32_t, 4> mdata = { 1, 2, 3, 4 };
			Matrix<int32_t, 2> m1(mdata);

			// When
			auto element = m1[3];

			// Then
			EXPECT_EQ(element, mdata[3]);

			// When
			m1[3] = 10;

			// Then
			EXPECT_EQ(10, m1[3]);
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I want to convert the matrix to an array.
		//		[Value] So that I can retrieve values in the matrix.
		TEST(MatrixTest, TestToArray)
		{
			// Given
			constexpr std::array<std::array<int32_t, 3>, 3> mdata = { {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} };
			Matrix<int32_t, 3> m1(mdata);

			// When
			auto element = m1.toArray();

			// Then
			for (auto i = 0; i < 3; ++i) {
				for (auto j = 0; j < 3; ++j) {
					EXPECT_EQ(mdata[i][j], element[i][j]);
				}
			}
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to subtract two matrices.
		//      [Value] So I can use the result to apply transformations to 3D models.
		TEST(MatrixTest, TestAdditionOperator) {
			// Given
			std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);

			mdata = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
			Matrix<int32_t, 4> m2(mdata);

			std::array<int32_t, 16> expectedResult = { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 };

			// When
			auto result = m1 + m2;

			// Then
			for (auto i = 0; i < 16; ++i) {
				EXPECT_EQ(expectedResult[i], result[i]);
			}
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to subtract two matrices.
		//      [Value] So I can use the result to apply transformations to 3D models.
		TEST(MatrixTest, TestSubtractionOperator) {
			// Given
			std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);

			mdata = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
			Matrix<int32_t, 4> m2(mdata);

			std::array<int32_t, 16> expectedResult = { -15, -13, -11, -9, -7, -5, -3, -1, 1, 3, 5, 7, 9, 11, 13, 15 };

			// When
			auto result = m1 - m2;

			// Then
			for (auto i = 0; i < 16; ++i) {
				EXPECT_EQ(expectedResult[i], result[i]);
			}
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I want to multiply two matrices together.
		//      [Value] So that I can apply multiple transformations to an object at once.
		TEST(MatrixTest, TestMultiplyOperator) {
			// Given
			std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);
			Matrix<int32_t, 4> m2(mdata);

			mdata = { 90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600 };
			Matrix<int32_t, 4> expected(mdata);

			// When
			auto result = m1 * m2;

			// Then
			for (auto i = 0; i < 16; ++i) {
				EXPECT_EQ(expected[i], result[i]);
			}
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I want to multiply two matrices together.
		//      [Value] So that I can apply multiple transformations to an object at once.
		TEST(MatrixTest, TestMultiplyOperator3x3Matrix) {
			// Given
			std::array<int32_t, 9> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Matrix<int32_t, 3> m1(mdata);
			Matrix<int32_t, 3> m2(mdata);

			mdata = { 30, 36, 42, 66, 81, 96, 102, 126, 150 };

			// When
			auto result = m1 * m2;

			// Then
			for (auto i = 0; i < 9; ++i) {
				EXPECT_EQ(mdata[i], result[i]);
			}
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I want to multiply a matrix by a scalar.
		//      [Value] So that I can scale an object.
		TEST(MatrixTest, TestMultiplyOperatorForScalar)
		{
			// Given
			constexpr std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);
			constexpr auto scalar = 2.0f;

			// When
			auto result = m1 * scalar;

			// Then
			for (auto i = 0; i < 16; ++i)
			{
				auto expectedResult = mdata[i] * scalar;
				EXPECT_EQ(expectedResult, result[i]);
			}
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I want to multiply a matrix by a scalar.
		//		[Value] So that I can scale an object.
		TEST(MatrixTest, MultiplyAssignmentOperatorWithScalar)
		{
			// Given 
			constexpr std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);
			constexpr auto scalar = 2.0f;

			// When
			m1 *= scalar;

			// Then
			for (auto i = 0; i < 16; ++i)
			{
				auto expectedResult = mdata[i] * scalar;
				EXPECT_EQ(expectedResult, m1[i]);
			}
		}

		// Story: 
		//      [Who] As a 3DViewer programmer, I need to compare two matrices. 
		//      [What] I need to compare two matrices
		//      [Value] So that I can check if a transformation matrix is correct.
		TEST(MatrixTest, TestEqualityOperator)
		{
			// Given
			std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);
			Matrix<int32_t, 4> m2(mdata);

			mdata[15] = 17;
			Matrix<int32_t, 4> m3(mdata);

			// When
			bool equal = (m1 == m2);
			bool notEqual = (m1 == m3);

			// Then
			EXPECT_TRUE(equal);
			EXPECT_FALSE(notEqual);
		}

		// Story: 
		//      [Who] As a 3DViewer programmer, I need to compare two matrices. 
		//      [What] I need to compare two matrices. 
		//      [Value] So that I can check if a transformation matrix is correct.
		TEST(MatrixTest, TestInequalityOperator)
		{
			// Given
			std::array<int32_t, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix<int32_t, 4> m1(mdata);
			Matrix<int32_t, 4> m2(mdata);

			mdata[15] = 17;
			Matrix<int32_t, 4> m3(mdata);

			// When
			bool inequal = (m1 != m3);
			bool equal = (m1 != m2);

			// Then
			EXPECT_TRUE(inequal);
			EXPECT_FALSE(equal);
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to calculate ortho matrix.
		//      [Value] So that I can see the 3D objects in orthographic view.
		TEST(MatrixTransformTest, TestLookAt) {
			// Given
			constexpr auto left = -1.0f;
			constexpr auto right = 1.0f;
			constexpr auto bottom = -1.0f;
			constexpr auto top = 1.0f;
			constexpr auto zNear = -1.0f;
			constexpr auto zFar = 1.0f;

			// When
			auto orthoMatrix = VL::ortho(left, right, bottom, top, zNear, zFar);

			// Then
			EXPECT_FLOAT_EQ(2.0f / (right - left), orthoMatrix(0, 0));
			EXPECT_FLOAT_EQ(2.0f / (bottom - top), orthoMatrix(1, 1));
			EXPECT_FLOAT_EQ(-2.0f / (zFar - zNear), orthoMatrix(2, 2));
			EXPECT_FLOAT_EQ(2.0f, orthoMatrix(3, 3));
			EXPECT_FLOAT_EQ((left - right) / (right - left), orthoMatrix(0, 3));
			EXPECT_FLOAT_EQ((top - bottom) / (bottom - top), orthoMatrix(1, 3));
			EXPECT_FLOAT_EQ((zNear - zFar) / (zFar - zNear), orthoMatrix(2, 3));
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to calculate ortho matrix.
		//      [Value] So that I can see the 3D objects in orthographic view.
		TEST(MatrixTransformTest, TestOrthoMatrix) {
			// Given
			constexpr auto left = -1.0f;
			constexpr auto right = 1.0f;
			constexpr auto bottom = -1.0f;
			constexpr auto top = 1.0f;
			constexpr auto zNear = -1.0f;
			constexpr auto zFar = 1.0f;

			// When
			auto orthoMatrix = VL::ortho(left, right, bottom, top, zNear, zFar);

			// Then
			EXPECT_FLOAT_EQ(2.0f / (right - left), orthoMatrix(0, 0));
			EXPECT_FLOAT_EQ(2.0f / (bottom - top), orthoMatrix(1, 1));
			EXPECT_FLOAT_EQ(-2.0f / (zFar - zNear), orthoMatrix(2, 2));
			EXPECT_FLOAT_EQ(2.0f, orthoMatrix(3, 3));
			EXPECT_FLOAT_EQ((left - right) / (right - left), orthoMatrix(0, 3));
			EXPECT_FLOAT_EQ((top - bottom) / (bottom - top), orthoMatrix(1, 3));
			EXPECT_FLOAT_EQ((zNear - zFar) / (zFar - zNear), orthoMatrix(2, 3));
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to calculate a perspective projection matrix.
		//      [Value] So that the objects in the scene appear to be in the distance or closer.
		TEST(MatrixTransformTest, TestPerspectiveMatrix)
		{
			// Given
			constexpr auto fov = 90.f;
			constexpr auto aspect = 16.f / 9.f;
			constexpr auto zNear = 0.1f;
			constexpr auto zFar = 100.0f;

			// When
			auto perspectiveMatrix = VL::perspective<float>(fov, aspect, zNear, zFar);

			// Then
			auto f = 1.f / tan(fov / 2.f);

			EXPECT_FLOAT_EQ(f / aspect, perspectiveMatrix(0, 0));
			EXPECT_FLOAT_EQ(f, perspectiveMatrix(1, 1));
			EXPECT_FLOAT_EQ(-(zFar + zNear) / (zFar - zNear), perspectiveMatrix(2, 2));
			EXPECT_FLOAT_EQ(-(2.f * zNear * zFar) / (zFar - zNear), perspectiveMatrix(3, 2));
			EXPECT_FLOAT_EQ(-1.f, perspectiveMatrix(2, 3));
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What]  I need to calculate the determinant of a 4x4 matrix.
		//      [Value] So that I can calculate the scaling factor and inverse of a matrix.
		TEST(MatrixTransformTest, TestDeterminantZeroDeterminant4x4) {
			// Given
			std::array<float, 16> mdata = { 1, 2, 3, 4, 1, 2, 3, 4, 0, 0, 3, 4, 0, 0, 0, 4 };
			Matrix<float, 4> m1(mdata);

			// When
			constexpr auto expectedResult = 0.f;
			auto result = VL::determinant(m1);

			// Then
			EXPECT_FLOAT_EQ(expectedResult, result);
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What]  I need to calculate the determinant of a 4x4 matrix.
		//      [Value] So that I can calculate the scaling factor and inverse of a matrix.
		TEST(MatrixTransformTest, TestDeterminantPositiveDeterminant4x4) {
			// Given
			Matrix<float, 4> m1(1.f);

			// When
			constexpr auto expectedResult = 1.f;
			auto result = VL::determinant(m1);

			// Then
			EXPECT_FLOAT_EQ(expectedResult, result);
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to calculate the determinant of a 4x4 matrix.
		//      [Value] So that I can calculate the scaling factor and inverse of a matrix.
		TEST(MatrixTransformTest, TestDeterminantNegativeDeterminant4x4) {
			// Given
			Matrix<float, 4> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 2.f, 1.f, 0.f, 4.f, 1.f, 0.f, 4.f, 1.f, 2.f, 0.f, 2.f, 1.f });

			// When
			constexpr auto expectedResult = -7.f;
			auto result = VL::determinant(m1);

			EXPECT_FLOAT_EQ(expectedResult, result);
		}

		// Story:
		//    [Who] As a 3DViewer programmer.
		//    [What] I need to calculate the determinant of a 3x3 matrix.
		//    [Value] So that I can calculate the scaling factor and inverse of a matrix.
		TEST(MatrixTransformTest, TestDeterminantZeroDeterminant3x3)
		{
			// Given
			std::array<float, 9> mdata = { 1, 2, 3, 1, 2, 3, 0, 0, 3 };
			Matrix<float, 3> m1(mdata);

			// When
			constexpr auto expectedResult = 0.f;
			auto result = VL::determinant(m1);

			// Then
			EXPECT_FLOAT_EQ(expectedResult, result);
		}


		// Story:
		//    [Who] As a 3DViewer programmer.
		//    [What] I need to calculate the determinant of a 3x3 matrix.
		//    [Value] So that I can calculate the scaling factor and inverse of a matrix.
		TEST(MatrixTransformTest, TestDeterminantPositiveDeterminant3x3)
		{
			// Given
			Matrix<float, 3> m1(1.f);

			// When
			constexpr auto expectedResult = 1.f;
			auto result = VL::determinant(m1);

			// Then
			EXPECT_FLOAT_EQ(expectedResult, result);
		}

		// Story:
		//    [Who] As a 3DViewer programmer.
		//    [What] I need to calculate the determinant of a 3x3 matrix.
		//    [Value] So that I can calculate the scaling factor and inverse of a matrix.
		TEST(MatrixTransformTest, TestDeterminantNegativeDeterminant3x3)
		{
			// Given
			Matrix<float, 3> m1(1.f);

			// Permutation 
			m1(0, 0) = 0;
			m1(0, 1) = 1;
			m1(1, 1) = 0;
			m1(1, 0) = 1;

			// When
			constexpr auto expectedResult = -1.f;
			auto result = VL::determinant(m1);

			// Then
			EXPECT_FLOAT_EQ(expectedResult, result);
		}

		// Story:
		//      [Who] As a graphics programmer.
		//      [What] I need to find the transpose of a matrix.
		//      [Value] So that I can quickly change the orientation of the objects in my 3D viewer.
		TEST(MatrixTransformTest, TestTranspose)
		{
			// Given
			Matrix<float, 3> m1(std::array{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f });

			// When
			Matrix<float, 3> result = VL::transpose(m1);

			// Then
			Matrix<float, 3> expectedResult(std::array{ 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f });
			EXPECT_EQ(expectedResult, result);
		}

		// Story:
		//		[Who] As a 2D game programmer.
		//		[What] I need to calculate the inverse of a 2x2 matrix.
		//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInverseSingular2x2)
		{
			// Given
			Matrix<float, 2> m1(std::array{ 1.f, 2.f, 2.f, 4.f });

			// Then
			EXPECT_THROW(VL::inverse(m1), std::runtime_error);

		}

		// Story:
		//		[Who] As a 2D game programmer.
		//		[What] I need to calculate the inverse of a 2x2 matrix.
		//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInversePositiveDeterminant2x2)
		{
			// Given
			Matrix<float, 2> m1(std::array{ 3.f, 1.f, 2.f, 5.f });

			// When
			std::array expectedResult{ 5.f / 13.f, -1.f / 13, -2.f / 13.f, 3.f / 13.f };
			auto result = VL::inverse(m1);

			// Then
			for (auto i = 0; i < 4; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}

		// Story:
		//		[Who] As a 2D game programmer.
		//		[What] I need to calculate the inverse of a 2x2 matrix.
		//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInverseNegativeDeterminant2x2)
		{
			// Given
			Matrix<float, 2> m1(std::array{ 2.f, 1.f, 2.f, 2.f });

			// When
			std::array expectedResult{ 1.f, -0.5f, -1.f, 1.f };
			auto result = VL::inverse(m1);

			// Then
			for (auto i = 0; i < 4; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}


		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to calculate the inverse of a 3x3 matrix.
		//      [Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInverseSingular3x3)
		{

			// Given
			Matrix<float, 3> m1(std::array{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f });

			// Then
			EXPECT_THROW(VL::inverse(m1), std::runtime_error);
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to calculate the inverse of a 3x3 matrix.
		//      [Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInversePositiveDeterminant3x3)
		{

			// Given
			Matrix<float, 3> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 1.f, 0.f, 1.f, 0.f, 4.f });

			// When
			std::array expectedResult{ 4.f, 0.f, -3.f, -8.f, 1.f, 6.f, -1.f, 0.f, 1.f };
			auto result = VL::inverse(m1);

			// Then
			for (auto i = 0; i < 9; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}

		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to calculate the inverse of a 3x3 matrix.
		//      [Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInverseNegativeDeterminant3x3)
		{
			// Given
			Matrix<float, 3> m1(std::array{ 1.f, 0.f, 3.f, 1.f, 0.f, 4.f, 2.f, 1.f, 0.f });

			// When
			std::array expectedResult{ 4.f, -3.f, 0.f, -8.f, 6.f, 1.f, -1.f, 1.f, 0.f };
			auto result = VL::inverse(m1);

			// Then
			for (auto i = 0; i < 9; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I need to calculate the inverse of a 4x4 matrix.
		//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInverseSingular4x4)
		{
			// Given
			Matrix<float, 4> m1(std::array{ 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f });

			// Then
			EXPECT_THROW(VL::inverse(m1), std::runtime_error);
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I need to calculate the inverse of a 4x4 matrix.
		//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInversePositiveDeterminant4x4)
		{
			// Given
			Matrix<float, 4> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 2.f, 1.f, 0.f, 4.f, 1.f, 0.f, 4.f, 1.f, 2.f, 0.f, 2.f, 1.f });

			// When
			std::array expectedResult{ -2.f / 7.f, 0.f, -1.f / 7.f, 5.f / 7.f, -20.f / 7.f, 1.f, 18.f / 7.f, -6.f / 7.f, -1.f / 7.f, 0.f, 3.f / 7.f, -1.f / 7.f, 6.f / 7.f, 0.f, -4.f / 7.f, -1.f / 7.f };
			auto result = VL::inverse(m1);

			// Then
			for (auto i = 0; i < 16; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}

		// Story:
		//		[Who] As a 3DViewer programmer.
		//		[What] I need to calculate the inverse of a 4x4 matrix.
		//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
		TEST(MatrixTransformTest, TestInverseNegativeDeterminant4x4)
		{
			// Given
			Matrix<float, 4> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 2.f, 1.f, 0.f, 4.f, 1.f, 0.f, 4.f, 1.f, 2.f, 0.f, 2.f, 1.f });

			// When
			std::array expectedResult{ -2.f / 7.f, 0.f, -1.f / 7.f, 5.f / 7.f, -20.f / 7.f, 1.f, 18.f / 7.f, -6.f / 7.f, -1.f / 7.f, 0.f, 3.f / 7.f, -1.f / 7.f, 6.f / 7.f, 0.f, -4.f / 7.f, -1.f / 7.f };
			auto result = VL::inverse(m1);

			// Then
			for (auto i = 0; i < 16; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}

		TEST(MatrixTransformTest, TestTranslateMatrixSuccess)
		{
			Matrix<float, 4> m1(std::array{ 1.f, 2.f, 3.f, 4.f,
											5.f, 6.f, 7.f, 8.f, 
											9.f, 10.f, 11.f, 12.f,
											13.f, 14.f, 15.f, 16.f });

			VL::Vector<float, 3> v(std::array{ 1.f, 2.f, 3.f });

			auto result = VL::translate(m1, v);

			VL::Matrix<float, 4> expectedResult(std::array{ 1.f, 2.f, 3.f, 4.f,
															5.f, 6.f, 7.f, 8.f,
															9.f, 10.f, 11.f, 12.f,
															51.f, 58.f, 65.f, 72.f });
			for (auto i = 0; i < 16; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}

		TEST(MatrixTransformTest, TestTranslateMatrixZeroVector)
		{
			Matrix<float, 4> m1(std::array{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f });

			auto result = VL::translate(m1, VL::Vector<float, 3>(std::array{ 0.f, 0.f, 0.f }));

			for (auto i = 0; i < 16; ++i)
			{
				EXPECT_FLOAT_EQ(m1[i], result[i]);
			}
		}
		TEST(MatrixTransformTest, TestTranslateMatrixZeroPosition)
		{
			Matrix<float, 4> m1(std::array{ 
				1.f, 2.f, 3.f, 4.f,
				5.f, 6.f, 7.f, 8.f,
				9.f, 10.f, 11.f, 12.f,
				13.f, 14.f, 15.f, 16.f });

			VL::Vector<float, 3> v(std::array{ -1.f, -2.f, -3.f });

			auto result = VL::translate(m1, v);

			VL::Matrix<float, 4> expectedResult(std::array{ 
				1.f, 2.f, 3.f, 4.f,
				5.f, 6.f, 7.f, 8.f,
				9.f, 10.f, 11.f, 12.f,
				-25.f, -30.f, -35.f, -40.f 
			});

			for (auto i = 0; i < 16; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}

		TEST(MatrixTransformTest, TestScale) 
		{
			VL::Matrix<float, 4> m1(std::array {
				1.0f, 2.0f, 3.0f, 4.0f,
				5.0f, 6.0f, 7.0f, 8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			});

			VL::Vector<float, 3> v(std::array{ 2.f, 3.f, 4.f });

			auto result = VL::scale(m1, v);

			VL::Matrix<float, 4> expectedResult(std::array{
				2.f, 4.f, 6.f, 8.f,
				15.f, 18.f, 21.f, 24.f,
				36.f, 40.f, 44.f, 48.f,
				13.f, 14.f, 15.f, 16.f
			});

			for (int i = 0; i < 16; ++i) {
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}
		}

		TEST(MatrixTransformTest, TestRotate) {
			Matrix<float, 4> m1(std::array{
				1.0f, 2.0f, 3.0f, 4.0f,
				5.0f, 6.0f, 7.0f, 8.0f,
				9.0f, 10.0f, 11.0f, 12.0f,
				13.0f, 14.0f, 15.0f, 16.0f
			});

			float angle = 0.5f;

			VL::Vector<float, 3> axis(std::array{ 0.f, 1.f, 0.f });

			Matrix<float, 4> expectedResult(std::array{
				-3.43725f, -3.03909f, -2.64093f, -2.24278f,
				5.f, 6.f, 7.f, 8.f,
				8.37767f, 9.73468f, 11.0917f, 12.4487f,
				13.f, 14.f, 15.f, 16.f
			});

			auto result = VL::rotate(m1, angle, axis);

			// Testování výsledku
			for (int i = 0; i < 16; i++) {
				EXPECT_NEAR(expectedResult[i], result[i], 0.0001f);
			}
		}

	}

	namespace VectorTest
	{
		using VL::Vector;

		// Story:
		//      [Who] As a programmer using the Vector class
		//      [What] I want to create a new vector with default values
		//      [Value] So that I can use it as a starting point for my calculations with unknown values.

		TEST(VectorTest, TestDefaultConstructor) {
			// Given
			Vector<float, 4> v4;

			// Then
			for (auto i = 0; i < 4; ++i) {
				EXPECT_FLOAT_EQ(v4[i], 0.f);
			}
		}

		// Story:
		//      [Who] As a programmer using the Vector class
		//      [What] I want to create a new vector with values from an array
		//      [Value] So that I can use it as a starting point for my calculations with values from an existing array.
		TEST(VectorTest, TestArrayConstructor) {
			// Given
			std::array<float, 3> data = { 1.f, 2.f, 3.f };
			Vector<float, 3> v3(data);

			// Then
			for (auto i = 0; i < 3; ++i) {
				EXPECT_FLOAT_EQ(v3[i], data[i]);
			}
		}

		// Story:
		//		[Who] As a user of the Vector class,
		//		[What] I need to test the [] operator
		//		[Value] So that I can ensure it returns a reference to the correct element in the vector
		TEST(VectorTest, TestBracketOperator) {
			// Given
			Vector<int, 4> v4(std::array{ 1, 2, 3, 4 });

			// Then
			EXPECT_EQ(v4[0], 1);
			EXPECT_EQ(v4[1], 2);
			EXPECT_EQ(v4[2], 3);
			EXPECT_EQ(v4[3], 4);

			// When
			v4[2] = 5;
			v4[3] = 33;

			// Then
			EXPECT_EQ(v4[2], 5);
			EXPECT_EQ(v4[3], 33);
		}

		// Story:
		//      [Who] As a programmer using the Vector class
		//      [What] I want to convert a vector to an array
		//      [Value] So that I can use the array for other calculations or for storing the vector's values.
		TEST(VectorTest, TestArrayConversion) {
			// Given
			Vector<float, 2> v2(std::array{ 1.f, 2.f });

			// When
			auto data = v2.toArray();

			// Then
			for (auto i = 0; i < 2; ++i) {
				EXPECT_FLOAT_EQ(v2[i], data[i]);
			}
		}

		// Story:
		//      [Who] As a programmer using the Vector class
		//      [What] I want to add two vectors together
		//      [Value] So that I can combine their values for calculations.
		TEST(VectorTest, TestAdditionOperator) {
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			Vector<float, 4> v42(std::array{ 1.f, 2.f, 3.f, 4.f });

			// When
			auto result = v41 + v42;

			// Then
			for (auto i = 0; i < 4; ++i) {
				auto expectedValue = 2 * (i + 1);
				EXPECT_FLOAT_EQ(result[i], expectedValue);
			}
		}

		// Story:
		//      [Who] As a developer using Vector class.
		//      [What] I need to test the addition-assignment operator.
		//      [Value] So I can ensure that it correctly adds the elements of two vectors and assigns the result to the left-hand side vector.
		TEST(VectorTest, TestAdditionAssignmentOperator)
		{
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			Vector<float, 4> v42(std::array{ 5.f, 6.f, 7.f, 8.f });

			// When
			v41 += v42;

			// Then
			EXPECT_FLOAT_EQ(v41[0], 6);
			EXPECT_FLOAT_EQ(v41[1], 8);
			EXPECT_FLOAT_EQ(v41[2], 10);
			EXPECT_FLOAT_EQ(v41[3], 12);
		}

		// Story:
		//      [Who] As a 3DViewer programmer.
		//      [What] I need to subtract one vector from another.
		//      [Value] So that I can use the result to translate a 3D model.
		TEST(VectorTest, TestSubtractionOperator)
		{
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			Vector<float, 4> v42(std::array{ 4.f, 3.f, 2.f, 1.f });
			std::array expectedResult = std::array{ -3.f, -1.f, 1.f, 3.f };

			auto result = v41 - v42;

			// Then
			for (auto i = 0; i < 4; ++i) {
				EXPECT_FLOAT_EQ(result[i], expectedResult[i]);
			}
		}

		// Story:
		//      [Who] As a developer using Vector class.
		//      [What] I need to test the subtraction-assignment operator.
		//      [Value] So I can ensure that it correctly subtracts the elements of two vectors and assigns the result to the left-hand side vector.
		TEST(VectorTest, TestSubtractionAssignmentOperator)
		{
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			Vector<float, 4> v42(std::array{ 4.f, 3.f, 2.f, 1.f });
			std::array expectedResult = std::array{ -3.f, -1.f, 1.f, 3.f };

			// When
			v41 -= v42;

			// Then
			for (auto i = 0; i < 4; ++i) {
				EXPECT_FLOAT_EQ(v41[i], expectedResult[i]);
			}
		}

		// Story:
		//		[Who] As a programmer, I need to use the multiplication operator on vectors
		//		[What] So that I can multiply the current vector by a given scalar value
		//		[Value] So that I can update the current vector's values and use it for further calculations
		TEST(VectorTest, TestMultiplicationOperator)
		{
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			float scalar = 2.f;

			// When
			Vector<float, 4> result = v41 * scalar;

			// Then
			EXPECT_FLOAT_EQ(result[0], 2);
			EXPECT_FLOAT_EQ(result[1], 4);
			EXPECT_FLOAT_EQ(result[2], 6);
			EXPECT_FLOAT_EQ(result[3], 8);
		}

		// Story:
		//		[Who] As a programmer, I need to use the multiplication-assignment operator on vectors
		//		[What] So that I can multiply the current vector by a given scalar value
		//		[Value] So that I can update the current vector's values and use it for further calculations
		TEST(VectorTest, TestMultiplicationAssignmentOperator)
		{
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			float scalar = 2.f;

			// When
			v41 *= scalar;

			// Then
			EXPECT_FLOAT_EQ(v41[0], 2);
			EXPECT_FLOAT_EQ(v41[1], 4);
			EXPECT_FLOAT_EQ(v41[2], 6);
			EXPECT_FLOAT_EQ(v41[3], 8);
		}

		// VectorTransform.hpp tests

		TEST(VectorTransformTest, TestDotProduct) {
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			Vector<float, 4> v42(std::array{ 5.f, 6.f, 7.f, 8.f });
			auto expectedDotProduct = 70.f;

			// When
			auto result = VL::dot(v41, v42);

			// Then
			EXPECT_FLOAT_EQ(result, expectedDotProduct);
		}

		// Story:
		//		[Who] As a computer graphics programmer.
		//		[What] I need to calculate the cross product of two 3-dimensional vectors.
		//		[Value] So that I can determine the normal vector of a triangle in 3D space.
		TEST(VectorTransformTest, TestCrossProduct)
		{
			// Given
			Vector<float, 3> v1(std::array{ 1.f, 2.f, 3.f });
			Vector<float, 3> v2(std::array{ 4.f, 5.f, 6.f });

			// When
			Vector<float, 3> expectedResult(std::array{ -3.f, 6.f, -3.f });
			auto result = VL::cross(v1, v2);

			// Then
			for (auto i = 0; i < 3; ++i)
			{
				EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
			}

		}

		// Story:
		//		[Who] As a 3D graphics programmer.
		//		[What] I want to normalize a Vector.
		//		[Value] So that I can ensure that the Vector has a length of 1 and can be used for 
		TEST(VectorTransformTest, TestLength) {
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			auto expectedLength = std::sqrt(30);

			// When
			auto result = VL::length(v41);

			// Then
			EXPECT_FLOAT_EQ(result, expectedLength);
		}

		// Story:
		//		[Who] As a 3D graphics programmer.
		//		[What] I want to normalize a Vector.
		//		[Value] So that I can ensure that the Vector has a length of 1 and can be used for various calculations.
		TEST(VectorTransformTest, TestNormalize)
		{
			// Given
			Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
			auto expectedLength = std::sqrt(30);

			// When
			auto result = VL::normalize(v41);

			// Then
			for (auto i = 0; i < 4; ++i) {
				EXPECT_FLOAT_EQ(result[i], v41[i] / expectedLength);
			}
		}
	}

	namespace MathUtilsTest
	{
		TEST(MatuUtilsTest, TestDegreesToRadians)
		{
			// Given
			const double degrees = 45.0;
			const double expectedResult = 3.14159265358979323846 / 4.0;

			// When
			const double result = VL::radians(degrees);

			// Then
			EXPECT_DOUBLE_EQ(result, expectedResult);
		}
	}
}