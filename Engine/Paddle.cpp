#include "Paddle.h"

Paddle::Paddle(Vec2 in_pos)
	:
	pos(in_pos)
{
}

Rect Paddle::GetRectToCompare()
{
	Vec2 half = Vec2(width / 2.0f, height / 2.0f);
	return Rect(pos - half, pos + half);
}

void Paddle::Draw(Graphics gfx)
{
	Rect rect = GetRectToCompare();
	rect.DrawRect(gfx, wingColor);
	rect.left += width / 2.0f;
	rect.right -= width / 2.0f;
	rect.DrawRect(gfx, color);
}

float Paddle::Width()
{
	return width;
}

float Paddle::WingWidth()
{
	return wingWidth;
}
