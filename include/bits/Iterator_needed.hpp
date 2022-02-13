#ifndef ITERATOR_NEEDED_H
#define ITERATOR_NEEDED_H

#include <iostream>
#include "Macros.hpp"
#include "Tags.hpp"

namespace axilib
{
    template<bool B, typename Iterator_1, typename Iterator_2>
    struct Iterator_needed
    {
        static constexpr Iterator_1 get(Iterator_1 it_1, Iterator_2 it_2)
        {
            AXILIB_UNUSED(it_2);

            return it_1;
        }
    };

    template<typename Iterator_1, typename Iterator_2>
    struct Iterator_needed<false, Iterator_1, Iterator_2>
    {
        static constexpr Iterator_2 get(Iterator_1 it_1, Iterator_2 it_2)
        {
            AXILIB_UNUSED(it_1);

            return it_2;
        }
    };
}

#endif // ITERATOR_NEEDED_H
