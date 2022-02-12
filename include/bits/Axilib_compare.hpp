#ifndef AXILIB_COMPARE_HPP
#define AXILIB_COMPARE_HPP

#include <cmath>

namespace axilib
{
    template<typename T>
    struct Almost_equal
    {
        bool operator()(const T& lhs, const T& rhs)
        {
            int ulp = 2;

            return std::fabs(lhs - rhs) <= std::numeric_limits<T>::epsilon() * std::fabs(lhs + rhs) * ulp
                   || std::fabs(lhs - rhs) < std::numeric_limits<T>::min();
        }
    };

} // namespace axilib

#endif // AXILIB_COMPARE_HPP
