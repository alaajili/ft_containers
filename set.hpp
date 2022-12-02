/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:17:22 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/30 22:53:46 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SET_H__
#define __SET_H__

#include <memory>
#include <functional>
#include "pair.hpp"
#include "iterator.hpp"
#include "Tree.hpp"
#include "algorithm.hpp"


namespace ft {
    
template<class T,
          class Compare = std::less<T>,
          class Alloc = std::allocator<T>
        > class set
{

public:
    typedef T                                                       key_type;
    typedef T                                                       value_type;
    typedef Compare                                                 key_compare;
    typedef Compare                                                 value_compare;
    typedef Alloc                                                   allocator_type;
    typedef std::ptrdiff_t                                          difference_type;
    typedef std::size_t                                             size_type;
    typedef typename allocator_type::reference                      reference;
    typedef typename allocator_type::const_reference                const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef Tree<key_type, value_type, key_compare, allocator_type> tree;
    typedef typename tree::iterator                                 iterator;
    typedef typename tree::const_iterator                           const_iterator;
    typedef typename tree::reverse_iterator                         reverse_iterator;
    typedef typename tree::const_reverse_iterator                   const_reverse_iterator;

private:
    tree __t_;


public:


explicit set( const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type() ) : __t_(comp, alloc) {}  // default constructor

template<class InputIter>
set( InputIter first , InputIter last,
     const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
        : __t_(comp, alloc) {
            insert(first, last);
        }

set( const set& x ) : __t_(x.__t_) {}

set& operator=( const set& x ) {
    __t_ = x.__t_;
    return *this;
}

~set() {}



    /*          ITERATORS          */
iterator begin() { return __t_.begin(); }
const_iterator begin() const { return __t_.begin(); }

iterator end() { return __t_.end(); }
const_iterator end() const { return __t_.end(); }

reverse_iterator rbegin() { return __t_.rbegin(); }
const_reverse_iterator rbegin() const { return __t_.rbegin(); }

reverse_iterator rend() { return __t_.rend(); }
const_reverse_iterator rend() const { return __t_.rend(); }


    /*          CAPACITY        */
bool empty() const { return __t_.empty(); }

size_type size() const { return __t_.size(); }

size_type max_size() const { return __t_.max_size(); }


    /*          MODIFIERS           */
ft::pair<iterator, bool> insert( const value_type& val ) { return __t_.insert(val, val); }

iterator insert( iterator pos, const value_type& val ) {
    
    pos = (__t_.insert(val, val)).first;
    return pos;
}

template<class InputIter>
void insert( InputIter first, InputIter last ) {
    for (; first != last; ++first ) { insert(*first); }
}


void erase( iterator pos ) { __t_.erase(pos); }

void erase( iterator first, iterator last ) {
    
    while ( first != last )
        erase(first++);
}

size_type erase( const value_type& val ) {
  iterator pos = find(val);
  if (pos == end())
    return 0;
  erase(pos);
  return 1;
}


void swap( set& x ) { __t_.swap(x.__t_); }



void clear() { __t_.clear(); }


        /*      OPERATIONS          */
iterator find( const value_type& val ) { return __t_.find(val); }
const_iterator find( const value_type& val ) const { return __t_.find(val); }

size_type count( const value_type& val ) const { return __t_.count(val); }

iterator lower_bound( const value_type& val ) { return __t_.lower_bound(val); }
const_iterator lower_bound( const value_type& val ) const { return __t_.lower_bound(val); }

iterator upper_bound( const key_type& val ) { return __t_.upper_bound(val); }
const_iterator upper_bound( const key_type& val ) const { return __t_.upper_bound(val); }

pair<iterator, iterator> equal_range( const key_type& val ) { return __t_.equal_range(val); }
pair<const_iterator, const_iterator> equal_range( const key_type& val ) const { return __t_.equal_range(val); }



    /*                  OBSERVERS                */
key_compare key_comp() const { return __t_.key_comp(); }

value_compare value_comp() const { return __t_.key_comp(); }



allocator_type get_allocator() const { return __t_.get_allocator(); }

};

        /*        comparaison operators       */
template <class T, class Comp, class Alloc>
  bool operator==( const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs ) {
    if (lhs.size() != rhs.size()) { return false; }
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
  } // operator ==

template <class T, class Comp, class Alloc>
  bool operator!=( const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs ) {
    return !(lhs == rhs);
  } // operator !=

template <class T, class Comp, class Alloc>
  bool operator<( const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs ) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  } // operator <

template <class T, class Comp, class Alloc>
  bool operator>( const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs ) {
    return (rhs < lhs);
  } // operator >

template <class T, class Comp, class Alloc>
  bool operator<=( const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs ) {
    return !(lhs > rhs);
  } // operator <=

template <class T, class Comp, class Alloc>
  bool operator>=( const set<T,Comp,Alloc>& lhs, const set<T,Comp,Alloc>& rhs ) {
    return !(lhs < rhs);
  } // operator >=

template <class T, class Comp, class Alloc>
void swap( set<T,Comp,Alloc>& lhs, set<T,Comp,Alloc>& rhs ) { lhs.swap(rhs); }



} // ft namespace






#endif