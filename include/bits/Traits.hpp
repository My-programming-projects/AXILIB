#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <type_traits>
//#include <vector>
//#include <initializer_list>

//#include "Container.hpp"
#include "include/bits/Aliases.hpp"

namespace axilib
{
    namespace traits
    {
        template<bool B, typename T>
        struct Zero
        {
            static bool has_value(const T& complex)
            {
                return complex.real() == 0 && complex.imag() == 0;
            }
        };

        template<typename T>
        struct Zero<false, T>
        {
            static bool has_value(const T& value)
            {
                return value == 0;
            }
        };

        template<bool B, typename T>
        struct In_type
        {
            static T value(typename T::value_type value)
            {
                return T{value, value};
            }
        };

        template<typename T>
        struct In_type<false, T>
        {
            static T value(T value)
            {
                return value;
            }
        };

        /*template<bool Cond, typename T>
        struct Get_type
        {
            using type = typename T::value_type;
        };

        template<typename T>
        struct Get_type<false, T>
        {
            using type = T;
        };*/

        /*template<typename T>
        struct Arithmetic_value
        {
            static T get(T value)
            {
                return value;
            }
        };

        template<typename T>
        struct Non_arithmetic_value
        {
            using element_type = typename T::element_type;
            using type = typename element_type::result_type;

            static type get(T struct_type)
            {
                return  struct_type->get();
            }
        };*/

        //////////////////////////////////////////////

        template<typename T, typename... Ts>
        constexpr bool is_one_of()
        {
            return (std::is_same_v<T, Ts> || ...);
        }
    }

} // namespace axilib

#endif // TRAITS_HPP
