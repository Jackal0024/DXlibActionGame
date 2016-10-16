#pragma once

#include"../Base/IScene.h"
#include"../../Math/Vector3.h"
#include"../../Math/Matrix.h"

class Title : public IScene
{
private:
	enum State
	{
		DEMO,
		WAIT
	};
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void End() override;

private:
	void StateUpdate(float deltaTime);
	void Demo(float deltaTime);
	void Wait(float deltaTime);
	void PlayerInit();

private:
	bool isEnd;
	int mTitleHandle;
	int mTextHandle;
	int mAlpha;
	State mState;
	int mTitleModel;
	Matrix mRotate = MGetIdent();
	Vector3 mPos;
	float mTimer;

};
