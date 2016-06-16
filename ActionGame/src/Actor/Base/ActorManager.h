#ifndef ACTORMANAGER_H_
#define ACTORMANAGER_H_

#include"Actor.h"
#include"ActorPtr.h"
#include"ActorGroup.h"
#include<unordered_map>

class ActorManager
{
public:
	ActorManager();
	void Initialize();
	void Start();
	void Update(float deltaTime);
	void Draw() const;
	void AddActor(ActorGroup group, const ActorPtr& actor);
	ActorPtr FindActor(const std::string& name);
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	void Collide();

private:
	Actor mRoot;
	std::unordered_map<ActorGroup, ActorPtr> mActor;

};

#endif