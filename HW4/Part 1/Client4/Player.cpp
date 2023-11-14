#include "Player.hpp"
#include "EventManager.hpp"

struct KeysPressed;

/**
 * @brief Construct a new Player object.
 * 
 * @param texturePath path to the texture
 */
Player::Player(float windowWidth, float windowHeight, const std::string& texturePath) {
    setPosition(0.f, 0.f);
    _speed = 50.f;
    _gravity = 9.81f;
    _jumpSpeed = 10.f;
    jumpVelocity = 0.f;
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    isJumping = false;
    totalMovement = sf::Vector2f(0.f, 0.f);
    onPlatform = false;
    
    // Load and set texture
    if (texture.loadFromFile(texturePath)) {
        setTexture(texture);
    }
}

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
Player::Player(float windowWidth, float windowHeight, const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed) {
    setPosition(x, y);
    _speed = speed;
    _gravity = gravity;
    _jumpSpeed = jumpSpeed;
    jumpVelocity = 0.f;
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    isJumping = false;
    onPlatform = false;
    totalMovement = sf::Vector2f(0.f, 0.f);
    
    // Load and set texture
    if (texture.loadFromFile(texturePath)) {
        setTexture(texture);
    }
}

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
Player::Player(float windowWidth, float windowHeight, const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed, float scaleX, float scaleY) {
    setPosition(x, y);
    setScale(sf::Vector2f(scaleX, scaleY));
    _speed = speed;
    _gravity = gravity;
    _jumpSpeed = jumpSpeed;
    jumpVelocity = 0.f;
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    isJumping = false;
    onPlatform = false;
    totalMovement = sf::Vector2f(0.f, 0.f);
    
    // Load and set texture
    if (texture.loadFromFile(texturePath)) {
        setTexture(texture);
    }
}

/**
 * @brief Get the Global Bounds object
 * 
 * @return sf::FloatRect global bounds of the object.
 */
sf::FloatRect Player::getGlobalBounds() const {
    return sf::Sprite::getGlobalBounds();
}

/**
 * @brief Override of the move function.
 * 
 * @param xOffset amount to move in the x direction.
 * @param yOffset amount to move in the y direction.
 */
void Player::move(float xOffset, float yOffset) {
    setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
}

/**
 * @brief Override of the move function.
 * 
 * @param offset amount to move given a float 2D vector.
 */
void Player::move(sf::Vector2f offset) {
    setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
}

/**
 * @brief Override of the getPosition function.
 * 
 * @return sf::Vector2f position of the object
 */
sf::Vector2f Player::getPosition() {
    return sf::Sprite::getPosition();
}

/**
 * @brief Get the Movement of an object
 * 
 * @return sf::Vector2f total movement of the object in that frame
 */
sf::Vector2f Player::getMovement() {
    return totalMovement;
}

/**
 * @brief Update each frame, transforming the object based on time and keyboard input.
 * 
 * @param time time elapsed since the last frame
 * @param keysPressed input keys currently pressed
 */
void Player::update(float time, KeysPressed keysPressed, EventManager* manager) {
    totalMovement = sf::Vector2f(0.f, 0.f);

    if (keysPressed.Left) {
        // Left or A key is pressed: move the player to the left
        totalMovement.x -= _speed * time;
    }
    if (keysPressed.Right) {
        // Right or D key is pressed: move the player to the right
        totalMovement.x += _speed * time;
    }
    if (keysPressed.Up && !isJumping) {
        // Space or W key is pressed: the player jumps
        isJumping = true;
        jumpVelocity = -_jumpSpeed;
    }

    bool isColliding = checkCollision(manager);

    if(onPlatform && !isJumping) {
        move(collidingPlatform->getMovement());
    }

    // Fall down by gravity
    totalMovement.y = jumpVelocity * time;
    jumpVelocity += _gravity * sqrt(time);

    move(totalMovement);

    if (onPlatform) {
        isJumping = false;
        jumpVelocity = 0.f;
    }
    
}

/**
 * @brief An override of the Collision function that adds logic of whether the player is on a platform.
 * 
 * @return whether there was a collision
 */
bool Player::checkCollision(EventManager* manager) {
    if(getCollisionEnabled()) {
        sf::FloatRect checkBounds = getGlobalBounds();

        bool bottomCollision = false;

        for(Collider* collideable : collisionObjects) {
            if(collideable == this) {
                continue;
            }

            sf::FloatRect collideableBounds = collideable->getGlobalBounds();

            if(checkBounds.top + checkBounds.height < collideableBounds.top + collideableBounds.height && onPlatform) {
                bottomCollision = true;
            }

            if(checkBounds.intersects(collideableBounds)) {
                if(checkBounds.top + checkBounds.height >= collideableBounds.top && checkBounds.top < collideableBounds.top) {
                    onPlatform = true;
                }
                collidingPlatform = collideable;
                manager->registerEvent(new EventCollisionHandler(manager, new EventCollision(this, new GameObject("", collideable))));
                return true;
            }
        }
        if(bottomCollision && !isJumping) {
            // Constants are tested to have additional movement due to collision not being directly detected every frame.
            move(collidingPlatform->getMovement().x * 1.1f, collidingPlatform->getMovement().y * 1.5f);
        }
    }
    onPlatform = false;
    collidingPlatform = nullptr;
    return false;
}

/**
 * @brief Checks if the object collides with another object. This will not resolve the collision
 * 
 * @param sf::FloatRect bounds to check for collision
 * @return bool of whether the collide object collides with the object.
 */
bool Player::checkCollision(sf::FloatRect objectToCheck) {
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
bool Player::checkCollision(std::vector<sf::FloatRect> objectsToCheck) {
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
