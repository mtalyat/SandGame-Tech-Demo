#pragma once

#include <ctime>
#include <chrono>
#include "Object.h"

class Stopwatch :
    public Object
{
public:
    Stopwatch();

    /// <summary>
    /// Starts this Stopwatch.
    /// </summary>
    void start();
    /// <summary>
    /// Stops this Stopwatch.
    /// </summary>
    void stop();
    /// <summary>
    /// Stops and resets the time on this Stopwatch.
    /// </summary>
    void reset();
    /// <summary>
    /// Stops, resets and starts this Stopwatch.
    /// </summary>
    void restart();
    /// <summary>
    /// Logs the last lap taken in this Stopwatch.
    /// </summary>
    void lap();

    float getLapTimeElapsed();
    float getTimeSinceLastLap();
    float getTotalTimeElapsed();
private:
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point lastTime;
    std::chrono::duration<float> timePassedSinceStart;
    std::chrono::duration<float> timePassedLastLap;
    bool isRunning;
};