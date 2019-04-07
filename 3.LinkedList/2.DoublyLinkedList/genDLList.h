//****************** genDLList.h ************************
#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

class DLLNode {
public: 
    DLLNode() {
        next = prev = 0;
    }
    DLLNode(const int el, DLLNode *n = 0, DLLNode *p = 0) {
        info = el;
        next = n;
        prev = p;
    }
    int info;
    DLLNode *next, *prev;
};

class DoublyLinkedList {
public:
    DoublyLinkedList() {
        head = tail = 0;
    }
    ~DoublyLinkedList();
    int isEmpty() {
        return head == 0;
    }
    void addToDLLHead(int);
    void addToDLLTail(int);
    int deleteFromDLLHead();
    int deleteFromDLLTail();
    void deleteDLLNode(int);
    bool isInDLList(int) const;
    void printDLListFromHead();
    void printDLListFromTail();

  protected:
    DLLNode *head, *tail;
};

#endif