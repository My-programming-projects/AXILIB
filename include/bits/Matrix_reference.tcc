#ifndef MINOR_TCC
#define MINOR_TCC

#include "Matrix_reference.hpp"

namespace axilib
{
    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>::Matrix_reference() :
        ptr_{nullptr} { }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>::Matrix_reference(const Range& range_rows, const Range& range_cols, Matrix<T, STORAGE>& mat) :
        matrix_size_{mat.size()},
        size_{range_rows.size(), range_cols.size()},
        ptr_{mat.data()}
    {
        init(range_rows, range_cols);
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>::Matrix_reference(std::size_t row, std::size_t col, Matrix<T, STORAGE>& mat) :
        matrix_size_{mat.size()},
        size_{mat.rows() - 1, mat.cols() - 1},
        ptr_{mat.data()}
    {
        init(row, col);
    }

    template<typename T, typename STORAGE>
    void
    Matrix_reference<T, STORAGE>::init(const Range& range_rows, const Range& range_cols)
    {
        ptrs_.resize(rows() * cols());

        for(size_type i_1 = range_rows.first(), i_2 = 0; i_1 < range_rows.last() + 1; ++i_1, ++i_2)
        {
            for(size_type j_1 = range_cols.first(), j_2 = 0; j_1 < range_cols.last() + 1; ++j_1, ++j_2)
            {
                ptrs_[rows() * j_2 + i_2] = ( &ptr_[matrix_size_.rows() * j_1 + i_1] );
            }
        }
    }

    template<typename T, typename STORAGE>
    void
    Matrix_reference<T, STORAGE>::init(size_type row, size_type col)
    {
        ptrs_.resize(rows() * cols());

        for(std::size_t i_1 = 0, i_2 = 0; i_1 < matrix_size_.rows(); ++i_1)
        {
            bool is_filled = false;

            for(std::size_t j_1 = 0, j_2 = 0; j_1 < matrix_size_.cols(); ++j_1)
            {
                if(j_1 != col && i_1 != row)
                {
                    ptrs_[rows() * j_2 + i_2] = ( &ptr_[matrix_size_.rows() * j_1 + i_1] );

                    is_filled = true;
                    ++j_2;
                }
            }

            if(is_filled)
            {
                ++i_2;
            }
        }
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::size_type
    Matrix_reference<T, STORAGE>::rows() const noexcept
    {
        return size_.rows();
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::size_type
    Matrix_reference<T, STORAGE>::cols() const noexcept
    {
        return size_.cols();
    }

    template<typename T, typename STORAGE>
    Size
    Matrix_reference<T, STORAGE>::size() const noexcept
    {
        return size_;
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::matrix_ref_iterator
    Matrix_reference<T, STORAGE>::begin()
    {
        return matrix_ref_iterator(ptrs_.begin());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_matrix_ref_iterator
    Matrix_reference<T, STORAGE>::cbegin() const noexcept
    {
        return const_matrix_ref_iterator(ptrs_.cbegin());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::matrix_ref_iterator
    Matrix_reference<T, STORAGE>::end()
    {
        return matrix_ref_iterator(ptrs_.end());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_matrix_ref_iterator
    Matrix_reference<T, STORAGE>::cend() const noexcept
    {
        return const_matrix_ref_iterator(ptrs_.cend());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::row_iterator
    Matrix_reference<T, STORAGE>::begin_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("begin_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return row_iterator(ptrs_.begin() + row, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_row_iterator
    Matrix_reference<T, STORAGE>::cbegin_row(size_type row) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("cbegin_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return row_iterator(ptrs_.cbegin() + row, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::row_iterator
    Matrix_reference<T, STORAGE>::end_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("end_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        size_type last = detail::last_element(rows(), cols(), row, Row_iterator_tag{});

        return row_iterator(ptrs_.begin() + last, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_row_iterator
    Matrix_reference<T, STORAGE>::cend_row(size_type row) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("cend_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        size_type last = detail::last_element(rows(), cols(), row, Row_iterator_tag{});

        return row_iterator(ptrs_.cbegin() + last, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::col_iterator
    Matrix_reference<T, STORAGE>::begin_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("begin_col()", "col = ", "cols size = ", col, cols()) )
        #endif

        size_type first = detail::first_element(rows(), col, Col_iterator_tag{});

        return col_iterator(ptrs_.begin() + first, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_col_iterator
    Matrix_reference<T, STORAGE>::cbegin_col(size_type col) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("begin_col()", "col = ", "cols size = ", col, cols()) )
        #endif

        size_type first = detail::first_element(rows(), col, Col_iterator_tag{});

        return const_col_iterator(ptrs_.cbegin() + first, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::col_iterator
    Matrix_reference<T, STORAGE>::end_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("end_col()", "col = ", "cols size = ", col, cols()) )
        #endif

        size_type last = detail::last_element(rows(), col, Col_iterator_tag{});

        return col_iterator(ptrs_.begin() + last, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_col_iterator
    Matrix_reference<T, STORAGE>::cend_col(size_type col) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("cend_col()", "col = ", "cols size = ", col, cols()) )
        #endif

        size_type last = detail::last_element(rows(), col, Col_iterator_tag{});

        return col_iterator(ptrs_.cbegin() + last, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::diagonal_iterator
    Matrix_reference<T, STORAGE>::begin_diag()
    {
        return diagonal_iterator(ptrs_.begin(), rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_diagonal_iterator
    Matrix_reference<T, STORAGE>::cbegin_diag() const
    {
        return diagonal_iterator(ptrs_.cbegin(), rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::diagonal_iterator
    Matrix_reference<T, STORAGE>::end_diag()
    {
        size_type last = detail::last_element(rows(), cols(), Diagonal_iterator_tag{});

        return diagonal_iterator(ptrs_.begin() + last, rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_diagonal_iterator
    Matrix_reference<T, STORAGE>::cend_diag() const
    {
        size_type last = detail::last_element(rows(), cols(), Diagonal_iterator_tag{});

        return diagonal_iterator(ptrs_.cbegin() + last, rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::reference
    Matrix_reference<T, STORAGE>::operator()(size_type i, size_type j)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )
        #endif
        return *ptrs_[rows() * j + i];
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_reference
    Matrix_reference<T, STORAGE>::operator()(size_type i, size_type j) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )
        #endif

        return *ptrs_[rows() * j + i];
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::reference
    Matrix_reference<T, STORAGE>::at(size_type i, size_type j)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )
        #endif

        return *ptrs_[rows() * j + i];
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::const_reference
    Matrix_reference<T, STORAGE>::at(size_type i, size_type j) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )
        #endif

        return *ptrs_[rows() * j + i];
    }

    template<typename T, typename STORAGE>
    bool
    Matrix_reference<T, STORAGE>::is_square() const noexcept
    {
        return rows() == cols();
    }

    template<typename T, typename STORAGE>
    void
    Matrix_reference<T, STORAGE>::fill_zeros()
    {
        imbue([]{ return value_type{}; });
    }

    template<typename T, typename STORAGE>
    std::size_t
    Matrix_reference<T, STORAGE>::zeros()
    {
        return detail::count_zeros_impl(begin(), end());
    }

    template<typename T, typename STORAGE>
    std::size_t
    Matrix_reference<T, STORAGE>::zeros_in_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("zeros_in_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return detail::count_zeros_impl(begin_row(row), end_row(row));
    }

    template<typename T, typename STORAGE>
    std::size_t
    Matrix_reference<T, STORAGE>::zeros_in_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("zeros_in_col()", "col = ", "cols size = ", col, cols()) )
        #endif

        return detail::count_zeros_impl(begin_col(col), end_col(col));
    }

    template<typename T, typename STORAGE>
    std::size_t
    Matrix_reference<T, STORAGE>::zeros_in_diag()
    {
       return  detail::count_zeros_impl(begin_diag(), end_diag());
    }

    template<typename T, typename STORAGE>
        template<typename Func>
        void
        Matrix_reference<T, STORAGE>::imbue(Func func)
        {
            detail::imbue_impl(begin(), end(), func);
        }

    template<typename T, typename STORAGE>
        template<typename Func>
        void
        Matrix_reference<T, STORAGE>::imbue_row(size_type row, Func func)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("imbue_row()", "row = ", "rows size = ", row, rows()) )
            #endif

            detail::imbue_impl(begin_row(row), end_row(row), func);
        }

    template<typename T, typename STORAGE>
        template<typename Func>
        void
        Matrix_reference<T, STORAGE>::imbue_col(size_type col, Func func)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("imbue_col()", "col = ", "cols size = ", col, cols()) )
            #endif

            detail::imbue_impl(begin_col(col), end_col(col), func);
        }

    template<typename T, typename STORAGE>
        template<typename Func>
        void
        Matrix_reference<T, STORAGE>::imbue_diag(Func func)
        {
            detail::imbue_impl(begin_diag(), end_diag(), func);
        }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::value_type
    Matrix_reference<T, STORAGE>::accumulate()
    {
        return detail::accumulate_impl(begin(), end());
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::value_type
    Matrix_reference<T, STORAGE>::accumulate_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("accumulate_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return detail::accumulate_impl(begin_row(row), end_row(row));
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::value_type
    Matrix_reference<T, STORAGE>::accumulate_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("accumulate_col()", "col = ", "cols size = ", col, cols()) )
        #endif

        return detail::accumulate_impl(begin_col(col), end_col(col));
    }

    template<typename T, typename STORAGE>
    typename Matrix_reference<T, STORAGE>::value_type
    Matrix_reference<T, STORAGE>::accumulate_diag()
    {
        return detail::accumulate_impl(begin_diag(), end_diag());
    }

    template<typename T, typename STORAGE>
    void
    Matrix_reference<T, STORAGE>::replace(const value_type old_value, const value_type new_value)
    {
        replace_if(new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix_reference<T, STORAGE>::replace_if(const value_type& new_value, Pred pred)
        {
            detail::replace_impl(begin(), end(), new_value, pred);
        }

    template<typename T, typename STORAGE>
    void
    Matrix_reference<T, STORAGE>::replace_in_row(size_type row, const value_type& old_value, const value_type& new_value)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("replace_in_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        replace_in_row_if(row, new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix_reference<T, STORAGE>::replace_in_row_if(size_type row, const value_type& new_value, Pred pred)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("replace_in_row_if()", "row = ", "rows size = ", row, rows()) )
            #endif

            detail::replace_impl(begin_row(row), end_row(row), new_value, pred);
        }

    template<typename T, typename STORAGE>
    void
    Matrix_reference<T, STORAGE>::replace_in_col(size_type col, const value_type& old_value, const value_type& new_value)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("replace_in_col()", "col = ", "cols size = ", col, cols()) )
        #endif

        replace_in_col_if(col, new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix_reference<T, STORAGE>::replace_in_col_if(size_type col, const value_type& new_value, Pred pred)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("replace_in_col_if()", "col = ", "cols size = ", col, cols()) )
            #endif

            detail::replace_impl(begin_col(col), end_col(col), new_value, pred);
        }

    template<typename T, typename STORAGE>
    void
    Matrix_reference<T, STORAGE>::replace_in_diag(value_type old_value, value_type new_value)
    {
        replace_in_diag_if(new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix_reference<T, STORAGE>::replace_in_diag_if(value_type new_value, Pred pred)
        {
            detail::replace_impl(begin_diag(), end_diag(), new_value, pred);
        }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>
    Matrix_reference<T, STORAGE>::to_matrix() const noexcept
    {
        Matrix<T, STORAGE> mat(rows(), cols());

        auto this_iter = cbegin();
        auto mat_iter = mat.begin();

        for( ; this_iter != cend(); ++this_iter, ++mat_iter)
        {
            *mat_iter = *this_iter;
        }

        return mat;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator+=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::plus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator-=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::minus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator*=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::multiplies<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator/=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::divides<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator+=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix<T, STORAGE>, std::plus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator-=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix<T, STORAGE>, std::minus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator*=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix<T, STORAGE>, std::multiplies<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator/=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix<T, STORAGE>, std::divides<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator+=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::plus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator-=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::minus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator*=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::multiplies<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>&
    Matrix_reference<T, STORAGE>::operator/=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::divides<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

} // namespace axilib

#endif // MINOR_TCC
