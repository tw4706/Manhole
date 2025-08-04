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
	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_player1GraphHandle; 
	int m_player2GraphHandle;
	// �v���C���[�̍U���O���t�B�b�N�n���h��
	int m_player1AttackGraphHandle; 
	int m_player2AttackGraphHandle;
	// �v���C���[�̑���O���t�B�b�N�n���h��
	int m_player1RunGraphHandle;	
	int m_player2RunGraphHandle;
	// �w�i�̃O���t�B�b�N�n���h��
	int m_bgGraphHandle;

	// �v���C���[
	Player*m_player1;
	Player*m_player2;
	// �w�i
	Bg*m_bg;
};

