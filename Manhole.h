#pragma once
#include"Vec2.h"
#include"Rect.h"
class Manhole
{
public:
	Manhole();
	~Manhole();

	void Init(int _handle1,int _handle2);
	void End();
	void Update();
	void Draw();

	// プレイヤーがマンホールに当たっているかどうか
	bool IsHitLeft(const Rect& playerRect);
	bool IsHitRight(const Rect& playerRect);
	// マンホールの当たり判定をなくす
	void DisableCollision();

private:
	// マンホールのハンドル
	int m_manhole1Handle;
	int m_manhole2Handle;
	// マンホールに当たっているか
	bool m_isHitManhole;
	bool m_leftTriggerFlag;
	bool m_rightTriggerFlag;
	Rect m_colRect; // 当たり判定用の矩形
	Rect m_leftRect;
	Rect m_rightRect;

};

