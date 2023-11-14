#pragma once

class SideScrollArea;

#include "Event.hpp"

class EventSpawn : public ::Event {

    public:
        /**
         * @brief Construct a new Event Spawn object
         * 
         * @param player player to set position to spawn point
         * @param xPos x position to spawn the player to
         * @param yPos y position to spawn the player to
         */
        EventSpawn(Player* player, double xPos, double yPos, sf::RenderWindow* window, sf::View* camera, SideScrollArea* leftSideScrollArea, SideScrollArea* rightSideScrollArea);

};