#include "Collider.hpp"

// Global List containing all collionable objects
std::vector<Collider*> collisionObjects;

/**
 * @brief Destroy the Collider object
 */
Collider::~Collider() {}

/**
 * @brief Set Collision to be enabled or disabled
 * 
 * @param enabled whether collision is to be enabled or not
 */
void Collider::setCollisionEnabled(bool enabled) {
    collisionEnabled = enabled;
    if(enabled) {
        collisionObjects.push_back(this);
    }
    else {
        // Remove from the global list
        auto toRemove = std::find(collisionObjects.begin(), collisionObjects.end(), this);
        if(toRemove != collisionObjects.end()) {
            collisionObjects.erase(toRemove);
        }
    }
}

/**
 * @brief Get the Collision enable boolean
 * 
 * @return bool is collision is enabled
 */
bool Collider::getCollisionEnabled() {
    return collisionEnabled;
}

/**
 * @brief Checks if the object collides with any other with collision on. It will resolve the object 
 * collision if needed.
 * 
 * @return bool of whether the collide object collides with any object in the collideableObjects list.
 */
bool Collider::checkCollision() {
    if(collisionEnabled) {
        sf::FloatRect checkBounds = getGlobalBounds();

        for(Collider* collideable : collisionObjects) {
            if(collideable == this) {
                continue;
            }

            sf::FloatRect collideableBounds = collideable->getGlobalBounds();

            if(checkBounds.intersects(collideableBounds)) {
                resolveCollision(*this, *collideable);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Checks if the object collides with another object. This will not resolve the collision
 * 
 * @param sf::FloatRect bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool Collider::checkCollision(sf::FloatRect objectToCheck) {
    if(collisionEnabled) {
        sf::FloatRect checkBounds = getGlobalBounds();

        if(checkBounds.intersects(objectToCheck)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the object collides with a list of objects. This will not resolve the collision
 * 
 * @param std::vector<sf::FloatRect> bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool Collider::checkCollision(std::vector<sf::FloatRect> objectsToCheck) {
    if(collisionEnabled) {
        sf::FloatRect checkBounds = getGlobalBounds();

        for(sf::FloatRect bounds : objectsToCheck) {
            if(checkBounds.intersects(bounds)) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Resolves a collision by taking an object and what it collides with and moving it back outside 
 * that object.
 * 
 * @param colliderOne Object to move outside of the bounding box of the other.
 * @param colliderTwo Object being collided with.
 */
void Collider::resolveCollision(Collider& colliderOne, Collider& colliderTwo) {
    sf::FloatRect boundsOne = colliderOne.getGlobalBounds();
    sf::FloatRect boundsTwo = colliderTwo.getGlobalBounds();

    // Find how much is being intersected in each direction.
    float intersectingX = std::min(boundsOne.left + boundsOne.width, boundsTwo.left + boundsTwo.width) - std::max(boundsOne.left, boundsTwo.left);
    float intersectingY = std::min(boundsOne.top + boundsOne.height, boundsTwo.top + boundsTwo.height) - std::max(boundsOne.top, boundsTwo.top);

    // Move outside collision
    if(intersectingX < intersectingY) {
        if(boundsOne.left > boundsTwo.left) {
            colliderOne.move(intersectingX, 0);
        }
        else {
            colliderOne.move(-intersectingX, 0);
        }
    }
    else {
        if(boundsOne.top > boundsTwo.top) {
            colliderOne.move(0, intersectingY);
        }
        else {
            colliderOne.move(0, -intersectingY);
        }
    }
}
