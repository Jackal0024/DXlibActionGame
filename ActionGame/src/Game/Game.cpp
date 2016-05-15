#include<string>
#include "Game.h"
#include"DxLib.h"
#include"../Input/Input.h"
#include"../Input/KeyNum.h"

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
	VECTOR v1 = VGet(1.0f,0.0f,0.0f);
	VECTOR v2 = VGet(1.0f, 0.0f, 0.0f);
	const char* str;
	std::string st = std::to_string((v1+v2).x);
	str = st.data();
	DrawString(250, 240 - 32, str, GetColor(255, 255, 255));
}

void Game::Finish()
{
}
