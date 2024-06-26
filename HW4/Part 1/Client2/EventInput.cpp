#include "EventInput.hpp"

EventInput::EventInput(Player * player, KeysPressed* KeyInput, float elapsedTime) : Event(EventType::EVENT_INPUT) {
    addVarient(ParamType::CHAR_POINTER, player);
    addVarient(ParamType::USER_INPUT_KEY, KeyInput);
    addVarient(ParamType::ELAPSED_TIME, elapsedTime);
}