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
#include "Server.hpp"
#include "HiddenObjects.hpp"

// Global window size
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

Timeline gameTime = Timeline(1);

std::vector<Object*> objects;

/**
 * @brief Jayden Sansom, jksanso2
 * HW 3 Part 1
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

// Create floor
    Platform* floor = new Platform(0.f, 550.f, 700.f, 50.f, sf::Color(178, 172, 136));
    floor->setCollisionEnabled(true);
    Object floorObj = {"floor", floor};
    objects.push_back(&floorObj);

    // Create moving platform
    MovingPlatform* movingPlatform1 = new MovingPlatform(30.f, 250.f, 200.f, 400.f, 400.f, 180.f, 50.f, 1.f, sf::Color(255, 84, 155));
    movingPlatform1->setCollisionEnabled(true);
    Object mpObj1 = {"movingPlatform1", movingPlatform1};
    objects.push_back(&mpObj1);

    // Create moving platform
    MovingPlatform* movingPlatform2 = new MovingPlatform(30.f, 0.f, 200.f, -350.f, 250.f, 180.f, 50.f, 3.f, sf::Color(0, 133, 204));
    movingPlatform2->setCollisionEnabled(true);
    Object mpObj2 = {"movingPlatform2", movingPlatform2};
    objects.push_back(&mpObj2);

    // Create platform one
    Platform* platform1 = new Platform(-650.f, 250.f, 200.f, 50.f, sf::Color(255, 219, 61));
    platform1->setCollisionEnabled(true);
    Object platform1Obj = {"platform1", platform1};
    objects.push_back(&platform1Obj);

    // Create spawn point
    SpawnPoint* spawnPoint = new SpawnPoint(250.f, 430.f);
    Object spObj = {"spawnPoint1", spawnPoint};
    objects.push_back(&spObj);

    // Create another spawn point
    SpawnPoint* spawnPoint2 = new SpawnPoint(150.f, 430.f);
    Object spObj2 = {"spawnPoint2", spawnPoint2};
    objects.push_back(&spObj2);

    // Create death zone
    DeathZone* deathZone = new DeathZone(-10000.f, 595.f, 20000.f, 5.f);
    Object dzObj = {"deathZone", deathZone};
    objects.push_back(&dzObj);

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

        // Update all shared objects that can be updated
        movingPlatform1->update(elapsed);
        movingPlatform2->update(elapsed);

        server.publishFunction(&objects);

        previousTime = currentTime;
    }

    return 0; // Return on end
}