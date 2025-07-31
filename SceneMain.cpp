#include "SceneMain.h"
#include"Dxlib.h"
#include"Game.h"

SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_player1 = new Player();	// �v���C���[�̃C���X�^���X�𐶐�	
	m_player2 = new Player();	
	m_player1->Init();// ������
	m_player2->Init();	// �v���C���[�̏�����
}

void SceneMain::End()
{
	m_player1->End();	// �I������
	m_player2->End();	// �v���C���[�̏I������
}

void SceneMain::Update()
{
	m_player1->Update();
	m_player2->Update();	// �v���C���[�̍X�V����
}

void SceneMain::Draw()
{
	m_player1->Draw();
	m_player2->Draw();	// �v���C���[�̕`�揈��
}
