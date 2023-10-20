#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <zmq.hpp>

#include "Collider.hpp"
#include "Platforms.hpp"
#include "Player.hpp"
#include "Thread.hpp"
#include "Timeline.hpp"
#include "Client.hpp"

// Global window size
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

Timeline gameTime = Timeline(1);

std::vector<Object*> objects;
std::vector<sf::Drawable*> drawObjects;
std::vector<PlayerClient> playerClients;

/**
 * @brief Jayden Sansom, jksanso2
 * HW 2 Part 4
 * 
 * @return int exit code
 */
int main() {

        // Mutex to handle locking, condition variable to handle notifications between threads
    std::mutex m;
    std::condition_variable cv;

    // Keys pressed to be passed to the thread update
    KeysPressed keysPressed;

    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CSC 481 Game Engine Foundations HW 2 Part 2");
    // Get running desktop and set window to be positioned in the middle of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, 
                           desktop.height / 2 - window.getSize().y / 2));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    // Create floor
    Platform* floor = new Platform(0.f, 550.f, 800.f, 50.f);
    floor->setCollisionEnabled(true);
    Object floorObj = {"floor", floor};
    objects.push_back(&floorObj);
    drawObjects.push_back(floor);
    // Create moving platform
    MovingPlatform* movingPlatform = new MovingPlatform(30.f, 400.f, 160.f, 600.f, 450.f, 180.f, 50.f, 1.f);
    movingPlatform->setCollisionEnabled(true);
    Object mpObj = {"movingPlatform1", movingPlatform};
    objects.push_back(&mpObj);
    drawObjects.push_back(movingPlatform);
    // Create Player
    Player* player = new Player(WINDOW_WIDTH, WINDOW_HEIGHT, "wolfie.png", 250.f, 430.f, 100.f, 50.f, 300.f, 0.3f, 0.3f);
    player->setCollisionEnabled(true);
    drawObjects.push_back(player);

    PlayerClient playerClient = {"Two", player};
    Client client(&playerClient, &playerClients);

    client.requesterFunction(&playerClient);

    Thread subscriberThread = Thread(0, nullptr, &m, &cv, [&]() {
        client.subscriberFunction(&objects);
    });
    std::thread runReplier(run_wrapper, &subscriberThread);

    // Set up time variables
    float previousTime = gameTime.getTime();
    float currentTime, elapsed;

    bool pauseKeyPressedOnce = false, lowerTicKeyPressedOnce = false, raiseTicKeyPressedOnce = false;

    // While open loop
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                keysPressed.Left = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                keysPressed.Right = true;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
                keysPressed.Up = true;
            }
        }

        if(gameTime.isPaused()) {
            elapsed = 0.f; // It just works "¯\_(ツ)_/¯ "
        }
        else {
            currentTime = gameTime.getTime();
            elapsed = (currentTime - previousTime) / 1000.f;
        }

        player->update(elapsed, keysPressed);
        client.requesterFunction(&playerClient);

        window.clear(sf::Color(255, 255, 255, 0));

        // Draw scene objects
        for(sf::Drawable* object : drawObjects) {
            window.draw(*object);
        }
        for(PlayerClient playerClient : playerClients) {
            Player* currentPlayer = playerClient.player;
            window.draw(*currentPlayer);
        }

        window.display();

        previousTime = currentTime;

        keysPressed.Left = false;
        keysPressed.Right = false;
        keysPressed.Up = false;
    }

    return 0; // Return on end
}