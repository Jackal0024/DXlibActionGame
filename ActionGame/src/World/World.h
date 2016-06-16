#ifndef WORLD_H_
#define WORLD_H_

#include"IWorld.h"
#include"../Field/FieldPtr.h"
#include"../Actor/Base/ActorManager.h"
#include"../Field/IField.h"

class World : public IWorld
{
public:
	World();
	void Start();
	void Update(float deltaTime);
	void Draw() const;

	virtual void AddActor(ActorGroup group, const ActorPtr& actor) override;
	ActorPtr FindActor(const std::string& name) override;
	void AddCamera(const ActorPtr& camera);
	void AddLight(const ActorPtr& light);
	void AddField(const FieldPtr& field);
	virtual IField& GetField() const override;
	//ToDoフィールドの追加処理

private:
	ActorManager mActors;
	ActorPtr mCamera;
	ActorPtr mLight;
	FieldPtr mField;

};

#endif