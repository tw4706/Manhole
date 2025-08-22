#include "Manhole.h"
#include "DxLib.h"

namespace
{
	constexpr int kManhole1Size = 64;
	constexpr int kManhole2Size = 64;
}

Manhole::Manhole():
	m_manhole1Handle(-1),
	m_manhole2Handle(-1),
	m_isHitManhole(false),
	m_leftTriggerFlag(false),
	m_rightTriggerFlag(false)
{
}

Manhole::~Manhole()
{
}

void Manhole::Init(int _handle1,int _handle2)
{
	m_manhole1Handle = _handle1;
	m_manhole2Handle = _handle2;
	m_isHitManhole = false;
	m_leftTriggerFlag = false;
	m_rightTriggerFlag = false;
}

void Manhole::End()
{

}

void Manhole::Update()
{

}

void Manhole::Draw()
{
	DrawExtendGraph(130, 450,130+96,450+96, m_manhole1Handle,true);
	DrawExtendGraph(1100,450,1100+96,450+96, m_manhole2Handle,true);
#ifdef _DEBUG
	// ���}���z�[���̓����蔻��
	Rect leftRect;
	leftRect.init(130, 450, 96, 96);
	leftRect.Draw(0xFF0000, false); // �ԐF�Řg���\��

	// �E�}���z�[���̓����蔻��
	Rect rightRect;
	rightRect.init(1100, 450, 96, 96);
	rightRect.Draw(0x0000FF, false); // �F�Řg���\��
#endif

}

bool Manhole::IsHitLeft(const Rect& playerRect) const
{
    if (m_leftTriggerFlag) return false; // �������Ă���ꍇ�͓����蔻��𖳌���
    Rect leftRect;
    leftRect.init(130, 450, 96, 96);
    if (leftRect.IsCollision(playerRect))
    {
		// const�̃����o�ϐ���ύX���邽�߂�const_cast���g�p
        const_cast<bool&>(m_leftTriggerFlag) = true;
        return true;
    }
    return false;
}

// �E�̃}���z�[���̓����蔻��擾
bool Manhole::IsHitRight(const Rect& playerRect) const
{
	if (m_rightTriggerFlag) return false; // �������Ă���ꍇ�͓����蔻��𖳌���
	Rect rightRect;
	rightRect.init(1100, 450, 96, 96);
	if (rightRect.IsCollision(playerRect))
	{
		// const�̃����o�ϐ���ύX���邽�߂�const_cast���g�p
		const_cast<bool&>(m_rightTriggerFlag) = true;
		return true;
	}
	return false;
}




