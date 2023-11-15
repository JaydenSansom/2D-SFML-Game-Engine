#pragma once

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <zmq.hpp>

#include "Player.hpp"
#include "GameObject.hpp"
#include "Timeline.hpp"
#include "EventManager.hpp"

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
        std::vector<PlayerClient> clients; // Clients currently in the server
        std::vector<Event*> events; // Events currently in the server

};