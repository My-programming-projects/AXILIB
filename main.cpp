#include "include/Axi.hpp"
#include <type_traits>
using cplx = std::complex<int>;

struct X;

template<typename T>
concept floating = std::is_floating_point<T>::value;

template<typename F, typename = std::enable_if_t<std::is_floating_point<F>::value>>
void f(F f) { }

int main()
{
    axilib::Matrix<int> m(2,3,[]{return 4;});



    return 0;
}
