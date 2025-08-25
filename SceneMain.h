#pragma once
#include"Player.h"
#include"Bg.h"
#include"Manhole.h"
#include"Timer.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	// プレイヤーのグラフィックハンドル
	int m_player1GraphHandle; 
	int m_player2GraphHandle;
	// プレイヤーの攻撃グラフィックハンドル
	int m_player1AttackGraphHandle; 
	int m_player2AttackGraphHandle;
	// プレイヤーの弱攻撃グラフィックハンドル
	int m_player1WeakAttackGraphHandle;
	int m_player2WeakAttackGraphHandle;
	// プレイヤーの走るグラフィックハンドル
	int m_player1RunGraphHandle;	
	int m_player2RunGraphHandle;
	// プレイヤーの攻撃を受けた時のハンドル
	int m_player1HurtGraphHandle;
	int m_player2HurtGraphHandle;
	// マンホールのグラフィックハンドル
	int m_manhole1GraphHandle;
	int m_manhole2GraphHandle;
	// 前回の時間を保存する変数
	int m_timer;
	// ゲームオーバーのフラグ
	bool m_gameOver;
	// 勝利したプレイヤーのフラグ
	bool m_player1WinFlag;
	bool m_player2WinFlag;
	// BGMのグラフィックハンドル
	int m_bgmHandle;
	// 勝利時のBGMハンドル
	int m_winBgmHandle;

	// プレイヤー
	Player*m_player1;
	Player*m_player2;
	// 背景
	Bg* m_Bg;
	// マンホール
	Manhole* m_manhole1;
	Manhole* m_manhole2;
	// タイマー
	Timer*m_roundTimer;
};

