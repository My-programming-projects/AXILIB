#include "include/Axi.hpp"
#include <armadillo>

using cplx = std::complex<int>;

int main()
{
    axilib::dmatrix m_1(4,3);
    axilib::dmatrix m_2(4,3);

    m_1+= m_2;

    return 0;
}
