/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 01:47:28 by alaajili          #+#    #+#             */
/*   Updated: 2022/12/02 15:21:09 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__


namespace ft {


/*      enable_if       */
template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };


/*      is_integral     */

template<class T> struct is_integral { static const bool value = false; };

template<> struct is_integral<bool> { static const bool value = true; };
template<> struct is_integral<char> { static const bool value = true; };
template<> struct is_integral<char16_t> { static const bool value = true; };
template<> struct is_integral<char32_t> { static const bool value = true; };
template<> struct is_integral<signed char> { static const bool value = true; };
template<> struct is_integral<unsigned char> { static const bool value = true; };
template<> struct is_integral<short> { static const bool value = true; };
template<> struct is_integral<unsigned short> { static const bool value = true; };
template<> struct is_integral<int> { static const bool value = true; };
template<> struct is_integral<unsigned int> { static const bool value = true; };
template<> struct is_integral<long> { static const bool value = true; };
template<> struct is_integral<unsigned long> { static const bool value = true; };
template<> struct is_integral<long long> { static const bool value = true; };
template<> struct is_integral<unsigned long long> { static const bool value = true; };


template<class iterator_category>
struct is_input_iterator_tag { static const bool value = true; };

template<> struct is_input_iterator_tag<std::forward_iterator_tag> { static const bool value = false; };
template<> struct is_input_iterator_tag<std::bidirectional_iterator_tag> { static const bool value = false; };
template<> struct is_input_iterator_tag<std::random_access_iterator_tag> { static const bool value = false; };

} // namespace ft

#endif