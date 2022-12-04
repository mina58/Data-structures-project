#include <iostream>
#include "AVL.h"
#include "RBT.h"

using namespace std;

int main() {
    RBT rbt;
    for (int i = 1; i <= 20; i++) {
        rbt.insertValue(i);
    }

    rbt.levelOrderPrint();
    rbt.deleteValue(4);
    rbt.deleteValue(8);
    rbt.deleteValue(7);
    rbt.deleteValue(20);
    rbt.deleteValue(16);
    rbt.deleteValue(3);
    rbt.deleteValue(9);
    rbt.levelOrderPrint();

}
