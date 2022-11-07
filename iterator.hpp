/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:07:43 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/07 19:10:30 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <cstddef>

namespace ft {


template<class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
struct iterator {
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
    typedef Category    iterator_category;
};  // iterator base class


    /*          iterator traits          */
template<class Iterator>
struct iterator_traits {
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T*> {
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
    typedef std::random_access_iterator_tag  iterator_category;
};

template<class T>
struct iterator_traits<const T*> {
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
    typedef std::random_access_iterator_tag  iterator_category;
};

    /*      random access iterator for vector       */
template<class T>
class RandomAccessIterator {
public:
    typedef typename ft::iterator_traits<T>::value_type         value_type;
    typedef typename ft::iterator_traits<T>::difference_type    difference_type;
    typedef typename ft::iterator_traits<T>::pointer            pointer;
    typedef typename ft::iterator_traits<T>::reference          reference;
    typedef typename ft::iterator_traits<T>::iterator_category  iterator_category;


private:
    pointer __p_;


public:
    /*       constructors        */
RandomAccessIterator() : __p_(nullptr) {} // default
explicit RandomAccessIterator(pointer p) : __p_(p) {} // initialization

template<class I>
RandomAccessIterator(const RandomAccessIterator<I>& it) : __p_(it.base()) {} // copy


pointer base() const { return __p_; } // base


    /*          operators           */
reference operator*() const { return *__p_; }
pointer operator->() const { return &(operator*()); }
reference operator[](difference_type n) const { return *(__p_ + n); }

RandomAccessIterator operator+(difference_type n) const { return RandomAccessIterator(__p_ + n); }
RandomAccessIterator& operator++() { ++__p_; return *this; }
RandomAccessIterator operator++(int) { RandomAccessIterator tmp(*this); ++__p_; return tmp; }
RandomAccessIterator& operator+=(difference_type n) { __p_ += n; return *this; }
RandomAccessIterator operator-(difference_type n) const { return RandomAccessIterator(__p_ - n); }
RandomAccessIterator& operator--() { --__p_; return *this; }
RandomAccessIterator operator--(int) { RandomAccessIterator tmp(*this); --__p_; return tmp; }
RandomAccessIterator& operator-=(difference_type n) { __p_ -= n; return *this; }

}; // RandomAccessIterator

template<class T1, class T2>
bool operator==(const RandomAccessIterator<T1>& l,
                const RandomAccessIterator<T2>& r) { return l.base() == r.base(); }

template<class T1, class T2>
bool operator!=(const RandomAccessIterator<T1>& l,
                const RandomAccessIterator<T2>& r) { return l.base() != r.base(); }

template<class T1, class T2>
bool operator<=(const RandomAccessIterator<T1>& l,
                const RandomAccessIterator<T2>& r) { return l.base() <= r.base(); }

template<class T1, class T2>
bool operator>=(const RandomAccessIterator<T1>& l,
                const RandomAccessIterator<T2>& r) { return l.base() >= r.base(); }

template<class T1, class T2>
bool operator<(const RandomAccessIterator<T1>& l,
                const RandomAccessIterator<T2>& r) { return l.base() < r.base(); }

template<class T1, class T2>
bool operator>(const RandomAccessIterator<T1>& l,
                const RandomAccessIterator<T2>& r) { return l.base() > r.base(); }


template<class T>
  RandomAccessIterator<T> operator+(
    typename RandomAccessIterator<T>::difference_type n, 
    const RandomAccessIterator<T>& it) { return RandomAccessIterator<T>(it + n); }

template<class T>
  typename RandomAccessIterator<T>::difference_type operator-(
    const RandomAccessIterator<T>& l,
    const RandomAccessIterator<T>& r) { return l.base() - r.base(); }

    /*      reverse iterator        */
template<class Iterator>
class reverse_iterator {
public:
    typedef Iterator                                                iterator_type;
    typedef typename iterator_traits<Iterator>::value_type          value_type;
    typedef typename iterator_traits<Iterator>::difference_type     difference_type;
    typedef typename iterator_traits<Iterator>::pointer             pointer;
    typedef typename iterator_traits<Iterator>::reference           reference;
    typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;

private:
    iterator_type __current_;
public:
    /*      constructors        */
reverse_iterator() : __current_() {} // default
explicit reverse_iterator(iterator_type it) : __current_(it) {} // initialization

template<class Iter>
reverse_iterator(const reverse_iterator<Iter>& rev_it) : __current_(rev_it.base()) {} // copy



    /*      base        */
iterator_type base() const { return __current_; }

    /*      operators       */
reference operator*() const { return *(__current_ - 1); }
pointer operator->() const { return &(operator*()); }
reference operator[](difference_type n) { return *(__current_ - n - 1); }

reverse_iterator operator+(difference_type n) const { return reverse_iterator(__current_ - n); }
reverse_iterator& operator++() { __current_--; return *this; }
reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
reverse_iterator& operator+=(difference_type n) { __current_ -= n; return *this; }
reverse_iterator operator-(difference_type n) const { return reverse_iterator(__current_ + n); }
reverse_iterator& operator--() { __current_++; return *this; }
reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }
reverse_iterator& operator-=(difference_type n) { __current_ += n; return *this; }

};

template <class It1, class It2>
  bool operator== (const reverse_iterator<It1>& lhs,
                   const reverse_iterator<It2>& rhs) { return lhs.base() == rhs.base(); }

template <class It1, class It2>
  bool operator!= (const reverse_iterator<It1>& lhs,
                   const reverse_iterator<It2>& rhs) { return lhs.base() != rhs.base(); }

template <class It1, class It2>
  bool operator<  (const reverse_iterator<It1>& lhs,
                   const reverse_iterator<It2>& rhs) { return lhs.base() > rhs.base(); }

template <class It1, class It2>
  bool operator<= (const reverse_iterator<It1>& lhs,
                   const reverse_iterator<It2>& rhs) { return lhs.base() >= rhs.base(); }

template <class It1, class It2>
  bool operator>  (const reverse_iterator<It1>& lhs,
                   const reverse_iterator<It2>& rhs) { return lhs.base() < rhs.base(); }

template <class It1, class It2>
  bool operator>= (const reverse_iterator<It1>& lhs,
                   const reverse_iterator<It2>& rhs) { return lhs.base() <= rhs.base(); }

template <class Iterator>
  reverse_iterator<Iterator> operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it) { return reverse_iterator<Iterator>(rev_it.base() - n); }

template <class Iterator>
  typename reverse_iterator<Iterator>::difference_type operator- (
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) { return rhs.base() - lhs.base(); }


template<class InputIterator>
  typename iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last) {
        ptrdiff_t diff = 0;
        while(first != last) { ++first; ++diff; }
        return diff;
    }


} // namespace ft


#endif