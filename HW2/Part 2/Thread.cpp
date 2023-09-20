#include "Thread.hpp"

/**
 * @brief Construct a new Thread object
 * 
 * @param i thread identifier
 * @param other other thread
 * @param _mutex the mutex object
 * @param _condition_variable for messaging between threads
 */
Thread::Thread(int i, Thread *other, std::mutex *_mutex, std::condition_variable *_condition_variable, std::function<void()> function) {
    this->i = i; // set the id of this thread
    if(i == 0) { 
        busy = true; 
        this->other = nullptr;
    }
    else { 
        busy = false; 
        this->other = other; 
    }
    this->_mutex = _mutex;
    this->_condition_variable = _condition_variable;
    this->threadFunction = function;
}

/**
 * @brief Is the thread busy?
 * 
 * @return boolean of if the thread is busy
 */
bool Thread::isBusy() {
    std::lock_guard<std::mutex> lock(*_mutex);  // this locks the mutuex until the variable goes out of scope (i.e., when the function returns in this case)
    return busy;
}

/**
 * @brief Run the thread
 */
void Thread::run() {
    if(i == 0) {
        try {
            threadFunction();

            { // anonymous inner block to manage scope of mutex lock 
                std::unique_lock<std::mutex> cv_lock(*this->_mutex);
                _condition_variable->notify_all();
            }
            { // anonymous inner block to manage scope of mutex lock 
                std::unique_lock<std::mutex> cv_lock(*this->_mutex);
                _condition_variable->notify_all();
            }
            { // anonymous inner block to manage scope of mutex lock 
                std::unique_lock<std::mutex> cv_lock(*this->_mutex);
                busy = !busy;
                _condition_variable->notify_all();
            }
        }
        catch (...) {
            std::cerr << "Thread " << i << " caught exception." << std::endl;
        }
    }
    else { // id == 1
        while(other->isBusy()) {
            try {
                std::unique_lock<std::mutex> lock(*_mutex);
                _condition_variable->wait(lock);
            }
            catch (...) {
                std::cerr << "Thread " << i << " caught exception." << std::endl;
            }
        }
        threadFunction();
    }
}

/**
 * Wrapper function because threads can't take pointers to member functions.
 */
void run_wrapper(Thread *fe)
{
    fe->run();
}
