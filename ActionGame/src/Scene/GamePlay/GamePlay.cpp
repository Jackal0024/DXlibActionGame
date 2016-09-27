#include "GamePlay.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include"DxLib.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Math/Vector3.h"
#include"../../Math//Matrix.h"
#include"../../Actor/Camera/Camera.h"
#include"../../Actor/Light/Light.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Enemy/Golem/Golem.h"
#include"../../Field/Field.h"
#include"../../Actor/UI/PlayerHP.h"
#include"../../Actor/UI/PlayerMP.h"
#include"../../Sound/SoundManager.h"
#include"../../Actor/Enemy/Ghost/Ghost.h"
#include"../Base/Scene.h"

void GamePlay::Start()
{
	isEnd = false;
	SoundManager::getInstance().Register("./res/Sound/PlayerDamage.ogg");
	SoundManager::getInstance().Register("./res/Sound/PlayerAttack.ogg");
	SoundManager::getInstance().Register("./res/Sound/EnemyVoice.ogg");

	mWorld = std::make_shared<World>();
	mWorld->AddEventMessageListener(
		[=](EventMessage msg, void* param) {
		HandleMessage(msg, param);
	});
	mWorld->AddField(std::make_shared<Field>(MV1LoadModel("./res/Map/Stage1/Stage1.mv1")));
	//3Dƒ‚ƒfƒ‹----------------------------------------------------------------------------------------------------
	//mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), Vector3(0,-0.5f,0)));
	MapDateInput("./res/MapData01.csv");
	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Ghost>(mWorld.get(), Vector3(0, 1.0f, -30)));
	//UI-----------------------------------------------------------------------------------------------------------
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerHP>(mWorld.get(), Vector3(1.0f, 5.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerMP>(mWorld.get(), Vector3(1.0f, 37.0f, 0.0f)));
	//-------------------------------------------------------------------------------------------------------------
	mWorld->AddCamera(std::make_shared<Camera>(mWorld.get()));
	mWorld->AddLight(std::make_shared<Light>(mWorld.get(), Vector3(0.5f, -1.0f, 1.0f)));
	//mWorld->Start();
	PlayMusic("./res/Sound/Dungeon1_BGM.mp3", DX_PLAYTYPE_LOOP);
}

void GamePlay::Update(float deltaTime)
{
	mWorld->Update(deltaTime);
	auto player = mWorld->FindActor("Player").get();
	if (0 >= ((Player*)player)->GetHP())
	{
		isEnd = true;
	}
}

void GamePlay::Draw() const
{
	mWorld->Draw();
}

bool GamePlay::IsEnd() const
{
	return isEnd;
}

Scene GamePlay::Next() const
{
	return Scene::TITLE;
}

void GamePlay::End()
{
	SoundManager::getInstance().Clear();
	mWorld = nullptr;
}

void GamePlay::HandleMessage(EventMessage message, void * param)
{
}

void GamePlay::MapDateInput(std::string fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs) {
		return;
	}
	std::string str;
	while (true)
	{
		std::string name;
		Vector3 pos;
		Vector3 rotate;

		ifs >> name >> pos.x >> pos.y >> pos.z >> rotate.x >> rotate.y >> rotate.z;
		if (name == "")break;
		CharacterCreate(name, pos,rotate);
	}
}

void GamePlay::CharacterCreate(std::string name,Vector3& position, Vector3& rotate)
{
	if(name == "Golem") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(mWorld.get(), position,rotate));
	if (name == "Player") mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), position,rotate));
	if(name == "Ghost") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Ghost>(mWorld.get(), position, rotate));
}
