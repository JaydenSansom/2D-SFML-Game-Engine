#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <zmq.hpp>

#include "GameObject.hpp"
#include "Platforms.hpp"
#include "Player.hpp"
#include "HiddenObjects.hpp"
#include "EventManager.hpp"
#include "Thread.hpp"
#include "Timeline.hpp"
#include "Client.hpp"

// Global window size
int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 400;

Timeline gameTime = Timeline(1);

std::vector<GameObject*> objects;
std::vector<sf::Drawable*> drawObjects;
std::vector<PlayerClient> playerClients;

void createMazePart(float x, float y, float width, float height) {
    // Create maze part
    Platform* maze = new Platform(x, y, width, height, sf::Color(0, 0, 0));
    maze->setCollisionEnabled(true);
    drawObjects.push_back(maze);
}

void initMaze() {
    // Create maze parts

    createMazePart(99.f, 0.f, 400.f, 13.f);
    createMazePart(99.f, 387.f, 400.f, 13.f);
    createMazePart(99.f, 30.f, 11.f, 370.f);
    createMazePart(490.f, 0.f, 10.f, 370.f);
    createMazePart(125.f, 30.f, 246.f, 8.f);
    createMazePart(108.f, 56.f, 54.f, 7.f);
    createMazePart(153.f, 62.f, 9.f, 29.f);
    createMazePart(179.f, 36.f, 9.f, 72.f);
    createMazePart(205.f, 36.f, 7.f, 30.f);
    createMazePart(309.f, 36.f, 8.f, 106.f);
    createMazePart(386.f, 11.f, 9.f, 122.f);
    createMazePart(412.f, 28.f, 9.f, 36.f);
    createMazePart(421.f, 56.f, 26.f, 8.f);
    createMazePart(438.f, 13.f, 9.f, 44.f);
    createMazePart(464.f, 28.f, 8.f, 137.f);
    createMazePart(438.f, 158.f, 26.f, 7.f);
    createMazePart(438.f, 165.f, 9.f, 77.f);
    createMazePart(335.f, 234.f, 103.f, 8.f);
    createMazePart(335.f, 242.f, 8.f, 26.f);
    createMazePart(257.f, 260.f, 78.f, 8.f);
    createMazePart(257.f, 234.f, 8.f, 26.f);
    createMazePart(231.f, 234.f, 26.f, 9.f);
    createMazePart(231.f, 243.f, 8.f, 50.f);
    createMazePart(239.f, 285.f, 29.f, 8.f);
    createMazePart(128.f, 79.f, 8.f, 61.f);
    createMazePart(136.f, 132.f, 52.f, 8.f);
    createMazePart(136.f, 107.f, 77.f, 8.f);
    createMazePart(205.f, 115.f, 8.f, 29.f);
    createMazePart(179.f, 140.f, 9.f, 76.f);
    createMazePart(128.f, 209.f, 51.f, 7.f);
    createMazePart(128.f, 181.f, 8.f, 28.f);
    createMazePart(110.f, 158.f, 69.f, 7.f);
    createMazePart(153.f, 165.f, 9.f, 28.f);
    createMazePart(110.f, 260.f, 26.f, 8.f);
    createMazePart(128.f, 268.f, 8.f, 28.f);
    createMazePart(205.f, 336.f, 9.f, 51.f);
    createMazePart(151.f, 336.f, 54.f, 8.f);
    createMazePart(128.f, 362.f, 62.f, 7.f);
    createMazePart(128.f, 311.f, 8.f, 51.f);
    createMazePart(136.f, 311.f, 132.f, 8.f);
    createMazePart(231.f, 318.f, 8.f, 54.f);
    createMazePart(239.f, 336.f, 45.f, 8.f);
    createMazePart(257.f, 359.f, 8.f, 29.f);
    createMazePart(283.f, 362.f, 37.f, 7.f);
    createMazePart(283.f, 268.f, 8.f, 95.f);
    createMazePart(291.f, 311.f, 29.f, 7.f);
    createMazePart(306.f, 336.f, 30.f, 8.f);
    createMazePart(306.f, 285.f, 63.f, 8.f);
    createMazePart(335.f, 293.f, 8.f, 94.f);
    createMazePart(361.f, 260.f, 8.f, 25.f);
    createMazePart(369.f, 260.f, 26.f, 9.f);
    createMazePart(387.f, 269.f, 8.f, 27.f);
    createMazePart(125.f, 234.f, 88.f, 8.f);
    createMazePart(153.f, 242.f, 9.f, 71.f);
    createMazePart(162.f, 285.f, 54.f, 8.f);
    createMazePart(205.f, 158.f, 8.f, 77.f);
    createMazePart(177.f, 260.f, 55.f, 9.f);
    createMazePart(213.f, 183.f, 29.f, 8.f);
    createMazePart(213.f, 158.f, 55.f, 7.f);
    createMazePart(231.f, 56.f, 8.f, 102.f);
    createMazePart(203.f, 81.f, 29.f, 8.f);
    createMazePart(239.f, 56.f, 29.f, 7.f);
    createMazePart(255.f, 81.f, 29.f, 8.f);
    createMazePart(239.f, 107.f, 26.f, 9.f);
    createMazePart(257.f, 116.f, 8.f, 24.f);
    createMazePart(265.f, 132.f, 26.f, 8.f);
    createMazePart(283.f, 139.f, 8.f, 54.f);
    createMazePart(229.f, 209.f, 62.f, 8.f);
    createMazePart(257.f, 181.f, 8.f, 29.f);
    createMazePart(283.f, 216.f, 8.f, 26.f);
    createMazePart(290.f, 234.f, 27.f, 8.f);
    createMazePart(309.f, 164.f, 8.f, 71.f);
    createMazePart(291.f, 158.f, 52.f, 7.f);
    createMazePart(335.f, 56.f, 8.f, 102.f);
    createMazePart(343.f, 56.f, 43.f, 7.f);
    createMazePart(283.f, 107.f, 26.f, 8.f);
    createMazePart(283.f, 53.f, 8.f, 54.f);
    createMazePart(358.f, 81.f, 29.f, 8.f);
    createMazePart(342.f, 107.f, 29.f, 8.f);
    createMazePart(358.f, 132.f, 63.f, 8.f);
    createMazePart(412.f, 140.f, 9.f, 25.f);
    createMazePart(384.f, 158.f, 28.f, 7.f);
    createMazePart(332.f, 183.f, 106.f, 8.f);
    createMazePart(361.f, 155.f, 8.f, 28.f);
    createMazePart(412.f, 81.f, 52.f, 8.f);
    createMazePart(412.f, 89.f, 9.f, 26.f);
    createMazePart(421.f, 107.f, 26.f, 8.f);
    createMazePart(438.f, 115.f, 9.f, 28.f);
    createMazePart(317.f, 209.f, 106.f, 7.f);
    createMazePart(412.f, 242.f, 9.f, 70.f);
    createMazePart(436.f, 260.f, 29.f, 8.);
    createMazePart(361.f, 311.f, 8.f, 61.f);
    createMazePart(369.f, 336.f, 28.f, 8.f);
    createMazePart(369.f, 311.f, 70.f, 7.f);
    createMazePart(438.f, 283.f, 9.f, 63.f);
    createMazePart(412.f, 334.f, 9.f, 29.f);
    createMazePart(387.f, 362.f, 8.f, 25.f);
    createMazePart(395.f, 362.f, 77.f, 7.f);
    createMazePart(464.f, 181.f, 8.f, 182.f);
}

/**
 * @brief Jayden Sansom, jksanso2
 * HW 5 Part EC
 * 
 * @return int exit code
 */
int main() {

    // Mutex to handle locking, condition variable to handle notifications between threads
    std::mutex m;
    std::condition_variable cv;

    // Keys pressed to be passed to the thread update
    KeysPressed keysPressed;

    EventManager eventManager;

    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CSC 481 Game Engine Foundations HW 5 Extra Credit");
    // Get running desktop and set window to be positioned in the middle of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, 
                           desktop.height / 2 - window.getSize().y / 2));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    // Create Player
    Player* player = new Player(WINDOW_WIDTH, WINDOW_HEIGHT, "WolfieMaze.png", 98.f, 15.f, 100.f, 50.f, 300.f, 1.f, 1.f);
    player->setCollisionEnabled(true);
    drawObjects.push_back(player);

    // Make Win area
    Platform* winArea = new Platform(499.f, 352.f, 21.f, 48.f);

    initMaze();

    sf::Texture wonTexture;
    sf::Sprite winUI;
    winUI.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 77.f, 150.f));
    // Load and set texture
    if (wonTexture.loadFromFile("WinTextUI.png")) {
        winUI.setTexture(wonTexture);
    }

    PlayerClient playerClient = {"One", player, true};
    Client client(&playerClient, &playerClients);

    client.requesterFunction(&playerClient);

    Thread subscriberThread = Thread(0, nullptr, &m, &cv, [&]() {
        client.subscriberFunction(&objects, &eventManager);
    });
    std::thread runReplier(run_wrapper, &subscriberThread);

    // Set up time variables
    float previousTime = gameTime.getTime();
    float currentTime, elapsed;

    bool winShowUI = false;

    // While open loop
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                playerClient.isActive = false;
                client.requesterFunction(&playerClient);
            }
        }

        if(gameTime.isPaused()) {
            elapsed = 0.f; // It just works "¯\_(ツ)_/¯ "
        }
        else {
            currentTime = gameTime.getTime();
            elapsed = (currentTime - previousTime) / 1000.f;
        }

        if(window.hasFocus()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Slash) && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                player->setPosition(98.f, 15.f);
                winShowUI = false;
            }
            if(!winShowUI) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    keysPressed.Left = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    keysPressed.Right = true;
                }
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
                    keysPressed.Up = true;
                }
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
                    keysPressed.Down = true;
                }
            }
        }

        eventManager.registerEvent(new EventInputHandler(&eventManager, new EventInput(player, &keysPressed, elapsed)));

        eventManager.raise();

        if(winArea->getGlobalBounds().intersects(player->getGlobalBounds())) {
            winShowUI = true;
        }

        // Keep within screen
        if(player->getPosition().x < 0.f) {
            player->setPosition(0.f, player->getPosition().y);
        }
        if(player->getPosition().x > WINDOW_WIDTH - 14.f) {
            player->setPosition(WINDOW_WIDTH - 14.f, player->getPosition().y);
        }
        if(player->getPosition().y < 0.f) {
            player->setPosition(player->getPosition().x, 0.f);
        }
        if(player->getPosition().y > WINDOW_HEIGHT - 12.f) {
            player->setPosition(player->getPosition().x, WINDOW_HEIGHT - 12.f);
        }

        client.requesterFunction(&playerClient);

        window.clear(sf::Color(255, 255, 255, 0));

        eventManager.raise();

        // Draw scene objects
        for(sf::Drawable* object : drawObjects) {
            window.draw(*object);
        }
        for(PlayerClient playerClient : playerClients) {
            if(playerClient.isActive) {
                Player* currentPlayer = playerClient.player;
                window.draw(*currentPlayer);
            }
        }
        if(winShowUI) {
            window.draw(winUI);
        }
        window.display();

        previousTime = currentTime;

        keysPressed.Left = false;
        keysPressed.Right = false;
        keysPressed.Up = false;
        keysPressed.Down = false;
    }

    return 0; // Return on end
}