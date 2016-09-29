#pragma once

#include"../Base/Actor.h"

class TextDraw : public Actor
{
public:
	TextDraw(IWorld* world,std::string text);
	~TextDraw();
private:
	void onStart() override;
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onMessage(EventMessage message, void* p) override;

private:
	std::string mText;
	float mTimer;

};
