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
	// プレイヤーグラフィックのサイズ
	constexpr int kGraphWidth = 48;
	constexpr int kGraphHeight = 48;
	// アニメーション情報
	constexpr int kIdleAnimNum = 4;
	constexpr int kAnimWaitFrame = 4;
	// 当たり判定の半径
	constexpr float kDefaultRadius = 16.0f;
	// プレイヤーの移動速度
	constexpr int  kSpeed = 2;
	// 重力
	constexpr float kGravity = 1.5f;
	// 地面の当たり判定
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
	
	// アニメーションの更新
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

	//	コントローラーのボタンの押された状態を取得する
	int input = GetJoypadInputState(m_padType);

	//	コントローラーの十字キーの押された状態を取得する
	if (input & PAD_INPUT_LEFT)
	{
		m_pos.x -= kSpeed;
		m_isTurn = true; // 左に移動したら向きを左にする
	}
	if (input & PAD_INPUT_RIGHT)
	{
		m_pos.x += kSpeed;
		m_isTurn = false; // 右に移動したら向きを右にする
	}
}

void Player::Draw()
{
	// アニメーションのフレーム数から表示したいコマ番号を計算で求める
	int animNum = m_animFrame / kAnimWaitFrame;

	// アニメーションの進行に合わせてグラフィックの切り取り位置を変更する
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
	// 重力を追加する
	m_pos.y += kGravity;
}
