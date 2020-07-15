/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <algorithm>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	wall(20.0f,gfx.ScreenWidth - 20.0f,20.0f, gfx.ScreenHeight - 20.0f),
	paddle(Vec2(200.0f,525.0f)),
	ball(Vec2(400.0f,200.0f), Vec2(6.0f,6.0f))
{
	Vec2 Vector(wall.left + 40.0f, wall.top + 20.0f);
	Rect rect;
	Color color;
	for (int x = 0; x <= brickRow - 1; x = x + 1)
	{
		switch (x)
		{
		case 0:
			color = Colors::Green;
			break;
		case 1:
			color = Colors::Blue;
			break;
		case 2:
			color = Colors::Red;
			break;
		case 3:
			color = Colors::Magenta;
			break;
		default:
			break;
		}
		for (int y = 0; y <= brickCol - 1; y = y + 1)
		{
			rect = Rect(Vector + Vec2(y * Brick::width + (y - 1) * 4.0f, x * Brick::height + (x - 1) * 4.0f),Brick::width,Brick::height);
			brick[x * (brickCol) + y] = Brick(rect,color);
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	if (!isOver)
	{
		static double dt;
		dt = ft.Mark();
		//Because run 8 times for each isOver check so after reset to true isOver is 
		//reset to false again in the next loop
		while (dt > 0.0f)
		{
			if (isOver)
			{
				break;
			}
			float delta_time = std::min(0.0025, dt);
			dt -= 0.0025;
			UpdateModel(delta_time * 60.0f);
		}
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(const float dt)
{
	static float pivot;
	static int index;
	static bool IsCollisionHappened;
	paddle.Update(gfx, wnd, dt);
	ball.Update(wnd, dt);
	isOver = ball.DoWallCollision(wall, paddle);
	ball.DoPaddleCollision(paddle, 0);

	IsCollisionHappened = false;
	pivot = 10000000.0f;
	index = -1;
	for (int i = 0; i <= 71; i++)
	{
		if (!brick[i].IsDestroyed())
		{
			if (ball.DistanceToBrick(brick[i]) < pivot)
			{
				pivot = ball.DistanceToBrick(brick[i]);
				index = i;
			}
		}		
	}
	if (index != -1)
	{
		ball.DoBrickCollision(brick[index], paddle);
	}
}

void Game::ComposeFrame()
{
	wall.DrawBorderOutside(gfx, Colors::LightGray);
	paddle.Draw(gfx);
	ball.Draw(gfx);
	for (int i = 0; i <= 71; i++)
	{
		if (!brick[i].IsDestroyed())
		{
			brick[i].Draw(gfx);
		}
	}
}
