//******************** genArrayQueue.h ****************************
//        generic queue implemented as an array

#ifndef ARRAY_QUEUE
#define ARRAY_QUEUE

template<class T, int size = 100>
class ArrayQueue {
public:
    ArrayQueue() {
        first = last = -1;
    }
    void enqueue(T);
    T dequeue();
    bool isFull() {
        return (first == 0 && last == size - 1) || first == last + 1;
    }
    bool isEmpty() {
        return first == -1;
    }

  private:
    int first, last;
    T storage[size];
};

#endif