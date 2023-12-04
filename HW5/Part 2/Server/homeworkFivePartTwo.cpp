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
#include "Server.hpp"

// Global window size
int WINDOW_WIDTH = 300;
int WINDOW_HEIGHT = 400;

Timeline gameTime = Timeline(1);

std::vector<GameObject*> objects;

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

    Server server = Server();
    Thread reciverThread = Thread(0, nullptr, &m, &cv, [&]() {
        server.replierFunction();
    });
    std::thread runReplier(run_wrapper, &reciverThread);

    // Create sidebar left
    Platform* sidebar1 = new Platform(0.f, 0.f, 15.f, WINDOW_HEIGHT, sf::Color(0, 0, 0, 0));
    sidebar1->setCollisionEnabled(true);
    GameObject sidebar1Obj = GameObject("sidebar1", sidebar1);
    objects.push_back(&sidebar1Obj);

    // Create sidebar right
    Platform* sidebar2 = new Platform(WINDOW_WIDTH - 15.f, 0.f, 15.f, WINDOW_HEIGHT, sf::Color(0, 0, 0, 0));
    sidebar2->setCollisionEnabled(true);
    GameObject sidebar2Obj = GameObject("sidebar2", sidebar2);
    objects.push_back(&sidebar2Obj);

    // Set up time variables
    float previousTime = gameTime.getTime();
    float currentTime, elapsed;

    while(true) {
        if(gameTime.isPaused()) {
            elapsed = 0.f; // It just works "¯\_(ツ)_/¯ "
        }
        else {
            currentTime = gameTime.getTime();
            elapsed = (currentTime - previousTime) / 1000.f;
        }

        server.publishFunction(&objects);

        previousTime = currentTime;
    }

    return 0; // Return on end
}