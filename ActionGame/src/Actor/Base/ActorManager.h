#pragma once
#include"Actor.h"
#include"ActorPtr.h"
#include"ActorGroup.h"
#include<unordered_map>

class ActorManager
{
public:
	ActorManager();
	void Initialize();
	void Update(float deltaTime);
	void Draw() const;
	void AddActor(ActorGroup group, const ActorPtr& actor);
	ActorPtr FindActor(const std::string& name);
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:

private:
	Actor mRoot;
	std::unordered_map<ActorGroup, ActorPtr> mActor;

};