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
	m_padType(0),
	m_radius(0.0f),
	m_isTurn(false),
	m_animFrame(0)
{
}

Player::~Player()
{

}

void Player::Init(int _padType, Vec2 _firstPos,int _handle)
{
	m_handle = _handle;
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

	//	�R���g���[���[�̏\���L�[�̉����ꂽ��Ԃ��擾����
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
}

void Player::Draw()
{
	// �A�j���[�V�����̃t���[��������\���������R�}�ԍ����v�Z�ŋ��߂�
	int animNum = m_animFrame / kAnimWaitFrame;

	// �A�j���[�V�����̐i�s�ɍ��킹�ăO���t�B�b�N�̐؂���ʒu��ύX����
	int srcX = kGraphWidth * animNum;
	int srcY = 0;
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
	/*DrawRectGraph(m_pos.x - kGraphWidth / 2,
				m_pos.y - kGraphHeight / 2,
				srcX, srcY,
				kGraphWidth, kGraphHeight,
				m_handle, true,true
				);*/
}

void Player::Gravity()
{
	// �d�͂�ǉ�����
	m_pos.y += kGravity;
}
