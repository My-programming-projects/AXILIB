#ifndef SIZE_HPP
#define SIZE_HPP

#include <iostream>

namespace axilib
{
    class Size
    {

    public:
        using size_type = std::size_t;

        Size();

        Size(size_type rows, size_type cols);

        std::size_t rows() const noexcept;

        std::size_t cols() const noexcept;

        std::size_t total() const noexcept;

        size_type operator[](size_type n);

        bool operator>(const Size& rhs) const noexcept;

        bool operator<(const Size& rhs) const noexcept;

        bool operator==(const Size& rhs) const noexcept;

        bool operator!=(const Size& rhs) const noexcept;

        Size operator+(const Size& rhs);

        Size operator-(const Size& rhs);

        Size& operator+=(const Size& rhs);

        Size& operator-=(const Size& rhs);

        Size& operator+=(const size_type& rhs);

        Size& operator-=(const size_type& rhs);

        Size& operator*=(const size_type& rhs);

        Size& operator/=(const size_type& rhs);

    private:
        size_type rows_;
        size_type cols_;
    };

} // namespace axilib

#endif // SIZE_HPP
