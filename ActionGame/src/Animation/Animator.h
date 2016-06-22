#ifndef  ANIMATOR_H_
#define  ANIMATOR_H_

#include"DxLib.h"

class Animator
{
public:
	Animator();
	~Animator();
	void Initialize(int modelhandle, int motionid,bool loop = false);
	void Update(float deltatime);
	void AnimationChange(int motionid,float timescale = 60, bool loop = false);
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
	bool mLoop;
};

#endif