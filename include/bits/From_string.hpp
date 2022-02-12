#ifndef FROM_STRING_H
#define FROM_STRING_H

#include <regex>
#include <numeric>
#include <iostream>

#include "Conversions.hpp"
#include "Exceptions.hpp"
#include "include/axi_config.hpp"

namespace axilib
{

    template<std::size_t N, typename... Ts>
    struct Select;

    template<std::size_t N, typename T, typename... Ts>
    struct Select<N, T, Ts...> : Select<N - 1, Ts...> { };

    template<typename T, typename... Ts>
    struct Select<0, T, Ts...> { using type = T; };

    ///////////////////////////////////////////////////////////

    template<typename T>
    class From_string
    {
    public:

        using value_type    = T;

        From_string(const std::string& expr);

        void start();

        std::vector<std::vector<T>> get() const noexcept;

    private:

        std::vector<std::string> split(const std::string& expr, char denom, bool denom_preserve = false);

        void erase_parenth(std::vector<std::string>& str_vec);

        std::vector<std::vector<std::string>> get_numbers(const std::vector<std::string>& str_vec);

        void convert(const std::vector<std::vector<std::string>> &str_map);

        void expr_check(const std::vector<std::string>& expr_vec);

        std::regex pattern_;
        std::string expr_;

        std::vector<std::vector<T>> expr_map_;
    };

} // namespace linarg

#endif // FROM_STRING_H
