#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <map>
#include "../GameObjects/GameObject.hpp"

/**
 * @brief Event types possible
 */
enum class EventType {
    EVENT_COLLISION, EVENT_DEATH, EVENT_SPAWN, EVENT_INPUT
};

/**
 * @brief Parameter types that will be used in events
 */
enum class ParamType {
    X_POS, Y_POS, CHAR_POINTER, OBJ_POINTER, USER_INPUT
};

/**
 * @brief Varient types of what the map object can be
 */
enum class VarientType {
    OBJ_POINTER, DOUBLE, BOOL
};

/**
 * @brief Varient class used to represent the value of the map in the Event class
 */
class Varient {

    public: 
        /**
         * @brief Construct a new Varient object with a GameObject pointer value
         * 
         * @param value game object pointer to set as the value of the varient
         */
        Varient(GameObject* value);

        /**
         * @brief Construct a new Varient object with a double value
         * 
         * @param value double to set as the value of the varient
         */
        Varient(double value);

        /**
         * @brief Construct a new Varient object with a boolean value
         * 
         * @param value boolean to set as the value of the varient
         */
        Varient(bool value);

        /**
         * @brief Get the Value object of the varient
         * 
         * @return void* pointer to the value of the varient
         */
        void* getValue();

    private:
        VarientType type;
        GameObject* gameObjValue;
        double doubleValue;
        bool boolValue;

};

/**
 * @brief Event class meant to represent an Event
 */
class Event {

    public:
        /**
         * @brief Construct a new Event object
         * 
         * @param type type of event
         */
        Event(EventType type);

        /**
         * @brief Get the Event Type object
         * 
         * @return EventType enum of types of events
         */
        EventType getEventType();

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, GameObject* value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, double value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, bool value);

        /**
         * @brief Get the Varient object from the map of parameters using the parameter type
         * 
         * @param paramType type of parameter being stored
         * @return Varient Varient object containing the type and value
         */
        Varient getVarient(ParamType paramType);
    
    private:
        EventType type;
        std::map<ParamType, Varient> parameters;

};

#endif