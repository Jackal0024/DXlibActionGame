#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"

class GamePlay : public IScene
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void End() override;

private:
	void MapDateInput(std::string fileName);
	void CharacterCreate(std::string name,Vector3& position,Vector3& rotate);
private:
	std::shared_ptr<World> mWorld;

};
