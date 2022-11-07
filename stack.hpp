/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:14:59 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/06 22:52:42 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_H__
#define __STACK_H__

#include "vector.hpp"

namespace ft {

template<class T, class Container = vector<T> >
class stack {

public:
    typedef T                                   value_type;
    typedef Container                           container_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

private:
    container_type c;

public:
    explicit stack( const container_type& ctnr = container_type() ) : c(ctnr) {}
    
    bool empty() const { return c.empty(); }

    size_type size() const { return c.size(); }

    value_type& top() { return c.back(); }
    const value_type& top() const { return c.back(); }
    
    void push( const value_type& val ) { c.push_back(val); }

    void pop() { c.pop_back(); }


    container_type uc() const { return c; }

}; // stack

template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.uc() == rhs.uc();
  }

template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.uc() != rhs.uc();
  }

template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.uc() < rhs.uc();
  }

template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.uc() <= rhs.uc();
  }

template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.uc() > rhs.uc();
  }

template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.uc() >= rhs.uc();
  }


 
} // namespace ft


#endif