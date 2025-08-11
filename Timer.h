#pragma once
class Timer
{
public:
	Timer(float _maxTime) : m_time(_maxTime), m_maxTime(_maxTime), m_isRunning(false) {}
	~Timer();

	void Init();
	void End();
	void Update(float _deltaTime);
	void Draw();

	// �^�C�}�[�̊J�n�ƒ�~
	void Start();
	void Stop();
	// �^�C�}�[�̃��Z�b�g
	void Reset();

	// �^�C�}�[�̐ݒ�
	int GetTime() const { return static_cast<int>(m_time); }
	bool IsTimeUp()const { return m_time <= 0.0f; }
	bool IsRunning() const { return m_isRunning; }

private:
	// �c�莞��
	float m_time;
	// �ő厞��
	float m_maxTime;
	// �^�C�}�[�������Ă��邩
	bool m_isRunning;	



};

