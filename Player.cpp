#include "Player.h"
#include "SceneMain.h"
#include"Dxlib.h"
#include <vector>
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
	constexpr int  kSpeed = 6;
	// �v���C���[�̊g�嗦
	constexpr float kScale = 2.0f;
	// �m�b�N�o�b�N�̋���
	constexpr int knockBackDist = 60;
	// �d��
	constexpr float kGravity = 1.5f;
	// �n�ʂ̓����蔻��
	constexpr int kGround = 400;
	// �����U���Ə�ԑJ�ڂ̋�����������邽�߂̍\����
	struct PendingHit
	{
		Player* attacker;
		Player* target;
		AttackType type;
	};
	std::vector<PendingHit> pendingHits;

}

Player::Player():
	m_handle(-1),
	m_attackHandle(-1),
	m_wAttackHandle(-1),
	m_runHandle(-1),
	m_hurtHandle(-1),
	m_pos(0.0f, 0.0f),
	m_centerPos(0.0f, 0.0f),
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
	m_isFalling(false),
	m_fallSpeed(0.0f),
	m_gameOver(false),
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
	m_centerPos = Vec2(0.0f, 0.0f);
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
	m_isFalling = false;
	m_fallSpeed = 0.0f;
	m_gameOver = false;
	m_state = PlayerState::Idle;
	m_attackType = AttackType::Normal;
}

void Player::End()
{
}

void Player::Update()
{
	// �����̃R�[�h
	if (m_state == PlayerState::Hurt)
	{
		m_hurtCount++;
	}
	if (ShouldTriggerHit()) 
	{
		pendingHits.push_back({ this, m_otherPlayer, m_attackType });
		printfDx("�U�����ǉ�����܂����I\n");
	}

	// �S�v���C���[�̍X�V��ɍU����K�p
	for (auto& hit : pendingHits) 
	{
		if (hit.target->CanBeHit()) 
		{
			hit.target->ApplyHit(hit.type,hit.attacker);
		}
	}
	pendingHits.clear();

	// �������̏���
	if (m_isFalling)
	{
		printfDx("�����Ă��܂�!");
		m_fallSpeed += 6.0f * kGravity;
		m_pos.y += m_fallSpeed;

		if (m_pos.x > 750)
		{
			m_isFalling = false;
			m_fallSpeed = 0.0f;
		}
	}
	else
	{
		// �ʏ�̏d�͏���
		Gravity();

		// �ʏ�̓����蔻��
		if (m_isTurn)
		{
			m_colRect.init(m_pos.x - kGraphWidth / 2 + 64.0f,
				m_pos.y - kGraphHeight / 2 + 48.0f,
				kGraphWidth, kGraphHeight);
		}
		else
		{
			m_colRect.init(m_pos.x - kGraphWidth / 2 + 32.0f,
				m_pos.y - kGraphHeight / 2 + 48.0f,
				kGraphWidth, kGraphHeight);
		}
	}
	//	�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int input = GetJoypadInputState(m_padType);
	// �v���C���[�̏�Ԃ̍X�V
	UpdateState(input);
	// �v���C���[�̃A�j���[�V�����̍X�V
	UpdateAnim();
	// �d�͂̐���
	if (!m_isFalling&&m_pos.y >= kGround)
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
	case PlayerState::Idle:			// �ҋ@��
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_handle;
		srcY = 0;
		break;

	case PlayerState::Run:			// �ړ���
		animNum = (m_animFrame / kAnimWaitFrame) % kRunAnimNum;
		handle = m_runHandle;
		srcY = 0;
		break;

	case PlayerState::Attack:		// ���U��
		animNum = (m_animFrame / kAnimWaitFrame) % kAttackAnimNum;
		handle = m_attackHandle;
		srcY = 0;
		break;

	case PlayerState::WeakAttack:	// ��U��
		animNum = (m_animFrame / kAnimWaitFrame) % kWeakAttackAnimNum;
		handle = m_wAttackHandle;
		srcY = 0;
		break;

	case PlayerState::Hurt:			// �U�����󂯂����
		animNum = (m_animFrame / kAnimWaitFrame) % kHurtAnimNum;
		handle = m_hurtHandle;
		srcY = 0;
		break;
	}

	// �A�j���[�V������X���W�����߂�
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
#ifdef _DEBUG
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

		// ���U���̏������
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
		// �ŏ��̃t���[���ōU���̔�����s��
		if (ShouldTriggerHit()) 
		{
			pendingHits.push_back({ this, m_otherPlayer, AttackType::Normal });
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

		if (ShouldTriggerHit()) 
		{
			pendingHits.push_back({ this, m_otherPlayer, AttackType::Normal });
		}

		if (m_wAttackCount > kWeakAttackCoolTime)
		{
			// �N�[���^�C���𒴂�����ʏ��Ԃɖ߂�
			m_isAttack = false;
			m_attackType = AttackType::Normal;// �U���^�C�v��ʏ�ɖ߂�
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			m_wAttackCount = 0;
		}
		break;
	case PlayerState::Hurt:
		// �U�����󂯂���̖��G���Ԃ��o�߂�����ʏ��Ԃɖ߂�
		if ((m_attackType == AttackType::Weak && m_hurtCount > kWeakHurtDuration) ||
			(m_attackType == AttackType::Normal && m_hurtCount > kHurtDuration))
		{
			m_state = PlayerState::Idle;
			m_hurtCount = 0;
			m_attackType = AttackType::Normal;
			printfDx("Hurt�I��\n");
			m_oldInput = _input; // �O��̓��͏�Ԃ��X�V
		}
		break;
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

	// �A�j���[�V�����t���[�����X�V
	if (m_animFrame++ >= animFrames * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}
}

// �v���C���[�̓����蔻����擾����֐�
const Rect& Player::GetCollisionRect() const
{
	return m_colRect;
}

// ���G���Ԃ��c���Ă���Ȃ�U�����󂯂Ȃ�
bool Player::CanBeHit() const
{
	if (m_state == PlayerState::Hurt)return true;
	if ((m_attackType == AttackType::Weak && m_hurtCount < kWeakHurtDuration) ||
		(m_attackType == AttackType::Normal && m_hurtCount < kHurtDuration)) 
	{
		return false; // ���G���Ԓ�
	}
	return true;
}

// �U��������o���ׂ����𔻒肷��֐�
bool Player::ShouldTriggerHit() const
{
	if (m_state == PlayerState::Attack && m_attackCount == 1) return true;
	if (m_state == PlayerState::WeakAttack && m_wAttackCount == 1) return true;

	return false;
}

void Player::ApplyHit(AttackType _type,const Player*_attacker)
{
	if (!CanBeHit()) return;

	float knockBackValue = knockBackDist;
	if (_type == AttackType::Weak)
	{
		knockBackValue *= 0.35f;
	}

	if (_attacker->m_isTurn) 
	{
		m_pos.x += knockBackValue; // �U���҂������� �� ������E�ɐ�����΂�
		printfDx("�m�b�N�o�b�N: �E�� %.2f �ړ�\n", knockBackValue);
	}
	else 
	{
		m_pos.x -= knockBackValue; // �U���҂��E���� �� ��������ɐ�����΂�
		printfDx("�m�b�N�o�b�N: ���� %.2f �ړ�\n", knockBackValue);
	}

	m_state = PlayerState::Hurt;
	m_attackType = _type;
	m_hurtCount = 0;
	m_animFrame = 0;
}

bool Player::IsFalling() const
{
	return m_isFalling;
}


void Player::DisableCollision()
{
	m_colRect.init(-9999, -9999, 0, 0);
}
