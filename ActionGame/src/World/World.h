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
	void HandleMessage(EventMessage message, void* param);
	void Update(float deltaTime);
	void Draw() const;

	virtual ActorPtr AddActor(ActorGroup group, const ActorPtr& actor) override;
	ActorPtr FindActor(const std::string& name) override;
	void AddCamera(const ActorPtr& camera);
	void AddLight(const ActorPtr& light);
	void AddField(const FieldPtr& field);
	virtual IField& GetField() const override;
	virtual ActorPtr GetCamera() const override;
	virtual void SendMsg(EventMessage message, void* param = nullptr)  override;
	void AddEventMessageListener(
		std::function<void(EventMessage, void*)> listener);

private:
	ActorManager mActors;
	ActorPtr mCamera;
	ActorPtr mLight;
	FieldPtr mField;
	//イベントリスナー
	std::function<void(EventMessage, void*)> mListener;

};

#endif