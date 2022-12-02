//
// Created by Mina on 01-Dec-22.
//

#ifndef DATA_STRUCTURES_PROJECT_RBT_H
#define DATA_STRUCTURES_PROJECT_RBT_H

#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

typedef int ElementType;


enum Color {
    RED, BLACK, DOUBLE_BLACK
};


class RBT {

private:
//    RBT node struct
    struct Node {
        ElementType data;
        int color;
        Node *left, *right, *parent;

        explicit Node(ElementType data) :
                data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {} //initialize an empty red node
    };


    Node *root;

    /***private member functions***/

    //this function rotates a node to the left
    void rotateLeft(Node *&node);

    //this function rotates a node to the right
    void rotateRight(Node *&node);

    //this function fixes the tree after insertion
    void fixInsert(Node *&node);

    //this function fixes the tree after deletion
    void fixDelete(Node *&node);

    //this function prints the inorder traversal of the tree
    void inorderAux(Node *&node);

    //this function prints the preorder traversal of the tree
    void preorderAux(Node *&node);

    //this function gets the color of a node
    static int getColor(Node *&node);

    //this function sets the color of a node
    static void setColor(Node *&node, int color);

    //this function return the node with the min value in a subtree
    Node *minValueNode(Node *&node);

    //this function inserts a node in the tree
    Node* insertAux(Node *&root, Node *&node);

    //this function deletes a node from the tree
    Node* deleteAux(Node *&node, int val);

public:

    /***public member functions***/

    //default constructor
    RBT();

    //user function to insert value
    void insertValue(ElementType val);

    //user function to delete value
    void deleteValue(ElementType val);

    //user function to get inorder
    void inorder();

    //user function to get preorder
    void preorder();

    //this function prints the tree in level order
    void levelOrderPrint();

    //this function checks if the tree is empty
    bool empty();

};


#endif //DATA_STRUCTURES_PROJECT_RBT_H
