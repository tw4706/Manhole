#pragma once
#include"Vec2.h"

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
};;

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

	// �����蔻��̏��
	float GetPosX() const { return m_pos.x; }	// X���W���擾
	float GetPosY() const { return m_pos.y; }	// Y���W���擾
	float GetPosRadius() const { return m_radius; }	// ���a���擾

	void UpdateState(int _input);	// �v���C���[�̏�ԊǗ�
	bool IsMoving(int _input);	// �v���C���[�̈ړ�
	void UpdateAnim();	// �v���C���[�̃A�j���[�V�����Ǘ�
	// �U���Ώۂ̎擾
	void SetOtherPlayer(Player* other) { m_otherPlayer = other; }
	void KnockBack();	// �m�b�N�o�b�N����


	// �A�h�o�C�X:�֐��͓�������n�߂�
	//�@UpdateAnim
	//�@UpdateState


private:

	int m_handle;				// �O���t�B�b�N�̃n���h��
	int m_attackHandle;			// ���U���̃O���t�B�b�N�̃n���h��
	int m_wAttackHandle;		// ��U���̃O���t�B�b�N�̃n���h��
	int m_runHandle;			// ����O���t�B�b�N�̃n���h��
	int m_hurtHandle;			// �U�����󂯂����̃O���t�B�b�N�̃n���h��
	Vec2 m_pos;					// ���W
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
	PlayerState m_state;		// �v���C���[�̏��
	AttackType m_attackType;	// �U���̎��
	Player* m_otherPlayer;		// �ΐ푊��̃v���C���[(�U���̑ΏۂƂȂ�)
};

