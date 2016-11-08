#include "BackStage1.h"
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

void BackStage1::Start()
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
	mWorld->AddField(std::make_shared<Field>(MV1LoadModel("./res/Map/Stage1/Stage1.mv1")));
	//3Dモデル----------------------------------------------------------------------------------------------------

	MapDateInput("./res/MapData01Back.csv");

	/*mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), Vector3(0, -0.5f, 0)));
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "アイスニードル", Vector3(50.0f, 0.0f, -300), MagicList::ICENEEDLE));
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "ヒーリング", Vector3(0.0f, 0.0f, -300), MagicList::HEALING));
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "ロックブラスト", Vector3(-50.0f, 0.0f, -300), MagicList::ROCKBLAST));
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "ファイアーウォール", Vector3(-50.0f, 0.0f, -250), MagicList::FIREWALL));
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "マジックマイン", Vector3(50.0f, 0.0f, -250), MagicList::MAGICMINE));
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "トラップスピアー", Vector3(0.0f, 0.0f, -250), MagicList::TRAPSPEAR));

	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(mWorld.get(), Vector3(0.0f, 0.0f, -500)));*/
	/*mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Mummy>(mWorld.get(), Vector3(50.0f, 0.0f, -290)));
	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Goblin>(mWorld.get(), Vector3(0.0f, 0.0f, -250)));
	mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Mummy>(mWorld.get(), Vector3(0.0f, 0.0f, -290)));*/
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

void BackStage1::Update(float deltaTime)
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

void BackStage1::Draw() const
{
	if (!isDraw) return;
	mWorld->Draw();
	if (isPause) mMenu.Draw();
	if (mFade) mFade->Draw();
}

bool BackStage1::IsEnd() const
{
	return isEnd;
}

Scene BackStage1::Next() const
{
	return mNext;
}

void BackStage1::End()
{
	AssetStorage::getInstance().Clear();
	SoundManager::getInstance().Clear();
	mWorld = nullptr;
}

void BackStage1::HandleMessage(EventMessage message, void * param)
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
			mNext = Scene::STAGE1_BACK;
			isEnd = true;
		}
		
		break;
	case EventMessage::PAUSE:
		isPause = !isPause;
		break;
	}
}

void BackStage1::MapDateInput(std::string fileName)
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

void BackStage1::CharacterCreate(std::string name, Vector3& position, Vector3& rotate)
{
	if (name == "Golem") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(mWorld.get(), position, rotate));
	if (name == "Player") mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), position, rotate));
	if (name == "Lizard") mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Lizard>(mWorld.get(), position, rotate));
	if (name == "WarpBack") mWorld->AddActor(ActorGroup::Effect, std::make_shared<WarpCircle>(mWorld.get(), position, rotate, Scene::TITLE));
	if (name == "WarpNext") mWorld->AddActor(ActorGroup::Effect, std::make_shared<WarpCircle>(mWorld.get(), position, rotate, Scene::STAGE2));
	if (name == "Healing") mWorld->AddActor(ActorGroup::Effect, std::make_shared<HealCircle>(mWorld.get(), position, rotate));
	if (name == "IceStone") mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "アイスニードル", position, MagicList::ICENEEDLE));
	if (name == "HeelStone") mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "ヒーリング", position, MagicList::HEALING));
}

void BackStage1::IsFadeEnd()
{
	Fadeeffect* temp = (Fadeeffect*)mFade.get();
	if (temp->IsEnd())
	{
		mFade = nullptr;
		if (isFade) isEnd = true;
	}
}
