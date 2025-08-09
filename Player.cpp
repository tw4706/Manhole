#include "Player.h"
#include "SceneMain.h"
#include"Dxlib.h"
#define _DEBUG

namespace
{
	// �v���C���[�T�C�Y
	constexpr float kPlayerSize = 48.0f;
	// �v���C���[�O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 48;
	constexpr int kGraphHeight = 48;
	// �A�j���[�V�������
	constexpr int kIdleAnimNum = 4;
	constexpr int kAnimWaitFrame = 4;
	constexpr int kRunAnimNum = 6;
	constexpr int kAttackAnimNum = 8;
	constexpr int kWeakAttackAnimNum = 6;
	constexpr int kHurtAnimNum = 2;	
	// �U���N�[���^�C��
	constexpr int kAttackCoolTime = 30;
	constexpr int kWeakAttackCoolTime = 20;
	//���U���̏�������
	constexpr int kAttackPrep = 20;
	// �U�����󂯂���̖��G����
	constexpr int kHurtDuration = 30;
	constexpr int kWeakHurtDuration = 15;
	// �����蔻��̔��a
	constexpr float kDefaultRadius = 16.0f;
	// �v���C���[�̈ړ����x
	constexpr int  kSpeed = 2;
	// �v���C���[�̊g�嗦
	constexpr float kScale = 2.0f;
	// �m�b�N�o�b�N�̋���
	constexpr int knockBackDist = 60;
	// �d��
	constexpr float kGravity = 1.5f;
	// �n�ʂ̓����蔻��
	constexpr int kGround = 400;
}

Player::Player():
	m_handle(-1),
	m_attackHandle(-1),
	m_wAttackHandle(-1),
	m_runHandle(-1),
	m_hurtHandle(-1),
	m_padType(0),
	m_radius(0.0f),
	m_isAttack(false),
	m_attackCount(0),
	m_wAttackCount(0),
	m_attackPrepCount(0),
	m_hurtCount(0),
	m_isTurn(false),
	m_animFrame(0),
	m_oldInput(0),
	m_state(PlayerState::Idle),
	m_attackType(AttackType::Normal),
	m_otherPlayer(nullptr)
{
}

Player::~Player()
{

}

void Player::Init(int _padType, Vec2 _firstPos,int _handle,int _attackHandle,int _wAttackHandle,int _runHandle,int _hurtHandle,bool _isTurn)
{
	// ������
	m_handle = _handle;
	m_attackHandle = _attackHandle;
	m_wAttackHandle = _wAttackHandle;
	m_runHandle = _runHandle;
	m_hurtHandle = _hurtHandle;
	m_pos = _firstPos;
	m_padType = _padType;
	m_radius = kDefaultRadius;
	m_isAttack = false;
	m_attackCount = 0;
	m_wAttackCount = 0;
	m_attackPrepCount = 0;
	m_hurtCount = 0;
	m_isTurn = _isTurn;
	m_animFrame = 0;
	m_oldInput = 0;
	m_state = PlayerState::Idle;
	m_attackType = AttackType::Normal;
}

void Player::End()
{
}

void Player::Update()
{
	// �d��
	Gravity();
	//	�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int input = GetJoypadInputState(m_padType);
	// �v���C���[�̏�Ԃ̍X�V
	UpdateState(input);
	// �v���C���[�̃A�j���[�V�����̍X�V
	UpdateAnim();
	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kPlayerSize, kPlayerSize);
	// �d�͂̐���
	if (m_pos.y >= kGround)
	{
		m_pos.y = kGround;
	}

}

void Player::Draw()
{
	// �A�j���[�V�����̃t���[��������\���������R�}�ԍ����v�Z�ŋ��߂�
	int animNum = 0;
	//// �v���C���[�̂��ꂼ��̏�Ԃ����Ƃ�X���W���v�Z����
	int srcX = 0;
	int srcY = 0;
	int handle = m_handle;

	// �v���C���[�̏�Ԃɉ����ăA�j���[�V�����̃n���h����ݒ�
	switch (m_state)
	{
	case PlayerState::Idle:
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_handle;
		srcY = 0;
		break;

	case PlayerState::Run:
		animNum = (m_animFrame / kAnimWaitFrame) % kRunAnimNum;
		handle = m_runHandle;
		srcY = 0;
		break;

	case PlayerState::Attack:
		animNum = (m_animFrame / kAnimWaitFrame) % kAttackAnimNum;
		handle = m_attackHandle;
		srcY = 0;
		break;

	case PlayerState::WeakAttack:
		animNum = (m_animFrame / kAnimWaitFrame) % kWeakAttackAnimNum;
		handle = m_wAttackHandle;
		srcY = 0;
		break;

	case PlayerState::Hurt:
		animNum = (m_animFrame / kAnimWaitFrame) % kHurtAnimNum;
		handle = m_hurtHandle;
		srcY = 0;
		break;
	}

	srcX = kGraphWidth * animNum;

	// �v���C���[�̕`�揈��
	if (handle != -1)
	{
		if (m_isTurn) 
		{ 
			// ������
			DrawRectExtendGraph(
				static_cast<int>(m_pos.x) + 96, static_cast<int>(m_pos.y),
				static_cast<int>(m_pos.x), static_cast<int>(m_pos.y) + 96,
				srcX, srcY,
				48, 48,
				handle, TRUE);
		}
		else 
		{
			// �E����
			DrawRectExtendGraph(
				static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
				static_cast<int>(m_pos.x) + kGraphWidth*kScale,
				static_cast<int>(m_pos.y) + kGraphHeight*kScale,
				srcX, srcY,
				kGraphWidth, kGraphHeight,
				handle, TRUE);
		}
	}
	float drawX = m_pos.x + kPlayerSize * 0.5f;
	float drawY = m_pos.y + kPlayerSize * 0.5f;
#ifdef _DEBUG
	if (m_isTurn)
	{
		DrawGraphF(drawX, drawY, handle, TRUE);
	}
	else
	{
		DrawTurnGraphF(drawX, drawY, handle, TRUE);
	}
	// �����蔻��̕\��
	m_colRect.Draw(0xFFFF00, false);

#endif

	

}

void Player::Gravity()
{
	// �d�͂�ǉ�����
	m_pos.y += kGravity;
}

// �v���C���[�̏�Ԃ��X�V����֐�
void Player::UpdateState(int _input)
{
	// �v���C���[�̏�Ԃ�ۑ�
	PlayerState saveState = m_state;
	// �U���̃g���K�[���`�F�b�N
	bool attackTrigger = (_input & PAD_INPUT_A) && !(m_oldInput & PAD_INPUT_A);
	// ��U���̃g���K�[���`�F�b�N
	bool weakAttackTrigger = (_input & PAD_INPUT_B) && !(m_oldInput & PAD_INPUT_B);

	// �v���C���[�̏�Ԃ��X�V����
	switch (m_state) 
	{
	case PlayerState::Idle:
		if (!m_isAttack && IsMoving(_input))
		{
			m_state = PlayerState::Run;
		}
		else if (!m_isAttack && (_input & PAD_INPUT_A)) 
		{
			m_state = PlayerState::AttackPrep;
			m_attackCount = 0;
			m_isAttack = true;
			printfDx("�U�������I\n");
		}
		else if (!m_isAttack && (_input & PAD_INPUT_B)) 
		{
			printfDx("B�{�^�����������I\n");
			m_attackType = AttackType::Weak;
			m_wAttackCount = 0;
			m_isAttack = true;
			m_state = PlayerState::WeakAttack;
			printfDx("��U�������I\n");
		}

		break;
	case PlayerState::AttackPrep:
		m_attackPrepCount++;
		if (m_attackPrepCount >= kAttackPrep)
		{
			m_state = PlayerState::Attack;
			m_attackPrepCount = 0;
			m_attackType = AttackType::Normal;
			printfDx("���U���̏�������!\n");
		}
		break;

	case PlayerState::Run:
		// �ړ�����
		if (_input & PAD_INPUT_LEFT && !(_input & PAD_INPUT_RIGHT)) 
		{
			m_pos.x -= kSpeed;
			m_isTurn = true;
		}
		if (_input & PAD_INPUT_RIGHT && !(_input & PAD_INPUT_LEFT)) 
		{
			m_pos.x += kSpeed;
			m_isTurn = false;
		}
		if (!IsMoving(_input)) 
		{
			m_state = PlayerState::Idle;
		}
		break;

	case PlayerState::Attack:
		m_attackCount++;

		// �U��
		// �������u�Ԕ��肷��
		if (!m_isAttack && attackTrigger)
		{
			m_state = PlayerState::Attack;
			m_attackCount = 0;
			m_isAttack = true;
			printfDx("�U���I\n");
		}
		if (m_attackCount == 1)
		{
			// �ŏ��̃t���[���ōU���̔�����s��
			KnockBack();
		}
		// �U���̃J�E���g���N�[���^�C���𒴂�����
		if (m_attackCount > kAttackCoolTime) 
		{
			m_isAttack = false;
			m_attackType = AttackType::Normal;
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			// �U���J�E���g�����Z�b�g
			m_attackCount = 0; 
		}
		break;
	case PlayerState::WeakAttack:	// ��U��
		m_wAttackCount++;
		if (!m_isAttack && weakAttackTrigger)
		{
			m_state = PlayerState::WeakAttack;
			m_attackCount = 0;
			m_isAttack = true;
			printfDx("��p���`�I\n");
		}
		if (m_wAttackCount == 1) 
		{
			m_attackType = AttackType::Weak;
			// ��U���̃m�b�N�o�b�N
			KnockBack();
		}
		if (m_wAttackCount > kWeakAttackCoolTime)
		{
			m_isAttack = false;
			m_attackType = AttackType::Normal;// �U���^�C�v��ʏ�ɖ߂�
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			m_wAttackCount = 0;
		}
		break;
	case PlayerState::Hurt:	// �U�����󂯂����
		m_hurtCount++;
		if ((m_attackType == AttackType::Weak && m_hurtCount > kWeakHurtDuration) || (m_attackType == AttackType::Normal &&m_hurtCount > kHurtDuration))
		{
			m_state = PlayerState::Idle;
			m_hurtCount = 0;
			m_attackType = AttackType::Normal; // ��ԃ��Z�b�g
		}
	}

	// ��Ԃ��؂�ւ������A�j���[�V�����t���[�������Z�b�g
	if (saveState != m_state) 
	{
		m_animFrame = 0;
	}
	m_oldInput = _input; // �O��̓��͏�Ԃ��X�V
}

// �v���C���[�̈ړ����]����
bool Player::IsMoving(int _input)
{
	return (_input & PAD_INPUT_LEFT) || (_input & PAD_INPUT_RIGHT);
}

// �v���C���[�̃A�j���[�V����
void Player::UpdateAnim()
{
	int animFrames = 0;
	switch (m_state)
	{
	case PlayerState::Idle:
		animFrames = kIdleAnimNum;
		break;
	case PlayerState::AttackPrep:
		animFrames = 1; 
		break;
	case PlayerState::Run:
		animFrames = kRunAnimNum;
		break;
	case PlayerState::Attack:
		animFrames = kAttackAnimNum;
		break;
	case PlayerState::WeakAttack:
		animFrames = kWeakAttackAnimNum;
		break;
	case PlayerState::Hurt:
		animFrames = kHurtAnimNum;
		break;
	}

	if (m_animFrame++ >= animFrames * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}
}

//�v���C���[�̍U��(�m�b�N�o�b�N)����
void Player::KnockBack()
{
	if (!m_otherPlayer) return;

	float dx = m_otherPlayer->m_pos.x - m_pos.x;
	float dy = m_otherPlayer->m_pos.y - m_pos.y;
	float dist = dx * dx + dy * dy;
	float hitRadius = m_radius + m_otherPlayer->m_radius;
	float knockBackValue = knockBackDist;
	// �U���̎�ނɂ��m�b�N�o�b�N�̒���
	if (m_attackType == AttackType::Weak)
	{
		// ��U��
		knockBackValue *= 0.35f;
	}

	if (dist <= hitRadius * hitRadius)
	{
		// �U�������Ńm�b�N�o�b�N
		if (m_isTurn)
		{
			// �v���C���[���������Ȃ獶�Ƀm�b�N�o�b�N
			m_otherPlayer->m_pos.x -= knockBackValue;
		}
		else
		{
			// �v���C���[���E�����Ȃ�E�Ƀm�b�N�o�b�N
			m_otherPlayer->m_pos.x += knockBackValue;
		}
		m_otherPlayer->m_state = PlayerState::Hurt;
		m_otherPlayer->m_hurtCount = 0;

		// �U���Ώۂ̏�Ԃ� Hurt �ɕύX
		m_otherPlayer->m_state = PlayerState::Hurt;
		// �ǂ̍U������ݒ�
		m_otherPlayer->m_attackType = m_attackType;
		// �U�����󂯂����̃A�j���[�V�����t���[�������Z�b�g
		m_otherPlayer->m_animFrame = 0; 
		printfDx("�m�b�N�o�b�N (%s)!\n", m_attackType == AttackType::Weak ? "��" : "��");
	}
}
