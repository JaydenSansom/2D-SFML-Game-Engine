#include "EventDeath.hpp"

/**
 * @brief Construct a new Event Death object
 * 
 * @param player player that died XP
 */
EventDeath::EventDeath(Player* player, std::vector<SpawnPoint*>* spawnPoints, sf::RenderWindow* window, sf::View* camera, SideScrollArea* leftSideScrollArea, SideScrollArea* rightSideScrollArea) : Event(EventType::EVENT_DEATH) {
    addVarient(ParamType::CHAR_POINTER, player);
    addVarient(ParamType::SPAWN_POINTS, spawnPoints);
    addVarient(ParamType::WINDOW, window);
    addVarient(ParamType::CAMERA, camera);
    addVarient(ParamType::LEFT_SIDE_SCROLL, leftSideScrollArea);
    addVarient(ParamType::RIGHT_SIDE_SCROLL, rightSideScrollArea);
}