#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

#include "Collider.hpp"

/**
 * @brief GameObject class including the objects's name and object.
 */
class GameObject {
    public:
        /**
         * @brief Construct a new GameObject
         */
        GameObject(std::string name, Collider* object);

        /**
         * @brief Get the Name
         * 
         * @return std::string name
         */
        std::string getName();

        /**
         * @brief Get the Collider object
         * 
         * @return Collider* collider object
         */
        Collider* getCollider();

    private:
        std::string name; // Name of the GameObject
        Collider* object; // Collider Object of the GameObject
};

#endif