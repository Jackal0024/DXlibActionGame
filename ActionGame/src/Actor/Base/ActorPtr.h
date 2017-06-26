/*
*アクターポインタクラス
*概要：アクターをシェアドポインタに変える
*/
#ifndef ACTORPTR_H_
#define ACTORPTR_H_

#include<memory>

class Actor;
using ActorPtr = std::shared_ptr<Actor>;

#endif
