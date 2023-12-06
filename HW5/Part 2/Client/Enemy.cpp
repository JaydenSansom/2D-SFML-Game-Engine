#include "Enemy.hpp"

Enemy::~Enemy() {};

/**
 * @brief Construct a new Player object.
 * 
 * @param texturePath path to the texture
 */
Enemy::Enemy(float x, float y, int column, const std::string& texturePath) {
    setPosition(x, y);
    this->column = column;
    
    // Load and set texture
    if (texture.loadFromFile(texturePath)) {
        setTexture(texture);
    }
}

sf::Vector2f Enemy::getPosition() {
    return sf::Sprite::getPosition();
}

sf::FloatRect Enemy::getGlobalBounds() const {
    return sf::Sprite::getGlobalBounds();
}

sf::Vector2f Enemy::getMovement() {
    return sf::Vector2f(0.f, 0.f);
}


void Enemy::move(float xOffset, float yOffset) {
    setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
}

void Enemy::move(sf::Vector2f offset) {
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Get the column of the enemy
 * 
 * @return int column of the enemy
 */
int Enemy::getColumn() {
    return this->column;
}

/**
 * @brief Update each frame, transforming the object based on time and keyboard input.
 * 
 * @param time time elapsed since the last frame
 * @param movement 1 = left, 2 = right, 3 = down
 */
void Enemy::update(float time, int movement) {
    if(movement == 1) {
        move(sf::Vector2f(-10.f * time, 0.f));
    }
    else if(movement == 2) {
        move(sf::Vector2f(10.f * time, 0.f));
    }
    else if(movement == 3) {
        move(sf::Vector2f(0.f, 10.f * time));
    }
}

/**
 * @brief Checks if the object collides with another object. This will not resolve the collision
 * 
 * @param sf::FloatRect bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool Enemy::checkCollision(sf::FloatRect objectToCheck) {
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
bool Enemy::checkCollision(std::vector<sf::FloatRect> objectsToCheck) {
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
