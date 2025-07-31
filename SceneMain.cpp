#include "SceneMain.h"
#include"Dxlib.h"
#include"Game.h"
#include "Ground.h"

SceneMain::SceneMain():
	m_player1GraphHandle(-1),
	m_player2GraphHandle(-1),
	m_player1(nullptr),
	m_player2(nullptr)
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::Init()
{
	//m_player1 = new Player();	// プレイヤーのインスタンスを生成	
	//m_player2 = new Player();	
	m_player1GraphHandle = LoadGraph("data/Player1.idle.png");	// プレイヤー1のグラフィックを読み込み
	m_player2GraphHandle = LoadGraph("data/Player2.idle.png");	// プレイヤー2のグラフィックを読み込み
	m_player1->Init(DX_INPUT_PAD1,Vec2(240,480),m_player1GraphHandle);// 初期化
	m_player2->Init(DX_INPUT_PAD2,Vec2(480, 480), m_player2GraphHandle);	// プレイヤーの初期化
	
}

void SceneMain::End()
{
	m_player1->End();	// 終了処理
	m_player2->End();	// プレイヤーの終了処理
}

void SceneMain::Update()
{
	m_player1->Update();
	m_player2->Update();	// プレイヤーの更新処理
	// グラフィックの解放
	DeleteGraph(m_player1GraphHandle);
	DeleteGraph(m_player2GraphHandle);
}

void SceneMain::Draw()
{
	m_player1->Draw();
	m_player2->Draw();	// プレイヤーの描画処理
}
