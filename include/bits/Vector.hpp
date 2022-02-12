#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "Iterator.hpp"
#include "Concepts.hpp"
#include "From_string.tcc"
#include "Matrix_support_funcs.hpp"

namespace axilib
{
    template<typename VO, typename T>
    class Vector
    {
        static_assert (is_row_or_col<VO>(), "Uncorrect type of vector");
        static_assert (std::is_arithmetic<T>::value || Is_complex<T>::value, "Uncorrect type");

        using self_type                 = Vector<VO, T>;

    public:

        using type                      = Vector_tag;
        using vector_order              = VO;
        using value_type                = T;
        using reference                 = T&;
        using const_reference           = const T&;
        using pointer                   = T*;
        using const_pointer             = const T*;
        using iterator                  = pointer;
        using const_iterator            = const_pointer;
        using reverse_iterator          = std::reverse_iterator<iterator>;
        using const_reverse_iterator    = std::reverse_iterator<const_iterator>;
        using size_type                 = std::size_t;

        Vector();

        Vector(size_type size);

        Vector(const std::initializer_list<T>& list);

        template<typename Iterator, typename = std::enable_if_t<Is_iterator<Iterator>::value>>
        Vector(Iterator first, Iterator last);

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        Vector(size_type size, Function function);

        Vector(const std::string& str);

        Vector(const Vector& copy);

        Vector(Vector&& move);

        Vector& operator=(const Vector<VO, T>& rhs);

        Vector& operator=(Vector<VO, T>&& rhs);

        Vector& operator=(const std::initializer_list<T>& rhs);

        Vector& operator=(const std::string& str);

        size_type size() const noexcept;

        size_type size_1() const noexcept;

        size_type size_2() const noexcept;

        reference operator[](size_type i);

        const_reference operator[](size_type i) const;

        reference operator()(size_type i, size_type j);

        const_reference operator()(size_type i, size_type j) const;

        iterator begin();

        const_iterator cbegin() const;

        iterator end();

        const_iterator cend() const;

        reverse_iterator rbegin();

        const_reverse_iterator crbegin() const;

        reverse_iterator rend();

        const_reverse_iterator crend() const;

        size_type zeros() const noexcept;

        value_type min() noexcept;

        value_type max() noexcept;

        size_type index_min() noexcept;

        size_type index_max() noexcept;

        bool is_empty() const noexcept;

        Vector<typename Vector_order<VO>::type, T> transposed();

        template<typename Function, typename = std::enable_if_t<Is_functor<Function>::value>>
        void imbue(Function function);

        void replace(value_type old_value, value_type new_value);

        template<typename Pred>
        void replace_if(value_type new_value, Pred pred);

        template<typename VO2, typename T2>
        Vector<VO, T>& operator+=(const Vector<VO2, T2>& rhs);

        template<typename VO2, typename T2>
        Vector<VO, T>& operator-=(const Vector<VO2, T2>& rhs);

        template<typename VO2, typename T2>
        Vector<VO, T>& operator*=(const Vector<VO2, T2>& rhs);

        Vector<VO, T>& operator+=(const value_type& rhs);

        Vector<VO, T>& operator-=(const value_type& rhs);

        Vector<VO, T>& operator*=(const value_type& rhs);

        Vector<VO, T>& operator/=(const value_type& rhs);

    private:
        void allocate();

        void set_size();

        template<typename Container>
        void copy_impl(const Container& container);

        std::shared_ptr<T[]> data_;

        size_type a_size_;
        Size size_;
    };

} // namespace axilib

#endif // VECTOR_HPP
