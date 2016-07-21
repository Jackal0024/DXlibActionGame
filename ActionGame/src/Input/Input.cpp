#include "Input.h"

Input & Input::getInstance(void)
{
	static Input input;
	return input;
}

Input::~Input()
{
}

bool Input::GetKeyDown(ButtonCode key)
{
	return mButton[key];
}


bool Input::GetKeyTrigger(ButtonCode key)
{
	return mButton[key] && !mPrveButton[key];
}

bool Input::GetKeyDown(int key)
{
	return mKey[key];
}

bool Input::GetKeyTrigger(int key)
{
	return mKey[key] && !mPrveKey[key];
}

void Input::Update()
{
	DINPUT_JOYSTATE tempButton;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &tempButton);
	for (int i = 0; i < 32; i++)
	{
		mPrveButton[i] = mButton[i];
		if (tempButton.Buttons[i] == 128)
		{
			
			mButton[i] = true;
		}
		else
		{
			mButton[i] = false;
		}
	}

	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) 
	{
		mPrveKey[i] = mKey[i];
		if (tmpKey[i] != 0) {
			mKey[i] = true;
		}
		else 
		{              
			mKey[i] = false;
		}
	}
}

void Input::Debug()
{
}

//返り値は-1から1
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

//返り値は-1から1
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
