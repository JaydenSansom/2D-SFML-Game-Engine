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
#include "Projectiles.hpp"
#include "Enemy.hpp"

// Global window size
int WINDOW_WIDTH = 300;
int WINDOW_HEIGHT = 400;

Timeline gameTime = Timeline(1);

std::vector<GameObject*> objects;
std::vector<sf::Drawable*> drawObjects;
std::vector<PlayerClient> playerClients;
std::vector<SpawnPoint*> spawnPoints;
std::vector<sf::FloatRect> deathZoneBounds;
std::vector<PlayerProjectile*> playerProjectiles;
std::vector<PlayerProjectile*> projectilesToRemove;
std::vector<EnemyProjectile*> enemyProjectiles;
std::vector<EnemyProjectile*> enemyProjectilesToRemove;
std::vector<Enemy*> enemies;
std::vector<Enemy*> col1;
std::vector<Enemy*> col2;
std::vector<Enemy*> col3;
std::vector<Enemy*> col4;
std::vector<Enemy*> col5;
std::vector<Enemy*> col6;
std::vector<Enemy*> col7;
std::vector<Enemy*> col8;
std::vector<int> currentColumns{1, 2, 3, 4, 5, 6, 7, 8};

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

void initializeEnemies() {
    // Row 1
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-
    Enemy* enemy1_1 = new Enemy(26.f, 141.f, 1, "Enemy1.png");
    enemy1_1->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_1);
    enemies.push_back(enemy1_1);
    col1.push_back(enemy1_1);

    Enemy* enemy1_2 = new Enemy(59.f, 141.f, 2, "Enemy1.png");
    enemy1_2->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_2);
    enemies.push_back(enemy1_2);
    col2.push_back(enemy1_2);

    Enemy* enemy1_3 = new Enemy(91.f, 141.f, 3, "Enemy1.png");
    enemy1_3->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_3);
    enemies.push_back(enemy1_3);
    col3.push_back(enemy1_3);

    Enemy* enemy1_4 = new Enemy(123.f, 141.f, 4, "Enemy1.png");
    enemy1_4->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_4);
    enemies.push_back(enemy1_4);
    col4.push_back(enemy1_4);

    Enemy* enemy1_5 = new Enemy(155.f, 141.f, 5, "Enemy1.png");
    enemy1_5->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_5);
    enemies.push_back(enemy1_5);
    col5.push_back(enemy1_5);

    Enemy* enemy1_6 = new Enemy(187.f, 141.f, 6, "Enemy1.png");
    enemy1_6->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_6);
    enemies.push_back(enemy1_6);
    col6.push_back(enemy1_6);

    Enemy* enemy1_7 = new Enemy(220.f, 141.f, 7, "Enemy1.png");
    enemy1_7->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_7);
    enemies.push_back(enemy1_7);
    col7.push_back(enemy1_7);

    Enemy* enemy1_8 = new Enemy(253.f, 141.f, 8, "Enemy1.png");
    enemy1_8->setCollisionEnabled(true);
    drawObjects.push_back(enemy1_8);
    enemies.push_back(enemy1_8);
    col8.push_back(enemy1_8);

    // Row 2
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-
    Enemy* enemy2_1 = new Enemy(26.f, 115.f, 1, "Enemy1.png");
    enemy2_1->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_1);
    enemies.push_back(enemy2_1);
    col1.push_back(enemy2_1);

    Enemy* enemy2_2 = new Enemy(59.f, 115.f, 2, "Enemy1.png");
    enemy2_2->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_2);
    enemies.push_back(enemy2_2);
    col2.push_back(enemy2_2);

    Enemy* enemy2_3 = new Enemy(91.f, 115.f, 3, "Enemy1.png");
    enemy2_3->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_3);
    enemies.push_back(enemy2_3);
    col3.push_back(enemy2_3);

    Enemy* enemy2_4 = new Enemy(123.f, 115.f, 4, "Enemy1.png");
    enemy2_4->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_4);
    enemies.push_back(enemy2_4);
    col4.push_back(enemy2_4);

    Enemy* enemy2_5 = new Enemy(155.f, 115.f, 5, "Enemy1.png");
    enemy2_5->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_5);
    enemies.push_back(enemy2_5);
    col5.push_back(enemy2_5);

    Enemy* enemy2_6 = new Enemy(187.f, 115.f, 6, "Enemy1.png");
    enemy2_6->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_6);
    enemies.push_back(enemy2_6);
    col6.push_back(enemy2_6);

    Enemy* enemy2_7 = new Enemy(220.f, 115.f, 7, "Enemy1.png");
    enemy2_7->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_7);
    enemies.push_back(enemy2_7);
    col7.push_back(enemy2_7);

    Enemy* enemy2_8 = new Enemy(253.f, 115.f, 8, "Enemy1.png");
    enemy2_8->setCollisionEnabled(true);
    drawObjects.push_back(enemy2_8);
    enemies.push_back(enemy2_8);
    col8.push_back(enemy2_8);

    // Row 3
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-
    Enemy* enemy3_1 = new Enemy(26.f, 86.f, 1, "Enemy2.png");
    enemy3_1->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_1);
    enemies.push_back(enemy3_1);
    col1.push_back(enemy3_1);

    Enemy* enemy3_2 = new Enemy(59.f, 86.f, 2, "Enemy2.png");
    enemy3_2->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_2);
    enemies.push_back(enemy3_2);
    col2.push_back(enemy3_2);

    Enemy* enemy3_3 = new Enemy(91.f, 86.f, 3, "Enemy2.png");
    enemy3_3->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_3);
    enemies.push_back(enemy3_3);
    col3.push_back(enemy3_3);

    Enemy* enemy3_4 = new Enemy(123.f, 86.f, 4, "Enemy2.png");
    enemy3_4->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_4);
    enemies.push_back(enemy3_4);
    col4.push_back(enemy3_4);

    Enemy* enemy3_5 = new Enemy(155.f, 86.f, 5, "Enemy2.png");
    enemy3_5->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_5);
    enemies.push_back(enemy3_5);
    col5.push_back(enemy3_5);

    Enemy* enemy3_6 = new Enemy(187.f, 86.f, 6, "Enemy2.png");
    enemy3_6->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_6);
    enemies.push_back(enemy3_6);
    col6.push_back(enemy3_6);

    Enemy* enemy3_7 = new Enemy(220.f, 86.f, 7, "Enemy2.png");
    enemy3_7->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_7);
    enemies.push_back(enemy3_7);
    col7.push_back(enemy3_7);

    Enemy* enemy3_8 = new Enemy(253.f, 86.f, 8, "Enemy2.png");
    enemy3_8->setCollisionEnabled(true);
    drawObjects.push_back(enemy3_8);
    enemies.push_back(enemy3_8);
    col8.push_back(enemy3_8);

    // Row 4
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-
    Enemy* enemy4_1 = new Enemy(26.f, 59.f, 1, "Enemy2.png");
    enemy4_1->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_1);
    enemies.push_back(enemy4_1);
    col1.push_back(enemy4_1);

    Enemy* enemy4_2 = new Enemy(59.f, 59.f, 2, "Enemy2.png");
    enemy4_2->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_2);
    enemies.push_back(enemy4_2);
    col2.push_back(enemy4_2);

    Enemy* enemy4_3 = new Enemy(91.f, 59.f, 3, "Enemy2.png");
    enemy4_3->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_3);
    enemies.push_back(enemy4_3);
    col3.push_back(enemy4_3);

    Enemy* enemy4_4 = new Enemy(123.f, 59.f, 4, "Enemy2.png");
    enemy4_4->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_4);
    enemies.push_back(enemy4_4);
    col4.push_back(enemy4_4);

    Enemy* enemy4_5 = new Enemy(155.f, 59.f, 5, "Enemy2.png");
    enemy4_5->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_5);
    enemies.push_back(enemy4_5);
    col5.push_back(enemy4_5);

    Enemy* enemy4_6 = new Enemy(187.f, 59.f, 6, "Enemy2.png");
    enemy4_6->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_6);
    enemies.push_back(enemy4_6);
    col6.push_back(enemy4_6);

    Enemy* enemy4_7 = new Enemy(220.f, 59.f, 7, "Enemy2.png");
    enemy4_7->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_7);
    enemies.push_back(enemy4_7);
    col7.push_back(enemy4_7);

    Enemy* enemy4_8 = new Enemy(253.f, 59.f, 8, "Enemy2.png");
    enemy4_8->setCollisionEnabled(true);
    drawObjects.push_back(enemy4_8);
    enemies.push_back(enemy4_8);
    col8.push_back(enemy4_8);

    // Row 5
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-
    Enemy* enemy5_1 = new Enemy(26.f, 30.f, 1, "Enemy3.png");
    enemy5_1->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_1);
    enemies.push_back(enemy5_1);
    col1.push_back(enemy5_1);

    Enemy* enemy5_2 = new Enemy(59.f, 30.f, 2, "Enemy3.png");
    enemy5_2->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_2);
    enemies.push_back(enemy5_2);
    col2.push_back(enemy5_2);

    Enemy* enemy5_3 = new Enemy(91.f, 30.f, 3, "Enemy3.png");
    enemy5_3->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_3);
    enemies.push_back(enemy5_3);
    col3.push_back(enemy5_3);

    Enemy* enemy5_4 = new Enemy(123.f, 30.f, 4, "Enemy3.png");
    enemy5_4->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_4);
    enemies.push_back(enemy5_4);
    col4.push_back(enemy5_4);

    Enemy* enemy5_5 = new Enemy(155.f, 30.f, 5, "Enemy3.png");
    enemy5_5->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_5);
    enemies.push_back(enemy5_5);
    col5.push_back(enemy5_5);

    Enemy* enemy5_6 = new Enemy(187.f, 30.f, 6, "Enemy3.png");
    enemy5_6->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_6);
    enemies.push_back(enemy5_6);
    col6.push_back(enemy5_6);

    Enemy* enemy5_7 = new Enemy(220.f, 30.f, 7, "Enemy3.png");
    enemy5_7->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_7);
    enemies.push_back(enemy5_7);
    col7.push_back(enemy5_7);

    Enemy* enemy5_8 = new Enemy(253.f, 30.f, 8, "Enemy3.png");
    enemy5_8->setCollisionEnabled(true);
    drawObjects.push_back(enemy5_8);
    enemies.push_back(enemy5_8);
    col8.push_back(enemy5_8);
    
}

void clearEnv() {
    drawObjects.clear();
    enemies.clear();
    projectilesToRemove.clear();
    playerProjectiles.clear();
    enemyProjectilesToRemove.clear();
    enemyProjectiles.clear();
    col1.clear();
    col2.clear();
    col3.clear();
    col4.clear();
    col5.clear();
    col6.clear();
    col7.clear();
    col8.clear();
}

void restart() {

    clearEnv();

    currentColumns = {1, 2, 3, 4, 5, 6, 7, 8};

    initializeEnemies();
}

/**
 * @brief Jayden Sansom, jksanso2
 * HW 5 Part 2
 * 
 * @return int exit code
 */
int main() {

    srand (time(NULL));

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
    Player* player = new Player(WINDOW_WIDTH, WINDOW_HEIGHT, "player.png", (WINDOW_WIDTH / 2) - 22.f, WINDOW_HEIGHT - 40.f, 100.f, 50.f, 300.f, 1.f, 1.f);
    player->setCollisionEnabled(true);
    drawObjects.push_back(player);

    PlayerClient playerClient = {"One", player, true};
    Client client(&playerClient, &playerClients);

    client.requesterFunction(&playerClient);

    Thread subscriberThread = Thread(0, nullptr, &m, &cv, [&]() {
        client.subscriberFunction(&objects, &eventManager);
    });
    std::thread runReplier(run_wrapper, &subscriberThread);

    initializeEnemies();

    // Set up time variables
    float previousTime = gameTime.getTime();
    float currentTime, elapsed;

    float timeUntilCanShoot = 0.f;
    float moveDownTimer = 0.f;
    int previousMovement = 0;
    int enemyMovement = 1;

    float enemyShootTimer = 3.f;

    bool won = false;
    bool endUIShow = false;
    bool enemyReached = false;

    int lives = 3;
    sf::Texture lifeTexture;
    sf::Sprite life1;
    life1.setPosition(sf::Vector2f(5.f, 388.f));
    sf::Sprite life2;
    life2.setPosition(sf::Vector2f(32.f, 388.f));
    sf::Sprite life3;
    life3.setPosition(sf::Vector2f(59.f, 388.f));
    // Load and set texture
    if (lifeTexture.loadFromFile("player.png")) {
        life1.setTexture(lifeTexture);
        life2.setTexture(lifeTexture);
        life3.setTexture(lifeTexture);
    }

    sf::Texture wonTexture;
    sf::Texture loseTexture;
    sf::Sprite loseUI;
    loseUI.setPosition(sf::Vector2f(77.f, 170.f));
    sf::Sprite winUI;
    winUI.setPosition(sf::Vector2f(77.f, 170.f));
    // Load and set texture
    if (wonTexture.loadFromFile("WinTextUI.png")) {
        winUI.setTexture(wonTexture);
    }
    if (loseTexture.loadFromFile("LoseTextUI.png")) {
        loseUI.setTexture(loseTexture);
    }
    

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
        if(timeUntilCanShoot > 0.f) {
            timeUntilCanShoot -= elapsed;
        }
        if(moveDownTimer > 0.f) {
            moveDownTimer -= elapsed;
        }
        if(enemyShootTimer > 0.f) {
            enemyShootTimer -= elapsed;
        }

        if(window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash) && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                restart();
                enemyReached = false;
                won = false;
                endUIShow = false;
                lives = 3;
                drawObjects.push_back(player);
                player->setPosition((WINDOW_WIDTH / 2) - 22.f, WINDOW_HEIGHT - 40.f);
                timeUntilCanShoot = 0.f;
                moveDownTimer = 0.f;
                enemyShootTimer = 4.f;
                enemyMovement = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                keysPressed.Left = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                keysPressed.Right = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeUntilCanShoot <= 0.f) {
                PlayerProjectile* bullet = new PlayerProjectile(player->getPosition().x + 11, player->getPosition().y - 10.f);
                bullet->setCollisionEnabled(true);
                drawObjects.push_back(bullet);
                playerProjectiles.push_back(bullet);
                timeUntilCanShoot = 1.75f;
            }
        }

        if(player->checkCollision(sidebar1->getGlobalBounds())) {
            player->setPosition(15.f, player->getPosition().y);
        }
        else if(player->checkCollision(sidebar2->getGlobalBounds())) {
            player->setPosition(WINDOW_WIDTH - 15.f - 22.f, player->getPosition().y);
        }

        if(!endUIShow) {
            eventManager.registerEvent(new EventInputHandler(&eventManager, new EventInput(player, &keysPressed, elapsed)));

            eventManager.raise();

            client.requesterFunction(&playerClient);

            window.clear(sf::Color(0, 0, 0));

            eventManager.raise();

            for(EnemyProjectile* projectile : enemyProjectiles) {
                if(player->checkCollision(projectile->getGlobalBounds())) {
                    enemyProjectilesToRemove.push_back(projectile);
                    lives--;
                    break;
                }
            }

            if(lives <= 0) {
                clearEnv();
                endUIShow = true;
                won = false;
            }

            if(enemyShootTimer <= 0.f) {
                int randomColumnIndex = rand() % currentColumns.size();
                int randomColumn = currentColumns.at(randomColumnIndex);
                float spawnX = 0.f;
                float spawnY = 0.f;

                if(randomColumn == 1) {
                    spawnX = col1.front()->getPosition().x;
                    spawnY = col1.front()->getPosition().y;
                }
                else if(randomColumn == 2) {
                    spawnX = col2.front()->getPosition().x;
                    spawnY = col2.front()->getPosition().y;
                }
                else if(randomColumn == 3) {
                    spawnX = col3.front()->getPosition().x;
                    spawnY = col3.front()->getPosition().y;
                }
                else if(randomColumn == 4) {
                    spawnX = col4.front()->getPosition().x;
                    spawnY = col4.front()->getPosition().y;
                }
                else if(randomColumn == 5) {
                    spawnX = col5.front()->getPosition().x;
                    spawnY = col5.front()->getPosition().y;
                }
                else if(randomColumn == 6) {
                    spawnX = col6.front()->getPosition().x;
                    spawnY = col6.front()->getPosition().y;
                }
                else if(randomColumn == 7) {
                    spawnX = col7.front()->getPosition().x;
                    spawnY = col7.front()->getPosition().y;
                }
                else if(randomColumn == 8) {
                    spawnX = col8.front()->getPosition().x;
                    spawnY = col8.front()->getPosition().y;
                }

                EnemyProjectile* enemyBullet = new EnemyProjectile(spawnX + 10.f, spawnY + 15.f);
                enemyBullet->setCollisionEnabled(true);
                drawObjects.push_back(enemyBullet);
                enemyProjectiles.push_back(enemyBullet);
                enemyShootTimer = 3.f;
            }

            if(enemyMovement == 1) { // Move left
                if(currentColumns.front() == 1) {
                    if(col1.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.front() == 2) {
                    if(col2.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.front() == 3) {
                    if(col3.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.front() == 4) {
                    if(col4.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.front() == 5) {
                    if(col5.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.front() == 6) {
                    if(col6.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.front() == 7) {
                    if(col7.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.front() == 8) {
                    if(col8.front()->getPosition().x <= 15.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
            }
            else if(enemyMovement == 2) { // Move right
                if(currentColumns.back() == 8) {
                    if(col8.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.back() == 7) {
                    if(col7.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.back() == 6) {
                    if(col6.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.back() == 5) {
                    if(col5.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.back() == 4) {
                    if(col4.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.back() == 3) {
                    if(col3.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.back() == 2) {
                    if(col2.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
                else if(currentColumns.back() == 1) {
                    if(col1.front()->getPosition().x >= WINDOW_WIDTH - 35.f) {
                        previousMovement = enemyMovement;
                        enemyMovement = 3;
                        moveDownTimer = 1.f;
                    }
                }
            }
            else if(enemyMovement == 3) { // Move down
                if(moveDownTimer <= 0.f) {
                    if(previousMovement == 1) {
                        enemyMovement = 2;
                    }
                    else { 
                        enemyMovement = 1;
                    }
                }
            }

            for(Enemy* enemy: enemies) {
                if(enemy->getPosition().y >= 345) {
                    enemyReached = true;
                }

                bool enemyShot = false;
                for(PlayerProjectile* projectile : playerProjectiles) {
                    if(enemy->checkCollision(projectile->getGlobalBounds())) {
                        projectilesToRemove.push_back(projectile);
                        enemyShot = true;
                        break;
                    }
                }
                if(!enemyShot) {
                    enemy->update(elapsed, enemyMovement);
                }
                else {
                    drawObjects.erase(std::remove(drawObjects.begin(), drawObjects.end(), enemy), drawObjects.end());
                    enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
                    int column = enemy->getColumn();

                    if(column == 1) {
                        col1.erase(std::remove(col1.begin(), col1.end(), enemy), col1.end());
                        if(col1.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 1), currentColumns.end());
                        }
                    }
                    else if(column == 2) {
                        col2.erase(std::remove(col2.begin(), col2.end(), enemy), col2.end());
                        if(col2.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 2), currentColumns.end());
                        }
                    }
                    else if(column == 3) {
                        col3.erase(std::remove(col3.begin(), col3.end(), enemy), col3.end());
                        if(col3.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 3), currentColumns.end());
                        }
                    }
                    else if(column == 4) {
                        col4.erase(std::remove(col4.begin(), col4.end(), enemy), col4.end());
                        if(col4.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 4), currentColumns.end());
                        }
                    }
                    else if(column == 5) {
                        col5.erase(std::remove(col5.begin(), col5.end(), enemy), col5.end());
                        if(col5.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 5), currentColumns.end());
                        }
                    }
                    else if(column == 6) {
                        col6.erase(std::remove(col6.begin(), col6.end(), enemy), col6.end());
                        if(col6.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 6), currentColumns.end());
                        }
                    }
                    else if(column == 7) {
                        col7.erase(std::remove(col7.begin(), col7.end(), enemy), col7.end());
                        if(col7.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 7), currentColumns.end());
                        }
                    }
                    else if(column == 8) {
                        col8.erase(std::remove(col8.begin(), col8.end(), enemy), col8.end());
                        if(col8.empty()) {
                            currentColumns.erase(std::remove(currentColumns.begin(), currentColumns.end(), 8), currentColumns.end());
                        }
                    }
                }
            }

            if(enemyReached) {
                clearEnv();
                endUIShow = true;
                won = false;
            }

            if(!endUIShow && enemies.size() <= 0) {
                clearEnv();
                endUIShow = true;
                won = true;
            }

            for(PlayerProjectile* projectile : playerProjectiles) {
                if(projectile->getPosition().y <= 0.f) { // Despawn and delete if out of frame
                    projectilesToRemove.push_back(projectile);
                }
                else {
                    projectile->update(elapsed);
                }
            }

            // Remove projectiles outside of the loop
            for (PlayerProjectile* projectileToRemove : projectilesToRemove) {
                drawObjects.erase(std::remove(drawObjects.begin(), drawObjects.end(), projectileToRemove), drawObjects.end());
                playerProjectiles.erase(std::remove(playerProjectiles.begin(), playerProjectiles.end(), projectileToRemove), playerProjectiles.end());
            }
            projectilesToRemove.clear();

            for(EnemyProjectile* projectile : enemyProjectiles) {
                if(projectile->getPosition().y >= WINDOW_HEIGHT) { // Despawn and delete if out of frame
                    enemyProjectilesToRemove.push_back(projectile);
                }
                else {
                    projectile->update(elapsed);
                }
            }

            // Remove projectiles outside of the loop
            for (EnemyProjectile* projectileToRemove : enemyProjectilesToRemove) {
                drawObjects.erase(std::remove(drawObjects.begin(), drawObjects.end(), projectileToRemove), drawObjects.end());
                enemyProjectiles.erase(std::remove(enemyProjectiles.begin(), enemyProjectiles.end(), projectileToRemove), enemyProjectiles.end());
            }
            projectilesToRemove.clear();

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

            if(lives >= 1) {
                window.draw(life1);
            }
            if(lives >= 2) {
                window.draw(life2);
            }
            if(lives >= 3) {
                window.draw(life3);
            }
        }

        if(endUIShow) {
            if(won) {
                window.draw(winUI);
            }
            else {
                window.draw(loseUI);
            }
        }

        window.display();

        previousTime = currentTime;

        keysPressed.Left = false;
        keysPressed.Right = false;
    }

    return 0; // Return on end
}