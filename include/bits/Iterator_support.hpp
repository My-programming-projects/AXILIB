#ifndef ITERATOR_SUPPORT_H
#define ITERATOR_SUPPORT_H

#include <iostream>
#include "Tags.hpp"


namespace axilib::detail
{
    inline std::size_t first_element(std::size_t rows, std::size_t col, Col_iterator_tag)
    {
        return rows * col;
    }

    inline std::size_t first_element(std::size_t rows, std::size_t range_first_col, std::size_t range_first_row, Matrix_reference_iterator_tag)
    {
        return (rows * range_first_col) + range_first_row;
    }

    inline std::size_t last_element(std::size_t rows, std::size_t col, Col_iterator_tag)
    {
        return rows + (rows * col);
    }

    inline std::size_t last_element(std::size_t rows, std::size_t cols, std::size_t row, Row_iterator_tag)
    {
        return (rows * cols) + row;
    }

    inline std::size_t last_element(std::size_t rows, std::size_t cols, Diagonal_iterator_tag)
    {
        return (cols > rows) || (cols == rows) ? rows * (rows + 1) : (rows * cols) + cols;
    }

    inline std::size_t last_element(std::size_t rows, std::size_t cols)
    {
        return (cols > rows) || (cols == rows) ? rows * (rows + 1) : (rows * cols) + cols;
    }

    inline std::size_t last_element(std::size_t rows, std::size_t range_last_col, std::size_t range_last_row, std::size_t stride, Matrix_reference_iterator_tag)
    {
        return rows * range_last_col + range_last_row + stride;
    }

    inline std::size_t stride(std::size_t rows, std::size_t col, Col_iterator_tag)
    {
        return rows * col;
    }

    class Iterator_traversing
    {
    public:
        Iterator_traversing() :
            count_limit_{},
            count_{},
            real_stride_{1},
            stride_1_{},
            stride_2_{} { }

        Iterator_traversing(std::size_t count_limit, std::size_t stride_1, std::size_t stride_2) :
            count_limit_{count_limit},
            count_{},
            real_stride_{1},
            stride_1_{stride_1},
            stride_2_{stride_2} { }

            std::size_t next() noexcept
            {
                limit_check();
                return real_stride_;
            }

            std::size_t increment()
            {
                limit_check();
                return count_++;
            }

            std::size_t stride() const noexcept
            {
                return real_stride_;
            }

    private:
        void limit_check()
        {
            if(count_++ == count_limit_)
            {
                real_stride_ = stride_2_;
                count_ = 0;
            }
            else
            {
                real_stride_ = stride_1_;
            }
        }

        std::size_t count_limit_;
        std::size_t count_;
        std::size_t real_stride_;
        std::size_t stride_1_;
        std::size_t stride_2_;
    };

}

#endif // ITERATOR_SUPPORT_H
