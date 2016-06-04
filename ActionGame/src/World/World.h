#pragma once
#include"IWorld.h"
#include"../Actor/Base/ActorManager.h"

class World : public IWorld
{
public:
	World();
	void Update(float deltaTime);
	void Draw() const;

	virtual void AddActor(ActorGroup group, const ActorPtr& actor) override;
	void AddCamera(const ActorPtr& camera);
	void AddLight(const ActorPtr& light);
	//ToDoフィールドの追加処理

private:
	ActorManager mActors;
	ActorPtr mCamera;
	ActorPtr mLight;
	//Todoフィールド変数

};