#include "Stopwatch.h"

#define NOW std::chrono::system_clock::now()

Stopwatch::Stopwatch()
{
	reset();
}

void Stopwatch::start()
{
	if (isRunning)
	{
		//already running
		return;
	}

	isRunning = true;

	startTime = NOW;
	lastTime = NOW;
}

void Stopwatch::stop()
{
	if (!isRunning)
	{
		//not even running
		return;
	}

	isRunning = false;

	timePassedSinceStart = NOW - startTime;
	timePassedLastLap = NOW - lastTime;
}

void Stopwatch::reset()
{
	//stop if running
	stop();

	//reset all values
	lastTime = std::chrono::system_clock::time_point();
	startTime = std::chrono::system_clock::time_point();
	timePassedSinceStart = std::chrono::duration<float>();
	timePassedLastLap = std::chrono::duration<float>();
}

void Stopwatch::restart()
{
	reset();

	start();
}

void Stopwatch::lap()
{
	if (!isRunning)
	{
		//cannot lap if not running
		return;
	}

	timePassedLastLap = NOW - lastTime;
	lastTime = NOW;
}

float Stopwatch::getLapTimeElapsed()
{
	return timePassedLastLap.count();
}

float Stopwatch::getTimeSinceLastLap()
{
	return static_cast<std::chrono::duration<float>>(NOW - lastTime).count();
}

float Stopwatch::getTotalTimeElapsed()
{
	if (isRunning)
	{
		timePassedSinceStart = NOW - startTime;
	}

	return timePassedSinceStart.count();
}
