#pragma once

#include "Brick.h"
#include "Paddle.h"
#include "Vec2.h"
#include "SpriteCodex.h"
#include "Graphics.h"
#include "Rect.h"

class Ball
{
public:
	Ball(Vec2& in_pos, Vec2& in_velocity);
	void Draw(Graphics& gfx);
	void Update();
	void DoWallCollision(Rect& wall);
	void DoPaddleCollision(Paddle& paddle);
	void DoBrickCollision(Brick& brick);
	void ReboundX();
	void ReboundY();
	Rect GetRectToCompare();
private:
	Vec2 pos; // Position at the center of ball rectangle
	Vec2 velocity;
	static constexpr float radius = 7.0f;
};