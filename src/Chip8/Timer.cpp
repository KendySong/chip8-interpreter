#include "Timer.hpp"

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	_start = std::chrono::high_resolution_clock::now();
}

void Timer::Restart()
{
    Start();
}

float Timer::GetElapsedTime()
{
	_stop = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(_stop - _start).count();
}