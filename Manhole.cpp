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
	m_isHitManhole(false)
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
}

// 左のマンホールの当たり判定取得
bool Manhole::IsHitLeft(const Rect& playerRect) const
{
	Rect leftRect;
	leftRect.init(130, 450, 96, 96);
	return leftRect.IsCollision(playerRect);
}

// 右のマンホールの当たり判定取得
bool Manhole::IsHitRight(const Rect& playerRect) const
{
	Rect rightRect;
	rightRect.init(1100, 450, 96, 96);
	return rightRect.IsCollision(playerRect);
}




