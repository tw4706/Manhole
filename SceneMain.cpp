#include "SceneMain.h"
#include"Dxlib.h"
#include"Game.h"
#include"Rect.h"
#include "Bg.h"
#include<cmath>
#include "Manhole.h"

SceneMain::SceneMain():
	m_player1GraphHandle(-1),
	m_player2GraphHandle(-1),
	m_player1AttackGraphHandle(-1),
	m_player2AttackGraphHandle(-1),
	m_player1WeakAttackGraphHandle(-1),
	m_player2WeakAttackGraphHandle(-1),
	m_player1RunGraphHandle(-1),
	m_player2RunGraphHandle(-1),
	m_player1HurtGraphHandle(-1),
	m_player2HurtGraphHandle(-1),
	m_player1FallGraphHandle(-1),
	m_player2FallGraphHandle(-1),
	m_manhole1GraphHandle(-1),
	m_manhole2GraphHandle(-1),
	m_timer(0),
	m_gameOver(false),
	m_player1WinFlag(false),
	m_player2WinFlag(false),
	m_bgmHandle(-1),
	m_winBgmHandle(-1),
	m_gameOverBgHandle(-1),
	m_player1(nullptr),
	m_player2(nullptr),
	m_Bg(nullptr),
	m_manhole(nullptr),
	m_roundTimer(nullptr)
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// ���݂̎��Ԃ��擾
	m_timer = GetNowCount();
	m_gameOver = false;
	// �v���C���[�̃C���X�^���X�𐶐�	
	m_player1 = new Player();	
	m_player2 = new Player();
	m_Bg = new Bg();
	m_manhole = new Manhole();
	m_roundTimer = new Timer();

	// �v���C���[�̃Q�[���I�[�o�[�t���O��������
	m_gameOver = false;
	// �v���C���[�̏����t���O��������
	m_player1WinFlag = false;
	m_player2WinFlag = false;
	//�O���t�B�b�N�̓ǂݍ���
	m_player1GraphHandle = LoadGraph("data/Player1.idle.png");
	m_player2GraphHandle = LoadGraph("data/Player2.idle.png");
	m_player1AttackGraphHandle = LoadGraph("data/Player1.weak.png");
	m_player2AttackGraphHandle = LoadGraph("data/Player2.attack.png");
	m_player1WeakAttackGraphHandle = LoadGraph("data/Player1.attack.png");
	m_player2WeakAttackGraphHandle = LoadGraph("data/Player2.weak.png");
	m_player1RunGraphHandle = LoadGraph("data/Player1.run.png");
	m_player2RunGraphHandle = LoadGraph("data/Player2.run.png");
	m_player1HurtGraphHandle = LoadGraph("data/Player1.hurt.png");
	m_player2HurtGraphHandle = LoadGraph("data/Player2.hurt.png");
	m_player1FallGraphHandle = LoadGraph("data/Fall.png");
	m_player2FallGraphHandle = LoadGraph("data/Fall1.png");
	m_manhole1GraphHandle = LoadGraph("data/Manhole1.png");
	m_manhole2GraphHandle = LoadGraph("data/Manhole2.png");
	m_bgmHandle = LoadSoundMem("data/game.mp3");
	ChangeVolumeSoundMem(110, m_bgmHandle);          // ���ʂ̒���
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);     // ���[�v�Đ�
	m_gameOverBgHandle = LoadSoundMem("data/gameOver.mp3");
	ChangeVolumeSoundMem(150, m_gameOverBgHandle);

	m_roundTimer->Init(300.0f);
	m_roundTimer->Reset();
	m_roundTimer->Start();
	m_player1->Init(DX_INPUT_PAD1,Vec2(400,480),m_player1GraphHandle,
		m_player1AttackGraphHandle, m_player1WeakAttackGraphHandle,
		m_player1RunGraphHandle,m_player1HurtGraphHandle,m_player1FallGraphHandle,false);
	m_player2->Init(DX_INPUT_PAD2,Vec2(840, 480), m_player2GraphHandle,
		m_player2AttackGraphHandle, m_player2WeakAttackGraphHandle,
		m_player2RunGraphHandle, m_player2HurtGraphHandle, m_player2FallGraphHandle,true);
	m_Bg->Init();
	m_manhole->Init(m_manhole1GraphHandle,m_manhole2GraphHandle);
}

void SceneMain::End()
{
	m_player1->End();	// �v���C���[�̏I������
	m_player2->End();
	m_Bg->End();		// �w�i�̏I������
	m_manhole->End();	// �}���z�[���̏I������
	m_roundTimer->End();// �^�C�}�[�̏I������
	// �O���t�B�b�N�̉��
	DeleteGraph(m_player1GraphHandle);
	DeleteGraph(m_player2GraphHandle);
	DeleteGraph(m_player1AttackGraphHandle);
	DeleteGraph(m_player2AttackGraphHandle);
	DeleteGraph(m_player1WeakAttackGraphHandle);
	DeleteGraph(m_player2WeakAttackGraphHandle);
	DeleteGraph(m_player1RunGraphHandle);
	DeleteGraph(m_player2RunGraphHandle);
	DeleteGraph(m_player1HurtGraphHandle);
	DeleteGraph(m_player2HurtGraphHandle);
	DeleteGraph(m_manhole1GraphHandle);
	DeleteGraph(m_manhole2GraphHandle);
	delete m_roundTimer;
	DeleteSoundMem(m_bgmHandle);
	StopSoundMem(m_gameOverBgHandle);
	DeleteSoundMem(m_gameOverBgHandle);
}

void SceneMain::Update()
{
	int currentTime = GetNowCount();
	float deltaTime = (currentTime - m_timer) / 1000.0f;
	m_timer = currentTime;
	// �Q�[���̃��X�^�[�g
	if (m_gameOver)
	{
		// ���҂͓������Ƃ��\
		if (m_player2WinFlag)
		{
			m_player1->Update();
			m_player2->Update();
		}
		else if (m_player1WinFlag)
		{
			m_player1->Update();
			m_player2->Update();
		}
		StopSoundMem(m_bgmHandle);
		// R�L�[�������ꂽ�烊�X�^�[�g
		if (CheckHitKey(KEY_INPUT_R))
		{
			End();   // ���݂̃��\�[�X�����
			Init();  // �ď�����
		}
		return;
	}
	m_roundTimer->Update(deltaTime);
	if (m_roundTimer->IsTimeUp())
	{
		printfDx("���Ԑ؂�!");
		// �Q�[���I�[�o�[�ɂ���
	}
	m_player1->SetOtherPlayer(m_player2);
	m_player2->SetOtherPlayer(m_player1);
	m_player2->Update();
	m_player1->Update();
	m_Bg->Update();
	m_manhole->Update();
	// �v���C���[1�����}���z�[���ɐG�ꂽ��2�̏���
	if (m_manhole->CheckLeftCollision(m_player1->GetCollisionRect()))
	{
		m_player1->CheckManholeCollision(m_manhole);
		//printfDx("�v���C���[2�̏���!");
		m_gameOver = true;
		m_player2WinFlag = true;
		m_player1->SetGameOver(true);
		m_player2->SetGameOver(false);
		m_roundTimer->Stop();
		PlaySoundMem(m_gameOverBgHandle, DX_PLAYTYPE_BACK);
	}
	// �v���C���[2���E�}���z�[���ɐG�ꂽ��1�̏���
	else if (m_manhole->CheckRightCollision(m_player2->GetCollisionRect()))
	{
		m_player2->CheckManholeCollision(m_manhole);
		//printfDx("�v���C���[1�̏����I");
		m_gameOver = true;
		m_player1WinFlag = true;
		m_player2->SetGameOver(true);
		m_player1->SetGameOver(false);
		m_roundTimer->Stop();
		PlaySoundMem(m_gameOverBgHandle, DX_PLAYTYPE_BACK);
	}
}

void SceneMain::Draw()
{
	// �`��(��ɕ`�悵�����̂��O�ɏo��)
	m_Bg->Draw();
	m_player1->Draw();
	m_player2->Draw();
	m_roundTimer->Draw(640, 600);
	m_manhole->Draw();
	// �_�ŗp�̏���
	int now = GetNowCount();
	// 500�~���b���Ƃɓ_�ł���
	bool blink = ((now / 500) % 2) == 0;
	if (m_player1WinFlag&&blink)
	{
		DrawFormatString(350, 100, GetColor(255, 0, 0), "�v���C���[1�̏����I");
	}
	else if (m_player2WinFlag && blink)
	{
		DrawFormatString(350, 100, GetColor(255, 0, 0), "�v���C���[2�̏����I");
	}
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
}
