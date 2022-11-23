/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:11:45 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/23 01:13:20 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_H__
#define __TREE_H__

#include "iterator.hpp"
#include "pair.hpp"

enum colors { BLACK, RED };

template<class key_type, class value_type>
struct Node {
    key_type    key;
    value_type  val;
    Node*       parent;
    Node*       left;
    Node*       right;
    colors      color;
    
    Node() : parent(nullptr), left(nullptr), right(nullptr), color(BLACK) {}
    
    Node(const key_type& key, const value_type& val) :
        key(key), val(val), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
};


template<class key_type, class value_type, class key_compare, class allocator_type>
class Tree {

public:
    typedef Node<key_type, value_type>*                 nodeptr;
    typedef value_type*                                 pointer;
    typedef const value_type*                           const_pointer;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_refernce;
    typedef size_t                                      size_type;
    typedef ft::TreeIterator<nodeptr, value_type>       iterator;
    typedef ft::TreeIterator<nodeptr, const value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

//private:
    nodeptr         root;
    nodeptr         __null_;
    allocator_type  __alloc_;
    key_compare     compare;
    nodeptr         __begin_;
    size_type       __size_;

public:
    Tree( const allocator_type& alloc = allocator_type() ) : __alloc_(alloc), compare(), __size_(0) {
        __null_ = new Node<key_type, value_type>();
        root = __begin_ = __null_;
    }
    
    iterator begin() { return iterator(__begin_); }
    const_iterator begin() const { return const_iterator(__begin_); }
    
    iterator end() { return iterator(__null_); }
    const_iterator end() const { return const_iterator(__null_); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }


    ft::pair<iterator, bool> insert( const key_type& key, const value_type& val ) {
        iterator it = find(key);
        if (it != end())
            return ft::pair<iterator, bool>(it, false);

        value_type* p = __alloc_.allocate(1);
        __alloc_.construct(p, val);
        nodeptr n = new Node<key_type, value_type>(key, *p);
        if ( root == __null_ ) {
            __begin_ = n;
            n->right = __null_;
        }
        if ( compare(n->key, __begin_->key) )
            __begin_ = n;
        __size_++;
        root = BstInsert(root, n);
        insertFix(n);
        return ft::pair<iterator, bool>(iterator(n), true);
    }

    nodeptr BstInsert( nodeptr r, nodeptr n ) {
        if ( r == nullptr || r == __null_) {
            if ( r == __null_ ) {
                __null_->parent = n;
                n->right = __null_;
            }
            return n;
        }
        if ( compare(n->key, r->key) ) {
            r->left = BstInsert(r->left, n);
            r->left->parent = r;
        }
        else {
            r->right = BstInsert(r->right, n);
            r->right->parent = r;
        }
        return r;
    }

    void insertFix( nodeptr n ) {
        nodeptr parent = nullptr;
        nodeptr grand_parent = nullptr;
        while (n->parent && n->parent->color == RED) {
            parent = n->parent;
            grand_parent = parent->parent; 
            if (grand_parent->left == parent) {
                if (grand_parent->right && grand_parent->right->color == RED) {
                    grand_parent->left->color = grand_parent->right->color = BLACK;
                    grand_parent->color = RED;
                    n = grand_parent;
                }
                else {
                    if (parent->right && parent->right == n) {
                        n = parent;
                        leftRotate(n);
                        parent = n->parent;
                    }
                    parent->color = BLACK;
                    grand_parent->color = RED;
                    rightRotate(grand_parent);
                }
            }
            else {
                if (grand_parent->left && grand_parent->left->color == RED) {
                        grand_parent->left->color = grand_parent->right->color = BLACK;
                        grand_parent->color = RED;
                        n = grand_parent;
                }
                else {
                    if (parent->left && parent->left == n) {
                        n = parent;
                        rightRotate(n);
                        parent = n->parent;
                    }
                    parent->color = BLACK;
                    grand_parent->color = RED;
                    leftRotate(grand_parent);
                }
            }
        }
        root->color = BLACK;
    } // fix insertion

    void leftRotate(nodeptr n) {
        nodeptr right = n->right;

        n->right = right->left;
        if (n->right != nullptr)
            n->right->parent = n;
        right->parent = n->parent;
        if (n->parent == nullptr)
            root = right;
        else if (n == n->parent->left)
            n->parent->left = right;
        else
            n->parent->right = right;
        right->left = n;
        n->parent = right;        
    } // left rotate

    void rightRotate(nodeptr n) {
        nodeptr left = n->left;

        n->left = left->right;
        if (n->left)
            n->left->parent = n;
        left->parent = n->parent;
        if (n->parent == nullptr)
            root = left;
        else if (n == n->parent->left)
            n->parent->left = left;
        else
            n->parent->right = left;
        left->right = n;
        n->parent = left;
    } // right rotate


    iterator find( const key_type& k ) {
        nodeptr t = root;

        while ( t && t != __null_ ) {
            if ( compare(k, t->key) )
                t = t->left;
            else if ( compare(t->key, k) )
                t = t->right;
            else
                return iterator(t);
        }
        return this->end();
    } // find laydir lkhir

    const_iterator find( const key_type& k ) const {
        nodeptr t = root;
        
        while ( t && t != __null_ ) {
            if ( compare(k, t->key) )
                t = t->left;
            else if ( compare(t->key, k) )
                t = t->right;
            else
                return const_iterator(t);
        }
        return this->end();
    }


    size_type count( const key_type& k ) const {
        if (find(k) == end())
            return 0;
        return 1;
    } // count laydir lkhir


    iterator lower_bound( const key_type& k ) {
        nodeptr t = root;
        nodeptr r = __null_;

        while ( t && t != __null_ ) {
            if ( !compare(t->key, k) ) {
                r = t;
                t = t->left;
            }
            else
                t = t->right;
        }
        return iterator(r);
    } // lower_bound

    const_iterator lower_bound( const key_type& k ) const {
        nodeptr t = root;
        nodeptr r = __null_;

        while ( t && t != __null_ ) {
            if ( !compare(t->key, k) ) {
                r = t;
                t = t->left;
            }
            else
                t = t->right;
        }
        return const_iterator(r);
    } // lower_bound const

    iterator upper_bound( const key_type& k ) {
        nodeptr t = root;
        nodeptr = __null_;

        while ( t && t != __null_ ) {
            if ( compare(k, t->key) ) {
                r = t;
                t = t->left;
            }
            else
                t = t->right;
        }
        return iteratort(r);
    } // upper_bound

    const_iterator upper_bound( const key_type& k ) const {
        nodeptr t = root;
        nodeptr = __null_;

        while ( t && t != __null_ ) {
            if ( compare(k, t->key) ) {
                r = t;
                t = t->left;
            }
            else
                t = t->right;
        }
        return const_iteratort(r);
    } // upper_bound const

    ft::pair<iterator, iterator> equal_range( const key_type& k ) {
        iterator low = lower_bound(k);
        iterator up = up_bound(k);
        return ft::pair<iterator, iterator>(low, up);
    }

    ft::pair<const_iterator, const_iterator> equal_range( const key_type& k ) const {
        const_iterator low = lower_bound(k);
        const_iterator up = up_bound(k);
        return ft::pair<const_iterator, const_iterator>(low, up);
    }


    bool empty() const { return (__size_ == 0); } // empty()

    size_type size() const { return __size_; } // size()

    size_type max_size() const { return __alloc_.max_size(); } // max_size()

    

};



#endif