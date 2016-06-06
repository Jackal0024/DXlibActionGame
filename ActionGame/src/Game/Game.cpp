#include<string>
#include "Game.h"
#include"DxLib.h"
#include"../Input/Input.h"
#include"../Input/KeyNum.h"
#include"../Math/Vector3.h"
#include"../Math//Matrix.h"
#include"../Math/BoundingSphere.h"
#include"../Actor/Camera/Camera.h"
#include"../Actor/Light/Light.h"


Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize()
{
	mWorld = std::make_shared<World>();
	mWorld->AddCamera(std::make_shared<Camera>(*mWorld));
	mWorld->AddLight(std::make_shared<Light>(*mWorld, Vector3(0.5f, -1.0f, 1.0f)));
}

void Game::Update()
{
	BoundingSphere bs(50.0f);
	bs.Draw();
	mWorld->Update(0.1f);
}

void Game::Draw()
{
	mWorld->Draw();
}

void Game::Finish()
{
	mWorld = nullptr;
}
