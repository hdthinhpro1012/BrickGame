#include "Ball.h"
#include <cmath>
#define PI 3.14159265

Ball::Ball(Vec2& in_pos, Vec2& in_velocity)
	:
	pos(in_pos),
	velocity(in_velocity)
{
	//Avoid using 0 and 11 direction
	for (int i = 0; i <= angleListNum - 1; i++)
	{
		angleList[i] = Vec2(float(sin(i * 15.0 * PI / 180)), float(cos(i * 15.0 * PI / 180)));
	}
	this->angle = angleList[angleId];
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(MainWindow& wnd, const float dt)
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		velocity += Vec2(dt, dt);
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		velocity -= Vec2(dt, dt);
	}
	angle = angleList[angleId];
	pos += (velocity * angle) * dt;
}

bool Ball::DoWallCollision(Rect& wall, Paddle& paddle)
{
	bool _isOver = false;
	Rect rect = GetRectToCompare();
	if (rect.left < wall.left)
	{
		ReboundX();
		pos.x = wall.left + radius;
		paddle.activate = true;
	}
	if (rect.right > wall.right)
	{
		ReboundX();
		pos.x = wall.right - radius;
		paddle.activate = true;
	}
	if (rect.top < wall.top)
	{
		ReboundY();
		pos.y = wall.top + radius;
		paddle.activate = true;
	}
	if (rect.bottom > wall.bottom)
	{
		ReboundY();
		pos.y = wall.bottom - radius;
		paddle.activate = true;
		_isOver = true;
	}
	return _isOver;
}

void Ball::DoPaddleCollision(Paddle& paddle, int mode)
{
	Rect rect = GetRectToCompare();
	Rect paddleRect = paddle.GetRectToCompare();
	if (paddle.activate)
	{
		if (mode == 0)
		{
			if (rect.IsOverlapWith(paddleRect))
			{
				ConvertAngle(paddle);
				if ((rect.left > paddleRect.left + paddle.WingWidth()) && (rect.right < paddleRect.right - paddle.WingWidth()))
				{
					ReboundY();
					paddle.activate = false;
				}
				else if (((velocity.x > 0) && (pos.x < paddleRect.left)) || ((velocity.x < 0) && (pos.x > paddleRect.right)))
				{
					ReboundX();
					ReboundY();
					paddle.activate = false;
				}
				else
				{
					ReboundY();
					paddle.activate = false;
				}
				//ConvertAngle(paddle); Change velocity then assess angle --> Wrong
			}
		}
		else
		{
			
		}
	}
}

bool Ball::DoBrickCollision(Brick& brick, Paddle& paddle)
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
			paddle.activate = true;
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
			paddle.activate = true;
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

void Ball::ConvertAngle(Paddle& paddle)
{
	if (this->GetPaddleCollsionSide(paddle) == 0)
	{
		return;
	}
	else if (this->GetPaddleCollsionSide(paddle) * velocity.x > 0)
	{
		angleId = min(Idmax, angleId + 1);
	}
	else
	{
		angleId = max(Idmin, angleId - 1);
	}
}

int Ball::GetPaddleCollsionSide(Paddle& paddle)
{
	//Right > 1, Middle = 0, Left < 0
	if (pos.x > paddle.GetCenter().x + (paddle.Width() / 4))
	{
		return 1;
	}
	//Why this case always be accept if the first one omitted
	else if (pos.x < paddle.GetCenter().x - (paddle.Width() / 4))
	{
		return -1;
	}
	else
	{
		return 0;
	}
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


