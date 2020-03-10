#include "Rect.h"

Rect::Rect(float in_left, float in_right, float in_top, float in_bottom)
	:
	left(in_left),
	top(in_top),
	bottom(in_bottom),
	right(in_right)
{
}

Rect::Rect(const Vec2& topLeft, const Vec2& bottomRight)
{
	Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y);
}

Rect::Rect(const Vec2& topLeft, float width, float height)
{
	Rect(topLeft, topLeft + Vec2(width, height));
}

bool Rect::IsOverlapWith(const Rect& other) const
{
	return ((left < other.right) && (right > other.left)) && ((top < other.bottom) && (bottom > other.top));
}

void Rect::DrawRect(Graphics& gfx,const Color& color)
{
	gfx.DrawRect(left,top,right,bottom,color);
}
