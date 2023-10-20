#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <zmq.hpp>

#include "Player.hpp"
#include "Timeline.hpp"
#include "Collider.hpp"

/**
 * @brief Client info represented as a struct including the client's name and player character object.
 */
struct PlayerClient {
    std::string name;
    Player* player;
};

/**
 * @brief Object info represented as a struct including the objects's name and object.
 */
struct Object {
    std::string name;
    Collider* object;
};

/**
 * @brief Client class responsible for handling client calls and server information
 */
class Client {
    public:
        /**
         * @brief Construct a new Client object and set up replier and publisher sockets
         */
        Client(PlayerClient* thisClient, std::vector<PlayerClient>* clients);

        /**
         * @brief Function to be run by the requester socket
         */
        void requesterFunction(PlayerClient* playerClient);

        /**
         * @brief Function to be run by the subscriber socket
         * 
         * @param objects objects to publish
         */
        void subscriberFunction(std::vector<Object*>* objects);

    private:
        zmq::context_t context; // ZMQ socket context
        zmq::socket_t requester; // Requester socket
        zmq::socket_t subscriber; // Subscriber socket
        std::vector<PlayerClient>* clients; // Clients currently in the server
        PlayerClient* thisClient; // Reference to current client
};

#endif