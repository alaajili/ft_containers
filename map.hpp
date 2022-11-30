/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:19:59 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/28 16:05:06 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_H__
#define __MAP_H__

#include <memory>
#include <functional>
#include "pair.hpp"
#include "iterator.hpp"
#include "Tree.hpp"
#include "algorithm.hpp"



namespace ft {
    
template<class Key, class T,
         class Compare = std::less<Key>,
         class Alloc = std::allocator<pair<const Key, T> >
        > class map
{
public:
    typedef Key                                                     key_type;
    typedef T                                                       mapped_type;
    typedef pair<const Key, T>                                      value_type;
    typedef Compare                                                 key_compare;
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



class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map;

protected:
    key_compare comp;
    value_compare (key_compare c) : comp(c) {}

public:
    bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
}; // friend class value_compare


map( const key_compare& comp = key_compare(),
     const allocator_type& alloc = allocator_type() ) : __t_(comp, alloc) {} // default constructor

template<class InputIter>
map( InputIter first , InputIter last,
     const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() )
        : __t_(comp, alloc) {
            insert(first, last);
     } // range constructor

map( const map& x ) : __t_(x.__t_) {}

map& operator=( const map& x ) {
    __t_ = x.__t_;
    return *this;
}

~map() {}




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
ft::pair<iterator, bool> insert( const value_type& val ) { return __t_.insert(val.first, val); }

iterator insert( iterator pos, const value_type& val ) {
    
    pos = (__t_.insert(val.first, val)).first;
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

size_type erase( const key_type& k ) {
  iterator pos = find(k);
  if (pos == end())
    return 0;
  erase(pos);
  return 1;
}


void swap( map& x ) { __t_.swap(x.__t_); }


    /*          OPERATIONS          */
iterator find( const key_type& k ) { return __t_.find(k); }
const_iterator find( const key_type& k ) const { return __t_.find(k); }

size_type count( const key_type& k ) const { return __t_.count(k); }

iterator lower_bound( const key_type& k ) { return __t_.lower_bound(k); }
const_iterator lower_bound( const key_type& k ) const { return __t_.lower_bound(k); }

iterator upper_bound( const key_type& k ) { return __t_.upper_bound(k); }
const_iterator upper_bound( const key_type& k ) const { return __t_.upper_bound(k); }

pair<iterator, iterator> equal_range( const key_type& k ) { return __t_.equal_range(k); }
pair<const_iterator, const_iterator> equal_range( const key_type& k ) const { return __t_.equal_range(k); }



    /*          ELEMENT ACCESS              */
mapped_type& operator[]( const key_type& k ) {
    iterator it = (insert(ft::make_pair(k, mapped_type()))).first;
    return it->second;
}




void clear() { __t_.clear(); }



    /*                  OBSERVERS                */
key_compare key_comp() const { return __t_.key_comp(); }

value_compare value_comp() const { return value_compare(key_comp()); }



allocator_type get_allocator() const { return __t_.get_allocator(); }

};


        /*        comparaison operators       */
template <class Key, class T, class Comp, class Alloc>
  bool operator==( const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs ) {
    if (lhs.size() != rhs.size()) { return false; }
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
  } // operator ==

template <class Key, class T, class Comp, class Alloc>
  bool operator!=( const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs ) {
    return !(lhs == rhs);
  } // operator !=

template <class Key, class T, class Comp, class Alloc>
  bool operator<( const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs ) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  } // operator <

template <class Key, class T, class Comp, class Alloc>
  bool operator>( const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs ) {
    return (rhs < lhs);
  } // operator >

template <class Key, class T, class Comp, class Alloc>
  bool operator<=( const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs ) {
    return !(lhs > rhs);
  } // operator <=

template <class Key, class T, class Comp, class Alloc>
  bool operator>=( const map<Key,T,Comp,Alloc>& lhs, const map<Key,T,Comp,Alloc>& rhs ) {
    return !(lhs < rhs);
  } // operator >=

template <class Key, class T, class Comp, class Alloc>
void swap( map<Key,T,Comp,Alloc>& lhs, map<Key,T,Comp,Alloc>& rhs ) { lhs.swap(rhs); }
    
} // ft namespace


#endif