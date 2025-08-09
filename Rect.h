#pragma once
#include"Vec2.h"
class Rect
{
public:
	Rect();
	~Rect();

	void init(float _left,float _top,float _width,float _height);
	void End();
	void Update();
	void Draw(unsigned int Color,bool isFill);

	// ���S���W�ƕ��������w��
	void SetCenter(float x, float y, float width, float height);
	// ��`�̕����擾
	float GetWidth()const;
	// ��`�̍������擾
	float GetHeight()const;
	// ��`�̒��S���W���擾
	Vec2 GetCenter() const;
	// ��`�̍����X���W���擾
	float GetLeft()const { return m_left; }
	// ��`�̍����Y���W���擾
	float GetTop()const { return m_top; }
	// ��`�̉E����X���W���擾
	float GetRight()const { return m_right; }
	// ��`�̉E����Y���W���擾
	float GetBottom()const { return m_bottom; }
	// ��`�̓����蔻����擾
	bool IsCollision(const Rect& rect);

public:
	float m_left;   // ��`�̍����X���W	
	float m_top;    // ��`�̍����Y���W
	float m_right;  // ��`�̉E����X���W
	float m_bottom; // ��`�̉E����Y���W


private:


};

