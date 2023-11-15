#include "EventClientDisconnect.hpp"

/**
 * @brief Construct a new Event Client Disconnect object
 * 
 * @param clientName name of the client
 */
EventClientDisconnect::EventClientDisconnect(std::string clientName, std::vector<PlayerClient>* clients) : Event(EventType::EVENT_CLIENT_DISCONNECT) {
    addVarient(ParamType::CLIENT_NAME, clientName);
    addVarient(ParamType::CLIENTS, clients);
}