#include "LoadAssetScnen.h"
#include"../Base/Scene.h"
#include"../../AssetStorage/AssetStorage.h"
#include"../../Sound/SoundManager.h"
#include"../../System/ConstantList/WindowSize.h"
#include"../../AssetStorage/EffectStorage.h"

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
	AssetStorage::getInstance().HandleRegister("./res/MagicStoneGolem/golem.mv1", "MagicStoneGolem");
	AssetStorage::getInstance().HandleRegister("./res/overload/overlord_Arm.mv1", "Player");
	AssetStorage::getInstance().HandleRegister("./res/lizard/lizard.mv1", "Lizard");
	AssetStorage::getInstance().HandleRegister("./res/Goblin/Goblin.mv1", "Goblin");
	AssetStorage::getInstance().HandleRegister("./res/Mummy/mummy.mv1", "Mummy");
	AssetStorage::getInstance().HandleRegister("./res/MagicMummy/mummy.mv1", "MagicMummy");
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
	SoundManager::getInstance().Register("./res/Sound/PlayerDead.mp3");
	SoundManager::getInstance().Register("./res/Sound/Healing.mp3");
	SoundManager::getInstance().Register("./res/Sound/PlayerHeal.mp3");
	SoundManager::getInstance().Register("./res/Sound/MagicStoneGet.mp3");
	SoundManager::getInstance().Register("./res/Sound/MagicMine1.mp3");
	SoundManager::getInstance().Register("./res/Sound/MagicMine2.mp3");
	SoundManager::getInstance().Register("./res/Sound/Spear.mp3");
	SoundManager::getInstance().Register("./res/Sound/Trap.mp3");
	SoundManager::getInstance().Register("./res/Sound/FireWall.mp3");
	SoundManager::getInstance().Register("./res/Sound/Rock.mp3");
	SoundManager::getInstance().Register("./res/Sound/Warp.mp3");
	SoundManager::getInstance().Register("./res/Sound/PowerUp.mp3");
	SoundManager::getInstance().Register("./res/Sound/MagicUp.mp3");
	SoundManager::getInstance().Register("./res/Sound/MenuClose.mp3");
	SoundManager::getInstance().Register("./res/Sound/MenuOpen.mp3");
	SoundManager::getInstance().Register("./res/Sound/MenuSubmit.mp3");
	SoundManager::getInstance().Register("./res/Sound/MenuSelect.mp3");
	SoundManager::getInstance().Register("./res/Sound/ResultEffect.mp3");

	EffectStorage::getInstance().HandleRegister("./res/Effect/FireEffect.efk",EffectList::FireBallEffect);
	EffectStorage::getInstance().HandleRegister("./res/Effect/Hit.efk",EffectList::HitEffect);
	EffectStorage::getInstance().HandleRegister("./res/Effect/IceNeedleEffect.efk", EffectList::IceNeedleEffect);
	EffectStorage::getInstance().HandleRegister("./res/Effect/MagicMine.efk", EffectList::MagicMineEffect);
	EffectStorage::getInstance().HandleRegister("./res/Effect/FireWall.efk", EffectList::FireWallEffect);

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
