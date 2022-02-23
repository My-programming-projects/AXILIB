#ifndef GENERATED_HPP
#define GENERATED_HPP

#include <random>
#include <chrono>

namespace axilib
{
    template<typename T>
    class Random
    {
    public:

        using value_type    = T;
        using dist          = std::conditional_t< std::is_integral_v<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T> >;
        using param         = typename dist::param_type;

        Random() { }

        Random(value_type min, value_type max) :
            dist_{min, max},
            mt_(std::chrono::_V2::system_clock::now().time_since_epoch().count()) { }

        value_type operator()()
        {
            return dist_(mt_);
        }

    private:
        dist dist_;
        param param_;
        std::random_device rd_;
        std::mt19937 mt_;
        long long seed_;
    };

} // namespace axilib

#endif // GENERATED_HPP
