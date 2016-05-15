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
	const char* str;
	std::string st = std::to_string(Input::getInstance().GetRightAnalogStick().y);
	str = st.data();
	DrawString(250, 240 - 32, str, GetColor(255, 255, 255));
}

void Game::Finish()
{
}
