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
	// 待機アニメーション情報
	constexpr int kIdleAnimNum = 4;
	constexpr int kAnimWaitFrame = 4;
	// 走るアニメーション情報
	constexpr int kRunAnimNum = 6;
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
	m_attackHandle(-1),
	m_runHandle(-1),
	m_padType(0),
	m_radius(0.0f),
	m_isAttack(false),
	m_attackCount(0),
	m_isTurn(false),
	m_animFrame(0),
	m_state(PlayerState::Idle)
{
}

Player::~Player()
{

}

void Player::Init(int _padType, Vec2 _firstPos,int _handle,int _attackHandle,int _runHandle)
{
	m_handle = _handle;
	m_attackHandle = _attackHandle;
	m_runHandle = _runHandle;
	m_pos = _firstPos;
	m_padType = _padType;
	m_radius = kDefaultRadius;
	m_isAttack = false;
	m_attackCount = 0;
	m_isTurn = false;
}

void Player::End()
{
}

void Player::Update()
{
	bool isMoving = false;
	Gravity();

	// アニメーションの更新
	int animNum = 0;
	int animFrames = (m_state == PlayerState::Run) ? kRunAnimNum : kIdleAnimNum;

	// フレームを状態に応じて計算
	animNum = (m_animFrame / kAnimWaitFrame) % animFrames;

	// アニメーションフレームのリセット
	if (++m_animFrame >= (animFrames * kAnimWaitFrame)) {
		m_animFrame = 0;
	}

	if (m_pos.y >= kGround)
	{
		m_pos.y = kGround;
	}

	//	コントローラーのボタンの押された状態を取得する
	int input = GetJoypadInputState(m_padType);
	

	// プレイヤーの状態
	if (input == DX_INPUT_PAD2)
	{
		m_isTurn = false; // 右側のプレイヤーは常に右向き
	}

	// 移動処理

	if (input & PAD_INPUT_LEFT && !(input & PAD_INPUT_RIGHT))
	{
		m_pos.x -= kSpeed;
		m_isTurn = true;
		isMoving = true;
		
	}
	if (input & PAD_INPUT_RIGHT && !(input & PAD_INPUT_LEFT))
	{
		m_pos.x += kSpeed;
		m_isTurn = false;
		isMoving = true;
		
	}
	if (!isMoving) 
	{
		
	}
	DrawFormatString(10, 10, GetColor(255, 255, 255), "isMoving: %d", isMoving); // 更新後の値表示

	// 状態判定
	if (m_isAttack&&input & PAD_INPUT_A)
	{
		m_state = PlayerState::Attack;
		m_attackCount = 0;
		m_isAttack = true;
	}
	else if (isMoving)
	{
		m_state = PlayerState::Run;
	}
	else
	{
		m_state = PlayerState::Idle;
	}


	//プレイヤーの状態の処理分岐
	switch (m_state)
	{
	case PlayerState::Idle:
			// 通常状態の処理
			break;
	case PlayerState::Run:
		if (input & PAD_INPUT_LEFT&& !(input & PAD_INPUT_RIGHT))
		{
			m_pos.x -= kSpeed;
			m_isTurn = true; // 左に移動したら向きを左にする
		}
		if (input & PAD_INPUT_RIGHT && !(input & PAD_INPUT_LEFT))
		{
			m_pos.x += kSpeed;
			m_isTurn = false; // 右に移動したら向きを右にする
		}
		break;
	case PlayerState::Attack:
		m_attackCount++;	//攻撃のカウントを進める
		if (m_attackCount > 60) 
		{
			// 攻撃状態を終了
			m_isAttack = false; 
			// 攻撃が終わったら通常状態に戻す
			m_state = PlayerState::Idle; 
		}
		break;
	}

}

void Player::Draw()
{
	// アニメーションのフレーム数から表示したいコマ番号を計算で求める
	int animNum = 0;
	//// プレイヤーのそれぞれの状態をもとにX座標を計算する
	int srcX = 0;
	int srcY = 0;
	int handle = m_handle;


	switch (m_state)
	{
	case PlayerState::Idle:
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_handle;
		srcY = 0;
		break;

	case PlayerState::Run:
		animNum = (m_animFrame / kAnimWaitFrame) % kRunAnimNum;
		handle = m_runHandle;
		srcY = kGraphHeight;
		break;

	case PlayerState::Attack:
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_attackHandle;
		srcY = 0;
		break;
	}

	srcX = kGraphWidth * animNum;
	if (handle != -1)
	{
		DrawRectGraph(
			m_pos.x - kGraphWidth / 2,
			m_pos.y - kGraphHeight / 2,
			srcX, srcY,
			kGraphWidth, kGraphHeight,
			handle, TRUE
		);
	}
	// デバッグ表示（状態とアニメーション番号）
	DrawFormatString(10, 190, GetColor(255, 255, 255), "Current State: %d", m_state);
}

void Player::Gravity()
{
	// 重力を追加する
	m_pos.y += kGravity;
}
