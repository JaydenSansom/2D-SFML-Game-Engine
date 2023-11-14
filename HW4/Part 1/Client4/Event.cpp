#include "Event.hpp"

/**
 * @brief Construct a new Varient object with a GameObject pointer value
 * 
 * @param value game object pointer to set as the value of the varient
 */
Varient::Varient(GameObject* value) {
    this->type = VarientType::OBJ_POINTER;
    this->gameObjValue = value;
}

/**
 * @brief Construct a new Varient object with a double value
 * 
 * @param value double to set as the value of the varient
 */
Varient::Varient(double value) {
    this->type = VarientType::DOUBLE;
    this->doubleValue = value;
}

/**
 * @brief Construct a new Varient object with a boolean value
 * 
 * @param value boolean to set as the value of the varient
 */
Varient::Varient(bool value) {
    this->type = VarientType::BOOL;
    this->boolValue = value;
}

/**
 * @brief Construct a new Varient object with a char value
 * 
 * @param value char to set as the value of the varient
 */
Varient::Varient(char value) {
    this->type = VarientType::CHAR;
    this->charValue = value;
}

/**
 * @brief Construct a new Varient object with a float value
 * 
 * @param value float to set as the value of the varient
 */
Varient::Varient(float value) {
    this->type = VarientType::FLOAT;
    this->floatValue = value;
}

/**
 * @brief Construct a new Varient object with a keyspressed value
 * 
 * @param value keyspressed to set as the value of the varient
 */
Varient::Varient(KeysPressed* value) {
    this->type = VarientType::KEYS_PRESSED;
    this->keysPressedValue = value;
}

/**
 * @brief Construct a new Varient object with a player value
 * 
 * @param value player to set as the value of the varient
 */
Varient::Varient(Player* value) {
    this->type = VarientType::PLAYER;
    this->playerValue = value;
}

/**
 * @brief Construct a new Varient object with a camera value
 * 
 * @param value camera to set as the value of the varient
 */
Varient::Varient(sf::View* value) {
    this->type = VarientType::CAMERA;
    this->cameraValue = value;
}

/**
 * @brief Construct a new Varient object with a window value
 * 
 * @param value window to set as the value of the varient
 */
Varient::Varient(sf::RenderWindow* value) {
    this->type = VarientType::WINDOW;
    this->windowValue = value;
}

/**
 * @brief Construct a new Varient object with a side scroll area value
 * 
 * @param value side scroll area to set as the value of the varient
 */
Varient::Varient(SideScrollArea* value) {
    this->type = VarientType::SIDE_SCROLL_AREA;
    this->sideScrollValue = value;
}

/**
 * @brief Construct a new Varient object with a side scroll area value
 * 
 * @param value side scroll area to set as the value of the varient
 */
Varient::Varient(std::vector<SpawnPoint*>* value) {
    this->type = VarientType::SPAWN_POINTS;
    this->spawnPointsValue = value;
}

/**
 * @brief Get the Value object of the varient
 * 
 * @return void* pointer to the value of the varient
 */
void* Varient::getValue() {
    if(this->type == VarientType::OBJ_POINTER) {
        return this->gameObjValue;
    }
    else if(this->type == VarientType::DOUBLE) {
        return &this->doubleValue;
    }
    else if(this->type == VarientType::BOOL) {
        return &this->boolValue;
    }
    else if(this->type == VarientType::CHAR) {
        return &this->charValue;
    }
    else if(this->type == VarientType::FLOAT) {
        return &this->floatValue;
    }
    else if(this->type == VarientType::CAMERA) {
        return this->cameraValue;
    }
    else if(this->type == VarientType::PLAYER) {
        return this->playerValue;
    }
    else if(this->type == VarientType::SIDE_SCROLL_AREA) {
        return this->sideScrollValue;
    }
    else if(this->type == VarientType::WINDOW) {
        return this->windowValue;
    }
    else if(this->type == VarientType::SPAWN_POINTS) {
        return this->spawnPointsValue;
    }
    else if(this->type == VarientType::KEYS_PRESSED) {
        return this->keysPressedValue;
    }
    else {
        return nullptr;
    }
}

/**
 * @brief Destroy the Event object
 */
Event::~Event() {}

/**
 * @brief Construct a new Event object
 * 
 * @param type type of event
 */
Event::Event(EventType type) {
    this->type = type;
}

/**
 * @brief Get the Event Type object
 * 
 * @return EventType enum of types of events
 */
EventType Event::getEventType() {
    return this->type;
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, GameObject* value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, double value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, bool value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, char value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, float value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, Player* value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, sf::RenderWindow* value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, sf::View* value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, SideScrollArea* value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, std::vector<SpawnPoint*>* value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Add Varient to the map of parameters
 * 
 * @param paramType type of parameter
 * @param value value of varient
 */
void Event::addVarient(ParamType paramType, KeysPressed* value) {
    this->parameters.insert({paramType, Varient(value)});
}

/**
 * @brief Get the Varient object from the map of parameters using the parameter type
 * 
 * @param paramType type of parameter being stored
 * @return Varient Varient object containing the type and value
 */
Varient Event::getVarient(ParamType paramType) {
    return this->parameters.find(paramType)->second;
}