#pragma once
#include"Player.h"
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

	int m_player1GraphHandle; // プレイヤー1のグラフィックハンドル
	int m_player2GraphHandle; // プレイヤー2のグラフィックハンドル
	// プレイヤー
	Player*m_player1;
	Player*m_player2;
};

