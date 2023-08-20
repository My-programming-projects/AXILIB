#ifndef BASE_TCC
#define BASE_TCC

#include "Matrix.hpp"

namespace axilib
{
    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix() { }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix(size_type rows, size_type cols) :
        data_(rows * cols, 0),
        size_(rows, cols) { }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix(const Size& mat_size) :
        Matrix(mat_size.rows(), mat_size.cols()) { }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix(std::initializer_list<value_type> list) :
        size_{1, list.size()}
    {
        copy_impl_(list, From_list{});
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix(std::initializer_list<std::initializer_list<value_type>> list)
    {
        copy_impl_(list, From_container{});
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix(const std::string& expr)
    {
        From_string<T> expression(expr);
        expression.start();
        std::vector<std::vector<value_type>> result = expression.get();

        copy_impl_(result, From_container{});
    }

    template<typename T, typename STORAGE>
        template<Requires_functor Function>
    Matrix<T, STORAGE>::Matrix(size_type req_rows, size_type req_cols, Function function) :
            Matrix(req_rows, req_cols)
        {
            copy_impl_(function, From_functor{});
        }

    template<typename T, typename STORAGE>
        template<Requires_functor Function>
        Matrix<T, STORAGE>::Matrix(const Size& size, Function function) :
            Matrix(size.rows(), size.cols(), function) { }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix(const Matrix<T, STORAGE>& copy) :
        data_(copy.data_),
        size_(copy.size_) {}

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>::Matrix(Matrix<T, STORAGE>&& move) :
        data_(move.data_),
        size_(move.size_)
    {
        move.clear();
        move.size_ = Size{};
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator=(const Matrix<T, STORAGE>& rhs)
    {
        size_ = rhs.size_;
        data_ = rhs.data_;

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator=(Matrix<T, STORAGE>&& rhs)
    {
        data_ = rhs.data_;
        size_ = rhs.size_;

        rhs.data_.clear();
        rhs.size_ = Size{};

        return *this;
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>:: allocator_type
    Matrix<T, STORAGE>::get_allocator() const noexcept
    {
        return data_.get_allocator();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::size_type
    Matrix<T, STORAGE>::rows() const noexcept
    {
        return size_.rows();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::size_type
    Matrix<T, STORAGE>::cols() const noexcept
    {
        return size_.cols();
    }

    template<typename T, typename STORAGE>
    Size
    Matrix<T, STORAGE>::size() const noexcept
    {
        return size_;
    }

    template<typename T, typename STORAGE>
    bool
    Matrix<T, STORAGE>::empty() const noexcept
    {
        return data_.empty();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reference
    Matrix<T, STORAGE>::operator[](size_type n)
    {
        return data_[n];
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reference
    Matrix<T, STORAGE>::operator[](size_type n) const
    {
        return data_[n];
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reference
    Matrix<T, STORAGE>::operator()(size_type i, size_type j)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("operator()") )
        #endif

        return data_[size_.rows() * j + i];
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reference
    Matrix<T, STORAGE>::operator()(size_type i, size_type j) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("operator()") )
        #endif

        return data_[size_.rows() * j + i];
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reference
    Matrix<T, STORAGE>::at(size_type i, size_type j)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )
        #endif

        return data_[size_.rows() * j + i];
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reference
    Matrix<T, STORAGE>::at(size_type i, size_type j) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
           AXILIB_CHECK( ((i < rows()) && (j < cols())), Out_of_bounds("at()") )
        #endif

        return data_[size_.rows() * j + i];
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::pointer
    Matrix<T, STORAGE>::data() noexcept
    {
        return data_.data();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_pointer
    Matrix<T, STORAGE>::data() const noexcept
    {
        return data_.data();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::iterator
    Matrix<T, STORAGE>::begin()
    {
        return data_.begin();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_iterator
    Matrix<T, STORAGE>::cbegin() const noexcept
    {
        return data_.cbegin();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::iterator
    Matrix<T, STORAGE>::end()
    {
        return data_.end();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_iterator
    Matrix<T, STORAGE>::cend() const noexcept
    {
        return data_.cend();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_iterator
    Matrix<T, STORAGE>::rbegin()
    {
        return data_.rbegin();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_iterator
    Matrix<T, STORAGE>::crbegin() const noexcept
    {
        return data_.rbegin();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_iterator
    Matrix<T, STORAGE>::rend()
    {
        return data_.rend();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_iterator
    Matrix<T, STORAGE>::crend() const noexcept
    {
        return data_.rend();
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::col_iterator
    Matrix<T, STORAGE>::begin_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("begin_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        size_type first = detail::first_element(rows(), col, Col_iterator_tag{});

        return col_iterator(begin() + first, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_col_iterator
    Matrix<T, STORAGE>::cbegin_col(size_type col) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("cbegin_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        size_type first = detail::first_element(rows(), col, Col_iterator_tag{});

        return const_col_iterator(cbegin() + first, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::col_iterator
    Matrix<T, STORAGE>::end_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("end_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        size_type last = detail::last_element(rows(), col, Col_iterator_tag{});

        return col_iterator(begin() + last, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_col_iterator
    Matrix<T, STORAGE>::cend_col(size_type col) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("cend_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        size_type last = detail::last_element(rows(), col, Col_iterator_tag{});

        return const_col_iterator(cbegin() + last, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_col_iterator
    Matrix<T, STORAGE>::rbegin_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("rbegin_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        return reverse_col_iterator(end_col(col) - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_col_iterator
    Matrix<T, STORAGE>::crbegin_col(size_type col) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("crbegin_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        return reverse_col_iterator(end_col(col) - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_col_iterator
    Matrix<T, STORAGE>::rend_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("rend_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        return reverse_col_iterator(begin_col(col) - 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_col_iterator
    Matrix<T, STORAGE>::crend_col(size_type col) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("crend_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        return reverse_col_iterator(begin_col(col) - 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::row_iterator
    Matrix<T, STORAGE>::begin_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("begin_row()", "row = ", "rows size = ", row, rows()) );
        #endif

        return row_iterator(begin() + row, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_row_iterator
    Matrix<T, STORAGE>::cbegin_row(size_type row) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("cbegin_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return const_row_iterator(cbegin() + row, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::row_iterator
    Matrix<T, STORAGE>::end_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("end_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        size_type last = detail::last_element(rows(), cols(), row, Row_iterator_tag{});

        return row_iterator(begin() + last, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_row_iterator
    Matrix<T, STORAGE>::cend_row(size_type row) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("cend_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        size_type last = detail::last_element(rows(), cols(), row, Row_iterator_tag{});

        return const_row_iterator(cbegin() + last, rows());
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_row_iterator
    Matrix<T, STORAGE>::rbegin_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("rbegin_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return reverse_row_iterator(end_row(row) - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_row_iterator
    Matrix<T, STORAGE>::crbegin_row(size_type row) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("crbegin_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return const_reverse_row_iterator(cend_row(row) - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_row_iterator
    Matrix<T, STORAGE>::rend_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("rend_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return reverse_row_iterator(begin_row(row) - 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_row_iterator
    Matrix<T, STORAGE>::crend_row(size_type row) const
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("crend_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return reverse_row_iterator(begin_row(row) - 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::diagonal_iterator
    Matrix<T, STORAGE>::begin_diag()
    {
        return diagonal_iterator(begin(), size_.rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_diagonal_iterator
    Matrix<T, STORAGE>::cbegin_diag() const noexcept
    {
        return const_diagonal_iterator(cbegin(), size_.rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::diagonal_iterator
    Matrix<T, STORAGE>::end_diag()
    {
        size_type last = detail::last_element(size_.rows(), size_.cols(), Diagonal_iterator_tag{});

        return diagonal_iterator(begin() + last, rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_diagonal_iterator
    Matrix<T, STORAGE>::cend_diag() const noexcept
    {
        size_type last = detail::last_element(size_.rows(), size_.cols(), Diagonal_iterator_tag{});

        return const_diagonal_iterator(cbegin() + last, rows() + 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_diagonal_iterator
    Matrix<T, STORAGE>::rbegin_diag()
    {
        return reverse_diagonal_iterator(end_diag() - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_diagonal_iterator
    Matrix<T, STORAGE>::crbegin_diag() const noexcept
    {
        return reverse_diagonal_iterator(end_diag() - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::reverse_diagonal_iterator
    Matrix<T, STORAGE>::rend_diag()
    {
        return reverse_diagonal_iterator(begin_diag() - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::const_reverse_diagonal_iterator
    Matrix<T, STORAGE>::crend_diag() const noexcept
    {
        return reverse_diagonal_iterator(begin_diag() - 1, 1);
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::value_type
    Matrix<T, STORAGE>::det()
    {
        return det_impl();
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>
    Matrix<T, STORAGE>::submatrix(size_type first_row, size_type last_row, size_type first_col, size_type last_col)
    {
        return Matrix_reference<T, STORAGE>(Range{first_row, last_row}, Range{first_col, last_col});
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>
    Matrix<T, STORAGE>::submatrix(const Range& rows, const Range& cols)
    {
        return Matrix_reference<T, STORAGE>(rows, cols, *this);
    }

    template<typename T, typename STORAGE>
    Matrix_reference<T, STORAGE>
    Matrix<T, STORAGE>::minor(std::size_t row, std::size_t col)
    {
        return Matrix_reference<T, STORAGE>(row, col, *this);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::clear()
    {
        data_.clear();
        size_ = Size();
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::fill_zeros()
    {
        fill_impl_(0);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::fill_ones()
    {
        fill_impl_(1);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::fill_eye()
    {
        Diagonal::fill(rows(), cols(), data_, 1);
    }

    template<typename T, typename STORAGE>
        template<Requires_functor Function>
        void
        Matrix<T, STORAGE>::imbue(Function function)
        {
            detail::imbue_impl(begin(), end(), function);
        }

    template<typename T, typename STORAGE>
        template<Requires_functor Function>
        void
        Matrix<T, STORAGE>::imbue_row(Function function, size_type row)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("imbue_row()", "row = ", "rows size = ", row, rows()) )
            #endif

            detail::imbue_impl(begin_row(row), end_row(row), function);
        }

    template<typename T, typename STORAGE>
        template<Requires_functor Function>
        void
        Matrix<T, STORAGE>::imbue_col(Function function, size_type col)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("imbue_row()", "col = ", "cols size = ", col, cols()) )
            #endif

            detail::imbue_impl(begin_col(col), end_col(col), function);
        }

    template<typename T, typename STORAGE>
        template<Requires_functor Function>
        void
        Matrix<T, STORAGE>::imbue_diag(Function function)
        {
            detail::imbue_impl(begin_diag(), end_diag(), function);
        }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::size_type
    Matrix<T, STORAGE>::zeros() noexcept
    {
        return detail::count_zeros_impl(data_.begin(), data_.end());
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::size_type
    Matrix<T, STORAGE>::zeros_in_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("zeros_in__row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return detail::count_zeros_impl(begin_row(row), end_row(row));
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::size_type
    Matrix<T, STORAGE>::zeros_in_diag() noexcept
    {
        return detail::count_zeros_impl(begin_diag(), end_diag());
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::size_type
    Matrix<T, STORAGE>::zeros_in_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("zeros_in_row()", "col = ", "cols size = ", col, cols()) )
        #endif

        return detail::count_zeros_impl(begin_col(col), end_col(col));
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::value_type
    Matrix<T, STORAGE>::accumulate()
    {
        return detail::accumulate_impl(data_.begin(), data_.end());
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::value_type
    Matrix<T, STORAGE>::accumulate_col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("accumulate_row()", "col = ", "cols size = ", col, cols()) )
        #endif

        return detail::accumulate_impl(begin_col(col), end_col(col));
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::value_type
    Matrix<T, STORAGE>::accumulate_row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("accumulate_row()", "row = ", "rows size = ", row, rows()) )
        #endif

        return detail::accumulate_impl(begin_row(row), end_row(row));
    }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::value_type
    Matrix<T, STORAGE>::accumulate_diag() noexcept
    {
        return detail::accumulate_impl(begin_diag(), end_diag());
    }

    template<typename T, typename STORAGE>
        template<typename SD>
        void
        Matrix<T, STORAGE>::sort_row(size_type row)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("sort_row()", "row = ", "rows size = ", row, rows()) )
            #endif

            sort_impl_<row_iterator, SD>(begin_row(row), end_row(row));
        }

    template<typename T, typename STORAGE>
        template<typename SD>
        void
        Matrix<T, STORAGE>::sort_col(size_type col)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("sort_col()", "col = ", "cols size = ", col, cols()) )
            #endif

            sort_impl_<col_iterator, SD>(begin_col(col), end_col(col));
        }

    template<typename T, typename STORAGE>
        template<typename SD>
        void
        Matrix<T, STORAGE>::sort_diag()
        {
            sort_impl_<diagonal_iterator, SD>(begin_diag(), end_diag());
        }

    template<typename T, typename STORAGE>
        template<typename RO>
        void
        Matrix<T, STORAGE>::rotate(size_type seq)
        {
            auto first = Required_iterator<std::is_same_v<RO, Left>, reverse_iterator, iterator>::get(rbegin(), begin());
            auto last = Required_iterator<std::is_same_v<RO, Left>, reverse_iterator, iterator>::get(rend(), end());

            rotate_impl_(first, last, seq);
        }

    template<typename T, typename STORAGE>
        template<Requires_rotate_order RO>
        void
        Matrix<T, STORAGE>::rotate_row(size_type row, size_type seq)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("rotate_row()", "row = ", "rows size = ", row, rows()) )
            #endif

            std::vector<T> temp(begin_row(row), end_row(row));

            using iter = typename std::vector<T>::iterator;
            using rev_iter = typename std::vector<T>::reverse_iterator;

            auto first = Required_iterator<std::is_same_v<RO, Left>, iter, rev_iter>::get(temp.begin(), temp.rbegin());
            auto last = Required_iterator<std::is_same_v<RO, Left>, iter, rev_iter>::get(temp.end(), temp.rend());

            rotate_impl_(first, last, seq);
            std::copy(temp.begin(), temp.end(), begin_row(row));
        }

    template<typename T, typename STORAGE>
        template<Requires_rotate_order RO>
        void
        Matrix<T, STORAGE>::rotate_col(size_type col, size_type seq)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("rotate_row()", "col = ", "cols size = ", col, cols()) )
            #endif

            std::vector<T> temp(begin_col(col), end_col(col));

            using iter = typename std::vector<T>::iterator;
            using rev_iter = typename std::vector<T>::reverse_iterator;

            auto first = Required_iterator<std::is_same_v<RO, Left>, iter, rev_iter>::get(temp.begin(), temp.rbegin());
            auto last = Required_iterator<std::is_same_v<RO, Left>, iter, rev_iter>::get(temp.end(), temp.rend());

            rotate_impl_(first, last, seq);
            std::copy(temp.begin(), temp.end(), begin_col(col));
        }

    template<typename T, typename STORAGE>
        template<Requires_rotate_order RO>
        void
        Matrix<T, STORAGE>::rotate_diag(size_type seq)
        {
            std::vector<T> temp = diag();

            using iter = typename std::vector<T>::iterator;
            using rev_iter = typename std::vector<T>::reverse_iterator;

            auto first = Required_iterator<std::is_same_v<RO, Left>, iter, rev_iter>::get(temp.begin(), temp.rbegin());
            auto last = Required_iterator<std::is_same_v<RO, Left>, iter, rev_iter>::get(temp.end(), temp.rend());

            rotate_impl_(first, last, seq);
            diag(temp);
        }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::replace(const value_type& old_value, const value_type& new_value)
    {
        detail::replace_impl(begin(), end(), new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix<T, STORAGE>::replace_if(Pred pred, const value_type& new_value)
        {
            detail::replace_impl(begin(), end(), new_value, pred);
        }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::replace_in_row(size_type row, const value_type& old_value, const value_type& new_value)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("replace_in_row()", "row = ", "rows size = ", row, rows()) );
        #endif

        detail::replace_impl(begin_row(row), end_row(row), new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix<T, STORAGE>::replace_in_row_if(size_type row, Pred pred, const value_type& new_value)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("replace_in_row_if()", "row = ", "rows size = ", row, rows()) );
            #endif

            detail::replace_impl(begin_row(row), end_row(row), new_value, pred);
        }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::replace_in_col(size_type col, const value_type& old_value, const value_type& new_value)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("replace_in_col()", "col = ", "cols size = ", col, cols()) );
        #endif

        detail::replace_impl(begin_col(col), end_col(col), new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix<T, STORAGE>::replace_in_col_if(size_type col, Pred pred, const value_type& new_value)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("replace_in_col_if()", "col = ", "cols size = ", col, cols()) );
            #endif

            detail::replace_impl(begin_col(col), end_col(col), new_value, pred);
        }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::replace_in_diag(const value_type& old_value, const value_type& new_value)
    {
        detail::replace_impl(begin_diag(), end_diag(), new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename T, typename STORAGE>
        template<typename Pred>
        void
        Matrix<T, STORAGE>::replace_in_diag_if(Pred pred, const value_type& new_value)
        {
            detail::replace_impl(begin_diag(), end_diag(), new_value, pred);
        }

    template<typename T, typename STORAGE>
    std::vector<T>
    Matrix<T, STORAGE>::row(size_type row)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("row_to_std_vector()", "row = ", "rows size = ", row, rows()) )
        #endif

        std::vector<value_type> vec(begin_row(row), end_row(row));

        return vec;
    }

    template<typename T, typename STORAGE>
    std::vector<T>
    Matrix<T, STORAGE>::col(size_type col)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("col_to_std_vector()", "col = ", "cols size = ", col, cols()) )
        #endif

        std::vector<value_type> vec(begin_col(col), end_col(col));

        return vec;
    }

    template<typename T, typename STORAGE>
    std::vector<T>
    Matrix<T, STORAGE>::diag() noexcept
    {
        std::vector<value_type> vec(begin_diag(), end_diag());

        return vec;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::row(size_type row, const std::vector<T>& vector)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (vector.size() == cols()), Incompatible_size("row()", "rows = ", rows(), vector.size()) );
            AXILIB_CHECK( ((row >= 0) && (row < rows())), Bad_index("row", "row = ", "rows size = ", row, rows()) );
        #endif

        std::copy(vector.cbegin(), vector.cend(), begin_row(row));
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::col(size_type col, const std::vector<T>& vector)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (vector.size() == rows()), Incompatible_size("col()", "cols = ", cols(), vector.size()) );
            AXILIB_CHECK( ((col >= 0) && (col < cols())), Bad_index("col", "col = ", "cols size = ", col, cols()) );
        #endif

        std::copy(vector.cbegin(), vector.cend(), begin_col(col));
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::diag(const std::vector<T>& vector)
    {
        std::copy(vector.cbegin(), vector.cend(), begin_diag());
    }

    template<typename T, typename STORAGE>
    bool
    Matrix<T, STORAGE>::is_empty() const noexcept
    {
        return data_.empty() && (size_ == Size{});
    }

    template<typename T, typename STORAGE>
    bool
    Matrix<T, STORAGE>::is_square() const noexcept
    {
        return rows() == cols();
    }

    template<typename T, typename STORAGE>
    bool
    Matrix<T, STORAGE>::is_diagonal() const noexcept
    {
        return Diagonal::is_type(*this);
    }

    template<typename T, typename STORAGE>
    bool
    Matrix<T, STORAGE>::is_banded() const noexcept
    {
        return Banded::is_type(*this);
    }

    template<typename T, typename STORAGE>
        template<Requires_triangular_type TT>
        bool
        Matrix<T, STORAGE>::is_triangular() const noexcept
        {
            return TT::is_type(*this);
        }

    template<typename T, typename STORAGE>
        template<typename SD>
        bool
        Matrix<T, STORAGE>::is_sorted() const noexcept
        {
            return is_sorted_impl_<const_iterator, SD>(cbegin(), cend());
        }

    template<typename T, typename STORAGE>
        template<typename SD>
        bool
        Matrix<T, STORAGE>::is_sorted_row(size_type row) const
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( (row >= 0) && (row < rows()), Bad_index("is_sorted_row()", "row = ", "rows size = ", row, rows()))
            #endif

            return is_sorted_impl_<const_row_iterator, SD>(cbegin_row(row), cend_row(row));
        }

    template<typename T, typename STORAGE>
        template<typename SD>
        bool
        Matrix<T, STORAGE>::is_sorted_col(size_type col) const
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( (col >= 0) && (col < cols()), Bad_index("is_sorted_col()", "col = ", "cols size = ", col, cols()))
            #endif

            return is_sorted_impl_<const_col_iterator, SD>(cbegin_col(col), cend_col(col));
        }

    template<typename T, typename STORAGE>
        template<typename SD>
        bool
        Matrix<T, STORAGE>::is_sorted_diag() const noexcept
        {
            return is_sorted_impl_<const_diagonal_iterator, SD>(cbegin_diag(), cend_diag());
        }

    template<typename T , typename STORAGE>
    void
    Matrix<T, STORAGE>::to_banded(value_type value)
    {
        transform_to_square();
        Banded::fill(rows(), cols(), data_, value);
    }

    template<typename T, typename STORAGE>
        template<Requires_triangular_type TT>
        void
        Matrix<T, STORAGE>::to_triangular(value_type value)
        {
            transform_to_square();
            TT::fill(rows(), cols(), data_, value);
        }

#ifndef AXILIB_USE_FIXED_MATRIX

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::resize(size_type rows, size_type cols)
    {
        Matrix<T, STORAGE> temp(rows, cols);

        size_type row_end = rows > size_.rows() ? size_.rows() : rows;
        size_type col_end = cols > size_.cols() ? size_.cols() : cols;

        for(size_type i = 0; i < row_end; ++i)
        {
            for(size_type j = 0; j < col_end; ++j)
            {
                temp(i, j) = this->operator()(i, j);
            }
        }

        *this = temp;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::resize(const Size& size)
    {
        resize(size.rows(), size.cols());
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::resize_rows(size_type new_rows)
    {
        resize(new_rows, cols());
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::resize_cols(size_type new_cols)
    {
        resize(rows(), new_cols);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_row(size_type position, value_type value)
    {
        insert_row_impl_(position, value);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_row(size_type position, const std::vector<T>& vector)
    {
        insert_row_impl_(position, vector);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_rows(size_type position, const Matrix& other)
    {
        insert_rows_impl_(position, other);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_col(size_type position, value_type value)
    {
        insert_col_impl_(position, value);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_col(size_type position, const std::vector<T>& vector)
    {
        insert_col_impl_(position, vector);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_cols(size_type position, const Matrix& other)
    {
        insert_cols_impl_(position, other);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_row(size_type position)
    {
        erase_row_impl_(position);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_rows(size_type first, size_type last)
    {
        erase_rows_impl_(Range{first, last});
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_rows(const Range& range)
    {
        erase_rows_impl_(range);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_col(size_type position)
    {
        erase_col_impl_(position);
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_cols(size_type first, size_type last)
    {
        erase_cols_impl_(Range{first, last});
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_cols(const Range& range)
    {
        erase_cols_impl_(range);
    }

#endif

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::swap_rows(size_type row_1, size_type row_2)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (row_1 >= 0) && (row_1 < rows()), Bad_index("swap_rows()", "row_1 = ", "rows size = ", row_1, rows()))
            AXILIB_CHECK( (row_2 >= 0) && (row_2 < rows()), Bad_index("swap_rows()", "row_2 = ", "rows size = ", row_2, rows()))
        #endif

        swap_impl_(begin_row(row_1), end_row(row_1), begin_row(row_2), end_row(2));
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::swap_rows(Matrix<T>& other, size_type row_1, size_type row_2)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (cols() == other.cols()), Incosistent_columns())
            AXILIB_CHECK( (row_1 >= 0) && (row_1 < rows()), Bad_index("swap_rows()", "row_1 = ", "rows size = ", row_1, rows()))
            AXILIB_CHECK( (row_2 >= 0) && (row_2 < rows()), Bad_index("swap_rows()", "row_2 = ", "rows size = ", row_2, rows()))
        #endif

        swap_impl_(other.begin_row(row_1), other.end_row(row_1), begin_row(row_2), end_row(row_2));
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::swap_cols(size_type col_1, size_type col_2)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (col_1 >= 0) && (col_1 < cols()), Bad_index("swap_cols()", "col_1 = ", "cols size = ", col_1, cols()))
            AXILIB_CHECK( (col_2 >= 0) && (col_2 < cols()), Bad_index("swap_cols()", "col_2 = ", "cols size = ", col_2, cols()))
        #endif

        swap_impl_(begin_col(col_1), end_col(col_1), begin_col(col_2), end_col(col_2));
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::swap_cols(Matrix<T, STORAGE>& other, size_type col_1, size_type col_2)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (rows() == other.rows()), Incosistent_rows())
            AXILIB_CHECK( (col_1 >= 0) && (col_1 < cols()), Bad_index("swap_cols()", "col_1 = ", "cols size = ", col_1, cols()))
            AXILIB_CHECK( (col_2 >= 0) && (col_2 < cols()), Bad_index("swap_cols()", "col_2 = ", "cols size = ", col_2, cols()))
        #endif

        swap_impl_(other.begin_col(col_1), other.end_col(col_1), begin_col(col_2), end_col(col_2));
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::set_size(const Size& mat_size)
    {
        size_ = mat_size;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator+=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::plus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator-=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::minus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator*=(const Matrix<T, STORAGE>& rhs)
    {
        Matrix<T, STORAGE> result = op::Multiplies<self_type, self_type, op::Op_matrix>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator^=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::multiplies<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator/=(const Matrix<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, self_type, std::divides<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator+=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix_reference<T, STORAGE>, std::plus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator-=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix_reference<T, STORAGE>, std::minus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator*=(const Matrix_reference<T, STORAGE>& rhs)
    {
        Matrix<T, STORAGE> result = op::Multiplies<self_type, Matrix_reference<T, STORAGE>, op::Op_matrix>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator^=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix_reference<T, STORAGE>, std::multiplies<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator/=(const Matrix_reference<T, STORAGE>& rhs)
    {
        op::Binary_op<self_type, Matrix_reference<T, STORAGE>, std::divides<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator+=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::plus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator-=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::minus<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator*=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::multiplies<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    template<typename T, typename STORAGE>
    Matrix<T, STORAGE>&
    Matrix<T, STORAGE>::operator/=(const value_type& rhs)
    {
        op::Binary_op_scalar<self_type, value_type, std::divides<value_type>, op::Op_matrix>()(*this, rhs);

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::size_type
    Matrix<T, STORAGE>::get_new_size(size_type old_size, size_type new_size)
    {
        return ( new_size > old_size ? old_size : new_size );
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::set_array(const std::vector<T> &data)
    {
        data_ = data;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::copy_impl_(Matrix<T, STORAGE>& other, From_other)
    {
        for(size_type i = 0; i < rows(); ++i)
        {
            for(size_type j = 0; j < cols(); ++j)
            {
                data_[rows() * j + i] = other(i, j);
            }
        }
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::copy_impl_(Matrix<T, STORAGE>& other, size_type r, size_type c, From_other)
    {
        for(size_type i = 0; i < r; ++i)
        {
            for(size_type j = 0; j < c; ++j)
            {
                other(i, j) = data_[rows() * j + i];
            }
        }
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::copy_impl_(std::initializer_list<value_type> list, From_list)
    {
        if(data_.size() != list.size())
        {
            data_.resize(list.size());
        }

        std::copy(list.begin(), list.end(), data_.begin());
    }

    template<typename T, typename STORAGE>
        template<typename Container>
        void
        Matrix<T, STORAGE>::Matrix::copy_impl_(Container container, From_container)
        {
            Matrix_initializer<value_type, Container> mat_init(container);
            set_size(mat_init.get_size());
            set_array(mat_init.get_data());
        }

    template<typename T, typename STORAGE>
        template<typename Function>
        void
        Matrix<T, STORAGE>::copy_impl_(Function function, From_functor)
        {
            for(auto& x : data_) x = function();
        }

    template<typename T, typename STORAGE>
        template<typename U>
        void
        Matrix<T, STORAGE>::fill_impl_(U value)
        {
            auto result = traits::In_type<Is_complex<T>::value, T>::value(value);

            detail::imbue_impl(data_.begin(), data_.end(), [result]{ return result; });
        }

    template<typename T, typename STORAGE>
        template<typename Iterator>
        void
        Matrix<T, STORAGE>::rotate_impl_(Iterator first, Iterator last, size_type seq)
        {
            std::rotate(first, first + seq, last);
        }

    template<typename T, typename STORAGE>
        template<typename Iterator, typename SD>
        bool
        Matrix<T, STORAGE>::is_sorted_impl_(Iterator first, Iterator last) const noexcept
        {
            return std::is_sorted(first, last, Sort_functor<value_type, SD>());
        }

    template<typename T, typename STORAGE>
        template<typename Iterator, typename SD>
        void
        Matrix<T, STORAGE>::sort_impl_(Iterator first, Iterator last)
        {
            std::vector<value_type> temp(first, last);
            std::sort(temp.begin(), temp.end(), Sort_functor<value_type, SD>());
            std::copy(temp.begin(), temp.end(), first);
        }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_row_impl_(size_type position, value_type value)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position <= rows()), Bad_index("insert_row()", "position = ", "rows size = ", position, rows()))
        #endif

        Matrix<T, STORAGE> mat(rows() + 1, cols());

        size_type count = 0;

        for(size_type i = 0; i < mat.rows(); ++i)
        {
            if( (i < position) || (i > position))
            {
                std::copy(begin_row(count), end_row(count), mat.begin_row(i));
                count++;
            }
            else if(i == position)
            {
                std::fill(mat.begin_row(i), mat.end_row(i), value);
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_row_impl_(size_type position, const std::vector<T>& vector)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position <= rows()), Bad_index("insert_row()", "position = ", "rows size = ", position, rows()))
            AXILIB_CHECK( vector.size() == cols(), Incosistent_columns() )
        #endif

        Matrix mat(rows() + 1, cols());

        size_type count = 0;

        for(size_type i = 0; i < mat.rows(); ++i)
        {
            if((i > position) || (i < position))
            {
                std::copy(begin_row(count), end_row(count), mat.begin_row(i));
                count++;
            }
            else
            {
                std::copy(vector.cbegin(), vector.cend(), mat.begin_row(i));
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_rows_impl_(size_type position, const Matrix<T>& other)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position <= rows()), Bad_index("insert_rows()", "position = ", "rows size = ", position, rows()))
            AXILIB_CHECK( other.cols() == cols(), Incosistent_columns() )
        #endif

        Matrix<T, STORAGE> mat(rows() + other.rows(), cols());

        size_type count_1 = 0;
        size_type count_2 = 0;
        size_type length = other.rows() + position;

        for(size_type i = 0; i < mat.rows(); ++i)
        {
            if( (((i <= position - 1) || (i > length - 1 )) && (position != 0)) ||
                (!((i >= position) && (i <= length - 1)) && (position == 0)) )
            {
                std::copy(begin_row(count_1), end_row(count_1), mat.begin_row(i));
                count_1++;
            }
            else
            {
                std::copy(other.cbegin_row(count_2), other.cend_row(count_2), mat.begin_row(i));
                count_2++;
            }
        }

        *this = mat;

    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_col_impl_(size_type position, value_type value)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position <= cols()), Bad_index("insert_col()", "position = ", "cols size = ", position, cols()))
        #endif

        Matrix<T, STORAGE> mat(rows(), cols() + 1);

        size_type count = 0;

        for(size_type i = 0; i < mat.cols(); ++i)
        {
            if( (i < position) || (i > position) )
            {
                std::copy(begin_col(count), end_col(count), mat.begin_col(i));
                count++;
            }
            else if(i == position)
            {
                std::fill(mat.begin_col(i), mat.end_col(i), value);
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_col_impl_(size_type position, const std::vector<T>& vector)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position <= cols()), Bad_index("insert_col()", "position = ", "cols size = ", position, cols()))
            AXILIB_CHECK( vector.size() == rows(), Incosistent_rows() )
        #endif

        Matrix<T> mat(rows(), cols() + 1);

        size_type count = 0;

        for(size_type i = 0; i < mat.cols(); ++i)
        {
            if((i > position) || (i < position))
            {
                std::copy(begin_col(count), end_col(count), mat.begin_col(i));
                count++;
            }
            else
            {
                std::copy(vector.cbegin(), vector.cend(), mat.begin_col(i));
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::insert_cols_impl_(size_type position, const Matrix& other)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position <= cols()), Bad_index("insert_cols()", "position = ", "cols size = ", position, cols()))
            AXILIB_CHECK( other.rows() == rows(), Incosistent_rows() )
        #endif

        Matrix<T, STORAGE> mat(rows(), cols() + other.cols());

        size_type count_1 = 0;
        size_type count_2 = 0;
        size_type length = other.cols() + position;

        for(size_type i = 0; i < mat.cols(); ++i)
        {
            if( (((i <= position - 1) || (i > length - 1 )) && (position != 0)) ||
                (!((i >= position) && (i <= length - 1)) && (position == 0)) )
            {
                std::copy(begin_col(count_1), end_col(count_1), mat.begin_col(i));
                count_1++;
            }
            else
            {
                std::copy(other.cbegin_col(count_2), other.cend_col(count_2), mat.begin_col(i));
                count_2++;
            }
        }

        *this = mat;
    }


    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_row_impl_(size_type position)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position < rows()), Bad_index("erase_row()", "position = ", "rows size = ", position, rows()))
        #endif

        Matrix<T, STORAGE> mat(rows() - 1, cols());
        size_type count = 0;

        for(size_type i = 0; i < rows(); ++i)
        {
            if(i != position)
            {
                std::copy(begin_row(i), end_row(i), mat.begin_row(count));
                count++;
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_rows_impl_(const Range& range)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (range.last() < rows()), Bad_index("erase_rows()", "last = ", "rows size = ", range.last(), rows()))
        #endif

        Matrix<T, STORAGE> mat(rows() - range.size(), cols());

        size_type count = 0;

        for(size_type i = 0; i < rows(); ++i)
        {
            if( !((i >= range.first()) && (i <= range.last())) )
            {
                std::copy(begin_row(i), end_row(i), mat.begin_row(count));
                count++;
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_col_impl_(size_type position)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (position >= 0) && (position < cols()), Bad_index("erase_col()", "position = ", "cols size = ", position, cols()))
        #endif

        Matrix<T, STORAGE> mat(rows(), cols() - 1);

        size_type count = 0;

        for(size_type i = 0; i < cols(); ++i)
        {
            if(i != position)
            {
                std::copy(begin_col(i), end_col(i), mat.begin_col(count));
                count++;
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::erase_cols_impl_(const Range& range)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( (range.last() < cols()), Bad_index("erase_cols()", "last = ", "cols size = ", range.last(), cols()))
        #endif

        Matrix<T, STORAGE> mat(rows(), cols() - range.size());

        size_type count = 0;

        for(size_type i = 0; i < cols(); ++i)
        {
            if( !((i >= range.first()) && (i <= range.last())) )
            {
                std::copy(begin_col(i), end_col(i), mat.begin_col(count));
                count++;
            }
        }

        *this = mat;
    }

    template<typename T, typename STORAGE>
        template<typename Iterator1, typename Iterator2>
        void
        Matrix<T, STORAGE>::swap_impl_(Iterator1 first_1, Iterator1 last_1, Iterator2 first_2, Iterator2 last_2)
        {
            std::vector<T> temp;
            std::copy(first_1, last_1, std::back_inserter(temp));
            std::copy(first_2, last_2, first_1);
            std::copy(temp.begin(), temp.end(), first_2);
        }

    template<typename T, typename STORAGE>
    typename Matrix<T, STORAGE>::value_type
    Matrix<T, STORAGE>::det_impl()
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK( is_square(), Bad_size("The matrix is not square") )
        #endif

        /*value_type n_1;
        value_type n_2;
        value_type total = 1;
        value_type determinant = 1;

        std::size_t index;

        Vector<Row, value_type> temp(rows() + 1);

        for(std::size_t i = 0; i < rows(); i++)
        {
            index = i;

            while(this->operator()(index, i) == 0 && index < rows())
            {
                index++;
            }

            if(index == rows())
            {
                continue;
            }

            if(index != i)
            {
                for(std::size_t j = 0; j < rows(); j++)
                {
                   std::swap(this->operator()(index, j), this->operator()(i, j));
                }

                determinant = determinant * std::pow(-1,index-i);
            }

            for(std::size_t j = 0; j < rows(); j++)
            {
                temp[j] = this->operator()(i, j);
            }

            for(std::size_t j = i+1; j < rows(); j++)
            {
                n_1 = temp[i];
                n_2 = this->operator()(j, i);

                for(std::size_t k = 0; k < rows(); k++)
                {
                     this->operator()(j, k) = (n_1 * this->operator()(j, k)) - (n_2 * temp[k]);
                }

                    total = total * n_1;
                }
            }

            for(std::size_t i = 0; i < rows(); i++)
            {
                determinant = determinant * this->operator()(i, i);
            }

        return (determinant/total);*/
    }

    template<typename T, typename STORAGE>
    void
    Matrix<T, STORAGE>::transform_to_square()
    {
        if(!is_square())
        {
           #ifndef AXILIB_USE_FIXED_MATRIX
                size_type size = rows() < cols() ? rows() : cols();
                resize(size, size);
           #else
               #error "Cannot be change the matrix size because the AXILIB_USE_FIXED_MATRIX macro is defined."
           #endif
        }
    }

}

#endif // BASE_TCC
