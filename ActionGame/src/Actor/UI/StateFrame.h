/*
*�X�e�[�^�X�̃t���[���N���X
*�T�v�F�X�e�[�^�X�̃t���[���t�h
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
