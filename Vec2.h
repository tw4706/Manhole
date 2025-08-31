#pragma once
class Vec2
{
public:
	float x;
	float y;

public:
	Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};