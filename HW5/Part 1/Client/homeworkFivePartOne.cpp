#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <v8.h>
#include <libplatform/libplatform.h>
#include "v8helpers.h"
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
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

Timeline gameTime = Timeline(1);

std::vector<GameObject*> objects;
std::vector<sf::Drawable*> drawObjects;
std::vector<PlayerClient> playerClients;
std::vector<SpawnPoint*> spawnPoints;
std::vector<sf::FloatRect> deathZoneBounds;
bool deathZonesAreEnabled = true;

ScriptManager* scriptManager = nullptr;

void ScriptedEnableDisableDeathZone(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    std::cout << "ScriptedEnableDisableDeathZone called" << std::endl;
	deathZonesAreEnabled = !deathZonesAreEnabled;
}

void usage()
{
	// Usage
	std::cout << "\n"
		<< "Commands:\n"
        << "\t/d: Disable/Enable Death Zones\n"
        << "\t/e: Handle all events\n"
		<< "\t/k: Kill the player\n"
        << "\t/;: Print Command List\n"
		<< std::endl;

}

void handleCommand(char command) {
    switch (command) {
        case 'd':
            std::cout << "d given" << std::endl;
            scriptManager->runOne("disable_death", false);
            break;
        case 'e':
            std::cout << "E given" << std::endl;
            scriptManager->runOne("handle_events", false);
            break;
        case 'k':
            std::cout << "K given" << std::endl;
            scriptManager->runOne("kill_player", false);
            break;
        case ';':
            std::cout << "; given" << std::endl;
            usage();
            break;
        default:
            std::cout << "Unknown command: " << command << std::endl;
            break;
    }
}

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
 * HW 5 Part 1
 * 
 * @return int exit code
 */
int main() {

    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.release());
    v8::V8::InitializeICU();
    v8::V8::Initialize();
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate *isolate = v8::Isolate::New(create_params);

    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope handle_scope(isolate);

    // Best practice to isntall all global functions in the context ahead of time.
    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);

    global->Set(isolate, "print", v8::FunctionTemplate::New(isolate, v8helpers::Print));
    global->Set(isolate, "gethandle", v8::FunctionTemplate::New(isolate, ScriptManager::getHandleFromScript));
    global->Set(v8::String::NewFromUtf8(isolate, "enabledisabledeathzone"),
            v8::FunctionTemplate::New(isolate, ScriptedEnableDisableDeathZone));
    global->Set(isolate, "enabledisabledeathzone", v8::FunctionTemplate::New(isolate, ScriptedEnableDisableDeathZone));

    v8::Local<v8::Context> default_context =  v8::Context::New(isolate, NULL, global);
	v8::Context::Scope default_context_scope(default_context); // enter the context

    scriptManager = new ScriptManager(isolate, default_context);

    // Without parameters, these calls are made to all contexts
    scriptManager->addScript("disable_death", "scripts/disable_death.js");
    scriptManager->addScript("handle_events", "scripts/handle_events.js");
    scriptManager->addScript("kill_player", "scripts/kill_player.js");

    usage();

    // Mutex to handle locking, condition variable to handle notifications between threads
    std::mutex m;
    std::condition_variable cv;

    // Keys pressed to be passed to the thread update
    KeysPressed keysPressed;
    bool isSprinting = false;

    EventManager eventManager;

    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CSC 481 Game Engine Foundations HW 5 Part 1");
    // Get running desktop and set window to be positioned in the middle of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, 
                           desktop.height / 2 - window.getSize().y / 2));
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    sf::View camera = sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(camera);

    // Create Left Scroll Zone
    SideScrollArea leftScrollArea = SideScrollArea(0.f, 0.f, 300.f, WINDOW_HEIGHT);

    // Create Right Scroll Zone
    SideScrollArea rightScrollArea = SideScrollArea(WINDOW_WIDTH - 300.f, 0.f, 300.f, WINDOW_HEIGHT);

    // Create floor
    Platform* floor = new Platform(0.f, 550.f, 700.f, 50.f, sf::Color(178, 172, 136));
    floor->setCollisionEnabled(true);
    GameObject floorObj = GameObject("floor", floor);
    objects.push_back(&floorObj);
    drawObjects.push_back(floor);

    // Create moving platform
    MovingPlatform* movingPlatform1 = new MovingPlatform(30.f, 250.f, 200.f, 400.f, 400.f, 180.f, 50.f, 1.f, sf::Color(255, 84, 155));
    movingPlatform1->setCollisionEnabled(true);
    GameObject mpObj1 = GameObject("movingPlatform1", movingPlatform1);
    objects.push_back(&mpObj1);
    drawObjects.push_back(movingPlatform1);

    // Create moving platform
    MovingPlatform* movingPlatform2 = new MovingPlatform(30.f, 0.f, 200.f, -350.f, 250.f, 180.f, 50.f, 3.f, sf::Color(0, 133, 204));
    movingPlatform2->setCollisionEnabled(true);
    GameObject mpObj2 = GameObject("movingPlatform2", movingPlatform2);
    objects.push_back(&mpObj2);
    drawObjects.push_back(movingPlatform2);

    // Create platform one
    Platform* platform1 = new Platform(-650.f, 250.f, 200.f, 50.f, sf::Color(255, 219, 61));
    platform1->setCollisionEnabled(true);
    GameObject platform1Obj = GameObject("platform1", platform1);
    objects.push_back(&platform1Obj);
    drawObjects.push_back(platform1);

    // Create spawn point
    SpawnPoint* spawnPoint = new SpawnPoint(250.f, 430.f);
    GameObject spObj = GameObject("spawnPoint1", spawnPoint);
    objects.push_back(&spObj);
    spawnPoints.push_back(spawnPoint);

    // Create another spawn point
    SpawnPoint* spawnPoint2 = new SpawnPoint(150.f, 430.f);
    GameObject spObj2 = GameObject("spawnPoint2", spawnPoint2);
    objects.push_back(&spObj2);
    spawnPoints.push_back(spawnPoint2);

    // Create death zone
    DeathZone* deathZone = new DeathZone(-10000.f, 595.f, 20000.f, 5.f);
    GameObject dzObj = GameObject("deathZone", deathZone);
    objects.push_back(&dzObj);
    deathZoneBounds.push_back(deathZone->getGlobalBounds());

    // Create Player
    sf::Vector2f spawnInit = getRandomSpawnPoint();
    Player* player = new Player(WINDOW_WIDTH, WINDOW_HEIGHT, "wolfie.png", spawnInit.x, spawnInit.y, 100.f, 50.f, 300.f, 0.3f, 0.3f);
    player->setCollisionEnabled(true);
    drawObjects.push_back(player);

    PlayerClient playerClient = {"One", player, true};
    Client client(&playerClient, &playerClients);

    client.requesterFunction(&playerClient);

    Thread subscriberThread = Thread(0, nullptr, &m, &cv, [&]() {
        client.subscriberFunction(&objects, &eventManager);
    });
    std::thread runReplier(run_wrapper, &subscriberThread);

    float waitBeforeNextCommand = 0.f;

    // Set up time variables
    float previousTime = gameTime.getTime();
    float currentTime, elapsed;

    // While open loop
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isolate->Dispose();
                v8::V8::Dispose();
                v8::V8::ShutdownPlatform();
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

        if(waitBeforeNextCommand > 0.f) {
            waitBeforeNextCommand -= elapsed;
        }

        if(window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash) && waitBeforeNextCommand <= 0.f) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    waitBeforeNextCommand = 1.f;
                    handleCommand('d');
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                    waitBeforeNextCommand = 1.f;
                    handleCommand('e');
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    waitBeforeNextCommand = 1.f;
                    handleCommand('k');
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)) {
                    waitBeforeNextCommand = 1.f;
                    handleCommand(';');
                }
            }
            else {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
                    isSprinting = true;
                }
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
        }

        eventManager.registerEvent(new EventInputHandler(&eventManager, new EventInput(player, &keysPressed, elapsed, isSprinting)));

        eventManager.raise();

        // If the player collides with a death zone
        if(deathZonesAreEnabled) {
            if(player->checkCollision(deathZoneBounds)) {
                eventManager.registerEvent(new EventDeathHandler(&eventManager, new EventDeath(player, &spawnPoints, &window, &camera, &leftScrollArea, &rightScrollArea)));
            }   
        }
        if(player->checkCollision(leftScrollArea.getGlobalBounds())) {
            sf::Vector2f playerMovement = player->getMovement();
            if(playerMovement.x < 0.f) {
                camera.move(playerMovement.x, 0.f);
                leftScrollArea.move(playerMovement.x, 0.f);
                rightScrollArea.move(playerMovement.x, 0.f);
            }
        }
        if(player->checkCollision(rightScrollArea.getGlobalBounds())) {
            sf::Vector2f playerMovement = player->getMovement();
            if(playerMovement.x > 0.f) {
                camera.move(playerMovement.x, 0.f);
                leftScrollArea.move(playerMovement.x, 0.f);
                rightScrollArea.move(playerMovement.x, 0.f);
            }
        }

        eventManager.raise();

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
        window.setView(camera);
        window.display();

        previousTime = currentTime;

        keysPressed.Left = false;
        keysPressed.Right = false;
        keysPressed.Up = false;
        isSprinting = false;
    }

    return 0; // Return on end
}