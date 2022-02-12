#ifndef MATRIX_INITIALIZER_TCC
#define MATRIX_INITIALIZER_TCC

#include "Matrix_initializer.hpp"

namespace axilib
{
    template<typename T, typename Container>
    Matrix_initializer<T, Container>::Matrix_initializer(Container container)
    {
        check_dimension(container);
        set_data(container);
    }

    template<typename T, typename Container>
    Size
    Matrix_initializer<T, Container>::get_size() const noexcept
    {
        return size_;
    }

    template<typename T, typename Container>
    std::vector<T> Matrix_initializer<T, Container>::get_data() const noexcept
    {
        return data_;
    }

    template<typename T, typename Container>
    void
    Matrix_initializer<T, Container>::check_dimension(Container container)
    {
        std::size_t rows = container.size();
        std::vector<std::size_t> cols_num(rows);

        using sub_container = typename Is_initializer_list<T, typename Container::value_type>::type;

        std::transform(container.begin(), container.end(), cols_num.begin(), [](sub_container sc){ return sc.size(); });

        auto first_column = cols_num[0];
        std::size_t total = std::count_if(cols_num.begin(), cols_num.end(),
                                          [first_column](std::size_t x){ return x == first_column; });

        #ifdef AXILIB_THROW_EXCEPTIONS
            AXILIB_CHECK(total == rows, Incosistent_columns())
        #endif

        size_ = Size{rows, cols_num[0]};
    }

    template<typename T, typename Container>
    void
    Matrix_initializer<T, Container>::set_data(Container container)
    {
        data_.resize(size_.rows() * size_.cols());
        std::size_t i = 0;

        for(auto iter = container.begin(); iter != container.end(); ++iter, ++i)
        {
            std::size_t j = 0;

            for(auto iter_2 = iter->begin(); iter_2 != iter->end(); ++iter_2, ++j)
            {
                data_[size_.rows() * j + i] = *iter_2;
            }
        }
    }


} // namespace linarg

#endif // MATRIX_INITIALIZER_TCC
