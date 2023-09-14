#include "Player.hpp"

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
 */
void Player::update(float time) {
    totalMovement = sf::Vector2f(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // Left or A key is pressed: move the player to the left
        totalMovement.x -= _speed * time;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // Right or D key is pressed: move the player to the right
        totalMovement.x += _speed * time;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !isJumping) {
        // Space or W key is pressed: the player jumps
        isJumping = true;
        jumpVelocity = -_jumpSpeed;
    }

    bool isColliding = checkCollision();

    if(onPlatform && !isJumping) {
        move(collidingPlatform->getMovement());
    }

    // Fall down by gravity
    totalMovement.y = jumpVelocity * time;
    jumpVelocity += _gravity * sqrt(time);

    move(totalMovement);

    checkWindowCollision();

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
bool Player::checkCollision() {
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
                resolveCollision(*this, *collideable);
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
 * @brief Checks if the player is against the window edge, not allowing it to go further
 */
void Player::checkWindowCollision() {
    if(getPosition().x < 0) {
        setPosition(0.f, getPosition().y);
    }
    if(getPosition().y < 0) {
        setPosition(getPosition().x, 0.f);
    }
    if(getPosition().x + getGlobalBounds().width > _windowWidth) {
        setPosition(_windowWidth - getGlobalBounds().width, getPosition().y);
    }
    if(getPosition().y + getGlobalBounds().height > _windowHeight) {
        setPosition(getPosition().x, _windowHeight - getGlobalBounds().height);
    }
}
