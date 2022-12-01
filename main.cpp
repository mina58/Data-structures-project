#include <iostream>
#include "AVL.h"

using namespace std;

int main() {
    AVL a;
    a.insert(1);
    a.levelOrderPrint();
    a.insert(2);
    a.levelOrderPrint();
    a.insert(3);
    a.levelOrderPrint();
    a.insert(4);
    a.levelOrderPrint();
    a.insert(5);
    a.levelOrderPrint();
    a.insert(6);
    a.levelOrderPrint();
    a.insert(7);
    a.levelOrderPrint();
    cout << a.search(8) << '\n';
    a.remove(4);
    a.levelOrderPrint();
    a.remove(5);
    a.levelOrderPrint();
    a.remove(2);
    a.levelOrderPrint();
    a.remove(7);
    a.levelOrderPrint();
    a.remove(3);
    a.levelOrderPrint();
    a.remove(1);
    a.levelOrderPrint();
    a.remove(6);
    a.levelOrderPrint();
    a.insert(1);
    a.levelOrderPrint();
    vector<int> v;
    a.inorderTraversal(v);
//    for (int i : v)
//        cout << i << ' ';
    cout << a.search(4);
}
