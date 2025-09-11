#include <iostream>
using namespace std;

// Implementing Double Ended Queue (Deque) using a doubly linked list and to make it generic by using Templates    
// template in C++ allows you to write generic and reusable code. They enable you to creat functions and classes that can operate with any data type without being tied to a specific one.
template <typename T>
struct Node{
    //data 
    T data;
    //pointer to next node
    Node* next;
    //pointer to previous node
    Node* prev;
    //constructor to initialize data and pointers
    Node(T val){
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class DequeImplementation{
    private:
        //member varialbles
        //pointer to front node
        Node<T>* front;
        //pointer to rear node
        Node<T>* rear;
        //number of elements in deque
        int count;

    public: 
        //zero parameter constructor
        DequeImplementation(){
            front = nullptr;
            rear = nullptr;
            count = 0;
        }

        //parameterized constructor 
        // Initializes a deque of length n with default values.
        DequeImplementation(int n){
            front = nullptr;
            rear = nullptr;
            count = 0;
            for(int i=0; i<n; i++){
                //  T() gives the default value (0 for int, "" for string, etc.)
                push_back(T()); 
            }
        }

        //parameterized constructor
        // initialize deque of length n with all values as x
        DequeImplementation(int n , int x){
            front = nullptr;
            rear = nullptr;
            count = 0;
            for(int i=0; i<n; i++){
                push_back(x);
            }
        }

        //destructor to free memory
        ~DequeImplementation(){
            // pop all elements from front until deque is empty
            while(!isEmpty()){
                pop_front();
            }
        }   

        //append data x at the end of the deque
        void push_back(T x){
            //create a new node with data x
            Node<T>* newNode = new Node<T>(x);
            //if deqe is empty initialize front and rear to new node
            if(isEmpty()){
                front = newNode;
                rear = newNode;
            }
            //else add new node at the end of the existing deque
            else{
                //link the current rear node with the new node
                rear->next = newNode;
                //link the new node with the current rear node
                newNode->prev = rear;
                //change rear to point to the new node
                rear = newNode;
            }
            //increase count of elements
            count++;
        }

        //erase an element from the end.
        void pop_back(){
            //if deque is empty i.e underflow condition
            if(isEmpty()){
                cout<<"Cannot pop from back. Underflow"<<endl;
                return;
            }
            //store the current rear node in a temporary variable
            Node<T>* temp = rear;
            //move rear to the previous node
            rear = rear->prev;
            //if rear is not null, set its next pointer to null
            if(rear != nullptr){
                rear->next = nullptr;
            }
            //if rear becomes null, set front to null as well (deque is now empty)
            else{
                front = nullptr;
            }
            //delete the temporary node to free memory
            delete temp;
            //decrease count of elements
            count--;
        }

        //appned data x at the front of the deque
        void push_front(T x){
            //create a new node with data x
            Node<T>* newNode = new Node<T>(x);
            //if deque is empty initialize front and rear to new node
            if(isEmpty()){
                front = newNode;
                rear = newNode;
            }
            //else add new node at the front of the existing deque
            else{
                //link the current front node with the new node
                front->prev = newNode;
                //link the new node with the current front node
                newNode->next = front;
                //change front to point to the new node
                front = newNode;
            }
            //increase count of elements
            count++;
        }

        //erase an element from the beginning.
        void pop_front(){
            //if deque is empty i.e underflow condition
            if(isEmpty()){
                cout<<"Cannot pop from front. Underflow"<<endl;
                return;
            }
            //store the current front node in a temporary variable
            Node<T>* temp = front;
            //move front to the next node
            front = front->next;
            //if front is not null, set its previous pointer to null
            if(front != nullptr){
                front->prev = nullptr;
            }
            //if front becomes null, set rear to null as well (deque is now empty)
            else{
                rear = nullptr;
            }
            //delete the temporary node to free memory
            delete temp;
            //decrease count of elements
            count--;
        }

        //returns the first element(value) in the deque
        T front(){
            if(empty()){
                cout<<"Deque is empty. No element at the font"<<endl;
                //return default value of T
                return T(); 
            }
            // return data of front node
            return front->data;
        }

        //returns the last element(value) in the deque
        T back(){
            if(empty()){
                cout<<"Deque is empty. No element at the back"<<endl;
                //return default value of T
                return T(); 
            }
            // return data of rear node/back node 
            return rear->data;
        }

        T D[n]

};



int main(){
    return 0;
}
