#ifndef MAT_INITIALIZER_HPP
#define MAT_INITIALIZER_HPP

#include <iostream>
#include <vector>
#include <algorithm>

#include "Concepts.hpp"
#include "Size.tcc"
#include "Traits.hpp"
//#include "include/Exceptions/Exception.hpp"

namespace axilib
{
    template<typename T, typename Container>
    class Matrix_initializer
    {
    public:

        Matrix_initializer(Container container);

        Size get_size() const noexcept;

        std::vector<T> get_data() const noexcept;

    private:

        void check_dimension(Container container);

        void set_data(Container container);

        std::vector<T> data_;
        Size size_;
    };
}

#endif // MAT_INITIALIZER_HPP
