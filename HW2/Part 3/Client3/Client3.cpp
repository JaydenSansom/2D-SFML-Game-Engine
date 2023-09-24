#include <string>
#include <iostream>

#include <zmq.hpp>

int CLIENT_NAME = 3;

int main()
{
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REQ (request) socket and connect to interface
    zmq::socket_t requester{context, zmq::socket_type::req};
    requester.connect("tcp://localhost:5555");

    // construct a SUB (subscriber) socket and connect to interface
    zmq::socket_t subscriber{context, zmq::socket_type::sub};
    subscriber.connect("tcp://localhost:5555");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "Client");

    requester.send(zmq::buffer(std::to_string(CLIENT_NAME)), zmq::send_flags::none);

    zmq::message_t message;
    requester.recv(message, zmq::recv_flags::none);
    std::string response = std::string(static_cast<char*>(message.data()), message.size());
    std::cout << response << '\n';

    while(true) {
        zmq::message_t dataMessage;
        requester.recv(dataMessage, zmq::recv_flags::none);
        std::string data = std::string(static_cast<char*>(dataMessage.data()), dataMessage.size());
        std::cout << data;
    }

    return 0;
}