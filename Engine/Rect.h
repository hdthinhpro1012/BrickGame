#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"

class Rect
{
public:
	Rect() = default;
	Rect(float in_left, float in_top, float in_bottom, float in_right);
	Rect(const Vec2& topLeft, const Vec2& bottomRight);
	Rect(const Vec2& topLeft, float width, float height);
	bool IsOverlapWith(const Rect& another) const;
	void DrawRect(Graphics& gfx,const Color& color);
	
public:
	float left;
	float top;
	float bottom;
	float right;
};