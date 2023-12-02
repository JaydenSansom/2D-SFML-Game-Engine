#pragma once

class SpawnPoint;

#include "EventSpawn.hpp"

class EventDeath : public ::Event {

    public:
        /**
         * @brief Construct a new Event Death object
         * 
         * @param player player that died XP
         */
        EventDeath(Player* player, std::vector<SpawnPoint*>* spawnPoints, sf::RenderWindow* window, sf::View* camera, SideScrollArea* leftSideScrollArea, SideScrollArea* rightSideScrollArea);

};