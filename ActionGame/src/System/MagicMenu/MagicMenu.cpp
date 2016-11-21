#include "MagicMenu.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Actor/Magic/Base/MagicList.h"
#include"../../Actor/Player/Player.h"
#include"../../Input/Input.h"
#include"../ConstantList/WindowSize.h"

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
	mCursorLeft = LoadGraph("./res/Texture/MagicListText/CursorLeft.png");
	mCursorRight = LoadGraph("./res/Texture/MagicListText/CursorRight.png");
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
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_UP) || StickCheck(Stick::UP))
	{
		mIndex = max(mIndex - 1, 0);
		mMagichas = false;
	}
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_DOWN) || StickCheck(Stick::DOWN))
	{
		mIndex = min(mIndex + 1, mTextTexture.size() - 1);
		mMagichas = false;
	}
	mStickX = Input::getInstance().GetLeftAnalogStick().x;

	for (auto magic : mList)
	{
		if (mIndex == (int)magic) mMagichas = true;
	}

	if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button3) || Input::getInstance().GetKeyTrigger(KEY_INPUT_RETURN))
	{
		if (!mMagichas) return;
		MagicList magic = (MagicList)mIndex;
		mWorld->SendMsg(EventMessage::MAGIC_CHANGE, (void*)&magic);
		PauseEnd();
	}
	if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button4) || Input::getInstance().GetKeyTrigger(KEY_INPUT_BACK))
	{
		PauseEnd();
	}
}

void MagicMenu::Draw() const
{
	DrawGraph(0, 0, mTextTexture[mIndex], TRUE);
	if (!mMagichas) DrawGraph(0, 0, mUnknownTexture, TRUE);
	if(mCurrentMagic == (MagicList)mIndex) DrawGraph(128, 128, mEquipmentTexture, TRUE);
	if(mIndex != 0) DrawGraph(0, (HEIGHT / 2) - 52, mCursorLeft, TRUE);
	if (mIndex != mTextTexture.size() - 1) DrawGraph((WIDTH - 73),(HEIGHT / 2) - 52, mCursorRight, TRUE);
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

bool MagicMenu::StickCheck(Stick dir)
{
	if (Input::getInstance().GetLeftAnalogStick().x == 1 && (mStickX != 1))
	{
		if (dir == Stick::DOWN) return true;
		else return false;
	}
	else if (Input::getInstance().GetLeftAnalogStick().x == -1 && (mStickX != -1))
	{
		if (dir == Stick::UP) return true;
		else return false;
	}
	else
	{
		return false;
	}
}
