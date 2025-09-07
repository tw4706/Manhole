#include "Manhole.h"
#include "DxLib.h"
#include <cmath>

namespace
{
	constexpr int kManholeGraphWidth = 48;
	constexpr int kManholeGraphHeight = 48;
	// �}���z�[���̓����蔻��p�̍��W
	constexpr int kManholeX1 = 220; // ���}���z�[����X���W
	constexpr int kManholeY1 = 460; // ���}���z�[����Y���W
	constexpr int kManholeX2 = 1060; // �E�}���z�[����X���W
	constexpr int kManholeY2 = 460; // �E�}���z�[����Y���W
	// �댯��m�点�鋗��
	constexpr float kWarningDistance = 150.0f;
	// �����p�̋���
	constexpr int kLeft = 96;	// ����
	constexpr int kTop = 80;	// ������̋���
	constexpr int kRight = 64;	// ����
	constexpr int kBottom = 240;// �ォ��̋���
}

Manhole::Manhole():
	m_handle1(-1),
	m_handle2(-1),
	m_leftTriggered(false), 
	m_rightTriggered(false),
	m_warningHandle(-1),
	m_blinkTimer(0.0f),
	m_blinkFlag(false),
	m_dangerSoundHandle(-1),
	m_showLeftWarning(false),
	m_showRightWarning(false),
	m_leftPlayed(false),
	m_rightPlayed(false),
	m_stopSoundFlag(false)
{
}

Manhole::~Manhole()
{
}

void Manhole::Init(int _handle1,int _handle2)
{
	m_handle1 = _handle1;
	m_handle2 = _handle2;
	m_leftRect.init(kManholeX1, kManholeY1, kManholeGraphWidth+20, kManholeGraphHeight);
	m_rightRect.init(kManholeX2, kManholeY2, kManholeGraphWidth+20, kManholeGraphHeight);
	m_warningHandle = LoadGraph("data/UI/Warning.png");
	m_dangerSoundHandle = LoadSoundMem("data/BGM�ESE/warning.mp3");
	ChangeVolumeSoundMem(180, m_dangerSoundHandle);
	m_blinkFlag = false;
	m_blinkTimer = 0;
	m_showLeftWarning = false;
	m_showRightWarning = false;
	m_leftPlayed = false;
	m_rightPlayed = false;
}

void Manhole::End()
{


}

void Manhole::Update(const Vec2&_player1Pos, const Vec2& _player2Pos)
{
	Vec2 leftCenter = m_leftRect.GetCenter();
	float LeftDist = sqrt(pow(_player1Pos.x - leftCenter.x, 2) + 
		pow(_player1Pos.y - leftCenter.y, 2));

	Vec2 rightCenter = m_rightRect.GetCenter();
	float RightDist = sqrt(pow(_player2Pos.x - rightCenter.x, 2) + 
		pow(_player2Pos.y - rightCenter.y, 2));

	// �}���z�[���Ɏg�Â��Ă��邩�ǂ����̔���
	bool isNearLeft = LeftDist < kWarningDistance;
	bool isNearRight = RightDist < kWarningDistance;

	// �_�ŗp�^�C�}�[�̍X�V
	m_blinkTimer++;

	// �_�Ńt���O
	bool isBlink = (m_blinkTimer % 30 < 15);

	// ���E�\���̍X�V
	m_showLeftWarning = isNearLeft && isBlink;
	m_showRightWarning = isNearRight && isBlink;

	// ���E�\�������������ꍇ�̓^�C�}�[�����Z�b�g����
	if (!isNearLeft && !isNearRight)
	{
		m_blinkTimer = 0;
		m_showLeftWarning = false;
		m_showRightWarning = false;
	}

}

void Manhole::Draw()
{
	DrawExtendGraph(
		static_cast<int>(m_leftRect.m_left)-20,
		static_cast<int>(m_leftRect.m_top),
		static_cast<int>(m_leftRect.m_right)+20,
		static_cast<int>(m_leftRect.m_bottom),
		m_handle1, TRUE);
	//printfDx("pos.x=%f,pos.y=%f\n", pos.x, pos.y);

	DrawExtendGraph(
		static_cast<int>(m_rightRect.m_left)-20,
		static_cast<int>(m_rightRect.m_top),
		static_cast<int>(m_rightRect.m_right)+20,
		static_cast<int>(m_rightRect.m_bottom),
		m_handle2, TRUE);

	//printfDx("pos.x=%f,pos.y=%f\n", pos.x, pos.y);

	if (!m_stopSoundFlag&&m_warningHandle != -1)
	{
		if (m_showLeftWarning)
		{
			Vec2 leftCenter = m_leftRect.GetCenter();
			DrawExtendGraph(
				static_cast<int>(leftCenter.x) - kLeft,
				static_cast<int>(leftCenter.y) + kTop,
				static_cast<int>(leftCenter.x) + kRight,
				static_cast<int>(leftCenter.y) + kBottom,
				m_warningHandle, TRUE);
			//printfDx("���x���\����\n");

			if (!m_leftPlayed)
			{
				PlaySoundMem(m_dangerSoundHandle, DX_PLAYTYPE_BACK);
				m_leftPlayed = true;
			}
		}
		else
		{
			m_leftPlayed = false; // �\������Ă��Ȃ��Ƃ��̓��Z�b�g
		}

		if (m_showRightWarning)
		{
			Vec2 rightCenter = m_rightRect.GetCenter();
			DrawExtendGraph(
				static_cast<int>(rightCenter.x) - kLeft,
				static_cast<int>(rightCenter.y) + kTop,
				static_cast<int>(rightCenter.x) + kRight,
				static_cast<int>(rightCenter.y) + kBottom,
				m_warningHandle, TRUE);
			//printfDx("�E�x���\����\n");
			if (!m_rightPlayed)
			{
				PlaySoundMem(m_dangerSoundHandle, DX_PLAYTYPE_BACK);
				m_rightPlayed = true;
			}
		}
		else
		{
			m_rightPlayed = false; // �\������Ă��Ȃ��Ƃ��̓��Z�b�g
		}
	}

#ifdef _DEBUG
	// ���}���z�[���̓����蔻��
	if (!m_leftTriggered)
	{
		m_leftRect.Draw(0xFF0000, false); // �ԐF�Řg���\��
	}

	// �E�}���z�[���̓����蔻��
	if (!m_rightTriggered)
	{
		m_rightRect.Draw(0x0000FF, false); // �F�Řg���\��
	}
#endif
}

bool Manhole::CheckLeftCollision(const Rect& playerRect)
{
	if (!m_leftTriggered && m_leftRect.IsCollision(playerRect))
	{
		m_leftTriggered = true;
		return true;
	}
	return false;
}

bool Manhole::CheckRightCollision(const Rect& playerRect)
{
	if (!m_rightTriggered && m_rightRect.IsCollision(playerRect))
	{
		m_rightTriggered = true;
		return true;
	}

	return false;
}

Vec2 Manhole::GetCenter()const
{
	// ���Ԑ؂�̍ۂ̋�������Ɏg�p
	Vec2 leftCenter = m_leftRect.GetCenter();
	Vec2 rightCenter = m_rightRect.GetCenter();
	return Vec2{ (leftCenter.x + rightCenter.x) / 2.0f, (leftCenter.y + rightCenter.y) / 2.0f };
}

void Manhole::SetGameOver(bool _isOver)
{
	m_stopSoundFlag = true;
	StopSoundMem(m_dangerSoundHandle);
}
