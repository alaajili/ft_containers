/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:11:45 by alaajili          #+#    #+#             */
/*   Updated: 2022/12/04 11:49:31 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_H__
#define __TREE_H__

#include "iterator.hpp" 
#include "pair.hpp"
#include <memory>
#include <iostream>

enum colors { BLACK, RED };

template<class key_type, class value_type>
struct Node {
    key_type    key;
    value_type  val;
    Node*       parent;
    Node*       left;
    Node*       right;
    colors      color;
    
    Node() : key(), val(), parent(nullptr), left(nullptr), right(nullptr), color(BLACK) {}

    Node( const key_type& key, const value_type& val, Node* null ) :
        key(key), val(val), parent(nullptr), left(null), right(null), color(RED) {}
    ~Node() {}
};


template<class key_type, class value_type, class key_compare, class allocator_type>
class Tree {

public:
    typedef Node<key_type, value_type>                              node;
    typedef node*                                                   nodeptr;
    typedef value_type*                                             pointer;
    typedef const value_type*                                       const_pointer;
    typedef value_type&                                             reference;
    typedef const value_type&                                       const_refernce;
    typedef size_t                                                  size_type;
    typedef ft::TreeIterator<nodeptr, value_type>                   iterator;
    typedef ft::TreeIterator<nodeptr, const value_type>             const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
    typedef typename allocator_type::template rebind<node>::other   allocator_node;

//private:
    nodeptr         root;
    nodeptr         __null_;
    allocator_type  a;
    allocator_node  __alloc_;
    key_compare     compare;
    nodeptr         __begin_;
    size_type       __size_;


public:
    Tree( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ) : a(alloc), __alloc_(), compare(comp), __size_(0) {
        node tmp;
        __null_ = __alloc_.allocate(1);
        __alloc_.construct(__null_, tmp);
        root = __begin_ = __null_;
    }

    Tree( const Tree& t ) : a(t.a), __alloc_(t.__alloc_), compare(t.compare) , __size_(0) {
        node tmp;
        __null_ = __alloc_.allocate(1);
        __alloc_.construct(__null_, tmp);
        root = __begin_ = __null_;
        for (const_iterator it = t.begin(); it != t.end(); ++it) {
            nodeptr p = it.base();
            insert(p->key, p->val);
        }
    }

    Tree& operator=( const Tree& t ) {
        clear();
        a = t.a;
        __alloc_ = t.__alloc_;
        compare = t.compare;
        for (const_iterator it = t.begin(); it != t.end(); ++it) {
            nodeptr p = it.base();
            insert(p->key, p->val);
        }
        return *this;
    }

    ~Tree() {
        clear();
        __alloc_.destroy(__null_);
        __alloc_.deallocate(__null_, 1);
    }
    
    iterator begin() { return iterator(__begin_, __null_); }
    const_iterator begin() const { return const_iterator(__begin_, __null_); }
    
    iterator end() { return iterator(__null_, __null_); }
    const_iterator end() const { return const_iterator(__null_, __null_); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }


/*                          inseeeerrrrrrtttt                                       */
    ft::pair<iterator, bool> insert( const key_type& key, const value_type& val ) {
        iterator it = find(key);
        if (it != end())
            return ft::pair<iterator, bool>(it, false);

        

        node tmp(key, val, __null_);
        nodeptr n = __alloc_.allocate(1);
        __alloc_.construct(n, tmp);

        nodeptr x = root;
        nodeptr y = nullptr;
        
        while ( x != __null_ ) {
            y = x;
            if ( compare(n->key, x->key) )
                x = x->left;
            else
                x = x->right;
        }

        n->parent = y;
        if ( !y ) {
            root = n;
            __begin_ = n;
            __null_->parent = n;
        }
        else if ( compare(n->key, y->key) ) {
            y->left = n;
            if ( y == __begin_ )
                __begin_ = n;
        }
        else {
            y->right = n;
            if ( y == __null_->parent )
                __null_->parent = n;
        }

        __size_++;

        if ( n->parent == nullptr ) {
            n->color = BLACK;
            return ft::pair<iterator, bool>(iterator(n, __null_), true);
        }
        if ( n->parent->parent == nullptr )
            return ft::pair<iterator, bool>(iterator(n, __null_), true);     

        insertFix(n);
        return ft::pair<iterator, bool>(iterator(n, __null_), true);
    }

    void insertFix( nodeptr n ) {
        nodeptr uncle = nullptr;
        while (n->parent && n->parent->color == RED) {
            if ( n->parent == n->parent->parent->left ) {
                uncle = n->parent->parent->right;
                if (uncle->color == RED) {
                    uncle->color = n->parent->color = BLACK;
                    n->parent->parent->color = RED;
                    n = n->parent->parent;
                }
                else {
                    if ( n->parent->right == n ) {
                        n = n->parent;
                        leftRotate(n);
                    }
                    n->parent->color = BLACK;
                    n->parent->parent->color = RED;
                    rightRotate(n->parent->parent);
                }
            }
            else {
                uncle = n->parent->parent->left;
                if ( uncle->color == RED) {
                    uncle->color = n->parent->color = BLACK;
                    n->parent->parent->color = RED;
                    n = n->parent->parent;
                }
                else {
                    if ( n->parent->left == n ) {
                        n = n->parent;
                        rightRotate(n);
                    }
                    n->parent->color = BLACK;
                    n->parent->parent->color = RED;
                    leftRotate(n->parent->parent);
                }
            }
            if ( n == root )
                break ;
        }
        root->color = BLACK;
    } // fix insertion

    void leftRotate(nodeptr n) {
        nodeptr right = n->right;

        n->right = right->left;
        if (n->right != __null_)
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
        if (n->left != __null_)
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

        while ( t != __null_ ) {
            if ( compare(k, t->key) )
                t = t->left;
            else if ( compare(t->key, k) )
                t = t->right;
            else
                return iterator(t, __null_);
        }
        return this->end();
    } // find laydir lkhir

    const_iterator find( const key_type& k ) const {
        nodeptr t = root;
        
        while ( t != __null_ ) {
            if ( compare(k, t->key) )
                t = t->left;
            else if ( compare(t->key, k) )
                t = t->right;
            else
                return const_iterator(t, __null_);
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
        return iterator(r, __null_);
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
        return const_iterator(r, __null_);
    } // lower_bound const

    iterator upper_bound( const key_type& k ) {
        nodeptr t = root;
        nodeptr r = __null_;

        while ( t && t != __null_ ) {
            if ( compare(k, t->key) ) {
                r = t;
                t = t->left;
            }
            else
                t = t->right;
        }
        return iterator(r, __null_);
    } // upper_bound

    const_iterator upper_bound( const key_type& k ) const {
        nodeptr t = root;
        nodeptr r = __null_;

        while ( t && t != __null_ ) {
            if ( compare(k, t->key) ) {
                r = t;
                t = t->left;
            }
            else
                t = t->right;
        }
        return const_iterator(r, __null_);
    } // upper_bound const

    ft::pair<iterator, iterator> equal_range( const key_type& k ) {
        iterator low = lower_bound(k);
        iterator up = upper_bound(k);
        return ft::pair<iterator, iterator>(low, up);
    }

    ft::pair<const_iterator, const_iterator> equal_range( const key_type& k ) const {
        const_iterator low = lower_bound(k);
        const_iterator up = upper_bound(k);
        return ft::pair<const_iterator, const_iterator>(low, up);
    }


    bool empty() const { return (__size_ == 0); } // empty()

    size_type size() const { return __size_; } // size()

    size_type max_size() const { return __alloc_.max_size(); } // max_size()


    void clear() {
        if (empty())
            return;
        iterator f = begin();
        while ( f != end() ) {
            erase(f++);
        }
        root = __begin_ = __null_;
    }

    key_compare key_comp() const { return compare; }

    void swap( Tree& x ) {
        std::swap(root, x.root);
        std::swap(__alloc_, x.__alloc_);
        std::swap(a, x.a);
        std::swap(compare, x.compare);
        std::swap(__size_, x.__size_);
        std::swap(__begin_, x.__begin_);
        std::swap(__null_, x.__null_);
    }


    allocator_type get_allocator() const { return a; }


    void erase( iterator pos ) {
        nodeptr nd = pos.base();

        if ( nd == __null_ ) { nd = nullptr; }

        nodeptr x = nullptr;
        nodeptr y = nullptr;

        int originColor = nd->color;

        if ( nd->right == __null_) {
            x = nd->left;
            swapNodes(nd, nd->left);
        }
        else if ( nd->left == __null_ ) {
            x = nd->right;
            swapNodes(nd, nd->right);
        }
        else {
            y = getMaxValue(nd->left);
            originColor = y->color;
            x = y->left;
            if ( y->parent == nd )
                x->parent = y;
            else {
                swapNodes(y, y->left);
                y->left = nd->left;
                y->left->parent = y;
            }
            swapNodes(nd, y);
            y->right = nd->right;
            y->right->parent = y;
            y->color = nd->color;
        }
        __alloc_.destroy(nd);
        __alloc_.deallocate(nd, 1);
        if ( originColor == BLACK )
            eraseFix(x);
        __size_--;
        if (__size_ == 0)
            root = __begin_ = __null_;
        else {
            __begin_ = getMinValue(root);
            __null_->parent = getMaxValue(root);
        }
    }


    /*           helpers        */
    void swapNodes( nodeptr a, nodeptr b ) {
        if ( a->parent == nullptr )
            root = b;
        else if ( a == a->parent->left )
            a->parent->left = b;
        else
            a->parent->right = b;
        b->parent = a->parent;
    }

    nodeptr getMaxValue( nodeptr n ) {
        while ( n->right != __null_ )
            n = n->right;
        return n;
    } // get max 

    nodeptr getMinValue(nodeptr n) {
        while (n->left != __null_)
            n = n->left;
        return n;
    } // get min


    void eraseFix( nodeptr x ) {
        nodeptr n;

        while ( x != root && x->color == BLACK ) {
            if ( x == x->parent->left ) {
                n = x->parent->right;
                if ( n->color == RED ) {
                    n->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    n = x->parent->right;
                }
                if ( n->left->color == BLACK && n->right->color == BLACK ) {
                    n->color = RED;
                    x = x->parent;
                }
                else if ( n->right->color == BLACK ) {
                    n->left->color = BLACK;
                    n->color = RED;
                    rightRotate(n);
                }
                else {
                    n->color = x->parent->color;
                    x->parent->color = BLACK;
                    n->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                n = x->parent->left;
                if (n->color == RED) {
                    n->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    n = x->parent->left;
                }

                if ( n->left->color == BLACK && n->right->color == BLACK ) {
                    n->color = RED;
                    x = x->parent;
                }
                else if ( n->left->color == BLACK ) {
                    n->right->color = BLACK;
                    n->color = RED;
                    leftRotate(n);
                    n = x->parent->left;
                }
                else {
                    n->color = x->parent->color;
                    x->parent->color = BLACK;
                    n->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    
};



#endif