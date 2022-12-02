#include <iostream>
#include "AVL.h"
#include "RBT.h"

using namespace std;

int main() {
    RBT rbt;
//    srand(122);
    for (int i = 1; i <= 20; i++) {
        rbt.insertValue(i);
    }
    rbt.levelOrderPrint();
    for (int i = 1; i <= 18; i++) {
        rbt.deleteValue(i);
        rbt.levelOrderPrint();
    }
    rbt.deleteValue(19);
    rbt.levelOrderPrint();
    rbt.deleteValue(20);
    rbt.levelOrderPrint();
}
