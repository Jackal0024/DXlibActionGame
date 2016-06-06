#pragma once

#include"../Base/Actor.h"
#include"../../Math/Vector3.h"

class Light : public Actor
{
public:
	//コンストラクタ
	Light(IWorld& world, const Vector3& position);
private:
	//描画
	virtual void onDraw() const override;
};
