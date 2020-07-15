#pragma once

#include "Brick.h"
#include "Paddle.h"
#include "Vec2.h"
#include "SpriteCodex.h"
#include "Graphics.h"
#include "Rect.h"
#include "MainWindow.h"

class Paddle;

class Ball
{
public:
	Ball(Vec2& in_pos, Vec2& in_velocity);
	void Draw(Graphics& gfx);
	void Update(MainWindow& wnd, const float dt);
	bool DoWallCollision(Rect& wall, Paddle& paddle);
	void DoPaddleCollision(Paddle& paddle, int mode);
	bool DoBrickCollision(Brick& brick, Paddle& paddle);
	void ConvertAngle(Paddle& paddle);
	int GetPaddleCollsionSide(Paddle& paddle);
	float DistanceToBrick(Brick& brick);
	void ReboundX();
	void ReboundY();
	Rect GetRectToCompare();
private:
	Vec2 angle;
	Vec2 pos; // Position at the center of ball rectangle
	Vec2 velocity;
	static constexpr int angleListNum = 24;
	static constexpr int Idmin = 1;
	static constexpr int Idmax = 5;
	static constexpr float radius = 7.0f;
	int angleId = 3;
	Vec2 angleList[angleListNum];
};