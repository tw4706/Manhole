#pragma once
class Manhole
{
public:
	Manhole();
	~Manhole();

	void Init(int _handle1,int _handle2);
	void End();
	void Update();
	void Draw();

	void HitManhole(int _handle1, int _handle2);

private:
	// マンホールのハンドル
	int m_manhole1Handle;
	int m_manhole2Handle;
	// マンホールに当たっているか
	bool m_isHitManhole;

};

