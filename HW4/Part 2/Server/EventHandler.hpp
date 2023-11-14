#pragma once

class Event;
enum class EventType;

#include "EventCollision.hpp"
#include "EventDeath.hpp"
#include "EventInput.hpp"
#include "EventSpawn.hpp"

class EventHandler {
    
    public:
        /**
         * @brief Destroy the EventHandler object
         */
        ~EventHandler();

        EventHandler(EventManager* manager, Event* event);

        virtual void onEvent() = 0;

        virtual void setEventType(EventType e) = 0;

        virtual EventType getEventType() = 0;

        virtual Event* getEvent() = 0;

        virtual EventManager* getEventManager() = 0;

    private:
        EventType eventType;

        EventManager* manager;

        Event* event;

};

class EventCollisionHandler : public EventHandler {

    public:
        EventCollisionHandler(EventManager* manager, Event* event);

        void onEvent() override;

        Event* getEvent() override;

        EventManager* getEventManager() override;

        void setEventType(EventType e);

        EventType getEventType();

    private:
        EventType eventType;

        EventManager* manager;

        Event* event;

};

class EventSpawnHandler : public EventHandler {

    public:
        EventSpawnHandler(EventManager* manager, Event* event);

        void onEvent() override;

        Event* getEvent() override;

        EventManager* getEventManager() override;

        void setEventType(EventType e);

        EventType getEventType();

    private:
        EventType eventType;

        EventManager* manager;

        Event* event;

};

class EventDeathHandler : public EventHandler {

    public:
        EventDeathHandler(EventManager* manager, Event* event);

        void onEvent() override;

        Event* getEvent() override;

        EventManager* getEventManager() override;

        void setEventType(EventType e);

        EventType getEventType();

    private:
        EventType eventType;

        EventManager* manager;

        Event* event;

};

class EventInputHandler : public EventHandler {

    public:
        EventInputHandler(EventManager* manager, Event* event);

        void onEvent() override;

        Event* getEvent() override;

        EventManager* getEventManager() override;

        void setEventType(EventType e);

        EventType getEventType();

    private:
        EventType eventType;

        EventManager* manager;

        Event* event;

};
