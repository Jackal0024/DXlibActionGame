#include "ActorManager.h"

ActorManager::ActorManager()
{
	Initialize();
}

void ActorManager::Initialize()
{
	mRoot.ClearChildren();
}

void ActorManager::Update(float deltaTime)
{
	mRoot.Update(deltaTime);
	mRoot.RemoveChildren();
}

void ActorManager::Draw() const
{
	mRoot.Draw();
}

void ActorManager::AddActor(ActorGroup group, const ActorPtr & actor)
{
	mActor[group]->AddChild(actor);
}

ActorPtr ActorManager::FindActor(const std::string & name)
{
	return mRoot.FindChildren(name);
}
