#include <chrono>
#include <iostream>

const size_t SIZE = 10000;

class Timer{
    public:
        Timer()
            : start_(std::chrono::high_resolution_clock::now()){
        }

        void print_time(){
            const auto finish = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
        }
    
    private:
        const std::chrono::high_resolution_clock::time_point start_;
};


int main(){
    //matrix creation
    int** arr = new int*[SIZE];
    for (size_t i = 0; i < SIZE; ++i){
        arr[i] = new int[SIZE];
    }
    for (size_t i = 0; i < SIZE; ++i){
        for (size_t j = 0; j < SIZE; ++j){
            arr[i][j] = i;
        }
    }
    volatile int sum = 0;
    
    //time measurement
    Timer t;
    for (size_t i = 0; i < SIZE; ++i){
        for (size_t j = 0; j < SIZE; ++j){
            sum += arr[j][i];
        }
    }
    //execution timeout
    t.print_time();
    for (size_t i = 0; i < SIZE; ++i)
        delete [] arr[i];
    delete [] arr;
    return 0;
}