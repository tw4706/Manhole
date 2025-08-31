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
	m_winPlayer1GraphHandle(-1),
	m_winPlayer2GraphHandle(-1),
	m_timer(0),
	m_startTimer(0),
	m_isStartSeq(false),
	m_gameStartSoundHandle(-1),
	m_gameStartUI1Handle(-1),
	m_gameStartUI2Handle(-1),
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
	// �Q�[���X�^�[�g�̃J�E���g�_�E���p�^�C�}�[��������
	m_startTimer = 0;
	m_isStartSeq = true;
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
	m_winPlayer1GraphHandle = LoadGraph("data/Win1.png");
	m_winPlayer2GraphHandle = LoadGraph("data/Win2.png");
	m_gameStartUI1Handle = LoadGraph("data/UI1.png");
	m_gameStartUI2Handle = LoadGraph("data/UI2.png");
	//BGM�̓ǂݍ��݂ƍĐ�
	m_gameStartSoundHandle = LoadSoundMem("data/ReadyFight.mp3");
	m_bgmHandle = LoadSoundMem("data/game.mp3");
	ChangeVolumeSoundMem(110, m_bgmHandle);          // ���ʂ̒���
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);     // ���[�v�Đ�
	m_gameOverBgHandle = LoadSoundMem("data/gameOver.mp3");
	ChangeVolumeSoundMem(150, m_gameOverBgHandle);

	m_roundTimer->Init(30.0f);
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
	DeleteGraph(m_player1FallGraphHandle);
	DeleteGraph(m_player2FallGraphHandle);
	DeleteGraph(m_manhole1GraphHandle);
	DeleteGraph(m_manhole2GraphHandle);
	DeleteGraph(m_winPlayer1GraphHandle);
	DeleteGraph(m_winPlayer2GraphHandle);
	DeleteGraph(m_gameStartUI1Handle);
	DeleteGraph(m_gameStartUI2Handle);
	delete m_roundTimer;
	DeleteSoundMem(m_gameStartSoundHandle);
	DeleteSoundMem(m_bgmHandle);
	StopSoundMem(m_gameOverBgHandle);
	DeleteSoundMem(m_gameOverBgHandle);
}

void SceneMain::Update()
{
	// �����{�^������
	if (CheckHitKey(KEY_INPUT_V))
	{
		m_gameOver = true;
		m_player1->SetGameOver(true);
		m_player2->SetGameOver(false);
		m_player1WinFlag = true;
		PlaySoundMem(m_gameOverBgHandle, DX_PLAYTYPE_BACK);
	}
	else if(CheckHitKey(KEY_INPUT_B))
	{ 
		m_gameOver = true;
		m_player1->SetGameOver(false);
		m_player2->SetGameOver(true);
		m_player2WinFlag = true;
		PlaySoundMem(m_gameOverBgHandle, DX_PLAYTYPE_BACK);
	}
	if (m_isStartSeq)
	{
		m_startTimer++;
		if (m_startTimer == 1)
		{
			PlaySoundMem(m_gameStartSoundHandle, DX_PLAYTYPE_BACK);
			ChangeVolumeSoundMem(200, m_gameStartSoundHandle);
		}

		// 3�b��ɊJ�n
		if (m_startTimer > 180)
		{
			m_isStartSeq = false;
		}
		return; // �J�E���g�_�E�����̓v���C���[�͓����Ȃ�
	}
	int currentTime = GetNowCount();
	float deltaTime = (currentTime - m_timer) / 1000.0f;
	m_timer = currentTime;
	if (CheckHitKey(KEY_INPUT_R))
	{
		End();   // ���݂̃��\�[�X�����
		Init();  // �ď�����
	}
	// �Q�[���̃��X�^�[�g
	if (m_gameOver)
	{
		// ���҂͓������Ƃ��\
		if (m_player2WinFlag)
		{
			m_player1->Update(deltaTime);
			m_player2->Update(deltaTime);
		}
		else if (m_player1WinFlag)
		{
			m_player1->Update(deltaTime);
			m_player2->Update(deltaTime);
		}
		StopSoundMem(m_bgmHandle);
		// R�L�[�������ꂽ�烊�X�^�[�g
		return;
	}
	m_roundTimer->Update(deltaTime);
	if (m_roundTimer->IsTimeUp())
	{
		printfDx("���Ԑ؂�!");
		if (m_roundTimer->IsTimeUp() && !m_gameOver)
		{
			Vec2 manholeCenter = m_manhole->GetCenter();
			Vec2 p1Center = m_player1->GetCollisionRect().GetCenter();
			Vec2 p2Center = m_player2->GetCollisionRect().GetCenter();

			float dist1 = fabs(p1Center.x - manholeCenter.x);
			float dist2 = fabs(p2Center.x - manholeCenter.x);

			if (dist1 > dist2)
			{
				m_player1->SetGameOver(true);
				m_player2->SetGameOver(false);
				m_player1WinFlag = true;
			}
			else if (dist2 > dist1)
			{
				m_player2->SetGameOver(true);
				m_player1->SetGameOver(false);
				m_player2WinFlag = true;
			}
			else
			{
				m_player1->SetGameOver(true);
				m_player2->SetGameOver(true);
			}
			m_gameOver = true;
			m_roundTimer->Stop();
			PlaySoundMem(m_gameOverBgHandle, DX_PLAYTYPE_BACK);
		}

	}
	m_player1->SetOtherPlayer(m_player2);
	m_player2->SetOtherPlayer(m_player1);
	m_player2->Update(deltaTime);
	m_player1->Update(deltaTime);
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
	// �Q�[���^�[�g�̃J�E���g�_�E��
	if (m_isStartSeq)
	{
		if (m_startTimer < 120)
		{
			DrawExtendGraph(500, 200, 800, 400, m_gameStartUI1Handle, true);
		}
		else
		{
			DrawExtendGraph(500, 200, 800, 400, m_gameStartUI2Handle, true);

		}
	}
	// �_�ŗp�̏���
	int now = GetNowCount();
	// 500�~���b���Ƃɓ_�ł���
	bool blink = ((now / 500) % 2) == 0;
	if (m_player1WinFlag&&blink)
	{
		DrawExtendGraph(500, 200, 800, 400, m_winPlayer1GraphHandle, true);
	}
	else if (m_player2WinFlag && blink)
	{
		DrawExtendGraph(500, 200, 800, 400, m_winPlayer2GraphHandle, true);
	}
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
}
