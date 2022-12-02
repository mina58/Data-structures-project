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


enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RBT {

private:
    //RBT node class
    class RBTNode {
    public:
        ElementType data;
        bool color; //true means red, false means black
        RBTNode *parent;
        RBTNode *left;
        RBTNode *right;

        //default constructor
        RBTNode(): data(0), color(true), parent(nullptr), left(nullptr), right(nullptr){};

        //parameterized constructor: takes the value of the node as a parameter
        RBTNode(ElementType data): data(data), color(true), parent(nullptr), left(nullptr), right(nullptr){};

        //parameterized constructor: takes the value of the node and the color as parameters
        RBTNode(ElementType data, bool isRed): data(data), color(isRed), parent(nullptr), left(nullptr), right(nullptr){};

        void clear() {
            if (left) {
                left->clear();
            }
            if (right) {
                right->clear();
            }
            delete this;
        }

    };// end of RBTNode

    RBTNode *root{};

    /***private member functions***/

    //this function performs right rotation on a node
    void rotateRight(RBTNode *node, bool changeColor);

    //this function performs left rotation on a node
    void rotateLeft(RBTNode *node, bool changeColor);

    //this function returns the sibling of a node
    RBTNode *sibling(RBTNode *node);

    //this is an auxiliary function that inserts a node in the tree
    RBTNode *insertAux(RBTNode *parent, RBTNode *&node, ElementType val);

    //this is an auxiliary function that fills a vector with the inorder
    void inorderAux(vector<ElementType> &v, RBTNode *node);

    /***public member functions***/

public:
    //this function inserts a node in the tree
    void insert(ElementType val);

    //this function takes a vector and fills it with the inorder traversal
    void inorder(vector<ElementType> &v);

};


#endif //DATA_STRUCTURES_PROJECT_RBT_H
