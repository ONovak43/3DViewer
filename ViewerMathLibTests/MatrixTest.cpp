#include "pch.h"
#include "../ViewerMathLib/Matrix.hpp"
#include "../ViewerMathLib/MatrixTransform.hpp"

namespace
{
	using VML::Matrix;

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

	// Story:-
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
	// [Who] As a 3DViewer programmer.
	// [What] I want to access elements in the matrix using the parenthesis operator.
	// [Value] So that I can modify and retrieve values in the matrix using row and column indices.
	TEST(MatrixTest, TestParenthesisOperator) {

		// Given
		constexpr std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);

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
	// [Who] As a 3DViewer programmer.
	// [What] I want to access elements in the matrix using the subscript operator.
	// [Value] So that I can modify and retrieve values in the matrix.
	TEST(MatrixTest, TestSubscriptOperator)
	{
		// Given
		constexpr std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);

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
	// [Who] As a 3DViewer programmer.
	// [What] I want to access elements in the matrix using the subscript operator.
	// [Value] So that I can modify and retrieve values in the matrix.
	TEST(MatrixTest, TestSubscriptOperator2x2)
	{
		// Given
		constexpr std::array<int, 4> mdata = { 1, 2, 3, 4 };
		Matrix<int, 2> m1(mdata);

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
	// [Who] As a 3DViewer programmer.
	// [What] I want to convert the matrix to an array.
	// [Value] So that I can retrieve values in the matrix.
	TEST(MatrixTest, TestToArray)
	{
		// Given
		constexpr std::array<std::array<int, 3>, 3> mdata = { {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} };
		Matrix<int, 3> m1(mdata);

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
		std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);

		mdata = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
		Matrix<int, 4> m2(mdata);

		std::array<int, 16> expectedResult = { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 };

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
		std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);

		mdata = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
		Matrix<int, 4> m2(mdata);

		std::array<int, 16> expectedResult = { -15, -13, -11, -9, -7, -5, -3, -1, 1, 3, 5, 7, 9, 11, 13, 15 };

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
		std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);
		Matrix<int, 4> m2(mdata);

		mdata = { 90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600 };
		Matrix<int, 4> expected(mdata);

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
		std::array<int, 9> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		Matrix<int, 3> m1(mdata);
		Matrix<int, 3> m2(mdata);

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
		constexpr std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);
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
	// [Who] As a 3DViewer programmer.
	// [What] I want to multiply a matrix by a scalar.
	// [Value] So that I can scale an object.
	TEST(MatrixTest, MultiplyAssignmentOperatorWithScalar)
	{
		// Given 
		constexpr std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);
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
		std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);
		Matrix<int, 4> m2(mdata);

		mdata[15] = 17;
		Matrix<int, 4> m3(mdata);

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
		std::array<int, 16> mdata = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		Matrix<int, 4> m1(mdata);
		Matrix<int, 4> m2(mdata);

		mdata[15] = 17;
		Matrix<int, 4> m3(mdata);

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
	TEST(MatrixTraformTest, TestOrthoMatrix) {
		// Given
		constexpr auto left = -1.0f;
		constexpr auto right = 1.0f;
		constexpr auto bottom = -1.0f;
		constexpr auto top = 1.0f;
		constexpr auto zNear = -1.0f;
		constexpr auto zFar = 1.0f;

		// When
		auto orthoMatrix = VML::ortho(left, right, bottom, top, zNear, zFar);

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
	TEST(MatrixTraformTest, TestPerspectiveMatrix)
	{
		// Given
		constexpr auto fov = 90.f;
		constexpr auto aspect = 16.f / 9.f;
		constexpr auto zNear = 0.1f;
		constexpr auto zFar = 100.0f;

		// When
		auto perspectiveMatrix = VML::perspective<float>(fov, aspect, zNear, zFar);

		// Then
		auto f = 1.f / tan(fov / 2.f);

		EXPECT_FLOAT_EQ(f / aspect, perspectiveMatrix(0, 0));
		EXPECT_FLOAT_EQ(f, perspectiveMatrix(1, 1));
		EXPECT_FLOAT_EQ(-(zFar + zNear) / (zNear - zFar), perspectiveMatrix(2, 2));
		EXPECT_FLOAT_EQ((2.f * zNear * zFar) / (zNear - zFar), perspectiveMatrix(2, 3));
		EXPECT_FLOAT_EQ(1.f, perspectiveMatrix(3, 2));
	}

	// Story:
	//      [Who] As a 3DViewer programmer.
	//      [What]  I need to calculate the determinant of a 4x4 matrix.
	//      [Value] So that I can calculate the scaling factor and inverse of a matrix.
	TEST(MatrixTraformTest, DeterminantTestZeroDeterminant4x4) {
		// Given
		std::array<float, 16> mdata = { 1, 2, 3, 4, 1, 2, 3, 4, 0, 0, 3, 4, 0, 0, 0, 4 };
		Matrix<float, 4> m1(mdata);

		// When
		constexpr auto expectedResult = 0.f;
		auto result = VML::determinant(m1);

		// Then
		EXPECT_FLOAT_EQ(expectedResult, result);
	}

	// Story:
	//      [Who] As a 3DViewer programmer.
	//      [What]  I need to calculate the determinant of a 4x4 matrix.
	//      [Value] So that I can calculate the scaling factor and inverse of a matrix.
	TEST(MatrixDeterminantTest, DeterminantTestPositiveDeterminant4x4) {
		// Given
		Matrix<float, 4> m1(1.f);

		// When
		constexpr auto expectedResult = 1.f;
		auto result = VML::determinant(m1);

		// Then
		EXPECT_FLOAT_EQ(expectedResult, result);
	}

	// Story:
	//      [Who] As a 3DViewer programmer.
	//      [What] I need to calculate the determinant of a 4x4 matrix.
	//      [Value] So that I can calculate the scaling factor and inverse of a matrix.
	TEST(MatrixDeterminantTest, DeterminantTestNegativeDeterminant4x4) {
		// Given
		Matrix<float, 4> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 2.f, 1.f, 0.f, 4.f, 1.f, 0.f, 4.f, 1.f, 2.f, 0.f, 2.f, 1.f });

		// When
		constexpr auto expectedResult = -7.f;
		auto result = VML::determinant(m1);

		EXPECT_FLOAT_EQ(expectedResult, result);
	}

	// Story:
	//    [Who] As a 3DViewer programmer.
	//    [What] I need to calculate the determinant of a 3x3 matrix.
	//    [Value] So that I can calculate the scaling factor and inverse of a matrix.
	TEST(MatrixTraformTest, DeterminantTestZeroDeterminant3x3)
	{
		// Given
		std::array<float, 9> mdata = { 1, 2, 3, 1, 2, 3, 0, 0, 3 };
		Matrix<float, 3> m1(mdata);

		// When
		constexpr auto expectedResult = 0.f;
		auto result = VML::determinant(m1);

		// Then
		EXPECT_FLOAT_EQ(expectedResult, result);
	}


	// Story:
	//    [Who] As a 3DViewer programmer.
	//    [What] I need to calculate the determinant of a 3x3 matrix.
	//    [Value] So that I can calculate the scaling factor and inverse of a matrix.
	TEST(MatrixTraformTest, DeterminantTestPositiveDeterminant3x3)
	{
		// Given
		Matrix<float, 3> m1(1.f);

		// When
		constexpr auto expectedResult = 1.f;
		auto result = VML::determinant(m1);

		// Then
		EXPECT_FLOAT_EQ(expectedResult, result);
	}

	// Story:
	//    [Who] As a 3DViewer programmer.
	//    [What] I need to calculate the determinant of a 3x3 matrix.
	//    [Value] So that I can calculate the scaling factor and inverse of a matrix.
	TEST(MatrixTraformTest, DeterminantTestNegativeDeterminant3x3)
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
		auto result = VML::determinant(m1);

		// Then
		EXPECT_FLOAT_EQ(expectedResult, result);
	}

	// Story:
	//      [Who] As a graphics programmer.
	//      [What] I need to find the transpose of a matrix.
	//      [Value] So that I can quickly change the orientation of the objects in my 3D viewer.
	TEST(MatrixTransformTest, TransposeTest)
	{
		// Given
		Matrix<float, 3> m1(std::array{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f });

		// When
		Matrix<float, 3> result = VML::transpose(m1);

		// Then
		Matrix<float, 3> expectedResult(std::array{ 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f });
		EXPECT_EQ(expectedResult, result);
	}

	// Story:
	//		[Who] As a 2D game programmer.
	//		[What] I need to calculate the inverse of a 2x2 matrix.
	//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
	TEST(MatrixTransformTest, InverseTestSingular2x2)
	{
		// Given
		Matrix<float, 2> m1(std::array{ 1.f, 2.f, 2.f, 4.f });

		// Then
		EXPECT_THROW(VML::inverse(m1), std::runtime_error);

	}

	// Story:
	//		[Who] As a 2D game programmer.
	//		[What] I need to calculate the inverse of a 2x2 matrix.
	//		[Value] So that I can apply transformations to the matrix and have an option to undo them.
	TEST(MatrixTransformTest, InverseTestPositiveDeterminant2x2)
	{
		// Given
		Matrix<float, 2> m1(std::array{ 3.f, 1.f, 2.f, 5.f });

		// When
		std::array expectedResult{ 5.f / 13.f, -1.f / 13, -2.f / 13.f, 3.f / 13.f };
		auto result = VML::inverse(m1);

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
	TEST(MatrixTransformTest, InverseTestNegativeDeterminant2x2)
	{
		// Given
		Matrix<float, 2> m1(std::array{ 2.f, 1.f, 2.f, 2.f });

		// When
		std::array expectedResult{ 1.f, -0.5f, -1.f, 1.f };
		auto result = VML::inverse(m1);

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
	TEST(MatrixTransformTest, InverseTestSingular3x3)
	{

		// Given
		Matrix<float, 3> m1(std::array{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f });

		// Then
		EXPECT_THROW(VML::inverse(m1), std::runtime_error);
	}

	// Story:
	//      [Who] As a 3DViewer programmer.
	//      [What] I need to calculate the inverse of a 3x3 matrix.
	//      [Value] So that I can apply transformations to the matrix and have an option to undo them.
	TEST(MatrixTransformTest, InverseTestPositiveDeterminant3x3)
	{

		// Given
		Matrix<float, 3> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 1.f, 0.f, 1.f, 0.f, 4.f });

		// When
		std::array expectedResult{ 4.f, 0.f, -3.f, -8.f, 1.f, 6.f, -1.f, 0.f, 1.f };
		auto result = VML::inverse(m1);

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
	TEST(MatrixTransformTest, InverseTestNegativeDeterminant3x3)
	{
		// Given
		Matrix<float, 3> m1(std::array{ 1.f, 0.f, 3.f, 1.f, 0.f, 4.f, 2.f, 1.f, 0.f });

		// When
		std::array expectedResult{ 4.f, -3.f, 0.f, -8.f, 6.f, 1.f, -1.f, 1.f, 0.f };
		auto result = VML::inverse(m1);

		// Then
		for (auto i = 0; i < 9; ++i)
		{
			EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
		}
	}

	// Story:
	// [Who] As a 3DViewer programmer.
	// [What] I need to calculate the inverse of a 4x4 matrix.
	// [Value] So that I can apply transformations to the matrix and have an option to undo them.
	TEST(MatrixTransformTest, InverseTestSingular4x4)
	{
		// Given
		Matrix<float, 4> m1(std::array{ 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f });

		// Then
		EXPECT_THROW(VML::inverse(m1), std::runtime_error);
	}

	// Story:
	// [Who] As a 3DViewer programmer.
	// [What] I need to calculate the inverse of a 4x4 matrix.
	// [Value] So that I can apply transformations to the matrix and have an option to undo them.
	TEST(MatrixTransformTest, InverseTestPositiveDeterminant4x4)
	{
		// Given
		Matrix<float, 4> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 2.f, 1.f, 0.f, 4.f, 1.f, 0.f, 4.f, 1.f, 2.f, 0.f, 2.f, 1.f });

		// When
		std::array expectedResult{ -2.f/7.f, 0.f, -1.f/7.f, 5.f/7.f, -20.f/7.f, 1.f, 18.f/7.f, -6.f/7.f, -1.f/7.f, 0.f, 3.f/7.f, -1.f/7.f, 6.f/7.f, 0.f, -4.f/7.f, -1.f/7.f };
		auto result = VML::inverse(m1);

		// Then
		for (auto i = 0; i < 16; ++i)
		{
			EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
		}
	}

	// Story:
	// [Who] As a 3DViewer programmer.
	// [What] I need to calculate the inverse of a 4x4 matrix.
	// [Value] So that I can apply transformations to the matrix and have an option to undo them.
	TEST(MatrixTransformTest, InverseTestNegativeDeterminant4x4)
	{
		// Given
		Matrix<float, 4> m1(std::array{ 1.f, 0.f, 3.f, 2.f, 2.f, 1.f, 0.f, 4.f, 1.f, 0.f, 4.f, 1.f, 2.f, 0.f, 2.f, 1.f });

		// When
		std::array expectedResult{ -2.f / 7.f, 0.f, -1.f / 7.f, 5.f / 7.f, -20.f / 7.f, 1.f, 18.f / 7.f, -6.f / 7.f, -1.f / 7.f, 0.f, 3.f / 7.f, -1.f / 7.f, 6.f / 7.f, 0.f, -4.f / 7.f, -1.f / 7.f };
		auto result = VML::inverse(m1);

		// Then
		for (auto i = 0; i < 16; ++i)
		{
			EXPECT_FLOAT_EQ(expectedResult[i], result[i]);
		}
	}

}