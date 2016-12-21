#include "LoadAssetScnen.h"
#include"../Base/Scene.h"
#include"../../AssetStorage/AssetStorage.h"
#include"../../Sound/SoundManager.h"
#include"../../System/ConstantList/WindowSize.h"

void LoadAssetScnen::Start()
{
	isEnd = false;
	isUpdate = false;
}

void LoadAssetScnen::Update(float deltaTime)
{
	if (!isUpdate)
	{
		isUpdate = true;
		return;
	}
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
	isEnd = true;
}

void LoadAssetScnen::Draw() const
{
	Vector3 pos = Vector3(WIDTH/2,HEIGHT/2,0);
	float len = GetDrawStringWidth("アセットロード", 7);
	pos.x -= len / 2;
	DrawString(pos.x, pos.y, "アセットロード", GetColor(255, 255, 255));
}

bool LoadAssetScnen::IsEnd() const
{
	return isEnd;
}

Scene LoadAssetScnen::Next() const
{
	return Scene::TITLE;
}

void LoadAssetScnen::End()
{
}
