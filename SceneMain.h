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

	// �v���C���[
	Player*m_player1;
	Player*m_player2;
};

