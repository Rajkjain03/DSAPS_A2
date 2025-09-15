#include <iostream>
using namespace std;

// Forward declaration
template<typename T>
class deque;

// Helper function to print deque contents
template<typename T>
void printDeque(const deque<T>& d, const string& name);

// template in C++ allows you to write generic and reusable code. They enable you to creat functions and classes that can operate with any data type without being tied to a specific one.
template<typename T>

//Implementing Double Ended Queue (Deque) using a dynamic array
class deque {
private:
    // Index of the first element.
    int head;     
    // index of the position after the last element.
    int tail;     
    // curent number of elements.
    int count;    
    // current capaCity of the array.
    int capaCity;   
    // Pointer to the dynamically allocated array.
    T* arr;         
    
    // Doubles the capaCity of the array when it's full.
    void resize() {
        int newCapacity = (capaCity == 0) ? 8 : capaCity * 2;
        T* nArr = new T[newCapacity];

        // Copy elements 
        for (int i = 0; i < count; ++i) {
            nArr[i] = arr[(head + i) % capaCity];
        }

        delete[] arr; 

        // Update state 
        arr = nArr;
        capaCity = newCapacity;
        head = 0;
        tail = count; 
    }

public:
    // default constructor
    // initializes an empty deque.
    deque() {  
        arr = nullptr;
        head = 0;
        tail = 0;
        count = 0;
        capaCity = 0;
    
    }

    // parameterized constructor Initializes a deque of length n with default values.
    deque(int n){
        arr = nullptr;
        head = 0;
        tail = n;
        count = n;
        capaCity = n;
        // initialize array with default values
        arr = new T[capaCity];
        for (int i = 0; i < n; ++i) {
            arr[i] = T();
        }
    }

    // parameterized constructor Initializes a deque of length n with a specific value x.
    deque(int n, const T& x)  {
        arr = nullptr;
        head = 0;
        tail = n;
        count = n;
        capaCity = n;
        // initialize array with value x
        arr = new T[capaCity];
        for (int i = 0; i < n; ++i) {
            arr[i] = x;
        }
    }

    //  Destructor 
    ~deque() {
        // Free dynamically allocated array
        delete[] arr;
    }

    // append data x at the end of deque
    void push_back(const T& value) {
        // check if deque is full
        if (count == capaCity) {
            // If array is full resize it .
            resize();
        }
        // insert value at tail position
        arr[tail] = value;
        // Move tail forward if necessary
        tail = (tail + 1) % capaCity;
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
            tail = capaCity - 1;
        else    
            tail = tail - 1;
        // Decrease the count of elements
        count--;
    }

    // append data x at the beginning of deque
    void push_front(const T& value) {
        if (count == capaCity) {
            resize();
        }
        if(head == 0){
            head = capaCity - 1;
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
        head = (head + 1) % capaCity;
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
        if(tail == 0)
            return arr[capaCity - 1];
        else
            return arr[tail - 1];
    }

    // returns the nth element of the deque. Overloads the [] operator for indexed access.
    T operator[](int n)  {
        if (empty() || (n >=0 && n >= count)) {
            //out of bound
            return T();
        }
        int idx;
        if(n >= 0){
            idx = (head + n) % capaCity;
        }else{
            //for negative index
            idx = (head + count + n) % capaCity;
        }
        return arr[idx];
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
        //if n lss than current size
        if (n < count) {
            count = n;
            tail = (head + count) % capaCity;
        } 
        
        else if (n > count) {
            tail = (head + n) % capaCity;
            count = n;
            // If new size exceeds current capaCity, resize the array.
            while (count > capaCity) {
                resize();
            }
        }
    }

    //change the size dynamically to new size n and initialize new elements with value x.
    void resize(int n, const T& x) {
        if (n < count) {
            count = n;
            tail = (head + count) % capaCity;
        } 
        
        else if (n > count) {
            tail = (head + n) % capaCity;
            count = n;
            int elm = n - count;
            for (int i = 0; i < elm; ++i) {
                push_back(x);
            }
        }
    }

    // change the capaCity of deque to n, if n > current capaCity otherwise do nothing.
    void reserve(int n){    
        if(n <= capaCity){
            return;
        }
        //create a new array of size n
        T* nArr = new T[n];
        // Copy elements from the old arry
        for (int i = 0; i < count; ++i) {
            nArr[i] = arr[(head + i) % capaCity];             
        }

        delete[] arr; 
        //update the state
        arr = nArr;
        capaCity = n;
        head = 0;
        tail = count; 
    
    }

    //reduce the capaCity of the deque to current size.
    void shrink_to_fit(){
        if(count == capaCity){
            //already at fit size
            return;
        }
        
        int newCapacity = count;
        // if no elemnts, free memory 
        if(newCapacity == 0){
            delete[] arr;
            arr = nullptr;
            capaCity = 0;
            head = 0;
            tail = 0;
            return;
        }

        T* nArr = new T[newCapacity];
        //copy from old array to new array
        for (int i = 0; i < count; ++i) {
            nArr[i] = arr[(head + i) % capaCity];
        }

        //free old memory
        delete[] arr;
        //update the state
        arr = nArr;
        capaCity = newCapacity;
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
        capaCity = 0;        
        resize();
    }

    //return the current capacity of deque.
    int capacity() const {
        return capaCity;
    }
};


template<typename T>
void printDeque(const deque<T>& d, const string& name) {
    cout << "--- " << name << " (size: " << d.size() << ", cap: " << d.capacity() << ") ---\n";
    if (d.empty()) {
        cout << "[EMPTY]\n";
    } else {
        cout << "Front -> ";
        for(int i = 0; i < d.size(); ++i) {
             cout << d[i] << " ";
        }
        cout << "<- Back\n";
    }
    cout << "-------------------------\n";
}

int main(){ 
    deque<int> d;
    d.push_back(1);
    d.push_back(2);

    printDeque(d, "Initial");

    return 0;
}