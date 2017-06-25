#include "TextDraw.h"
#include"../../System/ConstantList/WindowSize.h"

TextDraw::TextDraw(IWorld * world,const std::string& text):
	Actor(world,"Text",Vector3(WIDTH/2,HEIGHT-100,0), Capsule(Vector3(0, 0, 0), 0)),
	mText(text),
	mTimer(0)
{
	int len = GetDrawStringWidth(mText.c_str(), mText.length());
	mPosition.x -= (float)(len / 2);
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
	DrawString((int)mPosition.x, (int)mPosition.y, mText.c_str(), GetColor(255, 255, 255));
}

void TextDraw::onMessage(EventMessage message, void * p)
{
}
