#include <iostream>
#include <thread>
#include "Queue.h"

int main(){

    Queue<int> queue(2);

    std::thread pushthread([&queue](){

        queue.Push(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        queue.Push(2);
        queue.Push(3);
        queue.Push(4);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        queue.Push(5);


    });

    std::thread popthread([&queue](){


        queue.Pop();
        queue.Pop();
        queue.Pop();
        queue.Pop();
        queue.Pop();
        
    });

    pushthread.join();
    popthread.join();


    return 0;


}
