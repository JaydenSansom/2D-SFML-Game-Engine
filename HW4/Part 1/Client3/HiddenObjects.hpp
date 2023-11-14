#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.hpp"

/**
 * @brief Class for a spawn point object
 */
class SpawnPoint : public Collider {
    public:
        /**
         * @brief Construct a new Spawn Point object with no given parameters.
         */
        SpawnPoint();

        /**
         * @brief Construct a new Spawn Point object
         * 
         * @param x x position
         * @param y y position
         */
        SpawnPoint(float x, float y);

        /**
         * @brief Set the Spawn Point Location object
         * 
         * @param x x position
         * @param y y position
         */
        void setSpawnPointLocation(float x, float y);

        /**
         * @brief Get the Spawn Point Location object
         * 
         * @return sf::Vector2f spawn point location.
         */
        sf::Vector2f getSpawnPointLocation();

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

    private:
        sf::Vector2f spawnPointLocation;
};

/**
 * @brief Class for a death zone object
 */
class DeathZone : public sf::RectangleShape, public Collider {
    public:
        /**
         * @brief Construct a Death Zone object with no given parameters.
         */
        DeathZone();

        /**
         * @brief Construct a new Death Zone object
         * 
         * @param x x position
         * @param y y position
         * @param width width of the zone
         * @param height height of the zone
         */
        DeathZone(float x, float y, float width, float height);

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

    private:
        
};

/**
 * @brief Class for a Side Scroll Area object
 */
class SideScrollArea : public sf::RectangleShape, public Collider {
    public:
        /**
         * @brief Construct a Side Scroll Area object with no given parameters.
         */
        SideScrollArea();

        /**
         * @brief Construct a new Side Scroll Area object
         * 
         * @param x x position
         * @param y y position
         * @param width width of the zone
         * @param height height of the zone
         */
        SideScrollArea(float x, float y, float width, float height);

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

    private:
        
};