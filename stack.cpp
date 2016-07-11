#include "stack.hpp"

// pasar a template, stack solo acepta char de momento

Stack::Stack(int size) {
   MaxStack = size;
   EmptyStack = -1;
   top = EmptyStack;
   items = new char[MaxStack];
}

Stack::~Stack() {delete[] items;}

void Stack::push(char c) {
   items[++top] = c;
}

char Stack::pop() {
   return items[top--];
}

int Stack::full()  {
   return top + 1 == MaxStack;
}

int Stack::empty()  {
   return top == EmptyStack;
}
