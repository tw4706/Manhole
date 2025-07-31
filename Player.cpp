#include "Player.h"
#include "SceneMain.h"
#include"Dxlib.h"

namespace
{
	// プレイヤーのスタート位置
	constexpr int kPlayer1StartX = 240;
	constexpr int kPlayer1StartY = 480;
	// プレイヤー2のスタート位置
	constexpr int kPlayer2StartX = 480;
	constexpr int kPlayer2StartY = 480;
	// 当たり判定の半径
	constexpr float kDefaultRadius = 16.0f;
	// プレイヤーの移動速度
	constexpr int  kSpeed = 2;

}

Player::Player():
	m_radius(0.0f),
	m_isTurn(false)
{
}

Player::~Player()
{
}

void Player::Init(int _padType)
{
	m_padType = _padType;
	m_radius = kDefaultRadius;
	m_isTurn = false;
}

void Player::End()
{
}

void Player::Update()
{

	//	コントローラーのボタンの押された状態を取得する
	m_padType = GetJoypadInputState(DX_INPUT_PAD1);
	if (m_padType & PAD_INPUT_DOWN)
	{
		m_pos.y += kSpeed;
	}
}

void Player::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, m_radius, GetColor(255, 255, 0),true);
}
