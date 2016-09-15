#include "World.h"
#include"../Field/Field.h"
#include"../Actor/Base/EventMessage.h"

World::World()
{
}

void World::HandleMessage(EventMessage message, void * param)
{
	mListener(message, param);
	mActors.HandleMessage(message, param);
	mCamera->HandleMessage(message, param);
	mLight->HandleMessage(message, param);
}

void World::Update(float deltaTime)
{
	mActors.Update(deltaTime);
	mCamera->Update(deltaTime);
	mLight->Update(deltaTime);
}

void World::Draw() const
{
	mCamera->Draw();
	mLight->Draw();
	mField->Draw();
	mActors.Draw();
}

void World::AddActor(ActorGroup group, const ActorPtr & actor)
{
	mActors.AddActor(group, actor);
}

ActorPtr World::FindActor(const std::string & name)
{
	return mActors.FindActor(name);
}

void World::AddCamera(const ActorPtr & camera)
{
	mCamera = camera;
}

void World::AddLight(const ActorPtr & light)
{
	mLight = light;
}

void World::AddField(const FieldPtr & field)
{
	mField = field;
}

IField& World::GetField() const
{
	return *mField;
}

void World::SendMsg(EventMessage message, void * param)
{
	HandleMessage(message, param);
}

void World::AddEventMessageListener(std::function<void(EventMessage, void*)> listener)
{
	mListener = listener;
}
