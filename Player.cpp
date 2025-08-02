#include "Player.h"
#include "SceneMain.h"
#include"Dxlib.h"

namespace
{
	// �v���C���[�̃X�^�[�g�ʒu
	constexpr int kPlayer1StartX = 240;
	constexpr int kPlayer1StartY = 480;
	// �v���C���[2�̃X�^�[�g�ʒu
	constexpr int kPlayer2StartX = 480;
	constexpr int kPlayer2StartY = 480;
	// �v���C���[�O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 48;
	constexpr int kGraphHeight = 48;
	// �A�j���[�V�������
	constexpr int kIdleAnimNum = 4;
	constexpr int kAnimWaitFrame = 4;
	// �����蔻��̔��a
	constexpr float kDefaultRadius = 16.0f;
	// �v���C���[�̈ړ����x
	constexpr int  kSpeed = 2;
	// �d��
	constexpr float kGravity = 1.5f;
	// �n�ʂ̓����蔻��
	constexpr int kGround = 530;

}

Player::Player():
	m_handle(-1),
	m_attackHandle(-1),
	m_padType(0),
	m_radius(0.0f),
	m_isAttack(false),
	m_attackCount(0),
	m_isTurn(false),
	m_animFrame(0),
	m_state(PlayerState::Idle)
{
}

Player::~Player()
{

}

void Player::Init(int _padType, Vec2 _firstPos,int _handle,int _attackHandle)
{
	m_handle = _handle;
	m_attackHandle = _attackHandle;
	m_pos = _firstPos;
	m_padType = _padType;
	m_radius = kDefaultRadius;
	m_isAttack = false;
	m_attackCount = 0;
	m_isTurn = false;
}

void Player::End()
{
}

void Player::Update()
{
	
	// �A�j���[�V�����̍X�V
	m_animFrame++;
	if (m_animFrame >= kIdleAnimNum * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}

	Gravity();

	if (m_pos.y >= kGround)
	{
		m_pos.y = kGround;
	}

	//	�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int input = GetJoypadInputState(m_padType);

	// �v���C���[�̏��
	if (input & PAD_INPUT_A)
	{
		m_state = PlayerState::Attack;
		m_attackCount = 0;
		m_isAttack = true;
	}
	else if (input & PAD_INPUT_LEFT || input & PAD_INPUT_RIGHT)
	{
		m_state = PlayerState::Run;
	}
	else
	{
		m_state = PlayerState::Idle;
	}
	switch (m_state)
	{
	case PlayerState::Idle:
			// �ʏ��Ԃ̏���
			break;
	case PlayerState::Run:
		if (input & PAD_INPUT_LEFT)
		{
			m_pos.x -= kSpeed;
			m_isTurn = true; // ���Ɉړ���������������ɂ���
		}
		if (input & PAD_INPUT_RIGHT)
		{
			m_pos.x += kSpeed;
			m_isTurn = false; // �E�Ɉړ�������������E�ɂ���
		}
		break;
	case PlayerState::Attack:
		m_attackCount++;	//�U���̃J�E���g��i�߂�
		if (m_attackCount > 20) 
		{
			// �U�����I�������ʏ��Ԃɖ߂�
			m_state = PlayerState::Idle; 
			m_isAttack = false; // �U����Ԃ��I��
		}
		break;

	}


	// �U�����[�V����

}

void Player::Draw()
{
	// �A�j���[�V�����̃t���[��������\���������R�}�ԍ����v�Z�ŋ��߂�
	int animNum = m_animFrame / kAnimWaitFrame;
	int srcX = kGraphWidth * animNum;
	int srcY = 0;
	int handle = m_handle;
	switch (m_state)
	{
		case PlayerState::Idle:
			// �ҋ@���[�V����
			srcY = 0;
			handle = m_handle;
			break;
		case PlayerState::Run:
			// �ړ����[�V����
			srcY = kGraphHeight;
			handle = m_handle;
			break;
		case PlayerState::Attack:
			// �U�����[�V����
			srcY = kGraphHeight * 2;
			handle = m_attackHandle;
			break;
	}
	if (m_padType==DX_INPUT_PAD1)
	{
		DrawRectGraph(m_pos.x - kGraphWidth / 2,
			m_pos.y - kGraphHeight / 2,
			srcX, srcY,
			kGraphWidth, kGraphHeight,
			m_handle, true, false
		);
	}
	else
	{
		DrawRectGraph(m_pos.x - kGraphWidth / 2,
			m_pos.y - kGraphHeight / 2,
			srcX, srcY,
			kGraphWidth, kGraphHeight,
			m_handle, true, true
		);
	}
}

void Player::Gravity()
{
	// �d�͂�ǉ�����
	m_pos.y += kGravity;
}
