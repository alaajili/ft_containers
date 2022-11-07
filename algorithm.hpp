/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:30:59 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/03 17:17:00 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

namespace ft {
    /*          equal          */
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 f1, InputIterator1 l1, InputIterator2 f2)
{
    while (f1 != l1) {
        if (*f1 != *f2)
            return false;
        ++f1;
        ++f2;
    }
    return true;
}

template<class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 f1, InputIterator1 l1,
        InputIterator2 f2, BinaryPredicate pred)
{    
    while (f1 != l1)
    {
        if (!pred(*f1, *f2))
            return false;
        ++f1;
        ++f2;
    }
    return true;
}


    /*          lexicographical_compare         */
template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 f1, InputIterator1 l1,
                        InputIterator2 f2, InputIterator2 l2)
{                                
    while (f1 != l1)
    {
        if (f2 == l2 || *f2 < *f1) return false;
        else if (*f1 < *f2) return true;
        ++f1;
        ++f2;
    }
    return (f2 != l2);
}

template<class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 f1, InputIterator1 l1,
                        InputIterator2 f2, InputIterator2 l2, Compare comp)
{
    while (f1 != l1)
    {
        if (f2 == l2 || !comp(*f1, *f2)) return false;
        else if (comp(*f1, *f2)) return true;
        ++f1;
        ++f2;
    }
    return (f2 != l2);
}




} // namespace ft


#endif