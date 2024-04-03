#include "Timer.h"

void Timer::Start(int seconds, std::function<void()> callback)
{
    m_waitingTime = seconds;
    m_callback = callback;
    m_timeWhenTimerIsStarted = std::time(nullptr);
    m_isRunning = true;
}

int Timer::GetElaspedTimeInSeconds() const
{
    const auto currentTime = std::time(nullptr);
    const auto elapsedTime = currentTime - m_timeWhenTimerIsStarted;

    return elapsedTime;
}

bool Timer::IsRunning() const
{
    return m_isRunning;
}

void Timer::HandleEvent()
{
    if(false == IsRunning())
    {
        return;
    }

    if(GetElaspedTimeInSeconds() >= m_waitingTime)
    {
        m_callback();
        Stop();
    }
}

void Timer::Stop()
{
    m_isRunning = false;
}
