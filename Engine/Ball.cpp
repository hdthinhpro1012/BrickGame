#include "Ball.h"

Ball::Ball(Vec2& in_pos, Vec2& in_velocity)
	:
	pos(in_pos),
	velocity(in_velocity)
{
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update()
{
	pos += velocity;
}

void Ball::DoWallCollision(Rect& wall)
{
	if (pos.x < wall.left)
	{
		ReboundX();
		pos.x = wall.left;
	}
	if (pos.x > wall.right)
	{
		ReboundX();
		pos.x = wall.right;
	}
	if (pos.y < wall.top)
	{
		ReboundY();
		pos.y = wall.top;
	}
	if (pos.y > wall.bottom)
	{
		ReboundY();
		pos.y = wall.bottom;
	}
}

void Ball::DoPaddleCollision(Paddle& paddle)
{
	Rect rect = GetRectToCompare();
	Rect paddleRect = paddle.GetRectToCompare();
	if ((rect.IsOverlapWith(paddleRect)) && (velocity.y > 0))
	{
		if ((rect.left > paddleRect.left + paddle.WingWidth()) && (rect.right < paddleRect.right - paddle.WingWidth()))
		{
			ReboundY();
		}
		else
		{
			ReboundX();
			ReboundY();
		}
	}
}

void Ball::DoBrickCollision(Brick& brick)
{
	Rect rect = GetRectToCompare();
	Rect brickRect = brick.GetRectToCompare();
	if ((rect.IsOverlapWith(brickRect)) && (!brick.IsDestroyed()))
	{
		if (!((rect.left >= brickRect.left) && (rect.right <= brickRect.right)))
		{
			ReboundX();
		}
		if (!((rect.top >= brickRect.top) && (rect.bottom <= brickRect.bottom)))
		{
			ReboundY();
		}
		brick.Destroyed();
	}
}

void Ball::ReboundX()
{
	velocity.x = -velocity.x;
}

void Ball::ReboundY()
{
	velocity.y = -velocity.y;
}

Rect Ball::GetRectToCompare()
{
	Vec2 half = Vec2(radius, radius);
	return Rect(pos - half, pos + half);
}
