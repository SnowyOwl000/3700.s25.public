#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdexcept>

using namespace std;

const uint32_t
    QUEUE_SIZE = 16;
  
template <typename QueueType>
class Queue {
public:
    Queue() {
  
        count = tail = 0;
        head = QUEUE_SIZE - 1;
    }
  
    ~Queue() = default;
  
    void clear() { count = tail = 0; head = QUEUE_SIZE - 1; }
  
    uint32_t size() { return count; }
    bool isEmpty() { return count == 0; }
  
    void enqueue(QueueType d) {

        if (count == QUEUE_SIZE)
            throw overflow_error("Queue is full");
      
        data[tail] = d;

        tail = ++tail % QUEUE_SIZE;

        count++;
    }
  
    QueueType dequeue() {
  
        if (count == 0)
            throw underflow_error("Queue is empty");

        head = ++head % QUEUE_SIZE;

        count--;

        return data[head];
    }

private:
    QueueType
        data[QUEUE_SIZE];
    
    uint32_t
        head,tail,
        count;
};

#endif
