#include <iostream>
#include "AVL.h"
#include "RBT.h"

using namespace std;

int main() {
    RBT t{};
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    vector<int> v;
    t.inorder(v);
    for (int i : v) {
        cout << i << ' ';
    }
}
