#ifndef  ANIMATOR_H_
#define  ANIMATOR_H_

#include"DxLib.h"

class Animator
{
public:
	Animator();
	~Animator();
	void Initialize(int modelhandle, int motionid,bool loop = false,float timescale = 0.5f);
	void Update(float deltatime);
	void AnimationChange(int motionid,float changeTimer,float timescale = 1, bool loop = false);
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