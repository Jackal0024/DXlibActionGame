#include "World.h"

World::World()
{
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
