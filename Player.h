#pragma once
#include"Vec2.h"

enum class PlayerState
{
	Idle,		// �ҋ@
	Run,		// ����
	Attack,		// �U��
};

class Player
{
public:
	Player();
	~Player();

	void Init(int _padType,Vec2 _firstPos,int _handle,int _attackHandle,int _runHandle);
	void End();
	void Update();
	void Draw();
	void Gravity();	// �d��

	// �����蔻��̏��
	float GetPosX() const { return m_pos.x; }	// X���W���擾
	float GetPosY() const { return m_pos.y; }	// Y���W���擾
	float GetPosRadius() const { return m_radius; }	// ���a���擾

	void Updatestate(int _input);	// �v���C���[�̏�ԊǗ�
	bool IsMoving(int _input);	// �v���C���[�̈ړ�
	void UpdateAnim();	// �v���C���[�̃A�j���[�V�����Ǘ�


	// �A�h�o�C�X:�֐��͓�������n�߂�
	//�@UpdateAnim
	//�@UpdateState


private:

	int m_handle;		// �O���t�B�b�N�̃n���h��
	int m_attackHandle;	// �U���̃O���t�B�b�N�̃n���h��
	int m_runHandle;	// ����O���t�B�b�N�̃n���h��
	Vec2 m_pos;			// ���W
	int m_padType;		// �p�b�h�̎��
	float m_radius;		// �����蔻��̔��a
	bool m_isAttack;	// �U�������ǂ���
	int m_attackCount;	// �U���̃J�E���g
	bool m_isTurn;		// ���E���]
	int m_animFrame;	// �A�j���[�V�����̃t���[��
	PlayerState m_state;// �v���C���[�̏��
};

