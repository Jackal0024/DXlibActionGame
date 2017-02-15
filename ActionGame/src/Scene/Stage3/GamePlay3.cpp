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
#include"../../Actor/Enemy/Mummy/MagicMommy.h"
#include"../../Actor/UI/StateFrame.h"
#include"../../Actor/Gimmick/WarpCircle.h"
#include"../../Actor/Gimmick/HealCircle.h"
#include"../../Actor/Gimmick/MagicStone.h"
#include"../../Actor/Magic/Base/MagicList.h"
#include"../../Actor/UI/FadeEffect.h"
#include"../../Actor/Enemy/Goblin/Goblin.h"
#include"../../Actor/Enemy/Mummy/Mummy.h"

#include"../../Actor/UI/MagicUI.h"
#include"../../Actor/UI/Bar/HPBar.h"
#include"../../Actor/UI/Bar/MPBar.h"
#include"../../Actor/UI/Bar/StaminaBar.h"

#include"../../Actor/Light/PointLight.h"
#include"../../Actor/Gimmick/EnemyGenerator.h"

void GamePlay3::Start()
{
	isEnd = false;
	isPause = false;
	isDraw = false;
	mFade = std::make_shared<Fadeeffect>(mWorld.get(), 255.0f, 0.0f, 1.0f, "./res/Texture/Smoke.jpg");
	isFade = false;

	mWorld = std::make_shared<World>();
	mWorld->AddEventMessageListener(
		[=](EventMessage msg, void* param) {
		HandleMessage(msg, param);
	});
	mWorld->AddField(std::make_shared<Field>(MV1LoadModel("./res/Map/Stage3/Stage3.mv1")));
	//3Dモデル----------------------------------------------------------------------------------------------------
	MapDateInput("./res/MapData/MapData03.csv");
	//UI-----------------------------------------------------------------------------------------------------------
	mWorld->AddActor(ActorGroup::UI, std::make_shared<MagicUI>(mWorld.get(), Vector3(10.0f, 10.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<HPBar>(mWorld.get(), Vector3(77.0f, 15.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<MPBar>(mWorld.get(), Vector3(77.0f, 40.0f, 0.0f)));
	mWorld->AddActor(ActorGroup::UI, std::make_shared<StaminaBar>(mWorld.get(), Vector3(77.0f, 65.0f, 0.0f)));
	//-------------------------------------------------------------------------------------------------------------
	mWorld->AddCamera(std::make_shared<Camera>(mWorld.get()));
	mWorld->AddLight(std::make_shared<PointLight>(mWorld.get()));
	PlayMusic("./res/Sound/Dungeon3_BGM.ogg", DX_PLAYTYPE_LOOP);

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
		if (!mWorld->FindActor("Dead"))
		{
			if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button10) || Input::getInstance().GetKeyTrigger(KEY_INPUT_P))
			{
				mMenu = MagicMenu(mWorld.get());
				isPause = true;
			}
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

void GamePlay3::MapDateInput(const std::string& fileName)
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

void GamePlay3::CharacterCreate(const std::string& name, Vector3& position, Vector3& rotate)
{
	if (name == "Golem") GolemCreate(position,rotate);
	if (name == "Lizard") LizardCreate(position, rotate);
	if (name == "Goblin") GoblinCreate(position, rotate);
	if (name == "MineStone") MagicMummyCreate(position, rotate);
	if (name == "Mummy") MummyCreate(position, rotate);
	if (name == "GuardMummy") GuardMummyCreate(position, rotate);

	if (name == "Player") mWorld->AddActor(ActorGroup::PLAYER, std::make_shared<Player>(mWorld.get(), position, rotate));
	if (name == "TrapStone") mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<MagicStone>(mWorld.get(), "トラップスピアー", position, MagicList::TRAPSPEAR));
	if (name == "WarpBack") mWorld->AddActor(ActorGroup::Effect, std::make_shared<WarpCircle>(mWorld.get(), position, rotate, Scene::STAGE2_BACK));
	if (name == "Healing") mWorld->AddActor(ActorGroup::Effect, std::make_shared<HealCircle>(mWorld.get(), position, rotate));
}

void GamePlay3::GolemCreate(Vector3 & position, Vector3 & rotate)
{
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<EnemyGenerator>(mWorld.get(), [=]()
	{
		return mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Golem>(mWorld.get(), position, rotate, 80, 40));
	}
	));
}

void GamePlay3::LizardCreate(Vector3 & position, Vector3 & rotate)
{
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<EnemyGenerator>(mWorld.get(), [=]()
	{
		return mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Lizard>(mWorld.get(), position, rotate, 210, 60));
	}
	));
}

void GamePlay3::GoblinCreate(Vector3 & position, Vector3 & rotate)
{
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<EnemyGenerator>(mWorld.get(), [=]()
	{
		return mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Goblin>(mWorld.get(), position, rotate, 600, 80));
	}
	));
}

void GamePlay3::MagicMummyCreate(Vector3 & position, Vector3 & rotate)
{
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<EnemyGenerator>(mWorld.get(), [=]()
	{
		return mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<MagicMummy>(mWorld.get(), position, rotate, 200, 40));
	}
	));
}

void GamePlay3::MummyCreate(Vector3 & position, Vector3 & rotate)
{
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<EnemyGenerator>(mWorld.get(), [=]()
	{
		return mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Mummy>(mWorld.get(), position, rotate,false, 150, 40));
	}
	));
}

//ゴブリンの親衛隊のマミーを生成
void GamePlay3::GuardMummyCreate(Vector3 & position, Vector3 & rotate)
{
	mWorld->AddActor(ActorGroup::GIMMICK, std::make_shared<EnemyGenerator>(mWorld.get(), [=]()
	{
		return mWorld->AddActor(ActorGroup::ENEMY, std::make_shared<Mummy>(mWorld.get(), position, rotate,true, 150, 40));
	}
	));
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
