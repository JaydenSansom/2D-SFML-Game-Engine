#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Collider.hpp"

/**
 * @brief Class for a controlled player character
 */
class Enemy : public sf::Sprite, public Collider {
    public:
        virtual ~Enemy();

        /**
         * @brief Construct a new Player object.
         * 
         * @param texturePath path to the texture
         */
        Enemy(float x, float y, int column, const std::string& texturePath);

        sf::Vector2f getPosition() override;

        sf::FloatRect getGlobalBounds() const override;

        sf::Vector2f getMovement() override;

        void move(float xOffset, float yOffset) override;

        void move(sf::Vector2f offset) override;

        /**
         * @brief Get the column of the enemy
         * 
         * @return int column of the enemy
         */
        int getColumn();

        /**
         * @brief Update each frame, transforming the object based on time and keyboard input.
         * 
         * @param time time elapsed since the last frame
         * @param movement 1 = left, 2 = right, 3 = down
         */
        void update(float time, int movement);

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
        sf::Texture texture; // Texture of the platform
        int column;
};