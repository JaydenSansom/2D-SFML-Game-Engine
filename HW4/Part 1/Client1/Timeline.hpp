#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <cmath>
#include <mutex>
#include <chrono>

class Timeline {

    public:

        /**
         * @brief Move a timeline object to another as for some reason it wants a non-deafult move function?
         * It makes it happy :)
         * 
         * @param movedTimeline timeline to be moved
         */
        Timeline(Timeline&& movedTimeline) noexcept;

        /**
         * @brief Construct a new Timeline object
         * 
         * @param tic time per step
         */
        Timeline(int64_t tic);

        /**
         * @brief Get the Tic object
         * 
         * @return float tic amount per step
         */
        float getTic();

        /**
         * @brief Get the Time object
         * 
         * @return int64_t 
         */
        int64_t getTime();

        /**
         * @brief Pause the window
         */
        void pause();

        /**
         * @brief Unpause the window
         */
        void unpause();

        /**
         * @brief Change the tic to the given unit
         * 
         * @param tic new tic size to set
         */
        void changeTic(float tic);

        /**
         * @brief Get if the timeline is currently paused
         * 
         * @return boolean true if it is currently paused, false if not
         */
        bool isPaused();

    private:
        std::mutex m; // mutex used for locking the timeline info
        int64_t start_time; // time when the timeline was created
        int64_t elapsed_time; // elapsed time
        int64_t last_paused_time; // time that the timeline was last paused
        int64_t tic; // units of time per step
        bool paused; // whether the timeline is paused

        int64_t getCurrentTime() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }
};
