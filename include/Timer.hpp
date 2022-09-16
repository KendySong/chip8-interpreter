#include <chrono>

#pragma once

/**
 * @brief Mesure the time for count fps
 * 
 */
class Timer
{
public :
    /**
     * @brief Constructor
     * 
     */
	Timer();

    /**
     * @brief Start the timer
     * 
     */
	void Start();

    /**
     * @brief Restart the timer
     * 
     */
    void Restart();

    /**
     * @brief Return elapsed time between last start or restart and now
     * 
     * @return elapsed time in milliseconds
     */
	float GetElapsedTime();

private :
	std::chrono::time_point<std::chrono::system_clock> _start;
	std::chrono::time_point<std::chrono::system_clock> _stop;
};