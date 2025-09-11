#include <iostream>

// template in C++ allows you to write generic and reusable code. They enable you to creat functions and classes that can operate with any data type without being tied to a specific one.
template<typename T>

//Implementing Double Ended Queue (Deque) using a dynamic array
class DequeImplementation {
private:
    // Index of the first element.
    int head;     
    // Index of the position AFTER the last element.
    int tail;     
    // curent number of elements.
    int count;    
    // current capacity of the array.
    int capacity; 
     // Pointer to the dynamically allocated array.
    T* arr;         
    
    // Doubles the capacity of the array when it's full.
    void resize() {
        int newCapacity = (capacity == 0) ? 8 : capacity * 2;
        T* newArr = new T[newCapacity];

        // Copy elements from the old, wrapped array to the new, linear one.
        for (int i = 0; i < count; ++i) {
            newArr[i] = arr[(head + i) % capacity];
        }

        delete[] arr; // Free the old memory

        // Update state to reflect the new array
        arr = newArr;
        capacity = newCapacity;
        head = 0;
        tail = count; // tail is now simply at the end of the elements
    }

public:
    // default constructor
    // initializes an empty DequeImplementation.
    DequeImplementation() {  
        arr = nullptr;
        head = 0;
        tail = 0;
        count = 0;
        capacity = 0;
        // Start with a small capacity to avoid immediate resizing on first push_back or push_front         
        resize(); 
    }

    // parameterized constructor Initializes a deque of length n with default values.
    DequeImplementation(int n){
        arr = nullptr;
        head = 0;
        tail = n;
        count = n;
        capacity = n;
        // initialize array with default values
        arr = new T[capacity];
        for (int i = 0; i < n; ++i) {
            arr[i] = T();
        }
    }

    // parameterized constructor Initializes a deque of length n with a specific value x.
    DequeImplementation(int n, const T& x)  {
        arr = nullptr;
        head = 0;
        tail = n;
        count = n;
        capacity = n;
        // initialize array with value x
        arr = new T[capacity];
        for (int i = 0; i < n; ++i) {
            arr[i] = x;
        }
    }

    //  Destructor 
    ~DequeImplementation() {
        // Free the dynamically allocated array
        delete[] arr;
    }

    // append data x at the end of deque
    void push_back(const T& value) {
        if (count == capacity) {
            // If array is full resize it .
            resize();
        }
        // insert value at tail position
        arr[tail] = value;
        // Move tail forward, wrapping around if necessary
        tail = (tail + 1) % capacity;
        // increase the count of elements
        count++;
    }

    // erase data at the end of the deque
    void pop_back() {
        // If deque is empty, cannot pop
        if (empty()) {
            cout <<"Cannot pop from back" << endl;
            return;
        }
        // Move tail backward, wrapping around if necessary
        if(tail == 0)
            tail = capacity - 1;
        else
            tail = tail - 1;
        // Decrease the count of elements
        count--;
    }

    // append data x at the beginning of deque
    void push_front(const T& value) {
        // If array is full, resize it
        if (count == capacity) {
            resize();
        }
        // Move head backward, wrapping around if necessary
        if(head == 0){
            head = capacity - 1;
        }else{
            head = head - 1;
        }
        //insert the value at the new head position
        arr[head] = value;
        count++;
    }

    // erase data at the beginning of the deque
    void pop_front() {
        // if empty, cannot pop
        if (empty()) {
            cout <<"Cannot pop from front" << endl;
            return;
        }
        // Move head forward, wrapping around if necessary
        head = (head + 1) % capacity;
        // Decrease the count of elements
        count--;
    }

    // Returns the first element's data.
    T front() {
        if (empty()) {
            // default value if empty
            return T(); 
        }
        return arr[head];
    }

    // Returns the last element's data.
    T back() {
        if (empty()) {
            // default value if empty
            return T();  
        }
        // The last element is at the index before tail, handling wrap-around
        if(tail == 0)
            return arr[capacity - 1];
        else
            return arr[tail - 1];
    }

    // Overloads the [] operator for indexed access.
    T operator[](int index) const {
        if (index >= count) {
            // Index is out of bounds, return default value.
            return T();
        }
        // Calculate the actual array index from the logical DequeImplementation index
        return arr[(head + index) % capacity];
    }

    // checks if the deque is empty.
    // returns true if deque is empty else returns false.
    bool empty() const {
        return count == 0;
    }


    //returns the current size of deque.
    int size() const {
        return count;
    }

    //change the size dynamically to new size n.
    void resize(int n) {
        //If the new size n is smaller than the current size, then keep n elements from the beginning of the deque.
        if (n < count) {
            count = n;
            tail = (head + count) % capacity;
        } 
        
        //If the new size n is greater than the current size of the deque, then insert new elements with the default value of T at the end of the queue.
        else if (n > count) {
            int elem = n - count;
            for (int i = 0; i < elem; ++i) {
                push_back(T());
            }
        }
    }

    //change the size dynamically to new size n and initialize new elements with value x.
    void resize(int n, const T& x) {
        //If the new size n is smaller than the current size, then keep n elements from the beginning of the deque.
        if (n < count) {
            count = n;
            tail = (head + count) % capacity;
        } 
        
        //If the new size n is greater than the current size of the deque, then insert new elements with the value x at the end of the queue.
        else if (n > count) {
            int elem = n - count;
            for (int i = 0; i < elem; ++i) {
                push_back(x);
            }
        }
    }

    // change the capacity of deque to n, if n > current capacity otherwise do nothing.
    void reverse(int n){
        //do nothing new capacity is not larger.    
        if(n <= capacity){
            return
        }
        //create a new array of size n
        T* newArr = new T[n];
        // Copy elements from the old, wrapped array to the new, linear one.
        for (int i = 0; i < count; ++i) {
            newArr[i] = arr[(head + i) % capacity];             
        }

        delete[] arr; 

        // Update state to reflect the new array
        arr = newArr;
        capacity = n;
        head = 0;
        tail = count; // tail is now simply at the end of the elements
    
    }

    //reduce the capacity of the deque to current size.
    void shrink_to_fit(){
        if(count == capacity){
            //already at fit size
            return;
        }
        
        int newCapacity = count;
        // if no elemnts, free memory 
        if(newCapacity == 0){
            delete[] arr;
            arr = nullptr;
            capacity = 0;
            head = 0;
            tail = 0;
            return;
        }

        T* newArr = new T[newCapacity];
        //copy from old array to new array
        for (int i = 0; i < count; ++i) {
            newArr[i] = arr[(head + i) % capacity];
        }

        //free old memory
        delete[] arr;
        //update the state
        arr = newArr;
        capacity = newCapacity;
        head = 0;
        tail = count; 
    }

    // remove all elements from the deque 
    void clear(){
        // Free the dynamically allocated array
        delete[] arr;
        arr = nullptr;
        head = 0;
        tail = 0;
        count = 0;
        capacity = 0;        
        resize();
    }

    //return the current capacity of deque.
    int capacity() const {
        return capacity;
    }

};


int main() {
    

    return 0;
}
