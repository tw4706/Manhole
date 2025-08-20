#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene():
	m_isSceneEnd(false)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::End()
{

}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	DrawString(400,240,"ManholeFight",GetColor(255,0,0));
}

bool TitleScene::IsSceneEnd() const
{
	return m_isSceneEnd;
}
