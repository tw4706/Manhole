#include "Title.h"
#include"DxLib.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Init()
{

}

void Title::End()
{

}

void Title::Update()
{

}

void Title::Draw()
{
    static int alpha = 0;
    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE); // �w�i�̕`��
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawString(560, 320, "ManholeFight", GetColor(255, 0, 0));
    DrawString(530, 500, "Press:Return or Pad:�Z",GetColor(255,0,0));
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    alpha = (alpha < 255) ? alpha + 5 : 255; // �A���t�@�l�𑝂₵�ăt�F�[�h�C��
}
