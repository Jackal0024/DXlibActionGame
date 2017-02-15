#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class GamePlay2 : public IScene
{
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void End() override;
	void HandleMessage(EventMessage message, void* param);

private:
	void MapDateInput(const std::string& fileName);
	void CharacterCreate(const std::string& name, Vector3& position, Vector3& rotate);

	void GolemCreate(Vector3& position, Vector3& rotate);
	void LizardCreate(Vector3& position, Vector3& rotate);
	void IceGolemCreate(Vector3& position, Vector3& rotate);
	void RockGolemCreate(Vector3& position, Vector3& rotate);

	void IsFadeEnd();
private:
	std::shared_ptr<World> mWorld;
	ActorPtr mFade;
	bool isFade;
	Scene mNext;
	MagicMenu mMenu;
	bool isPause;
	bool isEnd;
	bool isDraw;

};
