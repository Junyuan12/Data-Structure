#include <iostream>
#include "genDLList.h"

DoublyLinkedList::~DoublyLinkedList() {
    for (DLLNode *p = head; isEmpty();) {
        p = head->next;
        delete head;
        head = p;
    }
}

void DoublyLinkedList::addToDLLHead(int el) {
    if (head != 0) {
        head = new DLLNode(el, head, 0);
        head->next->prev = head;
    }
    else {
        tail = head = new DLLNode(el);
    }
}

void DoublyLinkedList::addToDLLTail(int el) {
    if (tail != 0) {
        tail = new DLLNode(el, 0, tail);
        tail->prev->next = tail;
    }
    else
        head = tail = new DLLNode(el);
}

int DoublyLinkedList::deleteFromDLLHead() {
    int el = head->info;
    if (head == tail) {
        delete head;
        head = tail = 0;
    }
    else {
        head = head->next;
        delete head->prev;
        head->prev = 0;
    }
    return el;
}

int DoublyLinkedList::deleteFromDLLTail() {
    int el = tail->info;
    if (head == tail) { // if only one node in the list;
        delete head;
        head = tail = 0;
    }
    else { // if more than one node in the list;
        tail = tail->prev;
        delete tail->next;
        tail->next = 0;
    }
    return el;
}

void DoublyLinkedList::deleteDLLNode(int el) {
    if (head != 0) {
        if (head == tail && el == head->info) {
            delete head;
            head = tail = 0;
        }
        else if (el == head->info) {
            DLLNode *tmp = head;
            head = head->next;
            head->prev = 0;
            delete tmp;
        }
        else {
            DLLNode *tmp = head->next;
            for (; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
            if (tmp != 0) {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }
            if (tmp == tail) {
                tail = tmp->prev;
            }
            delete tmp;
        }
    }
}

bool DoublyLinkedList::isInDLList(int el) const {
    DLLNode *tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}

void DoublyLinkedList::printDLListFromHead() {
    DLLNode *p = head;
    while(p != 0) {
        std::cout << p->info << std::endl;
        p = p->next;
    }
}

void DoublyLinkedList::printDLListFromTail() {
    DLLNode *p = tail;
    while(p != 0) {
        std::cout << p->info << std::endl;
        p = p->prev;
    }
}

int main() {
    DoublyLinkedList list;
    list.addToDLLHead(3);
    list.addToDLLHead(2);
    list.addToDLLHead(1);
    list.addToDLLTail(4);
    list.addToDLLTail(5);
    list.deleteFromDLLHead();
    list.deleteFromDLLTail();
    if (list.isInDLList(3)){
        std::cout << "Element is in the list!" << std::endl;
    }
    list.deleteDLLNode(3);
    list.printDLListFromHead();
    system("pause");
    return 0;
}