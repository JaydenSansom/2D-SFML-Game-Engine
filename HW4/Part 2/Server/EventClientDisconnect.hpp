#pragma once

#include "Event.hpp"

class EventClientDisconnect : public ::Event {

    public:
        /**
         * @brief Construct a new Event Client Disconnect object
         * 
         * @param clientName name of the client
         */
        EventClientDisconnect(std::string clientName, std::vector<PlayerClient>* clients);

};