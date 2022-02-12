#ifndef BASE_EXPERIMENTAL_HPP
#define BASE_EXPERIMENTAL_HPP

#include "Size.hpp"
#include "Iterator.hpp"

namespace axilib
{
    template<typename Iterator, typename ConstIterator, typename RowIterator, typename ConstRow, typename ColIterator,
             typename ConstCol, typename DiagIterator, typename ConstDiag>
    struct Iterators
    {
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        using row_iterator = RowIterator;
        using const_row_iterator = ConstRow;
        using col_iterator = ColIterator;
        using const_col_iterator = ConstCol;
        using diag_iterator = DiagIterator;
        using const_diag_iterator = ConstDiag;
    };

    template<typename STORAGE, typename ITERATORS>
    class Base_experimental
    {
    public:

        using storage_type  = STORAGE;

        using size_type     = typename storage_type::size_type;

        using value_type                = typename storage_type::value_type;
        using reference                 = typename storage_type::reference;
        using const_reference           = typename storage_type::const_reference;
        using pointer                   = typename storage_type::pointer;

        using iterators                 = ITERATORS;

        using iterator                  = typename iterators::iterator;
        using const_iterator             = typename iterators::const_iterator;
        using row_iterator              = typename iterators::row_iterator;
        using const_row_iterator        = typename iterators::const_row_iterator;
        using col_iterator              = typename iterators::col_iterator;
        using const_col_iterator        = typename iterators::const_col_iterator;
        using diagonal_iterator         = typename iterators::diag_iterator;
        using const_diagonal_iterator   = typename iterators::const_diag_iterator;

        Base_experimental(storage_type& data, Size& size);

        size_type rows() const noexcept;

        size_type cols() const noexcept;

        Size size() const noexcept;

        iterator begin();

        const_iterator cbegin() const noexcept;

        iterator end();

        const_iterator cend() const noexcept;

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

    private:
        storage_type& data_;

        Size& size_;
};



} // namespace axilib

#endif // BASE_EXPERIMENTAL_HPP
