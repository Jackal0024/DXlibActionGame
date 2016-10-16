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
	mActor[ActorGroup::ENEMYATTACK] = std::make_shared<Actor>();
	mActor[ActorGroup::UI] = std::make_shared<Actor>();
	mActor[ActorGroup::Effect] = std::make_shared<Actor>();
	mActor[ActorGroup::GIMMICK] = std::make_shared<Actor>();
	mRoot.ClearChildren();
	mRoot.AddChild(mActor[ActorGroup::UI]);
	mRoot.AddChild(mActor[ActorGroup::Effect]);
	mRoot.AddChild(mActor[ActorGroup::PLAYER]);
	mRoot.AddChild(mActor[ActorGroup::PLAYERATTACK]);
	mRoot.AddChild(mActor[ActorGroup::ENEMY]);
	mRoot.AddChild(mActor[ActorGroup::ENEMYATTACK]);
	mRoot.AddChild(mActor[ActorGroup::GIMMICK]);
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

void ActorManager::HandleMessage(EventMessage message, void * param)
{
	mRoot.HandleMessage(message, param);
}

void ActorManager::Collide()
{
	mActor[ActorGroup::PLAYER]->CollideChildren(*mActor[ActorGroup::ENEMY]);
	mActor[ActorGroup::PLAYER]->CollideChildren(*mActor[ActorGroup::GIMMICK]);
	mActor[ActorGroup::PLAYER]->CollideChildren(*mActor[ActorGroup::ENEMYATTACK]);
	mActor[ActorGroup::PLAYERATTACK]->CollideChildren(*mActor[ActorGroup::ENEMY]);
}
