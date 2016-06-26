#ifndef CAMERA_H_
#define CAMERA_H_

#include"../Base/Actor.h"

class Camera : public Actor
{
public:
	//�R���X�g���N�^
	Camera(IWorld* world);

private:
	//�X�V
	virtual void onUpdate(float deltaTime) override;
	//�`��
	virtual void onDraw() const override;

private:
	Vector3 mLook;
	bool DebugMode;
	float mYLook;
};

#endif
