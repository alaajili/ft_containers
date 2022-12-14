/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:07:43 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/30 10:49:40 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <cstddef>
#include <iterator>
#include <iostream>

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
    typedef T                                   value_type;
    typedef ptrdiff_t                           difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef std::random_access_iterator_tag iterator_category;
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
reference operator*() const {
    iterator_type tmp = __current_;
    return *(--tmp);
}
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
  typename iterator_traits<InputIterator>::size_type
    distance (InputIterator first, InputIterator last) {
        size_t diff = 0;
        while(first != last) { ++first; ++diff; }
        return diff;
    }



template<class nodeptr, class value>
class TreeIterator {

    
public:
    typedef value                                                       value_type;
    typedef typename ft::iterator_traits<value_type*>::difference_type  difference_type;
    typedef typename ft::iterator_traits<value_type*>::pointer          pointer;
    typedef typename ft::iterator_traits<value_type*>::reference        reference;
    typedef std::bidirectional_iterator_tag                             iterator_category;


private:
    nodeptr __node_;
    nodeptr __null_;

public:
    TreeIterator() : __node_(nullptr), __null_(nullptr) {}
    explicit TreeIterator(const nodeptr& n, const nodeptr& null) : __node_(n), __null_(null) {} // initialization

    template<class T, class V>
    TreeIterator(const TreeIterator<T,V>& it) : __node_(it.base()), __null_(it.getNull()) {} // copy

    template<class T, class V>
    TreeIterator& operator=(const TreeIterator<T, V>& it) {
        __node_ = it.base();
        __null_ = it.getNull();
        return *this;
    }

nodeptr base() const { return __node_; } // base

nodeptr getNull() const { return __null_; }

    /*          operators           */
reference operator*() const { return __node_->val; }
pointer operator->() const { return &(operator*()); }


TreeIterator& operator++() {
    nodeptr p;
    if ( __node_ == __null_->parent )
        __node_ = __null_;
    else if ( __node_->right && __node_->right != __null_ ) {
        __node_ = __node_->right;
        while ( __node_->left != __null_ )
            __node_ = __node_->left;
    }
    else {
        p = __node_->parent;
        while ( p && __node_ == p->right ) {
            __node_ = p;
            p = p->parent;
        }
        __node_ = p;
    }
    return *this;
}

TreeIterator operator++(int) {
    TreeIterator t = *this;
    ++(*this);
    return t;
}

TreeIterator& operator--() {
    nodeptr p;
    if (__node_ == __null_) {
        __node_ = __node_->parent;
    }
    else if ( __node_->left != __null_ ) {
        __node_ = __node_->left;
        while ( __node_->right != __null_ )
            __node_ = __node_->right;
    }
    else {
        p = __node_->parent;
        while ( p && __node_ == p->left ) {
            __node_ = p;
            p = p->parent;
        }
        __node_ = p;
    }
    return *this;
}

TreeIterator operator--(int) {
    TreeIterator t = *this;
    --(*this);
    return t;
}


};

template<class T1, class T2, class V1, class V2>
bool operator==(const TreeIterator<T1, V1>& l,
                const TreeIterator<T2, V2>& r) { return l.base() == r.base(); }

template<class T1, class T2, class V1, class V2>
bool operator!=(const TreeIterator<T1, V1>& l,
                const TreeIterator<T2, V2>& r) { return l.base() != r.base(); }


} // namespace ft


#endif