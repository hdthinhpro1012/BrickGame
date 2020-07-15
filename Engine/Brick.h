#pragma once
#include "Rect.h"
#include "Colors.h"
#include "Graphics.h" 

class Brick
{
public:
	Brick() = default;
	Brick(Rect in_rect, Color in_color);
	void Draw(Graphics& gfx);
	Rect GetRectToCompare();
	void Destroyed();
	bool IsDestroyed();
	Vec2 GetCenter();

public:
	static constexpr float width = 40.0f;
	static constexpr float height = 20.0f;
private:
	Rect rect;
	Color color;
	bool destroyed = true;
};