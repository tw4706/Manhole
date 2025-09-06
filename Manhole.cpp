#include "Manhole.h"
#include "DxLib.h"

namespace
{
	constexpr int kManholeGraphWidth = 48;
	constexpr int kManholeGraphHeight = 48;
	// マンホールの当たり判定用の座標
	constexpr int kManholeX1 = 220; // 左マンホールのX座標
	constexpr int kManholeY1 = 460; // 左マンホールのY座標
	constexpr int kManholeX2 = 1060; // 右マンホールのX座標
	constexpr int kManholeY2 = 460; // 右マンホールのY座標
}

Manhole::Manhole():
	m_handle1(-1),
	m_handle2(-1),
	m_leftTriggered(false), 
	m_rightTriggered(false),
	m_warningHandle(-1)
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
}

void Manhole::End()
{


}

void Manhole::Update()
{
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
			// 点滅警告の描画


#ifdef _DEBUG
	// 左マンホールの当たり判定
	if (!m_leftTriggered)
	{
		m_leftRect.Draw(0xFF0000, false); // 赤色で枠線表示
	}

	// 右マンホールの当たり判定
	if (!m_rightTriggered)
	{
		m_rightRect.Draw(0x0000FF, false); // 青色で枠線表示
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
	// 時間切れの際の距離判定に使用
	Vec2 leftCenter = m_leftRect.GetCenter();
	Vec2 rightCenter = m_rightRect.GetCenter();
	return Vec2{ (leftCenter.x + rightCenter.x) / 2.0f, (leftCenter.y + rightCenter.y) / 2.0f };
}
