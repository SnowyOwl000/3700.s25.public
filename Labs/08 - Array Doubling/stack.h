#ifndef _STACK_H
#define _STACK_H

#include <stdexcept>

using namespace std;

const uint32_t
    STACK_SIZE = 16;
  
template <typename StackType>
class Stack {
public:
    Stack() { top = 0; }

    ~Stack() = default;

    void clear() { top = 0; }

    uint32_t size() { return top; }

    bool isEmpty() { return top == 0; }
  

    void push(StackType d) {
  
        if (top == STACK_SIZE)
            throw overflow_error("Stack is full");
      
        data[top++] = d;
    }
  
    StackType pop() {

        if (top == 0)
            throw underflow_error("Stack is empty");
      
        return data[--top];
    }
    
    StackType peek() {
  
        if (top == 0)
            throw underflow_error("Stack is empty");
      
        return data[top-1];
    }
  
private:
    StackType
        data[STACK_SIZE];
    
    uint32_t
        top;
};

#endif

