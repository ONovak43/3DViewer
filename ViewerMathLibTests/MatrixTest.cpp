#include "pch.h"
#include "../ViewerMathLib/Matrix.cpp"

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
                EXPECT_FLOAT_EQ(m4(i, j), mdata[i][j]);
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
        EXPECT_EQ(element, 12);

        // When
        m1(1, 2) = 22;

        // Then
        EXPECT_EQ(m1(1, 2), 22);
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
        EXPECT_EQ(element, mdata[4]);

        // When
        m1[4] = 10;

        // Then
        EXPECT_EQ(m1[4], 10);
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
        EXPECT_EQ(m1[3], 10);
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

        std::array<int, 16> expectedResult  = { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17 };

        // When
        auto result = m1 + m2;

        // Then
        for (auto i = 0; i < 16; ++i) {
            EXPECT_EQ(result[i], expectedResult[i]);
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
            EXPECT_EQ(result[i], expectedResult[i]);
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
        for (std::size_t i = 0; i < 16; ++i)
        {
            auto expectedResult = mdata[i] * scalar;
            EXPECT_EQ(result[i], expectedResult);
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
        for (std::size_t i = 0; i < 16; ++i)
        {
            auto expectedResult = mdata[i] * scalar;
            EXPECT_EQ(m1[i], expectedResult);
        }
    }

    // Story: 
    //      [Who] As a 3DViewer programmer, I need to compare two matrices. 
    //      [What] So I can check if they are equal or not.
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
    //      [What] So I can check if they are equal or not.
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
}