#include "GamePlay3.h"
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
#include"../../Actor/UI/FadeEffect.h"
#include"../../Actor/Enemy/Goblin/Goblin.h"
#include"../../Actor/Enemy/Mummy/Mummy.h"

void GamePlay3::Start()
{
	isEnd = false;
	isPause = false;
	isDraw = false;
	mFade = std::make_shared<Fadeeffect>(mWorld.get(), 255.0f, 0.0f, 1.0f, "./res/Texture/Smoke.jpg");
	isFade = false;

	AssetStorage::getInstance().HandleRegister("./res/golem/golem.mv1", "Golem");
	AssetStorage::getInstance().HandleRegister("./res/overload/overlord_Arm.mv1", "Player");
	AssetStorage::getInstance().HandleRegister("./res/lizard/lizard.mv1", "Lizard");
	AssetStorage::getInstance().HandleRegister("./res/Goblin/Goblin.mv1", "Goblin");
	AssetStorage::getInstance().HandleRegister("./res/Mummy/mummy.mv1", "Mummy");
	AssetStorage::getInstance().HandleRegister("./res/Rusted Longsword/LS.x", "Sword");
	AssetStorage::getInstance().HandleRegister("./res/IceNeedle/IceNeedle.mv1", "IceNeedle");
	AssetStorage::getInstance().HandleRegister("./res/RockBlast/Rock.mv1", "Rock");
	AssetStorage::getInstance().HandleRegister("./res/NeedleBomb/Needle.mv1", "Mine");
	AssetStorage::getInstance().HandleRegister("./res/NeedleBomb/Bomb.mv1", "Bomb");
	AssetStorage::getInstance().HandleRegister("./res/BlackSpear/BlackSpear.mv1", "BlackSpear");
	AssetStorage::getInstance().HandleRegister("./res/BlackSpear/Circle.mv1", "SpearCircle");
	AssetStorage::getInstance().HandleRegister("./res/FireWall/FireWall.mv1", "FireWall");

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
	mWorld->AddField(std::make_shared<Field>(MV1LoadModel("./res/Map/Stage3/Stage3.mv1")));
	//3D���f��----------------------------------------------------------------------------------------------------
	MapDateInput("./res/MapData03.csv");
	//UI-----------------------------------------------------------------------------------------------------------
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerHP>(mWorld.get(), Vector3(3.0f, 7.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<PlayerMP>(mWorld.get(), Vector3(3.0f, 49.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<Frame>(mWorld.get(), Vector3(2.0f, 2.0f, 0.0f)));
	//-------------------------------------------------------------------------------------------------------------
	mWorld->AddCamera(std::make_shared<Camera>(mWorld.get()));
	mWorld->AddLight(std::make_shared<Light>(mWorld.get(), Vector3(0.5f, -1.0f, 1.0f)));
	PlayMusic("./res/Sound/Dungeon1_BGM.mp3", DX_PLAYTYPE_LOOP);

	mMenu = MagicMenu(mWorld.get());

	isDraw = true;

}

void GamePlay3::Update(float deltaTime)
{
	if (!isDraw) return;
	if (mFade)
	{
		mFade->Update(deltaTime);
		IsFadeEnd();
		if (isFade) return;
	}
	if (!isPause)
	{
		mWorld->Update(deltaTime);
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

void GamePlay3::Draw() const
{
	if (!isDraw) return;
	mWorld->Draw();
	if (isPause) mMenu.Draw();
	if (mFade) mFade->Draw();
}

bool GamePlay3::IsEnd() const
{
	return isEnd;
}

Scene GamePlay3::Next() const
{
	return mNext;
}

void GamePlay3::End()
{
	AssetStorage::getInstance().Clear();
	SoundManager::getInstance().Clear();
	mWorld = nullptr;
}

void GamePlay3::HandleMessage(EventMessage message, void * param)
{
	switch (message)
	{
	case EventMessage::SCENE_END:
		if (param)
		{
			Scene* next = (Scene*)param;
			mNext = *next;
			mFade = std::make_shared<Fadeeffect>(mWorld.get(), 0.0f, 255.0f, 1.0f, "./res/Texture/Smoke.jpg");
			isFade = true;
		}
		else
		{
			mNext = Scene::STAGE3;
			isEnd = true;
		}
		break;
	case EventMessage::PAUSE:
		isPause = !isPause;
		break;
	}
}

void GamePlay3::MapDateInput(std::string fileName)
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

void GamePlay3::CharacterCreate(std::string name, Vector3& position, Vector3& rotate)
{
	if (name == "Golem") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(mWorld.get(), position, rotate));
	if (name == "Player") mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), position, rotate));
	if (name == "Lizard") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Lizard>(mWorld.get(), position, rotate));
	if (name == "Goblin") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Goblin>(mWorld.get(), position, rotate));
	if (name == "Mummy") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Mummy>(mWorld.get(), position, rotate));
	if (name == "WarpBack") mWorld->AddActor(ActorGroup::Effect, std::make_shared<WarpCircle>(mWorld.get(), position, rotate, Scene::STAGE2_BACK));
	if (name == "Healing") mWorld->AddActor(ActorGroup::Effect, std::make_shared<HealCircle>(mWorld.get(), position, rotate));
	if (name == "MineStone") mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "�A�C�X�j�[�h��", position, MagicList::MAGICMINE));
	if (name == "TrapStone") mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "�g���b�v�X�s�A�[", position, MagicList::TRAPSPEAR));
}

void GamePlay3::IsFadeEnd()
{
	Fadeeffect* temp = (Fadeeffect*)mFade.get();
	if (temp->IsEnd())
	{
		mFade = nullptr;
		if (isFade) isEnd = true;
	}
}