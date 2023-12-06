#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Collider.hpp"

/**
 * @brief Class for a player projectile object
 */
class PlayerProjectile : public sf::RectangleShape, public Collider {
    public:
        virtual ~PlayerProjectile();

        /**
         * @brief Construct a new PlayerProjectile object with no given parameters.
         */
        PlayerProjectile();

        /**
         * @brief Construct a new PlayerProjectile object
         * 
         * @param x x position
         * @param y y position
         */
        PlayerProjectile(float x, float y);

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
         * @brief Update each frame, transforming the object based on time
         * 
         * @param time time elapsed since the last frame
         */
        void update(float time);

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
        
};

/**
 * @brief Class for a enemy projectile object
 */
class EnemyProjectile : public sf::RectangleShape, public Collider {
    public:
        virtual ~EnemyProjectile();

        /**
         * @brief Construct a new EnemyProjectile object with no given parameters.
         */
        EnemyProjectile();

        /**
         * @brief Construct a new EnemyProjectile object
         * 
         * @param x x position
         * @param y y position
         */
        EnemyProjectile(float x, float y);

        /**
         * @brief Get the Global Bounds object
         * 
         * @return sf::FloatRect global bounds of the object.
         */
        sf::FloatRect getGlobalBounds() const override;

        /**
         * @brief Update each frame, transforming the object based on time
         * 
         * @param time time elapsed since the last frame
         */
        void update(float time);

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
        
};