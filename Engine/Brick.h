#pragma once
#include "Rect.h"
#include "Colors.h"
#include "Graphics.h" 

class Brick
{
public:
	Brick() = default;
	Brick(Rect in_rect, Color in_color);
	void Draw(Graphics& gfx, Color& color);
	Rect GetRectToCompare();
	void Destroyed();
	bool IsDestroyed();

public:
	static constexpr float width = 60.0f;
	static constexpr float height = 20.0f;
private:
	Rect rect;
	Color color;
	bool destroyed = false;
};