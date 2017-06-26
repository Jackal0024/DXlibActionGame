/*
*ステータスのフレームクラス
*概要：ステータスのフレームＵＩ
*/
#pragma once

#include"../Base/Actor.h"

class Frame : public Actor
{
public:
	Frame(IWorld* world,Vector3 position);
	~Frame();
private:
	void onDraw() const override;

private:
	int mHandle;

};
