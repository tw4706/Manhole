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
	// �v���C���[�̍U���A�j���[�V�������
	constexpr int kAttackAnimNum = 6;
	// �v���C���[�̍U���N�[���^�C��
	constexpr int kAttackCoolTime = 30;
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
	Gravity();
	//	�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int input = GetJoypadInputState(m_padType);
	// �v���C���[�̏�Ԃ̍X�V
	Updatestate(input);
	// �v���C���[�̃A�j���[�V�����̍X�V
	UpdateAnim();


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
	}

	srcX = kGraphWidth * animNum;


	if (handle != -1)
	{
		DrawRectGraph(
			m_pos.x - kGraphWidth / 2,
			m_pos.y - kGraphHeight / 2,
			srcX, srcY,
			kGraphWidth, kGraphHeight,
			handle, TRUE, m_isTurn
		);
	}
	// �����蔻��̕\��
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), static_cast<int>(m_radius), GetColor(255, 0, 0), FALSE);
	// �f�o�b�O�\��
	static PlayerState testState= m_state;
	if (testState != m_state) {
		DrawFormatString(10, 80, GetColor(255, 0, 0), "State Changed: %d -> %d", testState, m_state);
		testState = m_state;
	}
}

void Player::Gravity()
{
	// �d�͂�ǉ�����
	m_pos.y += kGravity;
}

void Player::Updatestate(int _input)
{
	PlayerState prevState = m_state; // ���݂̏�Ԃ��ꎞ�ۑ�

	switch (m_state) {
	case PlayerState::Idle:
		if (!m_isAttack && IsMoving(_input)) {
			m_state = PlayerState::Run;
		}
		else if (!m_isAttack && (_input & PAD_INPUT_A)) {
			m_state = PlayerState::Attack;
			m_attackCount = 0;
			m_isAttack = true;
			printfDx("�U�������I\n");
		}
		break;

	case PlayerState::Run:
		// �ړ�����
		if (_input & PAD_INPUT_LEFT && !(_input & PAD_INPUT_RIGHT)) {
			m_pos.x -= kSpeed;
			m_isTurn = true;
		}
		if (_input & PAD_INPUT_RIGHT && !(_input & PAD_INPUT_LEFT)) {
			m_pos.x += kSpeed;
			m_isTurn = false;
		}

		if (!IsMoving(_input)) {
			m_state = PlayerState::Idle;
		}
		break;

	case PlayerState::Attack:
		m_attackCount++;
		if (m_attackCount > kAttackCoolTime) {
			m_isAttack = false;
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
		}
		break;
	}

	// ��Ԃ��؂�ւ������A�j���[�V�����̃t���[�������Z�b�g
	if (prevState != m_state) {
		m_animFrame = 0;
	}


}

bool Player::IsMoving(int _input)
{
	return (_input & PAD_INPUT_LEFT) || (_input & PAD_INPUT_RIGHT);

}

void Player::UpdateAnim()
{
	int animFrames = 0;
	switch (m_state)
	{
	case PlayerState::Idle:
		animFrames = kIdleAnimNum;
		break;
	case PlayerState::Run:
		animFrames = kRunAnimNum;
		break;
	case PlayerState::Attack:
		animFrames = kAttackAnimNum;
		break;
	}

	if (++m_animFrame >= animFrames * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}

}
