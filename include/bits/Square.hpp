#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <numeric>
#include <vector>
#include <tuple>

namespace axilib
{
    namespace detail
    {
        template<std::size_t N, typename... Ts>
        using selected_type = typename std::tuple_element<N, std::tuple<Ts...>>::type;

        template<typename T>
        struct Equal_to
        {
            bool operator()(const T& lhs, const T& rhs)
            {
                return lhs != rhs && ((lhs - 1) != rhs) && ((lhs + 1) != rhs);
            }
        };

        template<std::size_t N, typename T>
        struct Compare_select
        {
            using type = selected_type<N, std::less<std::size_t>, std::greater<std::size_t>,
                                          std::not_equal_to<std::size_t>, Equal_to<std::size_t> >;
        };

        template<std::size_t N>
        struct Square
        {
            template<typename C>
            static void fill(std::size_t rows, std::size_t cols, C& storage, typename C::value_type value = typename C::value_type{})
            {
                using value_type = typename C::value_type;
                typename Compare_select<N, value_type>::type pred;

                for(std::size_t i = 0; i < rows; ++i)
                {
                    for(std::size_t j = 0; j < cols; ++j)
                    {
                        value_type v_1 = value != value_type{} ? value : storage[rows * j + i];
                        value_type v_2 = pred(i, j) ? value_type{} : v_1;
                        storage[rows * j + i] = v_2;
                    }
                }
            }

            template<typename M>
            static bool is_type(const M& mat)
            {
                if(!mat.is_square())
                {
                    return false;
                }

                using value_type = typename M::value_type;
                typename Compare_select<N, value_type>::type pred;

                for(std::size_t i = 0; i < mat.rows(); ++i)
                {
                    for(std::size_t j = 0; j < mat.cols(); ++j)
                    {
                        bool equal = pred(i, j) ? mat(i, j) == value_type{} : mat(i, j) != value_type{};

                        if(!equal)
                        {
                            return false;
                        }

                        /*if(pred(i, j))
                        {
                            if(mat(i, j) != value_type{})
                            {
                                return false;
                            }
                        }

                        if(!pred(i, j))
                        {
                            if(mat(i, j) == value_type{})
                            {
                                return false;
                            }
                        }*/
                    }
                }

                return true;
            }
        };

    } // namespace detail

    using Lower    = detail::Square<0>;
    using Upper    = detail::Square<1>;
    using Diagonal = detail::Square<2>;
    using Banded   = detail::Square<3>;

} // namespace axilib

#endif // SQUARE_HPP
