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
	void Update(const Vec2& _player1Pos, const Vec2& _player2Pos);
	void Draw();

	// �v���C���[���}���z�[���ɓ������Ă��邩�ǂ���
	bool CheckLeftCollision(const Rect& playerRect);
	bool CheckRightCollision(const Rect& playerRect);
	// �}���z�[���̈ʒu���擾
	Vec2 GetCenter()const;

private:
	// �}���z�[���̃n���h��
	int m_handle1;
	int m_handle2;
	// �}���z�[���ɓ������Ă��邩
	bool m_leftTriggered;
	bool m_rightTriggered;
	// �댯��m�点��p�̃O���t�B�b�N�̓��h��
	int m_warningHandle;
	// �_�ŗp�̃^�C�}�[
	int m_blinkTimer;
	// �_�ŗp�̃t���O
	bool m_blinkFlag;
	// ���E�̕\���X�V
	bool m_showLeftWarning;
	bool m_showRightWarning;

	// �����蔻��p�̋�`
	Rect m_colRect;
	Rect m_leftRect;
	Rect m_rightRect;

};

