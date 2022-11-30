#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <sstream>
#include <climits>
#include <map>
#include <algorithm>

#include "pair.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "iterator.hpp"

#include "map.hpp"
#include "Tree.hpp"

// template<class T>
// void info_std(std::vector<T> v) {
//     std::cout << "SIZE : " << v.size() << std::endl;
//     std::cout << "CAPACITY : " << v.capacity() << std::endl;
//     for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
//         std::cout << *it << " ";
//     std::cout << std::endl;
// }

template<class T>
void info_ft(ft::vector<T>& v) {
    std::cout << "SIZE : " << v.size() << std::endl;
    std::cout << "CAPACITY : " << v.capacity() << std::endl;
    typedef typename ft::vector<T>::iterator iter;
    iter it = v.begin();
    for (;it != v.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    // it+=4;
    // std::cout << *it << std::endl;

}

void test_char(void){
    // std ::cout << "!***     std namespace    ***!" << std::endl;
    // std::vector<char> v;
    // v.assign(0, 'c');
    // info_std(v);
    // v.assign(64, 'A');
    // info_std(v);
    // v.assign(32, '5');
    // info_std(v);
    // v.assign(49, '8');
    // info_std(v);
    // v.assign(77, '2');
    // info_std(v);

    std ::cout << std::endl << "!***     ft namespace     ***!" << std::endl;
    ft::vector<char> w;
    // w.assign(0, 'c');
    // info_ft(w);
    w.assign(64, 'A');
    // for (size_t i = 0; i < w.size(); i++) std::cout << w[i] << " ";
    // std::cout << std::endl;
    //info_ft(w);
    // w.assign(32, '5');
    // info_ft(w);
    // w.assign(49, '8');
    // info_ft(w);
    // w.assign(77, '2');
    // info_ft(w);
}
void print_info(ft::map<int, char>& m);
int main() {
    // test_char();
    // int arr[] = {2, 9, 5, 7};
    // std::vector<int> v(arr, arr+4);
    // std::cout << "capacity: " << v.capacity() << std::endl;
    // std::cout << "size: " << v.size() << std::endl;
    // std::vector<int>::iterator it = v.begin();
    // for (; it != v.end(); it++)
    //     std::cout << *it << " ";
    // std::cout << std::endl;

    
    // int arr[] = {3, 1, 7, 2};
    // ft::vector<char> v;
    // v.assign(64, 'A');
    // std::cout << "capacity: " << v.capacity() << std::endl;
    // std::cout << "size: " << v.size() << std::endl;
    // ft::vector<char>::iterator it = v.begin();
    // for(; it != v.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;
    // ft::vector<std::string> v1(5,"hello");
    //std::cout << v1.end() - v1.begin() << std::endl;
    // ft::vector<std::string> v2(v1.begin(), v1.end());

    // if (&v1[0] == &v2[0]) {
    //     std::cout << "Copy ctor doesn't do a deep copy!" << std::endl;
    // }
    // else{
    //     ft::vector<std::string>::iterator it = v2.begin();
    //     for (; it != v2.end(); ++it) { std::cout << *it << std::endl; }
    // {
    //     std::cout << "\\-----------STD-----------/" << std::endl;
    //     std::vector<int> v(5, 100);
    //     std::vector<int>::iterator it = v.insert(v.begin() + 4, 2);
    //     std::cout << *it << std::endl;
    //     std::cout << "SIZE = " << v.size() << std::endl;
    //     std::cout << "CAPACITY = " << v.capacity() << std::endl;
    //     for (it = v.begin(); it != v.end(); ++it)
    //         std::cout << *it << " ";
    //     std::cout << std::endl;
    // }
    
    {
        // std::cout << "\\-----------FT-----------/" << std::endl;
        // ft::vector<int> v;
        // ft::vector<int>::iterator it = v.insert(v.end(), 2);
        // std::cout << *it << std::endl;
        // it = v.insert(v.end(), 3);
        // std::cout << *it << std::endl;
        // // it = v.insert(v.begin(), 4);
        // // std::cout << *it << std::endl;
        // // it = v.insert(v.begin()+1, 5);
        // // std::cout << *it << std::endl;
        // std::cout << "SIZE = " << v.size() << std::endl;
        // std::cout << "CAPACITY = " << v.capacity() << std::endl;
        // for (it = v.begin(); it != v.end(); ++it)
        //     std::cout << *it << " ";
        // // std::cout << std::endl;
        // std::istringstream str("1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        // std::istreambuf_iterator<char> it(str), end;
        // ft::vector<char> v(it, end);
        // std::cout << "SIZE: " << v.size() << std::endl;
        // std::cout << "CAPACITY: " << v.capacity() << std::endl;
        // ft::vector<char>::iterator it2;
        // for (it2 = v.begin(); it2 != v.end(); ++it2) { std::cout << *it2 << " "; }
        // std::cout << std::endl;
    }
    {
        // ft::vector<int> v1(5, 4);
        // ft::vector<int> v2(4, 5);
        // std::cout << "V1 SIZE: " << v2.size() << std::endl;
        // std::cout << "V1 CAPACITY: " << v2.capacity() << std::endl;
        // v2 = v1;
        // // v1.swap(v2);
        // std::cout << "V1 SIZE: " << v2.size() << std::endl;
        // std::cout << "V1 CAPACITY: " << v2.capacity() << std::endl;
        // ft::vector<int>::iterator it;
        // std::cout << "V1 CONTENT:";
        // for(it = v2.begin(); it != v2.end(); ++it)
        //     std::cout << " " << *it;
        // std::cout << std::endl;
        // std::cout << "----------------------------" << std::endl;
        // std::cout << "V2 SIZE: " << v2.size() << std::endl;
        // std::cout << "V2 CAPACITY: " << v2.capacity() << std::endl;
        // std::cout << "V2 CONTENT:";
        // for(it = v2.begin(); it != v2.end(); ++it)
        //     std::cout << " " << *it;
        // std::cout << std::endl;
        // v1.resize(0);
        // ft::swap(v1, v2);

        // ft::vector<char> alloc;
        // std::cout << alloc.max_size() << std::endl;
    }
    {
        // Tree<int, std::string, std::less<int>, std::allocator<std::string> > tree;

        // tree.insert(6, "six");
        // tree.insert(9, "nine");
        // tree.insert(11, "eleven");
        // tree.insert(2, "two");
        // tree.insert(10, "ten");
        // tree.insert(4, "four");
        // tree.insert(3, "three");
        // tree.insert(8, "eight");
        // tree.insert(12, "twelve");

        
        // Tree<int, std::string, std::less<int>, std::allocator<std::string> >::iterator it;
        // it = tree.begin();
        // for (; it != tree.end(); it++) std::cout << *it << std::endl;
    }

    // {
    //     typedef  std::map<int, char>::iterator iterator;
    //     std::cout << "STD :\n";
    //     std::map<int, char> m;
    //     m.insert(std::pair<int, char>(2, 'b'));
    //     m.insert(std::pair<int, char>(4, 'd'));
    //     m.insert(std::pair<int, char>(1, 'a'));
    //     m.insert(std::pair<int, char>(6, 'f'));
        
    //     iterator itlow = m.lower_bound(0);
    //     iterator itup = m.upper_bound(0);
    //     std::cout << "lower bound " << itlow->first << std::endl;
    //     std::cout << "upper bound " << itup->first << std::endl;

    //     iterator it;
    //     for (it = m.begin(); it != m.end(); it++) { std::cout << it->first<< " ----> " << it->second << std::endl; }
    // }
    // std::cout << "\n";
    {
        // typedef  ft::map<int, char>::iterator iterator;
        // typedef  ft::map<int, char>::reverse_iterator reverse_iterator;

        ft::map<int, char> m;
        m[1] = 'a';
        m[2] = 'b';
        m[3] = 'c';
        m[4] = 'd';
        m[5] = 'e';
        m[6] = 'f';
        print_info(m);
        
        m.erase(2);
        // m.erase(15);
        // print_info(m);
        // m.erase(15);
        // print_info(m);
        // for (int i = 0; i < 2; i++) {
        //     iterator it = m.begin();
        //     std::advance(it, 2);
        //     m.erase(it);
        //     print_info(m);
        // }
        
        
        //iterator it = m.begin();
        //m.clear();
        // std::map<int, char> m2 = m;
        // if (m == m2) {
        //     std::cout << "HHH" << std::endl;
        // }
        //iterator it = m.find(11);
        //iterator it = m.begin();
        //m.erase(m.begin());
        // --it;
        // std::cout << m.size() << std::endl;
        // std::cout << (--m.end())->first << std::endl;
        // print_info(m);


        // reverse_iterator rit = m.rbegin();
        // std::cout << rit->first << std::endl;

        // iterator it = m.end();
        // --it;
        // std::cout << it->first << std::endl;
        //m.erase(rit->first);
        // for (it = m.begin(); it != m.end(); it = m.begin()) {
        //     m.erase(it);
            
        // }

        // it = m.begin();
        // std::cout << it->first << std::endl;
        // iterator end = it;
        // std::advance(it, 15);
        // std::advance(end, 20);
        // m.erase(it, end);
        // std::advance(i, 1);
        // m.erase(i);

        // i = m.end();
        // std::advance(i, -10);
        // m.erase(i);
        // print_info(m);

        // i = m.end();
        // std::advance(i, -19);
        // m.erase(i);
        // print_info(m);

        // i = m.end();
        // std::advance(i, -1);
        // m.erase(i);
        // print_info(m);
        // std::cout << i.base()->left->key << std::endl;
        // std::cout << i->first << " ------> " << i->second << std::endl;
        // m2.clear();
        // m2.insert(m.begin(), m.end());
        // iterator itlow = m2.lower_bound(0);
        // iterator itup = m2.upper_bound(0);
        // std::cout << "lower bound " << itlow->first << std::endl;
        // std::cout << "upper bound " << itup->first << std::endl;
        // std::cout << m2.size() << std::endl;
        // iterator it;
        // for (it = m.begin(); it != m.end(); it++) { std::cout << it->first<< " ----> " << it->second << std::endl; }
    }

}
void print_info(ft::map<int, char>& m){
    typedef  ft::map<int, char>::iterator iterator;
    iterator it;
    for (it = m.begin(); it != m.end(); ++it){
        std::cout << it->first << " >>>> " << it->second << std::endl;
    }
    std::cout <<"\n";
}