#pragma once

#include"IScene.h"

class SceneNull : public IScene
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void End() override;


};
