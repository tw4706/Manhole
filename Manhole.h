#pragma once
#include"Vec2.h"
#include"Rect.h"
class Manhole
{
public:
	Manhole();
	~Manhole();

	void Init(int _handle1,int _handle2);
	void End();
	void Update();
	void Draw();

	// �v���C���[���}���z�[���ɓ������Ă��邩�ǂ���
	bool CheckCollision(const Rect& playerRect);
	bool CheckLeftCollision(const Rect& playerRect);
	bool CheckRightCollision(const Rect& playerRect);

private:
	// �}���z�[���̃n���h��
	int m_handle1;
	int m_handle2;
	// �}���z�[���ɓ������Ă��邩
	bool m_leftTriggered;
	bool m_rightTriggered;
	// �����蔻��p�̋�`
	Rect m_colRect;
	Rect m_leftRect;
	Rect m_rightRect;

};

