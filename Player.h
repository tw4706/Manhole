#pragma once
#include"Vec2.h"

enum class PlayerState
{
	Idle,		// 待機
	Run,		// 走る
	AttackPrep,	// 強攻撃準備
	Attack,		// 強攻撃
	WeakAttack,	// 弱攻撃
	Hurt,		// 攻撃を受けた
};

enum class AttackType
{
	Normal,		// 強攻撃
	Weak,		// 弱攻撃
};;

class Player
{
public:
	Player();
	~Player();

	void Init(int _padType,Vec2 _firstPos,int _handle,int _attackHandle,int _wAttackHandle,int _runHandle,int _hurtHandle,bool _isTurn);
	void End();
	void Update();
	void Draw();
	void Gravity();	// 重力

	// 当たり判定の情報
	float GetPosX() const { return m_pos.x; }	// X座標を取得
	float GetPosY() const { return m_pos.y; }	// Y座標を取得
	float GetPosRadius() const { return m_radius; }	// 半径を取得

	void UpdateState(int _input);	// プレイヤーの状態管理
	bool IsMoving(int _input);	// プレイヤーの移動
	void UpdateAnim();	// プレイヤーのアニメーション管理
	// 攻撃対象の取得
	void SetOtherPlayer(Player* other) { m_otherPlayer = other; }
	void KnockBack();	// ノックバック処理


	// アドバイス:関数は動詞から始める
	//　UpdateAnim
	//　UpdateState


private:

	int m_handle;				// グラフィックのハンドル
	int m_attackHandle;			// 強攻撃のグラフィックのハンドル
	int m_wAttackHandle;		// 弱攻撃のグラフィックのハンドル
	int m_runHandle;			// 走るグラフィックのハンドル
	int m_hurtHandle;			// 攻撃を受けた時のグラフィックのハンドル
	Vec2 m_pos;					// 座標
	int m_padType;				// パッドの種類
	float m_radius;				// 当たり判定の半径
	bool m_isAttack;			// 攻撃中かどうか
	int m_attackCount;			// 強攻撃のカウント
	int m_wAttackCount;			// 弱攻撃のカウント
	int m_attackPrepCount;		// 強攻撃の準備のカウント
	int m_hurtCount;			// 攻撃を受けたカウント
	bool m_isTurn;				// 左右反転
	int m_animFrame;			// アニメーションのフレーム
	int m_oldInput;				// 前回の入力	
	PlayerState m_state;		// プレイヤーの状態
	AttackType m_attackType;	// 攻撃の種類
	Player* m_otherPlayer;		// 対戦相手のプレイヤー(攻撃の対象となる)
};

