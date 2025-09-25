#include <iostream>
using namespace std;


class priority_queue{
    private:
        int *arr;
        int cap;
        int sz;
        //flag which tells if its min/max heap
        bool isMinHeap;

    // resize the array
    void resize() {
        int newCap;
        if(cap == 0){
            newCap = 1;
        }
        else{
            newCap = cap * 2;
        }

        //copy to new array
        int* newArr = new int[newCap];
        for (int i = 0; i < sz; ++i) {
            newArr[i] = arr[i];
        }

        //delete old array Free the old memory
        delete[] arr; 
        arr = newArr;
        cap = newCap;
    }

    void swap(int &a1, int &a2){
        int tmp = a1;
        a1 = a2;
        a2 = tmp;
    }

    void heapify_Up(int ind){
        if(ind == 0) {
            return;
        } 

        int pInd = (ind - 1) / 2;

        //min heap
        if(isMinHeap){
            if(arr[ind] < arr[pInd]){
                swap(arr[ind], arr[pInd]);
                heapify_Up(pInd);
            }
        }
        //max heap
        else{
            if(arr[ind] > arr[pInd]){
                swap(arr[ind], arr[pInd]);
                heapify_Up(pInd);
            }
        }
    }

    void heapify_Down(int ind){
        
        int leftChldInd = 2 * ind + 1;
        int rightChldInd = 2 * ind + 2;
        int swapind = ind;

        //min heap
        if(isMinHeap){
            if(leftChldInd < sz && arr[leftChldInd] < arr[swapind]){
                swapind = leftChldInd;
            }
            if(rightChldInd < sz && arr[rightChldInd] < arr[swapind]){
                swapind = rightChldInd;
            }   
        }
        //max heap
        else{
            if(leftChldInd < sz && arr[leftChldInd] > arr[swapind]){
                swapind = leftChldInd;
            }
            if(rightChldInd < sz && arr[rightChldInd] > arr[swapind]){
                swapind = rightChldInd;
            }
        }   

        if(swapind != ind){
            swap(arr[ind], arr[swapind]);
            heapify_Down(swapind);
        }
    }

    public:
        //constructor
        priority_queue(bool isMinHp = false){
            cap = 0;
            sz = 0;
            arr = nullptr;
            //default max heap
            this->isMinHeap = isMinHp;
        }
        //destructor
        ~priority_queue() {
            delete[] arr;
        }


        int size(){
            return sz;
        }

        // insert an element el in the priority queue.
        void push(int el){
            if(sz == cap){
                resize();
            }
            arr[sz] = el;
            sz++;
            int ind = sz - 1;
            heapify_Up(ind);
        }

        int top(){
            if(sz == 0){
                cout << "Queue is empty" << endl;
                return -1;
            }
            return arr[0];
        }

        void pop(){
            if(sz == 0){
                cout << "Queue is empty" << endl;
                return ;
            }

            //move last element to root
            arr[0] = arr[sz - 1];
            sz--;
            //heapify down
            if(sz > 0){
                heapify_Down(0);
            }

        }

        bool empty(){
            return sz == 0;
        }   
};

void add(int num, priority_queue &lh , priority_queue &uh){
    lh.push(num);
    uh.push(lh.top());
    lh.pop();

    if(uh.size() > lh.size()){
        lh.push(uh.top());
        uh.pop();
    }
}

double medianFinder(int *arr, int size){
    if(size ==0){
        return 0.0;
    }

    //max heap
    priority_queue lh(false);
    //min heap
    priority_queue uh(true);

    for(int i = 0 ;i < size; i++){
        add(arr[i], lh, uh);
    }

    if (lh.size() > uh.size()) {
        return lh.top();
    } else {
        return (lh.top() + uh.top()) / 2.0;
    }

}


int countDaysForFreeMaggie(int *arr, int d, int n){
    //median sale of trailing number of d days +
    //median sale from the first day
    
    int count = 0;
    for(int i=d; i<n; i++){
        //median of last d days
        double medLastD = medianFinder(arr + (i-d) , d);

        //median from start
        double medAll = medianFinder(arr, i);               

        if(arr[i] >= medLastD + medAll)count++;
        
    }
    return count;
}
    
int main(){

    int n , d;
    cin >> n >> d;
    int* arr = new int[n];
    for(int i=0; i<n ;i++){
        cin >> arr[i] ;
    }

    cout << countDaysForFreeMaggie(arr, d, n);
    delete[] arr;
    return 0;
}