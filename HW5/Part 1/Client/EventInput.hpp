#pragma once

#include "Event.hpp"

class EventInput : public ::Event {

    public:
        /**
         * @brief Construct a new Event Input object
         * 
         * @param player player affected by the input
         * @param KeyInput key input recieved
         */
        EventInput(Player * player, KeysPressed* KeyInput, float elapsedTime, bool isSprinting);

};