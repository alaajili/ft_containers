/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:45:53 by alaajili          #+#    #+#             */
/*   Updated: 2022/12/02 14:18:37 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <memory>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace ft {

template<class T, class Alloc = std::allocator<T> >
class vector {
public:
        /*    Member types    */
    typedef T                                           value_type;
    typedef Alloc                                       allocator_type;
    typedef std::ptrdiff_t                              difference_type;
    typedef std::size_t                                 size_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef RandomAccessIterator<pointer>               iterator;
    typedef RandomAccessIterator<const_pointer>         const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;


private:
    allocator_type  __alloc_;
    size_type       __size_;
    size_type       __capacity_;
    pointer         __begin_;
    pointer         __end_;

public:
        /*    Member functions */
    explicit vector(const allocator_type& alloc = allocator_type()) :
        __alloc_(alloc), __size_(0), __capacity_(0), __begin_(nullptr), __end_(nullptr) {} //default constructor
      
    explicit vector(size_type n, const value_type& val = value_type(),
        const allocator_type& alloc = allocator_type()) : __alloc_(alloc), __size_(n), __capacity_(n) {
            __begin_ = __alloc_.allocate(n);
            __end_ = __begin_;
            for (; n > 0; n--, __end_++) { __alloc_.construct(__end_, val); }
    } // fill constructor
    
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
        typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator(),
        const allocator_type& alloc = allocator_type()) :
            __alloc_(alloc) , __size_(std::distance(first, last)), __capacity_(__size_), __begin_(nullptr), __end_(nullptr) {
                __begin_ = __end_ = __alloc_.allocate(__capacity_);
                for (; first != last; ++first, ++__end_)
                    __alloc_.construct(__end_, *first);
      } //range constructor

    vector (const vector& x) : __alloc_(x.__alloc_), __size_(x.__size_), __capacity_(x.__size_) {
        __begin_ = __alloc_.allocate(__size_);
        __end_ = __begin_;
        for (size_type i = 0; i < __size_; i++, __end_++) { __alloc_.construct(__end_, *(x.__begin_ + i)); }
    } //copy constructor

    ~vector() {
        for (pointer t = __begin_; t != __end_; t++) { __alloc_.destroy(t); }
        if (__begin_ != nullptr) { __alloc_.deallocate(__begin_, __capacity_); }
    } // destructor

    vector& operator=(const vector& x) {
        __alloc_ = x.__alloc_; __size_ = x.__size_;
        for (pointer t = __begin_; t != __end_; t++) { __alloc_.destroy(t); }
        if (__size_ > __capacity_) {
            if (__begin_) { __alloc_.deallocate(__begin_, __capacity_); }
            __begin_ = __alloc_.allocate(__size_);
            __capacity_ = __size_;
        }
        __end_ = __begin_;
        for (size_type i = 0; i < __size_; i++, __end_++) { __alloc_.construct(__end_, *(x.__begin_ + i)); }
        return *this;
    } //copy assignement operator

        /*     Capacity      */
    size_type size() const { return __size_; } // size
    
    size_type max_size() const { return std::min(__alloc_.max_size(),
                                  static_cast<size_type>(std::numeric_limits<difference_type>::max())); } // max_size

    void resize(size_type n, value_type val = value_type()) {
        if (n < __size_) {
            while (__size_ > n) {
                __alloc_.destroy(__end_ - 1);
                __end_--, __size_--;
            }
      }
      else {
          if (n < __capacity_) {}
          else if (n < __capacity_ * 2) { reserve(__capacity_ * 2); }
          else { reserve(n); }
          for (; __size_ < n; __size_++, __end_++) { __alloc_.construct(__end_, val); }
      }
    } // resize

    size_type capacity() const { return __capacity_; }; // capacity

    bool empty() const { return __size_ == 0; }; // is_empty???

    void reserve(size_type n) {
        if (n > __capacity_) {
            pointer tmp1 = __begin_, tmp2 = __end_;
            __begin_ = __end_ = __alloc_.allocate(n);
            for (size_type i = 0; i < __size_; i++, __end_++) { __alloc_.construct(__end_, *(tmp1 + i)); }
            for (pointer t = tmp1; t != tmp2; t++) { __alloc_.destroy(t); }
            if (tmp1 != nullptr) { __alloc_.deallocate(tmp1, __capacity_); }
            __capacity_ = n;
        }
    } // reserve


        /*    Element access     */
    reference operator[](size_type n) { return *(__begin_ + n); } // access_element []
    const_reference operator[](size_type n) const { return static_cast<const_reference>(*(__begin_ + n)); } // const_access_element []

    reference at(size_type n) {
        if (n < 0 || n >= __size_) { throw std::out_of_range("Index out of range"); }
        return *(__begin_ + n);
    } // access_element at

    const_reference at(size_type n) const {
        if (n < 0 || n >= __size_) { throw std::out_of_range("Index out of range"); }
        return *(__begin_ + n);
    } // const_access_element at

    reference front() { return *__begin_; } // access_first_element
    const_reference front() const { return *__begin_; } // const_access_first_element

    reference back() { return *(__end_ - 1); }; // access_last_element
    const_reference back() const { return *(__end_ - 1); } // const_access_last_element


        /*    Iterators     */
    iterator begin() { return iterator(__begin_); } // begin
    const_iterator begin() const { return const_iterator(__begin_); } // const_begin
    
    iterator end() { return iterator(__end_); } //end
    const_iterator end() const { return const_iterator(__end_); }; //const_end

    reverse_iterator rbegin() { return reverse_iterator(end()); } // reverse_begin
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); } // const_reverse_begin

    reverse_iterator rend() { return reverse_iterator(begin()); } // reverse_end
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }; // const_reverse_end


        /*      Modifiers       */
    template<class InputIterator>
    void assign(InputIterator first, InputIterator last,
            typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
                clear();
                __size_ = last - first;
                if ( __size_ > __capacity_ ) {
                    if ( __begin_ ) { __alloc_.deallocate(__begin_, __capacity_); }
                    __capacity_ = __size_;
                    __begin_ = __end_ = __alloc_.allocate(__capacity_);
                }
                for (; first != last; ++first, __end_++)
                    __alloc_.construct(__end_, *first);
      } // range_assign
    
    void assign(size_type n, const value_type& val) {
        clear();
        __size_ = n;
        if (n > __capacity_) { 
            if (__begin_ )
                __alloc_.deallocate(__begin_, __capacity_);
            __begin_ = __end_ = __alloc_.allocate(n);
            __capacity_ = n;
        }
        for (size_type i = 0; i < __size_; i++, __end_++)
            __alloc_.construct(__end_, val);
    } // fill_assign

    void push_back(const value_type& val) {
        if (__capacity_ == 0)
            reserve(1);
        else if (__capacity_ == __size_)
            reserve(__capacity_ * 2);
        __alloc_.construct(__end_, val);
        __size_++, __end_++;
    } // push_back

    void pop_back() {
        __alloc_.destroy(__end_ - 1);
        __size_--, __end_--;
    } // pop_back

    iterator insert(iterator pos, const value_type& val) {
        size_type diff = pos.base() - __begin_;
        if (__capacity_ == 0) { reserve(1); }
        else if (__capacity_ == __size_) { reserve(__capacity_ * 2); }

        pointer base = __begin_ + diff;
      
        for (pointer p = __end_-1; p >= base; --p) {
            __alloc_.construct(p + 1, *(p));
            __alloc_.destroy(p);
        }
        __alloc_.construct(base, val);
        __size_++, __end_++;
        return (begin() + diff);
    } // insert one element
    

    
    
    void insert(iterator pos, size_type n, const value_type& val) {
        if (n == 0) return;
        difference_type diff = pos.base() - __begin_;
        if (__size_ + n > __capacity_) {
            if (__size_ + n <= __capacity_ * 2) { reserve(__capacity_*2); }
            else { reserve(__size_ + n); }
        }
        pointer base = __begin_ + diff;
        for (pointer p = __end_ - 1; p >= base; --p) {
            __alloc_.construct(p + n, *(p));
            __alloc_.destroy(p);
        }
        for (size_type i = 0; i < n; ++i) { __alloc_.construct(base+i, val); }
        __size_ += n, __end_ += n;
    }

    template<class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last,
            typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) {
                difference_type diff = pos.base() - __begin_;
                size_type n = std::distance(first, last);
                if (n == 0) return;
                vector x(first, last);
                if (__size_ + n > __capacity_) {
                    if (__size_ + n <= __capacity_ * 2) { reserve(__capacity_*2); }
                    else { reserve(__size_ + n); }
                }
                pointer base = __begin_ + diff;
                for (pointer p = __end_ - 1; p >= base; --p) {
                    __alloc_.construct(p + n, *(p));
                    __alloc_.destroy(p);
                }
                for (size_type i = 0; i < n; ++i) { __alloc_.construct(base+i, x[i]); }
                __size_ += n, __end_ += n;
      } //range_insert

    iterator erase(iterator pos) {

        pointer p = pos.base();
        for (;p != __end_ - 1; ++p)
            *p = *(p + 1);
        __alloc_.destroy(p);
        __end_--, __size_--;

        return pos;
    } // erase one element

    iterator erase(iterator first, iterator last) {
        size_type n = last.base() - first.base();
        std::copy(first + n, end(), first);
        for (size_type i = 0; i < n; i++) { pop_back(); }
        return first;
    } // erase elements

    void swap(vector& x) {
        std::swap(__size_, x.__size_);
        std::swap(__capacity_, x.__capacity_);
        std::swap(__begin_, x.__begin_);
        std::swap(__end_, x.__end_);
        std::swap(__alloc_, x.__alloc_);
    } // swap content

    void clear() {
        for (pointer t = __begin_; t != __end_; t++) { __alloc_.destroy(t); }
        __end_ = __begin_;
        __size_ = 0;
    } // clear content


    allocator_type get_allocator() const { return __alloc_; } // get_allocator

}; //vector


template <class T, class Alloc>
  bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    if (lhs.size() != rhs.size()) { return false; }
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
  } // operator ==

template <class T, class Alloc>
  bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs == rhs);
  } // operator !=

template <class T, class Alloc>
  bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  } // operator <

template <class T, class Alloc>
  bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return (rhs < lhs);
  } // operator >

template <class T, class Alloc>
  bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs > rhs);
  } // operator <=

template <class T, class Alloc>
  bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs < rhs);
  } // operator >=


template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
    x.swap(y);
  } // swap

} //ft namespace

#endif