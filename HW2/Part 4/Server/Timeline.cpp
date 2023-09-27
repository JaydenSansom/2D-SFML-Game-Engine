#include "Timeline.hpp"

/**
 * @brief Move a timeline object to another as for some reason it wants a non-deafult move function?
 * 
 * @param movedTimeline timeline to be moved
 */
Timeline::Timeline(Timeline&& movedTimeline) noexcept {
    this->tic = movedTimeline.tic;
    this->paused = movedTimeline.paused;
    this->start_time = movedTimeline.start_time;
    this->elapsed_time = movedTimeline.elapsed_time;
    this->last_paused_time = movedTimeline.last_paused_time;

    movedTimeline.tic = 1000;
    movedTimeline.paused = false;
    movedTimeline.start_time = getCurrentTime();
    movedTimeline.elapsed_time = 0;
    movedTimeline.last_paused_time = 0;
}

/**
 * @brief Construct a new Timeline object
 * 
 * @param anchor Reference to anchor timeline
 * @param tic time per step
 */
Timeline::Timeline(int64_t tic) {
    this->tic = tic * 1000;
    this->paused = false;
    this->start_time = getCurrentTime();
    this->elapsed_time = 0;
    this->last_paused_time = 0;
}

/**
 * @brief Get the Tic object
 * 
 * @return float tic amount per step
 */
float Timeline::getTic() {
    std::unique_lock<std::mutex> lock(m);
    return this->tic / 1000.f;
}

/**
 * @brief Get the Time object
 * 
 * @return int64_t 
 */
int64_t Timeline::getTime() {
    if(paused) {
        return this->last_paused_time;
    }
    else {
        return (getCurrentTime() - this->start_time - this->elapsed_time);
    }
}

/**
 * @brief Pause the window
 */
void Timeline::pause() {
    std::unique_lock<std::mutex> lock(m);
    this->last_paused_time = getCurrentTime();
    this->paused = true;
}

/**
 * @brief Unpause the window
 */
void Timeline::unpause() {
    std::unique_lock<std::mutex> lock(m);
    this->elapsed_time += getCurrentTime() - this->last_paused_time;
    this->paused = false;
}

/**
 * @brief Change the tic to the given unit given in seconds and change to be milliseconds
 * 
 * @param tic new tic size to set in seconds
 */
void Timeline::changeTic(float tic) {
    std::unique_lock<std::mutex> lock(m);
    this->tic = (int64_t)(tic * 1000.f);
}

/**
 * @brief Get if the timeline is currently paused
 * 
 * @return boolean true if it is currently paused, false if not
 */
bool Timeline::isPaused() {
    std::unique_lock<std::mutex> lock(m);
    return paused;
}
