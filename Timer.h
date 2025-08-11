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

	// タイマーの開始と停止
	void Start();
	void Stop();
	// タイマーのリセット
	void Reset();

	// タイマーの設定
	int GetTime() const { return static_cast<int>(m_time); }
	bool IsTimeUp()const { return m_time <= 0.0f; }
	bool IsRunning() const { return m_isRunning; }

private:
	// 残り時間
	float m_time;
	// 最大時間
	float m_maxTime;
	// タイマーが動いているか
	bool m_isRunning;	



};

