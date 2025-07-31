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

	int m_player1GraphHandle; // �v���C���[1�̃O���t�B�b�N�n���h��
	int m_player2GraphHandle; // �v���C���[2�̃O���t�B�b�N�n���h��
	// �v���C���[
	Player*m_player1;
	Player*m_player2;
};

