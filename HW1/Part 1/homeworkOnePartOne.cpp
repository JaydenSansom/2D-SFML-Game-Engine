#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/**
 * @brief Jayden Sansom, jksanso2
 * HW 1 Part 1
 * 
 * @return int exit code
 */
int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "CSC 481 Game Engine Foundations HW 1 Part 1");
    // Get running desktop and set window to be positioned in the middle of the screen
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, 
                           desktop.height / 2 - window.getSize().y / 2));

    // While open loop
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255, 0));
        window.display();
    }

    return 0; // Return on end
}