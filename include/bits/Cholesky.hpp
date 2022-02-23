#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP

#include <iostream>
#include <math.h>

namespace axilib
{
    template<typename T, typename STORAGE>
    class Matrix;

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> cholesky(Matrix<T, STORAGE> mat)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( mat.is_square(), Bad_size("The matrix is not square") )
        #endif

        using value_type = typename Matrix<T, STORAGE>::value_type;

        Matrix<T, STORAGE> lower(mat.size());

        for(std::size_t j = 0; j < mat.rows(); ++j)
        {
            for(std::size_t k = j; k < mat.rows(); ++k)
            {
                value_type sum = 0;

                for(std::size_t i = 0; i < j; ++i)
                {
                    sum += (lower(k, i) * lower(j, i));
                }

                lower(k, j) = mat(k, j) - sum;
                lower(k, j) = (j == k) ? std::sqrt(lower(k, j)) : lower(k, j) / lower(j, j);
            }
        }

        return lower;
    }
} // namespace axilib



#endif // CHOLESKY_HPP
