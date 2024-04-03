#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <functional>

class Timer
{
public:
    void Start(int seconds, std::function<void()> callback);
    void Stop();

    auto GetElaspedTimeInSeconds() const -> int;

    auto IsRunning() const -> bool;

    void HandleEvent();

private:
    bool m_isRunning = false;
    int m_waitingTime;

    std::time_t m_timeWhenTimerIsStarted;

    std::function<void()> m_callback;
};

#endif // TIMER_H
