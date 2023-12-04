#include "EventCollision.hpp"

/**
 * @brief Construct a new Event Collision object
 * 
 * @param player player controlled by the client
 * @param obj object that was collided with
 */
EventCollision::EventCollision(Player* player, GameObject* obj) : Event(EventType::EVENT_COLLISION) {
    addVarient(ParamType::CHAR_POINTER, player);
    addVarient(ParamType::OBJ_POINTER, obj);
}