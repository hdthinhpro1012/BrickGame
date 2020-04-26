#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Rect.h"
#include "MainWindow.h"

class Paddle
{
public:
	Paddle() = default;
	Paddle(Vec2 in_pos);
	Rect GetRectToCompare();
	void Draw(Graphics& gfx);
	float Width();
	float WingWidth();
	void Update(Graphics& gfx, MainWindow& wnd, float delta_time);
private:
	Vec2 pos;
	static constexpr float width = 80.0f;
	static constexpr float wingWidth = 20.0f;
	static constexpr float height = 10.0f;
	static constexpr float speed = 5.0f;
	static constexpr Color wingColor = Colors::Red;
	static constexpr Color color = Colors::White;
};