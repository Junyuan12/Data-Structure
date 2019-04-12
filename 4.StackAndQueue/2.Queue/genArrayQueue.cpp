#include <iostream>
#include "genArrayQueue.h"

using namespace std;

template<class T, int size>
void ArrayQueue<T,size>::enqueue(T el) {
   if (!isFull())
        if (last == size-1 || last == -1) {
            storage[0] = el;
            last = 0;
            if (first == -1)
                first = 0;
        }
        else storage[++last] = el;
   else cout << "Full queue.\n";
}

template<class T, int size>
T ArrayQueue<T,size>::dequeue() {   
	T tmp;
    tmp = storage[first];
    if (first == last)
         last = first = -1;
    else if (first == size-1)
         first = 0;
    else first++;
    return tmp;
}

int main() {
    ArrayQueue<int, 3> q1;
    if (q1.isEmpty()) {
        cout << "is empty.\n" << endl;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    int st = q1.dequeue();
    cout << st << endl;
    }
    
    system("pause");
    return 0;
}