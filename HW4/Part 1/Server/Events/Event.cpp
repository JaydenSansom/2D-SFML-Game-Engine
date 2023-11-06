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
 * @brief Get the Value object of the varient
 * 
 * @return void* pointer to the value of the varient
 */
void* Varient::getValue() {
    if(this->type == VarientType::OBJ_POINTER) {
        return &this->gameObjValue;
    }
    else if(this->type == VarientType::DOUBLE) {
        return &this->doubleValue;
    }
    else if(this->type == VarientType::BOOL) {
        return &this->boolValue;
    }
    else {
        return nullptr;
    }
}

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
 * @brief Get the Varient object from the map of parameters using the parameter type
 * 
 * @param paramType type of parameter being stored
 * @return Varient Varient object containing the type and value
 */
Varient Event::getVarient(ParamType paramType) {
    return this->parameters.find(paramType)->second;
}