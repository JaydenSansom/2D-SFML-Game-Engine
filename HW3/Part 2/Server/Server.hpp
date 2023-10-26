#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <zmq.hpp>

#include "Player.hpp"
#include "Timeline.hpp"
#include "GameObject.hpp"

/**
 * @brief Client info represented as a struct including the client's name and player character object.
 */
struct Client {
    std::string name;
    Player* player;
};

/**
 * @brief Server class responsible for handling server calls and clients
 */
class Server {
    public:
        /**
         * @brief Construct a new Server object and set up replier and publisher sockets
         */
        Server();

        /**
         * @brief Function to be run by the replier socket
         */
        void replierFunction();

        /**
         * @brief Function to be run by the publisher socket
         * 
         * @param objects objects to publish
         */
        void publishFunction(std::vector<GameObject*>* objects);

    private:
        zmq::context_t context; // ZMQ socket context
        zmq::socket_t replier; // Replier socket
        zmq::socket_t publisher; // Publisher socket
        std::vector<Client> clients; // Clients currently in the server

};

#endif