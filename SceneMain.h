#pragma once
#include"Player.h"
#include"Bg.h"
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
	void UpdateGame();
private:
	// プレイヤーのグラフィックハンドル
	int m_player1GraphHandle; 
	int m_player2GraphHandle;
	// プレイヤーの攻撃グラフィックハンドル
	int m_player1AttackGraphHandle; 
	int m_player2AttackGraphHandle;
	// プレイヤーの走るグラフィックハンドル
	int m_player1RunGraphHandle;	
	int m_player2RunGraphHandle;
	// 背景のグラフィックハンドル
	int m_bgGraphHandle;

	// プレイヤー
	Player*m_player1;
	Player*m_player2;
	// 背景
	Bg*m_bg;
};

