#ifndef DELETED_HPP
#define DELETED_HPP

#include <numeric>

class Deleted
{
public:

    Deleted() :
        row_{},
        col_{} { }

    Deleted(std::size_t row, std::size_t col) :
        row_{row},
        col_{col} { }

    std::size_t row() const noexcept
    {
        return row_;
    }

    std::size_t col() const noexcept
    {
        return col_;
    }

private:
    std::size_t row_;
    std::size_t col_;
};

#endif // DELETED_HPP
