#pragma once

#include"../World/World.h"

class Game
{
public:
	Game();
	~Game();
	void initialize();
	void Update();
	void Draw();
	void Finish();

private:
	std::shared_ptr<World> mWorld;;

};