#include "include/Axi.hpp"
#include <armadillo>

using cplx = std::complex<int>;

int main()
{
    axilib::dmatrix mat_1
    {
        {2.3, -1.4,  5.6},
        {6.5,  4.4, -0.9},
        {0.6, -2.1,  6.7}
    };

    axilib::dmatrix mat_2
    {
        { 3.0,  6.7, -3.4},
        {-7.1, -4.5, -9.9},
        { 4.4,  8.4,  2.2}
    };

    axilib::dmatrix expected
    {
        { 5.3,  5.3,   2.2},
        {-0.6, -0.1, -10.8},
        { 5.0,  6.3,   8.9}
    };

    auto result = mat_1 + mat_2;

    double v1 = expected(1,1);
    double v2 = 4.4 + (-4.5);

    bool b = axilib::Almost_equal<double>()(v1, v2);

    std::cout << b;

    return 0;
}
