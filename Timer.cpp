#include "Timer.h"
#include "DxLib.h"

Timer::Timer():
	m_time(0.0f),
	m_maxTime(0.0f),
	m_isRunning(false)
{
}

Timer::~Timer()
{
}

void Timer::Init(float _maxTime)
{
	m_maxTime = _maxTime;
	Reset();
	Start();
}

void Timer::End()
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
void Timer::Draw(int _x, int _y) const
{
	int color = GetColor(255, 255, 0);
	// �^�C�}�[�̎c�莞�Ԃ𐮐��ɕϊ�
	char buffer[32];
	sprintf_s(buffer, "Time: %d", static_cast<int>(m_time));
	DrawFormatString(_x, _y, color, buffer);
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
