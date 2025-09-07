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
	void Update(const Vec2& _player1Pos, const Vec2& _player2Pos);
	void Draw();

	// プレイヤーがマンホールに当たっているかどうか
	bool CheckLeftCollision(const Rect& playerRect);
	bool CheckRightCollision(const Rect& playerRect);
	// マンホールの位置を取得
	Vec2 GetCenter()const;

private:
	// マンホールのハンドル
	int m_handle1;
	int m_handle2;
	// マンホールに当たっているか
	bool m_leftTriggered;
	bool m_rightTriggered;
	// 危険を知らせる用のグラフィックはンドル
	int m_warningHandle;
	// 点滅用のタイマー
	int m_blinkTimer;
	// 点滅用のフラグ
	bool m_blinkFlag;
	// 左右の表示更新
	bool m_showLeftWarning;
	bool m_showRightWarning;

	// 当たり判定用の矩形
	Rect m_colRect;
	Rect m_leftRect;
	Rect m_rightRect;

};

