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
	bool IsHitLeft(const Rect& playerRect);
	bool IsHitRight(const Rect& playerRect);
	// �}���z�[���̓����蔻����Ȃ���
	void DisableCollision();

private:
	// �}���z�[���̃n���h��
	int m_manhole1Handle;
	int m_manhole2Handle;
	// �}���z�[���ɓ������Ă��邩
	bool m_isHitManhole;
	bool m_leftTriggerFlag;
	bool m_rightTriggerFlag;
	Rect m_colRect; // �����蔻��p�̋�`
	Rect m_leftRect;
	Rect m_rightRect;

};

