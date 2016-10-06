#include "MagicMenu.h"
#include"../../Input/Input.h"
#include"../../Input/KeyNum.h"

MagicMenu::MagicMenu()
{
	mFadeTexture = LoadGraph("./res/Texture/FadeBlack.png");
}

MagicMenu::MagicMenu(IWorld* world):
	mWorld(world)
{
	mFadeTexture = LoadGraph("./res/Texture/FadeBlack.png");
}

void MagicMenu::Update(float deltaTime)
{
	if (Input::getInstance().GetKeyTrigger(ButtonCode::PAD_Button2) || Input::getInstance().GetKeyTrigger(KEY_INPUT_P))
	{
		PauseEnd();
	}
}

void MagicMenu::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0,0, mFadeTexture, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

MagicMenu::~MagicMenu()
{
}

void MagicMenu::PauseEnd()
{
	mWorld->SendMsg(EventMessage::PAUSE);
}
