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
int WINDOW_WIDTH = 300;
int WINDOW_HEIGHT = 400;

Timeline gameTime = Timeline(1);

std::vector<GameObject*> objects;
std::vector<sf::Drawable*> drawObjects;
std::vector<PlayerClient> playerClients;
std::vector<SpawnPoint*> spawnPoints;
std::vector<sf::FloatRect> deathZoneBounds;

/**
 * @brief Get the Random Spawn Point object from the spawnPoints vector
 * 
 * @return sf::Vector2f spawn point location
 */
sf::Vector2f getRandomSpawnPoint() {
    srand(time(NULL));
    int randomIndex = rand() % spawnPoints.size();
    return spawnPoints.at(randomIndex)->getSpawnPointLocation();
}

/**
 * @brief Jayden Sansom, jksanso2
 * HW 5 Part 2
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CSC 481 Game Engine Foundations HW 5 Part 2");
    // Get running desktop and set window to be positioned in the middle of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, 
                           desktop.height / 2 - window.getSize().y / 2));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    // Create sidebar left
    Platform* sidebar1 = new Platform(0.f, 0.f, 15.f, WINDOW_HEIGHT, sf::Color(0, 0, 0, 0));
    sidebar1->setCollisionEnabled(true);
    GameObject sidebar1Obj = GameObject("sidebar1", sidebar1);
    objects.push_back(&sidebar1Obj);
    drawObjects.push_back(sidebar1);

    // Create sidebar right
    Platform* sidebar2 = new Platform(WINDOW_WIDTH - 15.f, 0.f, 15.f, WINDOW_HEIGHT, sf::Color(0, 0, 0, 0));
    sidebar2->setCollisionEnabled(true);
    GameObject sidebar2Obj = GameObject("sidebar2", sidebar2);
    objects.push_back(&sidebar2Obj);
    drawObjects.push_back(sidebar2);

    // Create Player
    Player* player = new Player(WINDOW_WIDTH, WINDOW_HEIGHT, "player.png", WINDOW_WIDTH / 2, WINDOW_HEIGHT - 25.f, 100.f, 50.f, 300.f, 0.5f, 0.5f);
    player->setCollisionEnabled(true);
    drawObjects.push_back(player);

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                keysPressed.Left = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                keysPressed.Right = true;
            }
        }

        eventManager.registerEvent(new EventInputHandler(&eventManager, new EventInput(player, &keysPressed, elapsed)));

        eventManager.raise();

        client.requesterFunction(&playerClient);

        window.clear(sf::Color(0, 0, 0));

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
        window.display();

        previousTime = currentTime;

        keysPressed.Left = false;
        keysPressed.Right = false;
    }

    return 0; // Return on end
}