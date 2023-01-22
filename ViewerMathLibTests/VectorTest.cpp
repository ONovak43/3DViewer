#include "pch.h"
#include "../ViewerMathLib/Vector.cpp"

namespace
{
    using VML::Vector;

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
    // [Who] As a user of the Vector class,
    // [What] I need to test the [] operator
    // [Value] So that I can ensure it returns a reference to the correct element in the vector
    TEST(VectorTest, TestBracketOperator) {
        // Given
        Vector<int, 4> v4(std::array { 1, 2, 3, 4 });

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
        EXPECT_EQ(v41[0], 6);
        EXPECT_EQ(v41[1], 8);
        EXPECT_EQ(v41[2], 10);
        EXPECT_EQ(v41[3], 12);
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
    // [Who] As a programmer, I need to use the multiplication operator on vectors
    // [What] So that I can multiply the current vector by a given scalar value
    // [Value] So that I can update the current vector's values and use it for further calculations
    TEST(VectorTest, TestMultiplicationOperator)
    {
        // Given
        Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
        float scalar = 2.f;

        // When
        Vector<float, 4> result = v41 * scalar;

        // Then
        EXPECT_EQ(result[0], 2);
        EXPECT_EQ(result[1], 4);
        EXPECT_EQ(result[2], 6);
        EXPECT_EQ(result[3], 8);
    }

    // Story:
    // [Who] As a programmer, I need to use the multiplication-assignment operator on vectors
    // [What] So that I can multiply the current vector by a given scalar value
    // [Value] So that I can update the current vector's values and use it for further calculations
    TEST(VectorTest, TestMultiplicationAssignmentOperator)
    {
        // Given
        Vector<float, 4> v41(std::array{ 1.f, 2.f, 3.f, 4.f });
        float scalar = 2.f;

        // When
        v41 *= scalar;

        // Then
        EXPECT_EQ(v41[0], 2);
        EXPECT_EQ(v41[1], 4);
        EXPECT_EQ(v41[2], 6);
        EXPECT_EQ(v41[3], 8);
    }
}