#ifndef HELPER_HPP
#define HELPER_HPP

#include "include/Axi.hpp"

inline axilib::dmatrix matrix_1()
{
    return axilib::dmatrix
           {
                { 7.6, -7.8,  0.4},
                { 1.7,  4.7, -4.3},
                {-8.8,  3.2,  9.5},
                { 4.1, -0.1,  4.4}
           };
}

inline axilib::dmatrix matrix_2()
{
    return axilib::dmatrix
           {
                {0.0, 6.7, 0.0},
                {1.0, 4.8, 9.6},
                {0.5, 2.3, 5.1},
                {0.0, 3.4, 6.2}
           };
}

inline axilib::dmatrix matrix_3()
{
    return axilib::dmatrix
           {
                {3.4, 5.6, 7.8},
                {5.3, 5.2, 8.9},
                {1.1, 3.2, 9.8}
           };
}

inline axilib::dmatrix matrix_4()
{
    return axilib::dmatrix
           {
                {3.4, 8.6, 7.8},
                {5.3, 1.2, 7.9},
                {1.1, 3.2, 0.8}
           };
}

inline axilib::imatrix matrix_5()
{
    return axilib::imatrix
           {
                {-1,  3,  6},
                { 7, -6,  2},
                { 6,  0, -1}
           };
}

inline axilib::fmatrix matrix_6()
{
    return axilib::fmatrix
           {
                { 7.6, -7.8,  0.4, -0.3,  4.4},
                { 1.7,  4.7, -4.3,  9.1, -2.5},
                {-8.8,  3.2,  9.5,  3.4,  0.9},
                { 4.1, -0.1,  4.4,  7.7, -5.5},
           };
}

inline axilib::dmatrix get_diagonal_matrix()
{
    return axilib::dmatrix
           {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
           };
}

inline axilib::fmatrix not_banded_matrix()
{
    return axilib::fmatrix
           {
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 1, 1, 1},
                {0, 0, 1, 1}
           };
}

inline axilib::fmatrix banded_matrix()
{
    return axilib::fmatrix
           {
                {1, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 1, 1, 1},
                {0, 0, 1, 1}
           };
}

inline axilib::fmatrix upper_triangular_matrix()
{
    return axilib::fmatrix
           {
                {1, 1.2, 7.6, 2.4},
                {0, 4.5, 1.4, 0.3},
                {0, 0,   6.5, 2.8},
                {0, 0,   0,   9.8}
           };
}

inline axilib::fmatrix lower_triangular_matrix()
{
    return axilib::fmatrix
           {
                {3.3, 0,     0,   0},
                {1.4, 9.1,   0,   0},
                {4.4, 7.2, 5.6,   0},
                {0.2, 0.7, 8.6, 9.3}
           };
}

template<typename Iterator1, typename Iterator2>
bool compare(Iterator1 first_1, Iterator1 last_1, Iterator2 first_2)
{
    using value_type = typename Iterator2::value_type;
    bool equal = true;

    for(auto iter = first_1; iter != last_1; ++iter, ++first_2)
    {
        equal = axilib::Almost_equal<value_type>()(*iter, *first_2);
    }

    return equal;
}

#endif // HELPER_HPP
