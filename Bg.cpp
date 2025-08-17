#include "Bg.h"
#include "DxLib.h"
#include"Game.h"
#include "Player.h"
#include<fstream>
#include <sstream>

namespace
{
	// �`�b�v�̑傫��
	constexpr int kChipSize = 48;
	// �`�b�v�̊g�嗦
	constexpr float kChipScale = 1.0f;
	constexpr int kChipNumX = 40;
	constexpr int kChipNumY = Game::kScreenHeight / kChipSize;	// 720 / 48 = 15

	// �`�b�v�̔z�u
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6},
		{0,1,2,3,4,5,6}
	};

}



Bg::Bg():
	m_pos{0,0},
	m_mapData(0),
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_pPlayer(nullptr)
{
	// �`�b�v�̏c���Ɖ���
	int graphW = 0;
	int graphH = 0;
	m_mapHandle = LoadGraph("data/mapChip.png");
	GetGraphSize(m_mapHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipSize;
	m_graphChipNumY = graphH / kChipSize;
}

Bg::~Bg()
{
	DeleteGraph(m_mapHandle);
}

void Bg::Init()
{
}

void Bg::End()
{
	
}

void Bg::Update()
{

}

void Bg::Draw()
{
	DrawMapChip();
}

void Bg::DrawMapChip()
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			int posX = static_cast<int>(x * kChipSize * kChipScale);
			int posY = static_cast<int>(y * kChipSize * kChipScale);

			// ��ʊO�͕`�悵�Ȃ�
			if (posX < 0 - kChipSize)continue;
			if (posX > Game::kScreenWidth)continue;
			if (posY < 0 - kChipSize)continue;
			if (posY > Game:: kScreenHeight)continue;

			// �ݒu����`�b�v
			int chipNo = kChipData[y][x];

			// �}�b�v�`�b�v�̃O���t�B�b�N�؂�o���ʒu
			int srcX = (chipNo % m_graphChipNumX) * kChipSize;
			int srcY = (chipNo / m_graphChipNumX) * kChipSize;

			// �}�b�v�`�b�v�̕`��
			DrawRectRotaGraph(static_cast<int>(posX+kChipSize*kChipScale*0.5f),
				static_cast<int>(posY + kChipSize * kChipScale * 0.5f), 
				srcX, srcY,
				kChipSize, kChipSize,
				kChipScale, 0.0f,
				m_mapHandle, true);

			// �����蔻��
			DrawBoxAA(posX, posY,
				posX + kChipSize * kChipScale, 
				posY + kChipSize * kChipScale,
				0x00ff00, false);
		}
	}
}

void Bg::LoadMapData()
{
}


