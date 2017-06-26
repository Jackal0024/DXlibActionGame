/*
*シーンポインタ
*概要：シーン型をシェアドポインタに変える
*/
#pragma once
#include<memory>

class IScene;
using IScenePtr = std::shared_ptr<IScene>;
