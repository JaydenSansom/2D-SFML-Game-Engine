#include "Platforms.hpp"

/**
 * @brief Construct a new Platform object with no given parameters.
 */
Platform::Platform() {
    setPosition(0.f, 0.f);
    setSize(sf::Vector2f(50.f, 50.f));
    setFillColor(sf::Color(0, 0, 0));
}

/**
 * @brief Construct a new Platform object
 * 
 * @param x x position
 * @param y y position
 * @param width width of the platform
 * @param height height of the platform
 */
Platform::Platform(float x, float y, float width, float height) {
    setPosition(x, y);
    setSize(sf::Vector2f(width, height));
    setFillColor(sf::Color(0, 0, 0));
}

/**
 * @brief Construct a new Platform object
 * 
 * @param x x position
 * @param y y position
 * @param width width of the platform
 * @param height height of the platform
 * @param texturePath path to the texture file
 */
Platform::Platform(float x, float y, float width, float height, const std::string& texturePath) {
    setPosition(x, y);
    setSize(sf::Vector2f(width, height));
    
    // Load and set texture
    if (texture.loadFromFile(texturePath)) {
        setTexture(&texture);
    }
}

/**
 * @brief Get the Global Bounds object
 * 
 * @return sf::FloatRect global bounds of the object.
 */
sf::FloatRect Platform::getGlobalBounds() const {
    return sf::RectangleShape::getGlobalBounds();
}

/**
 * @brief Override of the move function.
 * 
 * @param xOffset amount to move in the x direction.
 * @param yOffset amount to move in the y direction.
 */
void Platform::move(float xOffset, float yOffset) {
    setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
}

/**
 * @brief Override of the move function.
 * 
 * @param offset amount to move given a float 2D vector.
 */
void Platform::move(sf::Vector2f offset) {
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Override of the getPosition function.
 * 
 * @return sf::Vector2f position of the object
 */
sf::Vector2f Platform::getPosition() {
    return sf::RectangleShape::getPosition();
}

/**
 * @brief Get the Movement of an object
 * 
 * @return sf::Vector2f total movement of the object in that frame
 */
sf::Vector2f Platform::getMovement() {
    return sf::Vector2f(0.f, 0.f);
}

/**
 * @brief Construct a new Moving Platform object with no given parameters.
 */
MovingPlatform::MovingPlatform() {
    setPosition(0.f, 0.f);
    setSize(sf::Vector2f(50.f, 50.f));
    setFillColor(sf::Color(0, 0, 0));
    _speed = 40.f;
    _x = 0.f;
    _y = 0.f;
    _destX = 50.f;
    _destY = 0.f;
    movingForward = true;
    _pauseLength = 0.f;
    paused = false;
    totalMovement = sf::Vector2f(0.f, 0.f);
}

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
MovingPlatform::MovingPlatform(float speed, float x, float y, float destX, float destY, float width, float height, float pauseLength) {
    setPosition(x, y);
    setSize(sf::Vector2f(width, height));
    setFillColor(sf::Color(0, 0, 0));
    _speed = speed;
    _x = x;
    _y = y;
    _destX = destX;
    _destY = destY;
    movingForward = true;
    _pauseLength = pauseLength;
    paused = false;
    totalMovement = sf::Vector2f(0.f, 0.f);
}

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
MovingPlatform::MovingPlatform(float speed, float x, float y, float destX, float destY, float width, float height, float pauseLength, const std::string& texturePath) {
    setPosition(x, y);
    setSize(sf::Vector2f(width, height));
    _speed = speed;
    _x = x;
    _y = y;
    _destX = destX;
    _destY = destY;
    movingForward = true;
    _pauseLength = pauseLength;
    paused = false;
    totalMovement = sf::Vector2f(0.f, 0.f);
    
    // Load and set texture
    if (texture.loadFromFile(texturePath)) {
        setTexture(&texture);
    }
}

/**
 * @brief Get the Global Bounds object
 * 
 * @return sf::FloatRect global bounds of the object.
 */
sf::FloatRect MovingPlatform::getGlobalBounds() const {
    return sf::RectangleShape::getGlobalBounds();
}

/**
 * @brief Override of the move function.
 * 
 * @param xOffset amount to move in the x direction.
 * @param yOffset amount to move in the y direction.
 */
void MovingPlatform::move(float xOffset, float yOffset) {
    setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
}

/**
 * @brief Override of the move function.
 * 
 * @param offset amount to move given a float 2D vector.
 */
void MovingPlatform::move(sf::Vector2f offset) {
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Override of the getPosition function.
 * 
 * @return sf::Vector2f position of the object
 */
sf::Vector2f MovingPlatform::getPosition() {
    return sf::RectangleShape::getPosition();
}

/**
 * @brief Get the Movement of an object
 * 
 * @return sf::Vector2f total movement of the object in that frame
 */
sf::Vector2f MovingPlatform::getMovement() {
    return totalMovement;
}

/**
 * @brief Update each frame, transforming the object based on time.
 * 
 * @param time time elapsed since the last frame
 */
void MovingPlatform::update(float time) {
    totalMovement = sf::Vector2f(0.f, 0.f);

    // If the platform is currently paused
    if(paused && _pauseLength != 0.f) {
        pauseTimer -= time;

        // If timer is done
        if(pauseTimer <= 0.f) {
            paused = false;
            pauseTimer = 0.f;
            movingForward = !movingForward;
        }

        return;
    }

    sf::Vector2f currentPosition = getPosition();

    if(movingForward) { // Move forward
        // Calculate the normalized vector towards destination
        sf::Vector2f directionVector(_destX - currentPosition.x, _destY - currentPosition.y);
        // Get direction vector length
        float directionLength = std::sqrt(std::pow(directionVector.x, 2.f) + std::pow(directionVector.y, 2.f));
        if(directionLength > 0) { // Normalize
            directionVector /= directionLength;
        }

        float xOffset = _speed * time * directionVector.x;
        float yOffset = _speed * time * directionVector.y;
        if(currentPosition.x + xOffset >= _destX || currentPosition.y + yOffset >= _destY) {
            totalMovement = sf::Vector2f(_destX - currentPosition.x, _destY - currentPosition.y);
            setPosition(_destX, _destY);
            paused = true;
            pauseTimer = _pauseLength;
        }
        else {
            totalMovement = sf::Vector2f(xOffset, yOffset);
            move(totalMovement);
        }
    }
    else { // Move backward
        // Calculate the normalized vector towards origin
        sf::Vector2f directionVector(_x - currentPosition.x, _y - currentPosition.y);
        // Get direction vector length
        float directionLength = std::sqrt(std::pow(directionVector.x, 2.f) + std::pow(directionVector.y, 2.f));
        if(directionLength > 0) { // Normalize
            directionVector /= directionLength;
        }

        float xOffset = _speed * time * directionVector.x;
        float yOffset = _speed * time * directionVector.y;
        if(currentPosition.x - xOffset <= _x || currentPosition.y - yOffset <= _y) {
            totalMovement = sf::Vector2f(_x - currentPosition.x, _y - currentPosition.y);
            setPosition(_x, _y);
            paused = true;
            pauseTimer = _pauseLength;
        }
        else {
            totalMovement = sf::Vector2f(xOffset, yOffset);
            move(totalMovement);
        }
    }
}