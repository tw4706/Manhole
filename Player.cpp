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
	// �ҋ@�A�j���[�V�������
	constexpr int kIdleAnimNum = 4;
	constexpr int kAnimWaitFrame = 4;
	// ����A�j���[�V�������
	constexpr int kRunAnimNum = 6;
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
	m_runHandle(-1),
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

void Player::Init(int _padType, Vec2 _firstPos,int _handle,int _attackHandle,int _runHandle)
{
	m_handle = _handle;
	m_attackHandle = _attackHandle;
	m_runHandle = _runHandle;
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
	bool isMoving = false;
	Gravity();

	// �A�j���[�V�����̍X�V
	int animNum = 0;
	int animFrames = (m_state == PlayerState::Run) ? kRunAnimNum : kIdleAnimNum;

	// �t���[������Ԃɉ����Čv�Z
	animNum = (m_animFrame / kAnimWaitFrame) % animFrames;

	// �A�j���[�V�����t���[���̃��Z�b�g
	if (++m_animFrame >= (animFrames * kAnimWaitFrame)) {
		m_animFrame = 0;
	}

	if (m_pos.y >= kGround)
	{
		m_pos.y = kGround;
	}

	//	�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int input = GetJoypadInputState(m_padType);
	

	// �v���C���[�̏��
	if (input == DX_INPUT_PAD2)
	{
		m_isTurn = false; // �E���̃v���C���[�͏�ɉE����
	}

	// �ړ�����

	if (input & PAD_INPUT_LEFT && !(input & PAD_INPUT_RIGHT))
	{
		m_pos.x -= kSpeed;
		m_isTurn = true;
		isMoving = true;
		
	}
	if (input & PAD_INPUT_RIGHT && !(input & PAD_INPUT_LEFT))
	{
		m_pos.x += kSpeed;
		m_isTurn = false;
		isMoving = true;
		
	}
	if (!isMoving) 
	{
		
	}
	DrawFormatString(10, 10, GetColor(255, 255, 255), "isMoving: %d", isMoving); // �X�V��̒l�\��

	// ��Ԕ���
	if (m_isAttack&&input & PAD_INPUT_A)
	{
		m_state = PlayerState::Attack;
		m_attackCount = 0;
		m_isAttack = true;
	}
	else if (isMoving)
	{
		m_state = PlayerState::Run;
	}
	else
	{
		m_state = PlayerState::Idle;
	}


	//�v���C���[�̏�Ԃ̏�������
	switch (m_state)
	{
	case PlayerState::Idle:
			// �ʏ��Ԃ̏���
			break;
	case PlayerState::Run:
		if (input & PAD_INPUT_LEFT&& !(input & PAD_INPUT_RIGHT))
		{
			m_pos.x -= kSpeed;
			m_isTurn = true; // ���Ɉړ���������������ɂ���
		}
		if (input & PAD_INPUT_RIGHT && !(input & PAD_INPUT_LEFT))
		{
			m_pos.x += kSpeed;
			m_isTurn = false; // �E�Ɉړ�������������E�ɂ���
		}
		break;
	case PlayerState::Attack:
		m_attackCount++;	//�U���̃J�E���g��i�߂�
		if (m_attackCount > 60) 
		{
			// �U����Ԃ��I��
			m_isAttack = false; 
			// �U�����I�������ʏ��Ԃɖ߂�
			m_state = PlayerState::Idle; 
		}
		break;
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
		srcY = kGraphHeight;
		break;

	case PlayerState::Attack:
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_attackHandle;
		srcY = 0;
		break;
	}

	srcX = kGraphWidth * animNum;
	if (handle != -1)
	{
		DrawRectGraph(
			m_pos.x - kGraphWidth / 2,
			m_pos.y - kGraphHeight / 2,
			srcX, srcY,
			kGraphWidth, kGraphHeight,
			handle, TRUE
		);
	}
	// �f�o�b�O�\���i��ԂƃA�j���[�V�����ԍ��j
	DrawFormatString(10, 190, GetColor(255, 255, 255), "Current State: %d", m_state);
}

void Player::Gravity()
{
	// �d�͂�ǉ�����
	m_pos.y += kGravity;
}
