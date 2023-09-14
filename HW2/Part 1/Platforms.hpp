#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Collider.hpp"

/**
 * @brief Class for a static platform object
 */
class Platform : public sf::RectangleShape, public Collider {
    public:
        /**
         * @brief Construct a new Platform object with no given parameters.
         */
        Platform();

        /**
         * @brief Construct a new Platform object
         * 
         * @param x x position
         * @param y y position
         * @param width width of the platform
         * @param height height of the platform
         */
        Platform(float x, float y, float width, float height);

        /**
         * @brief Construct a new Platform object
         * 
         * @param x x position
         * @param y y position
         * @param width width of the platform
         * @param height height of the platform
         * @param texturePath path to the texture file
         */
        Platform(float x, float y, float width, float height, const std::string& texturePath);

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
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        sf::Vector2f getMovement() override;

    private:
        sf::Texture texture; // Texture of the platform
};

/**
 * @brief Class for a moveable platform object
 */
class MovingPlatform : public sf::RectangleShape, public Collider {
    public:
        /**
         * @brief Construct a new Moving Platform object with no given parameters.
         */
        MovingPlatform();

        /**
         * @brief Construct a new Moving Platform object.
         * 
         * @param speed speed of the moving platform
         * @param x x position
         * @param y y position
         * @param destX x position to move back and forth to
         * @param destY y position to move back and forth to
         * @param width width of the platform
         * @param height height of the platform
         * @param pauseLength length to pause when reaching the destination
         */
        MovingPlatform(float speed, float x, float y, float destX, float destY, float width, float height, float pauseLength);

        /**
         * @brief Construct a new Moving Platform object.
         * 
         *  @param speed speed of the moving platform
         * @param x x position
         * @param y y position
         * @param destX x position to move back and forth to
         * @param destY y position to move back and forth to
         * @param width width of the platform
         * @param height height of the platform
         * @param pauseLength length to pause when reaching the destination
         * @param texturePath path to the texture file
         */
        MovingPlatform(float speed, float x, float y, float destX, float destY, float width, float height, float pauseLength, const std::string& texturePath);

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
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        sf::Vector2f getMovement() override;

        /**
         * @brief Update each frame, transforming the object based on time.
         * 
         * @param time time elapsed since the last frame
         */
        void update(float time);

    private:
        float _speed; // Speed of the moving platform
        float _x; // X Position of the moving platform
        float _y; // Y Position of the moving platform
        float _destX; // X Position of the destination the platform moves to
        float _destY; // Y Position of the destination the platform moves to
        bool movingForward; // Whether the platform is moving forward
        bool paused; // If the platform is currently paused
        float pauseTimer; // Timer of how long the platform is going to be paused
        float _pauseLength; // How long to pause the platform before it begins in the other direction
        sf::Vector2f totalMovement; // Movement of the platform in this frame;
        sf::Texture texture; // Texture of the platform
};

#endif