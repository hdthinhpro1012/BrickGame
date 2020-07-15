#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Rect.h"
#include "MainWindow.h"
#include "Ball.h"

class Ball;

class Paddle
{
	friend class Ball;
public:
	Paddle() = default;
	Paddle(Vec2 in_pos);
	Rect GetRectToCompare();
	void Draw(Graphics& gfx);
	float Width();
	float WingWidth();
	void Update(Graphics& gfx, MainWindow& wnd, float delta_time);
	Vec2 GetCenter();
	static constexpr float width = 150.0f;
	static constexpr float height = 30.0f;
	static constexpr float wingWidth = 60.0f;
private:
	Vec2 pos;
	static constexpr float speed = 8.0f;
	static constexpr Color wingColor = Colors::Red;
	static constexpr Color color = Colors::White;
	bool activate = true;
};