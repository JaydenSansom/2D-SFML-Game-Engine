#include "HiddenObjects.hpp"

/**
 * @brief Construct a new Spawn Point object with no given parameters.
 */
SpawnPoint::SpawnPoint() {
    setSpawnPointLocation(0.f, 0.f);
}

/**
 * @brief Construct a new Spawn Point object
 * 
 * @param x x position
 * @param y y position
 */
SpawnPoint::SpawnPoint(float x, float y) {
    setSpawnPointLocation(x, y);
}

/**
 * @brief Set the Spawn Point Location object
 * 
 * @param x x position
 * @param y y position
 */
void SpawnPoint::setSpawnPointLocation(float x, float y) {
    spawnPointLocation = sf::Vector2f(x, y);
}

/**
 * @brief Get the Spawn Point Location object
 * 
 * @return sf::Vector2f spawn point location.
 */
sf::Vector2f SpawnPoint::getSpawnPointLocation() {
    return spawnPointLocation;
}

/**
 * @brief Get the Global Bounds object
 * 
 * @return sf::FloatRect global bounds of the object.
 */
sf::FloatRect SpawnPoint::getGlobalBounds() const {
    return sf::FloatRect();
}

/**
 * @brief Override of the move function.
 * 
 * @param xOffset amount to move in the x direction.
 * @param yOffset amount to move in the y direction.
 */
void SpawnPoint::move(float xOffset, float yOffset) {
    spawnPointLocation = sf::Vector2f(getPosition().x + xOffset, getPosition().y + yOffset);
}

/**
 * @brief Override of the move function.
 * 
 * @param offset amount to move given a float 2D vector.
 */
void SpawnPoint::move(sf::Vector2f offset) {
    spawnPointLocation = sf::Vector2f(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Override of the getPosition function.
 * 
 * @return sf::Vector2f position of the object
 */
sf::Vector2f SpawnPoint::getPosition() {
    return spawnPointLocation;
}

/**
 * @brief Get the Movement of an object
 * 
 * @return sf::Vector2f total movement of the object in that frame
 */
sf::Vector2f SpawnPoint::getMovement() {
    return sf::Vector2f(0.f, 0.f);
}

/**
 * @brief Construct a Death Zone object with no given parameters.
 */
DeathZone::DeathZone() {
    setPosition(0.f, 0.f);
    setSize(sf::Vector2f(50.f, 50.f));
    setFillColor(sf::Color(255, 0, 0));
}

/**
 * @brief Construct a new Death Zone object
 * 
 * @param x x position
 * @param y y position
 * @param width width of the zone
 * @param height height of the zone
 */
DeathZone::DeathZone(float x, float y, float width, float height) {
    setPosition(x, y);
    setSize(sf::Vector2f(width, height));
    setFillColor(sf::Color(255, 0, 0));
}

/**
 * @brief Get the Global Bounds object
 * 
 * @return sf::FloatRect global bounds of the object.
 */
sf::FloatRect DeathZone::getGlobalBounds() const {
    return sf::RectangleShape::getGlobalBounds();
}

/**
 * @brief Override of the move function.
 * 
 * @param xOffset amount to move in the x direction.
 * @param yOffset amount to move in the y direction.
 */
void DeathZone::move(float xOffset, float yOffset) {
    setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
}

/**
 * @brief Override of the move function.
 * 
 * @param offset amount to move given a float 2D vector.
 */
void DeathZone::move(sf::Vector2f offset) {
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Override of the getPosition function.
 * 
 * @return sf::Vector2f position of the object
 */
sf::Vector2f DeathZone::getPosition() {
    return sf::RectangleShape::getPosition();
}

/**
 * @brief Get the Movement of an object
 * 
 * @return sf::Vector2f total movement of the object in that frame
 */
sf::Vector2f DeathZone::getMovement() {
    return sf::Vector2f(0.f, 0.f);
}