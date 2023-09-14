#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

/**
 * @brief Class for a static platform object
 */
class Platform : public sf::RectangleShape {
    public:
        Platform() {
            setPosition(0.f, 0.f);
            setSize(sf::Vector2f(50.f, 50.f));
            setFillColor(sf::Color(0, 0, 0));
        }

        Platform(float x, float y, float width, float height) {
            setPosition(x, y);
            setSize(sf::Vector2f(width, height));
            setFillColor(sf::Color(0, 0, 0));
        }

        Platform(float x, float y, float width, float height, const std::string& texturePath) {
            setPosition(x, y);
            setSize(sf::Vector2f(width, height));
            
            // Load and set texture
            if (texture.loadFromFile(texturePath)) {
                setTexture(&texture);
            }
        }
    private:
        sf::Texture texture;
};

/**
 * @brief Class for a moveable platform object
 */
class MovingPlatform : public sf::RectangleShape {
    public:
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
        }

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
        }

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
            
            // Load and set texture
            if (texture.loadFromFile(texturePath)) {
                setTexture(&texture);
            }
        }

        void update(float time) {
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
                    setPosition(_destX, _destY);
                    paused = true;
                    pauseTimer = _pauseLength;
                }
                else {
                    move(xOffset, yOffset);
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
                    setPosition(_x, _y);
                    paused = true;
                    pauseTimer = _pauseLength;
                }
                else {
                    move(xOffset, yOffset);
                }
            }
        }

    private:
        float _speed;
        float _x;
        float _y;
        float _destX;
        float _destY;
        bool movingForward;
        bool paused;
        float pauseTimer;
        float _pauseLength;
        sf::Texture texture;
};

/**
 * @brief Class for a player character
 */
class Player : public sf::Sprite {
    public:
        Player(const std::string& texturePath) {
            setPosition(0.f, 0.f);
            _speed = 50.f;
            _gravity = 9.81f;
            _jumpSpeed = 10.f;
            isJumping = false;
            totalMovement = sf::Vector2f(0.f, 0.f);
            
            // Load and set texture
            if (texture.loadFromFile(texturePath)) {
                setTexture(texture);
            }
        }

        Player(const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed) {
            setPosition(x, y);
            _speed = speed;
            _gravity = gravity;
            _jumpSpeed = jumpSpeed;
            isJumping = false;
            totalMovement = sf::Vector2f(0.f, 0.f);
            
            // Load and set texture
            if (texture.loadFromFile(texturePath)) {
                setTexture(texture);
            }
        }

        Player(const std::string& texturePath, float x, float y, float speed, float gravity, float jumpSpeed, float scaleX, float scaleY) {
            setPosition(x, y);
            setScale(sf::Vector2f(scaleX, scaleY));
            _speed = speed;
            _gravity = gravity;
            _jumpSpeed = jumpSpeed;
            isJumping = false;
            totalMovement = sf::Vector2f(0.f, 0.f);
            
            // Load and set texture
            if (texture.loadFromFile(texturePath)) {
                setTexture(texture);
            }
        }

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
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !isJumping) {
                // Space or W key is pressed: the player jumps
                isJumping = true;
                jumpVelocity = -_jumpSpeed;
            }

            if (isJumping) {
                totalMovement.y = jumpVelocity * time;
                jumpVelocity += _gravity * sqrt(time);

                move(totalMovement);

                if (getPosition().y + getGlobalBounds().height >= 550.f) {
                    setPosition(getPosition().x, 550.f - getGlobalBounds().height);
                    isJumping = false;
                    jumpVelocity = 0.f;
                }
            }
            else { 
                move(totalMovement);
            }

            
        }

    private:
        float _speed;
        float _gravity;
        float _jumpSpeed;
        float jumpVelocity;
        bool isJumping;
        sf::Vector2f totalMovement;
        sf::Texture texture;
};

/**
 * @brief Jayden Sansom, jksanso2
 * HW 1 Part 3
 * 
 * @return int exit code
 */
int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSC 481 Game Engine Foundations HW 1 Part 3");
    // Get running desktop and set window to be positioned in the middle of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, 
                           desktop.height / 2 - window.getSize().y / 2));
    window.setVerticalSyncEnabled(false);

    // Start clock
    sf::Clock clock;

    // Create floor
    Platform floor = Platform(0.f, 550.f, 800.f, 50.f);
    // Create moving platform
    MovingPlatform movingPlatform = MovingPlatform(30.f, 400.f, 160.f, 600.f, 450.f, 180.f, 50.f, 1.f);
    // Create Player
    Player player = Player("wolfie.png", 250.f, 430.f, 100.f, 10.f, 200.f, 0.3f, 0.3f);

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