#pragma once

class Player;

#include <iostream>
#include <map>
#include "Player.hpp"
#include "HiddenObjects.hpp"
#include "GameObject.hpp"

/**
 * @brief Client info represented as a struct including the client's name and player character object.
 */
struct PlayerClient {
    std::string name;
    Player* player;
    bool isActive;
};

/**
 * @brief What input keys are being currently pressed
 */
struct KeysPressed {
    bool Up = false;
    bool Left = false;
    bool Right = false;
};

/**
 * @brief Event types possible
 */
enum class EventType {
    EVENT_COLLISION, EVENT_DEATH, EVENT_SPAWN, EVENT_INPUT, EVENT_CLIENT_DISCONNECT
};

/**
 * @brief Parameter types that will be used in events
 */
enum class ParamType {
    X_POS, Y_POS, CHAR_POINTER, OBJ_POINTER, USER_INPUT_KEY, WINDOW, CAMERA, LEFT_SIDE_SCROLL, RIGHT_SIDE_SCROLL, SPAWN_POINTS, ELAPSED_TIME, CLIENT_NAME, CLIENTS, IS_SPRINTING
};

/**
 * @brief Varient types of what the map object can be
 */
enum class VarientType {
    OBJ_POINTER, DOUBLE, BOOL, CHAR, PLAYER, CAMERA, WINDOW, SIDE_SCROLL_AREA, SPAWN_POINTS, FLOAT, KEYS_PRESSED, STRING, CLIENTS
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
         * @brief Construct a new Varient object with a string value
         * 
         * @param value string to set as the value of the varient
         */
        Varient(std::string value);

        /**
         * @brief Construct a new Varient object with a boolean value
         * 
         * @param value boolean to set as the value of the varient
         */
        Varient(bool value);

        /**
         * @brief Construct a new Varient object with a boolean value
         * 
         * @param value char to set as the value of the varient
         */
        Varient(char value);

        /**
         * @brief Construct a new Varient object with a float value
         * 
         * @param value char to set as the value of the varient
         */
        Varient(float value);

        /**
         * @brief Construct a new Varient object with a player value
         * 
         * @param value player to set as the value of the varient
         */
        Varient(Player* value);

        /**
         * @brief Construct a new Varient object with a window value
         * 
         * @param value window to set as the value of the varient
         */
        Varient(sf::RenderWindow* value);

        /**
         * @brief Construct a new Varient object with a view value
         * 
         * @param value view to set as the value of the varient
         */
        Varient(sf::View* value);

        /**
         * @brief Construct a new Varient object with a keyspressed value
         * 
         * @param value keyspressed to set as the value of the varient
         */
        Varient(KeysPressed* value);

        /**
         * @brief Construct a new Varient object with a view value
         * 
         * @param value view to set as the value of the varient
         */
        Varient(SideScrollArea* value);

        /**
         * @brief Construct a new Varient object with a vector of spawn points value
         * 
         * @param value spawn points to set as the value of the varient
         */
        Varient(std::vector<SpawnPoint*>* value);

        /**
         * @brief Construct a new Varient object with a vector of clients value
         * 
         * @param value player client list to set as the value of the varient
         */
        Varient(std::vector<PlayerClient>* value);


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
        std::string stringValue;
        bool boolValue;
        char charValue;
        float floatValue;
        KeysPressed* keysPressedValue;
        Player* playerValue;
        sf::RenderWindow* windowValue;
        sf::View* cameraValue;
        SideScrollArea* sideScrollValue;
        std::vector<SpawnPoint*>* spawnPointsValue;
        std::vector<PlayerClient>* clientsValue;

};

/**
 * @brief Event class meant to represent an Event
 */
class Event {

    public:
        /**
         * @brief Destroy the Event object
         */
        virtual ~Event();

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
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, char value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, std::string value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, float value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, Player* value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, sf::RenderWindow* value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, sf::View* value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, KeysPressed* value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, SideScrollArea* value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, std::vector<SpawnPoint*>* value);

        /**
         * @brief Add Varient to the map of parameters
         * 
         * @param paramType type of parameter
         * @param value value of varient
         */
        void addVarient(ParamType paramType, std::vector<PlayerClient>* value);

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