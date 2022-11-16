/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:47:26 by alaajili          #+#    #+#             */
/*   Updated: 2022/11/12 19:32:49 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#include <functional>

#define BLACK 0
#define RED 1

template<class T>
struct Node {
    T val;
    Node* parent;
    Node* left;
    Node* right;
    int color;

    Node(T val) :
        val(val), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
};

template<class T, class C = std::less<T> >
Node<T>* BstInsert(Node<T>* root, Node<T>* n, C c = C()) {
    if (root == nullptr)
        return n;
    if (c(n->val, root->val)) {
        root->left = BstInsert(root->left, n);
        root->left->parent = root;
    }
    else {
        root->right = BstInsert(root->right, n);
        root->right->parent = root;
    }
    return root;
}

template<class T, class Compare>
class RedBlackTree
{
public:
    typedef Node<T>*    nodeptr;

//private:
    nodeptr root;


public:
    RedBlackTree() : root(nullptr) {}

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

    void insert( const T& val ) {
        nodeptr n = new Node<T>(val);

        root = BstInsert(root, n);
        nodeptr parent = nullptr;
        nodeptr grand_parent = nullptr;

        while (n->parent && n->parent->color == RED) {
            parent = n->parent;
            grand_parent = parent->parent;

            if (grand_parent->left == parent) {
                if (grand_parent->right->color == RED) {
                    grand_parent->left->color = grand_parent->right->color = BLACK;
                    grand_parent->color = RED;
                    n = grand_parent;
                }
                else {
                    if (parent->right == n) {
                        n = parent;
                        leftRotate(n);
                    }
                    parent->color = BLACK;
                    grand_parent->color = RED;
                    rightRotate(grand_parent);
                }
            }
            else {
                if (grand_parent->left->color == RED) {
                        grand_parent->left->color = grand_parent->right->color = BLACK;
                        grand_parent->color = RED;
                        n = grand_parent;
                }
                else {
                    if (parent->left == n) {
                        n = parent;
                        rightRotate(n);
                    }
                    parent->color = BLACK;
                    grand_parent->color = RED;
                    leftRotate(grand_parent);
                }
            }
        }
        root->color = BLACK;
    } // insertion

    
    nodeptr find( const T& val ) {
        nodeptr t = root;
        
        while (t != nullptr) {
            if (val < t->val)
                t = t->left;
            else if (val > t->val)
                t = t->right;
            else
                return t;
        }
        return nullptr;
    } // searching

    void transplant(nodeptr a, nodeptr b) {
        if (a->parent == nullptr)
            root = b;
        else if (a == a->parent->left)
            a->parent->left = b;
        else
            a->parent->right = b;
        b->parent = a->parent;
    } // transplant

    nodeptr getMinValue( nodeptr n ) {
        while (n->left != nullptr)
            n = n->left;
        return n;
    } // get minimum value of a right-subtree

    void deleteNode( const T& val ) {
        nodeptr dn = find(val);
        if ( !root || !dn ) { return ; }
        nodeptr x, y;
        int originColor = dn->color;
        if ( !dn->left ) {
            x = dn->right;
            transplant(dn, x);
        }
        else if ( !dn->right ) {
            x = dn->left;
            transplant(dn, x);
        }
        else {
            y = getMinValue(dn->right); // assign min val of right sub-tree into y
            originColor = y->color;
            x = y->right;
            // if (x->parent == y)
            //     std::cout << "WAAAAH" << std::endl;
            // if (y->parent == dn)
            //     x->parent = y;
            if (y->parent != dn) {
                std::cout << "HERE" << std::endl;
                transplant(y, y->right);
                y->right = dn->right;
                y->right->parent = y;
            }
            transplant(dn, y);
            y->left = dn->left;
            y->left->parent = y;
            y->color = dn->color;
        }
        delete dn;
        if (originColor == BLACK) { deleteFix(x); }
    } // delete a node

    
    void deleteFix(nodeptr x) {
        nodeptr w;
        
        while ( x != root && x->color == BLACK ) {
            if ( x == x->parent->left ) {
                w = x->parent->right;
                if ( w->color == RED ) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ( w->left->color == BLACK && w->right->color == BLACK ) {
                    w->color = RED;
                    x = x->parent;
                }
                else if ( w->right->color == BLACK ) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                else {
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ( w->left->color == BLACK && w->right->color == BLACK ) {
                    w->color = RED;
                    x = x->parent;
                }
                else if ( w->left->color == BLACK ) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                else {
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    } // fix rbt after deletion

};

#endif
