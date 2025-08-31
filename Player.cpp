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
	// �����蔻��̔��a
	constexpr float kDefaultRadius = 16.0f;
	// �v���C���[�̈ړ����x
	constexpr int  kSpeed = 2;

}

Player::Player():
	m_padType(0),
	m_radius(0.0f),
	m_isTurn(false)
{
}

Player::~Player()
{
}

void Player::Init(int _padType, Vec2 _firstPos)
{
	m_pos = _firstPos;
	m_padType = _padType;
	m_radius = kDefaultRadius;
	m_isTurn = false;
}

void Player::End()
{
}

void Player::Update()
{
	//	�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int input = GetJoypadInputState(m_padType);

	//	�R���g���[���[�̏\���L�[�̉����ꂽ��Ԃ��擾����
	if (input == PAD_INPUT_LEFT)
	{
		m_pos.x -= kSpeed;
	}
	if (input == PAD_INPUT_RIGHT)
	{
		m_pos.x += kSpeed;
	}
}

void Player::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, m_radius, GetColor(255, 255, 0),true);
}
