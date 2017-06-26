#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"
#include "KeyNum.h"
#include"Math\Vector3.h"

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
	Vector3 GetLeftAnalogStick();
	Vector3 GetRightAnalogStick();

private:
	Input();
	Vector3 mInputVectorL;
	Vector3 mInputVectorR;

	bool mButton[32];
	bool mKey[256];
	bool mPrveButton[32];
	bool mPrveKey[256];

	Vector3 mInputVectorLPrev;
	Vector3 mInputVectorRPrev;

};

#endif