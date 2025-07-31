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
	m_player1 = new Player();	// プレイヤーのインスタンスを生成	
	m_player2 = new Player();	
	m_player1->Init(DX_INPUT_PAD1,Vec2(240,480));// 初期化
	m_player2->Init(DX_INPUT_PAD2,Vec2(480, 480));	// プレイヤーの初期化
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
}

void SceneMain::Draw()
{
	m_player1->Draw();
	m_player2->Draw();	// プレイヤーの描画処理
}
