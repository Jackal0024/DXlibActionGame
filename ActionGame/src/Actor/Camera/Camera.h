#ifndef CAMERA_H_
#define CAMERA_H_

#include"../Base/Actor.h"

class Camera : public Actor
{
public:
	//コンストラクタ
	Camera(IWorld* world);

private:
	//更新
	virtual void onUpdate(float deltaTime) override;
	//描画
	virtual void onDraw() const override;

private:
	Vector3 mLook;
	bool DebugMode;
	float mYLook;
};

#endif
