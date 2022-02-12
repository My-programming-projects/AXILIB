#ifndef IO_HPP
#define IO_HPP

#include "Concepts.hpp"
//#include "Tags.hpp"
#include <complex>
#include <iomanip>

namespace axilib
{
    namespace priv
    {
        template<typename Tag, typename Obj>
        struct Text;

        template<typename Obj>
        struct Text<Matrix_tag, Obj>
        {
            static std::string get(const Obj& obj)
            {
                std::string str = "Matrix {" + std::to_string(obj.rows()) + ", " + std::to_string(obj.cols()) + "}";
                return str;
            }
        };

        template<typename Obj>
        struct Text<Submatrix_tag, Obj>
        {
            static std::string get(const Obj& obj)
            {
                std::string str = "Submatrix {" + std::to_string(obj.rows()) + ", " + std::to_string(obj.cols()) + "}";
                return str;
            }
        };

        template<typename Obj>
        struct Text<Vector_tag, Obj>
        {
            static std::string get(const Obj& obj)
            {
                std::string obj_name = std::is_same_v<typename Obj::vector_order, Row> ? "Row vector" : "Col vector";
                std::string str = obj_name + " {" + std::to_string(obj.size()) + "}";
                return str;
            }
        };

        template<bool B, typename Obj>
        struct Size
        {
            static std::pair<std::size_t, std::size_t> get(const Obj& obj)
            {
                return std::pair{obj.rows(), obj.cols()};
            }
        };

        template<typename Obj>
        struct Size<false, Obj>
        {
            static std::pair<std::size_t, std::size_t> get(const Obj& obj)
            {
                return std::pair{obj.size_1(), obj.size_2()};
            }
        };



        template<typename Char, typename Traits, typename Obj>
        void print(std::basic_ostream<Char, Traits>& os, const Obj& obj)
        {
            std::string str = Text<typename Obj::type, Obj>::get(obj);

            os << str << "\n\n";

            auto size = Size<Is_matrix<typename Obj::type>::value, Obj>::get(obj);

            for(std::size_t i = 0; i < size.first; ++i)
            {
                for(std::size_t j = 0; j < size.second; ++j)
                {
                    os << obj(i, j) << ' ';
                }

                os << '\n';
            }
        }

    } // namespace detail

    template<typename Char, typename Traits, typename M>
    std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, M mat)
    {
        priv::print(os, mat);

        return os;
    }

}

#endif // IO_HPP
