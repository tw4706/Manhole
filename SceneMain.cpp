#include "SceneMain.h"
#include"Dxlib.h"
#include"Game.h"
#include "Bg.h"
#include<cmath>

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
	m_bgGraphHandle(-1),
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
	// プレイヤーのインスタンスを生成	
	m_player1 = new Player();	
	m_player2 = new Player();
	m_bg = new Bg();
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
	m_bgGraphHandle = LoadGraph("data/Bg.png");

	m_player1->Init(DX_INPUT_PAD1,Vec2(400,480),m_player1GraphHandle,m_player1AttackGraphHandle, m_player1WeakAttackGraphHandle,m_player1RunGraphHandle,m_player1HurtGraphHandle,false);
	m_player2->Init(DX_INPUT_PAD2,Vec2(800, 480), m_player2GraphHandle, m_player2AttackGraphHandle, m_player2WeakAttackGraphHandle, m_player2RunGraphHandle, m_player2HurtGraphHandle,true);
	m_bg->Init(m_bgGraphHandle);
}

void SceneMain::End()
{
	m_player1->End();	// 終了処理
	m_player2->End();	// プレイヤーの終了処理
	m_bg->End();
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
	DeleteGraph(m_bgGraphHandle);
}

void SceneMain::Update()
{
	// プレイヤーの処理の更新
	m_player1->Update();
	m_player2->Update();
	m_player1->SetOtherPlayer(m_player2);
	m_player2->SetOtherPlayer(m_player1);
	m_bg->Update();
	UpdateGame();
}

void SceneMain::Draw()
{
	// 描画(後に描画したものが前に出る)
	m_bg->Draw();
	m_player1->Draw();
	m_player2->Draw();	// プレイヤーの描画処理
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
}

void SceneMain::UpdateGame()
{
	const float Player1X = m_player1->GetPosX();
	const float Player1Y = m_player1->GetPosY();
	const float Player1Radius = m_player1->GetPosRadius();
	
	const float Player2X = m_player2->GetPosX();
	const float Player2Y = m_player2->GetPosY();
	const float Player2Radius = m_player2->GetPosRadius();

	// 距離の計算
	float distX = Player1X - Player2X;
	float distY = Player1Y - Player2Y;

	float dist = (distX * distX) + (distY * distY);
	// 距離
	dist = sqrtf(dist);

	if (dist < (Player1Radius + Player2Radius))
	{
		printfDx("あたっている！\n");
	}

}
