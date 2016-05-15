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

//•Ô‚è’l‚Í-1000‚©‚ç1000
VECTOR Input::GetLeftAnalogStick()
{
	int x, y;
	GetJoypadAnalogInput(&x,&y, DX_INPUT_PAD1);
	mInputVectorL = VGet(x, y, 0.0f);
	return mInputVectorL;
}

//•Ô‚è’l‚Í-1000‚©‚ç1000
VECTOR Input::GetRightAnalogStick()
{
	int x, y;
	GetJoypadAnalogInputRight(&x, &y, DX_INPUT_PAD1);
	mInputVectorR = VGet(x, y, 0.0f);
	return mInputVectorR;
}

Input::Input()
{
}
