#include "MagicMenu.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"
#include"../../Actor/Magic/Base/MagicList.h"
#include"../../Actor/Player/Player.h"

MagicMenu::MagicMenu()
{
	mFadeTexture = LoadGraph("./res/Texture/FadeBlack.png");
}

MagicMenu::MagicMenu(IWorld* world):
	mWorld(world),
	mIndex(0)
{
	mFadeTexture = LoadGraph("./res/Texture/FadeBlack.png");

	auto player = mWorld->FindActor("Player");
	if (!player)
	{
		std::runtime_error("Player not");
	}
	mList = ((Player*)player.get())->GetHaveMagic();
	ListUp();
}

void MagicMenu::Update(float deltaTime)
{
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_UP))
	{
		mIndex = max(mIndex - 1, 0);
	}
	if (Input::getInstance().GetKeyTrigger(KEY_INPUT_DOWN))
	{
		mIndex = min(mIndex + 1, mList.size()-1);
	}
	if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button2) || Input::getInstance().GetKeyTrigger(KEY_INPUT_RETURN))
	{
		mWorld->SendMsg(EventMessage::MAGIC_CHANGE, (void*)&mList[mIndex]);
		PauseEnd();
	}
}

void MagicMenu::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0,0, mFadeTexture, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	int temp = (int)mList[mIndex];
	DrawString(500, 400,std::to_string(temp).c_str(), GetColor(255, 255, 255));
	//DrawGraph(0, 0, mTextTexture[mIndex], TRUE);
}

MagicMenu::~MagicMenu()
{
}

void MagicMenu::PauseEnd()
{
	mWorld->SendMsg(EventMessage::PAUSE);
}

void MagicMenu::ListUp()
{
	for (int i = 0; i < mList.size(); i++)
	{
		CreateMagicText(mList[i]);
	}
}

void MagicMenu::CreateMagicText(MagicList magic)
{
	switch (magic)
	{
	case MagicList::FIREBALL:
		mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/FireBallText.png"));
		break;
	case MagicList::ICENEEDLE:
		mTextTexture.push_back(LoadGraph("./res/Texture/MagicListText/IceNeedleText.png"));
		break;
	}
}
