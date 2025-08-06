#pragma once
class Manhole
{
public:
	Manhole();
	~Manhole();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	// マンホールのハンドル
	int m_manholeHandle;

};

