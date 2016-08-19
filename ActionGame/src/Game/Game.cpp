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
#include"../Actor/Player/Player.h"
#include"../Actor/Enemy/Golem/Golem.h"
#include"../Field/Field.h"
#include"../Math/Line.h"
#include"../Actor/UI/PlayerHP.h"
#include"../Actor/UI/PlayerMP.h"
#include"../Sound/SoundManager.h"

#include"../Scene/Base/Scene.h"
#include"../Scene/GamePlay/GamePlay.h"
#include"../Scene/Title/Title.h"



Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize()
{
	mSceneManager.Initialize();
	mSceneManager.Add(Scene::TITLE, std::make_shared<Title>());
	mSceneManager.Add(Scene::GAMEPLAY, std::make_shared<GamePlay>());
	mSceneManager.Change(Scene::TITLE);
}

void Game::Update(float deltatime)
{
	Input::getInstance().Update();
	mSceneManager.Update(deltatime);
}

void Game::Draw()
{
	mSceneManager.Draw();
}

void Game::Finish()
{
}
