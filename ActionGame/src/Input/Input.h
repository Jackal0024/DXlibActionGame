#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"
#include "KeyNum.h"

class Input
{
public:
	static Input& getInstance(void);
	~Input();
	//ジョイスティック用
	bool GetKeyDown(ButtonCode key);
	bool GetKeyTrigger(ButtonCode key);
	//キーボード用
	bool GetKeyDown(int key);
	bool GetKeyTrigger(int key);
	void Update();
	void Debug();
	VECTOR GetLeftAnalogStick();
	VECTOR GetRightAnalogStick();

private:
	Input();
	VECTOR mInputVectorL;
	VECTOR mInputVectorR;

	bool mButton[32];
	bool mKey[256];
	bool mPrveButton[32];
	bool mPrveKey[256];

	VECTOR mInputVectorLPrev;
	VECTOR mInputVectorRPrev;

};

#endif