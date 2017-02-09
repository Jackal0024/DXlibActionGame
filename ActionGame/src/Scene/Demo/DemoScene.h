#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class DemoScene : public IScene
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void End() override;
	void HandleMessage(EventMessage message, void* param);
private:
	int mBackGround;
	int mDemoText;
	float mDemoTextYPos;

	float mTimer;

	bool isEnd;
	bool isDraw;
};