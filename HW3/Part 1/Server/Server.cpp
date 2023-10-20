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
std::string createObjectMessage(Object* object) {
    if(object) {
        sf::Vector2f objectPos = object->object->getPosition();
        return "Object," + object->name + "," + std::to_string(objectPos.x) + "," + std::to_string(objectPos.y) + "\n";
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
std::string createPlayerMessage(Client* client) {
    sf::Vector2f playerPos = client->player->getPosition();
    return "Player," + client->name + "," + std::to_string(playerPos.x) + "," + std::to_string(playerPos.y) + "\n";
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
        float xPos = stof(parsedClientMessage[1]);
        float yPos = stof(parsedClientMessage[2]);

        // Check if there are any existing clients
        if(clients.empty()) {
            // Create Player
            Player* player = new Player(800, 600, "wolfie.png", 250.f, 430.f, 100.f, 50.f, 300.f, 0.3f, 0.3f);
            player->setCollisionEnabled(true);
            player->setPosition(xPos, yPos);
            clients.push_back(Client{clientID, player});
        }
        else {
            // See if client already exists
            for(Client client: clients) {
                if(client.name == clientID) {
                    client.player->setPosition(xPos, yPos);
                    newClient = false;
                }
            }
            if(newClient) {
                // Create Player
                Player* player = new Player(800, 600, "wolfie.png", 250.f, 430.f, 100.f, 50.f, 300.f, 0.3f, 0.3f);
                player->setCollisionEnabled(true);
                player->setPosition(xPos, yPos);
                clients.push_back(Client{clientID, player});
            }
        }

        newClient = true;

        this->replier.send(zmq::buffer("Reply Success!"), zmq::send_flags::none);
    }
}

/**
 * @brief Function to be run by the publisher socket
 * 
 * @param objects objects to publish
 */
void Server::publishFunction(std::vector<Object*>* objects) {
    using namespace std::chrono_literals;

    std::string message; // message to publish

    for(Object* object : *objects) {
        message += createObjectMessage(object);
    }
    for(Client client : clients) {
        message += createPlayerMessage(&client);
    }
    // Send the reply to the client
    this->publisher.send(zmq::buffer(message), zmq::send_flags::none);

    // Sleepy time                      zᶻ
    // to avoid going to fast   ૮˶- ﻌ -˶ა⌒)ᦱ
    std::this_thread::sleep_for(10ms);
}
