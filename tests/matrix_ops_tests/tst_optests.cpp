
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
        { 5.3,  5,3,  9.0},
        {-0.6, -0.1, -9.0},
        { 5.0,  6,3,  8,9}
    };

    EXPECT_EQ(result, expected);
}
