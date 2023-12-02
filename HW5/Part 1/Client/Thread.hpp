#pragma once
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <functional>

/**
 * @brief The thread class, allowing for two threads to run functions simultaniously
 */
class Thread {

    private:
        bool busy; // a member variable used to indicate thread "status"
        int i; // an identifier
        Thread *other; // a reference to the "other" thread
        std::mutex *_mutex; // the object for mutual exclusion of execution
        std::condition_variable *_condition_variable; // for messaging between threads
        std::function<void()> threadFunction; // function to run

    public:
        /**
         * @brief Construct a new Thread object
         * 
         * @param i thread identifier
         * @param other other thread
         * @param _mutex the mutex object
         * @param _condition_variable for messaging between threads
         * @param function function to run on the thread
         */
        Thread(int i, Thread *other, std::mutex *_mutex, std::condition_variable *_condition_variable, std::function<void()> function);

        /**
         * @brief Is the thread busy?
         * 
         * @return boolean of if the thread is busy
         */
        bool isBusy();

        /**
         * @brief Run the thread
         */
        void run();
};

/**
 * Wrapper function because threads can't take pointers to member functions.
 */
void run_wrapper(Thread *fe);