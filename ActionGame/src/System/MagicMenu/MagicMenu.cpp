#include "MagicMenu.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Actor/Magic/Base/MagicList.h"
#include"../../Actor/Player/Player.h"
#include"../../Input/Input.h"
#include"../ConstantList/WindowSize.h"
#include"../../Sound/SoundManager.h"

MagicMenu::MagicMenu()
{
}

MagicMenu::MagicMenu(IWorld* world):
	mWorld(world),
	mIndex(0),
	mMagichas(false)
{
	CreateMagicText();
	mUnknownTexture = LoadGraph("./res/Texture/MagicListText/unknown.png");
	mEquipmentTexture = LoadGraph("./res/Texture/MagicListText/Equipment.png");
	mCursorLeft = LoadGraph("./res/Texture/MagicListText/CursorLeft.png");
	mCursorRight = LoadGraph("./res/Texture/MagicListText/CursorRight.png");
	mHelpTexture = LoadGraph("./res/Texture/MagicListText/help.png");
	auto player = mWorld->FindActor("Player");
	if (!player)
	{
		std::runtime_error("Player not");
	}
	mList = ((Player*)player.get())->GetHaveMagic();
	for (auto magic : mList)
	{
		if (mIndex == (int)magic) mMagichas = true;
	}
	mCurrentMagic = ((Player*)player.get())->GetCurrentMagic();
	SoundManager::getInstance().Play("./res/Sound/MenuOpen.mp3");
}

void MagicMenu::Update(float deltaTime)
{
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_UP) || StickCheck(Stick::UP))
	{
		SoundManager::getInstance().Play("./res/Sound/MenuSelect.mp3");
		mIndex = max(mIndex - 1, 0);
		mMagichas = false;
	}
	else if (Input::getInstance().GetKeyTrigger(KEY_INPUT_DOWN) || StickCheck(Stick::DOWN))
	{
		SoundManager::getInstance().Play("./res/Sound/MenuSelect.mp3");
		mIndex = min((mIndex + 1), (int)mTextTexture.size() - 1);
		mMagichas = false;
	}
	//連続で移動しないように前回の傾きを調べる;
	mStickX = (int)Input::getInstance().GetLeftAnalogStick().x;

	for (auto magic : mList)
	{
		if (mIndex == (int)magic) mMagichas = true;
	}

	if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button2) || Input::getInstance().GetKeyTrigger(KEY_INPUT_RETURN))
	{
		if (!mMagichas) return;
		SoundManager::getInstance().Play("./res/Sound/MenuSubmit.mp3");
		MagicList magic = (MagicList)mIndex;
		mWorld->SendMsg(EventMessage::MAGIC_CHANGE, (void*)&magic);
		PauseEnd();
	}
	if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button3) || Input::getInstance().GetKeyTrigger(KEY_INPUT_BACK))
	{
		SoundManager::getInstance().Play("./res/Sound/MenuClose.mp3");
		PauseEnd();
	}
}

void MagicMenu::Draw() const
{
	DrawGraph(0, 0, mTextTexture[mIndex], TRUE);
	if (!mMagichas) DrawGraph(0, 0, mUnknownTexture, TRUE);
	if(mCurrentMagic == (MagicList)mIndex) DrawGraph(128, 128, mEquipmentTexture, TRUE);
	if(mIndex != 0) DrawGraph(0, (HEIGHT / 2) - 52, mCursorLeft, TRUE);
	if (mIndex != (int)mTextTexture.size() - 1) DrawGraph((WIDTH - 73),(HEIGHT / 2) - 52, mCursorRight, TRUE);
	DrawGraph(670, 480, mHelpTexture, TRUE);
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

//ステイックを見てメニューを左右に移動する（連続で移動しないようにする）
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
