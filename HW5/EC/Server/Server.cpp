#include "Server.hpp"

/**
 * @brief Will take a client message in the format ClientID,playerPositionX,playerPositionY
 * 
 * @param message message to parse
 * @return std::vector<std::string> vector list of parsed message
 */
std::vector<std::string> parseClientMessage(std::string message) {
    std::vector<std::string> output;

    std::istringstream iss(message);
    std::string parsed;

    while(std::getline(iss, parsed, ',')) {
        output.push_back(parsed);
    }

    return output;
}

/**
 * @brief Create a Object Message object string
 * 
 * @param object object to convert into string
 * @return std::string string format of object
 */
std::string createObjectMessage(GameObject* object) {
    if(object) {
        sf::Vector2f objectPos = object->getCollider()->getPosition();
        return "Object," + object->getName() + "," + std::to_string(objectPos.x) + "," + std::to_string(objectPos.y) + "\n";
    }
    else {
        return "";
    }
}

/**
 * @brief Create a Player Message object string
 * 
 * @param client client to convert into string
 * @return std::string string format of player
 */
std::string createPlayerMessage(PlayerClient* client) {
    sf::Vector2f playerPos = client->player->getPosition();
    std::string isActiveString;
    if(client->isActive) {
        isActiveString = "true";
    }
    else {
        isActiveString = "false";
    }
    return "Player," + client->name + "," + isActiveString + "," + std::to_string(playerPos.x) + "," + std::to_string(playerPos.y) + "\n";
}

/**
 * @brief Create a Event Message object string
 * 
 * @param event event to convert into string
 * @return std::string string format of an event
 */
std::string createEventMessage(Event* e) {
    EventType eventType = e->getEventType();
    std::string eventTypeString;
    std::string eventParams;
    if(eventType == EventType::EVENT_CLIENT_DISCONNECT) {
        eventTypeString = "ClientDisconnect";
        eventParams = *static_cast<std::string*>(e->getVarient(ParamType::CLIENT_NAME).getValue());
    }
    else {
        eventTypeString = "none";
    }
    return "Event," + eventTypeString + "," + eventParams + "\n";
}

/**
 * @brief Construct a new Server object and set up replier and publisher sockets
 */
Server::Server() {
    this->context = zmq::context_t{1};
    this->replier = zmq::socket_t{context, zmq::socket_type::rep};
    this->publisher = zmq::socket_t{context, zmq::socket_type::pub};

    this->replier.bind("tcp://*:5555");
    this->publisher.bind("tcp://*:5556");
    std::cout << "Successfully started server!\n";
}

/**
 * @brief Function to be run by the replier socket
 */
void Server::replierFunction() {
    bool newClient = true;
    while(true) {
        // Listen for clients
        zmq::message_t message;
        replier.recv(message, zmq::recv_flags::none);
        std::string clientMessage = std::string(static_cast<char*>(message.data()), message.size());

        // ClientID,x,y
        std::vector<std::string> parsedClientMessage = parseClientMessage(clientMessage);

        std::string clientID = parsedClientMessage[0];
        bool isActiveClient;
        if(parsedClientMessage[1] == "true") {
            isActiveClient = true;
        }
        else {
            isActiveClient = false;
        }
        float xPos = stof(parsedClientMessage[2]);
        float yPos = stof(parsedClientMessage[3]);

        // Check if there are any existing clients
        if(clients.empty()) {
            // Create Player
            Player* player = new Player(600, 400, "WolfieMaze.png", 98.f, 15.f, 100.f, 50.f, 300.f, 1.f, 1.f);
            player->setCollisionEnabled(true);
            player->setPosition(xPos, yPos);
            clients.push_back(PlayerClient{clientID, player, isActiveClient});
        }
        else {
            // See if client already exists
            int i = 0;
            for(PlayerClient client: clients) {
                if(client.name == clientID) {
                    if(isActiveClient) {
                        client.player->setPosition(xPos, yPos);
                    }
                    else {
                        client.player->setCollisionEnabled(false);
                        clients.erase(clients.begin() + i);
                        this->replier.send(zmq::buffer("Client Disconnected"), zmq::send_flags::none);
                        events.push_back(new EventClientDisconnect(client.name, &this->clients));
                        goto ClientDisconnect;
                    }
                    newClient = false;
                    break;
                }
                i++;
            }
            if(newClient) {
                // Create Player
                Player* player = new Player(600, 400, "WolfieMaze.png", 98.f, 15.f, 100.f, 50.f, 300.f, 1.f, 1.f);
                player->setCollisionEnabled(true);
                player->setPosition(xPos, yPos);
                clients.push_back(PlayerClient{clientID, player, isActiveClient});
            }
        }

        newClient = true;

        this->replier.send(zmq::buffer("Reply Success!"), zmq::send_flags::none);

        ClientDisconnect:;
    }
}

/**
 * @brief Function to be run by the publisher socket
 * 
 * @param objects objects to publish
 */
void Server::publishFunction(std::vector<GameObject*>* objects) {
    using namespace std::chrono_literals;

    std::string message; // message to publish

    for(GameObject* object : *objects) {
        message += createObjectMessage(object);
    }
    int i = 0;
    for(PlayerClient client : clients) {
        message += createPlayerMessage(&client);
        if(!client.isActive) {
            clients.erase(clients.begin() + i);
        }
        i++;
    }
    int j = 0;
    for(Event* eventHandler : events) {
        message += createEventMessage(eventHandler);
        events.erase(events.begin() + j);
        j++;
    }
    // Send the reply to the client
    this->publisher.send(zmq::buffer(message), zmq::send_flags::none);

    // Sleepy time                      zᶻ
    // to avoid going too fast   ૮˶- ﻌ -˶ა⌒)ᦱ
    std::this_thread::sleep_for(10ms);
}
