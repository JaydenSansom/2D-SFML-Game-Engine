#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class EventManager;

#include "Collider.hpp"

/**
 * @brief What input keys are being currently pressed
 */
struct KeysPressed;

// Global List containing all collionable objects
extern std::vector<Collider*> collisionObjects;

/**
 * @brief Class for a controlled player character
 */
class Player : public sf::Sprite, public Collider {
    public:
        /**
         * @brief Construct a new Player object.
         * 
         * @param texturePath path to the texture
         */
        Player(float windowWidth, float windowHeight, const std::string& texturePath);

        /**
         * @brief Construct a new Player object
         * 
         * @param texturePath path to the texture file
         * @param x x position
         * @param y y position
         * @param speed speed of the moving platform
         * @param gravity gravity to be applied once in the air
         * @param jumpSpeed power of a jump
         */
        Player(float windowWidth, float windowHeight, const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed);

        /**
         * @brief Construct a new Player object
         * 
         * @param texturePath path to the texture file
         * @param x x position
         * @param y y position
         * @param speed speed of the moving platform
         * @param gravity gravity to be applied once in the air
         * @param jumpSpeed power of a jump
         * @param scaleX amount to scale the sprite by horizontally
         * @param scaleY amount to scale the sprite by vertically
         */
        Player(float windowWidth, float windowHeight, const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed, float scaleX, float scaleY);

        /**
         * @brief Get the Global Bounds object
         * 
         * @return sf::FloatRect global bounds of the object.
         */
        sf::FloatRect getGlobalBounds() const override;

        /**
         * @brief Override of the move function.
         * 
         * @param xOffset amount to move in the x direction.
         * @param yOffset amount to move in the y direction.
         */
        void move(float xOffset, float yOffset) override;

        /**
         * @brief Override of the move function.
         * 
         * @param offset amount to move given a float 2D vector.
         */
        void move(sf::Vector2f offset) override;

         /**
         * @brief Override of the getPosition function.
         * 
         * @return sf::Vector2f position of the object
         */
        sf::Vector2f getPosition() override;

        /**
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        sf::Vector2f getMovement() override;

        /**
         * @brief Update each frame, transforming the object based on time and keyboard input.
         * 
         * @param time time elapsed since the last frame
         * @param keysPressed input keys currently pressed
         */
        void update(float time, KeysPressed keysPressed, EventManager* manager);

        /**
         * @brief Update each frame, transforming the object based on time and keyboard input.
         * 
         * @param time time elapsed since the last frame
         * @param keysPressed input keys currently pressed
         * @param speedMultiplier is the player sprinting
         */
        void update(float time, KeysPressed keysPressed, EventManager* manager, bool isSprinting);

        /**
         * @brief An override of the Collision function that adds logic of whether the player is on a platform.
         * 
         * @return whether there was a collision
         */
        bool checkCollision(EventManager* manager);

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
         * @param std::vector<sf::FloatRect> collideable objects to check for collision
         * @return bool of whether the collide object collides with the object.
         */
        bool checkCollision(std::vector<sf::FloatRect> objectsToCheck);

    private:
        float _speed; // Speed of the player
        float _gravity; // Amount that gravity affects the player
        float _jumpSpeed; // Power of the jump of the player
        float jumpVelocity; // Current jump velocity
        float _windowWidth; // Width of the game window
        float _windowHeight; // Height of the game window
        bool isJumping; // Is the character currently jumping?
        bool onPlatform; // Is the player on a platform?
        Collider* collidingPlatform; // Pointer to the collider of the platform the player is on
        sf::Vector2f totalMovement; // Total movement of the player
        sf::Texture texture; // Texture of the platform
};