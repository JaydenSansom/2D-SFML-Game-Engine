#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

// Global window size
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

class Collider;

// Global List containing all collionable objects
std::vector<Collider*> collisionObjects;

/**
 * @brief Class for the interface of a collider
 */
class Collider {
    public:
        /**
         * @brief Destroy the Collider object
         */
        virtual ~Collider() {}

        /**
         * @brief Set Collision to be enabled or disabled
         * 
         * @param enabled whether collision is to be enabled or not
         */
        void setCollisionEnabled(bool enabled) {
            collisionEnabled = enabled;
            if(enabled) {
                collisionObjects.push_back(this);
            }
            else {
                // Remove from the global list
                auto toRemove = std::find(collisionObjects.begin(), collisionObjects.end(), this);
                if(toRemove != collisionObjects.end()) {
                    collisionObjects.erase(toRemove);
                }
            }
        }

        /**
         * @brief Get the Collision enable boolean
         * 
         * @return bool is collision is enabled
         */
        bool getCollisionEnabled() {
            return collisionEnabled;
        }

        /**
         * @brief Checks if the object collides with any other with collision on. It will resolve the object 
         * collision if needed.
         * 
         * @return bool of whether the collide object collides with any object in the collideableObjects list.
         */
        bool checkCollision() {
            if(collisionEnabled) {
                sf::FloatRect checkBounds = getGlobalBounds();

                for(Collider* collideable : collisionObjects) {
                    if(collideable == this) {
                        continue;
                    }

                    sf::FloatRect collideableBounds = collideable->getGlobalBounds();

                    if(checkBounds.intersects(collideableBounds)) {
                        resolveCollision(*this, *collideable);
                        return true;
                    }
                }
            }
            return false;
        }

        /**
         * @brief Resolves a collision by taking an object and what it collides with and moving it back outside 
         * that object.
         * 
         * @param colliderOne Object to move outside of the bounding box of the other.
         * @param colliderTwo Object being collided with.
         */
        void resolveCollision(Collider& colliderOne, Collider& colliderTwo) {
            sf::FloatRect boundsOne = colliderOne.getGlobalBounds();
            sf::FloatRect boundsTwo = colliderTwo.getGlobalBounds();

            // Find how much is being intersected in each direction.
            float intersectingX = std::min(boundsOne.left + boundsOne.width, boundsTwo.left + boundsTwo.width) - std::max(boundsOne.left, boundsTwo.left);
            float intersectingY = std::min(boundsOne.top + boundsOne.height, boundsTwo.top + boundsTwo.height) - std::max(boundsOne.top, boundsTwo.top);

            // Move outside collision
            if(intersectingX < intersectingY) {
                if(boundsOne.left > boundsTwo.left) {
                    colliderOne.move(intersectingX, 0);
                }
                else {
                    colliderOne.move(-intersectingX, 0);
                }
            }
            else {
                if(boundsOne.top > boundsTwo.top) {
                    colliderOne.move(0, intersectingY);
                }
                else {
                    colliderOne.move(0, -intersectingY);
                }
            }
        }

        /**
         * @brief Virtual method for moving within the Collider class.
         * 
         * @param xOffset amount to move in the x direction.
         * @param yOffset amount to move in the y direction.
         */
        virtual void move(float xOffset, float yOffset) = 0;

        /**
         * @brief Virtual method for moving within the Collider class.
         * 
         * @param offset amount to move given a float 2D vector.
         */
        virtual void move(sf::Vector2f offset) = 0;

        /**
         * @brief Get the Global Bounds object
         * 
         * @return sf::FloatRect global bounds of the object.
         */
        virtual sf::FloatRect getGlobalBounds() const = 0;

        /**
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        virtual sf::Vector2f getMovement() = 0;

    private:
        bool collisionEnabled; // Whether the object has collision enabled
};

/**
 * @brief Class for a static platform object
 */
class Platform : public sf::RectangleShape, public Collider {
    public:
        /**
         * @brief Construct a new Platform object with no given parameters.
         */
        Platform() {
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
        Platform(float x, float y, float width, float height) {
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
        Platform(float x, float y, float width, float height, const std::string& texturePath) {
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
        sf::FloatRect getGlobalBounds() const override {
            return sf::RectangleShape::getGlobalBounds();
        }

        /**
         * @brief Override of the move function.
         * 
         * @param xOffset amount to move in the x direction.
         * @param yOffset amount to move in the y direction.
         */
        void move(float xOffset, float yOffset) override {
            setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
        }

        /**
         * @brief Override of the move function.
         * 
         * @param offset amount to move given a float 2D vector.
         */
        void move(sf::Vector2f offset) override {
            setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
        }

        /**
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        sf::Vector2f getMovement() override {
            return sf::Vector2f(0.f, 0.f);
        }

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
        MovingPlatform() {
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
        MovingPlatform(float speed, float x, float y, float destX, float destY, float width, float height, float pauseLength) {
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
        MovingPlatform(float speed, float x, float y, float destX, float destY, float width, float height, float pauseLength, const std::string& texturePath) {
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
        sf::FloatRect getGlobalBounds() const override {
            return sf::RectangleShape::getGlobalBounds();
        }

        /**
         * @brief Override of the move function.
         * 
         * @param xOffset amount to move in the x direction.
         * @param yOffset amount to move in the y direction.
         */
        void move(float xOffset, float yOffset) override {
            setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
        }

        /**
         * @brief Override of the move function.
         * 
         * @param offset amount to move given a float 2D vector.
         */
        void move(sf::Vector2f offset) override {
            setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
        }

        /**
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        sf::Vector2f getMovement() override {
            return totalMovement;
        }

        /**
         * @brief Update each frame, transforming the object based on time.
         * 
         * @param time time elapsed since the last frame
         */
        void update(float time) {
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

/**
 * @brief Class for a controlled player character
 */
class Player : public sf::Sprite, public Collider {
    public:
        /**
         * @brief Construct a new Player object.
         * 
         * @param texturePath path to the texture
         */
        Player(const std::string& texturePath) {
            setPosition(0.f, 0.f);
            _speed = 50.f;
            _gravity = 9.81f;
            _jumpSpeed = 10.f;
            jumpVelocity = 0.f;
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
        Player(const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed) {
            setPosition(x, y);
            _speed = speed;
            _gravity = gravity;
            _jumpSpeed = jumpSpeed;
            jumpVelocity = 0.f;
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
        Player(const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed, float scaleX, float scaleY) {
            setPosition(x, y);
            setScale(sf::Vector2f(scaleX, scaleY));
            _speed = speed;
            _gravity = gravity;
            _jumpSpeed = jumpSpeed;
            jumpVelocity = 0.f;
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
        sf::FloatRect getGlobalBounds() const override {
            return sf::Sprite::getGlobalBounds();
        }

        /**
         * @brief Override of the move function.
         * 
         * @param xOffset amount to move in the x direction.
         * @param yOffset amount to move in the y direction.
         */
        void move(float xOffset, float yOffset) override {
            setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
        }

        /**
         * @brief Override of the move function.
         * 
         * @param offset amount to move given a float 2D vector.
         */
        void move(sf::Vector2f offset) override {
            setPosition(getPosition().x + offset.x, getPosition().y + offset.y);
        }

        /**
         * @brief Get the Movement of an object
         * 
         * @return sf::Vector2f total movement of the object in that frame
         */
        sf::Vector2f getMovement() override {
            return totalMovement;
        }

        /**
         * @brief Update each frame, transforming the object based on time and keyboard input.
         * 
         * @param time time elapsed since the last frame
         */
        void update(float time) {
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
        bool checkCollision() {
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
        void checkWindowCollision() {
            if(getPosition().x < 0) {
                setPosition(0.f, getPosition().y);
            }
            if(getPosition().y < 0) {
                setPosition(getPosition().x, 0.f);
            }
            if(getPosition().x + getGlobalBounds().width > WINDOW_WIDTH) {
                setPosition(WINDOW_WIDTH - getGlobalBounds().width, getPosition().y);
            }
            if(getPosition().y + getGlobalBounds().height > WINDOW_HEIGHT) {
                setPosition(getPosition().x, WINDOW_HEIGHT - getGlobalBounds().height);
            }
        }

    private:
        float _speed; // Speed of the player
        float _gravity; // Amount that gravity affects the player
        float _jumpSpeed; // Power of the jump of the player
        float jumpVelocity; // Current jump velocity
        bool isJumping; // Is the character currently jumping?
        bool onPlatform; // Is the player on a platform?
        Collider* collidingPlatform; // Pointer to the collider of the platform the player is on
        sf::Vector2f totalMovement; // Total movement of the player
        sf::Texture texture; // Texture of the platform
};

/**
 * @brief Jayden Sansom, jksanso2
 * HW 1 Part 4
 * 
 * @return int exit code
 */
int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CSC 481 Game Engine Foundations HW 1 Part 4");
    // Get running desktop and set window to be positioned in the middle of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, 
                           desktop.height / 2 - window.getSize().y / 2));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    // Start clock
    sf::Clock clock;

    // Create floor
    Platform floor = Platform(0.f, 550.f, 800.f, 50.f);
    floor.setCollisionEnabled(true);
    // Create moving platform
    MovingPlatform movingPlatform = MovingPlatform(30.f, 400.f, 160.f, 600.f, 450.f, 180.f, 50.f, 1.f);
    movingPlatform.setCollisionEnabled(true);
    // Create Player
    Player player = Player("wolfie.png", 250.f, 430.f, 100.f, 50.f, 300.f, 0.3f, 0.3f);
    player.setCollisionEnabled(true);

    // While open loop
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        window.clear(sf::Color(255, 255, 255, 0));

        // Draw scene objects
        window.draw(floor);
        movingPlatform.update(elapsed.asSeconds());
        window.draw(movingPlatform);
        player.update(elapsed.asSeconds());
        window.draw(player);

        window.display();
    }

    return 0; // Return on end
}