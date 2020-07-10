#include "Ball.h"
#include <cmath>

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

void Ball::Update(MainWindow& wnd)
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		velocity += Vec2(1.0f/60.0f, 1.0f/60.0f);
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		velocity -= Vec2(1.0f/60.0f, 1.0f/60.0f);
	}
	pos += velocity;
}

void Ball::DoWallCollision(Rect& wall)
{
	Rect rect = GetRectToCompare();
	if (rect.left < wall.left)
	{
		ReboundX();
		pos.x = wall.left + radius;
	}
	if (rect.right > wall.right)
	{
		ReboundX();
		pos.x = wall.right - radius;
	}
	if (rect.top < wall.top)
	{
		ReboundY();
		pos.y = wall.top + radius;
	}
	if (rect.bottom > wall.bottom)
	{
		ReboundY();
		pos.y = wall.bottom - radius;
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
		else if (((velocity.x > 0) && (pos.x < paddleRect.left)) || ((velocity.x < 0) && (pos.x > paddleRect.right)))
		{
			ReboundY();
			ReboundX();
		}
		else
		{
			ReboundY();
		}
	}
}

bool Ball::DoBrickCollision(Brick& brick)
{
	bool IsTouch = false;
	Rect rect = GetRectToCompare();
	Rect brickRect = brick.GetRectToCompare();
	Vec2 vecBrickToBall = pos - brick.GetCenter();

	//Handle case that x goes from inside to collide to brick'rear, instead bounce down now bounce left right
	if ((vecBrickToBall.x) * velocity.x >= 0)
	{
		if ((rect.IsOverlapWith(brickRect)) && (!brick.IsDestroyed()))
		{
			IsTouch = true;
			brick.Destroyed();
			ReboundY();
		}
	}
	//Normal case
	else
	{
		if ((rect.IsOverlapWith(brickRect)) && (!brick.IsDestroyed()))
		{
			IsTouch = true;
			brick.Destroyed();
			if (pos.x >= brickRect.left && pos.x <= brickRect.right)
			{
				ReboundY();
			}
			else
			{
				ReboundX();
			}

			/*  Old Ball bounce implementation, wrong and hard to conceptualize
			if (!((rect.left >= brickRect.left) && (rect.right <= brickRect.right)))
			{
				ReboundX();
			}
			if (!((rect.top >= brickRect.top) && (rect.bottom <= brickRect.bottom)))
			{
				if ((velocity.y < 0) && (rect.bottom > brickRect.bottom))
				{
					ReboundY();
				}
				else if ((velocity.y > 0) && (rect.top > brickRect.top))
				{
					ReboundY();
				}
			}
			*/
		}
	}
	return IsTouch;
}

float Ball::DistanceToBrick(Brick& brick)
{
	Rect brickRect = brick.GetRectToCompare();
	Vec2 distanceVec = Vec2((brickRect.left + brickRect.right) / 2 - pos.x, (brickRect.top + brickRect.bottom) / 2 - pos.y);
	return distanceVec.GetLength();
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
