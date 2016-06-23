#include "Animator.h"

Animator::Animator():
	mModelHandle(-1),
	mMotionID(-1),
	mTotalTime(0.0f),
	mTimer(0.0f),
	mLerpTimer(1.0f),
	mPrevMotionTimer(0.0f),
	mLoop(false)
{
	
}

Animator::~Animator()
{
}

void Animator::Initialize(int modelhandle, int motionid,bool loop,float timescale)
{
	mTotalTime = 0.0f;
	mTimer = 0.0f;
	mTimerScale = timescale;
	mModelHandle = modelhandle;
	mMotionID = motionid;
	mLoop = loop;

	mAttachIndex = MV1AttachAnim(mModelHandle, mMotionID, -1, FALSE);
	mTotalTime = MV1GetAttachAnimTotalTime(mModelHandle, mAttachIndex);
}

void Animator::Update(float deltatime)
{
	mLerpTimer += 0.05f;
	mLerpTimer = min(mLerpTimer, 1.0f);
	MV1SetAttachAnimBlendRate(mModelHandle, mPrevAttachIndex, 1.0f - mLerpTimer);
	MV1SetAttachAnimBlendRate(mModelHandle,mAttachIndex,mLerpTimer);
	

	if (mLoop && mTimer > mTotalTime)
	{
		mTimer = 0.0f;
	}

	MV1SetAttachAnimTime(mModelHandle, mAttachIndex, mTimer);
	MV1SetAttachAnimTime(mModelHandle, mPrevAttachIndex, mPrevMotionTimer);
	mTimer += (60 * deltatime) * mTimerScale;
}

void Animator::AnimationChange(int motionid,float timescale,bool loop)
{
	if (motionid == mMotionID) return;
	MV1DetachAnim(mModelHandle, mAttachIndex);
	MV1DetachAnim(mModelHandle, mPrevAttachIndex);
	//今のモーションを昔のモーションに
	mPrevAttachIndex = MV1AttachAnim(mModelHandle, mMotionID, -1, FALSE);
	mPrevMotionTimer = mTimer;

	//新しいモーションの作成
	mAttachIndex = MV1AttachAnim(mModelHandle, motionid, -1, FALSE);
	mTotalTime = MV1GetAttachAnimTotalTime(mModelHandle, mAttachIndex);

	//再生時間を元にもどす
	mTimer = 0;
	mLerpTimer = 0.0f;
	mTimerScale = timescale;
	mMotionID = motionid;
}

bool Animator::IsAnimationEnd()
{
	if (mLoop) return false;
	if (mTotalTime < mTimer)
	{
		return true;
	}
	return false;
}
