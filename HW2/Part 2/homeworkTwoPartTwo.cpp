#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <X11/Xlib.h>

#include "Collider.hpp"
#include "Platforms.hpp"
#include "Player.hpp"
#include "Thread.hpp"

// Global window size
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

/**
 * @brief Jayden Sansom, jksanso2
 * HW 2 Part 2
 * 
 * @return int exit code
 */
int main() {

    // Mutex to handle locking, condition variable to handle notifications between threads
    XInitThreads();
    std::mutex m;
    std::condition_variable cv;

    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CSC 481 Game Engine Foundations HW 2 Part 2");
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
    Player player = Player(WINDOW_WIDTH, WINDOW_HEIGHT, "wolfie.png", 250.f, 430.f, 100.f, 50.f, 300.f, 0.3f, 0.3f);
    player.setCollisionEnabled(true);

    sf::Time elapsed = clock.restart();

    Thread playerThread = Thread(0, nullptr, &m, &cv, [&]() {
        player.update(elapsed.asSeconds());
    });
    Thread platformThread = Thread(0, &playerThread, &m, &cv, [&]() {
        movingPlatform.update(elapsed.asSeconds());
    });

    // While open loop
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        elapsed = clock.restart();

        std::thread runPlayerUpdate(run_wrapper, &playerThread);
        std::thread runPlatformUpdate(run_wrapper, &platformThread);

        window.clear(sf::Color(255, 255, 255, 0));

        // Draw scene objects
        runPlayerUpdate.join();
        runPlatformUpdate.join();

        window.draw(floor);
        window.draw(movingPlatform);
        window.draw(player);

        window.display();
    }

    return 0; // Return on end
}