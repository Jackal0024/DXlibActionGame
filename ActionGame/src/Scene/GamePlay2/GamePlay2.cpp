#include "GamePlay2.h"
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
#include"../../AssetStorage/AssetStorage.h"
#include"../../Actor/Enemy/Lizard/Lizard.h"
#include"../../Actor/UI/StateFrame.h"

void GamePlay2::Start()
{
	isEnd = false;

	AssetStorage::getInstance().HandleRegister("./res/golem/golem.mv1", "Golem");
	AssetStorage::getInstance().HandleRegister("./res/overload/overlord_Arm.mv1", "Player");
	AssetStorage::getInstance().HandleRegister("./res/lizard/lizard.mv1", "Lizard");
	AssetStorage::getInstance().HandleRegister("./res/Rusted Longsword/LS.x", "Sword");

	SoundManager::getInstance().Register("./res/Sound/PlayerDamage.ogg");
	SoundManager::getInstance().Register("./res/Sound/PlayerAttack.mp3");
	SoundManager::getInstance().Register("./res/Sound/EnemyVoice.ogg");
	SoundManager::getInstance().Register("./res/Sound/Fire.mp3");
	SoundManager::getInstance().Register("./res/Sound/Ice.mp3");

	mWorld = std::make_shared<World>();
	mWorld->AddEventMessageListener(
		[=](EventMessage msg, void* param) {
		HandleMessage(msg, param);
	});
	mWorld->AddField(std::make_shared<Field>(MV1LoadModel("./res/Map/Stage2/Stage2.mv1")));
	//3Dƒ‚ƒfƒ‹----------------------------------------------------------------------------------------------------
	//mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), Vector3(0,-0.5f,0)));
	MapDateInput("./res/MapData02.csv");
	//mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Ghost>(mWorld.get(), Vector3(0, 1.0f, -30)));
	//mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Lizard>(mWorld.get(), Vector3(-150, 1.0f, 0)));
	//UI-----------------------------------------------------------------------------------------------------------
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerHP>(mWorld.get(), Vector3(3.0f, 7.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerMP>(mWorld.get(), Vector3(3.0f, 49.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<Frame>(mWorld.get(), Vector3(2.0f, 2.0f, 0.0f)));
	//-------------------------------------------------------------------------------------------------------------
	mWorld->AddCamera(std::make_shared<Camera>(mWorld.get()));
	mWorld->AddLight(std::make_shared<Light>(mWorld.get(), Vector3(0.5f, -1.0f, 1.0f)));
	PlayMusic("./res/Sound/Dungeon1_BGM.mp3", DX_PLAYTYPE_LOOP);
}

void GamePlay2::Update(float deltaTime)
{
	mWorld->Update(deltaTime);
	auto player = mWorld->FindActor("Player").get();
	if (0 >= ((Player*)player)->GetHP())
	{
		isEnd = true;
	}
}

void GamePlay2::Draw() const
{
	mWorld->Draw();
}

bool GamePlay2::IsEnd() const
{
	return isEnd;
}

Scene GamePlay2::Next() const
{
	return Scene::TITLE;
}

void GamePlay2::End()
{
	SoundManager::getInstance().Clear();
	mWorld = nullptr;
}

void GamePlay2::HandleMessage(EventMessage message, void * param)
{
}

void GamePlay2::MapDateInput(std::string fileName)
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
		CharacterCreate(name, pos, rotate);
	}
}

void GamePlay2::CharacterCreate(std::string name, Vector3& position, Vector3& rotate)
{
	if (name == "Golem") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(mWorld.get(), position, rotate));
	if (name == "Player") mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), position, rotate));
	if (name == "Lizard") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Lizard>(mWorld.get(), position, rotate));
}