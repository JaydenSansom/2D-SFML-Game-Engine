#include "EventSpawn.hpp"

/**
 * @brief Construct a new Event Spawn object
 * 
 * @param player player to set position to spawn point
 * @param xPos x position to spawn the player to
 * @param yPos y position to spawn the player to
 */
EventSpawn::EventSpawn(Player* player, double xPos, double yPos, sf::RenderWindow* window, sf::View* camera, SideScrollArea* leftSideScrollArea, SideScrollArea* rightSideScrollArea) : Event(EventType::EVENT_SPAWN) {
    addVarient(ParamType::CHAR_POINTER, player);
    addVarient(ParamType::X_POS, xPos);
    addVarient(ParamType::Y_POS, yPos);
    addVarient(ParamType::WINDOW, window);
    addVarient(ParamType::CAMERA, camera);
    addVarient(ParamType::LEFT_SIDE_SCROLL, leftSideScrollArea);
    addVarient(ParamType::RIGHT_SIDE_SCROLL, rightSideScrollArea);
}