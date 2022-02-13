#ifndef OPS_HPP
#define OPS_HPP

#include "Matrix.tcc"
#include "Vector.tcc"
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

    //

    template<typename VO1, typename VO2, typename T1, typename T2>
    Vector<VO1, T1> operator+(const Vector<VO1, T1>& lhs, const Vector<VO2, T2>& rhs)
    {
        Vector<VO1, T1> vec = lhs;
        lhs+= rhs;

        return lhs;
    }

    template<typename VO1, typename VO2, typename T1, typename T2>
    Vector<VO1, T1> operator-(const Vector<VO1, T1>& lhs, const Vector<VO2, T2>& rhs)
    {
        Vector<VO1, T1> vec = lhs;
        lhs-= rhs;

        return lhs;
    }

    template<typename VO1, typename VO2, typename T1, typename T2>
    Vector<VO1, T1> operator*(const Vector<VO1, T1>& lhs, const Vector<VO2, T2>& rhs)
    {
        Vector<VO1, T1> vec = lhs;
        lhs*= rhs;

        return lhs;
    }

    template<typename VO1, typename VO2, typename T1, typename T2>
    T1 operator^(const Vector<VO1, T1>& lhs, const Vector<VO2, T2>& rhs)
    {
        Vector<VO1, T1> vec = lhs;
        lhs^= rhs;

        return lhs;
    }

    template<typename VO1, typename VO2, typename T1, typename T2>
    T1 operator/(const Vector<VO1, T1>& lhs, const Vector<VO2, T2>& rhs)
    {
        Vector<VO1, T1> vec = lhs;
        lhs/= rhs;

        return lhs;
    }

    template<typename VO, typename T>
    Vector<VO, T> operator+(const Vector<VO, T>& lhs, const T& rhs)
    {
        Vector<VO, T> vec = lhs;
        lhs+= rhs;

        return lhs;
    }

    template<typename VO, typename T>
    Vector<VO, T> operator-(const Vector<VO, T>& lhs, const T& rhs)
    {
        Vector<VO, T> vec = lhs;
        lhs-= rhs;

        return lhs;
    }

    template<typename VO, typename T>
    Vector<VO, T> operator*(const Vector<VO, T>& lhs, const T& rhs)
    {
        Vector<VO, T> vec = lhs;
        lhs*= rhs;

        return lhs;
    }

    template<typename VO, typename T>
    Vector<VO, T> operator/(const Vector<VO, T>& lhs, const T& rhs)
    {
        Vector<VO, T> vec = lhs;
        lhs/= rhs;

        return lhs;
    }

    template<typename VO, typename T>
    bool operator==(const Vector<VO, T>& lhs, const Vector<VO, T>& rhs)
    {
        return op::Equal<Vector<VO, T>, Vector<VO, T>, op::Op_vector>()(lhs, rhs);
    }

    //

    template<typename T, typename STORAGE, typename VO>
    Vector<VO, T> operator*(const Matrix<T, STORAGE>& lhs, const Vector<VO, T>& rhs)
    {
        return op::Multiplies<Matrix<T, STORAGE>, Vector<VO, T>, op::Op_mat_vec>()(lhs, rhs);
    }

} // namespace axilib

#endif // OPS_HPP
