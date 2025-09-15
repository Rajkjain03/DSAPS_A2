#include <iostream>
#include <cstdlib>   // For rand() 
#include <ctime>     // For time()
#include <limits>    // For numeric_limits
using namespace std;


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
        int newCap;
        if(capaCity == 0){
            newCap = 1;
        }else{
            newCap = capaCity*2;
        }
        T* nArr = new T[newCap];
        // Copy elements 
        for (int i = 0; i < count; ++i) {
            nArr[i] = arr[(head + i) % capaCity];
        }

        delete[] arr; 

        // Update state 
        arr = nArr;
        capaCity = newCap;
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
        tail = 0;
        count = n;
        capaCity = n;
        // initialize array with default values
        arr = new T[capaCity];
        if(n > 0)tail = n;
        for (int i = 0; i < n; ++i) {
            arr[i] = T();
        }
    }

    // parameterized constructor Initializes a deque of length n with a specific value x.
    deque(int n, const T& x)  {
        arr = nullptr;
        head = 0;
        tail = 0;
        count = n;
        capaCity = n;
        // initialize array with value x
        arr = new T[capaCity];
        if(n > 0)tail = n;
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
        if (count == capaCity || arr == nullptr) {
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
        if (count == capaCity || arr == nullptr ) {
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
    T operator[](int n) const {
        if (empty() || (n >=0 && n >= count) || (n < 0 && (-n) > count)) {
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
    
    T& operator[](int n){
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
            tail = (head + n) % capaCity;
            count = n;
            } 
        
        else if (n > count) {
            int elm = n - count;
            // If new size exceeds current capaCity, resize the array.
            for (int i = 0; i < elm; ++i) {
                push_back(T());
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
        
        int newCap = count;
        // if no elemnts, free memory 
        if(newCap == 0){
            delete[] arr;
            arr = nullptr;
            capaCity = 0;
            head = 0;
            tail = 0;
            return;
        }

        T* nArr = new T[newCap];
        //copy from old array to new array
        for (int i = 0; i < count; ++i) {
            nArr[i] = arr[(head + i) % capaCity];
        }

        //free old memory
        delete[] arr;
        //update the state
        arr = nArr;
        capaCity = newCap;
        head = 0;
        tail = count; 
    }

    // remove all elements from the deque 
    void clear(){
        head = 0;
        tail = 0;
        count = 0;    
    }

    //return the current capacity of deque.
    int capacity() const {
        return capaCity;
    }
};

//Randomized queue -
template<typename T>
class randomizedQueue { 
    private:
        deque<T> dq;
    public:
     
        void enqueue(const T &x){
            dq.push_back(x);
        }

        T dequeue(){
            if(dq.empty()){
                cout << "Queue is empty" << endl;
                throw out_of_range("Error deque");
            }
            int ind = rand() % dq.size();
            T randomReturn = dq[ind];
            T lstItem = dq[dq.size() -1 ];
            //remove the item
            dq[ind] = dq[lstItem];
            dq.pop_back();
            return randomReturn;
        } 

        T sample(){
            if(dq.empty()){
                cout << "Queue is empty" << endl;
                throw out_of_range("Error sample");
            }
            int ind = rand() % dq.size();
            return dq[ind];
        }
};


template<typename T>
void randomizerFun() {
    RandomizedQueue<T> rq;
    int n;
    T val;

    while (true) {
        cout << "Enter which operation you want to perform"<< endl;
        cout << "1. enqueue(x): To add the item " << endl;
        cout << "2. dequeue(): To remove and return a random item " << endl;
        cout << "3. sample(): To return a random sample " << endl;
        cout << "0. exit" <<endl;
        cin >> n;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (n == 0) {
            cout << "Returning to data type selection...\n";
            return; 
        }

        switch (n) {
            case 0: 
                cout << "GG ! BYE." << endl;
                return 0;
            case 1:
                cout << "Enter a value to enqueue: ";
                cin >> val;

                if (cin.fail()) {
                    cout << "Invalid input for this data type.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                rq.enqueue(val);
                cout << "Enqueued successfully.\n";
                break;
            case 2:
                try {
                    val = rq.dequeue();
                    cout << "Dequeued random item: " << val << "\n";
                } catch (const std::out_of_range& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            case 3: 
                try {
                    val = rq.sample();
                    cout << "Sampled random item: " << val << "\n";
                } catch (const std::out_of_range& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            default:
                cout << "Invalid n. Please try again.\n";
                break;
        }
    }
}


int main(){ 
    srand(time(0));
    int n ;
    while(true){    
        
        cout << "Select the data type for the Randomized Queue:\n";
        cout << "1. Integer (int)\n";
        cout << "2. Double (double)\n";
        cout << "3. Character (char)\n";
        cout << "0. Exit Program\n";
        cin >> n;   

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (n) {
            case 0:
                cout << "GG ! BYE." << endl;
                return 0;
            case 1:
                randomizerFun<int>();
                break;
            case 2:
                randomizerFun<double>();
                break;
            case 3:
                randomizerFun<char>();
                break;
            
            default:
                cout << "Invalid data type n. Please try again.\n";
                break;
        }
    }
    

    return 0;
}