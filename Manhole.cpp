#include "Manhole.h"
#include "DxLib.h"

Manhole::Manhole():
	m_manhole1Handle(-1),
	m_manhole2Handle(-1),
	m_isHitManhole(false)
{
}

Manhole::~Manhole()
{
}

void Manhole::Init(int _handle1,int _handle2)
{
	m_manhole1Handle = _handle1;
	m_manhole2Handle = _handle2;
	m_isHitManhole = false;
}

void Manhole::End()
{

}

void Manhole::Update()
{

}

void Manhole::Draw()
{
	DrawExtendGraph(130, 450,130+96,450+96, m_manhole1Handle,true);
	DrawExtendGraph(1100,450,1100+96,450+96, m_manhole2Handle,true);
}

void Manhole::HitManhole(int _handle1, int _handle2)
{
	// もしマンホールのグラフィックに当たっていれば
}




