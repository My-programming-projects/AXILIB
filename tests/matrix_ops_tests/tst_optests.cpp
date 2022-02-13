
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "Helper.hpp"

using namespace testing;

TEST(matrixTests, opTests)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(matrix_ops_test, plus)
{
    axilib::dmatrix lhs = matrix_1();
    axilib::dmatrix rhs = matrix_2();

    axilib::dmatrix result = lhs + rhs;
    lhs += rhs;

    axilib::dmatrix expected
    {
        { 5.3,  5.3,   2.2},
        {-0.6, -0.1, -10.8},
        { 5.0,  6.3,   8.9}
    };

    EXPECT_EQ(result, expected);
    EXPECT_EQ(lhs, expected);
}

TEST(matrix_ops_test, minus)
{
    axilib::dmatrix lhs = matrix_1();
    axilib::dmatrix rhs = matrix_2();

    axilib::dmatrix result = lhs - rhs;
    lhs-= rhs;

    axilib::dmatrix expected
    {
        {-0.7,  -8.1, 9.0},
        {13.6,  12.9, 9.0},
        {-3.8, -10.5, 4.5}
    };

    EXPECT_EQ(result, expected);
    EXPECT_EQ(lhs, expected);
}

TEST(matrix_ops_test, multiplies_1)
{
    axilib::fmatrix lhs = matrix_3();
    axilib::fmatrix rhs = matrix_4();

    axilib::fmatrix result = lhs * rhs;

    axilib::fmatrix expected
    {
        { 1.0, 16.0},
        {-1.0,  9.0}
    };

    EXPECT_EQ(result, expected);
}

TEST(matrix_ops_test, multiplies_2)
{
    axilib::fmatrix lhs = matrix_3();
    axilib::fmatrix rhs = matrix_5();

    axilib::fmatrix result = lhs ^ rhs;
    lhs^= rhs;

    axilib::fmatrix expected
    {
        {-7.0,  6.2, 6.0},
        {-7.6, -8.8, -8.4}
    };

    EXPECT_EQ(result, expected);
}

TEST(matrix_ops_test, divides)
{
    axilib::fmatrix lhs = matrix_3();
    axilib::fmatrix rhs = matrix_5();

    axilib::fmatrix result = lhs / rhs;
    lhs/= rhs;

    axilib::fmatrix expected
    {
        {-0.571428,  0.161290,   1.5},
        {-0.131578, -0.454545,  -1.904761}
    };

    EXPECT_EQ(result, expected);
    EXPECT_EQ(lhs, expected);
}

TEST(matrix_ops_test, scalar_plus)
{
    axilib::fmatrix lhs = matrix_3();
    float scalar = 3.2;

    axilib::fmatrix result = lhs + scalar;
    lhs+= scalar;

    axilib::fmatrix expected
    {
        {5.2, 4.2, 6.2},
        {2.2, 5.2, 7.2}
    };

    EXPECT_EQ(result, expected);
    EXPECT_EQ(lhs, expected);
}

TEST(matrix_ops_test, scalar_minus)
{
    axilib::fmatrix lhs = matrix_5();
    float scalar = 4.3;

    axilib::fmatrix result = lhs - scalar;
    lhs-= scalar;

    axilib::fmatrix expected
    {
        {-7.8,  1.9, -2.3},
        { 3.3, -8.7, -6.4}
    };

    EXPECT_EQ(result, expected);
    EXPECT_EQ(lhs, expected);
}

TEST(matrix_ops_test, scalar_multiplies)
{
    axilib::fmatrix lhs = matrix_5();
    float scalar = 6.7;

    axilib::fmatrix result = lhs * scalar;
    lhs*= scalar;

    axilib::fmatrix expected
    {
        {-23.45,  41.54,  13.4 },
        { 50.92, -29.48, -14.07}
    };

    EXPECT_EQ(result, expected);
    EXPECT_EQ(lhs, expected);
}

TEST(matrix_ops_test, scalar_divide)
{
    axilib::dmatrix lhs = matrix_2();
    double scalar = 3.3;

    axilib::dmatrix result = lhs / scalar;
    lhs/= scalar;

    axilib::dmatrix expected
    {
        { 0.909090,  2.030303, -1.030303},
        {-2.151515, -1.969696, -3.0},
        { 1.333333,  2.545454,  0.666666}
    };

    EXPECT_EQ(result, expected);
    EXPECT_EQ(lhs, expected);
}
