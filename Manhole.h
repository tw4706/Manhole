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
	// �}���z�[���̃n���h��
	int m_manholeHandle;

};

