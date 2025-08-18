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
	m_manhole1GraphHandle(-1),
	m_manhole2GraphHandle(-1),
	m_timer(0),
	m_gameOver(false),
	m_player1(nullptr),
	m_player2(nullptr),
	m_Bg(nullptr),
	m_manhole1(nullptr),
	m_manhole2(nullptr),
	m_roundTimer(nullptr)
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// 現在の時間を取得
	m_timer = GetNowCount();
	m_gameOver = false;
	// プレイヤーのインスタンスを生成	
	m_player1 = new Player();	
	m_player2 = new Player();
	m_Bg = new Bg();
	m_manhole1 = new Manhole();
	m_manhole2 = new Manhole();
	m_roundTimer = new Timer();
	//グラフィックの読み込み
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
	m_manhole1GraphHandle = LoadGraph("data/Manhole1.png");
	m_manhole2GraphHandle = LoadGraph("data/Manhole2.png");

	m_player1->Init(DX_INPUT_PAD1,Vec2(400,480),m_player1GraphHandle,m_player1AttackGraphHandle, m_player1WeakAttackGraphHandle,m_player1RunGraphHandle,m_player1HurtGraphHandle,false);
	m_player2->Init(DX_INPUT_PAD2,Vec2(800, 480), m_player2GraphHandle, m_player2AttackGraphHandle, m_player2WeakAttackGraphHandle, m_player2RunGraphHandle, m_player2HurtGraphHandle,true);
	m_Bg->Init();
	m_manhole1->Init(m_manhole1GraphHandle,m_manhole2GraphHandle);
	m_manhole2->Init(m_manhole1GraphHandle, m_manhole2GraphHandle);
	m_roundTimer->Init(30.0f);
	m_roundTimer->Reset();
	m_roundTimer->Start();
}

void SceneMain::End()
{
	m_player1->End();	// プレイヤーの終了処理
	m_player2->End();
	m_Bg->End();		// 背景の終了処理
	m_manhole1->End();	// マンホールの終了処理
	m_manhole2->End();
	m_roundTimer->End();// タイマーの終了処理
	// グラフィックの解放
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
}

void SceneMain::Update()
{
	int currentTime = GetNowCount();
	float deltaTime = (currentTime - m_timer) / 1000.0f;
	m_timer = currentTime;
	m_roundTimer->Update(deltaTime);
	if (m_roundTimer->IsTimeUp())
	{
		printfDx("時間切れ!");
		// ゲームオーバーにする
		m_gameOver = true; 
	}
	m_player1->Update();
	m_player2->Update();
	m_player1->SetOtherPlayer(m_player2);
	m_player2->SetOtherPlayer(m_player1);
	m_Bg->Update();
	m_manhole1->Update();
	m_manhole2->Update();
	// プレイヤー1が左マンホールに触れたら2の勝利
	if (m_manhole1->IsHitLeft(m_player1->GetCollisionRect()))
	{
		printfDx("プレイヤー2の勝利!");
		m_gameOver = true;
	}
	// プレイヤー2が右マンホールに触れたら1の勝利
	else if (m_manhole2->IsHitRight(m_player2->GetCollisionRect()))
	{
		printfDx("プレイヤー1の勝利！");
		m_gameOver = true;
	}
}

void SceneMain::Draw()
{
	// 描画(後に描画したものが前に出る)
	m_roundTimer->Draw(1080,20);
	m_Bg->Draw();
	m_manhole1->Draw();
	m_manhole2->Draw();
	m_player1->Draw();
	m_player2->Draw();
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
}
