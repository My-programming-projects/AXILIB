#ifndef HELPER_HPP
#define HELPER_HPP

#include "include/Axi.hpp"

axilib::dmatrix matrix_1()
{
    return axilib::dmatrix
    {
        {2.3, -1.4,  5.6},
        {6.5,  6.4, -0.9},
        {0.6, -2.1,  6.7}
    };
}

axilib::dmatrix matrix_2()
{
    return axilib::dmatrix
    {
        { 3.0,  6.7, -3.4},
        {-7.1, -6.5, -9.9},
        { 4.4,  8.4,  2.2}
    };
}

axilib::fmatrix matrix_3()
{
    return axilib::fmatrix
    {
        { 2.0, 1.0, 3.0},
        {-1.0, 2.0, 4.0}
    };
}

axilib::fmatrix matrix_4()
{
    return axilib::fmatrix
    {
        { 1.0,  3.0},
        { 2.0, -2.0},
        {-1.0,  4.0}
    };
}

#endif // HELPER_HPP
