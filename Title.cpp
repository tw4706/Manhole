#include "Title.h"
#include"DxLib.h"
#include"Game.h"

Title::Title() :
    m_titleGraphHandle(-1),
    m_bgmHandle(-1)
{
}

Title::~Title()
{
}

void Title::Init()
{
    m_titleGraphHandle = LoadGraph("data/title.png");
    m_bgmHandle = LoadSoundMem("data/title.mp3");
    PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
    ChangeVolumeSoundMem(150, m_bgmHandle);
}

void Title::End()
{
    StopSoundMem(m_bgmHandle);
    DeleteSoundMem(m_bgmHandle);
}

void Title::Update()
{

}

void Title::Draw()
{
    DrawGraph(0,0, m_titleGraphHandle, true);
    // タイトル文字の描画とフェード
    static int alpha = 0;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawString(560, 320, "ManholeFight", GetColor(255, 0, 0));
    DrawString(530, 500, "Press:Return or Pad:〇",GetColor(255,0,0));
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    alpha = (alpha < 255) ? alpha + 5 : 255; // アルファ値を増やしてフェードイン
}
