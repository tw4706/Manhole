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

private:
	// マンホールのハンドル
	int m_manhole1Handle;
	int m_manhole2Handle;

};

