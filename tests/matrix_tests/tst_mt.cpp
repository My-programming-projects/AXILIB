#include "include/Axi.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

template<typename Iterator1, typename Iterator2>
bool compare(Iterator1 first_1, Iterator1 last_1, Iterator2 first_2)
{
    for(auto it = first_1; it != last_1; ++it, ++first_2)
    {
        if(*it != *first_2)
        {
            return false;
        }
    }

    return true;
}

TEST(matrixTests, mt)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(matrixTests, construct_1)
{
    const std::size_t rows = 4;
    const std::size_t cols = 5;

    axilib::fmatrix mat(rows, cols);

    std::vector<float> vec(20 ,0);

    bool cond = compare(vec.begin(), vec.end(), mat.begin());

    EXPECT_EQ(mat.rows(), rows);
    EXPECT_EQ(mat.cols(), cols);
    EXPECT_EQ(cond, true);
}

TEST(matrixTests, construct_2)
{
    axilib::fmatrix mat{2.0, 3.2, 4.1, 6.3, 7.1};

    std::vector<float> vec{2.0, 3.2, 4.1, 6.3, 7.1};

    bool cond = compare(vec.begin(), vec.end(), mat.begin());

    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 5);
    EXPECT_EQ(cond, true);
}

TEST(matrixTests, construct_3)
{
    axilib::imatrix mat
    {
        {4,5,6},
        {1,2,3},
        {8,9,0},
        {3,8,7}
    };

    std::vector<int> vec{4,1,8,3,5,2,9,8,6,3,0,7};

    bool cond = compare(vec.begin(), vec.end(), mat.begin());

    EXPECT_EQ(mat.rows(), 4);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_EQ(cond, true);
}

TEST(matrixTests, construct_4)
{
    short val = 0;
    axilib::smatrix mat(2, 3, [&val]{ short v = val; val++; return v; });

    std::vector<short> vec{0,1,2,3,4,5};

    bool cond = compare(vec.begin(), vec.end(), mat.begin());

    EXPECT_EQ(cond, true);
}

TEST(matrixTests, construct_5)
{
    axilib::dmatrix mat("{5,6,3,1}{2,3,3,0}{8,9,7,6}");

    std::vector<double> vec{5,2,8,6,3,9,3,3,7,1,0,6};

    bool cond = compare(vec.begin(), vec.end(), mat.begin());

    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 4);
    EXPECT_TRUE(cond);
}

TEST(matrixTests, copy_construct)
{
    axilib::imatrix mat_1
    {
        {1,5,3},
        {6,4,3},
        {7,8,4}
    };

    axilib::imatrix mat_2(mat_1);

    EXPECT_EQ(mat_1, mat_2);
}

TEST(matrixTests, move_construct)
{
    axilib::dmatrix mat_1
    {
        {4.3, 5.6, 2.1},
        {9.8, 5.2, 3.4},
        {6.3, 7.9, 2.4}
    };

    axilib::dmatrix aux{mat_1};
    axilib::dmatrix mat_2(std::move(mat_1));

    EXPECT_EQ(mat_2, aux);
    EXPECT_TRUE(mat_1.is_empty());
}

TEST(matrixTests, copy_assign)
{
    axilib::dmatrix mat_1
    {
        {4.3, 5.6, 2.1},
        {9.8, 5.2, 3.4},
        {6.3, 7.9, 2.4}
    };

    axilib::dmatrix mat_2;
    mat_2 = mat_1;

    EXPECT_EQ(mat_2, mat_1);
}

TEST(matrixTests, move_assign)
{
    axilib::dmatrix mat_1
    {
        {4.3, 5.6, 2.1},
        {9.8, 5.2, 3.4},
        {6.3, 7.9, 2.4}
    };

    axilib::dmatrix aux = mat_1;
    axilib::dmatrix mat_2;

    mat_2 = std::move(mat_1);

    EXPECT_EQ(mat_2, aux);
    EXPECT_TRUE(mat_1.is_empty());
}
