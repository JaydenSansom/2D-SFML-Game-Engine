#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <SFML/Graphics.hpp>

/**
 * @brief Class for the interface of a collider
 */
class Collider {
    public:
        /**
         * @brief Destroy the Collider object
         */
        virtual ~Collider();

        /**
         * @brief Set Collision to be enabled or disabled
         * 
         * @param enabled whether collision is to be enabled or not
         */
        void setCollisionEnabled(bool enabled);

        /**
         * @brief Get the Collision enable boolean
         * 
         * @return bool is collision is enabled
         */
        bool getCollisionEnabled();

        /**
         * @brief Checks if the object collides with any other with collision on. It will resolve the object 
         * collision if needed.
         * 
         * @return bool of whether the collide object collides with any object in the collideableObjects list.
         */
        bool checkCollision();

        /**
         * @brief Checks if the object collides with another object. This will not resolve the collision
         * 
         * @param sf::FloatRect bounds to check for collision
         * @return bool of whether the collide object collides with the object.
         */
        bool checkCollision(sf::FloatRect objectToCheck);

        /**
         * @brief Checks if the object collides with a list of objects. This will not resolve the collision
         * 
         * @param std::vector<Collider*> collideable objects to check for collision
         * @return bool of whether the collide object collides with the object.
         */
        bool checkCollision(std::vector<sf::FloatRect> objectsToCheck);

        /**
         * @brief Resolves a collision by taking an object and what it collides with and moving it back outside 
         * that object.
         * 
         * @param colliderOne Object to move outside of the bounding box of the other.
         * @param colliderTwo Object being collided with.
         */
        void resolveCollision(Collider& colliderOne, Collider& colliderTwo);

        /**
         * @brief Virtual method for moving within the Collider class.
         * 
         * @param xOffset amount to move in the x direction.
         * @param yOffset amount to move in the y direction.
         */
        virtual void move(float xOffset, float yOffset) = 0;

        /**
         * @brief Virtual method for moving within the Collider class.
         * 
         * @param offset amount to move given a float 2D vector.
         */
        virtual void move(sf::Vector2f offset) = 0;

        /**
         * @brief Virtual method for getting the position of the given object.
         * 
         * @return sf::Vector2f position of the object
         */
        virtual sf::Vector2f getPosition() = 0;

        /**
         * @brief Get the Global Bounds object
         * 
         * @return sf::FloatRect global bounds of the object.
         */
        virtual sf::FloatRect getGlobalBounds() const = 0;

        /**
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        virtual sf::Vector2f getMovement() = 0;

    private:
        bool collisionEnabled; // Whether the object has collision enabled
};

#endif