#ifndef VECTOR_TCC
#define VECTOR_TCC

#include "Vector.hpp"

namespace axilib
{
    template<typename VO, typename T>
    Vector<VO, T>::Vector() :
        a_size_{} { }

    template<typename VO, typename T>
    Vector<VO, T>::Vector(size_type size) :
        a_size_{size}
    {
        allocate();
        set_size();
        detail::imbue_impl(begin(), end(), []{ return value_type{}; });
    }

    template<typename VO, typename T>
    Vector<VO, T>::Vector(const std::initializer_list<T>& list) :
        a_size_{list.size()}
    {
        allocate();
        set_size();
        std::copy(list.begin(), list.end(), begin());
    }

    template<typename VO, typename T>
        template<typename Iterator, typename>
        Vector<VO, T>::Vector(Iterator first, Iterator last)
        {
            a_size_ = dist(first, last);
            allocate();
            set_size();

            std::copy(first, last, begin());
        }

    template<typename VO, typename T>
        template<typename Function, typename>
        Vector<VO, T>::Vector(size_type size, Function function) :
            a_size_{size}
        {
            allocate();
            set_size();
            detail::imbue_impl(begin(), end(), function);
        }

    template<typename VO, typename T>
    Vector<VO, T>::Vector(const std::string& str)
    {
        From_string<value_type> from_string(str);
        from_string.start();
        auto result = from_string.get();

        auto array = result[0];

        copy_impl(array);
    }

    template<typename VO, typename T>
    Vector<VO, T>::Vector(const Vector<VO, T>& copy) :
        data_{copy.data_},
        a_size_{copy.a_size_},
        size_{copy.size_} { }

    template<typename VO, typename T>
    Vector<VO, T>::Vector(Vector<VO, T>&& move)
    {
        data_ = move.data_;
        a_size_ = move.a_size_;
        size_ = move.size_;

        move.data_ = nullptr;
        move.a_size_ = 0;
        move.size_ = Size{};
    }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator=(const Vector<VO, T>& rhs)
    {
        if(*this == rhs)
        {
            return *this;
        }

        data_ = nullptr;
        a_size_ = 0;
        size_ = Size{};

        a_size_ = rhs.a_size_;

        allocate();
        set_size();

        std::copy(rhs.cbegin(), rhs.cend(), begin());

        return *this;
    }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator=(Vector<VO, T>&& rhs)
    {
        if(*this == rhs)
        {
            return *this;
        }

        data_ = nullptr;
        a_size_ = 0;
        size_ = Size{};

        a_size_ = rhs.a_size_;

        allocate();
        set_size();

        std::copy(rhs.cbegin(), rhs.cend(), begin());

        rhs.data_ = nullptr;
        rhs.a_size_ = 0;
        rhs.size_ = Size{};

        return *this;
    }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator=(const std::initializer_list<T>& rhs)
    {
        if(data_)
        {
            data_ = nullptr;
            a_size_ = 0;
            size_ = Size{};
        }

        a_size_ = rhs.size();
        allocate();
        set_size();

        std::copy(rhs.begin(), rhs.end(), begin());

        return *this;
    }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator=(const std::string& str)
    {
        if(data_)
        {
            data_ = nullptr;
            a_size_ = 0;
            size_ = Size{};
        }

        From_string<value_type> from_string(str);
        from_string.start();
        auto result = from_string.get();
        auto array = result[0];

        copy_impl(array);
        std::cout << "Copy str\n\n";
        return *this;
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::size_type
    Vector<VO, T>::size() const noexcept
    {
        return std::is_same_v<vector_order, Row> ? size_.cols() : size_.rows();
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::size_type
    Vector<VO, T>::size_1() const noexcept
    {
        return size_.rows();
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::size_type
    Vector<VO, T>::size_2() const noexcept
    {
        return size_.cols();
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::reference
    Vector<VO, T>::operator[](size_type i)
    {
        return data_[i];
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::const_reference
    Vector<VO, T>::operator[](size_type i) const
    {
        return data_[i];
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::reference
    Vector<VO, T>::operator()(size_type i, size_type j)
    {
        return data_[size_.rows() * j + i];
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::const_reference
    Vector<VO, T>::operator()(size_type i, size_type j) const
    {
        return data_[size_.rows() * j + i];
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::iterator
    Vector<VO, T>::begin()
    {
        return data_.get();
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::const_iterator
    Vector<VO, T>::cbegin() const
    {
        return data_.get();
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::iterator
    Vector<VO, T>::end()
    {
        return data_.get() + a_size_;
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::const_iterator
    Vector<VO, T>::cend() const
    {
        return data_.get() + a_size_;
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::reverse_iterator
    Vector<VO, T>::rbegin()
    {
        return reverse_iterator(end());
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::const_reverse_iterator
    Vector<VO, T>::crbegin() const
    {
        return const_reverse_iterator(cend());
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::reverse_iterator
    Vector<VO, T>::rend()
    {
        return reverse_iterator(begin());
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::const_reverse_iterator
    Vector<VO, T>::crend() const
    {
        return const_reverse_iterator(cbegin());
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::size_type
    Vector<VO, T>::zeros() const noexcept
    {
        return detail::count_zeros_impl(cbegin(), cend());
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::value_type
    Vector<VO, T>::min() noexcept
    {
        auto minmax = detail::index_min_max_impl(begin(), end());

        return *minmax.first;
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::value_type
    Vector<VO, T>::max() noexcept
    {
        auto minmax = detail::index_min_max_impl(begin(), end());

        return *minmax.second;
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::size_type
    Vector<VO, T>::index_min() noexcept
    {
        auto minmax = detail::index_min_max_impl(begin(), end());

        return dist(begin(), minmax.first);
    }

    template<typename VO, typename T>
    typename Vector<VO, T>::size_type
    Vector<VO, T>::index_max() noexcept
    {
        auto minmax = detail::index_min_max_impl(begin(), end());

        return dist(begin(), minmax.second);
    }

    template<typename VO, typename T>
    bool
    Vector<VO, T>::is_empty() const noexcept
    {
        return a_size_ == 0 && data_ == nullptr;
    }

    template<typename VO, typename T>
    Vector<typename Vector_order<VO>::type, T>
    Vector<VO, T>::transposed()
    {
        using new_order = typename Vector_order<VO>::type;

        Vector<new_order, T> trans(a_size_);
        std::copy(begin(), end(), trans.begin());

        return trans;
    }

    template<typename VO, typename T>
        template<typename Function, typename>
        void
        Vector<VO, T>::imbue(Function function)
        {
            detail::imbue_impl(begin(), end(), function);
        }

    template<typename VO, typename T>
    void
    Vector<VO, T>::replace(value_type old_value, value_type new_value)
    {
        replace_if(new_value, [old_value](value_type val){ return val == old_value; });
    }

    template<typename VO, typename T>
        template<typename Pred>
        void
        Vector<VO, T>::replace_if(value_type new_value, Pred pred)
        {
            detail::replace_impl(begin(), end(), new_value, pred);
        }

    template<typename VO, typename T>
        template<typename VO2, typename T2>
        Vector<VO, T>&
        Vector<VO, T>::operator+=(const Vector<VO2, T2>& rhs)
        {
            Vector<VO, T> result = op::Binary_op<self_type, Vector<VO2, T2>, std::plus<value_type>, op::Op_vector>()(*this, rhs);
            *this = result;

            return *this;
        }

    template<typename VO, typename T>
        template<typename VO2, typename T2>
        Vector<VO, T>&
        Vector<VO, T>::operator-=(const Vector<VO2, T2>& rhs)
        {
            Vector<VO, T> result = op::Binary_op<self_type, Vector<VO2, T2>, std::minus<value_type>, op::Op_vector>()(*this, rhs);
            *this = result;

            return *this;
        }

    template<typename VO, typename T>
        template<typename VO2, typename T2>
        Vector<VO, T>&
        Vector<VO, T>::operator*=(const Vector<VO2, T2>& rhs)
        {
            Vector<VO, T> result = op::Multiplies<self_type, Vector<VO2, T2>, op::Op_vector>()(*this, rhs);
            *this = result;

            return *this;
        }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator+=(const value_type& rhs)
    {
        Vector<VO, T> result = op::Binary_op_scalar<self_type, value_type, std::plus<value_type>, op::Op_vector>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator-=(const value_type& rhs)
    {
        Vector<VO, T> result = op::Binary_op_scalar<self_type, value_type, std::minus<value_type>, op::Op_vector>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator*=(const value_type& rhs)
    {
        Vector<VO, T> result = op::Binary_op_scalar<self_type, value_type, std::multiplies<value_type>, op::Op_vector>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename VO, typename T>
    Vector<VO, T>&
    Vector<VO, T>::operator/=(const value_type& rhs)
    {
        Vector<VO, T> result = op::Binary_op_scalar<self_type, value_type, std::divides<value_type>, op::Op_vector>()(*this, rhs);
        *this = result;

        return *this;
    }

    template<typename VO, typename T>
    void
    Vector<VO, T>::allocate()
    {
        data_ = std::shared_ptr<value_type[]>{new value_type[a_size_]};
    }

    template<typename VO, typename T>
    void
    Vector<VO, T>::set_size()
    {
        size_ = std::is_same_v<vector_order, Row> ? Size{1, a_size_} : Size{a_size_, 1};
    }

    template<typename VO, typename T>
        template<typename Container>
        void
        Vector<VO, T>::copy_impl(const Container& container)
        {
            a_size_ = container.size();

            allocate();
            set_size();

            std::copy(container.begin(), container.end(), begin());
        }

} // namespace axilib

#endif // VECTOR_TCC
