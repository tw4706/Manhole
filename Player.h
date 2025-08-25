#pragma once
#include"Rect.h"
#include"DxLib.h"
#include"Vec2.h"
#include<vector>

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
};

class Player; // 前方宣言

// 攻撃を一時保存するための構造体
struct Attack
{
	Player* attacker;
	Player* target;
	int priority;   // 強攻撃ほど高く
	int hitFrame;   // 攻撃が当たったフレーム
};

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

	void UpdateState(int _input);									// プレイヤーの状態管理
	bool IsMoving(int _input);										// プレイヤーの移動
	void UpdateAnim();												// プレイヤーのアニメーション管理
	void SetOtherPlayer(Player* other) { m_otherPlayer = other; }	// 攻撃対象の取得
	void KnockBack();												// ノックバック処理
	const Rect& GetCollisionRect() const;							// 当たり判定を取得するためのgetter関数
	bool IsHurt()const;
	void SetGameOver(bool isOver) { m_gameOver = isOver; }			// ゲームオーバーの判定
	void SetFalling(bool isFalling) { m_isFalling = isFalling; }	// 落下中の判定
	bool IsFalling()const;											// 落下中かどうかの判定
	// 先輩からのアドバイス:関数は動詞から始める
	//　UpdateAnim
	//　UpdateState


private:

	int m_handle;				// グラフィックのハンドル
	int m_attackHandle;			// 強攻撃のグラフィックのハンドル
	int m_wAttackHandle;		// 弱攻撃のグラフィックのハンドル
	int m_runHandle;			// 走るグラフィックのハンドル
	int m_hurtHandle;			// 攻撃を受けた時のグラフィックのハンドル
	Vec2 m_pos;					// 座標
	Vec2 m_centerPos;			// 当たり判定のサイズ座標
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
	bool m_isFalling;			// 落下中かどうか
	float m_fallSpeed;			// 落下速度
	bool m_gameOver;			// ゲームオーバーかどうか
	int m_currentFrame;			// 現在のフレーム数
	PlayerState m_state;		// プレイヤーの状態
	AttackType m_attackType;	// 攻撃の種類
	Player* m_otherPlayer;		// 対戦相手のプレイヤー(攻撃の対象となる)
	std::vector<Attack> m_pendingAttacks;

protected:
	// 当たり判定の矩形
	Rect m_colRect;	
};

