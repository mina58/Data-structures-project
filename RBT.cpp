//
// Created by Mina on 01-Dec-22.
//

#include <iostream>
#include "RBT.h"
#include <queue>

using namespace std;

RBT::RBT() : root(nullptr) {}

int RBT::getColor(RBT::Node *&node) {
    if (node == nullptr)
        return BLACK;
    return node->color;
}

void RBT::setColor(RBT::Node *&node, int color) {
    if (node == nullptr)
        return;
    node->color = color;
}

void RBT::insertValue(ElementType val) {
    Node *node = new Node(val);
    root = insertAux(root, node);
    fixInsert(node);
}

RBT::Node *RBT::insertAux(RBT::Node *&root, RBT::Node *&node) {
    if (root == nullptr)
        return node;
    if (node->data < root->data) {
        root->left = insertAux(root->left, node);
        root->left->parent = root;
    } else if (node->data > root->data) {
        root->right = insertAux(root->right, node);
        root->right->parent = root;
    } else {
        cerr << "cannot have duplicates in the tree. exiting program";
        exit(1);
    }
    return root;
}

void RBT::fixInsert(RBT::Node *&node) {
    Node *parent = nullptr, *grandParent = nullptr;
    //iteratively fix the tree from bottom to top
    while (node != root && getColor(node) == RED && getColor(node->parent) == RED) {
        parent = node->parent;
        grandParent = parent->parent;

        Node *uncle;
        if (parent == grandParent->left) {
            uncle = grandParent->right;
            if (getColor(uncle) == RED) { //simple case, we just recolor
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandParent, RED);
                node = grandParent;
                //now we are done with this iteration, in the next iteration we check if recoloring the grandparent
                //cause any conflicts
            } else { //black uncle case, this means that we must make rotations
                if (node == parent->right) { //left right case
                    rotateLeft(parent); //turn it to a left left case
                    //fix the pointer after rotation
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandParent); // fix the left left case
                swap(grandParent->color, parent->color); //recoloring
                node = parent; //now the parent is the new root of the subtree, so we will fix it in the next iteration
            }
        } else {
            //this is the mirror of the above case
            uncle = grandParent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandParent, RED);
                node = grandParent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandParent);
                swap(grandParent->color, parent->color);
                node = parent;
            }
        }
    }
    setColor(root, BLACK); //root should always be black
}

RBT::Node *RBT::minValueNode(RBT::Node *&node) {
    Node *temp = node;
    while (temp->left != nullptr)
        temp = temp->left;
    return temp;
}

bool RBT::empty() {
    return root == nullptr;
}

void RBT::rotateRight(RBT::Node *&node) {
    Node *leftChild = node->left; //my left child who will later become my parent

    node->left = leftChild->right;

    //if my left now is not null we need to change its parent pointer to point to me
    if (node->left != nullptr)
        node->left->parent = node;

    //now my old left child's parent should be my old parent
    leftChild->parent = node->parent;

    //if my parent was null this means I was the root and my left child is the new root now
    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left) //if I was a left child then my left child should replace me as left
        node->parent->left = leftChild;
    else //else my left child will replace me as right
        node->parent->right = leftChild;

    leftChild->right = node; //I am now the right child of my old left child
    node->parent = leftChild; // and my old left child is now my parent
}

void RBT::rotateLeft(RBT::Node *&node) {
    Node *rightChild = node->right;
    node->right = rightChild->left;
    if (node->right != nullptr)
        node->right->parent = node;
    rightChild->parent = node->parent;
    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->right)
        node->parent->right = rightChild;
    else
        node->parent->left = rightChild;
    rightChild->left = node;
    node->parent = rightChild;
}

void RBT::levelOrderPrint() {
    if (empty()) {
        cout << "empty tree";
        return;
    }
    queue<Node *> q;
    Node *cur = root;
    q.push(root);
    while (!q.empty()) {
        int size = (int) q.size();
        while (size--) {
            cur = q.front();
            q.pop();
            cout << cur->data << ' ';
            if (cur->left != nullptr)
                q.push(cur->left);
            if (cur->right != nullptr)
                q.push(cur->right);
        }
        cout << '\n';
    }
    cout << '\n';
}

void RBT::deleteValue(ElementType val) {
    Node *node = deleteAux(root, val);
    fixDelete(node);
}

RBT::Node *RBT::deleteAux(RBT::Node *&node, int val) {
    if (node == nullptr)
        return node;
    if (node->data > val)
        return deleteAux(node->left, val);
    if (val > node->data)
        return deleteAux(node->right, val);

    //found
    if (node->left == nullptr || node->right == nullptr)
        return node; //no need to switch with successor, already a 1 child or 0 child case

    Node *successor = minValueNode(node->right);
    node->data = successor->data;
    return deleteAux(node->right, successor->data);
}

void RBT::fixDelete(RBT::Node *&node) {

    if (node == nullptr)
        return;

    if (node == root) {
        if (node->right != nullptr)
            root = node->right;
        else if (node->left != nullptr)
            root = node->left;
        else
            root = nullptr;
        delete node;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}








