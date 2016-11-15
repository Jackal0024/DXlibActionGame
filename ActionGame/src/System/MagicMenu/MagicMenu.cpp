#include "MagicMenu.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Actor/Magic/Base/MagicList.h"
#include"../../Actor/Player/Player.h"

MagicMenu::MagicMenu()
{
}

MagicMenu::MagicMenu(IWorld* world):
	mWorld(world),
	mIndex(0),
	mMagichas(true)
{
	CreateMagicText();
	mUnknownTexture = LoadGraph("./res/Texture/MagicListText/unknown.png");
	mEquipmentTexture = LoadGraph("./res/Texture/MagicListText/Equipment.png");
	auto player = mWorld->FindActor("Player");
	if (!player)
	{
		std::runtime_error("Player not");
	}
	mList = ((Player*)player.get())->GetHaveMagic();
	mCurrentMagic = ((Player*)player.get())->GetCurrentMagic();
}

void MagicMenu::Update(float deltaTime)
{
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_UP))
	{
		mIndex = max(mIndex - 1, 0);
		mMagichas = false;
	}
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_DOWN))
	{
		mIndex = min(mIndex + 1, mTextTexture.size() - 1);
		mMagichas = false;
	}

	for (auto magic : mList)
	{
		if (mIndex == (int)magic) mMagichas = true;
	}

	if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button2) || Input::getInstance().GetKeyTrigger(KEY_INPUT_RETURN))
	{
		if (!mMagichas) return;
		MagicList magic = (MagicList)mIndex;
		mWorld->SendMsg(EventMessage::MAGIC_CHANGE, (void*)&magic);
		PauseEnd();
	}
}

void MagicMenu::Draw() const
{
	DrawGraph(0, 0, mTextTexture[mIndex], TRUE);
	if (!mMagichas) DrawGraph(0, 0, mUnknownTexture, TRUE);
	if(mCurrentMagic == (MagicList)mIndex) DrawGraph(128, 128, mEquipmentTexture, TRUE);
}

MagicMenu::~MagicMenu()
{
	/*for (auto text : mTextTexture)
	{
		DeleteGraph(text);
	}
	mTextTexture.clear();*/
}

void MagicMenu::PauseEnd()
{
	mWorld->SendMsg(EventMessage::PAUSE);
}

void MagicMenu::CreateMagicText()
{
	mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/FireBallText.png"));
	mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/IceNeedleText.png"));
	mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/HealingText.png"));
	mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/RockBlastText.png"));
	mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/FireWallText.png"));
	mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/MainText.png"));
	mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/TrapText.png"));
}
