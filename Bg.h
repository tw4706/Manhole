#pragma once
#include "Player.h"
#include"Vec2.h"

class Bg
{
public:
	Bg();
	~Bg();

	void Init();
	void End();
	void Update();
	void Draw();

	void DrawMapChip();
	void LoadMapData();

private:
	// �O���t�B�b�N�̃n���h��
	int m_mapHandle;
	// �}�b�v�f�[�^
	int m_mapData;
	// �}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;
	Vec2 m_pos;
	Player* m_pPlayer;
};

