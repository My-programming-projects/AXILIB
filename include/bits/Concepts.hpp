#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <type_traits>
#include <vector>

#include "Tags.hpp"
#include "Square.hpp"

namespace axilib
{

    //////////////////////////////////////////////

    template<typename T>
    struct Has_rotate_order
    {
        static constexpr bool value = std::is_same_v<T, Left> || std::is_same_v<T, Right>;
    };

    template<typename T>
    concept Requires_rotate_order = Has_rotate_order<T>::value;

    //////////////////////////////////////////////

    template<typename T, typename C>
    struct Is_initializer_list : std::false_type
    {
        using type = std::vector<T>;
    };

    template<typename T>
    struct Is_initializer_list<T, std::initializer_list<T>> : public std::true_type
    {
        using type = std::initializer_list<T>;
    };


    template<typename T, typename = void>
    struct Is_complex : std::false_type { };

    template<typename T>
    struct Is_complex<T, std::conditional_t<false, std::void_t < typename T::value_type,
                                                                 decltype(std::declval<T>().real()),
                                                                 decltype(std::declval<T>().imag())
                                                               >, void
                                                               > > : public std::true_type { };


    ////////////////////////////////////////////////

    template<typename T>
    struct Is_functor
    {
        typedef char true_t[1];
        typedef char false_t[2];

        template<typename U> static true_t& check(decltype(&U::operator()));
        template<typename U> static false_t& check(...);

        static constexpr bool value = ( sizeof(check<T>(0)) == sizeof(true_t) );
    };

    template<typename T>
    concept Requires_functor = Is_functor<T>::value;


    ////////////////////////////////////////////////

    template<typename T>
    struct Is_row_or_col
    {
        static constexpr bool value = std::is_same_v<T, Row> || std::is_same_v<T, Col>;
    };

    template<typename T>
    constexpr bool is_row_or_col()
    {
        return Is_row_or_col<T>::value;
    }

    template<typename T>
    struct Is_matrix
    {
        static constexpr bool value = std::is_same_v<T, Matrix_tag> || std::is_same_v<T, Submatrix_tag>;
    };

    template<typename T, typename = void>
    struct Is_iterator : std::false_type { };

    template<typename T>
    struct Is_iterator<T, std::conditional_t<false, std::void_t< typename T::iterator_category,
                                                                 typename T::value_type,
                                                                 typename T::reference,
                                                                 typename T::pointer,
                                                                 typename T::difference_type >, void>
                                                               > : public std::true_type { };

    template<bool B, typename T>
    struct Ptr_val
    {
        using type = typename T::value_type;
    };

    template<typename T>
    struct Ptr_val<false, T>
    {
        using type = std::remove_pointer_t<T>;
    };

    template<typename VO>
    struct Vector_order
    {
        using type = std::conditional_t< std::is_same_v<VO, Row>, Col, Row >;
    };

    /////////////////////////////////////////////

    template<typename T>
    struct Has_triangular_type_tag
    {
        static constexpr bool value = std::is_same_v<T, Lower> || std::is_same_v<T, Upper>;
    };

    template<typename T>
    concept Requires_triangular_type = Has_triangular_type_tag<T>::value;

} // namespace linarg

#endif // CONCEPTS_H
