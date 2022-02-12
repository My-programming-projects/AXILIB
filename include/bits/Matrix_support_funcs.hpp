#ifndef MATRIX_SUPPORT_FUNCS_HPP
#define MATRIX_SUPPORT_FUNCS_HPP

#include <algorithm>
#include <numeric>
#include "Traits.hpp"
#include "Concepts.hpp"

namespace axilib::detail
{
    template<typename Iterator, typename Func>
    void imbue_impl(Iterator first, Iterator last, Func function)
    {
        for(auto it = first; it < last; ++it)
        {
            *it = function();
        }
    }

    template<typename M, typename T = typename M::value_type>
    void fill_eye_impl(M& mat, const T& value)
    {
        std::size_t end = mat.rows() > mat.cols() ? mat.cols() : mat.rows();

        for(std::size_t i = 0; i < end; ++i)
        {
            mat(i, i) = traits::In_type<Is_complex<T>::value, T>::value(value);
        }
    }

    template<typename Iterator, typename Pred, typename T = typename Iterator::value_type>
    void replace_impl(Iterator first, Iterator last, const T& new_value, Pred pred)
    {
        std::replace_if(first, last, pred, new_value);
    }

    template<typename Iterator>
    std::size_t count_zeros_impl(Iterator first, Iterator last)
    {
        using value_type = typename Ptr_val< Is_iterator<Iterator>::value, Iterator >::type;

        return std::count_if(first, last, [](value_type value){ return traits::Zero<Is_complex<value_type>::value, value_type>::has_value(value); });
    }

    template<typename Iterator, typename T = typename Iterator::value_type>
    T accumulate_impl(Iterator first, Iterator last)
    {
        return std::accumulate(first, last, T{});
    }

    template<typename Iterator>
    std::pair<Iterator, Iterator> index_min_max_impl(Iterator first, Iterator last)
    {
        const auto [min, max] = std::minmax_element(first, last);

        return {min, max};
    }

} // namespace axilib::detail

#endif // MATRIX_SUPPORT_FUNCS_HPP
