/*
*アニメータークラス
*概要：アニメーションを管理する
*/
#ifndef  ANIMATOR_H_
#define  ANIMATOR_H_

#include"DxLib.h"

class Animator
{
public:
	//コンストラクタ
	Animator();
	//デストラクタ
	~Animator();
	//初期化処理
	void Initialize(int modelhandle, int motionid,bool loop = false,float timescale = 0.5f);
	//更新処理
	void Update(float deltatime);
	//アニメーションを変える
	void AnimationChange(int motionid,float changeTimer,float timescale = 1, bool loop = false);
	//アニメーションが終わっているか？
	bool IsAnimationEnd();

private:
	int mModelHandle;
	int mMotionID;
	int mPrevMotionID;
	

	int mAttachIndex;
	int mPrevAttachIndex;

	float mTimerScale;
	float mTotalTime;
	float mTimer;
	float mPrevMotionTimer;
	float mLerpTimer;
	float mChangeTime;
	bool mLoop;
};

#endif