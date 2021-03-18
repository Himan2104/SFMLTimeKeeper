#pragma once
#include<SFML/System.hpp>

class TimeKeeper
{
public:
    enum ClockType 
    {
        Static, //Static = clock unaffected by the timescale
        Dynamic //Dynamic = clock that varies with the timescale
    };

    //use this right before your main game loop
    static void initializeTime();

    //returns the deltaTime in float
    static float deltaTime();

    //change the timescale
    /*
    default = 1.0f
    pause = 0.0f
    */
    static void timeScale(float multiplier);

    //call this at the beginning of your main loop
    static void updateTime();

    //get the time elapsed in seconds
    /*
    Static = clock unaffected by the timescale
    Dynamic = clock that varies with the timescale
    */
    static float timeSinceStart(ClockType _type);

    //returns the current timescale
    static float getTimeScale();

    //returns the frametime
    static float frameTime();

    static void resetClock(ClockType _type);

private:
    static sf::Clock* m_GameClock;
    static sf::Clock* m_FrameClock;
    static float m_timeScale;
    static float m_deltaTime;
    static float m_dynamicClockTime;
};

sf::Clock* TimeKeeper::m_GameClock = new sf::Clock();
sf::Clock* TimeKeeper::m_FrameClock = new sf::Clock();

float TimeKeeper::m_deltaTime = 0.0f;

float TimeKeeper::m_timeScale = 1.0f;

float TimeKeeper::m_dynamicClockTime = 0.0f;

void TimeKeeper::initializeTime()
{
    m_GameClock->restart().asSeconds();
    m_FrameClock->restart().asSeconds();
}

void TimeKeeper::timeScale(float multiplier)
{
    m_timeScale = multiplier;
}

void TimeKeeper::updateTime()
{
    m_deltaTime = m_FrameClock->getElapsedTime().asSeconds();
    m_FrameClock->restart().asSeconds();
    m_dynamicClockTime += m_deltaTime * m_timeScale; 
}

float TimeKeeper::timeSinceStart(ClockType _type)
{
    if(_type == ClockType::Static) return m_GameClock->getElapsedTime().asSeconds();
    else  return m_dynamicClockTime;
}

float TimeKeeper::deltaTime()
{
    return m_deltaTime * m_timeScale; 
}

float TimeKeeper::getTimeScale()
{
    return m_timeScale;
}

float TimeKeeper::frameTime()
{
    return m_deltaTime;
}

void TimeKeeper::resetClock(ClockType _type)
{
    if(_type == Static) m_GameClock->restart().asSeconds();
    else if(_type == Dynamic) m_dynamicClockTime = 0;
}