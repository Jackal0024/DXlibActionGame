#pragma once

#include"../Base/Actor.h"
#include"../../Math/Vector3.h"

class Light : public Actor
{
public:
	//�R���X�g���N�^
	Light(IWorld& world, const Vector3& position);
private:
	//�`��
	virtual void onDraw() const override;
};
