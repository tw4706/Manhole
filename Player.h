#pragma once
#include"Vec2.h"
class Player
{
public:
	Player();
	~Player();

	void Init(int _padType,Vec2 _firstPos);
	void End();
	void Update();
	void Draw();

private:

	Vec2 m_pos;		// ���W
	int m_padType;	// �p�b�h�̎��
	float m_radius;	// �����蔻��̔��a
	bool m_isTurn;	// ���E���]
};

