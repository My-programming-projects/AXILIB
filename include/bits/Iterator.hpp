#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Size.hpp"
#include "Iterator_support.hpp"

#include <iterator>

namespace axilib
{
    template<typename Iterator>
    inline typename std::iterator_traits<Iterator>::difference_type dist(Iterator first, Iterator last)
    {
        typename std::iterator_traits<Iterator>::difference_type diff = 0;

        while(first != last)
        {
            diff++;
            first++;
        }

        return diff;
    }

    template<typename Iterator>
    inline typename std::iterator_traits<Iterator>::difference_type dist_1(Iterator first, Iterator last)
    {
        typename std::iterator_traits<Iterator>::difference_type diff = 0;

        while(first != last)
        {
            diff++;
            first++;
        }

        return diff;
    }

    template<typename Iterator, typename IteratorCategory>
    class Matrix_iterator : std::iterator< typename std::iterator_traits<Iterator>::iterator_category,
                                           typename std::iterator_traits<Iterator>::value_type,
                                           typename std::iterator_traits<Iterator>::reference,
                                           typename std::iterator_traits<Iterator>::pointer,
                                           typename std::iterator_traits<Iterator>::difference_type >
    {
    public:

        using iterator_type     = Iterator;
        using traits_type       = std::iterator_traits<Iterator>;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = typename traits_type::value_type;
        using reference         = typename traits_type::reference;
        using pointer           = typename traits_type::pointer;
        using difference_type   = typename traits_type::difference_type;
        using size_type         = std::size_t;

        Matrix_iterator() :
            current_{},
            stride_{} { }

        Matrix_iterator(iterator_type current) :
            current_{current},
            stride_{} { }

        Matrix_iterator(iterator_type current, std::size_t stride) :
            current_{current},
            stride_{stride} { }

        iterator_type base() const
        {
            return current_;
        }

        std::size_t stride() const noexcept
        {
            return stride_;
        }

        reference operator*()
        {
            return *current_;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        Matrix_iterator operator++()
        {
            Matrix_iterator temp;
            current_+= stride_;

            return temp;
        }

        Matrix_iterator operator++(int)
        {
            Matrix_iterator temp;
            current_+= stride_;

            return temp;
        }

        Matrix_iterator operator--()
        {
            current_-= stride_;

            return *this;
        }

        Matrix_iterator operator--(int)
        {
            Matrix_iterator temp = *this;
            current_-= stride_;

            return temp;
        }

        Matrix_iterator operator+(difference_type n)
        {
            current_+= (n * stride_);

            return *this;
        }

        Matrix_iterator operator-(difference_type n)
        {
            current_-= (n * stride_);

            return *this;
        }

        Matrix_iterator operator+=(difference_type n)
        {
            current_+= (n * stride_);

            return *this;
        }

        Matrix_iterator& operator-=(difference_type n)
        {
            current_-= (n * stride_);

            return *this;
        }

        bool operator==(Matrix_iterator rhs)
        {
            return current_ == rhs.current_;
        }

        bool operator!=(Matrix_iterator rhs)
        {
            return !(current_ == rhs.current_);
        }

        bool operator<(Matrix_iterator rhs)
        {
            return (current_ < rhs.current_);
        }

    private:
        iterator_type current_;
        std::size_t stride_;
    };

    template<typename Iterator, typename IteratorCategory>
    class Reverse_matrix_iterator : std::iterator< typename std::iterator_traits<Iterator>::iterator_category,
                                                   typename std::iterator_traits<Iterator>::value_type,
                                                   typename std::iterator_traits<Iterator>::reference,
                                                   typename std::iterator_traits<Iterator>::pointer,
                                                   typename std::iterator_traits<Iterator>::difference_type >
    {
    public:

        using iterator_type     = Iterator;
        using traits_type       = std::iterator_traits<Iterator>;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = typename traits_type::value_type;
        using reference         = typename traits_type::reference;
        using pointer           = typename traits_type::pointer;
        using difference_type   = typename traits_type::difference_type;
        using size_type         = std::size_t;

        Reverse_matrix_iterator(iterator_type current) :
            current_{current},
            stride_{} { }

        Reverse_matrix_iterator(iterator_type current, std::size_t stride) :
            current_{current},
            stride_{stride} { }

        iterator_type base() const
        {
            return current_;
        }

        std::size_t stride() const noexcept
        {
            return stride_;
        }

        reference operator*()
        {
            return *current_;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        Reverse_matrix_iterator operator++()
        {
            current_--;

            return *this;
        }

        Reverse_matrix_iterator operator++(int)
        {
            Reverse_matrix_iterator temp = *this;
            current_--;

            return temp;
        }

        Reverse_matrix_iterator operator--()
        {
            current_++;

            return *this;
        }

        Reverse_matrix_iterator operator--(int)
        {
            Reverse_matrix_iterator temp = *this;
            current_++;

            return temp;
        }

        Reverse_matrix_iterator operator+(difference_type n)
        {
            current_-= n;

            return *this;
        }

        Reverse_matrix_iterator operator-(difference_type n)
        {
            current_+= n;

            return *this;
        }

        Reverse_matrix_iterator operator+=(difference_type n)
        {
            current_-= n;

            return *this;
        }

        Reverse_matrix_iterator& operator-=(difference_type n)
        {
            current_+= n;

            return *this;
        }

        bool operator==(Reverse_matrix_iterator rhs)
        {
            return current_ == rhs.current_;
        }

        bool operator!=(Reverse_matrix_iterator rhs)
        {
            return !(current_ == rhs.current_);
        }

        bool operator<(Reverse_matrix_iterator rhs)
        {
            return (current_ < rhs.current_);
        }

    private:
        iterator_type current_;
        std::size_t stride_;
    };

    template<typename Iterator>
    class Matrix_ref_iterator : std::iterator< typename std::iterator_traits<Iterator>::iterator_category,
                                                     typename std::iterator_traits<Iterator>::value_type,
                                                     typename std::iterator_traits<Iterator>::reference,
                                                     typename std::iterator_traits<Iterator>::pointer,
                                                     typename std::iterator_traits<Iterator>::difference_type >
    {
    public:

        using iterator_category = std::random_access_iterator_tag;
        using iterator_type     = Iterator;
        using traits_type       = std::iterator_traits<Iterator>;
        using pointer           = typename traits_type::value_type;
        using value_type        = std::remove_pointer_t<pointer>;
        using reference         = value_type&;
        using difference_type   = typename traits_type::difference_type;
        using size_type         = std::size_t;


        Matrix_ref_iterator(iterator_type current, size_type stride = 1) :
            current_{current},
            stride_{stride} { }

        reference base() const
        {
            reference ptr = *current_;

            return ptr;
        }

        reference operator*()
        {
            pointer ptr = *current_;

            return *ptr;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        Matrix_ref_iterator operator++()
        {
            current_+= stride_;

            return *this;
        }

        Matrix_ref_iterator operator++(int)
        {
            Matrix_ref_iterator temp = *this;
            current_+= stride_;

            return temp;
        }

        Matrix_ref_iterator operator--()
        {
            current_-= stride_;

            return *this;
        }

        Matrix_ref_iterator operator--(int)
        {
            Matrix_ref_iterator temp = *this;
            current_-= stride_;

            return temp;
        }

        Matrix_ref_iterator operator+(difference_type n)
        {
            current_ += (n * stride_);

            return *this;
        }

        Matrix_ref_iterator operator-(difference_type n)
        {
            current_ -= (n * stride_);

            return *this;
        }

        Matrix_ref_iterator operator+=(difference_type n)
        {
            current_ += (n * stride_);

            return *this;
        }

        Matrix_ref_iterator& operator-=(difference_type n)
        {
            current_ += (n * stride_);

            return *this;
        }

        bool operator==(Matrix_ref_iterator rhs)
        {
            return current_ == rhs.current_;
        }

        bool operator!=(Matrix_ref_iterator rhs)
        {
            return !(current_ == rhs.current_);
        }

        bool operator<(Matrix_ref_iterator rhs)
        {
            return (current_ < rhs.current_);
        }

    private:
        iterator_type current_;
        size_type stride_;
    };


    template<typename Iterator, typename Category>
    auto operator-(const Matrix_iterator<Iterator, Category>& lhs, const Matrix_iterator<Iterator, Category>& rhs) ->decltype(dist_1(lhs, rhs))
    {
        auto r = dist_1(rhs, lhs);
        return r;
    }

    template<typename Iterator_lhs, typename Iterator_rhs, typename Category_lhs, typename Category_rhs>
    auto operator-(const Reverse_matrix_iterator<Iterator_lhs, Category_lhs>& lhs, const Reverse_matrix_iterator<Iterator_rhs, Category_rhs>& rhs) ->decltype(rhs.base() - lhs.base())
    {
        return dist_1(lhs, rhs);
    }

}

#endif // ITERATOR_HPP
