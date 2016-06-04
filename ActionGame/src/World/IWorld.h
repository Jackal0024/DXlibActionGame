#pragma once

#include<string>
#include"../Actor/Base/ActorPtr.h"
#include"../Actor/Base/ActorGroup.h"

class IWorld
{
public:
	virtual ~IWorld() {}
	virtual void AddActor(ActorGroup group,const ActorPtr& actor) = 0;
	virtual ActorPtr FindActor(const std::string& name) = 0;
private:

};
