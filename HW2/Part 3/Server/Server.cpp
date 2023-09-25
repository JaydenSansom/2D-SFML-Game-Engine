#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

#include <zmq.hpp>

/**
 * @brief Client info represented as a struct including the client's name and iteration number.
 */
typedef struct {
    std::string name;
    int iteration;
} Client;

/**
 * @brief Function for running the publisher socket where data will be processed
 * 
 * @param publisherSocket socket of the publisher
 * @param clients list of current client objects
 */
void publishThreadFunction(zmq::socket_t* publisherSocket, std::vector<Client>* clients) {
    using namespace std::chrono_literals;

    while(true) {
        std::string message = "";
        for(int i = 0; i < clients->size(); i++) {
            message += "Client " + std::to_string(i + 1) + ": Iteration " + std::to_string((*clients)[i].iteration) + "\n";
            (*clients)[i].iteration += 1;
        }

        // Send the reply to the client
        (*publisherSocket).send(zmq::buffer(message), zmq::send_flags::none);

        // Sleepy time             zᶻ
        //                  ૮˶- ﻌ -˶ა⌒)ᦱ
        std::this_thread::sleep_for(3s);
    }

}

/**
 * @brief jksanso2, HW 2 Part 3
 * Base functionality was based off of 0MQ Documentation cppzmq C++ client-server examples
 * 
 * @return int exit code
 */
int main() 
{
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a PUB (publisher) socket and bind to interface
    zmq::socket_t publisher{context, zmq::socket_type::pub};
    publisher.bind("tcp://*:5556");

    // construct a REP (reply) socket and bind to interface
    zmq::socket_t replier{context, zmq::socket_type::rep};
    replier.bind("tcp://*:5555");

    std::vector<Client> clients;

    std::thread publisherThread([&publisher, &clients] {
        publishThreadFunction(&publisher, &clients);
    });

    while (true) {
        // Wait for a client
        zmq::message_t message;
        replier.recv(message, zmq::recv_flags::none);
        std::string clientId = std::string(static_cast<char*>(message.data()), message.size());

        // Create new Client
        Client newClient = {clientId, 1};
        clients.push_back(newClient);
        std::cout << "Received " << clientId << std::endl;

        // Send the reply to the client
        replier.send(zmq::buffer("Client " + clientId + " connected."), zmq::send_flags::none);
    }

    return 0;
}
