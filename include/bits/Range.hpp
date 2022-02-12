#ifndef RANGE_H
#define RANGE_H

#include <iostream>

#include "include/axi_config.hpp"
#include "Exceptions.hpp"

namespace axilib
{
    class Range
    {
    public:
        Range() :
            first_{},
            last_{} { }

        Range(std::size_t first, std::size_t last) :
            first_{first},
            last_{last}
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( (first_ <= last_), Bad_range(first_, last_) );
            #endif
        }

        Range(std::size_t value) :
            first_{value},
            last_{value} { }

        std::size_t first() const noexcept
        {
            return first_;
        }

        std::size_t last() const noexcept
        {
            return last_;
        }

        std::size_t size() const noexcept
        {
            return last_ - first_ + 1;
        }

    private:
        std::size_t first_;
        std::size_t last_;
    };

} // namespace axilib


#endif // RANGE_H
