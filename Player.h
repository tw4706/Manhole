#pragma once
#include"Vec2.h"
class Player
{
public:
	Player();
	~Player();

	void Init(int _padType,Vec2 _firstPos);
	void End();
	void Update();
	void Draw();

private:

	Vec2 m_pos;		// 座標
	int m_padType;	// パッドの種類
	float m_radius;	// 当たり判定の半径
	bool m_isTurn;	// 左右反転
};

