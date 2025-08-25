#pragma once
#include"Rect.h"
#include"DxLib.h"
#include"Vec2.h"
#include<vector>

enum class PlayerState
{
	Idle,		// �ҋ@
	Run,		// ����
	AttackPrep,	// ���U������
	Attack,		// ���U��
	WeakAttack,	// ��U��
	Hurt,		// �U�����󂯂�
};

enum class AttackType
{
	Normal,		// ���U��
	Weak,		// ��U��
};

class Player; // �O���錾

// �U�����ꎞ�ۑ����邽�߂̍\����
struct Attack
{
	Player* attacker;
	Player* target;
	int priority;   // ���U���قǍ���
	int hitFrame;   // �U�������������t���[��
};

class Player
{
public:
	Player();
	~Player();

	void Init(int _padType,Vec2 _firstPos,int _handle,int _attackHandle,int _wAttackHandle,int _runHandle,int _hurtHandle,bool _isTurn);
	void End();
	void Update();
	void Draw();
	void Gravity();	// �d��

	void UpdateState(int _input);									// �v���C���[�̏�ԊǗ�
	bool IsMoving(int _input);										// �v���C���[�̈ړ�
	void UpdateAnim();												// �v���C���[�̃A�j���[�V�����Ǘ�
	void SetOtherPlayer(Player* other) { m_otherPlayer = other; }	// �U���Ώۂ̎擾
	void KnockBack();												// �m�b�N�o�b�N����
	const Rect& GetCollisionRect() const;							// �����蔻����擾���邽�߂�getter�֐�
	bool IsHurt()const;
	void SetGameOver(bool isOver) { m_gameOver = isOver; }			// �Q�[���I�[�o�[�̔���
	void SetFalling(bool isFalling) { m_isFalling = isFalling; }	// �������̔���
	bool IsFalling()const;											// ���������ǂ����̔���
	// ��y����̃A�h�o�C�X:�֐��͓�������n�߂�
	//�@UpdateAnim
	//�@UpdateState


private:

	int m_handle;				// �O���t�B�b�N�̃n���h��
	int m_attackHandle;			// ���U���̃O���t�B�b�N�̃n���h��
	int m_wAttackHandle;		// ��U���̃O���t�B�b�N�̃n���h��
	int m_runHandle;			// ����O���t�B�b�N�̃n���h��
	int m_hurtHandle;			// �U�����󂯂����̃O���t�B�b�N�̃n���h��
	Vec2 m_pos;					// ���W
	Vec2 m_centerPos;			// �����蔻��̃T�C�Y���W
	int m_padType;				// �p�b�h�̎��
	float m_radius;				// �����蔻��̔��a
	bool m_isAttack;			// �U�������ǂ���
	int m_attackCount;			// ���U���̃J�E���g
	int m_wAttackCount;			// ��U���̃J�E���g
	int m_attackPrepCount;		// ���U���̏����̃J�E���g
	int m_hurtCount;			// �U�����󂯂��J�E���g
	bool m_isTurn;				// ���E���]
	int m_animFrame;			// �A�j���[�V�����̃t���[��
	int m_oldInput;				// �O��̓���
	bool m_isFalling;			// ���������ǂ���
	float m_fallSpeed;			// �������x
	bool m_gameOver;			// �Q�[���I�[�o�[���ǂ���
	int m_currentFrame;			// ���݂̃t���[����
	PlayerState m_state;		// �v���C���[�̏��
	AttackType m_attackType;	// �U���̎��
	Player* m_otherPlayer;		// �ΐ푊��̃v���C���[(�U���̑ΏۂƂȂ�)
	std::vector<Attack> m_pendingAttacks;

protected:
	// �����蔻��̋�`
	Rect m_colRect;	
};

