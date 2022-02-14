#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <math.h>
#include <complex>

#include "Iterator.hpp"
#include "Matrix_reference.tcc"
#include "Math.hpp"
#include "Algorithms.hpp"
#include "Vector.tcc"
#include "Iterator_needed.hpp"
#include "From_string.tcc"
#include "Matrix_initializer.tcc"
#include "Square.hpp"
#include "include/axi_config.hpp"

namespace axilib
{
    template<typename T, typename STORAGE = std::vector<T>>
    class Matrix
    {
        static_assert (std::is_arithmetic<T>::value || Is_complex<T>::value, "Uncorrect type");

    private:

        using self_type                 = Matrix<T, STORAGE>;

    public:

        using type                              = Matrix_tag;

        using storage_type                      = STORAGE;
        using value_type                        = T;
        using reference                         = T&;
        using const_reference                   = const T&;
        using pointer                           = T*;
        using const_pointer                     = const T*;

        using iterator                          = typename storage_type::iterator;
        using const_iterator                    = typename storage_type::const_iterator;
        using reverse_iterator                  = typename storage_type::reverse_iterator;
        using const_reverse_iterator            = typename storage_type::const_reverse_iterator;
        using col_iterator                      = Matrix_iterator<iterator, Col_iterator_tag>;
        using const_col_iterator                = Matrix_iterator<const_iterator, Col_iterator_tag>;
        using reverse_col_iterator              = Reverse_matrix_iterator<col_iterator, Reverse_col_iterator_tag>;
        using const_reverse_col_iterator        = Reverse_matrix_iterator<col_iterator, Reverse_col_iterator_tag>;
        using row_iterator                      = Matrix_iterator<iterator, Row_iterator_tag>;
        using const_row_iterator                = Matrix_iterator<const_iterator, Row_iterator_tag>;
        using reverse_row_iterator              = Reverse_matrix_iterator<row_iterator, Reverse_row_iterator_tag>;
        using const_reverse_row_iterator        = Reverse_matrix_iterator<row_iterator, Reverse_row_iterator_tag>;
        using diagonal_iterator                 = Matrix_iterator<iterator, Diagonal_iterator_tag>;
        using const_diagonal_iterator           = Matrix_iterator<const_iterator, Diagonal_iterator_tag>;
        using reverse_diagonal_iterator         = Reverse_matrix_iterator<diagonal_iterator, Reverse_diagonal_iterator_tag>;
        using const_reverse_diagonal_iterator   = Reverse_matrix_iterator<diagonal_iterator, Reverse_diagonal_iterator_tag>;

        using difference_type                   = typename storage_type::difference_type;
        using size_type                         = std::size_t;
        using allocator_type                    = typename storage_type::allocator_type;


        Matrix();

        Matrix(size_type req_rows, size_type req_cols);

        Matrix(const Size& mat_size);

        Matrix(std::initializer_list<value_type> list);

        Matrix(std::initializer_list<std::initializer_list<value_type>> list);

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        Matrix(size_type rows, size_type cols, Function function);

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        Matrix(const Size& size, Function function);

        Matrix(const std::string& expr);

        Matrix(const Matrix& copy);

        template<typename U>
        Matrix(const Matrix<U>&) = delete;

        template<typename U>
        Matrix(Matrix<U>&&) = delete;

        Matrix(Matrix&& move);

        Matrix& operator=(const Matrix& rhs);

        Matrix& operator=(Matrix&& rhs);

        template<typename U>
        Matrix& operator=(const Matrix<U>&) = delete;

        template<typename U>
        Matrix& operator=(Matrix<U>&&) = delete;

        allocator_type get_allocator() const noexcept;

        size_type rows() const noexcept;

        size_type cols() const noexcept;

        Size size() const noexcept;

        bool empty() const noexcept;

        reference operator[](size_type n);

        const_reference operator[](size_type n) const;

        reference operator()(size_type i, size_type j);

        const_reference operator()(size_type i, size_type j) const;

        reference at(size_type i, size_type j);

        const_reference at(size_type i, size_type j) const;

        pointer data() noexcept;

        const_pointer data() const noexcept;

        iterator begin();

        const_iterator cbegin() const noexcept;

        iterator end();

        const_iterator cend() const noexcept;

        reverse_iterator rbegin();

        const_reverse_iterator crbegin() const noexcept;

        reverse_iterator rend();        

        const_reverse_iterator crend() const noexcept;

        col_iterator begin_col(size_type col);

        const_col_iterator cbegin_col(size_type col) const;

        col_iterator end_col(size_type col);

        const_col_iterator cend_col(size_type col) const;

        reverse_col_iterator rbegin_col(size_type col);

        const_reverse_col_iterator crbegin_col(size_type col) const;

        reverse_col_iterator rend_col(size_type col);

        const_reverse_col_iterator crend_col(size_type col) const;

        row_iterator begin_row(size_type row);

        const_row_iterator cbegin_row(size_type row) const;

        row_iterator end_row(size_type row);

        const_row_iterator cend_row(size_type row) const;

        reverse_row_iterator rbegin_row(size_type row);

        const_reverse_row_iterator crbegin_row(size_type row) const;

        reverse_row_iterator rend_row(size_type row);

        const_reverse_row_iterator crend_row(size_type row) const;

        diagonal_iterator begin_diag();

        const_diagonal_iterator cbegin_diag() const noexcept;

        diagonal_iterator end_diag();

        const_diagonal_iterator cend_diag() const noexcept;

        reverse_diagonal_iterator rbegin_diag();

        const_reverse_diagonal_iterator crbegin_diag() const noexcept;

        reverse_diagonal_iterator rend_diag();

        const_reverse_diagonal_iterator crend_diag() const noexcept;

        value_type det();

        Matrix_reference<T, STORAGE> submatrix(size_type first_row, size_type last_row, size_type first_col, size_type last_col);

        Matrix_reference<T, STORAGE> submatrix(const Range& rows, const Range& cols);

        void set_fixed();

        void clear();

        void fill_zeros();

        void fill_ones();

        void fill_eye();

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        void imbue(Function function);

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        void imbue_row(Function function, size_type row);

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        void imbue_col(Function function, size_type col);

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        void imbue_diag(Function function);

        size_type zeros() noexcept;

        size_type zeros_in_row(size_type row);

        size_type zeros_in_col(size_type col);

        size_type zeros_in_diag() noexcept;

        T accumulate();

        T accumulate_col(size_type col);

        T accumulate_row(size_type row);

        T accumulate_diag() noexcept;

        template<typename SD>
        void sort_row(size_type row);

        template<typename SD>
        void sort_col(size_type col);

        template<typename SD>
        void sort_diag();

        template<typename RO>
        void rotate(size_type step);

        template<typename RO, typename = std::enable_if_t<Has_rotate_tag<RO>::value>>
        void rotate_row(size_type row, size_type seq);

        template<typename RO, typename = std::enable_if_t<Has_rotate_tag<RO>::value>>
        void rotate_col(size_type col, size_type seq);

        template<typename RO, typename = std::enable_if_t<Has_rotate_tag<RO>::value>>
        void rotate_diag(size_type seq);

        void replace(const T& old_value, const T& new_value);

        template<typename Pred>
        void replace_if(Pred pred, const value_type& new_value);

        void replace_in_row(size_type row, const T& old_value, const T& new_value);

        template<typename Pred>
        void replace_in_row_if(size_type row, Pred pred, const T& new_value);

        void replace_in_col(size_type col, const T& old_value, const T& new_value);

        template<typename Pred>
        void replace_in_col_if(size_type col, Pred pred, const value_type& new_value);

        void replace_in_diag(const T& old_value, const T& new_value);

        template<typename Pred>
        void replace_in_diag_if(Pred pred, const value_type& new_value);

        Vector<Row, T> row(size_type row);

        Vector<Col, T> col(size_type col);

        std::vector<T> diag() noexcept;

        void row(size_type row, const Vector<Row, T>& vector);

        void col(size_type col, const Vector<Col, T>& vector);

        void diag(const std::vector<T>& vector);

        bool is_empty() const noexcept;

        bool is_square() const noexcept;

        bool is_diagonal() const noexcept;

        bool is_banded() const noexcept;

        template<typename TT, typename = std::enable_if_t< std::is_same_v<TT, Lower> ||
                                                           std::is_same_v<TT, Upper>> >
        bool is_triangular() const noexcept;

        template<typename SD>
        bool is_sorted() const noexcept;

        template<typename SD>
        bool is_sorted_row(size_type row) const;

        template<typename SD>
        bool is_sorted_col(size_type col) const;

        template<typename SortDir>
        bool is_sorted_diag() const noexcept;

        void to_banded(value_type value = value_type{});

        template<typename TT, typename = std::enable_if_t< std::is_same_v<TT, Lower> || std::is_same_v<TT, Upper> >>
        void to_triangular(value_type value = value_type{});

#ifndef AXI_USE_FIXED_MATRIX

        void resize(size_type rows, size_type cols);

        void resize(const Size& size);

        void resize_rows(size_type new_rows);

        void resize_cols(size_type new_cols);

        void insert_row(size_type position, value_type value = {});

        void insert_row(size_type position, const Vector<Row, T>& vector);

        void insert_rows(size_type position, const Matrix& other);

        void insert_col(size_type position, value_type value = {});

        void insert_col(size_type position, const Vector<Col, T>& vector);

        void insert_cols(size_type position, const Matrix& other);

        void erase_row(size_type position);

        void erase_rows(size_type first, size_type last);

        void erase_rows(const Range& range);

        void erase_col(size_type position);

        void erase_cols(size_type first, size_type last);

        void erase_cols(const Range& range);

#endif

        void swap_rows(size_type row_1, size_type row_2);

        void swap_rows(Matrix<T>& other, size_type row_1, size_type row_2);

        void swap_cols(size_type col_1, size_type col_2);

        void swap_cols(Matrix& other, size_type col_1, size_type col_2);

        Matrix<T, STORAGE>& operator+=(const Matrix<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator-=(const Matrix<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator*=(const Matrix<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator^=(const Matrix<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator/=(const Matrix<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator+=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator-=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator*=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator^=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator/=(const Matrix_reference<T, STORAGE>& rhs);

        Matrix<T, STORAGE>& operator+=(const value_type& rhs);

        Matrix<T, STORAGE>& operator-=(const value_type& rhs);

        Matrix<T, STORAGE>& operator*=(const value_type& rhs);

        Matrix<T, STORAGE>& operator/=(const value_type& rhs);

    private:

        void set_size(const Size& mat_size);

        size_type get_new_size(size_type old_size, size_type new_size);

        void set_array(const std::vector<T> &data);

        void copy_impl_(Matrix& other, From_other);

        void copy_impl_(Matrix& other, size_type r, size_type c, From_other);

        void copy_impl_(std::initializer_list<value_type> list, From_list);

        template<typename Container>
        void copy_impl_(Container container, From_container);

        template<typename Function>
        void copy_impl_(Function function, From_functor);

        template<typename U>
        void fill_impl_(U value);

        template<typename Iterator>
        void rotate_impl_(Iterator first, Iterator last, size_type seq);

        template<typename Iterator, typename SortType>
        bool is_sorted_impl_(Iterator first, Iterator last) const noexcept;

        template<typename Iterator, typename SortType>
        void sort_impl_(Iterator first, Iterator last);

        void insert_row_impl_(size_type position, value_type value);

        void insert_row_impl_(size_type position, const Vector<Row, T>& vector);

        void insert_rows_impl_(size_type position, const Matrix<T>& other);

        void insert_col_impl_(size_type position, value_type value);

        void insert_col_impl_(size_type position, const Vector<Col, T>& vector);

        void insert_cols_impl_(size_type position, const Matrix& other);

        void erase_row_impl_(size_type position);

        void erase_rows_impl_(const Range& range);

        void erase_col_impl_(size_type position);

        void erase_cols_impl_(const Range& range);

        template<typename Iterator1, typename Iterator2>
        void swap_impl_(Iterator1 first_1, Iterator1 last_1, Iterator2 first_2, Iterator2 last_2);

        void transform_to_square();


        storage_type data_;

        Size size_;
    };
}

#endif // MATRIX_H
