#include "Title.h"
#include"DxLib.h"
#include"Game.h"
#include<cmath>

namespace
{
    // �g�嗦
    constexpr float kScaleX = 0.3f;
    constexpr float kScaleY = 0.28f;

    // �^�C�g�����S�E�����̃T�C�Y
    constexpr int kDrawWidth = 600;
    constexpr int kDrawHeight = 400;
    // �`��̒����p�萔
    constexpr int kStrOffsetY = 80;
}

Title::Title() :
    m_titleGraphHandle(-1),
	m_titleLogoHandle(-1),
    m_titleStrHandle(-1),
    m_bgmHandle(-1),
	m_pushHandle(-1)
{
}

Title::~Title()
{
}

void Title::Init()
{
    m_titleGraphHandle = LoadGraph("data/title_1.png");
	m_titleLogoHandle = LoadGraph("data/titleL.png");
    m_titleStrHandle = LoadGraph("data/str.png");
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
    int drawX = (Game::kScreenWidth - kDrawWidth) / 2;
    int drawY = (Game::kScreenHeight -kDrawHeight) / 2-50;

    int strWidth, strHeight;
    GetGraphSize(m_titleStrHandle, &strWidth, &strHeight);

    int strDrawWidth = static_cast<int>(strWidth * kScaleX);
    int strDrawHeight = static_cast<int>(strHeight * kScaleY);

    // X���W�͒���
    int strX = (Game::kScreenWidth - strDrawWidth) / 2;
    // Y���W�͒�����艺
    int strY = (Game::kScreenHeight - strDrawHeight) / 2 + 150;

    DrawGraph(0,0, m_titleGraphHandle, true);
    // ���S����ʒ����ɗ���悤�ɔz�u
	DrawExtendGraph(drawX, drawY, drawX + kDrawWidth, 
        drawY + kDrawHeight,m_titleLogoHandle, true);
    // �^�C�g�������̕`��ƃt�F�[�h
    int alpha = 128 + 
        static_cast<int>(127 * sin(GetNowCount() / 100.0));
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);    // �A���t�@�̒l�������I�ɕω������āA�_�ŕ��Ɍ�����
    DrawRectExtendGraphF(
        strX, strY,
        strX + strDrawWidth, strY + strDrawHeight+30,
        0, 0, strWidth, strHeight,
        m_titleStrHandle, true
    );
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
