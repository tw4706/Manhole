#include "Player.h"
#include "SceneMain.h"
#include"Dxlib.h"
#include <algorithm>

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
	constexpr int kFallAnimNum = 4;
	// �U���N�[���^�C��
	constexpr int kAttackCoolTime = 50;
	constexpr int kWeakAttackCoolTime = 30;
	//���U���̏�������
	constexpr int kAttackPrep = 10;
	// �U�����󂯂���̖��G����
	constexpr int kHurtDuration = 50;
	constexpr int kWeakHurtDuration = 20;
	// �����蔻��̔��a
	constexpr float kDefaultRadius = 16.0f;
	// �v���C���[�̈ړ����x
	constexpr int  kSpeed = 2.0;
	// �v���C���[�̊g�嗦
	constexpr float kScale = 2.0f;
	// �m�b�N�o�b�N�̋���
	constexpr int knockBackDist = 70;
	// �d��
	constexpr float kGravity = 1.5f;
	// �n�ʂ̓����蔻��
	constexpr int kGround = 400;
	// �������x�̍ő�l
	constexpr float kMaxFallSpeed = 15.0f;
	// �U������̃t���[��
	constexpr int kAttackActiveStartFrame = 3;
	constexpr int kAttackActiveEndFrame = 5;
	constexpr int kWeakAttackStartFrame = 2;
	constexpr int kWeakAttackEndFrame = 3;


}

Player::Player() :
	m_handle(-1),
	m_attackHandle(-1),
	m_wAttackHandle(-1),
	m_runHandle(-1),
	m_hurtHandle(-1),
	m_fallHandle(-1),
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
	m_currentFrame(0),
	m_hasHit(false),
	m_weakBgHandle(-1),
	m_attackBgHandle(-1),
	m_state(PlayerState::Idle),
	m_attackType(AttackType::Normal),
	m_otherPlayer(nullptr)
{
}

Player::~Player()
{

}

void Player::Init(int _padType, Vec2 _firstPos,int _handle,int _attackHandle,int _wAttackHandle,int _runHandle,int _hurtHandle,int _fallHandle,bool _isTurn)
{
	// ������
	m_handle = _handle;
	m_attackHandle = _attackHandle;
	m_wAttackHandle = _wAttackHandle;
	m_runHandle = _runHandle;
	m_hurtHandle = _hurtHandle;
	m_fallHandle = _fallHandle;
	m_pos = _firstPos;
	m_pos.y = kGround;
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
	m_currentFrame = 0;
	m_hasHit = false;
	m_weakBgHandle = LoadSoundMem("data/weak.mp3");
	m_attackBgHandle = LoadSoundMem("data/attack.mp3");
	m_state = PlayerState::Idle;
	m_attackType = AttackType::Normal;
	ChangeVolumeSoundMem(150,m_weakBgHandle);
	ChangeVolumeSoundMem(150,m_attackBgHandle);
}

void Player::End()
{
	StopSoundMem(m_weakBgHandle);
	DeleteSoundMem(m_weakBgHandle);
	StopSoundMem(m_attackBgHandle);
	DeleteSoundMem(m_attackBgHandle);
}

void Player::Update()
{
	// �d��
	Gravity();

	// �����蔻��
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

	//	�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int padInput = GetJoypadInputState(m_padType);
	int keyInput = 0;

	if (m_padType == DX_INPUT_PAD1)
	{
		if (CheckHitKey(KEY_INPUT_Z))     keyInput |= PAD_INPUT_A;
		if (CheckHitKey(KEY_INPUT_X))	keyInput |= PAD_INPUT_B;
		if (CheckHitKey(KEY_INPUT_A))  keyInput |= PAD_INPUT_LEFT;
		if (CheckHitKey(KEY_INPUT_D)) keyInput |= PAD_INPUT_RIGHT;
		if (CheckHitKey(KEY_INPUT_W))    keyInput |= PAD_INPUT_UP;
		if (CheckHitKey(KEY_INPUT_S))  keyInput |= PAD_INPUT_DOWN;
	}
	else if (m_padType == DX_INPUT_PAD2)
	{
		if (CheckHitKey(KEY_INPUT_K))     keyInput |= PAD_INPUT_A;
		if (CheckHitKey(KEY_INPUT_M))	keyInput |= PAD_INPUT_B;
		if (CheckHitKey(KEY_INPUT_LEFT))  keyInput |= PAD_INPUT_LEFT;
		if (CheckHitKey(KEY_INPUT_RIGHT)) keyInput |= PAD_INPUT_RIGHT;
		if (CheckHitKey(KEY_INPUT_UP))    keyInput |= PAD_INPUT_UP;
		if (CheckHitKey(KEY_INPUT_DOWN))  keyInput |= PAD_INPUT_DOWN;
	}
	int input = padInput | keyInput; // �����̓��͂𓝍�

	// �v���C���[�̏�Ԃ̍X�V
	UpdateState(input);
	// �v���C���[�̃A�j���[�V�����̍X�V
	UpdateAnim();
	// �d�͂̐���
	if (!m_isFalling&& !m_gameOver && m_pos.y >= kGround)
	{
		m_pos.y = kGround;
	}
	// ���U���̍U������iAttack��ԁj
	if (m_state == PlayerState::Attack &&
		m_animFrame >= kAttackActiveStartFrame &&
		m_animFrame <= kAttackActiveEndFrame)
	{
		KnockBack();
	}

	// ��U���̍U������iWeakAttack��ԁj
	if (m_state == PlayerState::WeakAttack &&
		m_animFrame >= kWeakAttackStartFrame &&
		m_animFrame <= kWeakAttackEndFrame)
	{
		KnockBack();
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
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_handle;
		srcY = 0;
		break;
	}

	case PlayerState::Run:			// �ړ���
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kRunAnimNum;
		handle = m_runHandle;
		srcY = 0;
		break;
	}

	case PlayerState::Attack:		// ���U��
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kAttackAnimNum;
		handle = m_attackHandle;
		srcY = 0;
		break;
	}

	case PlayerState::WeakAttack:	// ��U��
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kWeakAttackAnimNum;
		handle = m_wAttackHandle;
		srcY = 0;
		break;
	}

	case PlayerState::Hurt:			// �U�����󂯂����
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kHurtAnimNum;
		handle = m_hurtHandle;
		srcY = 0;
		break;
	}
	case PlayerState::Fall:			// ������
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kFallAnimNum;
		handle = m_fallHandle;
		srcY = kGraphHeight; // �����A�j���[�V������2�s�ڂɂ���Ɖ���
		break;
	}
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
			//printfDx("�U�������I\n");
		}
		else if (!m_isAttack && (_input & PAD_INPUT_B))
		{
			//printfDx("B�{�^�����������I\n");
			m_attackType = AttackType::Weak;
			m_wAttackCount = 0;
			m_isAttack = true;
			m_state = PlayerState::WeakAttack;
			//printfDx("��U�������I\n");
			PlaySoundMem(m_weakBgHandle, DX_PLAYTYPE_BACK);
		}
		break;

		// ���U���̏������
	case PlayerState::AttackPrep:
	{
		m_attackPrepCount++;
		if (m_attackPrepCount >= kAttackPrep)
		{
			m_state = PlayerState::Attack;
			PlaySoundMem(m_attackBgHandle, DX_PLAYTYPE_BACK);
			m_attackPrepCount = 0;
			m_attackType = AttackType::Normal;
			//printfDx("���U���̏�������!\n");
		}
		break;
	}

	case PlayerState::Run:
	{
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
	}

	case PlayerState::Attack:
		m_attackCount++;
		// �U��
		// �������u�Ԕ��肷��
		if (!m_isAttack && attackTrigger)
		{
			m_state = PlayerState::Attack;
			m_attackCount = 0;
			m_isAttack = true;
			//printfDx("�U���I\n");
		}

		// �U���̃J�E���g���N�[���^�C���𒴂�����
		if (m_attackCount > kAttackCoolTime)
		{
			m_isAttack = false;
			m_attackType = AttackType::Normal;
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			// �U���J�E���g�����Z�b�g
			m_attackCount = 0;
			m_hasHit = false;
		}
		break;

	case PlayerState::WeakAttack:	// ��U��
		m_wAttackCount++;
		if (!m_isAttack && weakAttackTrigger)
		{
			m_state = PlayerState::WeakAttack;
			m_attackCount = 0;
			m_isAttack = true;
			//printfDx("��p���`�I\n");
		}

		if (m_wAttackCount > kWeakAttackCoolTime)
		{
			// �N�[���^�C���𒴂�����ʏ��Ԃɖ߂�
			m_isAttack = false;
			m_attackType = AttackType::Normal;// �U���^�C�v��ʏ�ɖ߂�
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			m_wAttackCount = 0;
			m_hasHit = false;
		}
		break;
	case PlayerState::Hurt:
		m_hurtCount++;
		// �U�����󂯂���̖��G���Ԃ��o�߂�����ʏ��Ԃɖ߂�
		if ((m_receivedAttackType == AttackType::Weak && m_hurtCount > kWeakHurtDuration) ||
			(m_receivedAttackType == AttackType::Normal && m_hurtCount > kHurtDuration))
		{
			m_state = PlayerState::Idle;
			m_hurtCount = 0;
			m_receivedAttackType = AttackType::Normal;
			m_oldInput = _input;
		}
		break;

		// ��Ԃ��؂�ւ������A�j���[�V�����t���[�������Z�b�g
		if (saveState != m_state)
		{
			m_animFrame = 0;
		}
		m_oldInput = _input; // �O��̓��͏�Ԃ��X�V
		break;	
	case PlayerState::Fall:
		if (m_isFalling && m_state != PlayerState::Fall)
		{
			m_state = PlayerState::Fall;
			m_animFrame = 0; // �A�j���[�V�����t���[�������Z�b�g
			printfDx("state==%d\n", m_state);
		}

		if (m_isFalling)
		{
			//printfDx("Fall");
			m_fallSpeed += kGravity; // �������x�𑝉�������
			if (m_fallSpeed > kMaxFallSpeed)
			{
				m_fallSpeed = kMaxFallSpeed;
			}
			m_pos.y += m_fallSpeed;  // �v���C���[�̈ʒu���X�V����
			// ��ʊO�ɗ�������Q�[���I�[�o�[
			if (m_pos.y > 500)
			{
				m_gameOver = true;
				//printfDx("�Q�[���I�[�o�[\n");
			}
		}
		m_oldInput = _input; // �O��̓��͏�Ԃ��X�V
		return;
	}
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
		animFrames = 2; 
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
	case PlayerState::Fall:
		animFrames = kFallAnimNum;
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

// Hurt��Ԃ�Ԃ��֐�
bool Player::IsHurt() const
{
	return m_state == PlayerState::Hurt;
}

void Player::CheckManholeCollision(Manhole* manhole)
{
	if (m_state == PlayerState::Fall || m_gameOver)return;

	if (manhole->CheckLeftCollision(m_colRect))
	{
		m_state = PlayerState::Fall;
		m_animFrame = 0;
		m_isFalling = true;
		m_fallSpeed = 0.0f;
		//printfDx("���̃}���z�[���ɗ�����\n");
	}
	else if (manhole->CheckRightCollision(m_colRect))
	{
		m_state = PlayerState::Fall;
		m_animFrame = 0;
		m_fallSpeed = 0.0f;
		m_isFalling = true;
		//printfDx("�E�̃}���z�[���ɗ�����\n");
	}
}

//�v���C���[�̍U��(�m�b�N�o�b�N)���� 
void Player::KnockBack()
{
	if (!m_otherPlayer) return;

	// �U�����L�^
	m_otherPlayer->m_receivedAttackType = m_attackType;

	// ���҂��U�����Ȃ瑊�ł��𐬗�������
	bool bothAttacking = (m_state == PlayerState::Attack || m_state == PlayerState::WeakAttack) &&
		(m_otherPlayer->m_state == PlayerState::Attack || m_otherPlayer->m_state == PlayerState::WeakAttack);

	if (m_colRect.IsCollision(m_otherPlayer->GetCollisionRect()))
	{
		// �_���[�W���󂯂����
		if (!m_otherPlayer->IsHurt())
		{
			float knockBackValue = (m_attackType == AttackType::Weak) ? knockBackDist * 0.5f : knockBackDist;
			m_otherPlayer->m_pos.x += m_isTurn ? -knockBackValue : knockBackValue;
			m_otherPlayer->m_state = PlayerState::Hurt;
			m_otherPlayer->m_hurtCount = 0;
			m_otherPlayer->m_attackType = m_attackType;
			m_otherPlayer->m_animFrame = 0;
			m_hasHit = true;
		}

		if (bothAttacking && !IsHurt())
		{
			float knockBackValue = (m_otherPlayer->m_attackType == AttackType::Weak) ? knockBackDist * 0.5f : knockBackDist;
			m_pos.x += m_otherPlayer->m_isTurn ? -knockBackValue : knockBackValue;
			m_state = PlayerState::Hurt;
			m_isAttack = false;
			m_hurtCount = 0;
			m_attackType = m_otherPlayer->m_attackType;
			m_animFrame = 0;
			m_otherPlayer->m_hasHit = true;
		}
	}
}