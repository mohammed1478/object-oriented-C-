#include <iostream>
using namespace std;

class stack {
private:
   int top;      // The index 1 past the last element (also the number of elements)
   int *p;       // Pointer to int array
   int capacity; // The amount of space currently allocated for the array in terms of number of elements
                 // (may be larger than the number of elements)
                 // I named it capacity because it has the same meaning as capacity in the vector class

public:
   // No-argument constructor: Creates an empty stack of capacity 100
   stack() {
      top = 0;
      capacity = 100;
      p = new int[capacity];
   }

   // 1-argument constructor: Creates an empty stack of capacity n
   stack(int n) {
      top = 0;
      capacity = n;
      p = new int[capacity];
   }

   // Destructor: Deletes the stack
   ~stack() {
      delete[] p; // Delete the dynamically-allocated array (top and capacity don't have to be deleted)
   }

   // Returns true if the number of elements is the same as the capacity
   bool full() {
      return top == capacity;
   }

   // Returns true if the number of elements is 0
   bool empty() {
      return top == 0;
   }

   // Removes and returns the last element (we "remove" the last element by decreasing top by 1)
   // Note that this is different from vector's pop_back function, which does not return anything
   int pop() {
      if (empty()) { // If the stack is already empty, print "error" and exit
         cout << "Error: stack empty";
         exit(1);
      }
      --top; // top is 1 past the last element, so decrease top before accessing p[top]
      return p[top];
   }

   // Adds n as a new last element, increasing the capacity if necessary
   void push(int n) {
      if (full()) {                         // If the stack is already full, increase the capacity by a factor of 2
         int* q = new int[capacity*2];      // Create a new array twice the capacity
         for (int i = 0; i < capacity; ++i) // Copy the elements from the old array to the new array
            q[i] = p[i];
         delete[] p;    // Delete the old array
         p = q;         // Update p to point to the new array
         capacity *= 2; // Update the capacity
      }
      p[top] = n;       // top is 1 past the last element, so place the element in p[top] before increasing top
      ++top;
   }

   // Assignment: Assigns one stack to another stack, e.g. y = x (x and y are already-existing stacks)
   stack& operator=(const stack& r) {
      if (this == &r) return *this; // If this and &r both point to the same object, e.g. x = x, return the object
      delete[] p;                   // Delete this's old array
      top = r.top;                  // Copy the data members top and capacity
      capacity = r.capacity;
      p = new int[capacity];        // Create a new array with the same capacity as r's array
      for (int i = 0; i < capacity; ++i) // Copy the elements from r's array to this's array
         p[i] = r.p[i];
      return *this; // Return the object
   }

   // Copy constructor: Used in initialization, e.g. stack y = x (x is a stack)
   // The copy constructor is also called when passing a stack by value or returning a stack
   // This is the same as operator= but without the first 2 lines and the last line
   stack(const stack& r) {
      top = r.top;
      capacity = r.capacity;
      p = new int[capacity];
      for (int i = 0; i < capacity; ++i)
         p[i] = r.p[i];
   }
};

int main() {
   stack x(3);
   x.push(3);
   x.push(5);
   x.push(7);
   stack y = x;
   cout << "Popping from stack x:\n";
   while (!x.empty())
      cout << x.pop() << endl;
   cout << "Popping from stack y:\n";
   while (!y.empty())
      cout << y.pop() << endl;
   cout << x.pop();
   return 0;
}
