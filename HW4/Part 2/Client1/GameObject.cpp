#include "GameObject.hpp"

/**
 * @brief Construct a new GameObject
 */
GameObject::GameObject(std::string name, Collider* object) {
    this->name = name;
    this->object = object;
}

/**
 * @brief Get the Name
 * 
 * @return std::string name
 */
std::string GameObject::getName() {
    return this->name;
}

/**
 * @brief Get the Collider object
 * 
 * @return Collider* collider object
 */
Collider* GameObject::getCollider() {
    return this->object;
}