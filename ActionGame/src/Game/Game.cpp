#include<string>
#include "Game.h"
#include"DxLib.h"
#include"../Input/Input.h"
#include"../Input/KeyNum.h"
#include"../Math/Vector3.h"
#include"../Math//Matrix.h"
#include"../Math/BoundingSphere.h"

Vector3 pos;

Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize()
{
	ChangeLightTypeDir(VGet(-0.5f, -0.5f, 0.5f));
	pos = VGet(400, 400, 0);
}

void Game::Update()
{
	
}

void Game::Draw()
{
	Vector3 veloctiy;
	if (CheckHitKey(KEY_INPUT_UP))
	{
		veloctiy.y += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		veloctiy.y -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		veloctiy.x += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		veloctiy.x -= 1.0f;
	}
	pos += veloctiy;
	BoundingSphere sp1(pos,50);
	BoundingSphere sp2(Vector3(380.0f, 400.0f, 0.0f), 50);
	sp1.Draw();
	sp2.Draw();
	if(!sp1.Intersects(sp2)) DrawFormatString(0, 0, GetColor(255, 255, 255), "ê¨å˜ÇµÇƒÇ»Ç¢");
	else DrawFormatString(0, 0, GetColor(255, 255, 255), "ê¨å˜!");

}

void Game::Finish()
{
}
