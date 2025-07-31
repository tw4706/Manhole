#include "SceneMain.h"
#include"Dxlib.h"
#include"Game.h"

SceneMain::SceneMain():
	m_player1(nullptr),
	m_player2(nullptr)
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::Init()
{
	m_player1 = new Player();	// �v���C���[�̃C���X�^���X�𐶐�	
	m_player2 = new Player();	
	m_player1->Init(DX_INPUT_PAD1,Vec2(240,480));// ������
	m_player2->Init(DX_INPUT_PAD2,Vec2(480, 480));	// �v���C���[�̏�����
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
