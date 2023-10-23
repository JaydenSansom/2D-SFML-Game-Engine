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
    Platform* floor = new Platform(0.f, 550.f, 800.f, 50.f);
    floor->setCollisionEnabled(true);
    Object floorObj = {"floor", floor};
    objects.push_back(&floorObj);
    // Create moving platform
    MovingPlatform* movingPlatform = new MovingPlatform(30.f, 400.f, 160.f, 600.f, 450.f, 180.f, 50.f, 1.f);
    movingPlatform->setCollisionEnabled(true);
    Object mpObj = {"movingPlatform1", movingPlatform};
    objects.push_back(&mpObj);
    // Create spawn point
    SpawnPoint* spawnPoint = new SpawnPoint(250.f, 430.f);
    Object spObj = {"spawnPoint1", spawnPoint};
    objects.push_back(&spObj);
    // Create spawn point
    SpawnPoint* spawnPoint2 = new SpawnPoint(150.f, 430.f);
    Object spObj2 = {"spawnPoint2", spawnPoint2};
    objects.push_back(&spObj2);
    // Create death zone
    DeathZone* deathZone = new DeathZone();
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
        movingPlatform->update(elapsed);

        server.publishFunction(&objects);

        previousTime = currentTime;
    }

    return 0; // Return on end
}