#include "TextDraw.h"

TextDraw::TextDraw(IWorld * world, std::string text):
	Actor(world,"Text",Vector3(280,400,0), Capsule(Vector3(0, 0, 0), 0)),
	mText(text),
	mTimer(0)
{
}

TextDraw::~TextDraw()
{
}

void TextDraw::onStart()
{
}

void TextDraw::onUpdate(float deltaTime)
{
	mTimer += deltaTime;
	if (mTimer > 2)
	{
		Dead();
	}
}

void TextDraw::onDraw() const
{
	DrawString(mPosition.x, mPosition.y, mText.c_str(), GetColor(255, 255, 255));
}

void TextDraw::onMessage(EventMessage message, void * p)
{
}