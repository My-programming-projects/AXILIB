#ifndef OPS_HPP
#define OPS_HPP

#include "Matrix.tcc"
#include "Operations.hpp"

namespace axilib
{
    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator+(const Matrix<T, STORAGE>& lhs, const Matrix<T, STORAGE>& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat+= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator-(const Matrix<T, STORAGE>& lhs, const Matrix<T, STORAGE>& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat-= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator*(const Matrix<T, STORAGE>& lhs, const Matrix<T, STORAGE>& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat*= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator^(const Matrix<T, STORAGE>& lhs, const Matrix<T, STORAGE>& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat^= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator/(const Matrix<T, STORAGE>& lhs, const Matrix<T, STORAGE>& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat/= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator+(const Matrix<T, STORAGE>& lhs, const T& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat+= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator-(const Matrix<T, STORAGE>& lhs, const T& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat-= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator*(const Matrix<T, STORAGE>& lhs, const T& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat*= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE> operator/(const Matrix<T, STORAGE>& lhs, const T& rhs)
    {
        Matrix<T, STORAGE> mat = lhs;
        mat/= rhs;

        return mat;
    }

    template<typename T, typename STORAGE>
    bool operator==(const Matrix<T, STORAGE>& lhs, const Matrix<T, STORAGE>& rhs)
    {
        return op::Equal<Matrix<T, STORAGE>, Matrix<T, STORAGE>, op::Op_matrix>()(lhs, rhs);
    }

} // namespace axilib

#endif // OPS_HPP
