#include "EventHandler.hpp"
#include "EventManager.hpp"

/**
 * @brief Destroy the EventHandler object
 */
EventHandler::~EventHandler() {}

EventHandler::EventHandler(EventManager* manager, Event* event) {
    this->manager = manager;
    this->event = event;
}

EventCollisionHandler::EventCollisionHandler(EventManager* manager, Event* event) : EventHandler(manager, event) {
    this->manager = manager;
    this->event = event;
    this->eventType = EventType::EVENT_COLLISION;
}

void EventCollisionHandler::onEvent() {
    Player* player = static_cast<Player*>(this->event->getVarient(ParamType::CHAR_POINTER).getValue());
    Collider* objCollider = nullptr;
    GameObject* obj = static_cast<GameObject*>(this->event->getVarient(ParamType::OBJ_POINTER).getValue());
    
    if (obj)
        objCollider = obj->getCollider();
    
    if (player && objCollider)
        player->resolveCollision(*player, *objCollider);
}

void EventCollisionHandler::setEventType(EventType e) {
    this->eventType = e;
}

EventType EventCollisionHandler::getEventType() {
    return this->eventType;
}

Event* EventCollisionHandler::getEvent() {
    return this->event;
}

EventManager* EventCollisionHandler::getEventManager() {
    return this->manager;
}

EventSpawnHandler::EventSpawnHandler(EventManager* manager, Event* event) : EventHandler(manager, event) {
    this->manager = manager;
    this->event = event;
    this->eventType = EventType::EVENT_SPAWN;
}

void EventSpawnHandler::onEvent() {
    Player* player = static_cast<Player*>(this->event->getVarient(ParamType::CHAR_POINTER).getValue());
    sf::RenderWindow* window = static_cast<sf::RenderWindow*>(this->event->getVarient(ParamType::WINDOW).getValue());
    sf::View* camera = static_cast<sf::View*>(this->event->getVarient(ParamType::CAMERA).getValue());
    SideScrollArea* leftScrollArea = static_cast<SideScrollArea*>(this->event->getVarient(ParamType::LEFT_SIDE_SCROLL).getValue());
    SideScrollArea* rightScrollArea = static_cast<SideScrollArea*>(this->event->getVarient(ParamType::RIGHT_SIDE_SCROLL).getValue());
    double xPos = *static_cast<double*>(this->event->getVarient(ParamType::X_POS).getValue());
    double yPos = *static_cast<double*>(this->event->getVarient(ParamType::Y_POS).getValue());

    player->setPosition(xPos, yPos);
    camera->setCenter(window->getDefaultView().getCenter());
    leftScrollArea->setPosition(window->getView().getViewport().left, 0.f);
    rightScrollArea->setPosition(window->getView().getViewport().left + window->getDefaultView().getSize().x - rightScrollArea->getLocalBounds().width, 0.f);
}

void EventSpawnHandler::setEventType(EventType e) {
    this->eventType = e;
}

EventType EventSpawnHandler::getEventType() {
    return this->eventType;
}

Event* EventSpawnHandler::getEvent() {
    return this->event;
}

EventManager* EventSpawnHandler::getEventManager() {
    return this->manager;
}

EventDeathHandler::EventDeathHandler(EventManager* manager, Event* event) : EventHandler(manager, event) {
    this->manager = manager;
    this->event = event;
    this->eventType = EventType::EVENT_DEATH;
}

void EventDeathHandler::onEvent() {
    Player* player = static_cast<Player*>(this->event->getVarient(ParamType::CHAR_POINTER).getValue());
    sf::RenderWindow* window = static_cast<sf::RenderWindow*>(this->event->getVarient(ParamType::WINDOW).getValue());
    sf::View* camera = static_cast<sf::View*>(this->event->getVarient(ParamType::CAMERA).getValue());
    SideScrollArea* leftScrollArea = static_cast<SideScrollArea*>(this->event->getVarient(ParamType::LEFT_SIDE_SCROLL).getValue());
    SideScrollArea* rightScrollArea = static_cast<SideScrollArea*>(this->event->getVarient(ParamType::RIGHT_SIDE_SCROLL).getValue());

    std::vector<SpawnPoint*>* spawnPoints = static_cast<std::vector<SpawnPoint*>*>(this->event->getVarient(ParamType::SPAWN_POINTS).getValue());
    srand(time(NULL));
    int randomIndex = rand() % spawnPoints->size();
    sf::Vector2f chosenSpawnPoint = spawnPoints->at(randomIndex)->getSpawnPointLocation();
    double xPos = chosenSpawnPoint.x;
    double yPos = chosenSpawnPoint.y;

    getEventManager()->registerEvent(new EventSpawnHandler(this->manager, new EventSpawn(player, xPos, yPos, window, camera, leftScrollArea, rightScrollArea)));
}

void EventDeathHandler::setEventType(EventType e) {
    this->eventType = e;
}

EventType EventDeathHandler::getEventType() {
    return this->eventType;
}

Event* EventDeathHandler::getEvent() {
    return this->event;
}

EventManager* EventDeathHandler::getEventManager() {
    return this->manager;
}

EventInputHandler::EventInputHandler(EventManager* manager, Event* event) : EventHandler(manager, event) {
    this->manager = manager;
    this->event = event;
    this->eventType = EventType::EVENT_INPUT;
}

void EventInputHandler::onEvent() {
    Player* player = static_cast<Player*>(this->event->getVarient(ParamType::CHAR_POINTER).getValue());
    float elapsedTime = *static_cast<float*>(this->event->getVarient(ParamType::ELAPSED_TIME).getValue());
    KeysPressed* keys = static_cast<KeysPressed*>(this->event->getVarient(ParamType::USER_INPUT_KEY).getValue());
    bool isSprinting = *static_cast<bool*>(this->event->getVarient(ParamType::IS_SPRINTING).getValue());
    player->update(elapsedTime, *keys, this->manager, isSprinting);
}

void EventInputHandler::setEventType(EventType e) {
    this->eventType = e;
}

EventType EventInputHandler::getEventType() {
    return this->eventType;
}

Event* EventInputHandler::getEvent() {
    return this->event;
}

EventManager* EventInputHandler::getEventManager() {
    return this->manager;
}

EventClientDisconnectHandler::EventClientDisconnectHandler(EventManager* manager, Event* event) : EventHandler(manager, event) {
    this->manager = manager;
    this->event = event;
    this->eventType = EventType::EVENT_CLIENT_DISCONNECT;
}

void EventClientDisconnectHandler::onEvent() {
    std::string clientName = *static_cast<std::string*>(this->event->getVarient(ParamType::CLIENT_NAME).getValue());
    std::vector<PlayerClient>* clients = static_cast<std::vector<PlayerClient>*>(this->event->getVarient(ParamType::CLIENTS).getValue());
    for(int i = 0; i < clients->size(); i++) {
        if(clients->at(i).name == clientName) {
            clients->at(i).player->setCollisionEnabled(false);
            clients->erase(clients->begin() + i);
            break;
        }
    }
}

void EventClientDisconnectHandler::setEventType(EventType e) {
    this->eventType = e;
}

EventType EventClientDisconnectHandler::getEventType() {
    return this->eventType;
}

Event* EventClientDisconnectHandler::getEvent() {
    return this->event;
}

EventManager* EventClientDisconnectHandler::getEventManager() {
    return this->manager;
}