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
#include"../Scene/Stage1/GamePlay.h"
#include"../Scene/Stage2/GamePlay2.h"
#include"../Scene/Stage1/BackStage1.h"
#include"../Scene/Stage2/BackStage2.h"
#include"../Scene/Stage3/GamePlay3.h"
#include"../Scene/Title/Title.h"
#include"../Scene/Result/ResultScene.h"
#include"../Scene/Demo/DemoScene.h"



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
	mSceneManager.Add(Scene::DEMO , std::make_shared<DemoScene>());
	mSceneManager.Add(Scene::STAGE1, std::make_shared<GamePlay>());
	mSceneManager.Add(Scene::STAGE1_BACK, std::make_shared<BackStage1>());
	mSceneManager.Add(Scene::STAGE2, std::make_shared<GamePlay2>());
	mSceneManager.Add(Scene::STAGE2_BACK, std::make_shared<BackStage2>());
	mSceneManager.Add(Scene::STAGE3, std::make_shared<GamePlay3>());
	mSceneManager.Add(Scene::RESULT, std::make_shared<ResultScene>());
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
