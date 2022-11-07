/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:53:08 by alaajili          #+#    #+#             */
/*   Updated: 2022/10/21 02:13:44 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_H__
#define __PAIR_H__


namespace ft {

template<class T1, class T2>
struct pair {

    typedef T1  first_type;
    typedef T2  second_type;

    T1  first;
    T2  second;

        /*    constructors    */
    pair() : first(), second() {} // default constructor
    
    template<class U, class V>
    pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {} // copy constructor

    pair(const first_type& a, const second_type& b) : first(a), second(b) {} // initialization constructor
    

        /*          operator=           */
    pair& operator=(const pair& pr) {
        first = pr.first;
        second = pr.second;
        return *this;
    } 
    
}; // pair class


    /*      relational operators (pair)      */
template<class T1, class T2>
bool operator==(const pair<T1,T2>& l, const pair<T1,T2>& r) {
    return (l.first == r.first && l.second == r.second);
} // operator ==

template<class T1, class T2>
bool operator!=(const pair<T1,T2>& l, const pair<T1,T2>& r) { return !(l==r); } // operator !=

template<class T1, class T2>
bool operator<(const pair<T1,T2>& l, const pair<T1,T2>& r) {
    return (l.first < r.first || (l.first == r.first && l.second < r.second));
} // operator <
    
template<class T1, class T2>
bool operator<=(const pair<T1,T2>& l, const pair<T1,T2>& r) { return !(r < l); } // operator <=

template<class T1, class T2>
bool operator>(const pair<T1,T2>& l, const pair<T1,T2>& r) { return (r < l); } // operator >

template<class T1, class T2>
bool operator>=(const pair<T1,T2>& l, const pair<T1,T2>& r) { return !(r > l); } // operator >=



    /*          make_pair           */
template<class T1, class T2>
pair<T1,T2> make_pair(T1 x, T2 y) { return pair<T1,T2>(x, y); }

    
} // namespace ft


#endif