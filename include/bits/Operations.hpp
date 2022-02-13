#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "include/axi_config.hpp"
#include "Axilib_compare.hpp"
#include "Size.hpp"
#include "include/bits/Traits.hpp"
#include "include/bits/Exceptions.hpp"

#include <iostream>
#include <functional>

namespace axilib::op
{
    struct Op_vector { };
    struct Op_matrix { };
    struct Op_mat_vec { };

    template<typename LHS, typename RHS, typename OpType>
    struct Multiplies;

    template<typename L, typename R, typename OpType>
    struct Equal;

    //

    template<typename LHS, typename RHS, typename Op, typename OpType>
    struct Binary_op;

    template<typename LHS, typename RHS, typename Op, typename OpType>
    struct Binary_op_scalar;

    //

    template<typename LHS, typename RHS, typename Op>
    struct Binary_op<LHS, RHS, Op, Op_matrix>
    {
        void operator()(LHS& lhs, const RHS& rhs)
        {
            auto lhs_iter = lhs.begin();
            auto rhs_iter = rhs.cbegin();

            Op op;

            while(lhs_iter < lhs.cend())
            {
                *lhs_iter = op(*lhs_iter, *rhs_iter);

                lhs_iter++;
                rhs_iter++;
            }
        }
    };

    template<typename LHS, typename RHS, typename Op>
    struct Binary_op_scalar<LHS, RHS, Op, Op_matrix>
    {

        void operator()(LHS& lhs, const RHS& scalar)
        {
            if(std::is_same_v<Op, std::divides<RHS>>)
            {
                bool is_zero = traits::Zero<Is_complex<RHS>::value, RHS>::has_value(scalar);

                #ifdef AXILIB_THROW_EXCEPTIONS
                    AXILIB_CHECK( !is_zero, Divide_by_zero("Scalar divide") )
                #endif
            }

            Op op;

            auto lhs_iter = lhs.begin();

            while(lhs_iter < lhs.end())
            {
                *lhs_iter = op(*lhs_iter, scalar);

                lhs_iter++;
            }
        }
    };

    template<typename LHS, typename RHS, typename Op>
    struct Binary_op<LHS, RHS, Op, Op_vector>
    {

        void operator()(LHS& lhs, const RHS& rhs)
        {
            Op op;

            for(std::size_t i = 0; i < lhs.size(); ++i)
            {
                lhs[i] = op(lhs[i], rhs[i]);
            }
        }
    };

    template<typename LHS, typename RHS, typename Op>
    struct Binary_op_scalar<LHS, RHS, Op, Op_vector>
    {

        void operator()(LHS& lhs, const RHS& scalar)
        {
            if(std::is_same_v<Op, std::divides<RHS>>)
            {
                bool is_zero = traits::Zero<Is_complex<RHS>::value, RHS>::has_value(scalar);

                #ifdef AXILIB_THROW_EXCEPTIONS
                    AXILIB_CHECK( !is_zero, Divide_by_zero("Scalar divide") )
                #endif
            }

            Op op;

            for(std::size_t i = 0; i < lhs.size(); ++i)
            {
                lhs[i] = op(lhs[i], scalar);
            }
        }
    };

    template<typename LHS, typename RHS>
    struct Multiplies<LHS, RHS, Op_matrix>
    {
        using result_type = LHS;

        result_type operator()(const LHS& lhs, const RHS& rhs)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK( (lhs.rows() == rhs.cols()) && (lhs.cols() == rhs.rows()), Incompatible_size() )
            #endif

            using value_type = typename LHS::value_type;
            result_type result(lhs.rows(), rhs.cols());

            for(std::size_t i = 0; i < lhs.rows(); ++i)
            {
                for(std::size_t j = 0; j < rhs.cols(); ++j)
                {
                    value_type val = 0;

                    for(std::size_t k = 0; k < lhs.cols(); ++k)
                    {
                        val += lhs(i, k) * rhs(k, j);
                    }

                    result(i, j) = val;
                }
            }

            return result;
        }
    };

    template<typename LHS, typename RHS>
    struct Multiplies<LHS, RHS, Op_vector>
    {
        using result_type    = typename LHS::value_type;

        result_type operator()(const LHS& lhs, const RHS& rhs)
        {
            #ifdef AXILIB_THROW_EXCEPTIONS
                AXILIB_CHECK(lhs.size() == rhs.size(), Incompatible_size("Multiplies(): incompatible vectors sizes: ", lhs.size(), rhs.size()))
            #endif

            result_type value;

            for(std::size_t i = 0; i < lhs.size(); ++i)
            {
                value += lhs[i] * rhs[i];
            }

            return value;
        }
    };

    template<typename LHS, typename RHS>
    struct Multiplies<LHS, RHS, Op_mat_vec>
    {
        using result_type = RHS;

        result_type operator()(const LHS& lhs, const RHS& rhs)
        {
            result_type result(lhs.rows());

            for(std::size_t i = 0; i < lhs.rows(); ++i)
            {
                std::size_t count = 0;

                for(auto row_iter = lhs.cbegin_row(i); row_iter != lhs.cend_row(i); ++row_iter, ++count)
                {
                    result[i]+= *row_iter * rhs[count];
                }
            }

            return result;
        }
    };

    template<typename LHS, typename RHS>
    struct Equal<LHS, RHS, Op_matrix>
    {
        using rhs_type      = RHS;

        bool operator()(const LHS& lhs, const RHS& rhs)
        {
            if(lhs.size() != rhs.size())
            {
                return false;
            }

            using value_type = typename LHS::value_type;

            auto lhs_iter = lhs.cbegin();
            auto rhs_iter = rhs.cbegin();

            while(lhs_iter < lhs.cend())
            {
                typename std::conditional_t<std::is_integral_v<value_type>,
                         std::equal_to<value_type>, Almost_equal<value_type>> equal;

                if(!equal(*lhs_iter, *rhs_iter))
                {
                    return false;
                }

                lhs_iter++;
                rhs_iter++;
            }

            return true;
        }
    };

    template<typename LHS, typename RHS>
    struct Equal<LHS, RHS, Op_vector>
    {
        bool operator()(const LHS& lhs, const RHS& rhs)
        {
            if(lhs.size() != rhs.size())
            {
                return false;
            }

            using value_type = typename LHS::value_type;

            auto lhs_iter = lhs.cbegin();
            auto rhs_iter = rhs.cbegin();

            typename std::conditional_t<std::is_integral_v<value_type>,
                     std::equal_to<value_type>, Almost_equal<value_type>> equal;

            while(lhs_iter < lhs.cend())
            {
                if(!equal(*lhs_iter, *rhs_iter))
                {
                    return false;
                }

                lhs_iter++;
                rhs_iter++;
            }

            return true;
        }
    };

} // namespace axilib

#endif // OPERATIONS_HPP
