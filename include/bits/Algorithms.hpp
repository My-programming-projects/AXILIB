#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <type_traits>
#include <numeric>
#include <functional>

#include "Traits.hpp"
#include "Enums.hpp"
#include "Concepts.hpp"
#include "Square.hpp"

namespace axilib
{
    template<typename Iterator, typename T>
    void copy(Iterator first, Iterator last, T val)
    {
        for(auto iter = first; iter != last; ++iter)
        {
            *iter = val;
        }
    }

    template<typename Iterator>
    void copy(Iterator first, Iterator last, Iterator result)
    {
        for(auto iter = first; iter != last; ++iter, ++result)
        {
            *result = *iter;
        }
    }

    template<typename T, typename SortType>
    struct Sort_functor
    {
        bool operator()(const T& lhs, const T& rhs)
        {
            return std::is_same_v<SortType, Ascend> ? lhs < rhs : lhs > rhs;
        }
    };

    template<typename M>
    bool is_diagonal(const M& mat) noexcept
    {
        return Diagonal::is_type(mat);
    }

    template<typename M>
    bool is_banded(const M& mat) noexcept
    {
        return Banded::is_type(mat);
    }


    template<typename M, typename TT>
    bool is_triangular(const M& mat) noexcept
    {
        return TT::is_type(mat);
    }


 /*

    template<typename M>
    void
    transpose(M& m)
    {
        M mat(m.cols(), m.rows());

        for(std::size_t i = 0; i < m.cols(); ++i)
        {
            for(std::size_t j = 0; j < m.rows(); ++j)
                mat(i, j) = m(j, i);
        }

        m = std::move(mat);
    }*/

} // namespace axilib

#endif // ALGORITHMS_HPP
