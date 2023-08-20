#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <iostream>

namespace axilib::detail
{

    template<typename T> struct Conversion { };

    template<> struct Conversion<int>         { enum { value = 0 }; };
    template<> struct Conversion<float>       { enum { value = 1 }; };
    template<> struct Conversion<double>      { enum { value = 2 }; };
    template<> struct Conversion<long double> { enum { value = 3 }; };

    ////////////////////////////////////////////////////////

    struct Int
    {
        static int convert(const std::string& str)
        {
            return std::stoi(str);
        }
    };

    struct Float
    {
        static float convert(const std::string& str)
        {
            return std::stof(str);
        }
    };

    struct Double
    {
        static double convert(const std::string& str)
        {
            return std::stod(str);
        }
    };

    struct Long_double
    {
        static long double convert(const std::string& str)
        {
            return std::stold(str);
        }
    };

} // namespace linarg

#endif // CONVERSIONS_HPP
