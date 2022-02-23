#ifndef MATRIX_REFERENCE_HPP
#define MATRIX_REFERENCE_HPP

#include <memory>
#include <iterator>

#include "Range.hpp"
#include "Deleted.hpp"
#include "Size.hpp"
#include "Iterator.hpp"
#include "Matrix_support_funcs.hpp"
#include "Operations.hpp"

namespace axilib
{
    template<typename T, typename STORAGE>
    class Matrix;

    template<typename T, typename STORAGE>
    class Matrix_reference
    {

    private:

        using self_type                 = Matrix_reference<T, STORAGE>;

    public:

        using type                      = Submatrix_tag;

        using value_type                = typename Matrix<T, STORAGE>::value_type;
        using reference                 = typename Matrix<T, STORAGE>::reference;
        using const_reference           = typename Matrix<T, STORAGE>::const_reference;
        using pointer                   = typename Matrix<T, STORAGE>::pointer;
        using const_pointer             = const pointer;
        using iterator                  = pointer;
        using const_iterator            = const_pointer;
        using vector_iterator           = typename std::vector<pointer>::iterator;
        using const_vector_iterator     = typename std::vector<pointer>::const_iterator;
        using matrix_ref_iterator       = Matrix_ref_iterator<vector_iterator>;
        using const_matrix_ref_iterator = Matrix_ref_iterator<const_vector_iterator>;
        using row_iterator              = Matrix_ref_iterator<vector_iterator>;
        using const_row_iterator        = Matrix_ref_iterator<const_vector_iterator>;
        using col_iterator              = Matrix_ref_iterator<vector_iterator>;
        using const_col_iterator        = Matrix_ref_iterator<const_vector_iterator>;
        using diagonal_iterator         = Matrix_ref_iterator<vector_iterator>;
        using const_diagonal_iterator   = Matrix_ref_iterator<const_vector_iterator>;
        using size_type                 = typename Matrix<T, STORAGE>::size_type;

        friend class Matrix<T, STORAGE>;

    protected:

        Matrix_reference();

        Matrix_reference(const Range& range_rows, const Range& range_cols, Matrix<T, STORAGE>& mat);

        Matrix_reference(std::size_t row, std::size_t col, Matrix<T, STORAGE>& mat);

    public:

        size_type rows() const noexcept;

        size_type cols() const noexcept;

        Size size() const noexcept;

        matrix_ref_iterator begin();

        const_matrix_ref_iterator cbegin() const noexcept;

        matrix_ref_iterator end();

        const_matrix_ref_iterator cend() const noexcept;

        row_iterator begin_row(size_type row);

        const_row_iterator cbegin_row(size_type row) const;

        row_iterator end_row(size_type row);

        const_row_iterator cend_row(size_type row) const;

        col_iterator begin_col(size_type col);

        const_col_iterator cbegin_col(size_type col) const;

        col_iterator end_col(size_type col);

        const_col_iterator cend_col(size_type col) const;

        diagonal_iterator begin_diag();

        const_diagonal_iterator cbegin_diag() const;

        diagonal_iterator end_diag();

        const_diagonal_iterator cend_diag() const;

        reference operator()(size_type i, size_type j);

        const_reference operator()(size_type i, size_type j) const;

        reference at(size_type row, size_type col);

        const_reference at(size_type row, size_type col) const;

        bool is_square() const noexcept;

        void fill_zeros();

        std::size_t zeros();

        std::size_t zeros_in_row(size_type row);

        std::size_t zeros_in_col(size_type col);

        std::size_t zeros_in_diag();

        template<typename Func>
        void imbue(Func func);

        template<typename Func>
        void imbue_row(size_type row, Func func);

        template<typename Func>
        void imbue_col(size_type col, Func func);

        template<typename Func>
        void imbue_diag(Func func);

        value_type accumulate();

        value_type accumulate_row(size_type row);

        value_type accumulate_col(size_type col);

        value_type accumulate_diag();

        void replace(const value_type old_value, const value_type new_value);

        template<typename Pred>
        void replace_if(const value_type& new_value, Pred pred);

        void replace_in_row(size_type row, const value_type& old_value, const value_type& new_value);

        template<typename Pred>
        void replace_in_row_if(size_type row, const value_type& new_value, Pred pred);

        void replace_in_col(size_type col, const value_type& old_value, const value_type& new_value);

        template<typename Pred>
        void replace_in_col_if(size_type col, const value_type& new_value, Pred pred);

        void replace_in_diag(value_type old_value, value_type new_value);

        template<typename Pred>
        void replace_in_diag_if(value_type new_value, Pred pred);

        Matrix<T, STORAGE> to_matrix() const noexcept;

        Matrix_reference<T, STORAGE>& operator+=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator-=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator*=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator/=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator+=(const Matrix<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator-=(const Matrix<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator*=(const Matrix<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator/=(const Matrix<T, STORAGE>& rhs);

        Matrix_reference<T, STORAGE>& operator+=(const value_type& rhs);

        Matrix_reference<T, STORAGE>& operator-=(const value_type& rhs);

        Matrix_reference<T, STORAGE>& operator*=(const value_type& rhs);

        Matrix_reference<T, STORAGE>& operator/=(const value_type& rhs);

    private:
        void init(const Range& range_rows, const Range& range_cols);
        void init(size_type row, size_type col);

        Size matrix_size_;
        Size size_;

        pointer ptr_;
        std::vector<pointer> ptrs_;
    };

} // namespace axilib

#endif // MATRIX_REFERENCE_HPP
