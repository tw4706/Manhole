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

private:
	// �O���t�B�b�N�̃n���h��
	int m_mapHandle;
	// �o�b�N�̔w�i�̃O���t�B�b�N�n���h��
	int m_bgHandle;
};

