#ifndef IWORLD_H_
#define IWORLD_H_

#include<string>
#include"../Actor/Base/ActorPtr.h"
#include"../Actor/Base/ActorGroup.h"
#include"../Field/IField.h"
#include"../Actor/Base/EventMessage.h"

class IWorld
{
public:
	virtual ~IWorld() {}
	virtual void AddActor(ActorGroup group,const ActorPtr& actor) = 0;
	virtual ActorPtr FindActor(const std::string& name) = 0;
	virtual IField& GetField() const = 0;
	virtual void SendMsg(EventMessage message, void* param = nullptr) = 0;
private:



};

#endif
