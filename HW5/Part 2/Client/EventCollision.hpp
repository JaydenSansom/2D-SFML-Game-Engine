#pragma once

#include "Event.hpp"
#include "Collider.hpp"

class EventCollision : public ::Event {

    public:
        /**
         * @brief Construct a new Event Collision object
         * 
         * @param player player controlled by the client
         * @param obj object that was collided with
         */
        EventCollision(Player* player, GameObject* obj);

};