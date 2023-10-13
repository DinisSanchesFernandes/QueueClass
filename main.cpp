#include <iostream>
#include <thread>
#include <csignal>
#include "Queue.h"

int main(){

    Queue<int> queue(2);
    int PushSignal = false;

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
        //std::this_thread::sleep_for(std::chrono::seconds(100));
        queue.Pop();
        queue.Pop();
        queue.Pop();
        queue.Pop();
        
    });

    pushthread.join();
    popthread.join();


    return 0;


}