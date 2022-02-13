
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
    axilib::fmatrix rhs = matrix_4();

    axilib::fmatrix result = lhs ^ rhs;
    lhs^= rhs;

    axilib::fmatrix expected
    {
        {-7.0,  6.2, 6.0},
        {-7.6, -8.8, -8.4}
    };

    EXPECT_EQ(result, expected);
}
