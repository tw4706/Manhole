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
	// �}���z�[���̃n���h��
	int m_manhole1Handle;
	int m_manhole2Handle;
	// �}���z�[���ɓ������Ă��邩
	bool m_isHitManhole;

};

