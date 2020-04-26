#include "Paddle.h"

Paddle::Paddle(Vec2 in_pos)
	:
	pos(in_pos)
{
}

Rect Paddle::GetRectToCompare()
{
	Vec2 half = Vec2(width / 2.0f, height / 2.0f);
	Vec2 center = pos;
	return Rect(center - half, center + half);
}

void Paddle::Draw(Graphics& gfx)
{
	Rect rect = GetRectToCompare();
	rect.DrawRect(gfx, wingColor);
	rect.left += wingWidth / 2.0f;
	rect.right -= wingWidth / 2.0f;
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

void Paddle::Update(Graphics& gfx, MainWindow& wnd, float delta_time)
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * delta_time * 60;
	}
	if (pos.x < 0.0f + width/2.0f + 1.0f)
	{
		pos.x = 0.0f + width / 2.0f;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * delta_time * 60;
	}
	if (pos.x > gfx.ScreenWidth - 1.0f - width/2.0f - 1.0f)
	{
		pos.x = gfx.ScreenWidth - 1.0f - width / 2.0f;
	}
}
