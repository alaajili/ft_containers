/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:19:59 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/20 23:41:05 by alaajili         ###   ########.fr       */
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

private:
    tree __t_;

public:

map() : __t_() {} // default constructor




iterator begin() { return __t_.begin(); }

iterator end() { return __t_.end(); }


void insert( const value_type& val ) { __t_.insert(val.first, val); }

};



    
} // ft namespace


#endif