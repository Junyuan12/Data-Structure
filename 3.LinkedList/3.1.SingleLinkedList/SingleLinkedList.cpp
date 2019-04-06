#include <iostream>

using namespace std;

class IntSLLNode {
public:
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(int i, IntSLLNode * in = 0) {
        info = i;
        next = in;
    }

    int info;
    IntSLLNode *next;
};

int main() {
    IntSLLNode *p = new IntSLLNode(10);
    p->next = new IntSLLNode(8);
    p->next->next = new IntSLLNode(50);
    return 0;
}