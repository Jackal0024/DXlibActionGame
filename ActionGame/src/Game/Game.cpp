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


Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize()
{
	mWorld = std::make_shared<World>();
	mWorld->AddField(std::make_shared<Field>(MV1LoadModel("./res/Map/Stage0/Stage0.mv1")));
	mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(*mWorld, Vector3(0.0f,1.0f, -30.0f)));
	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(*mWorld, Vector3(0.0f, 0.0f, 1.0f)));
	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(*mWorld, Vector3(20.0f, 0.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(*mWorld, Vector3(40.0f, 0.0f, 0.0f)));
	mWorld->AddCamera(std::make_shared<Camera>(*mWorld));
	mWorld->AddLight(std::make_shared<Light>(*mWorld, Vector3(0.5f, -1.0f, 1.0f)));
	mWorld->Start();
}

void Game::Update(float deltatime)
{
	mWorld->Update(deltatime);
}

void Game::Draw()
{
	mWorld->Draw();
	if (Input::getInstance().GetKeyTrigger(Keycode::PAD_Button17))
	{
		printfDx("�����ꂽ");
	}
}

void Game::Finish()
{
	mWorld = nullptr;
}
