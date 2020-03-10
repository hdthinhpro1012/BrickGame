#include "Brick.h"

Brick::Brick(Rect in_rect, Color in_color)
	:
	rect(in_rect),
	color(in_color)
{
}

void Brick::Draw(Graphics& gfx, Color& color)
{
	rect.DrawRect(gfx, color);
}

Rect Brick::GetRectToCompare()
{
	return rect;
}

void Brick::Destroyed()
{
	destroyed = 0;
}

bool Brick::IsDestroyed()
{
	return destroyed;
}
