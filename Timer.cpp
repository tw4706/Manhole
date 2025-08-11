#include "Timer.h"

Timer roundTimer(99.0f);

Timer::~Timer()
{
}

void Timer::Update(float _deltaTime)
{
	if (m_isRunning && m_time > 0.0f)
	{
		m_time-= _deltaTime;
		if (m_time < 0.0f)
		{
			m_time = 0.0f;
		}
	}
}

void Timer::Start()
{
	m_isRunning = true;
}

void Timer::Stop()
{
	m_isRunning = false;
}

void Timer::Reset()
{
	m_time = m_maxTime;
	m_isRunning = false;
}
