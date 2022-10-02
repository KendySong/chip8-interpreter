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
    #ifdef _MSC_VER
        std::chrono::time_point<std::chrono::steady_clock> _start;
        std::chrono::time_point<std::chrono::steady_clock> _stop;
    #endif

    #ifdef __GNUC__
        std::chrono::time_point<std::chrono::system_clock> _start;
        std::chrono::time_point<std::chrono::system_clock> _stop;
    #endif
};