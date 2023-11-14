#include "EventManager.hpp"

std::mutex eventsMutex;

/**
 * @brief Construct a new Event Manager object
 */
EventManager::EventManager() {}

/**
 * @brief Adds a pointer to the EventHandler to the events queue
 * 
 * @param e event handler to add
 */
void EventManager::registerEvent(EventHandler* e) {
    events.push(e);
}

/**
 * @brief Calls the onEvent function of the event handler and removes it from the events queue
 */
void EventManager::raise() {
    std::lock_guard<std::mutex> lock(eventsMutex);  // Lock the mutex
    while(!events.empty()) {
        EventHandler* calledEvent = events.front();
        calledEvent->onEvent();
        delete calledEvent;
        events.pop();
    }
}