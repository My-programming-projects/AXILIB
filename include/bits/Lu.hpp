#ifndef MATH_HPP
#define MATH_HPP

//#include "include/Vector/Vector.hpp"
#include "include/bits/Enums.hpp"
#include "Matrix.tcc"
#include "Vector.tcc"

namespace axilib
{


    template<typename T, typename STORAGE>
    void LU(Matrix<T, STORAGE>& L_mat, Matrix<T, STORAGE>& U_mat, const Matrix<T, STORAGE>& mat)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( mat.is_square(), Bad_size("The matrix is not square") )
        #endif

        using value_type = typename Matrix<T, STORAGE>::value_type;

        for(std::size_t i = 0; i < mat.rows(); ++i)
        {
            for(std::size_t k = i; k < mat.rows(); ++k)
            {
                value_type sum = 0;

                 for(std::size_t j = 0; j < i; ++j)
                 {
                     sum += L_mat(i, j) * U_mat(j, k);
                 }

                 U_mat(i, k) = mat(i, k) - sum;
             }

             for(std::size_t k = i; k < mat.rows(); ++k)
             {
                 if(i == k)
                 {
                     L_mat(i, i) = 1;
                 }
                 else
                 {
                    value_type sum = 0;

                    for(std::size_t j = 0; j < mat.rows(); ++j)
                    {
                        sum += L_mat(k, j) * U_mat(j, i);
                    }

                    L_mat(k, i) = (mat(k, i) - sum) / U_mat(i, i);
                 }
             }
        }
    }

    template<typename T, typename STORAGE>
    void find_max(const Matrix<T, STORAGE>& coeffs, const Vector<Row, std::size_t>& rows, std::size_t& max_row, double& max_elem, std::size_t k)
    {
        for(std::size_t i = k + 1; i < coeffs.rows(); i++)
        {
            if(fabs( coeffs(rows[i], k)) > max_elem)
            {
                max_row = i;
                max_elem = std::fabs(coeffs(rows[i], k) );
            }
        }
    }

    template<typename T, typename STORAGE>
    void submat_modif(Matrix<T, STORAGE>& coeffs, const Vector<Row, std::size_t>& rows, std::size_t k)
    {
        for(std::size_t i = k + 1; i < coeffs.rows(); i++)
        {
            for(std::size_t j = k + 1; j < coeffs.rows(); j++)
            {
                coeffs(rows[i], j ) -= coeffs (rows[i], k ) *  coeffs(rows[k], j );
            }
        }
    }

    template<typename T, typename STORAGE>
    void forward_subst(const Matrix<T, STORAGE>& coeffs, const Vector<Row, std::size_t>& rows, Vector<Row, T>& X, T& sum)
    {
        for(std::size_t i = 1; i < coeffs.rows(); i++)
        {
            sum = coeffs(rows[i], coeffs.rows() );

            for(std::size_t j = 0; j < i; j++)
            {
                sum -= coeffs(rows[i], j ) * X[j];
            }

            X[i] = sum;
        }
    }

    template<typename T, typename STORAGE>
    void backward_subst(const Matrix<T, STORAGE>& coeffs, const Vector<Row, std::size_t>& rows, Vector<Row, T>& X, T& sum)
    {
        for(int i = coeffs.rows() - 2; i >= 0; i--)
        {
            sum = X[i];

            for(std::size_t j = coeffs.rows() - 1; j > static_cast<std::size_t>(i); j--)
            {
                sum -= coeffs(rows[i], j ) * X[j];
            }

            X[i] = sum / coeffs(rows[i], i );
        }
    }

    template<typename T, typename STORAGE>
    bool LU_2(Matrix<T, STORAGE> coeffs, Vector<Row, T>& X)
    {
        const double EPS = 0.000000001;

        std::size_t max_row;
        double sum, diag_val, max_elem;

        Vector<Row, std::size_t> rows(coeffs.rows());

        for(std::size_t i = 0; i < coeffs.rows(); i++)
        {
            rows[i] = i;
        }

        for(std::size_t k = 0; k < coeffs.rows(); k++)
        {
            max_row = k;
            max_elem = fabs(coeffs(rows[k], k));

            find_max(coeffs, rows, max_row, max_elem, k);

            if(max_elem <= EPS)
            {
                return false;
            }

            max_row != k ? std::swap(rows[k], rows[max_row]) : void(0);

            diag_val = coeffs(rows[k], k );

            for(std::size_t i = k + 1; i < coeffs.rows(); i++)
            {
                coeffs(rows[i], k ) /= diag_val;
            }

            submat_modif(coeffs, rows, k);
        }

        X[0] = coeffs(rows[0], coeffs.rows() );

        forward_subst(coeffs, rows, X, sum);

        X[coeffs.rows() - 1] /= coeffs(rows[coeffs.rows() - 1], coeffs.rows() - 1);

        backward_subst(coeffs, rows, X, sum);

        return true;
    }

} // namespace axilib

        /*template<typename M>
        typename M::value_type det(M mat)
        {
            if(!mat.is_square())
            {
                throw std::logic_error("No square matrix (" + std::to_string(mat.rows()) + "x" +
                                       std::to_string(mat.cols()) + ")");
            }

            using value_type = typename M::value_type;

            value_type n_1;
            value_type n_2;
            value_type total = 1;
            value_type determinant = 1;

            std::size_t index;
            std::size_t n = mat.rows();

            Vector<Row, value_type> temp(n + 1);

            for(std::size_t i = 0; i < n; i++)
            {
                index = i;

                while(mat(index, i) == 0 && index < n)
                {
                     index++;
                }

                if(index == n)
                {
                    continue;
                }

                if(index != i)
                {
                    for(std::size_t j = 0; j < n; j++)
                    {
                       std::swap(mat(index, j),mat(i, j));
                    }

                    determinant = determinant * std::pow(-1,index-i);
                }

                for(std::size_t j = 0; j < n; j++)
                {
                    temp[j] = mat(i, j);
                }

                for(std::size_t j = i+1; j < n; j++)
                {
                    n_1 = temp[i];
                    n_2 = mat(j, i);


                    for(std::size_t k = 0; k < n; k++)
                    {
                         mat(j, k) = (n_1 * mat(j, k)) - (n_2 * temp[k]);
                    }

                    total = total * n_1;
                }
            }

            for(std::size_t i = 0; i < n; i++)
            {
                determinant = determinant * mat(i, i);
            }

            return (determinant/total);
        }


   } // namespace math*/

//} // namespace axi

#endif // MATH_HPP
