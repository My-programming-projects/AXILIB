#ifndef BASE_EXPERIMENTAL_TCC
#define BASE_EXPERIMENTAL_TCC

#include "Base_experimental.hpp"

namespace axilib
{
    template<typename STORAGE, typename ITERATORS>
    Base_experimental<STORAGE, ITERATORS>::Base_experimental(storage_type& data, Size& size) :
        data_{data},
        size_{size} { }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::size_type
    Base_experimental<STORAGE, ITERATORS>::rows() const noexcept
    {
        return size_.rows();
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::size_type
    Base_experimental<STORAGE, ITERATORS>::cols() const noexcept
    {
        return size_.cols();
    }


    template<typename STORAGE, typename ITERATORS>
    Size
    Base_experimental<STORAGE, ITERATORS>::size() const noexcept
    {
        return size_;
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::iterator
    Base_experimental<STORAGE, ITERATORS>::begin()
    {
        return data_.begin();
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_iterator
    Base_experimental<STORAGE, ITERATORS>::cbegin() const noexcept
    {
        return data_.cbegin();
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::iterator
    Base_experimental<STORAGE, ITERATORS>::end()
    {
        return data_.end();
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_iterator
    Base_experimental<STORAGE, ITERATORS>::cend() const noexcept
    {
        return data_.cend();
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::row_iterator
    Base_experimental<STORAGE, ITERATORS>::begin_row(size_type row)
    {
        return row_iterator(begin() + row, rows());
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_row_iterator
    Base_experimental<STORAGE, ITERATORS>::cbegin_row(size_type row) const
    {
        return const_row_iterator(cbegin() + row, rows());
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::row_iterator
    Base_experimental<STORAGE, ITERATORS>::end_row(size_type row)
    {
        size_type last = detail::last_element(rows(), cols(), row, Row_iterator_tag{});

        return row_iterator(begin() + last, rows());
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_row_iterator
    Base_experimental<STORAGE, ITERATORS>::cend_row(size_type row) const
    {
        size_type last = detail::last_element(rows(), cols(), row, Row_iterator_tag{});

        return const_row_iterator(cbegin() + last, rows());
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::col_iterator
    Base_experimental<STORAGE, ITERATORS>::begin_col(size_type col)
    {
        size_type first = detail::first_element(rows(), col, Col_iterator_tag{});

        return col_iterator(begin() + first, 1);
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_col_iterator
    Base_experimental<STORAGE, ITERATORS>::cbegin_col(size_type col) const
    {
        size_type first = detail::first_element(rows(), col, Col_iterator_tag{});

        return const_col_iterator(cbegin() + first, 1);
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::col_iterator
    Base_experimental<STORAGE, ITERATORS>::end_col(size_type col)
    {
        size_type last = detail::last_element(rows(), col, Col_iterator_tag{});

        return col_iterator(begin() + last, 1);
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_col_iterator
    Base_experimental<STORAGE, ITERATORS>::cend_col(size_type col) const
    {
        size_type last = detail::last_element(rows(), col, Col_iterator_tag{});

        return const_col_iterator(cbegin() + last, 1);
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::diagonal_iterator
    Base_experimental<STORAGE, ITERATORS>::begin_diag()
    {
        return diagonal_iterator(begin(), size_.rows() + 1);
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_diagonal_iterator
    Base_experimental<STORAGE, ITERATORS>::cbegin_diag() const
    {
        return const_diagonal_iterator(cbegin(), size_.rows() + 1);
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::diagonal_iterator
    Base_experimental<STORAGE, ITERATORS>::end_diag()
    {
        size_type last = detail::last_element(size_.rows(), size_.cols(), Diagonal_iterator_tag{});

        return diagonal_iterator(begin() + last, rows() + 1);
    }

    template<typename STORAGE, typename ITERATORS>
    typename Base_experimental<STORAGE, ITERATORS>::const_diagonal_iterator
    Base_experimental<STORAGE, ITERATORS>::cend_diag() const
    {
        size_type last = detail::last_element(size_.rows(), size_.cols(), Diagonal_iterator_tag{});

        return diagonal_iterator(cbegin() + last, rows() + 1);
    }

} // namespace axilib


#endif // BASE_EXPERIMENTAL_TCC
