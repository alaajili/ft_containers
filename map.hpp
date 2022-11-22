/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:19:59 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/22 17:52:25 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_H__
#define __MAP_H__

#include <memory>
#include "pair.hpp"
#include "iterator.hpp"
#include "Tree.hpp"

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

map() : __t_() {} // default constructor



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



    /*          OPERATIONS          */
iterator find( const key_type& k ) { return __t_.find(k); }
const_iterator find( const key_type& k ) const { return __t_.find(k); }

size_type count( const key_type& k ) const { return __t_.count(k); }

iterator lower_bound( const key_type& k ) { return __t_.lower_bound(k); }
const_iterator lower_bound( const key_type& k ) const { return __t_.lower_bound(k); }

iterator upper_bound( const key_type& k ) { return __t_.upper_bound(k); }
const_iterator upper_bound( const key_type& k ) const { return __t_.upper_bound(k); }


};



    
} // ft namespace


#endif