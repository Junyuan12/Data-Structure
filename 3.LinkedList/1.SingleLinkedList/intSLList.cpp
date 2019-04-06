//*************** intSLList.cpp *********************

#include <iostream>
#include "intSLList.h"

IntSLList::~IntSLList() {
    for (IntSLLNode *p; isEmpty();) {
        p = head->next;
        delete head;
        head = p;
    }
}

void IntSLList::addToHead(int el) {
    head = new IntSLLNode(el, head);
    if (tail == 0)
        tail = head;
}

void IntSLList::addToTail(int el) {
    if (tail != 0) { // if list not empty
        tail->next = new IntSLLNode(el);
        tail = tail->next;
    }
    else
        head = tail = new IntSLLNode(el);
}

int IntSLList::deleteFromHead() {
    int el = head->info;
    IntSLLNode *tmp = head;
    if (head == tail) // if only one node in the list;
        head = tail = 0;
    else
        head = head->next;
    delete tmp;
    return el;
}

int IntSLList::deleteFromTail() {
    int el = tail->info;
    if (head == tail){ // if only one node in the list;
        delete head;
        head = tail = 0;
    }
    else { // if more than one node in the list,
        IntSLLNode *tmp; // find the predecessor of tail;
        for (tmp = head; tmp->next != tail; tmp = tmp->next);
        delete tail;
        tail = tmp; // the predecessor of tail becomes tail;
        tail->next = 0;
        }
        return el;
}

void IntSLList::deleteNode(int el) {
    if (head != 0){ // if nonempty list;
        if (head == tail && el == head->info) { // if only one
            delete head;                        // node in the list;
            head = tail = 0;
        }
        else if (el == head->info) { // if more than one node in the list
            IntSLLNode *tmp = head;
            head = head->next;
            delete tmp; // and old head is delete;
        }
        else { // if more than one node in the list;
            IntSLLNode *pred, *tmp;
            for (pred = head, tmp = head->next; // and a nohead node
                 tmp != 0 && !(tmp->info == el); // is delete;
                 pred = pred->next, tmp = tmp->next);
            if (tmp != 0) {
            pred->next = tmp->next;
            if (tmp == tail)
                tail = pred;
            delete tmp;
            }
        }
    }
}

bool IntSLList::isInList(int el) const {
    IntSLLNode *tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}

void IntSLList::printList(){
    IntSLLNode *tmp = head;
    while (tmp != 0) {
        std::cout << tmp->info << std::endl;
        tmp = tmp->next;
    }
}

int main() {
    IntSLLNode *p = new IntSLLNode(10);
    p->next = new IntSLLNode(8);
    p->next->next = new IntSLLNode(6);

    IntSLList list;
    list.addToHead(5);
    list.addToHead(6);
    list.addToHead(7);
    list.addToHead(8);
    list.deleteFromHead();
    list.printList();

    system("pause");
    return 0;
}
