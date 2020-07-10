#include "Brick.h"

Brick::Brick(Rect in_rect, Color in_color)
	:
	rect(in_rect),
	color(in_color),
	destroyed(false)
{
}

void Brick::Draw(Graphics& gfx)
{
	Rect NewRect = Rect(rect.left + 1.0f,rect.right - 1.0f,rect.top + 1.0f,rect.bottom - 1.0f);
	NewRect.DrawRect(gfx, color);
}

Vec2 Brick::GetCenter()
{
	return Vec2((rect.left + rect.right)/2, (rect.top + rect.bottom)/2);
}

Rect Brick::GetRectToCompare()
{
	return rect;
}

void Brick::Destroyed()
{
	destroyed = true;
}

bool Brick::IsDestroyed()
{
	return destroyed;
}
