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
	// 左マンホールの当たり判定
	if (!m_leftTriggerFlag)
	{
		m_leftRect.Draw(0xFF0000, false); // 赤色で枠線表示
	}

	// 右マンホールの当たり判定
	if (!m_rightTriggerFlag)
	{
		m_rightRect.Draw(0x0000FF, false); // 青色で枠線表示
	}
	
#endif

}

bool Manhole::IsHitLeft(const Rect& playerRect)
{
    if (m_leftTriggerFlag) return false; // 当たっている場合は当たり判定を無効化
    if (m_leftRect.IsCollision(playerRect))
    {
        m_leftTriggerFlag = true;
		printfDx("左マンホールの描画をスキップ\n");
        return true;
    }
    return false;
}

// 右のマンホールの当たり判定取得
bool Manhole::IsHitRight(const Rect& playerRect)
{
	if (m_rightTriggerFlag) return false; // 当たっている場合は当たり判定を無効化
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
	printfDx("Disが呼ばれた！");
}




