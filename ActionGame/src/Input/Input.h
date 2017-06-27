/*
*インプットクラス
*概要：パットとキーボードの入力を管理
*/
#ifndef INPUT_H_
#define INPUT_H_

#include "DxLib.h"
#include "KeyNum.h"
#include"Math\Vector3.h"

class Input
{
public:
	//シングルトン
	static Input& getInstance(void);
	//デストラクタ
	~Input();
	//ジョイスティック用
	bool GetKeyDown(ButtonCode key);
	//トリガー処理
	bool GetKeyTrigger(ButtonCode key);
	//キーボード用
	bool GetKeyDown(int key);
	//キーボード用のトリガー処理
	bool GetKeyTrigger(int key);
	//更新処理
	void Update();
	//デバッグ用の処理
	void Debug();
	//左スティックの入力
	Vector3 GetLeftAnalogStick();
	//右スティックの入力
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