#include "include/Axi.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(matrixTests, ts)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(matrixTests, iterator)
{
    axilib::imatrix mat
    {
        {1,2,3},
        {5,4,2},
        {8,7,5}
    };

    std::vector<int> vec{1,5,8,2,4,7,3,2,5};
    std::vector<int> aux;

    std::copy(mat.begin(), mat.end(), std::back_inserter(aux));

    EXPECT_EQ(aux, vec);
}

TEST(matrixTests, row_iterator)
{
    axilib::fmatrix mat
    {
        {4,  33, 21, 55},
        {77, 6,  4,  42},
        {29, 30, 5,  16}
    };

    std::vector<float> vec{77,6,4,42};
    std::vector<float> aux;

    std::copy(mat.begin_row(1), mat.end_row(1), std::back_inserter(aux));

    EXPECT_EQ(aux, vec);
}

TEST(matrixTests, col_iterator)
{
    axilib::dmatrix mat
    {
        {3,4,5,6},
        {0,9,7,0},
        {2,3,4,5}
    };

    std::vector<double> vec{5,7,4};
    std::vector<double> aux;

    std::copy(mat.begin_col(2), mat.end_col(2), std::back_inserter(aux));

    EXPECT_EQ(aux, vec);
}

TEST(matrixTests, diag_iterator)
{
    axilib::imatrix mat_1
    {
        {2,0,0,0},
        {0,3,0,0},
        {0,0,4,0}
    };

    std::vector<int> vec_1{2,3,4};
    std::vector<int> aux_1;

    std::copy(mat_1.begin_diag(), mat_1.end_diag(), std::back_inserter(aux_1));

    axilib::imatrix mat_2
    {
        {7,0,0},
        {0,6,0},
        {0,0,5},
        {0,0,0}
    };

    std::vector<int> vec_2{7,6,5};
    std::vector<int> aux_2;

    std::copy(mat_2.begin_diag(), mat_2.end_diag(), std::back_inserter(aux_2));


    EXPECT_EQ(aux_1, vec_1);
    EXPECT_EQ(aux_2, vec_2);
}
