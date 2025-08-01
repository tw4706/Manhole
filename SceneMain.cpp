#include "SceneMain.h"
#include"Dxlib.h"
#include"Game.h"
#include "Bg.h"

SceneMain::SceneMain():
	m_player1GraphHandle(-1),
	m_player2GraphHandle(-1),
	m_player1AttackGraphHandle(-1),
	m_player2AttackGraphHandle(-1),
	m_player1(nullptr),
	m_player2(nullptr),
	m_bg(nullptr)
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// �v���C���[�̃C���X�^���X�𐶐�	
	m_player1 = new Player();	
	m_player2 = new Player();
	m_bg = new Bg();
	//�O���t�B�b�N�̓ǂݍ���
	m_player1GraphHandle = LoadGraph("data/Player1.idle.png");
	m_player2GraphHandle = LoadGraph("data/Player2.idle.png");
	m_player1AttackGraphHandle = LoadGraph("data/Player1.attack.png");
	m_player2AttackGraphHandle = LoadGraph("data/Player2.attack.png");
	// ������
	m_player1->Init(DX_INPUT_PAD1,Vec2(400,480),m_player1GraphHandle);
	m_player2->Init(DX_INPUT_PAD2,Vec2(800, 480), m_player2GraphHandle);
	m_bg->Init();
	
	
}

void SceneMain::End()
{
	m_player1->End();	// �I������
	m_player2->End();	// �v���C���[�̏I������
	m_bg->End();
}

void SceneMain::Update()
{
	// �v���C���[�̏����̍X�V
	m_player1->Update();
	m_player2->Update();
	m_bg->Update();
}

void SceneMain::Draw()
{
	m_player1->Draw();
	m_player2->Draw();	// �v���C���[�̕`�揈��
	m_bg->Draw();
}
