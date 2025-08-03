#pragma once
#include"Vec2.h"

enum class PlayerState
{
	Idle,		// 待機
	Run,		// 走る
	Attack,		// 攻撃
};

class Player
{
public:
	Player();
	~Player();

	void Init(int _padType,Vec2 _firstPos,int _handle,int _attackHandle,int _runHandle);
	void End();
	void Update();
	void Draw();
	void Gravity();	// 重力

	void State(int _input);	// プレイヤーの状態管理
	bool IsMoving(int _input);	// プレイヤーの移動
	void PlayerAnimation();	// プレイヤーのアニメーション管理



private:

	int m_handle;		// グラフィックのハンドル
	int m_attackHandle;	// 攻撃のグラフィックのハンドル
	int m_runHandle;	// 走るグラフィックのハンドル
	Vec2 m_pos;			// 座標
	int m_padType;		// パッドの種類
	float m_radius;		// 当たり判定の半径
	bool m_isAttack;	// 攻撃中かどうか
	int m_attackCount;	// 攻撃のカウント
	bool m_isTurn;		// 左右反転
	int m_animFrame;	// アニメーションのフレーム
	PlayerState m_state;// プレイヤーの状態
};

