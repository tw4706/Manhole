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
	// グラフィックのハンドル
	int m_mapHandle;
	// マップデータ
	int m_mapData;
	// マップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;
	Vec2 m_pos;
	Player* m_pPlayer;
};

