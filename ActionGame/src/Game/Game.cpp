#include<string>
#include "Game.h"
#include"DxLib.h"
#include"../Input/Input.h"
#include"../Input/KeyNum.h"
#include"../Math/Vector3.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize()
{
}

void Game::Update()
{
	
}

void Game::Draw()
{
	Vector3 v1(0.0f, 1.0f, 0.0f);
	VECTOR v2 = VGet(1.0f, 0.0f, 0.0f);
	v2 = v1;
	DrawFormatString(0, 0, GetColor(255, 255, 255), "v1  x=%f y=%f z=%f", v2.x, v2.y, v2.z);
}

void Game::Finish()
{
}
