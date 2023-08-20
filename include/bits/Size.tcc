#ifndef MATRIX_SIZE_TCC
#define MATRIX_SIZE_TCC

#include "Size.hpp"

namespace axilib
{
    Size::Size() :
        rows_{},
        cols_{} { }

    Size::Size(size_type rows, size_type cols) :
        rows_{rows},
        cols_{cols} { }

    std::size_t
    Size::rows() const noexcept
    {
        return rows_;
    }

    std::size_t
    Size::cols() const noexcept
    {
        return cols_;
    }

    std::size_t
    Size::total() const noexcept
    {
        return (rows_ * cols_);
    }

    typename Size::size_type
    Size::operator[](size_type n)
    {
        return (n == 0 ? rows_ : cols_);
    }

    bool
    Size::operator>(const Size& rhs) const noexcept
    {
        return total() > rhs.total();
    }

    bool
    Size::operator<(const Size& rhs) const noexcept
    {
        return total() < rhs.total();
    }

    bool
    Size::operator==(const Size& rhs) const noexcept
    {
        return total() == rhs.total();
    }

    bool
    Size::operator!=(const Size& rhs) const noexcept
    {
        return !(this->operator==(rhs));
    }

    Size&
    Size::operator+=(const Size& rhs)
    {
        cols_ += rhs.cols_;
        rows_ += rhs.rows_;

        return *this;
    }

    Size&
    Size::operator-=(const Size& rhs)
    {
        cols_ -= rhs.cols_;
        rows_ -= rhs.rows_;

        return *this;
    }

    Size&
        Size::operator*=(const Size& rhs)
    {
        cols_ *= rhs.cols_;
        rows_ *= rhs.rows_;

        return *this;
    }

    Size&
    Size::operator /=(const Size& rhs)
    {
        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK(rhs.rows() != 0, Divide_by_zero("Size::operator/=(Size&)"))
            AXILIB_CHECK(rhs.cols() != 0, Divide_by_zero("Size::operator/=(Size&)"))
        #endif

        cols_ /= rhs.cols_;
        rows_ /= rhs.rows_;

        return *this;
    }

    Size&
    Size::operator+=(const size_type& rhs)
    {
        cols_ += rhs;
        rows_ += rhs;

        return *this;
    }

    Size&
    Size::operator-=(const size_type& rhs)
    {
        cols_ -= rhs;
        rows_ -= rhs;

        return *this;
    }

    Size&
    Size::operator*=(const size_type& rhs)
    {
        cols_ *= rhs;
        rows_ *= rhs;

        return *this;
    }

    Size&
    Size::operator/=(const size_type& rhs)
    {
        cols_ /= rhs;
        rows_ /= rhs;

        return *this;
    }

} // namespace axilib

#endif // MATRIX_SIZE_TCC
