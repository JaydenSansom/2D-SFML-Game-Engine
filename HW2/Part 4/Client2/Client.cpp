#include "Client.hpp"

std::string CLIENT_ID = "Two";

/**
 * @brief Will take a server message in the format Object/Character,PositionX,PositionY
 * 
 * @param message message to parse
 * @return std::vector<std::string> vector list of parsed message
 */
std::vector<std::string> parseServerMessage(std::string message, char parseBy) {
    std::vector<std::string> output;

    std::istringstream iss(message);
    std::string parsed;

    while(std::getline(iss, parsed, parseBy)) {
        output.push_back(parsed);
    }

    return output;
}

/**
 * @brief Create a Client Message object string
 * 
 * @param client client to convert into string
 * @return std::string string format of client
 */
std::string createClientMessage(PlayerClient* client) {
    sf::Vector2f playerPosition = client->player->getPosition();
    return client->name + "," + std::to_string(playerPosition.x) + "," + std::to_string(playerPosition.y);
}

/**
 * @brief Construct a new Client object and set up replier and publisher sockets
 */
Client::Client(PlayerClient* thisClient, std::vector<PlayerClient>* playerClients) {
    this->context = zmq::context_t{1};
    this->requester = zmq::socket_t{context, zmq::socket_type::req};
    this->subscriber = zmq::socket_t{context, zmq::socket_type::sub};
    this->thisClient = thisClient;
    this->clients = playerClients;

    requester.connect("tcp://localhost:5555");
    subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", strlen("")); // Subscribe to all messages
    std::cout << "Successfully started client " << CLIENT_ID << "!\n";
}

/**
 * @brief Function to be run by the requester socket
 */
void Client::requesterFunction(PlayerClient* playerClient) {
    // Generate message with Client info
    std::string message = createClientMessage(playerClient);
    std::cout << "sent: " << message << '\n';

    requester.send(zmq::buffer(message), zmq::send_flags::none);

    zmq::message_t recievingMessage;
    requester.recv(recievingMessage, zmq::recv_flags::none);
}

/**
 * @brief Function to be run by the subscriber socket
 * 
 * @param objects objects to publish
 */
void Client::subscriberFunction(std::vector<Object*>* objects) {
    // Loop-de-loop
    while(true) {
        zmq::message_t serverMessage;
        subscriber.recv(serverMessage, zmq::recv_flags::none);
        std::string message = std::string(static_cast<char*>(serverMessage.data()), serverMessage.size());

        // Seperate publish message into lines, each containing an object/player
        std::vector<std::string> lines = parseServerMessage(message, '\n');

        for(std::string line : lines) {
            std::vector<std::string> data = parseServerMessage(line, ',');
            std::cout << "Recieved line " << line << '\n';

            if(data[0] == "Object") {
                std::string objID = data[1];
                float xPos = stof(data[2]);
                float yPos = stof(data[3]);
                
                for(int i = 0; i < objects->size(); i++) {
                    if((*objects).at(i)->name == objID) {
                        sf::Vector2f currentPosition = (*objects).at(i)->object->getPosition();
                        (*objects).at(i)->object->move(xPos - currentPosition.x, yPos - currentPosition.y);
                        break;
                    }
                }
            }
            else { // data[0] == "Player"
                bool playerClientExists = false;

                std::string clientID = data[1];
                float xPos = stof(data[2]);
                float yPos = stof(data[3]);
                sf::Vector2f position = sf::Vector2f(xPos, yPos);
                
                if(clientID != CLIENT_ID) {
                    for(int i = 0; i < this->clients->size(); i++) {
                        if(this->clients->at(i).name == clientID) {
                            this->clients->at(i).player->setPosition(position);
                            playerClientExists = true;
                            break;
                        }
                    }
                    if(!playerClientExists) {
                        Player* player = new Player(800, 600, "wolfie.png", 250.f, 430.f, 100.f, 50.f, 300.f, 0.3f, 0.3f);
                        player->setCollisionEnabled(true);
                        player->setPosition(position);
                        PlayerClient newClient = {clientID, player};
                        clients->push_back(newClient);
                    }
                }
                playerClientExists = false;
            }
        }

    }
}