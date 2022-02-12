#include "Helper.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;


TEST(matrixTests, mt)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(matrixTests, clear)
{
    axilib::dmatrix mat = matrix_1();
    mat.clear();

    bool equal = mat.size() == axilib::Size{};

    EXPECT_TRUE(equal);
}

TEST(matrix_filling_test, fill_zeros)
{
    axilib::dmatrix mat = matrix_1();
    mat.fill_zeros();

    axilib::dmatrix expected(4, 3);

    EXPECT_EQ(mat, expected);
}

TEST(matrix_filling_test, fill_ones)
{
    axilib::dmatrix mat = matrix_1();
    mat.fill_ones();

    axilib::dmatrix expected
    {
        {1,1,1},
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_filling_test, fill_eye)
{
    axilib::dmatrix mat = matrix_1();
    mat.fill_eye();
    /*{
        {1,1,2},
        {6,2,6},
        {3,4,5}
    };*/

    axilib::dmatrix expected
    {
        {1,0,0},
        {0,1,0},
        {0,0,1},
        {0,0,0}
    };



    EXPECT_EQ(mat, expected);
}

TEST(matrix_imbue_test, imbue_all)
{
    //axilib::dmatrix mat(4, 5);

    axilib::dmatrix mat = matrix_1();
    mat.imbue([]{ return 23.0; });

    std::array<double, 12> expected;
    std::fill(expected.begin(), expected.end(), 23.0);

    bool equal = compare(expected.begin(), expected.end(), mat.begin());

    EXPECT_TRUE(equal);
}

TEST(matrix_imbue_test, imbue_row)
{
    axilib::dmatrix mat = matrix_1();
    mat.imbue_row([]{ return 11.6; }, 1);

    std::array<double, 3> expected;
    std::fill(expected.begin(), expected.end(), 11.6);
    bool equal = compare(expected.begin(), expected.end(), mat.begin_row(1));

    EXPECT_TRUE(equal);
}

TEST(matrix_imbue_test, imbue_col)
{
    axilib::dmatrix mat = matrix_1();
    mat.imbue_col([]{ return 5.9; }, 0);

    std::array<double, 4> expected;
    std::fill(expected.begin(), expected.end(), 5.9);
    bool equal = compare(expected.begin(), expected.end(), mat.begin_col(0));

    EXPECT_TRUE(equal);
}

TEST(matrix_imbue_test, imbue_diag)
{
    axilib::dmatrix mat = matrix_1();
    mat.imbue_diag([]{ return 4.3; });

    std::array<double, 3> expected;
    std::fill(expected.begin(), expected.end(), 4.3);

    bool equal = compare(expected.begin(), expected.end(), mat.begin_diag());

    EXPECT_TRUE(equal);
}

TEST(matrix_counting_elems_test, zeros)
{
    axilib::dmatrix mat = matrix_2();

    std::size_t zeros = mat.zeros();
    std::size_t row_1st_zeros = mat.zeros_in_row(0);
    std::size_t row_2nd_zeros = mat.zeros_in_row(1);
    std::size_t col_3rd_zeros = mat.zeros_in_col(2);
    std::size_t diag_zeros = mat.zeros_in_diag();

    EXPECT_EQ(zeros, 3);
    EXPECT_EQ(row_1st_zeros, 2);
    EXPECT_EQ(row_2nd_zeros, 0);
    EXPECT_EQ(col_3rd_zeros, 1);
    EXPECT_EQ(diag_zeros, 1);
}

TEST(matrix_accumulate_test, accumulate_all)
{
    axilib::dmatrix mat = matrix_3();
    double total = mat.accumulate();
    double expected = 50.3;

    EXPECT_DOUBLE_EQ(total, expected);
}

TEST(matrix_accumulate_test, accumulate_row)
{
    axilib::dmatrix mat = matrix_3();
    double total = mat.accumulate_row(1);
    double expected = 19.4;

    EXPECT_DOUBLE_EQ(total, expected);
}

TEST(matrix_accumulate_test, accumulate_col)
{
    axilib::dmatrix mat = matrix_3();
    double total = mat.accumulate_col(0);
    double expected = 9.8;

    EXPECT_DOUBLE_EQ(total, expected);
}

TEST(matrix_accumulate_test, accumulate_diag)
{
    axilib::dmatrix mat = matrix_3();
    double total = mat.accumulate_diag();
    double expected = 18.4;

    EXPECT_DOUBLE_EQ(total, expected);
}

TEST(matrix_sort_test, row_ascend_sort)
{
    axilib::dmatrix mat = matrix_1();
    mat.sort_row<axilib::Ascend>(3);

    std::array<double, 3> expected{-0.1, 4.1, 4.4};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_row(3));

    EXPECT_TRUE(equal);
}

TEST(matrix_sort_test, row_descend_sort)
{
    axilib::dmatrix mat = matrix_1();
    mat.sort_row<axilib::Descend>(0);

    std::array<double, 4> expected{7.6, 0.4, -7.8};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_row(0));

    EXPECT_TRUE(equal);
}

TEST(matrix_sort_test, col_ascend_sort)
{
    axilib::dmatrix mat = matrix_1();
    mat.sort_col<axilib::Ascend>(2);

    std::array<double, 4> expected{-4.3, 0.4, 4.4, 9.5};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_col(2));

    EXPECT_TRUE(equal);
}

TEST(matrix_sort_test, col_descend_sort)
{
    axilib::dmatrix mat = matrix_1();
    mat.sort_col<axilib::Descend>(0);

    std::array<double, 4> expected{7.6, 4.1, 1.7, -8.8};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_col(0));

    EXPECT_TRUE(equal);
}

TEST(matrix_sort_test, diag_ascend_sort)
{
    axilib::dmatrix mat = matrix_1();
    mat.sort_diag<axilib::Ascend>();

    std::array<double, 3> expected{4.7, 7.6, 9.5};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_diag());

    EXPECT_TRUE(equal);
}

TEST(matrix_sort_test, diag_descend_sort)
{
    axilib::dmatrix mat = matrix_1();
    mat.sort_diag<axilib::Descend>();

    std::array<double, 3> expected{9.5, 7.6, 4.7};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_diag());

    EXPECT_TRUE(equal);
}

TEST(matrix_rotate_test, rotate_right)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate<axilib::Right>(1);

    axilib::dmatrix expected
    {
        { 1.7,  4.7, -4.3},
        {-8.8,  3.2,  9.5},
        { 4.1, -0.1,  4.4},
        {-7.8,  0.4,  7.6}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_rotate_test, rotate_left)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate<axilib::Left>(1);

    axilib::dmatrix expected
    {
        { 4.4,  4.1, -0.1},
        { 7.6, -7.8,  0.4},
        { 1.7,  4.7, -4.3},
        {-8.8,  3.2,  9.5}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_rotate_test, row_rotate_right)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate_row<axilib::Right>(1, 1);

    std::array<double, 3> expected{-4.3, 1.7, 4.7};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_row(1));

    EXPECT_TRUE(equal);
}

TEST(matrix_rotate_test, row_rotate_left)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate_row<axilib::Left>(1, 1);

    std::array<double, 3> expected{4.7, -4.3, 1.7};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_row(1));

    EXPECT_TRUE(equal);
}

TEST(matrix_rotate_test, col_rotate_right)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate_col<axilib::Right>(0, 1);

    std::array<double, 4> expected{4.1, 7.6, 1.7, -8.8};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_col(0));

    EXPECT_TRUE(equal);
}

TEST(matrix_rotate_test, col_rotate_left)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate_col<axilib::Left>(2, 1);

    std::array<double, 4> expected{-4.3, 9.5, 4.4, 0.4};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_col(2));

    EXPECT_TRUE(equal);
}

TEST(matrix_rotate_test, diag_rotate_right)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate_diag<axilib::Right>(1);

    std::array<double, 3> expected{9.5, 7.6, 4.7};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_diag());

    EXPECT_TRUE(equal);
}

TEST(matrix_rotate_test, diag_rotate_left)
{
    axilib::dmatrix mat = matrix_1();
    mat.rotate_diag<axilib::Left>(1);

    std::array<double, 3> expected{4.7, 9.5, 7.6};
    bool equal = compare(expected.begin(), expected.end(), mat.begin_diag());

    EXPECT_TRUE(equal);
}

TEST(matrix_bool_funcs_test, is_empty)
{
    axilib::dmatrix empty;
    axilib::dmatrix not_empty = matrix_1();

    EXPECT_TRUE(empty.is_empty());
    EXPECT_FALSE(not_empty.is_empty());
}

TEST(matrix_bool_funcs_test, is_square)
{
    axilib::dmatrix not_square = matrix_1();
    axilib::dmatrix square = matrix_3();

    EXPECT_FALSE(not_square.is_square());
    EXPECT_TRUE(square.is_square());
}

TEST(matrix_bool_funcs_test, is_diagonal)
{
    axilib::dmatrix not_diagonal = matrix_1();
    axilib::dmatrix diagonal = get_diagonal_matrix();

    EXPECT_FALSE(not_diagonal.is_diagonal());
    EXPECT_TRUE(diagonal.is_diagonal());
}

TEST(matrix_bool_funcs_test, is_banded)
{
    axilib::fmatrix not_banded = not_banded_matrix();
    axilib::fmatrix banded = banded_matrix();

    EXPECT_FALSE(not_banded.is_banded());
    EXPECT_TRUE(banded.is_banded());
}

TEST(matrix_bool_funcs_test, is_triangular)
{
    axilib::fmatrix upper_triangular = upper_triangular_matrix();
    axilib::fmatrix lower_triangular = lower_triangular_matrix();

    EXPECT_FALSE(upper_triangular.is_triangular<axilib::Lower>());
    EXPECT_FALSE(lower_triangular.is_triangular<axilib::Upper>());
}

TEST(matrix_bool_funcs_test, is_sorted_ascend_row)
{
    axilib::dmatrix mat = matrix_4();

    EXPECT_FALSE(mat.is_sorted_row<axilib::Ascend>(1));

    mat.sort_row<axilib::Ascend>(1);

    EXPECT_TRUE(mat.is_sorted_row<axilib::Ascend>(1));
}

TEST(matrix_bool_funcs_test, is_sorted_descend_row)
{
    axilib::dmatrix mat = matrix_4();

    EXPECT_FALSE(mat.is_sorted_row<axilib::Descend>(1));

    mat.sort_row<axilib::Descend>(1);

    EXPECT_TRUE(mat.is_sorted_row<axilib::Descend>(1));
}

TEST(matrix_bool_funcs_test, is_sorted_ascend_col)
{
    axilib::dmatrix mat = matrix_4();

    EXPECT_FALSE(mat.is_sorted_col<axilib::Ascend>(0));

    mat.sort_col<axilib::Ascend>(0);

    EXPECT_TRUE(mat.is_sorted_col<axilib::Ascend>(0));
}

TEST(matrix_bool_funcs_test, is_sorted_descend_col)
{
    axilib::dmatrix mat = matrix_4();

    EXPECT_FALSE(mat.is_sorted_col<axilib::Descend>(0));

    mat.sort_col<axilib::Descend>(0);

    EXPECT_TRUE(mat.is_sorted_col<axilib::Descend>(0));
}

TEST(matrix_bool_funcs_test, is_sorted_ascend_diag)
{
    axilib::dmatrix mat = matrix_1();

    EXPECT_FALSE(mat.is_sorted_diag<axilib::Ascend>());

    mat.sort_diag<axilib::Ascend>();

    EXPECT_TRUE(mat.is_sorted_diag<axilib::Ascend>());
}

TEST(matrix_bool_funcs_test, is_sorted_descend_diag)
{
    axilib::dmatrix mat = matrix_1();

    EXPECT_FALSE(mat.is_sorted_diag<axilib::Descend>());

    mat.sort_diag<axilib::Descend>();

    EXPECT_TRUE(mat.is_sorted_diag<axilib::Descend>());
}

TEST(matrix_replacing_test, replace)
{
    axilib::imatrix mat = matrix_5();
    mat.replace(6, 0);

    axilib::imatrix expected
    {
         {-1,  3,  0},
         { 7, -6,  2},
         { 0,  0, -1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_replacing_test, replace_if)
{
    axilib::imatrix mat = matrix_5();
    mat.replace_if([](int val){ return val < 0; }, 1);

    axilib::imatrix expected
    {
         { 1,  3,  6},
         { 7,  1,  2},
         { 6,  0,  1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_replacing_test, replace_in_row)
{
    axilib::imatrix mat = matrix_5();
    int value = 6;
    mat.replace_in_row(0, value, -value);

    axilib::imatrix expected
    {
         {-1,  3, -6},
         { 7, -6,  2},
         { 6,  0, -1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_replacing_test, replace_in_row_if)
{
    axilib::imatrix mat = matrix_5();
    mat.replace_in_row_if(1, [](int val){ return val < 7; }, 10);

    axilib::imatrix expected
    {
         {-1,  3,  6},
         { 7, 10, 10},
         { 6,  0, -1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_replacing_test, replace_in_col)
{
    axilib::imatrix mat = matrix_5();
    mat.replace_in_col(1, 3, 0);

    axilib::imatrix expected
    {
         {-1,  0,  6},
         { 7, -6,  2},
         { 6,  0, -1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_replacing_test, replace_in_col_if)
{
    axilib::imatrix mat = matrix_5();
    mat.replace_in_col_if(2, [](int val){ return val != 2; }, 2);

    axilib::imatrix expected
    {
         {-1,  3,  2},
         { 7, -6,  2},
         { 6,  0,  2}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_replacing_test, replace_in_diag)
{
    axilib::imatrix mat = matrix_5();
    mat.replace_in_diag(-1, -20);

    axilib::imatrix expected
    {
         {-20,  3,   6},
         {  7, -6,   2},
         {  6,  0, -20}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_replacing_test, replace_in_diag_if)
{
    axilib::imatrix mat = matrix_5();
    mat.replace_in_diag_if([](int val){ return val < 0; }, 5);

    axilib::imatrix expected
    {
         {5, 3, 6},
         {7, 5, 2},
         {6, 0, 5}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, to_banded)
{
    axilib::dmatrix mat = matrix_1();
    mat.to_banded();

    axilib::dmatrix expected
    {
         {7.6, -7.8,  0.0},
         {1.7,  4.7, -4.3},
         {0.0,  3.2,  9.5}
    };

    bool equal = (mat.size() == axilib::Size{3, 3});

    EXPECT_TRUE(equal);
    EXPECT_TRUE(mat.is_banded());
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, to_upper_triangular)
{
    axilib::fmatrix mat = matrix_6();
    mat.to_triangular<axilib::Upper>();

    axilib::fmatrix expected
    {
         {7.6, -7.8,  0.4, -0.3},
         {0.0,  4.7, -4.3,  9.1},
         {0.0,  0.0,  9.5,  3.4},
         {0.0,  0.0,  0.0,  7.7},
    };

    bool equal = (mat.size() == axilib::Size{4, 4});

    EXPECT_TRUE(equal);
    EXPECT_TRUE(mat.is_triangular<axilib::Upper>());
    EXPECT_FALSE(mat.is_triangular<axilib::Lower>());
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, to_lower_triangular)
{
    axilib::fmatrix mat = matrix_6();
    mat.to_triangular<axilib::Lower>();

    axilib::fmatrix expected
    {
         { 7.6,  0.0, 0.0, 0.0},
         { 1.7,  4.7, 0.0, 0.0},
         {-8.8,  3.2, 9.5, 0.0},
         { 4.1, -0.1, 4.4, 7.7},
    };

    bool equal = (mat.size() == axilib::Size{4, 4});

    EXPECT_TRUE(equal);
    EXPECT_TRUE(mat.is_triangular<axilib::Lower>());
    EXPECT_FALSE(mat.is_triangular<axilib::Upper>());
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, resize)
{
    axilib::fmatrix mat = matrix_6();
    mat.resize(axilib::Size{2, 2});

    axilib::fmatrix expected_1
    {
         { 7.6, -7.8},
         { 1.7,  4.7}
    };

    bool equal_1 = (mat.size() == axilib::Size{2, 2});

    EXPECT_TRUE(equal_1);
    EXPECT_EQ(mat, expected_1);

    mat.resize(4, 5);

    axilib::fmatrix expected_2
    {
         {7.6, -7.8, 0.0, 0.0, 0.0},
         {1.7,  4.7, 0.0, 0.0, 0.0},
         {0.0,  0.0, 0.0, 0.0, 0.0},
         {0.0,  0.0, 0.0, 0.0, 0.0}
    };

    bool equal_2 = (mat.size() == axilib::Size{4, 5});

    EXPECT_TRUE(equal_2);
    EXPECT_EQ(mat, expected_2);
}

TEST(matrix_transformation_test, resize_rows)
{
    axilib::fmatrix mat = matrix_6();
    mat.resize_rows(2);

    axilib::fmatrix expected_1
    {
         {7.6, -7.8,  0.4, -0.3,  4.4},
         {1.7,  4.7, -4.3,  9.1, -2.5}
    };

    bool equal_1 = (mat.size() == axilib::Size{2, 5});

    EXPECT_TRUE(equal_1);
    EXPECT_EQ(mat, expected_1);

    mat.resize_rows(3);

    axilib::fmatrix expected_2
    {
         {7.6, -7.8,  0.4, -0.3,  4.4},
         {1.7,  4.7, -4.3,  9.1, -2.5},
         {0.0,  0.0,  0.0,  0.0,  0.0}
    };

    bool equal_2 = (mat.size() == axilib::Size{3, 5});

    EXPECT_TRUE(equal_2);
    EXPECT_EQ(mat, expected_2);
}

TEST(matrix_transformation_test, resize_cols)
{
    axilib::fmatrix mat = matrix_6();
    mat.resize_cols(2);

    axilib::fmatrix expected_1
    {
         { 7.6, -7.8},
         { 1.7,  4.7},
         {-8.8,  3.2},
         { 4.1, -0.1},
    };

    bool equal_1 = (mat.size() == axilib::Size{4, 2});

    EXPECT_TRUE(equal_1);
    EXPECT_EQ(mat, expected_1);

    mat.resize_cols(4);

    axilib::fmatrix expected_2
    {
         { 7.6, -7.8,  0.0,  0.0},
         { 1.7,  4.7,  0.0,  0.0},
         {-8.8,  3.2,  0.0,  0.0},
         { 4.1, -0.1,  0.0,  0.0},
    };

    bool equal_2 = (mat.size() == axilib::Size{4, 4});

    EXPECT_TRUE(equal_2);
    EXPECT_EQ(mat, expected_2);
}

TEST(matrix_transformation_test, insert_row_1)
{
    axilib::imatrix mat = matrix_5();
    mat.insert_row(1, 5);

    axilib::imatrix expected
    {
         {-1,  3,  6},
         { 5,  5,  5},
         { 7, -6,  2},
         { 6,  0, -1}
    };

    bool equal = (mat.size() == axilib::Size{4, 3});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, insert_row_2)
{
    axilib::imatrix mat = matrix_5();
    axilib::Rowvec<int> rowvec{7, 3, 1};
    mat.insert_row(2, rowvec);

    axilib::imatrix expected
    {
         {-1,  3,  6},
         { 7, -6,  2},
         { 7,  3,  1},
         { 6,  0, -1}
    };

    bool equal = (mat.size() == axilib::Size{4, 3});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, insert_rows)
{
    axilib::imatrix mat = matrix_5();

    axilib::imatrix other
    {
         {9,  6, -7},
         {7, -6,  2}
    };

    mat.insert_rows(1, other);

    axilib::imatrix expected
    {
         {-1,  3,  6},
         { 9,  6, -7},
         { 7, -6,  2},
         { 7, -6,  2},
         { 6,  0, -1}
    };

    bool equal = (mat.size() == axilib::Size{5, 3});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, insert_col_1)
{
    axilib::imatrix mat = matrix_5();
    mat.insert_col(2, 10);

    axilib::imatrix expected
    {
         {-1,  3, 10,  6},
         { 7, -6, 10,  2},
         { 6,  0, 10, -1}
    };

    bool equal = (mat.size() == axilib::Size{3, 4});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, insert_col_2)
{
    axilib::imatrix mat = matrix_5();
    axilib::Colvec<int> colvec{-12, 45, 68};
    mat.insert_col(3, colvec);

    axilib::imatrix expected
    {
         {-1,  3,  6, -12},
         { 7, -6,  2,  45},
         { 6,  0, -1,  68}
    };

    bool equal = (mat.size() == axilib::Size{3, 4});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, insert_cols)
{
    axilib::imatrix mat = matrix_5();

    axilib::imatrix other
    {
         { 3,  1,  7},
         {-9, -6, -5},
         { 6,  0,  0}
    };

    mat.insert_cols(0, other);

    axilib::imatrix expected
    {
         { 3,  1,  7, -1,  3,  6},
         {-9, -6, -5,  7, -6,  2},
         { 6,  0,  0,  6,  0, -1}
    };

    bool equal = (mat.size() == axilib::Size{3, 6});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, erase_row)
{
    axilib::fmatrix mat = matrix_6();
    mat.erase_row(2);

    axilib::fmatrix expected
    {
         { 7.6, -7.8,  0.4, -0.3,  4.4},
         { 1.7,  4.7, -4.3,  9.1, -2.5},
         { 4.1, -0.1,  4.4,  7.7, -5.5},
    };

    bool equal = (mat.size() == axilib::Size{3, 5});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, erase_rows)
{
    axilib::fmatrix mat = matrix_6();
    mat.erase_rows(axilib::Range{1, 2});

    axilib::fmatrix expected
    {
         { 7.6, -7.8,  0.4, -0.3,  4.4},
         { 4.1, -0.1,  4.4,  7.7, -5.5},
    };

    bool equal = (mat.size() == axilib::Size{2, 5});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, erase_col)
{
    axilib::fmatrix mat = matrix_6();
    mat.erase_col(3);

    axilib::fmatrix expected
    {
         { 7.6, -7.8,  0.4,  4.4},
         { 1.7,  4.7, -4.3, -2.5},
         {-8.8,  3.2,  9.5,  0.9},
         { 4.1, -0.1,  4.4, -5.5},
    };

    bool equal = (mat.size() ==  axilib::Size{4, 4});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_transformation_test, erase_cols)
{
    axilib::fmatrix mat = matrix_6();
    mat.erase_cols(axilib::Range{1, 3});

    axilib::fmatrix expected
    {
         { 7.6,  4.4},
         { 1.7, -2.5},
         {-8.8,  0.9},
         { 4.1, -5.5},
    };

    bool equal = (mat.size() == axilib::Size{4, 2});

    EXPECT_TRUE(equal);
    EXPECT_EQ(mat, expected);
}

TEST(matrix_exchange_test, swap_rows_1)
{
    axilib::dmatrix mat = matrix_2();
    mat.swap_rows(0, 2);

    axilib::dmatrix expected
    {
         {0.5, 2.3, 5.1},
         {1.0, 4.8, 9.6},
         {0.0, 6.7, 0.0},
         {0.0, 3.4, 6.2}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_exchange_test, swap_rows_2)
{
    axilib::dmatrix mat_1 = matrix_2();
    axilib::dmatrix mat_2 = matrix_3();

    mat_1.swap_rows(mat_2, 1, 2);

    axilib::dmatrix expected_1
    {
         {0.0, 6.7, 0.0},
         {1.0, 4.8, 9.6},
         {5.3, 5.2, 8.9},
         {0.0, 3.4, 6.2}
    };

    axilib::dmatrix expected_2
    {
         {3.4, 5.6, 7.8},
         {0.5, 2.3, 5.1},
         {1.1, 3.2, 9.8}
    };

    EXPECT_EQ(mat_1, expected_1);
    EXPECT_EQ(mat_2, expected_2);
}

TEST(matrix_exchange_test, swap_cols_1)
{
    axilib::dmatrix mat = matrix_3();
    mat.swap_cols(0, 2);

    axilib::dmatrix expected
    {
         {7.8, 5.6, 3.4},
         {8.9, 5.2, 5.3},
         {9.8, 3.2, 1.1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_exchange_test, swap_cols_2)
{
    axilib::dmatrix mat_1 = matrix_1();
    axilib::dmatrix mat_2 = matrix_2();

    mat_1.swap_cols(mat_2, 2, 1);

    axilib::dmatrix expected_1
    {
         { 7.6,  0.0,  0.4},
         { 1.7,  9.6, -4.3},
         {-8.8,  5.1,  9.5},
         { 4.1,  6.2,  4.4}
    };

    axilib::dmatrix expected_2
    {
         {0.0, 6.7, -7.8},
         {1.0, 4.8,  4.7},
         {0.5, 2.3,  3.2},
         {0.0, 3.4, -0.1}
    };

    EXPECT_EQ(mat_1, expected_1);
    EXPECT_EQ(mat_2, expected_2);
}

TEST(matrix_row_col_diag_change, row)
{
    axilib::dmatrix mat = matrix_1();
    axilib::Rowvec<double> rowvec{5.5, -6.6, 8.1};
    mat.row(1, rowvec);

    axilib::dmatrix expected
    {
         { 7.6, -7.8,  0.4},
         { 5.5, -6.6,  8.1},
         {-8.8,  3.2,  9.5},
         { 4.1, -0.1,  4.4}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_row_col_diag_change, col)
{
    axilib::dmatrix mat = matrix_1();
    axilib::Colvec<double> colvec{3.2, -2.5, -6.5, -0.1};
    mat.col(2, colvec);

    axilib::dmatrix expected
    {
         { 7.6, -7.8,  3.2},
         { 1.7,  4.7, -2.5},
         {-8.8,  3.2, -6.5},
         { 4.1, -0.1, -0.1}
    };

    EXPECT_EQ(mat, expected);
}

TEST(matrix_row_col_diag_change, diag)
{
    axilib::dmatrix mat = matrix_1();
    std::vector<double> vec{0.1, 0.2, 0.3};
    mat.diag(vec);

    axilib::dmatrix expected
    {
         { 0.1, -7.8,  0.4},
         { 1.7,  0.2, -4.3},
         {-8.8,  3.2,  0.3},
         { 4.1, -0.1,  4.4}
    };

    EXPECT_EQ(mat, expected);
}
