#pragma once

#include"../Base/IScene.h"
#include"../../Math/Vector3.h"
#include"../../Math/Matrix.h"

class LoadAssetScnen : public IScene
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void End() override;

private:
	bool isUpdate;
	bool isEnd;

};