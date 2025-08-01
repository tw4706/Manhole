#pragma once
#include"Vec2.h"
class Player
{
public:
	Player();
	~Player();

	void Init(int _padType,Vec2 _firstPos,int _handle);
	void End();
	void Update();
	void Draw();
	void Gravity();


private:

	int m_handle;	// �O���t�B�b�N�̃n���h��
	Vec2 m_pos;		// ���W
	int m_padType;	// �p�b�h�̎��
	float m_radius;	// �����蔻��̔��a
	bool m_isTurn;	// ���E���]
	int m_animFrame;// �A�j���[�V�����̃t���[��
};

