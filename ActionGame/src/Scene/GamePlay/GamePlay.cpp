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
#include"../../AssetStorage/AssetStorage.h"
#include"../../Actor/Enemy/Lizard/Lizard.h"
#include"../../Actor/UI/StateFrame.h"
#include"../../Actor/Gimmick/WarpCircle.h"
#include"../../Actor/Gimmick/HealCircle.h"
#include"../../Actor/Gimmick/MagicStone.h"
#include"../../Actor/Magic/Base/MagicList.h"

#include"../../Actor/Enemy/Goblin/Goblin.h"

void GamePlay::Start()
{
	isEnd = false;
	isPause = false;

	AssetStorage::getInstance().HandleRegister("./res/golem/golem.mv1", "Golem");
	AssetStorage::getInstance().HandleRegister("./res/overload/overlord_Arm.mv1", "Player");
	AssetStorage::getInstance().HandleRegister("./res/lizard/lizard.mv1", "Lizard");
	AssetStorage::getInstance().HandleRegister("./res/Goblin/Goblin.mv1", "Goblin");
	AssetStorage::getInstance().HandleRegister("./res/Rusted Longsword/LS.x", "Sword");
	AssetStorage::getInstance().HandleRegister("./res/IceNeedle/IceNeedle.mv1", "IceNeedle");

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
	mWorld->AddField(std::make_shared<Field>(MV1LoadModel("./res/Map/Stage1/Stage1.mv1")));
	//3D���f��----------------------------------------------------------------------------------------------------
	mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), Vector3(0,-0.5f,0)));
	//MapDateInput("./res/MapData01.csv");
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "�A�C�X�j�[�h��", Vector3(0, 10, -100), MagicList::ICENEEDLE));
	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Goblin>(mWorld.get(), Vector3(0.0f, 0.0f, -250)));
	//UI-----------------------------------------------------------------------------------------------------------
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerHP>(mWorld.get(), Vector3(3.0f, 7.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerMP>(mWorld.get(), Vector3(3.0f, 49.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<Frame>(mWorld.get(), Vector3(2.0f, 2.0f, 0.0f)));
	//-------------------------------------------------------------------------------------------------------------
	mWorld->AddCamera(std::make_shared<Camera>(mWorld.get()));
	mWorld->AddLight(std::make_shared<Light>(mWorld.get(), Vector3(0.5f, -1.0f, 1.0f)));
	PlayMusic("./res/Sound/Dungeon1_BGM.mp3", DX_PLAYTYPE_LOOP);

	mMenu = MagicMenu(mWorld.get());

}

void GamePlay::Update(float deltaTime)
{
	if (!isPause)
	{
		mWorld->Update(deltaTime);
		auto player = mWorld->FindActor("Player").get();
		if (0 >= ((Player*)player)->GetHP() || Input::getInstance().GetKeyTrigger(KEY_INPUT_T))
		{
			isEnd = true;
		}
		if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button2) || Input::getInstance().GetKeyTrigger(KEY_INPUT_P))
		{
			mMenu = MagicMenu(mWorld.get());
			isPause = true;
		}
	}
	else
	{
		mMenu.Update(deltaTime);
	}
}

void GamePlay::Draw() const
{
	mWorld->Draw();
	if (isPause) mMenu.Draw();
}

bool GamePlay::IsEnd() const
{
	return isEnd;
}

Scene GamePlay::Next() const
{
	return Scene::GAMEPLAY2;
}

void GamePlay::End()
{
	SoundManager::getInstance().Clear();
	mWorld = nullptr;
}

void GamePlay::HandleMessage(EventMessage message, void * param)
{
	switch (message)
	{
	case EventMessage::SCENE_END:
		isEnd = true;
		break;
	case EventMessage::PAUSE : 
		isPause = !isPause;
		break;
	}
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
	if(name == "Lizard") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Lizard>(mWorld.get(), position, rotate));
	if (name == "Warp") mWorld->AddActor(ActorGroup::Effect, std::make_shared<WarpCircle>(mWorld.get(), position, rotate));
	if (name == "Healing") mWorld->AddActor(ActorGroup::Effect, std::make_shared<HealCircle>(mWorld.get(), position, rotate));
}
