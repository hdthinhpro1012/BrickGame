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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	wall(0.0f,gfx.ScreenWidth - 1.0f,0.0f, gfx.ScreenHeight - 1.0f),
	paddle(Vec2(360.0f,550.0f)),
	ball(Vec2(400.0f,200.0f), Vec2(2.5f,2.5f))
{
	Vec2 Vector(40.0f, 40.0f);
	Rect rect;
	Color color;
	for (int x = 0; x <= 3; x++)
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
		for (int y = 0; y <= 11; y++)
		{
			rect = Rect(Vector + Vec2(y * Brick::width,x * Brick::height),Brick::width,Brick::height);
			brick[x * 12 + y] = Brick(rect,color);
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	paddle.Update(gfx, wnd, 1.0f/60.0f);
	ball.Update(wnd);
	ball.DoWallCollision(wall);
	ball.DoPaddleCollision(paddle);
	for (int i = 0; i <= 47; i++)
	{
		if (ball.DoBrickCollision(brick[i]))
		{
			break;
		}
	}
}

void Game::ComposeFrame()
{
	paddle.Draw(gfx);
	ball.Draw(gfx);
	for (int i = 0; i <= 47; i++)
	{
		if (!brick[i].IsDestroyed())
		{
			brick[i].Draw(gfx);
		}
	}
}
