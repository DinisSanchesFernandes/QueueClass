#pragma once
#ifndef QUEUE_CLASS
#define QUEUE_CLASS

#include <iostream>
#include <mutex>
#include <condition_variable>

template <typename T>
class Queue
{
private:

    // Store the total capacity of the Queue array
    int QueueSize; 

    // Queue array that stores all the queue data
    T * QueueArr;

    // Queue variable to keep track od the pushed data
    int QueueRear, QueueFront, QueueCounter;

    // Mutex to avoid the access to the array by two threads at the same time
    std::mutex mutex;

    // Condition to lock and free the mutex
    std::condition_variable condition;

    // Timeout value to wait for Push/Pop
    int timeout_value = 1000;

    // If Queue is full return True
    bool QueueIsFull();

    // If Queue is empty return true
    bool QueueIsEmpty();

    // Stores an element in the Queue array
    void StoreElement(T element);
    T GetElement();
    
    // Retrieves an element from Queue the array
    void PushQueue(T element);
    T PopQueue();


public:

    // Class constructor
    Queue(int size);

    //Class destructor
    ~Queue();

    // Push element 
    void Push(T element);

    // Push element
    T Pop();

    // Return current amount of elements
    int Count();

    // Return Total size of queue array
    int Size();

};

template <class T>
Queue<T>::Queue(int size)
{
    QueueSize = size;
    QueueArr = new T[QueueSize];
    QueueRear = QueueFront = QueueCounter = 0;

}

template <class T>
Queue<T>::~Queue()
{
    delete[] QueueArr; 
}

template <typename T>
int Queue<T>::Size()
{
    return QueueSize;
}

template <typename T>
int Queue<T>::Count()
{
    return QueueCounter;
}

template <typename T>
bool Queue<T>::QueueIsFull()
{
    return QueueSize == QueueCounter;
}

template <typename T>
bool Queue<T>::QueueIsEmpty()
{
    //std::cout << QueueCounter << std::endl;
    return QueueCounter == 0;
}

template <typename T>
void Queue<T>::StoreElement(T element)
{
    QueueArr[QueueRear] = element;
    QueueRear = (QueueRear + 1) % QueueSize;
    QueueCounter++;

}
template <typename T>
T Queue<T>::GetElement()
{
    int value = QueueArr[QueueFront];
    QueueFront = (QueueFront + 1) % QueueSize;
    QueueCounter--;
    return value;
}


template <typename T>
void Queue<T>::PushQueue(T element)
{

    // Get Mutex lock, this way Pop can not get the mutex therefore cant execute
    // This is done to protect the shared memory which in this case is the Queue Array
    std::unique_lock<std::mutex> lock(mutex);

    while(true)
    {
        if(QueueIsFull())
        {
            std::cout << "Push Blocked " << element << std::endl;
            
            if(timeout_value == 0){
                throw std::runtime_error("Push Timeout");
            }

            // Releases the lock of the mutex
            // This way Pop can get the lock of the mutex and access the shared memory
            if(condition.wait_for(lock, std::chrono::milliseconds(timeout_value)) == std::cv_status::timeout)
            {
                throw std::runtime_error("Push Timeout");
            }
            
        }
        else
        {
            std::cout << "Push " << element << std::endl;
            StoreElement(element);

            // Notify Pop that Queue is not empty anymore
            condition.notify_all();
            break;
        }


    }

}

template <typename T>
T Queue<T>::PopQueue()
{
    // Get Mutex lock, this way Push can not get the mutex therefore cant execute
    // This is done to protect the shared memory which in this case is the Queue Array
    std::unique_lock<std::mutex> lock(mutex);

    while(QueueIsEmpty()){

        std::cout << "Pop Blocked " << std::endl;

        if(timeout_value == 0){
            throw std::runtime_error("Pop Timeout");
        }
        // Releases the lock of the mutex
        // This way Push can get the lock of the mutex and access the shared memory
        if(condition.wait_for(lock, std::chrono::milliseconds(timeout_value)) == std::cv_status::timeout)
        {
            throw std::runtime_error("Pop Timeout");
        }        
    
        

    }

    int value = GetElement();
    std::cout << "Pop " <<value<< std::endl;
    condition.notify_all();
    return value;

}

template <typename T>
void Queue<T>::Push(T element){
     
    try
    {
        PushQueue(element);
          
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }
}

template <typename T>
T Queue<T>::Pop(){
    
    try
    {
        T value = PopQueue();
        //std::cout << "Pop  " << value << std::endl;  
        return value;
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }

    
}


#endif