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
	m_leftRect.init(130, 450, 96, 96);
	m_rightRect.init(1100, 450, 96, 96);
}

void Manhole::End()
{

}

void Manhole::Update()
{

}

void Manhole::Draw()
{
	if (!m_leftTriggerFlag) 
	{
		DrawExtendGraph(130, 450, 130 + 96, 450 + 96, m_manhole1Handle, true);
	}

	if (!m_rightTriggerFlag) 
	{
		DrawExtendGraph(1100, 450, 1100 + 96, 450 + 96, m_manhole2Handle, true);
	}

#ifdef _DEBUG
	// ���}���z�[���̓����蔻��
	if (!m_leftTriggerFlag)
	{
		m_leftRect.Draw(0xFF0000, false); // �ԐF�Řg���\��
	}

	// �E�}���z�[���̓����蔻��
	if (!m_rightTriggerFlag)
	{
		m_rightRect.Draw(0x0000FF, false); // �F�Řg���\��
	}
	
#endif

}

bool Manhole::IsHitLeft(const Rect& playerRect)
{
    if (m_leftTriggerFlag) return false; // �������Ă���ꍇ�͓����蔻��𖳌���
    if (m_leftRect.IsCollision(playerRect))
    {
        m_leftTriggerFlag = true;
		printfDx("���}���z�[���̕`����X�L�b�v\n");
        return true;
    }
    return false;
}

// �E�̃}���z�[���̓����蔻��擾
bool Manhole::IsHitRight(const Rect& playerRect)
{
	if (m_rightTriggerFlag) return false; // �������Ă���ꍇ�͓����蔻��𖳌���
	if (m_rightRect.IsCollision(playerRect))
	{
		m_rightTriggerFlag = true;
		return true;
	}
	return false;
}

void Manhole::DisableCollision(bool isLeft)
{
	if (isLeft)
	{
		m_leftTriggerFlag = true;
		m_leftRect.init(-9999, -9999, 0, 0);
	}
	else
	{
		m_rightTriggerFlag = true;
		m_rightRect.init(-9999, -9999, 0, 0);
	}
	printfDx("Dis���Ă΂ꂽ�I");
}




