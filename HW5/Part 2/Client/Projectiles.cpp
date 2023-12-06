#include "Projectiles.hpp"

/**
 * @brief Destroy the PlayerProjectile object
 */
PlayerProjectile::~PlayerProjectile() {}

/**
 * @brief Construct a new Platform object with no given parameters.
 */
PlayerProjectile::PlayerProjectile() {
    setPosition(0.f, 0.f);
    setSize(sf::Vector2f(2.f, 6.f));
    setFillColor(sf::Color(255, 255, 255));
}

/**
 * @brief Construct a new Platform object
 * 
 * @param x x position
 * @param y y position
 * @param width width of the platform
 * @param height height of the platform
 */
PlayerProjectile::PlayerProjectile(float x, float y) {
    setPosition(x, y);
    setSize(sf::Vector2f(2.f, 6.f));
    setFillColor(sf::Color(255, 255, 255));
}

/**
 * @brief Get the Global Bounds object
 * 
 * @return sf::FloatRect global bounds of the object.
 */
sf::FloatRect PlayerProjectile::getGlobalBounds() const {
    return sf::RectangleShape::getGlobalBounds();
}

/**
 * @brief Override of the move function.
 * 
 * @param xOffset amount to move in the x direction.
 * @param yOffset amount to move in the y direction.
 */
void PlayerProjectile::move(float xOffset, float yOffset) {
    setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
}

/**
 * @brief Override of the move function.
 * 
 * @param offset amount to move given a float 2D vector.
 */
void PlayerProjectile::move(sf::Vector2f offset) {
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Override of the getPosition function.
 * 
 * @return sf::Vector2f position of the object
 */
sf::Vector2f PlayerProjectile::getPosition() {
    return sf::RectangleShape::getPosition();
}

/**
 * @brief Get the Movement of an object
 * 
 * @return sf::Vector2f total movement of the object in that frame
 */
sf::Vector2f PlayerProjectile::getMovement() {
    return sf::Vector2f(0.f, 0.f);
}

/**
 * @brief Checks if the object collides with another object. This will not resolve the collision
 * 
 * @param sf::FloatRect bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool PlayerProjectile::checkCollision(sf::FloatRect objectToCheck) {
    if(getCollisionEnabled()) {
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
 * @param std::vector<Collider*> bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool PlayerProjectile::checkCollision(std::vector<sf::FloatRect> objectsToCheck) {
    if(getCollisionEnabled()) {
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
 * @brief Update each frame, transforming the object based on time and keyboard input.
 * 
 * @param time time elapsed since the last frame
 */
void PlayerProjectile::update(float time) {

    move(sf::Vector2f(0.f, -100.f * time));
    
}

/**
 * @brief Destroy the EnemyProjectile object
 */
EnemyProjectile::~EnemyProjectile() {}

/**
 * @brief Construct a new Platform object with no given parameters.
 */
EnemyProjectile::EnemyProjectile() {
    setPosition(0.f, 0.f);
    setSize(sf::Vector2f(2.f, 6.f));
    setFillColor(sf::Color(255, 255, 255));
}

/**
 * @brief Construct a new Platform object
 * 
 * @param x x position
 * @param y y position
 * @param width width of the platform
 * @param height height of the platform
 */
EnemyProjectile::EnemyProjectile(float x, float y) {
    setPosition(x, y);
    setSize(sf::Vector2f(2.f, 6.f));
    setFillColor(sf::Color(255, 255, 255));
}

/**
 * @brief Get the Global Bounds object
 * 
 * @return sf::FloatRect global bounds of the object.
 */
sf::FloatRect EnemyProjectile::getGlobalBounds() const {
    return sf::RectangleShape::getGlobalBounds();
}

/**
 * @brief Override of the move function.
 * 
 * @param xOffset amount to move in the x direction.
 * @param yOffset amount to move in the y direction.
 */
void EnemyProjectile::move(float xOffset, float yOffset) {
    setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
}

/**
 * @brief Override of the move function.
 * 
 * @param offset amount to move given a float 2D vector.
 */
void EnemyProjectile::move(sf::Vector2f offset) {
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Override of the getPosition function.
 * 
 * @return sf::Vector2f position of the object
 */
sf::Vector2f EnemyProjectile::getPosition() {
    return sf::RectangleShape::getPosition();
}

/**
 * @brief Get the Movement of an object
 * 
 * @return sf::Vector2f total movement of the object in that frame
 */
sf::Vector2f EnemyProjectile::getMovement() {
    return sf::Vector2f(0.f, 0.f);
}

/**
 * @brief Checks if the object collides with another object. This will not resolve the collision
 * 
 * @param sf::FloatRect bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool EnemyProjectile::checkCollision(sf::FloatRect objectToCheck) {
    if(getCollisionEnabled()) {
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
 * @param std::vector<Collider*> bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool EnemyProjectile::checkCollision(std::vector<sf::FloatRect> objectsToCheck) {
    if(getCollisionEnabled()) {
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
 * @brief Update each frame, transforming the object based on time and keyboard input.
 * 
 * @param time time elapsed since the last frame
 */
void EnemyProjectile::update(float time) {

    move(sf::Vector2f(0.f, 100.f * time));
    
}
