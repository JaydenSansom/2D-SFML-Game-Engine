#pragma once

#include "EventHandler.hpp"
#include <queue>
#include <mutex>

class EventManager {

	public:
        /**
         * @brief Construct a new Event Manager object
         */
		EventManager();

        /**
         * @brief Adds a pointer to the EventHandler to the events queue
         * 
         * @param e event handler to add
         */
		void registerEvent(EventHandler* e);

        /**
         * @brief Calls the onEvent function of the event handler and removes it from the events queue
         */
		void raise();

	private:
		std::queue<EventHandler*> events;
};