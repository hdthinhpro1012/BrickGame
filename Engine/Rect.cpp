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
	:
	Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y) //Special use of intialize list calling its own constructor to intialize itself
{
	//Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y); //Initial the newly create object, make no change to itself
}

Rect::Rect(const Vec2& topLeft, float width, float height) //Special use of intialize list calling its own constructor to intialize itself
	:
	Rect(topLeft, topLeft + Vec2(width, height))
{
	//Rect(topLeft, topLeft + Vec2(width, height)); //Initial the newly create object, make no change to itself
}

bool Rect::IsOverlapWith(const Rect& other) const
{
	return ((left < other.right) && (right > other.left)) && ((top < other.bottom) && (bottom > other.top));
}

void Rect::DrawRect(Graphics& gfx,const Color& color)
{
	gfx.DrawRect(int(left),int(top),int(right),int(bottom),color);
}

void Rect::DrawBorderOutside(Graphics& gfx, const Color& color)
{
	gfx.DrawRect(int(left), int(top - 5.0f), int(right), int(top), color);
	gfx.DrawRect(int(left), int(bottom), int(right), int(bottom + 5.0f), color);
	gfx.DrawRect(int(left - 5.0f), int(top - 5.0f), int(left), int(bottom + 5.0f), color);
	gfx.DrawRect(int(right), int(top - 5.0f), int(right + 5.0f), int(bottom + 5.0f), color);
}
