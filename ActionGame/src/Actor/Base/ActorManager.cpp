#include "ActorManager.h"

ActorManager::ActorManager()
{
	Initialize();
}

void ActorManager::Initialize()
{
	mActor[ActorGroup::PLAYER] = std::make_shared<Actor>();
	mActor[ActorGroup::PLAYERATTACK] = std::make_shared<Actor>();
	mActor[ActorGroup::ENEMY] = std::make_shared<Actor>();
	mRoot.ClearChildren();
	mRoot.AddChild(mActor[ActorGroup::PLAYER]);
	mRoot.AddChild(mActor[ActorGroup::PLAYERATTACK]);
	mRoot.AddChild(mActor[ActorGroup::ENEMY]);
}

void ActorManager::Start()
{
	mRoot.Start();
}

void ActorManager::Update(float deltaTime)
{
	mRoot.Update(deltaTime);
	Collide();
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

void ActorManager::Collide()
{
	mActor[ActorGroup::PLAYER]->CollideChildren(*mActor[ActorGroup::ENEMY]);
	mActor[ActorGroup::PLAYERATTACK]->CollideChildren(*mActor[ActorGroup::ENEMY]);
}
