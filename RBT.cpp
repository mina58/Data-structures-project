//
// Created by Mina on 01-Dec-22.
//

#include <iostream>
#include "RBT.h"

using namespace std;

void RBT::rotateRight(RBT::RBTNode *node, bool changeColor) {
    RBTNode *parent = node->parent; //this will hold my old parent
    node->parent = parent->parent; //my new parent is my grandparent
    if (parent->parent != nullptr) { //if my new parent is not null then I need to adjust its
        // left or right to point on me
        if (parent->parent->right == parent)
            parent->parent->right = node;//if my old parent was a right child then
            // I should be the right child of my new parent
        else
            parent->parent->left = node; //else I should be the left child
    }

    RBTNode *right = node->right; // this will hold my right child
    node->right = parent; //my old parent will be my right child
    parent->parent = node; //and I will be his parent
    parent->left = right; //my old parent's left child now will be my right child
    if (right != nullptr)
        right->parent = parent; //if my right child was not null, make its parent my old parent

    if (changeColor) {
        node->color = false; //recolor myself
        parent->color = true; // and my old parent
    }
}

void RBT::rotateLeft(RBT::RBTNode *node, bool changeColor) {
    RBTNode *parent = node->parent;
    node->parent = parent->parent;
    if (node->parent != nullptr) {
        if (node->parent->right == parent)
            node->parent->right = node;
        else
            node->parent->left = node;
    }

    RBTNode *left = node->left;
    node->left = parent;
    parent->parent = node;
    parent->right = left;
    if (left != nullptr)
        left->parent = parent;

    if (changeColor) {
        node->color = false; //recolor myself
        parent->color = true; // and my old parent
    }
}

void RBT::insert(ElementType val) {
    if (root == nullptr)
        root = new RBTNode(val, false);
    else
        insertAux(nullptr, root, val);
}

RBT::RBTNode *RBT::insertAux(RBT::RBTNode *parent, RBT::RBTNode *&node, ElementType val) {
    if (node == nullptr) { //we insert here
        node = new RBTNode(val, true);
        node->parent = parent;
        return node;
    }
    bool isLeft; //tells us which side of the tree we went to

    if (node->data == val) {
        cerr << "Cannot have duplicates in the tree";
        exit(1);
    }

    if (node->data > val) {
        RBTNode *left = insertAux(node, node->left, val); //insert in the left subtree

        //if the returned node is now our parent, this mean that rotations happened and there are no conflicts
        //below us, so we just return out new parent to be dealt with at the higher level
        if (left == node->parent)
            return left;

        //else we just assign the left to our left subtree
        node->left = left;

        isLeft = true;
    } else {
        RBTNode *right = insertAux(node, node->right, val);
        if (right == node->parent)
            return right;
        node->right = right;

        isLeft = false;
    }

    if (isLeft) { //fix the left
        if (node->color && node->left && node->left->color) { //check for red red conflict
            RBTNode *sib = sibling(node); //this is my sibling
            //check which case I am in
            if (sib == nullptr || !sib->color) { //black sibling
                if (node->parent->left == node) { //left left case
                    rotateRight(node, true);
                } else { //left right case
                    rotateRight(node->left, false);
                    node = node->parent;
                    rotateLeft(node, true);
                }
            } else { //red sibling
                node->color = false;
                sib->color = false;
                if(node->parent != root)
                    node->parent->color = true;
            }
        }
    } else { //fix the right
        if (node->color && node->right && node->right->color) { //check for red red conflict
            RBTNode *sib = sibling(node);
            if (sib == nullptr || !sib->color) {
                if (node->parent->right == node) { //right right case
                    rotateLeft(node, true);
                } else { //right left case
                    rotateLeft(node->right, false);
                    node = node->parent;
                    rotateRight(node, true);
                }
            } else {
                node->color = false;
                sib->color = false;
                if(node->parent != root)
                    node->parent->color = true;
            }
        }
    }
    return node;

}

RBT::RBTNode *RBT::sibling(RBT::RBTNode *node) {
    RBTNode *parent = node->parent;
    if (parent->left == node)
        return parent->right;
    else
        return parent->left;
}

void RBT::inorder(vector<ElementType> &v) {
    if (root == nullptr)
        return;
    inorderAux(v, root);
}

void RBT::inorderAux(vector<ElementType> &v, RBT::RBTNode *node) {
    if (node->left != nullptr)
        inorderAux(v, node->left);
    v.push_back(node->data);
    if (node->right != nullptr)
        inorderAux(v, node->right);
}
