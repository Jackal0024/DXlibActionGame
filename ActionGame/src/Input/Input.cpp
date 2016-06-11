#include "Input.h"

Input & Input::getInstance(void)
{
	static Input input;
	return input;
}

Input::~Input()
{
}

bool Input::GetKeyDown(Keycode key)
{
	if(GetJoypadNum > 0) return (GetJoypadInputState(DX_INPUT_PAD1) & key) != 0;
	return CheckHitKey(key) != 0;
}

//•Ô‚è’l‚Í-1‚©‚ç1
VECTOR Input::GetLeftAnalogStick()
{

		int x = 0, y = 0;
		GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
		if (CheckHitKey(KEY_INPUT_W))
		{
			y = -1000;
		}
		else if (CheckHitKey(KEY_INPUT_S))
		{
			y = 1000;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			x = 1000;
		}
		else if (CheckHitKey(KEY_INPUT_A))
		{
			x = -1000;
		}
		mInputVectorL = VGet(x, -y, 0.0f) / 1000;
		return mInputVectorL;
}

//•Ô‚è’l‚Í-1‚©‚ç1
VECTOR Input::GetRightAnalogStick()
{
	int x = 0, y = 0;
	GetJoypadAnalogInputRight(&x, &y, DX_INPUT_PAD1);
	mInputVectorR = VGet(x, y, 0.0f);
	if (CheckHitKey(KEY_INPUT_UP))
	{
		y = 1000;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		y = -1000;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		x = 1000;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		x = -1000;
	}
	mInputVectorR = VGet(x, y, 0.0f) / 1000;
	return mInputVectorR;
}

Input::Input()
{
}
