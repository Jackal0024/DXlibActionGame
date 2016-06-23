#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"
#include "KeyNum.h"

class Input
{
public:
	static Input& getInstance(void);
	~Input();
	bool GetKeyDown(Keycode key);
	bool GetKeyTrigger(Keycode key);
	void Update();
	VECTOR GetLeftAnalogStick();
	VECTOR GetRightAnalogStick();

private:
	Input();
	VECTOR mInputVectorL;
	VECTOR mInputVectorR;
	bool mPrevFrameKey = false;
	Keycode mPrevKey;

};

#endif